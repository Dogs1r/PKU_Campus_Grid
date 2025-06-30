/********************************************************************************
** Form generated from reading UI file 'bookmarkmanager.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKMARKMANAGER_H
#define UI_BOOKMARKMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookmarkManager
{
public:

    void setupUi(QWidget *BookmarkManager)
    {
        if (BookmarkManager->objectName().isEmpty())
            BookmarkManager->setObjectName("BookmarkManager");
        BookmarkManager->resize(400, 300);

        retranslateUi(BookmarkManager);

        QMetaObject::connectSlotsByName(BookmarkManager);
    } // setupUi

    void retranslateUi(QWidget *BookmarkManager)
    {
        BookmarkManager->setWindowTitle(QCoreApplication::translate("BookmarkManager", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookmarkManager: public Ui_BookmarkManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKMARKMANAGER_H
