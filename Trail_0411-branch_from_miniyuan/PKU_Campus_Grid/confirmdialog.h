#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include <QString>

// 确认对话

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent = nullptr, const QString & dialogTitle = "警告");
    ~ConfirmDialog();

private:
    Ui::ConfirmDialog *ui;
};

#endif // CONFIRMDIALOG_H
