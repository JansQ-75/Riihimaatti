/********************************************************************************
** Form generated from reading UI file 'otheramountwithdrawal.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OTHERAMOUNTWITHDRAWAL_H
#define UI_OTHERAMOUNTWITHDRAWAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_OtherAmountWithdrawal
{
public:
    QLineEdit *textAmount;
    QLabel *label_OA_header;
    QPushButton *btn5;
    QPushButton *btn2;
    QPushButton *btn9;
    QPushButton *btn0;
    QPushButton *btnOK;
    QPushButton *btn1;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btnClear;
    QPushButton *btn6;
    QPushButton *btn8;
    QPushButton *btn7;
    QLabel *label_errorText;

    void setupUi(QDialog *OtherAmountWithdrawal)
    {
        if (OtherAmountWithdrawal->objectName().isEmpty())
            OtherAmountWithdrawal->setObjectName("OtherAmountWithdrawal");
        OtherAmountWithdrawal->resize(500, 400);
        textAmount = new QLineEdit(OtherAmountWithdrawal);
        textAmount->setObjectName("textAmount");
        textAmount->setGeometry(QRect(60, 150, 121, 51));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        textAmount->setFont(font);
        label_OA_header = new QLabel(OtherAmountWithdrawal);
        label_OA_header->setObjectName("label_OA_header");
        label_OA_header->setGeometry(QRect(20, 50, 201, 71));
        label_OA_header->setFont(font);
        label_OA_header->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btn5 = new QPushButton(OtherAmountWithdrawal);
        btn5->setObjectName("btn5");
        btn5->setGeometry(QRect(330, 120, 65, 65));
        btn2 = new QPushButton(OtherAmountWithdrawal);
        btn2->setObjectName("btn2");
        btn2->setGeometry(QRect(330, 50, 65, 65));
        btn9 = new QPushButton(OtherAmountWithdrawal);
        btn9->setObjectName("btn9");
        btn9->setGeometry(QRect(400, 190, 65, 65));
        btn0 = new QPushButton(OtherAmountWithdrawal);
        btn0->setObjectName("btn0");
        btn0->setGeometry(QRect(330, 260, 65, 65));
        btnOK = new QPushButton(OtherAmountWithdrawal);
        btnOK->setObjectName("btnOK");
        btnOK->setGeometry(QRect(400, 260, 65, 65));
        btn1 = new QPushButton(OtherAmountWithdrawal);
        btn1->setObjectName("btn1");
        btn1->setGeometry(QRect(260, 50, 65, 65));
        btn3 = new QPushButton(OtherAmountWithdrawal);
        btn3->setObjectName("btn3");
        btn3->setGeometry(QRect(400, 50, 65, 65));
        btn4 = new QPushButton(OtherAmountWithdrawal);
        btn4->setObjectName("btn4");
        btn4->setGeometry(QRect(260, 120, 65, 65));
        btnClear = new QPushButton(OtherAmountWithdrawal);
        btnClear->setObjectName("btnClear");
        btnClear->setGeometry(QRect(260, 260, 65, 65));
        btn6 = new QPushButton(OtherAmountWithdrawal);
        btn6->setObjectName("btn6");
        btn6->setGeometry(QRect(400, 120, 65, 65));
        btn8 = new QPushButton(OtherAmountWithdrawal);
        btn8->setObjectName("btn8");
        btn8->setGeometry(QRect(330, 190, 65, 65));
        btn7 = new QPushButton(OtherAmountWithdrawal);
        btn7->setObjectName("btn7");
        btn7->setGeometry(QRect(260, 190, 65, 65));
        label_errorText = new QLabel(OtherAmountWithdrawal);
        label_errorText->setObjectName("label_errorText");
        label_errorText->setGeometry(QRect(30, 220, 211, 161));
        QFont font1;
        font1.setPointSize(12);
        label_errorText->setFont(font1);
        label_errorText->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        retranslateUi(OtherAmountWithdrawal);

        QMetaObject::connectSlotsByName(OtherAmountWithdrawal);
    } // setupUi

    void retranslateUi(QDialog *OtherAmountWithdrawal)
    {
        OtherAmountWithdrawal->setWindowTitle(QCoreApplication::translate("OtherAmountWithdrawal", "Dialog", nullptr));
        label_OA_header->setText(QCoreApplication::translate("OtherAmountWithdrawal", "Chooce amount \n"
"to withdraw", nullptr));
        btn5->setText(QCoreApplication::translate("OtherAmountWithdrawal", "5", nullptr));
        btn2->setText(QCoreApplication::translate("OtherAmountWithdrawal", "2", nullptr));
        btn9->setText(QCoreApplication::translate("OtherAmountWithdrawal", "9", nullptr));
        btn0->setText(QCoreApplication::translate("OtherAmountWithdrawal", "0", nullptr));
        btnOK->setText(QCoreApplication::translate("OtherAmountWithdrawal", "OK", nullptr));
        btn1->setText(QCoreApplication::translate("OtherAmountWithdrawal", "1", nullptr));
        btn3->setText(QCoreApplication::translate("OtherAmountWithdrawal", "3", nullptr));
        btn4->setText(QCoreApplication::translate("OtherAmountWithdrawal", "4", nullptr));
        btnClear->setText(QCoreApplication::translate("OtherAmountWithdrawal", "Clear", nullptr));
        btn6->setText(QCoreApplication::translate("OtherAmountWithdrawal", "6", nullptr));
        btn8->setText(QCoreApplication::translate("OtherAmountWithdrawal", "8", nullptr));
        btn7->setText(QCoreApplication::translate("OtherAmountWithdrawal", "7", nullptr));
        label_errorText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OtherAmountWithdrawal: public Ui_OtherAmountWithdrawal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OTHERAMOUNTWITHDRAWAL_H
