/********************************************************************************
** Form generated from reading UI file 'balance.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANCE_H
#define UI_BALANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Balance
{
public:
    QLabel *label_header;
    QLabel *labelCustomer;
    QLabel *labelBalance;
    QPushButton *BtnToTransactions;

    void setupUi(QWidget *Balance)
    {
        if (Balance->objectName().isEmpty())
            Balance->setObjectName("Balance");
        Balance->resize(800, 480);
        label_header = new QLabel(Balance);
        label_header->setObjectName("label_header");
        label_header->setGeometry(QRect(80, 30, 241, 61));
        labelCustomer = new QLabel(Balance);
        labelCustomer->setObjectName("labelCustomer");
        labelCustomer->setGeometry(QRect(80, 160, 191, 81));
        labelBalance = new QLabel(Balance);
        labelBalance->setObjectName("labelBalance");
        labelBalance->setGeometry(QRect(570, 170, 171, 61));
        BtnToTransactions = new QPushButton(Balance);
        BtnToTransactions->setObjectName("BtnToTransactions");
        BtnToTransactions->setGeometry(QRect(570, 320, 190, 31));

        retranslateUi(Balance);

        QMetaObject::connectSlotsByName(Balance);
    } // setupUi

    void retranslateUi(QWidget *Balance)
    {
        Balance->setWindowTitle(QCoreApplication::translate("Balance", "Form", nullptr));
        label_header->setText(QCoreApplication::translate("Balance", "Balance", nullptr));
        labelCustomer->setText(QCoreApplication::translate("Balance", "Customer info", nullptr));
        labelBalance->setText(QCoreApplication::translate("Balance", "Balance", nullptr));
        BtnToTransactions->setText(QCoreApplication::translate("Balance", "View Transactions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Balance: public Ui_Balance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANCE_H
