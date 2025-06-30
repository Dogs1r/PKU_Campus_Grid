/********************************************************************************
** Form generated from reading UI file 'routefinder.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTEFINDER_H
#define UI_ROUTEFINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RouteFinder
{
public:

    void setupUi(QWidget *RouteFinder)
    {
        if (RouteFinder->objectName().isEmpty())
            RouteFinder->setObjectName("RouteFinder");
        RouteFinder->resize(400, 300);

        retranslateUi(RouteFinder);

        QMetaObject::connectSlotsByName(RouteFinder);
    } // setupUi

    void retranslateUi(QWidget *RouteFinder)
    {
        RouteFinder->setWindowTitle(QCoreApplication::translate("RouteFinder", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RouteFinder: public Ui_RouteFinder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTEFINDER_H
