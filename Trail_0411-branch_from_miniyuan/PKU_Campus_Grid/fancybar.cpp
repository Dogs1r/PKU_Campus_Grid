#include "fancybar.h"
#include "ui_fancybar.h"

FancyBar::FancyBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FancyBar)
{
    ui->setupUi(this);
}

FancyBar::~FancyBar()
{
    delete ui;
}
