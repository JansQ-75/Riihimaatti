#include "environment.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //NetworkManager
    MainWindowManager = new QNetworkAccessManager(this);

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
    connect(objWithdrawal,&Withdrawal::backMainSignal, this, &MainWindow::goBackSlot);


    //Bring data
    connect(objLogin,&Login::sendDataToMain, this, &MainWindow::getDataFromLoginSlot);
    connect(objLogin,&Login::sendToken, this, &MainWindow::getTokenSlot);
    connect(objLogin, &Login::RetrieveCustomerData, this, &MainWindow::getCustomerData);

    // Send data
    connect(this, &MainWindow::sendTokenToWithdrawal, objWithdrawal, &Withdrawal::getToken);
    connect(this, &MainWindow::sendCustomerWithdrawal, objWithdrawal, &Withdrawal::CustomerDataSlot);


}



MainWindow::~MainWindow()
{
    delete ui;
    MainWindowManager->deleteLater();
}

void MainWindow::goBackSlot()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::getTokenSlot(QByteArray customersToken)
{
    token = customersToken;
    //HAE TOKEN TÄSTÄ
    emit sendTokenToWithdrawal(customersToken); // signal for getting token in Withdrawal
}

void MainWindow::getCustomerData(int idcustomer)
{
    // customerId = idcustomer;
    qDebug() << "Customers id: " <<idcustomer;

    // API request
    QString site_url=Environment::base_url()+"/bank_account/by-customerId/" + QString::number(idcustomer);
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + token));

    // make GET request
    QNetworkReply *reply = MainWindowManager->get(request);

    // connect to slot for handling response
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        this->receivedCustomerInfo(reply);
        reply->deleteLater();
    });




}

void MainWindow::receivedCustomerInfo(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response_data = reply->readAll();
        qDebug() << "Raw API Response: " << response_data;

        QJsonDocument jsonresponse = QJsonDocument::fromJson(response_data);

        if (jsonresponse.isNull() || !jsonresponse.isObject()) {
        qDebug() << "Error: Invalid JSON response";
        reply->deleteLater();
        return;
        }

        QJsonObject jsonObj = jsonresponse.object();

        // Extract data
        if (jsonObj.contains("idbank_account")) idbank_account = jsonObj["idbank_account"].toInt();
        if (jsonObj.contains("bank_account_number")) bank_account_number = jsonObj["bank_account_number"].toString();
        if (jsonObj.contains("account_type")) account_type = jsonObj["account_type"].toString();
        if (jsonObj.contains("balance")) balance = QString::number(jsonObj["balance"].toString().toDouble(), 'f', 2).toDouble();
        if (jsonObj.contains("credit_limit")) credit_limit = QString::number(jsonObj["credit_limit"].toString().toDouble(), 'f', 2).toDouble();
        if (jsonObj.contains("idcustomer")) idcustomer = jsonObj["idcustomer"].toInt();
        if (jsonObj.contains("fname")) fname = jsonObj["fname"].toString();
        if (jsonObj.contains("lname")) lname = jsonObj["lname"].toString();
        if (jsonObj.contains("address")) address = jsonObj["address"].toString();
        if (jsonObj.contains("phone")) phone = jsonObj["phone"].toString();

        //debuggausta
        qDebug() << "Bank account number successfully: " << bank_account_number;
        qDebug() << "idcustomer successfully: " << idcustomer;
        qDebug() << "phone successfully: " << phone;
        qDebug() << "credit " << credit_limit;
        qDebug() << "balance " << balance;

        ui->labelHeyAndName->setText("Welcome " + fname + " " + lname);

        // Signaalit asiakastietojen hakemiseksi omaan widgetiin.
        /*
            Keksikää omat signaalit vastaavalla tavalla
        */
        emit sendCustomerWithdrawal(idbank_account, bank_account_number, account_type, balance, credit_limit, idcustomer, fname, lname, address, phone);

        // delete later
        reply->deleteLater();

    } else {
        qDebug() << "Error: " << reply->errorString();
    }

}



void MainWindow::getDataFromLoginSlot(int idcustomer, int idcard, QString type, QString fname, QString lname)
{

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
