#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mainwindow.h"
#include "registerdialog.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QPixmap>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

// 登录界面

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
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

    // 设置窗口初始大小
    this->resize(500, 300);
    // 设置窗口标题
    this->setWindowTitle("登录");

    // 设置整体垂直布局
    QVBoxLayout *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);

    // 创建背景板
    QWidget *bgWidget = new QWidget(this);
    bgWidget->setObjectName("bg_widget");
    rootLayout->addWidget(bgWidget);

    // 背景板的垂直布局
    QVBoxLayout *bgLayout = new QVBoxLayout(bgWidget);
    bgLayout->setAlignment(Qt::AlignCenter); // 居中对齐

    // 添加标题图片
    QLabel *titleLabel = new QLabel(bgWidget);
    titleLabel->setObjectName("titleLabel");
    QPixmap titlePixmap(":/assets/title.png");
    titleLabel->setPixmap(titlePixmap.scaled(300, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    titleLabel->setAlignment(Qt::AlignCenter);
    bgLayout->addWidget(titleLabel);
    bgLayout->addSpacing(30); // 添加间距

    // 内容表单布局
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setFormAlignment(Qt::AlignmentFlag::AlignCenter);
    bgLayout->addLayout(formLayout);

    // 底部按钮水平布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    bgLayout->addLayout(buttonLayout);

    // 用户名输入框
    linkUsername = new QLineEdit(bgWidget);
    linkUsername->setObjectName("linkUsername");
    linkUsername->setPlaceholderText(tr("账号"));
    linkUsername->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    linkUsername->setMaximumSize(200, 30);
    linkUsername->setMinimumSize(200, 30);
    formLayout->setWidget(0, QFormLayout::FieldRole, linkUsername);

    // 密码输入框
    linkPassword = new QLineEdit(bgWidget);
    linkPassword->setObjectName("linkPassword");
    linkPassword->setPlaceholderText(tr("密码"));
    linkPassword->setEchoMode(QLineEdit::Password);
    linkPassword->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    linkPassword->setMaximumSize(200, 30);
    linkPassword->setMinimumSize(200, 30);
    formLayout->setWidget(1, QFormLayout::FieldRole, linkPassword);

    // 注册按钮
    QPushButton *buttonRegister = new QPushButton(tr("注册"), bgWidget);
    buttonRegister->setObjectName("registerButton");
    buttonRegister->setIcon(QIcon(":/icon/register.png"));
    buttonRegister->setFlat(true);
    buttonRegister->setCursor(Qt::CursorShape::PointingHandCursor);

    // 登录按钮
    QPushButton *okButton = new QPushButton(tr("登录"), bgWidget);
    okButton->setObjectName("okButton");
    okButton->setIcon(QIcon(":/icon/login.png"));
    okButton->setFlat(true);

    // 取消按钮
    QPushButton *cancelButton = new QPushButton(tr("取消"), bgWidget);
    cancelButton->setObjectName("cancelButton");
    cancelButton->setIcon(QIcon(":/icon/cancel.png"));
    cancelButton->setFlat(true);

    buttonLayout->addWidget(buttonRegister);
    buttonLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    // 连接信号和槽
    connect(okButton, &QPushButton::clicked, this, &LoginWidget::on_okButton_clicked);
    connect(linkPassword, &QLineEdit::returnPressed, this, &LoginWidget::on_registerButton_clicked);
    connect(cancelButton, &QPushButton::clicked, this, &LoginWidget::on_cancelButton_clicked);
    connect(buttonRegister, &QPushButton::clicked, this, &LoginWidget::on_registerButton_clicked);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_okButton_clicked()
{
    QString username = linkUsername->text().trimmed();
    QString password = linkPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, tr("登录失败"), tr("用户名和密码不能为空"));
        return;
    }

    if (validateCredentials(username, password)) {
        this->close();
        MainWindow *window = new MainWindow;
        window->show();
    } else {
        QMessageBox::warning(this, tr("登录失败"), tr("用户名或密码不正确"));
    }
}


void LoginWidget::on_registerButton_clicked()
{
    RegisterDialog regDialog(this);
    connect(&regDialog, &RegisterDialog::registrationSuccess,
            this, &LoginWidget::handleRegistrationSuccess);

    if (regDialog.exec() == QDialog::Accepted) {
        // 注册成功，可以自动填充用户名等
    }
}

void LoginWidget::handleRegistrationSuccess(const QString &username, const QString &password)
{
    // 自动填充用户名和密码
    linkUsername->setText(username);
    linkPassword->setText(password);
}

void LoginWidget::on_cancelButton_clicked()
{
    // 创建一个确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("确认退出"), tr("你确定退出吗？"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close(); // 如果用户选择“是”，关闭窗口
    } else {
        // 如果用户选择“否”，不做任何操作
    }
}

bool LoginWidget::validateCredentials(const QString &username, const QString &password)
{
    QFile file("user_info.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false; // 文件不存在，没有注册用户
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(':');
        if (parts.size() == 2 && parts[0] == username && parts[1] == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
