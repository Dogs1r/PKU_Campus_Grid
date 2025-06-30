/********************************************************************************
** Form generated from reading UI file 'searchbox.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHBOX_H
#define UI_SEARCHBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchBox
{
public:

    void setupUi(QWidget *SearchBox)
    {
        if (SearchBox->objectName().isEmpty())
            SearchBox->setObjectName("SearchBox");
        SearchBox->resize(319, 63);

        retranslateUi(SearchBox);

        QMetaObject::connectSlotsByName(SearchBox);
    } // setupUi

    void retranslateUi(QWidget *SearchBox)
    {
        SearchBox->setWindowTitle(QCoreApplication::translate("SearchBox", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchBox: public Ui_SearchBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHBOX_H
