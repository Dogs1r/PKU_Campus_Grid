#include "registerdialog.h"
#include "ui_registerdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>

// 注册界面

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    // 加载QSS文件
    QFile qssFile(":/style/login_style.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QTextStream in(&qssFile);
        QString qssContent = in.readAll();
        this->setStyleSheet(qssContent);
        qssFile.close();
    }

    setWindowTitle(tr("用户注册"));
    setFixedSize(400, 300);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 标题
    QLabel *titleLabel = new QLabel(tr("创建新账户"), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 20px;");
    mainLayout->addWidget(titleLabel);

    // 表单布局
    QFormLayout *formLayout = new QFormLayout();

    // 用户名输入框
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText(tr("请输入用户名"));
    formLayout->addRow(tr("用户名:"), usernameEdit);

    // 密码输入框
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText(tr("请输入密码"));
    passwordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addRow(tr("密码:"), passwordEdit);

    // 确认密码输入框
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText(tr("请再次输入密码"));
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addRow(tr("确认密码:"), confirmPasswordEdit);

    mainLayout->addLayout(formLayout);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // 注册按钮
    QPushButton *registerButton = new QPushButton(tr("注册"), this);
    connect(registerButton, &QPushButton::clicked, this, &RegisterDialog::onRegisterButtonClicked);

    // 取消按钮
    QPushButton *cancelButton = new QPushButton(tr("取消"), this);
    connect(cancelButton, &QPushButton::clicked, this, &RegisterDialog::onCancelButtonClicked);

    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onRegisterButtonClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();
    QString confirmPassword = confirmPasswordEdit->text();

    // 验证输入
    if (username.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("用户名不能为空"));
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("密码不能为空"));
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, tr("输入错误"), tr("两次输入的密码不一致"));
        return;
    }

    if (userExists(username)) {
        QMessageBox::warning(this, tr("注册失败"), tr("该用户名已被注册"));
        return;
    }

    // 保存用户信息
    if (saveUserInfo(username, password)) {
        QMessageBox::information(this, tr("注册成功"), tr("账户创建成功，请登录"));
        emit registrationSuccess(username, password);
        accept();
    } else {
        QMessageBox::critical(this, tr("注册失败"), tr("无法保存用户信息"));
    }
}

void RegisterDialog::onCancelButtonClicked()
{
    reject();
}

bool RegisterDialog::saveUserInfo(const QString &username, const QString &password)
{
    QFile file("user_info.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out << username << ":" << password << "\n";
    file.close();
    return true;
}

bool RegisterDialog::userExists(const QString &username)
{
    QFile file("user_info.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false; // 文件不存在，用户肯定不存在
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(':');
        if (parts.size() >= 1 && parts[0] == username) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
