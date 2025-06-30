#include "mapview.h"
#include "momentedit.h"
#include "bookmarkmanager.h"
#include "slotmachinedialog.h"

#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QWheelEvent>
#include <QScrollBar>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QPropertyAnimation>
#include <QSettings>
#include <QDomDocument>
#include <QSvgRenderer>
#include <QGraphicsColorizeEffect>
#include<QGraphicsEffect>
// 地图界面

MapView::MapView(QWidget *parent)
    : QGraphicsView(parent)
{
    // 加载 SVG 地图
    scene = new QGraphicsScene(this);
    mainSvgItem = new QGraphicsSvgItem(":/assets/ground_new.svg");
    scene->addItem(mainSvgItem);

    // 加载需要高亮的建筑ID
    loadHighlightBuildings();
    processBuildings();

    // 设置场景和视图
    this->setScene(scene);
    this->setMinimumSize(600, 600);

    // 启用优化显示
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // 创建时间标签
    timeLabel = new QLabel(this->viewport()); // 添加到视口
    timeLabel->setObjectName("mapTimeLabel");

    QPropertyAnimation *anim = new QPropertyAnimation(timeLabel, "geometry");
    anim->setDuration(2000);
    anim->setLoopCount(-1); // 无限循环
    anim->setKeyValueAt(0, QRect(10, 10, 140, 28));
    anim->setKeyValueAt(0.5, QRect(10, 8, 140, 28));  // 上移2px
    anim->setKeyValueAt(1, QRect(10, 10, 140, 28));
    anim->start();
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setFixedSize(300, 30);
    timeLabel->move(200, 10); // 初始位置

    // 创建定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MapView::updateTime);
    timer->start(1000);
    updateTime(); // 立即显示时间

    // 确保时间标签始终在最前
    timeLabel->raise();
}

void MapView::updateTime()
{
    timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
}

MapView::~MapView()
{
    delete scene;
    delete mainSvgItem;
}

void MapView::moveBy(int dx, int dy)
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + dx);
    verticalScrollBar()->setValue(verticalScrollBar()->value() + dy);
}

void MapView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor); // 放大
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor); // 缩小
    }
}

void MapView::zoomIn()
{
    scale(scaleFactor, scaleFactor);
}

void MapView::zoomOut()
{
    scale(1.0 / scaleFactor, 1.0 / scaleFactor);
}

void MapView::keyPressEvent(QKeyEvent *event)
{
    const int moveStep = 50; // 每次移动的步长

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        moveBy(-moveStep, 0); // 向左移动
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        moveBy(moveStep, 0); // 向右移动
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        moveBy(0, -moveStep); // 向上移动
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        moveBy(0, moveStep); // 向下移动
        break;
    default:
        QGraphicsView::keyPressEvent(event); // 调用基类的 keyPressEvent
        break;
    }
}

void MapView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF logicalPos = mapToScene(event->pos());

        // 检查Ctrl+点击创建动态
        if (event->modifiers() & Qt::ControlModifier) {
            handleMomentCreation(logicalPos);
            event->accept();
            return;
        }

        // 检查Shift+点击处理建筑点击
        if (event->modifiers() & Qt::ShiftModifier) {
            handleMapClick(logicalPos);
            event->accept();
            return;
        }

        // 普通点击处理建筑高亮
        handleBuildingHighlight(logicalPos);
        event->accept();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void MapView::handleMapClick(const QPointF &scenePos)
{
    if (!m_bookmarkManager) return;

    const int clickRadius = 20; // 点击敏感半径(像素)

    for (const auto &building : m_bookmarkManager->rtBuildings()) {
        qreal distance = QLineF(scenePos, building.position).length();
        if (distance <= clickRadius) {
            emit buildingClicked(building.name);
            return;
        }
    }
}

void MapView::handleBuildingHighlight(const QPointF &scenePos)
{
    QGraphicsItem* item = scene->itemAt(scenePos, transform());
    if (QGraphicsSvgItem* svgItem = qgraphicsitem_cast<QGraphicsSvgItem*>(item)) {
        QString id = svgItem->elementId();

        // 只处理在highlightBuildingIds集合中的建筑ID
        if (!highlightBuildingIds.contains(id)) {
            qDebug() << "点击了非高亮建筑:" << id;
            return;
        }

        qDebug() << "点击高亮建筑:" << id;

        // 切换高亮状态
        if (id == m_highlightId) {
            if (m_highlightItem) {
                m_highlightItem->setGraphicsEffect(nullptr);
                m_highlightItem = nullptr;
                m_highlightId = "";
            }
        } else {
            if (m_highlightItem) {
                m_highlightItem->setGraphicsEffect(nullptr);
                m_highlightItem = nullptr;
                m_highlightId = "";
            }

            QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(this);
            effect->setColor(Qt::red);
            effect->setStrength(0.7);

            item->setGraphicsEffect(effect);
            m_highlightItem = svgItem;
            m_highlightId = id;
        }
    }
}


void MapView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);  // 先调用父类处理
    emit resized();  // 发出尺寸变化信号
}

void MapView::drawPath(const QList<QPointF>& pathPoints) {
    qDebug() << "=== Start Drawing Path ===";
    clearPath();

    if (pathPoints.isEmpty()) {
        qDebug() << "Error: Empty path points!";
        return;
    }

    QPainterPath painterPath;
    painterPath.moveTo(pathPoints.first());
    qDebug() << "Path starts at:" << pathPoints.first();

    // 样式配置
    const QColor pathColor(30, 144, 255);       // 道奇蓝
    const QColor markerColor(255, 69, 0);       // 橙红标记点
    const QColor labelBgColor(0, 0, 0, 150);    // 半透明黑色标签背景
    const qreal markerRadius = 4.0;             // 标记点半径

    QLinearGradient gradient(0, 0, 1, 0); // 水平渐变
    gradient.setColorAt(0, QColor(30, 144, 255)); // 起始颜色
    gradient.setColorAt(1, QColor(255, 105, 180)); // 结束颜色
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode); // 渐变模式

    for (int i = 0; i < pathPoints.size(); i++) {
        const QPointF& point = pathPoints[i];
        qDebug() << "Point" << i << ":" << point;

        // 1. 绘制标记点（带发光效果）
        if (i==0||i==pathPoints.size()-1){
            QGraphicsEllipseItem* marker = new QGraphicsEllipseItem(
                point.x() - markerRadius/2,
                point.y() - markerRadius/2,
                markerRadius,
                markerRadius
                );
            marker->setBrush(markerColor);
            marker->setPen(Qt::NoPen);
            scene->addItem(marker);
            pathItems.append(marker);
        }


        // 2. 添加序号标签（带背景）
        QGraphicsSimpleTextItem* label = new QGraphicsSimpleTextItem(QString::number(i + 1));
        // 修改这行代码：将标签放在标记点左上角（x和y都减去半径）
        label->setPos(point.x() - markerRadius - 8, point.y() - markerRadius - 8);  // 调整-15和-8为适当偏移量
        label->setBrush(Qt::black);
        label->setFont(QFont("Arial", 8, QFont::Bold));

        // 标签背景（圆角矩形）
        QGraphicsRectItem* labelBg = new QGraphicsRectItem(
            label->boundingRect().adjusted(-2, -2, 2, 2)
            );
        labelBg->setPos(label->pos());
        labelBg->setBrush(labelBgColor);
        labelBg->setPen(Qt::NoPen);
        labelBg->setZValue(-1);  // 确保背景在文字下方

        scene->addItem(labelBg);
        scene->addItem(label);
        pathItems.append(labelBg);
        pathItems.append(label);

        // 3. 添加到路径
        if (i > 0) {
            painterPath.lineTo(point);
        }
    }
    QGraphicsDropShadowEffect* glowEffect = new QGraphicsDropShadowEffect;
    glowEffect->setColor(QColor(30, 144, 255, 150)); // 设置发光颜色
    glowEffect->setBlurRadius(10);                  // 设置模糊半径
    glowEffect->setOffset(0);                       // 设置偏移量


    // 4. 绘制路径线（更密集的虚线）
    QGraphicsPathItem* pathLine = new QGraphicsPathItem(painterPath);
    QPen pen(QBrush(gradient), 2);
    pen.setStyle(Qt::DashLine);
    pen.setDashPattern({3, 2});  // 修改为 3px实线 + 2px空白（更密集）
    pathLine->setPen(pen);
    pathLine->setGraphicsEffect(glowEffect);
    pathLine->setOpacity(0.7);
    scene->addItem(pathLine);
    pathItems.append(pathLine);

    scene->update();
    qDebug() << "=== Path Drawing Complete ===";

    // 自动聚焦到路径
    focusOnPath(pathPoints);
}

void MapView::clearPath() {
    // 移除所有路径项
    foreach (QGraphicsItem* item, pathItems) {
        scene->removeItem(item);
        delete item;
    }
    pathItems.clear();
}

void MapView::focusOnPath(const QList<QPointF>& pathPoints) {
    if (pathPoints.isEmpty()) return;

    // 计算路径边界
    QRectF pathRect;
    for (const QPointF& point : pathPoints) {
        pathRect |= QRectF(point, QSizeF(1, 1));
    }

    // 添加一些边距
    pathRect.adjust(-50, -50, 50, 50);

    // 缩放视图以适应路径
    fitInView(pathRect, Qt::KeepAspectRatio);
}

void MapView::setBookmarkManager(BookmarkManager *manager)
{
    m_bookmarkManager = manager;
}

void MapView::handleMomentCreation(const QPointF &scenePos)
{
    MomentEdit *editor = new MomentEdit(scenePos, this);
    connect(editor, &MomentEdit::momentSaved, this, &MapView::momentCreated);
    connect(editor, &MomentEdit::momentSaved, this, [this](const QString &path, const QPointF &loc) {
        // 添加奖励功能
        QMessageBox::information(this, tr("奖励"), tr("发布动态成功，获得10金币！"));
        SlotMachineDialog::addCoins(10);

        // 添加到MomentWidget
        if (momentWidget) {
            momentWidget->addMoment(path, loc);
        }
    });
    editor->exec();
    delete editor;
}

void MapView::loadHighlightBuildings()
{
    // 从文件加载需要高亮的建筑ID
    QFile file(":/info/building_names.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开建筑ID文件: building_names.txt";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            highlightBuildingIds.insert(line);
        }
    }
    file.close();

    qDebug() << "已加载高亮建筑ID数量:" << highlightBuildingIds.size();
}

void MapView::processBuildings()
{
    // 使用主地图的渲染器，确保坐标系统一致
    QSvgRenderer *renderer = mainSvgItem->renderer();

    QFile file(":/assets/ground_new.svg");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开SVG文件";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        qWarning() << "无法解析SVG文件";
        return;
    }
    file.close();

    // 查找所有<path>元素（建筑）
    QDomNodeList paths = doc.elementsByTagName("path");
    for (int i = 0; i < paths.size(); ++i) {
        QDomElement pathElem = paths.at(i).toElement();
        QString buildingId = pathElem.attribute("id");

        // 只处理在highlightBuildingIds集合中的建筑ID
        if (!buildingId.isEmpty() && highlightBuildingIds.contains(buildingId)) {
            // 创建建筑项 - 使用主渲染器
            QGraphicsSvgItem* buildingItem = new QGraphicsSvgItem();
            buildingItem->setSharedRenderer(renderer);
            buildingItem->setElementId(buildingId);
            buildingItem->setFlags(QGraphicsItem::ItemIsSelectable);

            // 获取元素在SVG中的边界框
            QRectF bounds = renderer->boundsOnElement(buildingId);
            if (bounds.isValid()) {
                // 设置位置为元素在原始SVG中的位置
                buildingItem->setPos(bounds.topLeft());
                qDebug() << "创建建筑项:" << buildingId << "位置:" << bounds.topLeft();
            } else {
                qWarning() << "无法获取建筑" << buildingId << "的位置信息";
                // 如果没有位置信息，默认放在(0,0)
                buildingItem->setPos(0, 0);
            }

            // 添加到场景并存储
            scene->addItem(buildingItem);
            m_buildings.insert(buildingId, buildingItem);
        }
    }
}
