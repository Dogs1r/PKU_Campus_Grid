/********************************************************************************
** Form generated from reading UI file 'buildingdetailwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDINGDETAILWIDGET_H
#define UI_BUILDINGDETAILWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildingDetailWidget
{
public:

    void setupUi(QWidget *BuildingDetailWidget)
    {
        if (BuildingDetailWidget->objectName().isEmpty())
            BuildingDetailWidget->setObjectName("BuildingDetailWidget");
        BuildingDetailWidget->resize(400, 300);

        retranslateUi(BuildingDetailWidget);

        QMetaObject::connectSlotsByName(BuildingDetailWidget);
    } // setupUi

    void retranslateUi(QWidget *BuildingDetailWidget)
    {
        BuildingDetailWidget->setWindowTitle(QCoreApplication::translate("BuildingDetailWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BuildingDetailWidget: public Ui_BuildingDetailWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDINGDETAILWIDGET_H
