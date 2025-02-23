#include "environment.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //NetworkManager
    MainWindowManager = new QNetworkAccessManager(this);

    createObjects();

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
    //Show buttons
    ui->btnBack->setVisible(true);
    ui->btnLogout->setVisible(true);

    // API request
    QString site_url=Environment::base_url()+"/customer/" + QString::number(idcustomer);
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

void MainWindow::getAccountData(int idBankAccount)
{
    //Show buttons
    ui->btnBack->setVisible(true);
    ui->btnLogout->setVisible(true);

    // API request
    QString site_url=Environment::base_url()+"/bank_account/by-id/" + QString::number(idBankAccount);
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + token));

    // make GET request
    QNetworkReply *reply = MainWindowManager->get(request);

    // connect to slot for handling response
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        this->receivedAccountInfo(reply);
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
        if (jsonObj.contains("idcustomer")) idcustomer = jsonObj["idcustomer"].toInt();
        if (jsonObj.contains("fname")) fname = jsonObj["fname"].toString();
        if (jsonObj.contains("lname")) lname = jsonObj["lname"].toString();
        if (jsonObj.contains("address")) address = jsonObj["address"].toString();
        if (jsonObj.contains("phone")) phone = jsonObj["phone"].toString();
        if (jsonObj.contains("picture")) picture = jsonObj["picture"].toString();

        ui->labelHeyAndName->setText("Welcome " + fname + " " + lname);

        //Get a profile picture
        QNetworkAccessManager *pictureManager = new QNetworkAccessManager(this);
        connect(pictureManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *replyPicture){
            if(replyPicture->error() == QNetworkReply::NoError){
                //Read picture
                QByteArray data = replyPicture->readAll();

                QPixmap profilepicture;
                profilepicture.loadFromData(data);

                if(!profilepicture.isNull()){
                    ui->label_test->setPixmap(profilepicture.scaled(
                        ui->label_test->size(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation));
                    //ui->label_test->setScaledContents(true);
                }
            }else{
                qDebug()<<"profilepicture error";
            }
            replyPicture->deleteLater();
        });

        QString imageUrl = Environment::base_url() + "/profilepictures/" + picture;
        pictureManager->get(QNetworkRequest(QUrl(imageUrl)));

        //Signal to send customer's data to widgets
        emit sendCustomerData(idcustomer, fname, lname, address, phone, picture);

        //Delete later
        reply->deleteLater();

    } else {
        qDebug() << "Error: " << reply->errorString();
    }
}

void MainWindow::receivedAccountInfo(QNetworkReply *reply)
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

        //Signal to send customer's data to widgets
        emit sendAccountData(idbank_account, bank_account_number, account_type, balance, credit_limit);

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

    // set selected values to variables in Transaction
    objTransactions->setDualAccountId(dualAccountId);

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
        this->receivedAccountInfo(reply);
        reply->deleteLater();
    });

}

void MainWindow::getDataFromLoginSlot(int idcustomer, int idcard, QString type, QString fname, QString lname, int idbankAccount)
{
    emit sendLoginDataWithdrawal(idcard, type); // send login data to withdrawal
    objTransactions->setCardType(type); // set card type in Transaction
    objBalance->setCardtype(type); // set card type in Balance
}

void MainWindow::timerLogoutSlot()
{
    //Hide buttons
    ui->btnBack->setVisible(false);
    ui->btnLogout->setVisible(false);

    this->stopWidgetTimers();   // stop inactivity timer in other widgets

    ui->label_logout->setText("Timeout. Logging out...");
    ui->label_thankYou->setText("");
    ui->stackedWidget->setCurrentIndex(2); // show logout text for customer

    // after 5 seconds, continue with logout
    QTimer::singleShot(3000, this, [this](){
        emit logoutSignal(); // finish logout
    });

}

void MainWindow::startMainTimer()
{
    mainTimer->start(30000); //start 30s timer
}

void MainWindow::stopWidgetTimers()
{
    objLogin->stopLoginTimer();     // stop inactivitytimer in Login
    objWithdrawal->stopTimer();     // stop inactivitytimer in Withdrawal
    objTransactions->stopTimer();   // stop inactivitytimer in Transactions
    objBalance->stopBalanceTimer(); // stop inactivitytimer in Balance
}

void MainWindow::createObjects()
{
    //Create objects
    objBalance = new Balance(this);
    objLogin = new Login(this);
    objTransactions = new Transactions(this);
    objWithdrawal = new Withdrawal(this);

    // Timer
    mainTimer = new QTimer(this);

    //Hide buttons
    ui->btnBack->setVisible(false);
    ui->btnLogout->setVisible(false);

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
    connect(mainTimer, &QTimer::timeout, this, &MainWindow::timerLogoutSlot);

    //Go back -connect
    connect(objLogin,&Login::backMain, this, &MainWindow::goBackSlot);
    connect(objTransactions,&Transactions::backMain, this, &MainWindow::goBackSlot);
    connect(objWithdrawal,&Withdrawal::backMainSignal, this, &MainWindow::goBackSlot);

    // Logout connections
    connect(objWithdrawal, &Withdrawal::logOutSignal, this, &MainWindow::timerLogoutSlot);
    connect(objTransactions, &Transactions::logoutSignal, this, &MainWindow::timerLogoutSlot);
    connect(objLogin, &Login::backStartScreen, this, &MainWindow::timerLogoutSlot);
    connect(objBalance, &Balance::backStartScreen, this, &MainWindow::timerLogoutSlot);
    connect(this, &MainWindow::logoutSignal, this, &MainWindow::on_btnLogout_clicked);

    //Bring data
    connect(objLogin,&Login::sendToken, this, &MainWindow::getTokenSlot);
    connect(objLogin, &Login::RetrieveCustomerData, this, &MainWindow::getCustomerData);
    connect(objLogin, &Login::RetrieveAccountData, this, &MainWindow::getAccountData);
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

    //...account data
    connect(this, &MainWindow::sendAccountData, objWithdrawal, &Withdrawal::AccountDataSlot);
    connect(this, &MainWindow::sendAccountData, objTransactions, &Transactions::AccountDataSlot);
    connect(this, &MainWindow::sendAccountData, objBalance, &Balance::AccountDataSlot);


    // ...login data
    connect(this, &MainWindow::sendLoginDataWithdrawal, objWithdrawal, &Withdrawal::LoginDataSlot);

    // for connecting balance to transactions
    connect(objBalance, &Balance::openTransactions, this, &MainWindow::on_btnTransactions_clicked);

    //Add a logo without strching the logo
    QPixmap logo(":/images/riihimaattilogopng.png");
    ui->label_logoStart->setPixmap(logo.scaled(ui->label_logoStart->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::destroyObjects()
{
    if (objBalance) {
        disconnect(this, nullptr, objBalance, nullptr);
        disconnect(objBalance, nullptr, this, nullptr);
        delete objBalance;
        objBalance = nullptr;
    }

    if (objLogin) {
        disconnect(this, nullptr, objLogin, nullptr);
        disconnect(objLogin, nullptr, this, nullptr);
        delete objLogin;
        objLogin = nullptr;
    }

    if (objTransactions) {
        disconnect(this, nullptr, objTransactions, nullptr);
        disconnect(objTransactions, nullptr, this, nullptr);
        delete objTransactions;
        objTransactions = nullptr;
    }

    if (objWithdrawal) {
        disconnect(this, nullptr, objWithdrawal, nullptr);
        disconnect(objWithdrawal, nullptr, this, nullptr);
        delete objWithdrawal;
        objWithdrawal = nullptr;
    }

    if (mainTimer) {
        disconnect(this, nullptr, mainTimer, nullptr);
        disconnect(mainTimer, nullptr, this, nullptr);
        delete mainTimer;
        mainTimer = nullptr;
    }

    // Clear customer data

    this->token.clear();

    this->response_data.clear();


    this->idcard = 0;
    this->type = "";

    this->idbank_account = 0;
    this->bank_account_number = "";
    this->account_type = "";
    this->balance = 0;
    this->credit_limit = 0;
    this->idcustomer = 0;
    this->fname = "";
    this->lname = "";
    this->address = "";
    this->phone = "";
    this->picture = "";
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
    objTransactions->startTimer();
}

//Go back button
void MainWindow::on_btnBack_clicked()
{
    this->stopWidgetTimers();                     // stop inactivity timer in other widgets
    this->startMainTimer();                       // restart inactivity timer in main menu
    ui->stackedWidget->setCurrentIndex(1);        // return to main menu
}

//Logout button --> go start page
void MainWindow::on_btnLogout_clicked()
{
    this->stopWidgetTimers();   // stop inactivity timer in other widgets
    mainTimer->stop();          // stop inactivity timer in main menu
    ui->label_logout->setText("Logout successful");
    ui->label_thankYou->setText("Thank you for choosing Riihimaatti!");
    ui->stackedWidget->setCurrentIndex(2); // show logout text for customer

    //Hide buttons
    ui->btnBack->setVisible(false);
    ui->btnLogout->setVisible(false);

    qDebug()<<"Kirjauduttu ulos";

    // after 5 seconds, return to start screen
    QTimer::singleShot(3000, this, [this](){
        ui->stackedWidget->setCurrentIndex(0);
        destroyObjects();
        createObjects();
    });

}

void MainWindow::onButtonPressed()
{
    // stop inactivity timer in main menu
    mainTimer->stop();
}

