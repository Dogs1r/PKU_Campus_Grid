/********************************************************************************
** Form generated from reading UI file 'studyfinderwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDYFINDERWIDGET_H
#define UI_STUDYFINDERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudyFinderWIdget
{
public:

    void setupUi(QWidget *StudyFinderWIdget)
    {
        if (StudyFinderWIdget->objectName().isEmpty())
            StudyFinderWIdget->setObjectName("StudyFinderWIdget");
        StudyFinderWIdget->resize(400, 300);

        retranslateUi(StudyFinderWIdget);

        QMetaObject::connectSlotsByName(StudyFinderWIdget);
    } // setupUi

    void retranslateUi(QWidget *StudyFinderWIdget)
    {
        StudyFinderWIdget->setWindowTitle(QCoreApplication::translate("StudyFinderWIdget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudyFinderWIdget: public Ui_StudyFinderWIdget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDYFINDERWIDGET_H
