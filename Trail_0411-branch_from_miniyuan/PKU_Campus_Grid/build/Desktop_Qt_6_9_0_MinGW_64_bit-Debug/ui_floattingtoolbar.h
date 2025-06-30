/********************************************************************************
** Form generated from reading UI file 'floattingtoolbar.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOATTINGTOOLBAR_H
#define UI_FLOATTINGTOOLBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FloattingToolBar
{
public:

    void setupUi(QWidget *FloattingToolBar)
    {
        if (FloattingToolBar->objectName().isEmpty())
            FloattingToolBar->setObjectName("FloattingToolBar");
        FloattingToolBar->resize(400, 300);

        retranslateUi(FloattingToolBar);

        QMetaObject::connectSlotsByName(FloattingToolBar);
    } // setupUi

    void retranslateUi(QWidget *FloattingToolBar)
    {
        FloattingToolBar->setWindowTitle(QCoreApplication::translate("FloattingToolBar", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FloattingToolBar: public Ui_FloattingToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOATTINGTOOLBAR_H
