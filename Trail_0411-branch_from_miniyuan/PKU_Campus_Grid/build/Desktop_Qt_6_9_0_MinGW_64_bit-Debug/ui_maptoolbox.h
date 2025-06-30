/********************************************************************************
** Form generated from reading UI file 'maptoolbox.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPTOOLBOX_H
#define UI_MAPTOOLBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLayout>
#include <QtWidgets/QToolBox>

QT_BEGIN_NAMESPACE

class Ui_MapToolBox
{
public:

    void setupUi(QToolBox *MapToolBox)
    {
        if (MapToolBox->objectName().isEmpty())
            MapToolBox->setObjectName("MapToolBox");
        MapToolBox->resize(400, 300);

        retranslateUi(MapToolBox);

        QMetaObject::connectSlotsByName(MapToolBox);
    } // setupUi

    void retranslateUi(QToolBox *MapToolBox)
    {
        MapToolBox->setWindowTitle(QCoreApplication::translate("MapToolBox", "ToolBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapToolBox: public Ui_MapToolBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPTOOLBOX_H
