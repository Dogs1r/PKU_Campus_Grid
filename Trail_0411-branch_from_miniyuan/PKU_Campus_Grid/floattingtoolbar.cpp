#include "floattingtoolbar.h"
#include "ui_floattingtoolbar.h"
#include "mapview.h"
#include "dragpanbutton.h"

#include <QAction>
#include <QIcon>
#include <QVBoxLayout>
#include <QToolButton>
#include <QFile>

// 悬浮工具栏（地图右上角）

FloattingToolBar::FloattingToolBar(MapView *mapView, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FloattingToolBar)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground); // 设置为浮动且无窗口边框
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    const int btnSize = 40;
    const int iconSize = btnSize * 0.75;

    QFile qssfile(":/style/button_style.qss");
    if (qssfile.open(QFile::ReadOnly)) {
        QString unifiedButtonStyle = QTextStream(&qssfile).readAll();
        this->setStyleSheet(unifiedButtonStyle.arg(btnSize).arg(btnSize/2));
        qssfile.close();
    } else {
        qDebug() << "error!";
    }

    // 放大按钮
    QToolButton *zoomInButton = new QToolButton(this);
    zoomInButton->setIcon(QIcon(":/icon/zoom_in.png"));
    zoomInButton->setIconSize(QSize(iconSize, iconSize));
    zoomInButton->setToolTip(tr("放大"));
    zoomInButton->setStyleSheet("padding: 0; border: none;");

    // 缩小按钮
    QToolButton *zoomOutButton = new QToolButton(this);
    zoomOutButton->setIcon(QIcon(":/icon/zoom_out.png"));
    zoomOutButton->setIconSize(QSize(iconSize, iconSize));
    zoomOutButton->setToolTip(tr("缩小"));
    zoomOutButton->setStyleSheet("padding: 0; border: none;");

    // 拖拽按钮
    DragPanButton *dragButton = new DragPanButton(mapView, this);
    dragButton->setIcon(QIcon(":/icon/drag-icon.png"));
    dragButton->setIconSize(QSize(iconSize, iconSize));
    dragButton->setStyleSheet("padding: 0; border: none;");

    // 移到右上角
    updateButtonPositions();

    // 信号连接
    connect(zoomInButton, &QToolButton::clicked, mapView, &MapView::zoomIn);
    connect(zoomOutButton, &QToolButton::clicked, mapView, &MapView::zoomOut);
}

FloattingToolBar::~FloattingToolBar()
{
    delete ui;
}

void FloattingToolBar::updateButtonPositions()
{
    const int buttonMargin = 10; // 右边距
    const int spacing = 4;       // 按钮间距

    // 等待有效尺寸
    if (width() <= 0 || height() <= 0) return;

    // 统一处理所有按钮
    int yPos = buttonMargin;
    for (QAbstractButton* btn : findChildren<QAbstractButton*>()) {
        QPoint newPos(width() - btn->width() - buttonMargin, yPos);
        btn->move(newPos);

        // 如果是拖拽按钮，更新其原始位置
        if (DragPanButton *dragBtn = qobject_cast<DragPanButton*>(btn)) {
            dragBtn->updateOriginalPos(newPos);
        }
        yPos += btn->height() + spacing;
        btn->raise(); // 确保在最上层
    }
}

void FloattingToolBar::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    updateButtonPositions(); // 尺寸变化时重新定位
}
