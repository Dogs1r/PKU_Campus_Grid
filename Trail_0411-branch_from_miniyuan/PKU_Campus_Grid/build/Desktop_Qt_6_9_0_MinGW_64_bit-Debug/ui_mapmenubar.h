/********************************************************************************
** Form generated from reading UI file 'mapmenubar.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPMENUBAR_H
#define UI_MAPMENUBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapMenubar
{
public:

    void setupUi(QWidget *MapMenubar)
    {
        if (MapMenubar->objectName().isEmpty())
            MapMenubar->setObjectName("MapMenubar");
        MapMenubar->resize(400, 300);

        retranslateUi(MapMenubar);

        QMetaObject::connectSlotsByName(MapMenubar);
    } // setupUi

    void retranslateUi(QWidget *MapMenubar)
    {
        MapMenubar->setWindowTitle(QCoreApplication::translate("MapMenubar", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapMenubar: public Ui_MapMenubar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPMENUBAR_H
