/********************************************************************************
** Form generated from reading UI file 'confirmdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMDIALOG_H
#define UI_CONFIRMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfirmDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ConfirmDialog)
    {
        if (ConfirmDialog->objectName().isEmpty())
            ConfirmDialog->setObjectName("ConfirmDialog");
        ConfirmDialog->resize(258, 183);
        verticalLayoutWidget = new QWidget(ConfirmDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(50, 60, 166, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ConfirmDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ConfirmDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ConfirmDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfirmDialog)
    {
        ConfirmDialog->setWindowTitle(QCoreApplication::translate("ConfirmDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ConfirmDialog", "Are you sure?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfirmDialog: public Ui_ConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMDIALOG_H
