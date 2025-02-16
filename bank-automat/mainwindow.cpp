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

    //Create objects
    objBalance = new Balance(this);
    objLogin = new Login(this);
    objTransactions = new Transactions(this);
    objWithdrawal = new Withdrawal(this);

    // Timer
    mainTimer = new QTimer(this);

    // other screenviews
    ui->stackedWidget->addWidget(objBalance);
    ui->stackedWidget->addWidget(objLogin);
    ui->stackedWidget->addWidget(objTransactions);
    ui->stackedWidget->addWidget(objWithdrawal);

    // make list of push buttons of stacked widget page 1
    QWidget *page = ui->stackedWidget->widget(1);
    QList<QPushButton*> menuButtons = page->findChildren<QPushButton*>();
    //connect button' clicked() signals to slot for reseting timer if necessary
    for (QPushButton* button : menuButtons) {
        connect(button, &QPushButton::pressed, this, &MainWindow::onButtonPressed);
    }

    // Timer connections
    connect(mainTimer, &QTimer::timeout, this, &MainWindow::on_btnLogout_clicked);

    //Go back -connect
    connect(objLogin,&Login::backMain, this, &MainWindow::goBackSlot);
    connect(objTransactions,&Transactions::backMain, this, &MainWindow::goBackSlot);
    connect(objWithdrawal,&Withdrawal::backMainSignal, this, &MainWindow::goBackSlot);

    // Logout connections
    connect(objWithdrawal, &Withdrawal::logOutSignal, this, &MainWindow::on_btnLogout_clicked);
    connect(objLogin, &Login::backStartScreen, this, &MainWindow::on_btnLogout_clicked);
    connect(objBalance, &Balance::backStartScreen, this, &MainWindow::on_btnLogout_clicked);

    //Bring data
    connect(objLogin,&Login::sendToken, this, &MainWindow::getTokenSlot);
    connect(objLogin, &Login::RetrieveCustomerData, this, &MainWindow::getCustomerData);
    connect(objLogin,&Login::sendDataToMain, this, &MainWindow::getDataFromLoginSlot);
    connect(objLogin, &Login::sendDualInfoToMain, this, &MainWindow::getDualSelections);

    //Send...
    //...tokens
    connect(this, &MainWindow::sendTokenToWidget, objWithdrawal, &Withdrawal::getToken);
    connect(this, &MainWindow::sendTokenToWidget, objTransactions, &Transactions::getToken);

    //...customer data
    connect(this, &MainWindow::sendCustomerData, objWithdrawal, &Withdrawal::CustomerDataSlot);
    connect(this, &MainWindow::sendCustomerData, objTransactions, &Transactions::CustomerDataSlot);
    connect(this, &MainWindow::sendCustomerData, objBalance, &Balance::CustomerDataSlot);
      
    // ...login data
    connect(this, &MainWindow::sendLoginDataWithdrawal, objWithdrawal, &Withdrawal::LoginDataSlot);

    // for connecting balance to transactions
    connect(objBalance, &Balance::openTransactions, this, &MainWindow::on_btnTransactions_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    MainWindowManager->deleteLater();
}

void MainWindow::goBackSlot()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->startMainTimer();
}

void MainWindow::getTokenSlot(QByteArray customersToken)
{
    token = customersToken; // store token
  
    //Send token signal to widgets
    emit sendTokenToWidget(customersToken);
}

void MainWindow::getCustomerData(int idcustomer)
{
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

        ui->labelHeyAndName->setText("Welcome " + fname + " " + lname);

        //Signal to send customer's data to widgets
        emit sendCustomerData(idbank_account, bank_account_number, account_type, balance, credit_limit, idcustomer, fname, lname, address, phone);

        //Delete later
        reply->deleteLater();

    } else {
        qDebug() << "Error: " << reply->errorString();
    }

}

void MainWindow::getDualSelections(QString dualAccountType, int dualAccountId)
{
    // set selected values to variables in Withdrawal
    objWithdrawal->setDualAccountType(dualAccountType);
    objWithdrawal->setDualAccountId(dualAccountId);
    objBalance->setDualAccountType(dualAccountType);

    // haetaan tilin tiedot kun on valittu credit tai debit

    // API request
    QString site_url=Environment::base_url()+"/bank_account/by-id/" + QString::number(dualAccountId);
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

void MainWindow::getDataFromLoginSlot(int idcustomer, int idcard, QString type, QString fname, QString lname)
{
    emit sendLoginDataWithdrawal(idcard, type); // send login data to withdrawal
    objBalance->setCardtype(type);
}

void MainWindow::startMainTimer()
{
    mainTimer->start(30000); //start 30s timer
}

void MainWindow::stopWidgetTimers()
{
    objLogin->stopLoginTimer();     // stop inactivitytimer in Login
    objWithdrawal->stopTimer();     // stop inactivitytimer in Withdrawal
    objBalance->stopBalanceTimer(); // in Balance
}

//Go the login page
void MainWindow::on_btnStart_clicked()
{
    ui->stackedWidget->setCurrentWidget(objLogin);
    objLogin->startLoginTimer();
}

//Go the balance page
void MainWindow::on_btnBalance_clicked()
{
    ui->stackedWidget->setCurrentWidget(objBalance);
    objBalance->startBalanceTimer();
}

//Go the withdrawal page
void MainWindow::on_btnWithdrawal_clicked()
{
    ui->stackedWidget->setCurrentWidget(objWithdrawal);
    objWithdrawal->startTimer();
}

//Go the transaction page
void MainWindow::on_btnTransactions_clicked()
{
    ui->stackedWidget->setCurrentWidget(objTransactions);
}

//Go back button
void MainWindow::on_btnBack_clicked()
{
    this->stopWidgetTimers();                     // stop inactivity timer in other widgets
    this->startMainTimer();                       // restart inactivitytimer in main menu
    ui->stackedWidget->setCurrentIndex(1);        // return to main menu
}

//Logout button --> go start page
void MainWindow::on_btnLogout_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // logout text for customer
    this->stopWidgetTimers();   // stop inactivity timer in other widgets
    mainTimer->stop();          // stop inactivitytimer in main menu

    qDebug()<<"Kirjauduttu ulos";

    // after 5 seconds, return to start screen
    QTimer::singleShot(5000, this, [this](){
        ui->stackedWidget->setCurrentIndex(0);
    });

}

void MainWindow::onButtonPressed()
{
    // stop inactivity timer in main menu
    mainTimer->stop();
}

