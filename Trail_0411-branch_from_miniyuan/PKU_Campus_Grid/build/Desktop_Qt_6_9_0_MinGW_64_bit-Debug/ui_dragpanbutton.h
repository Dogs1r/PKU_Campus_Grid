/********************************************************************************
** Form generated from reading UI file 'dragpanbutton.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAGPANBUTTON_H
#define UI_DRAGPANBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DragPanButton
{
public:

    void setupUi(QWidget *DragPanButton)
    {
        if (DragPanButton->objectName().isEmpty())
            DragPanButton->setObjectName("DragPanButton");
        DragPanButton->resize(400, 300);

        retranslateUi(DragPanButton);

        QMetaObject::connectSlotsByName(DragPanButton);
    } // setupUi

    void retranslateUi(QWidget *DragPanButton)
    {
        DragPanButton->setWindowTitle(QCoreApplication::translate("DragPanButton", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DragPanButton: public Ui_DragPanButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAGPANBUTTON_H
