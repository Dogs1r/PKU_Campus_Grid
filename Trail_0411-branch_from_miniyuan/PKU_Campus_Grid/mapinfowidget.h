#ifndef MAPINFOWIDGET_H
#define MAPINFOWIDGET_H

#include "fancytoolbar.h"
#include "canteenmanager.h"

#include <QWidget>

// 校园信息查询

namespace Ui {
class MapInfoWidget;
}

class MapInfoWidget : public FancyToolBar
{
    Q_OBJECT

public:
    explicit MapInfoWidget(QWidget *parent = nullptr);
    ~MapInfoWidget();

signals:
    void requestReturn();

private:
    Ui::MapInfoWidget *ui;

    CanteenManager *m_canteenManager;  // 餐厅管理器
};

#endif // MAPINFOWIDGET_H
