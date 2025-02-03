#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objBalance = new Balance(this);
    objLogin = new Login(this);
    objTransactions = new Transactions(this);
    objWithdrawal = new Withdrawal(this);
    objcreditOrDebit = new creditOrDebit(this);


    ui->stackedWidget->addWidget(objBalance);
    ui->stackedWidget->addWidget(objLogin);
    ui->stackedWidget->addWidget(objTransactions);
    ui->stackedWidget->addWidget(objWithdrawal);



    //Timer
    loginTimer = new QTimer(this);
    connect(loginTimer, &QTimer::timeout, this, &MainWindow::stopwatchForTenSeconds);

    //Go back connet
    connect(objLogin,&Login::backMain, this, &MainWindow::goBackSlot);
    //connect(objLogin,&Login::backMain, this, &MainWindow::goBackSlot);
    //connect(objBalance,&Balance::backMain, this, &MainWindow::goBackSlot);
    //connect(objTransactions,&Transactions::backMain, this, &MainWindow::goBackSlot);
    //connect(objWithdrawal,&Withdrawal::backMain, this, &MainWindow::goBackSlot);


    //Bring data
    connect(objLogin,&Login::sendDataToMain, this, &MainWindow::getDataFromLoginSlot);
    connect(objLogin,&Login::sendToken, this, &MainWindow::getTokenSlot);


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goBackSlot()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::getTokenSlot(QByteArray customersToken)
{
    //HAE TOKEN TÄSTÄ
}



void MainWindow::getDataFromLoginSlot(int idcustomer, int idcard, QString type, QString fname, QString lname)
{
    ui->labelHeyAndName->setText("Welcome " + fname + " " + lname);

    /* tähän tulee emit signaali,
     * josta jokainen hakee omaan widgettiin tarvittavat tiedot,
     * jotka on tullu mainista!
     *
     * emit nimeäSunOma(idcustomer, idcard, type, fname, lname);
     *
    */

}

//Go the login page
void MainWindow::on_btnStart_clicked()
{
    //loginTimer->start(10000);
    ui->stackedWidget->setCurrentWidget(objLogin);
}

//Go the balance page
void MainWindow::on_btnBalance_clicked()
{
    ui->stackedWidget->setCurrentWidget(objBalance);
}

//Go the withdrawal page
void MainWindow::on_btnWithdrawal_clicked()
{
    ui->stackedWidget->setCurrentWidget(objWithdrawal);
}

//Go the transaction page
void MainWindow::on_btnTransactions_clicked()
{
    ui->stackedWidget->setCurrentWidget(objTransactions);
}

//Go back button
void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//Logout button --> go start page
void MainWindow::on_btnLogout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::stopwatchForTenSeconds()
{
    qDebug()<<"10 seconds passed in the stopwatch";
    ui->stackedWidget->setCurrentIndex(0);
}
