#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>

// 登录界面

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_okButton_clicked();
    void on_registerButton_clicked();
    void on_cancelButton_clicked();
    void handleRegistrationSuccess(const QString &username, const QString &password);

private:
    Ui::LoginWidget *ui;
    QLineEdit *linkUsername;
    QLineEdit *linkPassword;

    bool validateCredentials(const QString& username, const QString& password);
};

#endif // LOGINWIDGET_H
