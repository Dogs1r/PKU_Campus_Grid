#ifndef MAPNAVIGATEWIDGET_H
#define MAPNAVIGATEWIDGET_H

#include "fancytoolbar.h"
#include "routefinder.h"

#include <QWidget>
#include <QStackedWidget>

// 校园导航功能

namespace Ui {
class MapNavigateWidget;
}

class MapNavigateWidget : public FancyToolBar
{
    Q_OBJECT

public:
    explicit MapNavigateWidget(MapView *mapView, QWidget *parent = nullptr);
    ~MapNavigateWidget();

signals:
    void requestReturn();

private:
    Ui::MapNavigateWidget *ui;

    QStackedWidget *stackedWidget;
    RouteFinder *routeFinder;

    void showRouteFinder();

friend class MapToolBox;
};

#endif // MAPNAVIGATEWIDGET_H
