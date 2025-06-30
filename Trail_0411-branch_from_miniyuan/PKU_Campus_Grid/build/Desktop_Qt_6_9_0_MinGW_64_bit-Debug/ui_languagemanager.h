/********************************************************************************
** Form generated from reading UI file 'languagemanager.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGEMANAGER_H
#define UI_LANGUAGEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LanguageManager
{
public:

    void setupUi(QWidget *LanguageManager)
    {
        if (LanguageManager->objectName().isEmpty())
            LanguageManager->setObjectName("LanguageManager");
        LanguageManager->resize(400, 300);

        retranslateUi(LanguageManager);

        QMetaObject::connectSlotsByName(LanguageManager);
    } // setupUi

    void retranslateUi(QWidget *LanguageManager)
    {
        LanguageManager->setWindowTitle(QCoreApplication::translate("LanguageManager", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LanguageManager: public Ui_LanguageManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGEMANAGER_H
