#include "dragpanbutton.h"
#include "ui_dragpanbutton.h"

#include <QPropertyAnimation>
#include <QTimer>
#include <QPainter>
#include <cmath>
#include <QDebug>

DragPanButton::DragPanButton(MapView *view, QWidget *parent)
    : QPushButton(parent)
    , ui(new Ui::DragPanButton)
    , mapView(view)
    , dragging(false)
{
    ui->setupUi(this);

    const int btnSize = 40;
    setFixedSize(btnSize, btnSize);
    circleRadius = btnSize / 2;

    setText("");
    setIcon(QIcon(":/icon/drag-icon.png"));
    setIconSize(QSize(btnSize * 0.75, btnSize * 0.75));

    setStyleSheet(
        "QPushButton {"
        "   border-radius: 20px;"
        "   background-color: rgba(255,255,255,0.9);"
        "   border: 1px solid #3498db;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(220,240,255,0.95);"
        "}"
        );

    // 延迟初始化，确保父组件已定位
    QTimer::singleShot(0, this, [this](){
        originalPos = this->pos();
        circleCenter = originalPos + QPoint(width()/2, height()/2);
    });
}

DragPanButton::~DragPanButton()
{
    delete ui;
}

void DragPanButton::updateOriginalPos(const QPoint& newPos)
{
    originalPos = newPos;
    circleCenter = newPos + QPoint(width()/2, height()/2);
}

void DragPanButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && rect().contains(event->pos())) {
        // 停止任何正在进行的动画
        QPropertyAnimation *anim = findChild<QPropertyAnimation*>();
        if (anim) anim->stop();

        dragging = true;
        dragStartGlobalPos = event->globalPos();  // 记录全局起始位置
        lastVector = QPointF(0, 0);   // 重置上一次向量
        setCursor(Qt::ClosedHandCursor);
    }
    QPushButton::mousePressEvent(event);
}

void DragPanButton::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && mapView) {
        // 1. 计算鼠标全局偏移量
        QPoint currentGlobalPos = event->globalPos();
        QPoint globalDelta = currentGlobalPos - dragStartGlobalPos;

        // 2. 计算按钮新位置（基于原始位置+偏移量）
        QPoint newPos = originalPos + globalDelta;

        // 3. 计算相对于圆心的向量
        QPointF vector = newPos + QPointF(width()/2, height()/2) - QPointF(circleCenter);
        double length = std::sqrt(vector.x()*vector.x() + vector.y()*vector.y());

        // 4. 计算地图移动增量（基于向量变化）
        QPointF deltaVector = vector - lastVector;
        lastVector = vector;

        // 5. 根据距离圆心位置调整移动速度
        double speedFactor = 0.5 + (length / circleRadius) * 1.5;

        // 6. 平滑移动地图
        mapView->moveBy(deltaVector.x() * speedFactor, deltaVector.y() * speedFactor);

        // 7. 限制按钮在圆形区域内（但允许地图继续移动）
        if (length > circleRadius) {
            // 计算限制后的向量
            vector = vector * (circleRadius / length);

            // 计算限制后的按钮位置
            newPos = circleCenter + vector.toPoint() - QPoint(width()/2, height()/2);
        }

        // 8. 移动按钮到新位置
        move(newPos);
    }
    QPushButton::mouseMoveEvent(event);
}

void DragPanButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (dragging) {
        dragging = false;
        setCursor(Qt::ArrowCursor);

        // 添加返回动画
        QPropertyAnimation *anim = new QPropertyAnimation(this, "pos");
        anim->setDuration(300);
        anim->setStartValue(pos());
        anim->setEndValue(originalPos);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
    QPushButton::mouseReleaseEvent(event);
}
