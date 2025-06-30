#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapview.h"
#include "mapmenubar.h"
#include "maintoolbar.h"
#include "floattingtoolbar.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QPointF>
#include <QFile>
#include <QToolButton>
#include <QGraphicsView>

// 主界面

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置样式
    QFile qssFile(":/style/light_style.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QTextStream in(&qssFile);
        QString qssContent = in.readAll();
        this->setStyleSheet(qssContent);
        qssFile.close();
    }

    // 主窗口设置
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    this->resize(1200, 800);
    this->setWindowTitle("PKU Mapper");

    // 主垂直布局（菜单栏+内容区）
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    centralWidget->setLayout(mainLayout);

    // 1. 添加菜单栏
    menubar = new MapMenubar(centralWidget);
    connect(menubar, &MapMenubar::themeChanged, this, &MainWindow::onThemeChanged);
    mainLayout->addWidget(menubar, 0);

    // 2. 内容区域（工具栏+地图）
    QWidget *contentWidget = new QWidget(centralWidget);
    QHBoxLayout *contentLayout = new QHBoxLayout(contentWidget);
    contentLayout->setSpacing(0);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(contentWidget, 1);

    // 2.1 左侧工具栏区域
    toolbarContainer = new QWidget(contentWidget);
    toolbarContainer->setFixedWidth(200);  // 固定宽度
    QVBoxLayout *toolbarLayout = new QVBoxLayout(toolbarContainer);
    toolbarLayout->setContentsMargins(0, 0, 0, 0);

    // 2.2 右侧地图区域
    QWidget *mapContainer = new QWidget(contentWidget);
    mapContainer->setObjectName("mapContainer");

    QGridLayout *mapContainerLayout = new QGridLayout(mapContainer);
    mapContainerLayout->setSpacing(0);
    mapContainerLayout->setContentsMargins(0, 0, 0, 0);

    // 地图视图
    view = new MapView(mapContainer);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mapContainerLayout->addWidget(view, 0, 0);

    // 左侧工具栏补充（为了传入地图视图）
    MainToolBar *mainTool = new MainToolBar(view, toolbarContainer);
    toolbarLayout->addWidget(mainTool);
    contentLayout->addWidget(toolbarContainer, 0);  // 不拉伸

    connect(mainTool, &FancyToolBar::widgetShown, this, [this](QWidget* w){
        w->setParent(toolbarContainer);
        w->setGeometry(0, 0, toolbarContainer->width(), toolbarContainer->height());
    }); // 连接工具栏

    // 建筑交互系统（为了传入地图视图）
    m_buildingInteractor = new BuildingInteractionSystem(view, &m_buildingManager);
    m_buildingManager.loadFromFile(":/info/building_details.txt"); // 加载建筑信息

    connect(m_buildingInteractor, &BuildingInteractionSystem::showDetailsRequested,
            this, &MainWindow::showBuildingDetails); // 连接交互系统

    // 悬浮工具栏
    floatTool = new FloattingToolBar(view, mapContainer);
    floatTool->setObjectName("floatToolBar");
    floatTool->setFixedWidth(75);
    mapContainerLayout->addWidget(floatTool, 0, 1); // 覆盖整个网格

    contentLayout->addWidget(mapContainer, 1);

    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    qApp->removeTranslator(m_translator);
    delete m_translator;
    delete m_buildingInteractor;
}

void MainWindow::onThemeChanged(const QString &themeName) {
    QString qssFilePath;
    if (themeName == "system") {
        qssFilePath = QString(":/style/PKU_style.qss");
    } else {
        qssFilePath = QString(":/style/%1_style.qss").arg(themeName);
    }
    QFile qssFile(qssFilePath);
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QTextStream(&qssFile).readAll();
        this->setStyleSheet(styleSheet);
        floatTool->updateButtonPositions();
        qssFile.close();
    } else {
        qDebug() << "Failed to load theme:" << themeName;
    }
}

void MainWindow::onLanguageChanged(const QString &languageCode) {
    // 移除旧翻译
    qApp->removeTranslator(m_translator);

    // 加载新翻译
    QString path = ":/translations/lang_" + languageCode + ".qm";
    if (m_translator->load(path)) {
        qApp->installTranslator(m_translator);
    } else {
        qDebug() << "Failed to load:" << path;
    }

    // 刷新所有界面
    ui->retranslateUi(this);
}

void MainWindow::showBuildingDetails(const QString& title, const QString& details)
{
    if (!m_buildingDetailWidget) {
        m_buildingDetailWidget = new BuildingDetailWidget(toolbarContainer);

        // 连接信号
        connect(m_buildingDetailWidget, &BuildingDetailWidget::widgetShown, this, [this](QWidget* w) {
            w->setParent(toolbarContainer);
            w->setGeometry(0, 0, toolbarContainer->width(), toolbarContainer->height());
        });

        connect(m_buildingDetailWidget, &BuildingDetailWidget::requestReturn, this, [this]() {
            m_buildingDetailWidget->hide();
            // 如果需要显示父工具栏，可以在这里添加
        });
    }

    m_buildingDetailWidget->setBuildingInfo(title, details);
    emit m_buildingDetailWidget->widgetShown(m_buildingDetailWidget);
    m_buildingDetailWidget->show();
    m_buildingDetailWidget->raise();
}
