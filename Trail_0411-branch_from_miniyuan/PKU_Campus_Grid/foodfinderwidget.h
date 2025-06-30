#ifndef FOODFINDERWIDGET_H
#define FOODFINDERWIDGET_H

#include <QWidget>
#include <QTimeEdit>
#include <QComboBox>
#include <QStringList>

class CanteenManager;

namespace Ui {
class FoodFinderWidget;
}

class FoodFinderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FoodFinderWidget(CanteenManager *canteenManager, QWidget *parent = nullptr);
    ~FoodFinderWidget();

signals:
    void requestReturn();  // 返回导航信号

private slots:
    void onCheckOpeningClicked();  // 查询开放餐厅
    void onCheckHoursClicked();    // 查询营业时间

private:
    Ui::FoodFinderWidget *ui;
    CanteenManager *m_canteenManager;
    QTimeEdit *m_timeEdit;         // 时间输入控件
    QComboBox *m_canteenComboBox;  // 餐厅选择框
};

#endif // FOODFINDERWIDGET_H
