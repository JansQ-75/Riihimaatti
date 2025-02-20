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
    QLabel *label_7;
    QPushButton *btnStart;
    QLabel *label_logo;
    QWidget *page_2;
    QPushButton *btnBalance;
    QPushButton *btnTransactions;
    QPushButton *btnWithdrawal;
    QLabel *labelHeyAndName;
    QLabel *label_test;
    QWidget *page_6;
    QLabel *label_thankYou;
    QLabel *label_logout;
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
        stackedWidget->setGeometry(QRect(0, 30, 800, 480));
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page = new QWidget();
        page->setObjectName("page");
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(480, 190, 301, 81));
        QFont font;
        font.setPointSize(35);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnStart = new QPushButton(page);
        btnStart->setObjectName("btnStart");
        btnStart->setGeometry(QRect(540, 270, 150, 50));
        label_logo = new QLabel(page);
        label_logo->setObjectName("label_logo");
        label_logo->setGeometry(QRect(0, 0, 491, 471));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Script")});
        font1.setBold(true);
        label_logo->setFont(font1);
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
        labelHeyAndName = new QLabel(page_2);
        labelHeyAndName->setObjectName("labelHeyAndName");
        labelHeyAndName->setGeometry(QRect(270, 60, 411, 21));
        label_test = new QLabel(page_2);
        label_test->setObjectName("label_test");
        label_test->setGeometry(QRect(320, 180, 421, 291));
        stackedWidget->addWidget(page_2);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        label_thankYou = new QLabel(page_6);
        label_thankYou->setObjectName("label_thankYou");
        label_thankYou->setGeometry(QRect(180, 180, 451, 111));
        QFont font2;
        font2.setPointSize(16);
        label_thankYou->setFont(font2);
        label_thankYou->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_logout = new QLabel(page_6);
        label_logout->setObjectName("label_logout");
        label_logout->setGeometry(QRect(190, 30, 411, 171));
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        label_logout->setFont(font3);
        label_logout->setAlignment(Qt::AlignmentFlag::AlignCenter);
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
        menubar->setGeometry(QRect(0, 0, 800, 22));
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
        label_7->setText(QCoreApplication::translate("MainWindow", "Riihimaatti", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_logo->setText(QString());
        btnBalance->setText(QCoreApplication::translate("MainWindow", "Show balance", nullptr));
        btnTransactions->setText(QCoreApplication::translate("MainWindow", "Show transactions", nullptr));
        btnWithdrawal->setText(QCoreApplication::translate("MainWindow", "Make a withdrawal", nullptr));
        labelHeyAndName->setText(QCoreApplication::translate("MainWindow", "Tervetuloa", nullptr));
        label_test->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_thankYou->setText(QCoreApplication::translate("MainWindow", "Thank you for choosing Riihimaatti!", nullptr));
        label_logout->setText(QCoreApplication::translate("MainWindow", "Logout successful", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        btnBack->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
