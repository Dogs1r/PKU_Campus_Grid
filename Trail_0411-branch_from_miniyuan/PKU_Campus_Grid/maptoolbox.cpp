#include "maptoolbox.h"
#include "ui_maptoolbox.h"
#include "mapnavigatewidget.h"
#include "mapinfowidget.h"
#include "themesettingwidget.h"

#include <QToolBox>
#include <QPushButton>
#include <QMenu>
#include <QHBoxLayout>

// 地图工具组

MapToolBox::MapToolBox(QWidget *parent)
    : QToolBox(parent)
    , ui(new Ui::MapToolBox)
{
    ui->setupUi(this);

    QHBoxLayout *toolboxLayout = new QHBoxLayout(parent);
    this->setLayout(toolboxLayout);

    // 创建第一个工具组：校园导航
    MapNavigateWidget *navGroup = new MapNavigateWidget(this);
    this->addItem(navGroup, "校园导航");

    // 创建第二个工具组：校园信息查询
    MapInfoWidget *infoGroup = new MapInfoWidget(this);
    this->addItem(infoGroup, "信息查询");

    // 创建第三个工具栏：主题切换
    ThemeSettingWidget *themeSettings = new ThemeSettingWidget(this);
    this->addItem(themeSettings, "主题切换");  // 添加到你的布局中

}

MapToolBox::~MapToolBox()
{
    delete ui;
}
