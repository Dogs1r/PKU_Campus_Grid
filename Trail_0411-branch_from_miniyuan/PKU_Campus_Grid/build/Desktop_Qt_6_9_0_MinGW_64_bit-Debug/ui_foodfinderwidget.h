/********************************************************************************
** Form generated from reading UI file 'foodfinderwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOODFINDERWIDGET_H
#define UI_FOODFINDERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FoodFinderWidget
{
public:

    void setupUi(QWidget *FoodFinderWidget)
    {
        if (FoodFinderWidget->objectName().isEmpty())
            FoodFinderWidget->setObjectName("FoodFinderWidget");
        FoodFinderWidget->resize(400, 300);

        retranslateUi(FoodFinderWidget);

        QMetaObject::connectSlotsByName(FoodFinderWidget);
    } // setupUi

    void retranslateUi(QWidget *FoodFinderWidget)
    {
        FoodFinderWidget->setWindowTitle(QCoreApplication::translate("FoodFinderWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FoodFinderWidget: public Ui_FoodFinderWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOODFINDERWIDGET_H
