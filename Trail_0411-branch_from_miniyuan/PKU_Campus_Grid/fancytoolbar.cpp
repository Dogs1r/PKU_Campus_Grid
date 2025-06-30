#include "fancytoolbar.h"
#include "ui_fancytoolbar.h"
#include "LanguageManager.h"

#include <QAction>
#include <QIcon>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>

// 工具栏的基类

FancyToolBar::FancyToolBar(QWidget *parent)
    : QToolBar(parent)
    , ui(new Ui::FancyToolBar)
{
    ui->setupUi(this);

    setupStyle();
}

FancyToolBar::~FancyToolBar()
{
    delete ui;
}

void FancyToolBar::addTabAction(const QString &iconPath, const QString context, const QString &text, QWidget *associatedWidget)
{
    auto *langManager = LanguageManager::instance();

    QAction *action = langManager->createTranslatableAction(QIcon(iconPath), context, text, this);
    addAction(action);
    m_actions.insert(text, action);

    if (associatedWidget) {
        m_widgets.insert(text, associatedWidget);
        associatedWidget->hide();

        connect(action, &QAction::triggered, this, [this, associatedWidget]() {
            this->hide();
            emit widgetShown(associatedWidget); // 发出信号
            associatedWidget->show();
        });
    }
}

void FancyToolBar::addRegularAction(const QString &iconPath, const QString context, const QString &text, QWidget *associatedWidget)
{
    auto *langManager = LanguageManager::instance();

    QAction *action = langManager->createTranslatableAction(QIcon(iconPath), context, text, this);
    addAction(action);
    m_actions.insert(text, action);

    if (associatedWidget) {
        m_widgets.insert(text, associatedWidget);
        associatedWidget->hide();

        connect(action, &QAction::triggered, this, [associatedWidget]() {
            associatedWidget->show();
            associatedWidget->raise();
        });
    }
}

void FancyToolBar::addNavigationAction(const QString &iconPath, const QString context, const QString &text)
{
    auto *langManager = LanguageManager::instance();

    QAction *action = langManager->createTranslatableAction(QIcon(iconPath), context, text, this);
    addAction(action);
    m_actions.insert(text, action);
}

void FancyToolBar::addSeparator()
{
    QToolBar::addSeparator();
}

QAction* FancyToolBar::action(const QString &text) const
{
    return m_actions.value(text, nullptr);
}

void FancyToolBar::showToolBar()
{
    this->show();
}

void FancyToolBar::hideToolBar()
{
    this->hide();
}

void FancyToolBar::setupStyle()
{
    // 设置工具栏方向为垂直
    setOrientation(Qt::Vertical);

    // 设置按钮大小策略
    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    policy.setHorizontalStretch(0);
    policy.setVerticalStretch(0);
    setSizePolicy(policy);

    // 设置工具栏宽度
    setFixedWidth(200);

    // 设置工具栏属性
    setMovable(false); // 禁止拖动
    setIconSize(QSize(30, 30));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // 文字在图片下方
}
