#ifndef MAPMENUBAR_H
#define MAPMENUBAR_H

#include <QMenuBar>
#include <QMap>
#include <functional>
#include <QSettings>

class QMenu;
class QAction;

class MapMenubar : public QMenuBar
{
    Q_OBJECT

public:
    explicit MapMenubar(QWidget *parent = nullptr);
    ~MapMenubar();

    // 添加菜单
    void addMenu(const QString &menuName);
    // 添加菜单项
    void addMenuItem(const QString &menuName, const QString &itemName, std::function<void()> slot, const QString &shortcut = QString());
    // 添加子菜单
    void addSubMenu(const QString &menuName, const QString &subMenuName);

    // 应用主题
    void applyTheme(const QString &themeName);

signals:
    void settingsRequested();
    void themeChanged(const QString &theme);

private slots:
    void onFileOpen();
    void onFileSave();
    void onEditCopy();
    void onEditPaste();
    void onHelpAbout();
    void onThemeActionTriggered();

private:
    void createSettingsMenu();
    void applySavedTheme();
    void saveTheme(const QString &themeName);
    QMenu* createThemeMenu();

    QMap<QString, QMenu*> menus;
    QSettings m_settings;
};

#endif // MAPMENUBAR_H
