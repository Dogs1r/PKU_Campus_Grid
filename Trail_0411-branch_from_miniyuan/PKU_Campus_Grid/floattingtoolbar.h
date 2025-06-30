#ifndef FLOATTINGTOOLBAR_H
#define FLOATTINGTOOLBAR_H

#include "mapview.h"

#include <QWidget>

// 悬浮工具栏（地图右上角）

namespace Ui {
class FloattingToolBar;
}

class FloattingToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit FloattingToolBar(MapView *mapView, QWidget *parent = nullptr);
    ~FloattingToolBar();

    void updateButtonPositions();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::FloattingToolBar *ui;
};

#endif // FLOATTINGTOOLBAR_H
