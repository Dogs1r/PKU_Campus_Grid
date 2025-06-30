#ifndef DRAGPANBUTTON_H
#define DRAGPANBUTTON_H

#include "mapview.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QCursor>
#include <QPoint>
#include <QPainter>
#include <QPropertyAnimation>

namespace Ui {
class DragPanButton;
}

class DragPanButton : public QPushButton
{
    Q_OBJECT

public:
    explicit DragPanButton(MapView *view, QWidget *parent = nullptr);
    ~DragPanButton();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void updateOriginalPos(const QPoint& newPos);

private:
    Ui::DragPanButton *ui;
    MapView *mapView;
    bool dragging = false;
    QPoint dragStartGlobalPos;  // 全局鼠标起始位置
    QPoint originalPos;        // 相对于父组件的原始位置
    QPoint circleCenter;       // 相对于父组件的圆心位置
    int circleRadius = 20;
    QPointF lastVector;        // 上一次的相对向量
};

#endif // DRAGPANBUTTON_H
