/********************************************************************************
** Form generated from reading UI file 'fancytoolbar.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FANCYTOOLBAR_H
#define UI_FANCYTOOLBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FancyToolBar
{
public:

    void setupUi(QWidget *FancyToolBar)
    {
        if (FancyToolBar->objectName().isEmpty())
            FancyToolBar->setObjectName("FancyToolBar");
        FancyToolBar->resize(400, 300);

        retranslateUi(FancyToolBar);

        QMetaObject::connectSlotsByName(FancyToolBar);
    } // setupUi

    void retranslateUi(QWidget *FancyToolBar)
    {
        FancyToolBar->setWindowTitle(QCoreApplication::translate("FancyToolBar", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FancyToolBar: public Ui_FancyToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FANCYTOOLBAR_H
