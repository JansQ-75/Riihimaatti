/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *btnLogin;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *textCardnumber;
    QPlainTextEdit *textPin;
    QWidget *page_2;
    QPushButton *btnBalance;
    QPushButton *btnTransactions;
    QPushButton *btnWithdrawal;
    QWidget *page_3;
    QLabel *label_3;
    QWidget *page_4;
    QLabel *label_4;
    QWidget *page_5;
    QLabel *label_5;
    QWidget *page_6;
    QLabel *label_6;
    QPushButton *btnLogout;
    QPushButton *btnBack;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 597);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 30, 791, 481));
        stackedWidget->setAutoFillBackground(false);
        page = new QWidget();
        page->setObjectName("page");
        btnLogin = new QPushButton(page);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(310, 420, 97, 30));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 180, 261, 61));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 260, 261, 61));
        textCardnumber = new QPlainTextEdit(page);
        textCardnumber->setObjectName("textCardnumber");
        textCardnumber->setGeometry(QRect(480, 170, 104, 76));
        textPin = new QPlainTextEdit(page);
        textPin->setObjectName("textPin");
        textPin->setGeometry(QRect(373, 270, 261, 76));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        btnBalance = new QPushButton(page_2);
        btnBalance->setObjectName("btnBalance");
        btnBalance->setGeometry(QRect(280, 130, 191, 30));
        btnTransactions = new QPushButton(page_2);
        btnTransactions->setObjectName("btnTransactions");
        btnTransactions->setGeometry(QRect(280, 280, 211, 30));
        btnWithdrawal = new QPushButton(page_2);
        btnWithdrawal->setObjectName("btnWithdrawal");
        btnWithdrawal->setGeometry(QRect(280, 200, 211, 30));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 170, 63, 21));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        label_4 = new QLabel(page_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(450, 260, 63, 21));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        label_5 = new QLabel(page_5);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(320, 210, 63, 21));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        label_6 = new QLabel(page_6);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(242, 150, 341, 171));
        stackedWidget->addWidget(page_6);
        btnLogout = new QPushButton(centralwidget);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setGeometry(QRect(720, 0, 71, 30));
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(340, 520, 91, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Insert your card number", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Insert your pin code", nullptr));
        btnBalance->setText(QCoreApplication::translate("MainWindow", "Show balance", nullptr));
        btnTransactions->setText(QCoreApplication::translate("MainWindow", "Show transactions", nullptr));
        btnWithdrawal->setText(QCoreApplication::translate("MainWindow", "Make a withdrawal", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "SALDO", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "nosto", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "tilitapahtumat", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "kiitos? onnistuit kirjautumaan ulos", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        btnBack->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
