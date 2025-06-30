/********************************************************************************
** Form generated from reading UI file 'momentedit.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOMENTEDIT_H
#define UI_MOMENTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MomentEdit
{
public:

    void setupUi(QWidget *MomentEdit)
    {
        if (MomentEdit->objectName().isEmpty())
            MomentEdit->setObjectName("MomentEdit");
        MomentEdit->resize(400, 300);

        retranslateUi(MomentEdit);

        QMetaObject::connectSlotsByName(MomentEdit);
    } // setupUi

    void retranslateUi(QWidget *MomentEdit)
    {
        MomentEdit->setWindowTitle(QCoreApplication::translate("MomentEdit", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MomentEdit: public Ui_MomentEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOMENTEDIT_H
