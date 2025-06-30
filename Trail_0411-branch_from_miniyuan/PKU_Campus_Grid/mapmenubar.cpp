#include "mapmenubar.h"
#include "languagemanager.h"

#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QFile>
#include <QInputDialog>
#include <QSettings>

MapMenubar::MapMenubar(QWidget *parent)
    : QMenuBar(parent)
    , m_settings("MyOrganization", "MyApplication")
{
    // 添加菜单
    addMenu(tr("&文件"));
    addMenu(tr("&编辑"));
    addMenu(tr("&视图"));
    addMenu(tr("&帮助"));

    // 添加菜单项
    addMenuItem(tr("&文件"), tr("&打开"), [this]() { onFileOpen(); }, tr("Ctrl+O"));
    addMenuItem(tr("&文件"), tr("&保存"), [this]() { onFileSave(); }, tr("Ctrl+S"));
    addMenuItem(tr("&编辑"), tr("&复制"), [this]() { onEditCopy(); }, tr("Ctrl+C"));
    addMenuItem(tr("&编辑"), tr("&粘贴"), [this]() { onEditPaste(); }, tr("Ctrl+V"));
    addMenuItem(tr("&帮助"), tr("&关于"), [this]() { onHelpAbout(); });

    // 添加子菜单
    addSubMenu(tr("&文件"), tr("&最近文件"));
    addMenuItem(tr("&最近文件"), tr("文件1"), [this]() { onFileOpen(); });
    addMenuItem(tr("&最近文件"), tr("文件2"), [this]() { onFileOpen(); });

    // 创建设置相关菜单
    createSettingsMenu();
}

MapMenubar::~MapMenubar()
{
}

void MapMenubar::createSettingsMenu()
{
    // 添加主题设置
    QMenu* themeMenu = createThemeMenu();
    menus[tr("&视图")]->addMenu(themeMenu);

    // 添加语言设置
    addSubMenu(tr("&视图"), tr("&语言"));
    addMenuItem(tr("&语言"), tr("&中文"), []() { LanguageManager::instance()->switchLanguage("zh_CN");  });
    addMenuItem(tr("&语言"), tr("&English"), []() { LanguageManager::instance()->switchLanguage("en_US"); });
}

QMenu* MapMenubar::createThemeMenu()
{
    auto *langManager = LanguageManager::instance();

    QMenu* themeMenu = langManager->createTranslatableMenu("MapMenubar", tr("主题"), this);

    // 添加主题选项
    QAction* lightAction = langManager->createTranslatableMenuAction("MapMenubar", tr("浅色主题"), themeMenu);
    themeMenu->addAction(lightAction);
    lightAction->setData("light");
    connect(lightAction, &QAction::triggered, this, &MapMenubar::onThemeActionTriggered);

    QAction* darkAction = langManager->createTranslatableMenuAction("MapMenubar", tr("深色主题"), themeMenu);
    themeMenu->addAction(darkAction);
    darkAction->setData("dark");
    connect(darkAction, &QAction::triggered, this, &MapMenubar::onThemeActionTriggered);

    QAction* blueAction = langManager->createTranslatableMenuAction("MapMenubar", tr("蓝色主题"), themeMenu);
    themeMenu->addAction(blueAction);
    blueAction->setData("blue");
    connect(blueAction, &QAction::triggered, this, &MapMenubar::onThemeActionTriggered);

    QAction* pkuAction = langManager->createTranslatableMenuAction("MapMenubar", tr("北大主题"), themeMenu);
    themeMenu->addAction(pkuAction);
    pkuAction->setData("PKU");
    connect(pkuAction, &QAction::triggered, this, &MapMenubar::onThemeActionTriggered);

    QAction* thuAction = langManager->createTranslatableMenuAction("MapMenubar", tr("清华主题"), themeMenu);
    themeMenu->addAction(thuAction);
    thuAction->setData("THU");
    connect(thuAction, &QAction::triggered, this, &MapMenubar::onThemeActionTriggered);

    QAction* systemAction = langManager->createTranslatableMenuAction("MapMenubar", tr("系统默认"), themeMenu);
    themeMenu->addAction(systemAction);
    systemAction->setData("system");
    connect(systemAction, &QAction::triggered, this, &MapMenubar::onThemeActionTriggered);

    return themeMenu;
}

void MapMenubar::onThemeActionTriggered()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        QString themeName = action->data().toString();
        emit themeChanged(themeName);
    }
}

void MapMenubar::applyTheme(const QString &themeName)
{
    QString qssFile;
    if (themeName == "light") {
        qssFile = ":/style/light.qss";
    } else if (themeName == "dark") {
        qssFile = ":/style/dark.qss";
    } else if (themeName == "blue") {
        qssFile = ":/style/blue.qss";
    } else if (themeName == "PKU") {
        qssFile = ":/style/pku.qss";
    } else if (themeName == "THU") {
        qssFile = ":/style/thu.qss";
    } else {
        qssFile = ":/style/style.qss"; // 系统默认
    }

    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();

        // 保存主题设置
        saveTheme(themeName);

        // 发射信号通知主题变化
        emit themeChanged(themeName);
    } else {
        QMessageBox::warning(nullptr, tr("Theme Error"), tr("Failed to load theme file: %1").arg(qssFile));
    }
}

void MapMenubar::applySavedTheme()
{
    QString savedTheme = m_settings.value("Theme", "system").toString();
    applyTheme(savedTheme);
}

void MapMenubar::saveTheme(const QString &themeName)
{
    m_settings.setValue("Theme", themeName);
}

void MapMenubar::addMenu(const QString &menuName)
{
    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    QMenu *menu = langManager->createTranslatableMenu("MapMenubar", menuName, this);
    menus[menuName] = menu;
    QMenuBar::addMenu(menu);
}

void MapMenubar::addMenuItem(const QString &menuName, const QString &itemName, std::function<void()> slot, const QString &shortcut)
{
    auto *langManager = LanguageManager::instance();

    if (menus.contains(menuName)) {
        QMenu *menu = menus[menuName];
        QAction *action = langManager->createTranslatableMenuAction("MapMenubar", itemName, menu, shortcut);
        if (!shortcut.isEmpty()) {
            action->setShortcut(QKeySequence(shortcut));
        }
        menu->addAction(action);
        connect(action, &QAction::triggered, this, slot);
    }
}

void MapMenubar::addSubMenu(const QString &menuName, const QString &subMenuName)
{
    auto *langManager = LanguageManager::instance();

    if (menus.contains(menuName)) {
        QMenu *menu = menus[menuName];
        QMenu *subMenu = langManager->createTranslatableMenu("MapMenubar", subMenuName, menu);
        menu->addMenu(subMenu);
        menus[subMenuName] = subMenu;
    }
}

void MapMenubar::onFileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("打开文件"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QMessageBox::information(nullptr, tr("File Open"), tr("你选择的是: %1").arg(fileName));
    }
}

void MapMenubar::onFileSave()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("保存文件"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QMessageBox::information(nullptr, tr("保存文件"), tr("你选择的是: %1").arg(fileName));
    }
}

void MapMenubar::onEditCopy()
{
    QMessageBox::information(nullptr, tr("复制"), tr("休想"));
}

void MapMenubar::onEditPaste()
{
    QMessageBox::information(nullptr, tr("粘贴"), tr("想得美"));
}

void MapMenubar::onHelpAbout()
{
    QMessageBox::about(nullptr, tr("关于"), tr("一些简短的陈述"));
}
