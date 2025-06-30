/********************************************************************************
** Form generated from reading UI file 'translatablestring.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSLATABLESTRING_H
#define UI_TRANSLATABLESTRING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TranslatableString
{
public:

    void setupUi(QWidget *TranslatableString)
    {
        if (TranslatableString->objectName().isEmpty())
            TranslatableString->setObjectName("TranslatableString");
        TranslatableString->resize(400, 300);

        retranslateUi(TranslatableString);

        QMetaObject::connectSlotsByName(TranslatableString);
    } // setupUi

    void retranslateUi(QWidget *TranslatableString)
    {
        TranslatableString->setWindowTitle(QCoreApplication::translate("TranslatableString", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TranslatableString: public Ui_TranslatableString {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSLATABLESTRING_H
