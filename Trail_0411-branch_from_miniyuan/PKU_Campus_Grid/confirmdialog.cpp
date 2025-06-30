#include "confirmdialog.h"
#include "ui_confirmdialog.h"

#include <QString>

// 确认对话

// input: parent, dialog title(默认为“警告”)
ConfirmDialog::ConfirmDialog(QWidget *parent, const QString & dialogTitle)
    : QDialog(parent)
    , ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(dialogTitle);
    this->show();
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}
