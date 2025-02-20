/********************************************************************************
** Form generated from reading UI file 'withdrawal.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WITHDRAWAL_H
#define UI_WITHDRAWAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Withdrawal
{
public:
    QLabel *label_w_header;
    QPushButton *btn_20e;
    QPushButton *btn_60e;
    QPushButton *btn_otherAmount;
    QPushButton *btn_100e;
    QPushButton *btn_40e;
    QLabel *label_balance;
    QLabel *label_ownerName;

    void setupUi(QWidget *Withdrawal)
    {
        if (Withdrawal->objectName().isEmpty())
            Withdrawal->setObjectName("Withdrawal");
        Withdrawal->resize(800, 480);
        Withdrawal->setMinimumSize(QSize(0, 0));
        label_w_header = new QLabel(Withdrawal);
        label_w_header->setObjectName("label_w_header");
        label_w_header->setGeometry(QRect(300, 10, 191, 71));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        label_w_header->setFont(font);
        label_w_header->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btn_20e = new QPushButton(Withdrawal);
        btn_20e->setObjectName("btn_20e");
        btn_20e->setGeometry(QRect(20, 280, 150, 60));
        btn_20e->setMinimumSize(QSize(80, 60));
        QFont font1;
        font1.setPointSize(16);
        btn_20e->setFont(font1);
        btn_60e = new QPushButton(Withdrawal);
        btn_60e->setObjectName("btn_60e");
        btn_60e->setGeometry(QRect(610, 210, 150, 60));
        btn_60e->setMinimumSize(QSize(80, 60));
        btn_60e->setFont(font1);
        btn_otherAmount = new QPushButton(Withdrawal);
        btn_otherAmount->setObjectName("btn_otherAmount");
        btn_otherAmount->setGeometry(QRect(610, 370, 150, 60));
        btn_otherAmount->setMinimumSize(QSize(80, 60));
        btn_otherAmount->setFont(font1);
        btn_100e = new QPushButton(Withdrawal);
        btn_100e->setObjectName("btn_100e");
        btn_100e->setGeometry(QRect(610, 290, 150, 60));
        btn_100e->setMinimumSize(QSize(80, 60));
        btn_100e->setFont(font1);
        btn_40e = new QPushButton(Withdrawal);
        btn_40e->setObjectName("btn_40e");
        btn_40e->setGeometry(QRect(20, 360, 150, 60));
        btn_40e->setMinimumSize(QSize(80, 60));
        btn_40e->setFont(font1);
        label_balance = new QLabel(Withdrawal);
        label_balance->setObjectName("label_balance");
        label_balance->setGeometry(QRect(270, 120, 331, 151));
        QFont font2;
        font2.setPointSize(14);
        label_balance->setFont(font2);
        label_balance->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        label_ownerName = new QLabel(Withdrawal);
        label_ownerName->setObjectName("label_ownerName");
        label_ownerName->setGeometry(QRect(30, 120, 221, 131));
        label_ownerName->setFont(font2);
        label_ownerName->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        retranslateUi(Withdrawal);

        QMetaObject::connectSlotsByName(Withdrawal);
    } // setupUi

    void retranslateUi(QWidget *Withdrawal)
    {
        Withdrawal->setWindowTitle(QCoreApplication::translate("Withdrawal", "Form", nullptr));
        label_w_header->setText(QCoreApplication::translate("Withdrawal", "Withdrawal", nullptr));
        btn_20e->setText(QCoreApplication::translate("Withdrawal", "20", nullptr));
        btn_60e->setText(QCoreApplication::translate("Withdrawal", "60", nullptr));
        btn_otherAmount->setText(QCoreApplication::translate("Withdrawal", "Other Amount", nullptr));
        btn_100e->setText(QCoreApplication::translate("Withdrawal", "100", nullptr));
        btn_40e->setText(QCoreApplication::translate("Withdrawal", "40", nullptr));
        label_balance->setText(QCoreApplication::translate("Withdrawal", "tilin saldo", nullptr));
        label_ownerName->setText(QCoreApplication::translate("Withdrawal", "Omistajan nimi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Withdrawal: public Ui_Withdrawal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WITHDRAWAL_H
