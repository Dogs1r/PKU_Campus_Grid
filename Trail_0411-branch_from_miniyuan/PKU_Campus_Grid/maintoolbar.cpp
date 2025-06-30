#include "maintoolbar.h"
#include "ui_maintoolbar.h"
#include "mapnavigatewidget.h"
#include "mapinfowidget.h"
#include "themesettingwidget.h"
#include "mapview.h"
#include "bookmarkwidget.h"
#include "slotmachinedialog.h"

// 主工具栏

MainToolBar::MainToolBar(MapView *mapView, QWidget *parent)
    : FancyToolBar(parent)
    , ui(new Ui::MainToolBar)
    , mapView(mapView)
{
    ui->setupUi(this);

    // 第一个功能：信息查询
    MapInfoWidget *infoWidget = new MapInfoWidget(this);
    addTabAction(":/icon/info.png", "MainToolBar", tr("信息查询"), infoWidget);

    connect(infoWidget, &MapInfoWidget::requestReturn, this, [this, infoWidget]() {
        infoWidget->hide();
        this->show();
    }); // 连接返回信号

    connect(infoWidget, &FancyToolBar::widgetShown, [parent](QWidget* w){
        w->setParent(parent);
        w->setGeometry(0, 0, parent->width(), parent->height());
    }); // 连接信息查询

    // 第二个功能：校园导航
    MapNavigateWidget *navWidget = new MapNavigateWidget(mapView, this);
    addTabAction(":/icon/navigate.png", "MainToolBar", tr("校园导航"), navWidget);

    connect(navWidget, &MapNavigateWidget::requestReturn, this, [this, navWidget]() {
        navWidget->hide();
        this->show();
    }); // 连接返回信号

    connect(navWidget, &FancyToolBar::widgetShown, [parent](QWidget* w){
        w->setParent(parent);
        w->setGeometry(0, 0, parent->width(), parent->height());
    }); // 连接校园导航

    // 第四个功能：收藏地点
    mapView->setBookmarkManager(&m_bookmarkManager);
    m_bookmarkManager.updateBookmarkMarks(mapView->rtScene());
    connect(mapView, &MapView::buildingClicked, this, &MainToolBar::onBuildingClicked);

    connect(&m_bookmarkManager, &BookmarkManager::bookmarksChanged,
        this, [this, mapView]() {
            m_bookmarkManager.updateBookmarkMarks(mapView->rtScene());
        });

    // 创建收藏地点Widget
    BookmarkWidget *bookmarkWidget = new BookmarkWidget(&m_bookmarkManager, this);
    addTabAction(":/icon/star.png", "MainToolBar", tr("收藏地点"), bookmarkWidget);

    // 连接返回信号
    connect(bookmarkWidget, &BookmarkWidget::requestReturn, this, [this, bookmarkWidget]() {
        bookmarkWidget->hide();
        this->show();
    });

    // 第五个功能：校园动态
    MomentWidget *momentWidget = new MomentWidget(this);
    addTabAction(":/icon/share.png", "MainToolBar", tr("校园动态"), momentWidget);

    // 连接返回信号
    connect(momentWidget, &MomentWidget::requestReturn, this, [this, momentWidget]() {
        momentWidget->hide();
        this->show();
    });

    // 连接地图视图
    mapView->setMomentWidget(momentWidget);

    // 分隔符
    addSeparator();

    // 常规动作
    SlotMachineDialog *slotMachine = new SlotMachineDialog(this);
    addRegularAction(":/icon/slot_machine.png", "MainToolBar", tr("老虎机"), slotMachine);
}

MainToolBar::~MainToolBar()
{
    delete ui;
}

ThemeSettingWidget* MainToolBar::themeWidgt() const
{
    return qobject_cast<ThemeSettingWidget*>(m_widgets.value(tr("主题切换")));
}

void MainToolBar::onBuildingClicked(const QString &buildingName)
{
    m_bookmarkManager.toggleBookmark(buildingName);
}
