/********************************************************************************
** Form generated from reading UI file 'buildinginteractionsystem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDINGINTERACTIONSYSTEM_H
#define UI_BUILDINGINTERACTIONSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildingInteractionSystem
{
public:

    void setupUi(QWidget *BuildingInteractionSystem)
    {
        if (BuildingInteractionSystem->objectName().isEmpty())
            BuildingInteractionSystem->setObjectName("BuildingInteractionSystem");
        BuildingInteractionSystem->resize(400, 300);

        retranslateUi(BuildingInteractionSystem);

        QMetaObject::connectSlotsByName(BuildingInteractionSystem);
    } // setupUi

    void retranslateUi(QWidget *BuildingInteractionSystem)
    {
        BuildingInteractionSystem->setWindowTitle(QCoreApplication::translate("BuildingInteractionSystem", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BuildingInteractionSystem: public Ui_BuildingInteractionSystem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDINGINTERACTIONSYSTEM_H
