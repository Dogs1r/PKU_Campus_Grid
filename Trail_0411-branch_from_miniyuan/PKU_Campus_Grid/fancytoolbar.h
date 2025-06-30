#ifndef FANCYTOOLBAR_H
#define FANCYTOOLBAR_H

#include <QToolBar>
#include <QMap>

// 工具栏的基类

namespace Ui {
class FancyToolBar;
}

class FancyToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit FancyToolBar(QWidget *parent = nullptr);
    ~FancyToolBar();

    void addTabAction(const QString &iconPath, const QString context, const QString &text, QWidget *associatedWidget = nullptr);
    void addRegularAction(const QString &iconPath, const QString context, const QString &text, QWidget *associatedWidget = nullptr);
    void addNavigationAction(const QString &iconPath, const QString context, const QString &text);
    void addSeparator();
    QAction* action(const QString &text) const;
    void showToolBar();
    void hideToolBar();

signals:
    void requestShowWidget(QWidget *widget);
    void requestShowToolBar();
    void widgetShown(QWidget *widget);

protected:
    Ui::FancyToolBar *ui;
    QMap<QString, QAction*> m_actions;
    QMap<QString, QWidget*> m_widgets;

    void setupStyle();
};

#endif // FANCYTOOLBAR_H
