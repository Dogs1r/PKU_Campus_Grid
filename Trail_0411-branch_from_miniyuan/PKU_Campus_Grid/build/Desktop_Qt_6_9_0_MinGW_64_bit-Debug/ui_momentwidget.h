/********************************************************************************
** Form generated from reading UI file 'momentwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOMENTWIDGET_H
#define UI_MOMENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MomentWidget
{
public:

    void setupUi(QWidget *MomentWidget)
    {
        if (MomentWidget->objectName().isEmpty())
            MomentWidget->setObjectName("MomentWidget");
        MomentWidget->resize(400, 300);

        retranslateUi(MomentWidget);

        QMetaObject::connectSlotsByName(MomentWidget);
    } // setupUi

    void retranslateUi(QWidget *MomentWidget)
    {
        MomentWidget->setWindowTitle(QCoreApplication::translate("MomentWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MomentWidget: public Ui_MomentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOMENTWIDGET_H
