/********************************************************************************
** Form generated from reading UI file 'maintoolbar.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTOOLBAR_H
#define UI_MAINTOOLBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainToolBar
{
public:

    void setupUi(QWidget *MainToolBar)
    {
        if (MainToolBar->objectName().isEmpty())
            MainToolBar->setObjectName("MainToolBar");
        MainToolBar->resize(400, 300);

        retranslateUi(MainToolBar);

        QMetaObject::connectSlotsByName(MainToolBar);
    } // setupUi

    void retranslateUi(QWidget *MainToolBar)
    {
        MainToolBar->setWindowTitle(QCoreApplication::translate("MainToolBar", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainToolBar: public Ui_MainToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTOOLBAR_H
