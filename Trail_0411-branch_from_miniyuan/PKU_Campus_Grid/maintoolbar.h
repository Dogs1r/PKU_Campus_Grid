#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include "fancytoolbar.h"
#include "themesettingwidget.h"
#include "mapview.h"
#include "bookmarkmanager.h"

#include <QWidget>

// 主工具栏

namespace Ui {
class MainToolBar;
}

class MainToolBar : public FancyToolBar
{
    Q_OBJECT

public:
    explicit MainToolBar(MapView *mapView, QWidget *parent = nullptr);
    ~MainToolBar();

    ThemeSettingWidget *themeWidgt() const;
    void retranslateUi();

private slots:
    void onBuildingClicked(const QString &buildingName);

private:
    Ui::MainToolBar *ui;

    MapView *mapView;
    BookmarkManager m_bookmarkManager;
};

#endif // MAINTOOLBAR_H
