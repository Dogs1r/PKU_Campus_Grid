/********************************************************************************
** Form generated from reading UI file 'canteenmanager.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANTEENMANAGER_H
#define UI_CANTEENMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CanteenManager
{
public:

    void setupUi(QWidget *CanteenManager)
    {
        if (CanteenManager->objectName().isEmpty())
            CanteenManager->setObjectName("CanteenManager");
        CanteenManager->resize(400, 300);

        retranslateUi(CanteenManager);

        QMetaObject::connectSlotsByName(CanteenManager);
    } // setupUi

    void retranslateUi(QWidget *CanteenManager)
    {
        CanteenManager->setWindowTitle(QCoreApplication::translate("CanteenManager", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CanteenManager: public Ui_CanteenManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANTEENMANAGER_H
