/********************************************************************************
** Form generated from reading UI file 'bookmarkwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKMARKWIDGET_H
#define UI_BOOKMARKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookmarkWidget
{
public:

    void setupUi(QWidget *BookmarkWidget)
    {
        if (BookmarkWidget->objectName().isEmpty())
            BookmarkWidget->setObjectName("BookmarkWidget");
        BookmarkWidget->resize(400, 300);

        retranslateUi(BookmarkWidget);

        QMetaObject::connectSlotsByName(BookmarkWidget);
    } // setupUi

    void retranslateUi(QWidget *BookmarkWidget)
    {
        BookmarkWidget->setWindowTitle(QCoreApplication::translate("BookmarkWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookmarkWidget: public Ui_BookmarkWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKMARKWIDGET_H
