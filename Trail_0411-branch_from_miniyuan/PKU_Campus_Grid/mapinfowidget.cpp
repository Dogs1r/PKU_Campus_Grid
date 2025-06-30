#include "mapinfowidget.h"
#include "ui_mapinfowidget.h"
#include "fancytoolbar.h"
#include "foodfinderwidget.h"
#include "studyfinderwidget.h"
#include "canteenmanager.h"
#include "aichatwidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>

// 校园信息查询

MapInfoWidget::MapInfoWidget(QWidget *parent)
    : FancyToolBar(parent)
    , ui(new Ui::MapInfoWidget)
    , m_canteenManager(new CanteenManager(this))
{
    ui->setupUi(this);

    // 加载餐厅数据
    m_canteenManager->loadCanteens(":/info/canteens.txt");

    // 我想吃功能
    FoodFinderWidget *foodWidget = new FoodFinderWidget(m_canteenManager, this);
    addTabAction(":/icon/food.png", "MapInfoWidget", tr("我想吃"), foodWidget);
    connect(foodWidget, &FoodFinderWidget::requestReturn, this, [this, foodWidget]() {
        foodWidget->hide();
        this->show();
    }); // 连接返回信号

    // 我想学功能
    StudyFinderWidget *studyWidget = new StudyFinderWidget(this);
    addTabAction(":/icon/study.png", "MapInfoWidget", tr("我想学"), studyWidget);
    connect(studyWidget, &StudyFinderWidget::requestReturn, this, [this, studyWidget]() {
        studyWidget->hide();
        this->show();
    }); // 连接返回信号

    // 问问AI功能
    AIChatWidget *aiWidget = new AIChatWidget(this);
    addTabAction(":/icon/AI.png", "MapInfoWidget", tr("问问AI"), aiWidget);
    connect(aiWidget, &AIChatWidget::requestReturn, this, [this, aiWidget]() {
        aiWidget->hide();
        this->show();
    }); // 连接返回信号

    // 分隔符
    addSeparator();

    // 导航动作
    addNavigationAction(":/icon/goback.png", "MapInfoWidget", tr("返回"));
    connect(action(tr("返回")), &QAction::triggered, this, &MapInfoWidget::requestReturn);
}

MapInfoWidget::~MapInfoWidget()
{
    delete ui;
}

