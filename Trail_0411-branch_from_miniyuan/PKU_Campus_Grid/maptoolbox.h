#ifndef MAPTOOLBOX_H
#define MAPTOOLBOX_H

#include <QToolBox>

// 地图工具组

namespace Ui {
class MapToolBox;
}

class MapToolBox : public QToolBox
{
    Q_OBJECT

public:
    explicit MapToolBox(QWidget *parent = nullptr);
    ~MapToolBox();

private:
    Ui::MapToolBox *ui;
};

#endif // MAPTOOLBOX_H
