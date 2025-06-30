#include "themesettingwidget.h"
#include "ui_themesettingwidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QToolButton>
#include <QFile>
#include <QDebug>

// 主题设置

ThemeSettingWidget::ThemeSettingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThemeSettingWidget)
{
    ui->setupUi(this);
    QVBoxLayout *themeLayout = new QVBoxLayout(this);
    themeLayout->setContentsMargins(0, 0, 0, 0);

    // 返回按钮
    QToolButton *returnButton = new QToolButton(this);
    returnButton->setIcon(QIcon(":/icon/return.png"));
    returnButton->setText(tr("返回"));
    returnButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(returnButton, &QToolButton::clicked, this, &ThemeSettingWidget::requestReturn);

    QPushButton *themeButton = new QPushButton(tr("主题设置"));
    themeButton->setMenu(createThemeMenu());
    themeLayout->addWidget(themeButton);

    // 应用保存的主题
    applySavedTheme();
}

ThemeSettingWidget::~ThemeSettingWidget()
{
    delete ui;
}

void ThemeSettingWidget::applySavedTheme()
{
    QString savedTheme = m_settings.value("Theme", "system").toString();
    applyTheme(savedTheme);
}

QMenu *ThemeSettingWidget::createThemeMenu()
{
    QMenu *themeMenu = new QMenu(tr("选择主题"));

    QAction *lightAction = themeMenu->addAction(tr("浅色主题"));
    connect(lightAction, &QAction::triggered, this, &ThemeSettingWidget::onLightTheme);

    QAction *darkAction = themeMenu->addAction(tr("深色主题"));
    connect(darkAction, &QAction::triggered, this, &ThemeSettingWidget::onDarkTheme);

    QAction *blueAction = themeMenu->addAction(tr("蓝色主题"));
    connect(blueAction, &QAction::triggered, this, &ThemeSettingWidget::onBlueTheme);

    QAction *pkuAction = themeMenu->addAction(tr("北大主题"));
    connect(pkuAction, &QAction::triggered, this, &ThemeSettingWidget::onPKUTheme);

    QAction *thuAction = themeMenu->addAction(tr("清华主题"));
    connect(thuAction, &QAction::triggered, this, &ThemeSettingWidget::onTHUTheme);

    QAction *systemAction = themeMenu->addAction(tr("系统默认"));
    connect(systemAction, &QAction::triggered, this, &ThemeSettingWidget::onSystemTheme);

    return themeMenu;
}

void ThemeSettingWidget::applyTheme(const QString &themeName) {
    saveCurrentTheme(themeName);
    emit themeChanged(themeName);
}

void ThemeSettingWidget::saveCurrentTheme(const QString &themeName)
{
    m_settings.setValue("Theme", themeName);
}

void ThemeSettingWidget::onLightTheme() { applyTheme("light"); }
void ThemeSettingWidget::onDarkTheme() { applyTheme("dark"); }
void ThemeSettingWidget::onBlueTheme() { applyTheme("blue"); }
void ThemeSettingWidget::onPKUTheme() { applyTheme("PKU"); }
void ThemeSettingWidget::onTHUTheme() { applyTheme("THU"); }
void ThemeSettingWidget::onSystemTheme() { applyTheme("system"); }
