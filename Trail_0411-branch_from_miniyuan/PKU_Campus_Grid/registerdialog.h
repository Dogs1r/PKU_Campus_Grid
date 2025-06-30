#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QWidget>
#include <QLineEdit>
#include <QDialog>

// 注册界面

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

signals:
    void registrationSuccess(const QString &username, const QString &password);

private slots:
    void onRegisterButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::RegisterDialog *ui;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;

    bool saveUserInfo(const QString &username, const QString &password);
    bool userExists(const QString &username);
};

#endif // REGISTERDIALOG_H
