#ifndef FANCYBAR_H
#define FANCYBAR_H

#include <QWidget>

namespace Ui {
class FancyBar;
}

class FancyBar : public QWidget
{
    Q_OBJECT

public:
    explicit FancyBar(QWidget *parent = nullptr);
    ~FancyBar();

private:
    Ui::FancyBar *ui;
};

#endif // FANCYBAR_H
