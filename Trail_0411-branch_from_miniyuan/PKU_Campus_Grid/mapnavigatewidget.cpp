#include "mapnavigatewidget.h"
#include "ui_mapnavigatewidget.h"
#include "routefinder.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QToolButton>
#include <QDebug>

// 校园导航功能

MapNavigateWidget::MapNavigateWidget(MapView *mapView, QWidget *parent)
    : FancyToolBar(parent)
    , ui(new Ui::MapNavigateWidget)
{
    ui->setupUi(this);

    RouteFinder *routeWidget = new RouteFinder(mapView, this);
    addTabAction(":/icon/info.png", "MapNavigateWidget", tr("规划路径"), routeWidget);
    connect(routeWidget, &RouteFinder::requestReturn, this, [this, routeWidget]() {
        routeWidget->hide();
        this->show();
    }); // 连接返回信号

    // 分隔符
    addSeparator();

    // 导航动作
    addNavigationAction(":/icon/goback.png", "MapNavigateWidget", tr("返回"));
    connect(action(tr("返回")), &QAction::triggered, this, &MapNavigateWidget::requestReturn);
}

MapNavigateWidget::~MapNavigateWidget()
{
    delete ui;
}

