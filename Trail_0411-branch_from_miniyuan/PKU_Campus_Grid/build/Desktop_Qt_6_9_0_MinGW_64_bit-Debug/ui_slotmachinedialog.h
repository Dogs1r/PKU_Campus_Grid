/********************************************************************************
** Form generated from reading UI file 'slotmachinedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLOTMACHINEDIALOG_H
#define UI_SLOTMACHINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SlotMachineDialog
{
public:

    void setupUi(QWidget *SlotMachineDialog)
    {
        if (SlotMachineDialog->objectName().isEmpty())
            SlotMachineDialog->setObjectName("SlotMachineDialog");
        SlotMachineDialog->resize(400, 300);

        retranslateUi(SlotMachineDialog);

        QMetaObject::connectSlotsByName(SlotMachineDialog);
    } // setupUi

    void retranslateUi(QWidget *SlotMachineDialog)
    {
        SlotMachineDialog->setWindowTitle(QCoreApplication::translate("SlotMachineDialog", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlotMachineDialog: public Ui_SlotMachineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLOTMACHINEDIALOG_H
