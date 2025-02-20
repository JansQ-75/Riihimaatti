/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QPushButton *btn1;
    QPushButton *btn4;
    QLabel *label_9;
    QPushButton *btn3;
    QLabel *label_10;
    QLabel *labelPincode;
    QPushButton *btn9;
    QPushButton *btnClear;
    QPushButton *btnLogin;
    QPushButton *btn2;
    QPushButton *btn7;
    QPushButton *btn0;
    QPushButton *btn6;
    QLabel *labelCardnumber;
    QPushButton *btn5;
    QPushButton *btn8;
    QLabel *labelInfo;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(800, 480);
        btn1 = new QPushButton(Login);
        btn1->setObjectName("btn1");
        btn1->setGeometry(QRect(470, 110, 65, 65));
        btn4 = new QPushButton(Login);
        btn4->setObjectName("btn4");
        btn4->setGeometry(QRect(470, 180, 65, 65));
        label_9 = new QLabel(Login);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 170, 200, 60));
        QFont font;
        font.setFamilies({QString::fromUtf8("Footlight MT")});
        font.setPointSize(18);
        label_9->setFont(font);
        btn3 = new QPushButton(Login);
        btn3->setObjectName("btn3");
        btn3->setGeometry(QRect(610, 110, 65, 65));
        label_10 = new QLabel(Login);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(60, 250, 200, 60));
        label_10->setFont(font);
        labelPincode = new QLabel(Login);
        labelPincode->setObjectName("labelPincode");
        labelPincode->setGeometry(QRect(290, 250, 111, 61));
        btn9 = new QPushButton(Login);
        btn9->setObjectName("btn9");
        btn9->setGeometry(QRect(610, 250, 65, 65));
        btnClear = new QPushButton(Login);
        btnClear->setObjectName("btnClear");
        btnClear->setGeometry(QRect(470, 320, 65, 65));
        btnLogin = new QPushButton(Login);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(610, 320, 65, 65));
        btn2 = new QPushButton(Login);
        btn2->setObjectName("btn2");
        btn2->setGeometry(QRect(540, 110, 65, 65));
        btn7 = new QPushButton(Login);
        btn7->setObjectName("btn7");
        btn7->setGeometry(QRect(470, 250, 65, 65));
        btn0 = new QPushButton(Login);
        btn0->setObjectName("btn0");
        btn0->setGeometry(QRect(540, 320, 65, 65));
        btn6 = new QPushButton(Login);
        btn6->setObjectName("btn6");
        btn6->setGeometry(QRect(610, 180, 65, 65));
        labelCardnumber = new QLabel(Login);
        labelCardnumber->setObjectName("labelCardnumber");
        labelCardnumber->setGeometry(QRect(290, 180, 131, 61));
        QFont font1;
        font1.setPointSize(9);
        labelCardnumber->setFont(font1);
        labelCardnumber->setStyleSheet(QString::fromUtf8(""));
        btn5 = new QPushButton(Login);
        btn5->setObjectName("btn5");
        btn5->setGeometry(QRect(540, 180, 65, 65));
        btn8 = new QPushButton(Login);
        btn8->setObjectName("btn8");
        btn8->setGeometry(QRect(540, 250, 65, 65));
        labelInfo = new QLabel(Login);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(470, 400, 201, 21));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        btn1->setText(QCoreApplication::translate("Login", "1", nullptr));
        btn4->setText(QCoreApplication::translate("Login", "4", nullptr));
        label_9->setText(QCoreApplication::translate("Login", "Card number", nullptr));
        btn3->setText(QCoreApplication::translate("Login", "3", nullptr));
        label_10->setText(QCoreApplication::translate("Login", "Pin code", nullptr));
        labelPincode->setText(QCoreApplication::translate("Login", "Your pin code", nullptr));
        btn9->setText(QCoreApplication::translate("Login", "9", nullptr));
        btnClear->setText(QCoreApplication::translate("Login", "Clear", nullptr));
        btnLogin->setText(QCoreApplication::translate("Login", "Login", nullptr));
        btn2->setText(QCoreApplication::translate("Login", "2", nullptr));
        btn7->setText(QCoreApplication::translate("Login", "7", nullptr));
        btn0->setText(QCoreApplication::translate("Login", "0", nullptr));
        btn6->setText(QCoreApplication::translate("Login", "6", nullptr));
        labelCardnumber->setText(QCoreApplication::translate("Login", "Your card number", nullptr));
        btn5->setText(QCoreApplication::translate("Login", "5", nullptr));
        btn8->setText(QCoreApplication::translate("Login", "8", nullptr));
        labelInfo->setText(QCoreApplication::translate("Login", ".", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
