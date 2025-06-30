/********************************************************************************
** Form generated from reading UI file 'aichatwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AICHATWIDGET_H
#define UI_AICHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AIChatWidget
{
public:

    void setupUi(QWidget *AIChatWidget)
    {
        if (AIChatWidget->objectName().isEmpty())
            AIChatWidget->setObjectName("AIChatWidget");
        AIChatWidget->resize(400, 300);

        retranslateUi(AIChatWidget);

        QMetaObject::connectSlotsByName(AIChatWidget);
    } // setupUi

    void retranslateUi(QWidget *AIChatWidget)
    {
        AIChatWidget->setWindowTitle(QCoreApplication::translate("AIChatWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AIChatWidget: public Ui_AIChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AICHATWIDGET_H
