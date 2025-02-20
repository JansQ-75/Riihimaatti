/********************************************************************************
** Form generated from reading UI file 'statuswithdrawal.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSWITHDRAWAL_H
#define UI_STATUSWITHDRAWAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_StatusWithdrawal
{
public:
    QLabel *label_status;

    void setupUi(QDialog *StatusWithdrawal)
    {
        if (StatusWithdrawal->objectName().isEmpty())
            StatusWithdrawal->setObjectName("StatusWithdrawal");
        StatusWithdrawal->resize(500, 400);
        label_status = new QLabel(StatusWithdrawal);
        label_status->setObjectName("label_status");
        label_status->setGeometry(QRect(30, 70, 441, 241));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label_status->setFont(font);
        label_status->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(StatusWithdrawal);

        QMetaObject::connectSlotsByName(StatusWithdrawal);
    } // setupUi

    void retranslateUi(QDialog *StatusWithdrawal)
    {
        StatusWithdrawal->setWindowTitle(QCoreApplication::translate("StatusWithdrawal", "Dialog", nullptr));
        label_status->setText(QCoreApplication::translate("StatusWithdrawal", "Making withdrawal...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatusWithdrawal: public Ui_StatusWithdrawal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWITHDRAWAL_H
