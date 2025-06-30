#ifndef TRANSLATABLESTRING_H
#define TRANSLATABLESTRING_H

#include <QObject>
#include <QString>
#include <QCoreApplication>

// 翻译文本

class TranslatableString : public QObject {
    Q_OBJECT
public:
    explicit TranslatableString(const QString &context, const QString &key, QObject *parent = nullptr);
    ~TranslatableString();

    QString context() const; // 获取当前上下文
    QString text() const; // 获取当前语言下的翻译文本
    QString key() const; // 获取原始键值
    void updateTranslation(); // 触发翻译更新

signals:
    void textChanged();

private:
    QString m_context; // 上下文
    QString m_key; // 原始文本键
};

#endif // TRANSLATABLESTRING_H
