/********************************************************************************
** Form generated from reading UI file 'mapinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPINFOWIDGET_H
#define UI_MAPINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapInfoWidget
{
public:

    void setupUi(QWidget *MapInfoWidget)
    {
        if (MapInfoWidget->objectName().isEmpty())
            MapInfoWidget->setObjectName("MapInfoWidget");
        MapInfoWidget->resize(400, 300);

        retranslateUi(MapInfoWidget);

        QMetaObject::connectSlotsByName(MapInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *MapInfoWidget)
    {
        MapInfoWidget->setWindowTitle(QCoreApplication::translate("MapInfoWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapInfoWidget: public Ui_MapInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPINFOWIDGET_H
