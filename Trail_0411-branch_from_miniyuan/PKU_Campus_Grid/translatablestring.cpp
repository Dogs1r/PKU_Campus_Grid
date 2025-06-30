#include "TranslatableString.h"
#include <QCoreApplication>

// 翻译文本

TranslatableString::TranslatableString(const QString &context, const QString &key, QObject *parent)
    : QObject(parent), m_context(context), m_key(key) {}

TranslatableString::~TranslatableString() {}

QString TranslatableString::text() const {
    return QCoreApplication::translate(m_context.toUtf8().constData(),
                                       m_key.toUtf8().constData());
}

QString TranslatableString::key() const {
    return m_key;
}

void TranslatableString::updateTranslation() {
    emit textChanged();  // 通知绑定控件更新文本
}
