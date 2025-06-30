#include "LanguageManager.h"

#include <QTranslator>
#include <QCoreApplication>
#include <QMenu>

// 管理翻译

LanguageManager* LanguageManager::instance() {
    static LanguageManager manager;
    return &manager;
}

LanguageManager::LanguageManager(QObject *parent) : QObject(parent) {}

LanguageManager::~LanguageManager() {
    m_widgetBindings.clear();
}

QPushButton* LanguageManager::createTranslatablePushButton(const QString context, const QString &textKey, QWidget *parent) {
    // 创建按钮和翻译对象
    auto *button = new QPushButton(parent);
    auto *translatable = new TranslatableString(context, textKey, button);

    // 绑定文本更新
    connect(translatable, &TranslatableString::textChanged,
            button, [button, translatable]() {
                button->setText(translatable->text());
            });
    translatable->updateTranslation();

    // 注册到管理器
    m_widgetBindings[button] = translatable;
    return button;
}

QLabel* LanguageManager::createTranslatableLabel(const QString context, const QString &textKey, QWidget *parent) {
    auto *label = new QLabel(parent);
    auto *translatable = new TranslatableString(context, textKey, label);

    connect(translatable, &TranslatableString::textChanged,
            label, [label, translatable]() {
                label->setText(translatable->text());
            });
    translatable->updateTranslation();

    m_widgetBindings[label] = translatable;
    return label;
}

QAction* LanguageManager::createTranslatableAction(const QString context, const QString &textKey, QObject *parent) {
    auto *action = new QAction(parent);
    auto *translatable = new TranslatableString(context, textKey, action);

    connect(translatable, &TranslatableString::textChanged,
            action, [action, translatable]() {
                action->setText(translatable->text());
            });
    translatable->updateTranslation();

    m_actionBindings[action] = translatable;
    return action;
}

QAction* LanguageManager::createTranslatableAction(const QIcon &icon, const QString context, const QString &textKey, QObject *parent) {
    auto *action = createTranslatableAction(context, textKey, parent);
    action->setIcon(icon);
    return action;
}

QToolButton* LanguageManager::createTranslatableToolButton(const QString context, const QString &textKey, QWidget *parent) {
    QToolButton *button = new QToolButton(parent);
    TranslatableString *translatable = new TranslatableString(context, textKey, button);

    connect(translatable, &TranslatableString::textChanged,
            button, [button, translatable]() {
                button->setText(translatable->text());
            });
    translatable->updateTranslation();

    m_widgetBindings[button] = translatable;
    return button;
}

QGroupBox* LanguageManager::createTranslatableGroupBox(const QString context, const QString &titleKey, QWidget *parent) {
    QGroupBox *groupBox = new QGroupBox(parent);
    TranslatableString *translatable = new TranslatableString(context, titleKey, groupBox);

    connect(translatable, &TranslatableString::textChanged,
            groupBox, [groupBox, translatable]() {
                groupBox->setTitle(translatable->text());
            });
    translatable->updateTranslation();

    m_widgetBindings[groupBox] = translatable;
    return groupBox;
}

QMenu* LanguageManager::createTranslatableMenu(const QString context, const QString &titleKey, QWidget *parent) {
    QMenu *menu = new QMenu(parent);
    TranslatableString *translatable = new TranslatableString(context, titleKey, menu);

    connect(translatable, &TranslatableString::textChanged, menu, [menu, translatable]() {
        menu->setTitle(translatable->text());
    });
    translatable->updateTranslation();

    m_widgetBindings[menu] = translatable;
    return menu;
}

QAction* LanguageManager::createTranslatableMenuAction(const QString context, const QString &textKey, QMenu *parentMenu, const QKeySequence &shortcut) {
    QAction *action = new QAction(parentMenu);
    TranslatableString *translatable = new TranslatableString(context, textKey, action);

    connect(translatable, &TranslatableString::textChanged, action, [action, translatable]() {
        // 处理带快捷键的文本（如 "Open (&O)" -> "打开(&O)"）
        QString translated = translatable->text();
        if (action->shortcut().isEmpty() == false) {
            translated += " (" + action->shortcut().toString() + ")";
        }
        action->setText(translated);
    });

    action->setShortcut(shortcut);
    translatable->updateTranslation();
    parentMenu->addAction(action);

    m_widgetBindings[action] = translatable;
    return action;
}

void LanguageManager::switchLanguage(const QString &lang) {
    // 加载翻译文件
    auto *translator = new QTranslator(this);
    if (translator->load(":/translations/lang_" + lang + ".qm")) {
        qApp->installTranslator(translator);
    }

    // 更新所有绑定的 QWidget
    const auto widgetEnd = m_widgetBindings.cend();
    for (auto it = m_widgetBindings.cbegin(); it != widgetEnd; ++it) {
        it.value()->updateTranslation();
    }

    // 更新所有绑定的 QAction
    const auto actionEnd = m_actionBindings.cend();
    for (auto it = m_actionBindings.cbegin(); it != actionEnd; ++it) {
        qDebug() << it.value()->text() << Qt::endl;
        it.value()->updateTranslation();
        qDebug() << it.value()->text() << Qt::endl;
    }
}
