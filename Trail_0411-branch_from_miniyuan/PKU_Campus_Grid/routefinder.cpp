#include "routefinder.h"
#include "ui_routefinder.h"
#include "languagemanager.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>
#include <cmath>
#include <QToolButton>
#include <QPushButton>
#include <QDebug>

// 路径查询功能

RouteFinder::RouteFinder(MapView *mapView, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RouteFinder)
    , mapView(mapView)
    , dj(new DijkstraFindPath())
{
    ui->setupUi(this);

    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    // 返回按钮
    QToolButton *returnButton = langManager->createTranslatableToolButton("RouteFinder", tr("返回导航"), this);
    returnButton->setIcon(QIcon(":/icon/return.png"));
    returnButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(returnButton, &QToolButton::clicked, this, &RouteFinder::requestReturn);

    // 创建垂直排列的控件组
    QGroupBox *controlGroup = langManager->createTranslatableGroupBox("RouteFinder", tr("路径规划设置"), this);
    QGridLayout *gridLayout = new QGridLayout(controlGroup);

    // 起点选择
    QLabel *startLabel = langManager->createTranslatableLabel("RouteFinder", tr("起点:"), this);
    startComboBox = new QComboBox(this);
    gridLayout->addWidget(startLabel, 0, 0);
    gridLayout->addWidget(startComboBox, 0, 1);

    // 终点选择
    QLabel *endLabel = langManager->createTranslatableLabel("RouteFinder", tr("终点:"), this);
    endComboBox = new QComboBox(this);
    gridLayout->addWidget(endLabel, 1, 0);
    gridLayout->addWidget(endComboBox, 1, 1);

    // 路径搜索按钮
    QPushButton *findPathButton = langManager->createTranslatablePushButton("RouteFinder", tr("搜索路径"), this);
    gridLayout->addWidget(findPathButton, 2, 0, 1, 2); // 跨两列

    // 连接信号
    connect(startComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setStartStation()));
    connect(endComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setEndStation()));
    connect(findPathButton, &QPushButton::clicked, this, &RouteFinder::triggerFindPath);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(returnButton);
    mainLayout->addWidget(controlGroup);

    setLayout(mainLayout);

    // 加载顶点信息
    loadVertices();
}

RouteFinder::~RouteFinder()
{
    delete ui;
}

void RouteFinder::loadVertices() {
    QFile file(":/info/building_info.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(' ');
        if (parts.size() >= 3) {
            QString name = parts[0];
            bool okX, okY;
            double x = parts[1].toDouble(&okX);
            double y = parts[2].toDouble(&okY);

            if (okX && okY) {
                nameToLocMap.insert(name, qMakePair(x, y));
                startComboBox->addItem(name);
                endComboBox->addItem(name);
                indexToNameMap.append(name);
            } else {
                qDebug() << "Invalid coordinates for building:" << name;
            }
        }
    }
    file.close();

    dj->loadVertices();
}

void RouteFinder::drawPath(const QVector<int>& path) {
    if (!mapView) {
        qDebug() << "MapView is not available";
        return;
    }

    // 清除旧路径
    mapView->clearPath();

    if (path.isEmpty()) {
        qDebug() << "Path is empty!";
        return;
    }

    // 创建路径点集合
    QList<QPointF> pathPoints;

    for (int i = 0; i < path.size(); ++i) {
        int index = path[i];
        if (index < 0 || index >= indexToNameMap.size()) {
            qDebug() << "Invalid index in path:" << index;
            continue;
        }

        QString buildingName = indexToNameMap[index];
        if (!nameToLocMap.contains(buildingName)) {
            qDebug() << "Building not found:" << buildingName;
            continue;
        }

        QPair<double, double> coords = nameToLocMap.value(buildingName);
        pathPoints.append(QPointF(coords.first, coords.second));
    }

    // 绘制路径到地图
    mapView->drawPath(pathPoints);

    // 可选：聚焦到路径
    mapView->focusOnPath(pathPoints);
}

void RouteFinder::setStart(double X, double Y) {
    startX = X;
    startY = Y;
    emit startStationChanged(X, Y);
}

void RouteFinder::setEnd(double X, double Y) {
    endX = X;
    endY = Y;
    emit endStationChanged(X, Y);
}

void RouteFinder::triggerFindPath() {
    FindPath();
}

void RouteFinder::setStartStation() {
    QString selectedStart = startComboBox->currentText();
    if (nameToLocMap.contains(selectedStart)) {
        QPair<double, double> startCoords = nameToLocMap.value(selectedStart);
        setStart(startCoords.first, startCoords.second);
    }
}

void RouteFinder::setEndStation() {
    QString selectedEnd = endComboBox->currentText();
    if (nameToLocMap.contains(selectedEnd)) {
        QPair<double, double> endCoords = nameToLocMap.value(selectedEnd);
        setEnd(endCoords.first, endCoords.second);
    }
}

void RouteFinder::FindPath()
{
    if (startComboBox->currentIndex() < 0 || endComboBox->currentIndex() < 0) {
        qDebug() << "Please select both start and end points";
        return;
    }

    int startIndex = startComboBox->currentIndex();
    int endIndex = endComboBox->currentIndex();

    dj->dijkstra(startIndex);
    QVector<int> path = dj->get_Path(endIndex);

    if (path.isEmpty()) {
        qDebug() << "No path found between"
                 << startComboBox->currentText()
                 << "and"
                 << endComboBox->currentText();
        return;
    }

    qDebug() << "Path found with" << path.size() << "points";
    drawPath(path);
    emit pathFound(path);
}

void RouteFinder::DijkstraFindPath::loadVertices()
{
    indexToLocMap.clear();

    QFile verFile(":/info/building_info.txt");
    if (!verFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open verFile";
        return;
    }

    QTextStream verIn(&verFile);
    int num = 0; // 从0开始索引
    while (!verIn.atEnd()) {
        QString line = verIn.readLine();
        QStringList parts = line.split(' ');
        if (parts.size() >= 3) {
            bool okX, okY;
            double x = parts[1].toDouble(&okX);
            double y = parts[2].toDouble(&okY);

            if (okX && okY) {
                indexToLocMap.insert(num, qMakePair(x, y));
                num++;
            }
        }
    }
    verFile.close();

    // 初始化图结构
    mgraph.vexnum = num;
    mgraph.vexs.clear();
    for (int i = 0; i < mgraph.vexnum; i++) {
        mgraph.vexs.push_back(i);
    }

    // 初始化邻接矩阵
    for (int i = 0; i < mgraph.vexnum; i++) {
        for (int j = 0; j < mgraph.vexnum; j++) {
            if (i == j) {
                mgraph.arcs[i][j].adj = 0;
            } else {
                mgraph.arcs[i][j].adj = mgraph.arcs[j][i].adj = INF;
            }
        }
    }

    QFile edgeFile(":/info/connected_vertices.txt");
    if (!edgeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open edgeFile";
        return;
    }
    QTextStream edgeIn(&edgeFile);
    while (!edgeIn.atEnd()) {
        QString line = edgeIn.readLine();
        QStringList parts = line.split(' ');
        if (parts.size() >= 2) {
            bool okX, okY;
            int x = parts[0].toInt(&okX);
            int y = parts[1].toInt(&okY);
            x--; y--;

            if (okX && okY) {
                mgraph.arcs[x][y].adj = mgraph.arcs[y][x].adj = manhattan(indexToLocMap.value(x), indexToLocMap.value(y));
            }
        }
    }
    edgeFile.close();
}

double RouteFinder::DijkstraFindPath::manhattan(const QPair<double, double>& x, const QPair<double, double>& y)
{
    return std::abs(x.first - y.first) + std::abs(x.second - y.second);
}

RouteFinder::DijkstraFindPath::DijkstraFindPath() {
    // 初始化成员变量
    mgraph.vexnum = 0;

    // 初始化为足够大的值
    const int MAX_VERTICES = 200;
    for (int i = 0; i < MAX_VERTICES; i++) {
        d[i] = INF;
        used[i] = false;
        prev[i] = -1;
        for (int j = 0; j < MAX_VERTICES; j++) {
            mgraph.arcs[i][j].adj = INF;
        }
    }

    // 加载顶点
    loadVertices();
}

void RouteFinder::DijkstraFindPath::dijkstra(int startPos)
{
    if (startPos < 0 || startPos >= mgraph.vexnum) {
        qDebug() << "Invalid start position:" << startPos;
        return;
    }

    // 初始化
    for (int i = 0; i < mgraph.vexnum; i++) {
        d[i] = INF;
        used[i] = false;
        prev[i] = -1;
    }

    d[startPos] = 0;

    for (int iter = 0; iter < mgraph.vexnum; iter++) {
        int v = -1;
        for (int u = 0; u < mgraph.vexnum; u++) {
            if (!used[u] && (v == -1 || d[u] < d[v])) {
                v = u;
            }
        }

        if (v == -1 || d[v] == INF) break;
        used[v] = true;

        for (int u = 0; u < mgraph.vexnum; u++) {
            double weight = mgraph.arcs[v][u].adj;
            if (!used[u] && weight < INF && d[u] > d[v] + weight) {
                d[u] = d[v] + weight;
                prev[u] = v;
            }
        }
    }
}

QVector<int> RouteFinder::DijkstraFindPath::get_Path(int endPos)
{
    QVector<int> path;
    if (endPos < 0 || endPos >= mgraph.vexnum || d[endPos] == INF) {
        qDebug() << "No path to position:" << endPos;
        return path;
    }

    for (int pos = endPos; pos != -1; pos = prev[pos]) {
        path.push_back(pos);
    }

    if (path.size() > 1) {
        std::reverse(path.begin(), path.end());
    }

    return path;
}
