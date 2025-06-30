#ifndef THEMESETTINGWIDGET_H
#define THEMESETTINGWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QSettings>

// 主题设置

namespace Ui {
class ThemeSettingWidget;
}

class ThemeSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeSettingWidget(QWidget *parent = nullptr);
    ~ThemeSettingWidget();
    void applySavedTheme();  // 应用保存的主题

signals:
    void requestReturn();
    void themeChanged(const QString& themeName);

private slots:
    void onLightTheme();
    void onDarkTheme();
    void onBlueTheme();
    void onPKUTheme();
    void onTHUTheme();
    void onSystemTheme();

private:
    Ui::ThemeSettingWidget *ui;
    QMenu *createThemeMenu();
    void applyTheme(const QString &themeName);
    void saveCurrentTheme(const QString &themeName);

    QSettings m_settings;
};

#endif // THEMESETTINGWIDGET_H
