/********************************************************************************
** Form generated from reading UI file 'buildinginfomanager.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDINGINFOMANAGER_H
#define UI_BUILDINGINFOMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildingInfo
{
public:

    void setupUi(QWidget *BuildingInfo)
    {
        if (BuildingInfo->objectName().isEmpty())
            BuildingInfo->setObjectName("BuildingInfo");
        BuildingInfo->resize(400, 300);

        retranslateUi(BuildingInfo);

        QMetaObject::connectSlotsByName(BuildingInfo);
    } // setupUi

    void retranslateUi(QWidget *BuildingInfo)
    {
        BuildingInfo->setWindowTitle(QCoreApplication::translate("BuildingInfo", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BuildingInfo: public Ui_BuildingInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDINGINFOMANAGER_H
