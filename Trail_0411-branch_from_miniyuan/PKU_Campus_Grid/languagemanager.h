#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include "TranslatableString.h"

#include <QObject>
#include <QList>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>
#include <QGroupBox>

// 管理翻译

class LanguageManager : public QObject
{
    Q_OBJECT

public:
    static LanguageManager* instance();
    void switchLanguage(const QString &lang);

    QPushButton* createTranslatablePushButton(const QString context, const QString &textKey, QWidget *parent);
    QLabel* createTranslatableLabel(const QString context, const QString &textKey, QWidget *parent);
    QAction* createTranslatableAction(const QString context, const QString &textKey, QObject *parent);
    QAction* createTranslatableAction(const QIcon &icon, const QString context, const QString &textKey, QObject *parent);
    QToolButton* createTranslatableToolButton(const QString context, const QString &textKey, QWidget *parent);
    QGroupBox* createTranslatableGroupBox(const QString context, const QString &titleKey, QWidget *parent);
    QMenu* createTranslatableMenu(const QString context, const QString &titleKey, QWidget *parent = nullptr);
    QAction* createTranslatableMenuAction(const QString context, const QString &textKey, QMenu *parentMenu, const QKeySequence &shortcut = QKeySequence());

private:
    explicit LanguageManager(QObject *parent = nullptr);
    ~LanguageManager();
    QHash<QObject*, TranslatableString*> m_widgetBindings;  // QObject对象绑定
    QHash<QAction*, TranslatableString*> m_actionBindings; // QAction对象绑定
};

#endif // LANGUAGEMANAGER_H
