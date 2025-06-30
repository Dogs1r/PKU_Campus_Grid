/********************************************************************************
** Form generated from reading UI file 'themesettingwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEMESETTINGWIDGET_H
#define UI_THEMESETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThemeSettingWidget
{
public:

    void setupUi(QWidget *ThemeSettingWidget)
    {
        if (ThemeSettingWidget->objectName().isEmpty())
            ThemeSettingWidget->setObjectName("ThemeSettingWidget");
        ThemeSettingWidget->resize(400, 300);

        retranslateUi(ThemeSettingWidget);

        QMetaObject::connectSlotsByName(ThemeSettingWidget);
    } // setupUi

    void retranslateUi(QWidget *ThemeSettingWidget)
    {
        ThemeSettingWidget->setWindowTitle(QCoreApplication::translate("ThemeSettingWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThemeSettingWidget: public Ui_ThemeSettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEMESETTINGWIDGET_H
