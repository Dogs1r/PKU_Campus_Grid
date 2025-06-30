/********************************************************************************
** Form generated from reading UI file 'mapnavigatewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPNAVIGATEWIDGET_H
#define UI_MAPNAVIGATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapNavigateWidget
{
public:

    void setupUi(QWidget *MapNavigateWidget)
    {
        if (MapNavigateWidget->objectName().isEmpty())
            MapNavigateWidget->setObjectName("MapNavigateWidget");
        MapNavigateWidget->resize(400, 300);

        retranslateUi(MapNavigateWidget);

        QMetaObject::connectSlotsByName(MapNavigateWidget);
    } // setupUi

    void retranslateUi(QWidget *MapNavigateWidget)
    {
        MapNavigateWidget->setWindowTitle(QCoreApplication::translate("MapNavigateWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapNavigateWidget: public Ui_MapNavigateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPNAVIGATEWIDGET_H
