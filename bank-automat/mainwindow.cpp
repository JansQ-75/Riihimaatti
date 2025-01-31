#include "creditordebit.h"
#include "environment.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <CreditOrDebit.h>
#include <CreditOrDebit.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect: when button is pressed, go to slot pressed number.
    connect(ui->btn1,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn2,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn3,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn4,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn5,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn6,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn7,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn8,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn9,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btn0,SIGNAL(clicked()), this, SLOT(pressed_number()));
    connect(ui->btnClear,SIGNAL(clicked()), this, SLOT(pressed_number()));

}

void MainWindow::pressed_number()
{
    //Empty label
    ui->labelInfo->setText(" ");

    /*
     * What button was pressed?
    */
    QPushButton *pressedButton=qobject_cast<QPushButton*>(sender());  //this makes sure it was really push button who sent the signal
    QString textFromButton=pressedButton->text();
    //if we want it to int add .toInt()


    //If button was "clear"
    if(textFromButton == "Clear"){
        if(iForLogin<6){
            cardnumberForLabel = "";
            ui->labelCardnumber->setText(cardnumberForLabel);
            iForLogin=0;
        }else if(iForLogin>5 && iForLogin<10){
            pincodeForLabel = "";
            ui->labelPincode->setText(pincodeForLabel);
            iForLogin=6;
        }
    //6 numbers for the card number
    } else if (iForLogin<6){
        cardnumberForLabel = cardnumberForLabel + textFromButton;
        //Numbers to label
        ui->labelCardnumber->setText(cardnumberForLabel);
        iForLogin++;
    //next 4 numbers for the pin
    }else if(iForLogin>5 && iForLogin<10){
        pincodeForLabel = pincodeForLabel + textFromButton;
        ui->labelPincode->setText(pincodeForLabel);
        iForLogin++;
        pincodeTries++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//----------------Main interface buttons------------------

void MainWindow::on_btnBalance_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnWithdrawal_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_btnTransactions_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


//Go back button
void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//Logout button
void MainWindow::on_btnLogout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//Start view button
void MainWindow::on_btnStart_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//Login button
void MainWindow::on_btnLogin_clicked()
{
    //Create a json obejct
    QJsonObject jsonObj;

    //Read user's input for a cardnumber and pin code
    jsonObj.insert("cardnumber", ui->labelCardnumber->text());
    jsonObj.insert("pin", ui->labelPincode->text());

    //
    //Without environment --> QString site_url="http://localhost:3000/login";
    QString site_url=Environment::base_url()+"/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply=loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    //reply's answer to response_data
    response_data=reply->readAll();

    //Server errors
    if(response_data.length()<2){
        qDebug()<<"Server error";
        //Print it to ui
        ui->labelInfo->setText("Server problems");
    //Database errors
    } else if (response_data=="Internal Server Error"){
        qDebug()<<"Database error";
        ui->labelInfo->setText("Database problems");

    } else {
        //Wrong card number or pin code
        if(response_data=="Unauthorized"||response_data=="Card number doesn't exist" ){
            //Print customer
            ui->labelInfo->setText("Wrong card number or pin code");
        //Card locked
        } else if (response_data=="Card locked."){
            ui->labelInfo->setText("Your card is locked.");
        //Login OK
        } else if (response_data.length()>30){
            ui->labelInfo->setText("Login successful");

            //Data from the database
            QJsonDocument jsonresponse=QJsonDocument::fromJson(response_data);
            if (jsonresponse.isNull() || !jsonresponse.isObject()) {
                qDebug() << "Error";
                return;
            }
            QJsonObject jsonObj = jsonresponse.object();
            QByteArray customersToken =jsonresponse["token"].toString().toUtf8();


            QString site_url=Environment::base_url()+"/card/bycardnumberstart/"+cardnumberForLabel;
            QNetworkRequest request(site_url);
            request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + customersToken));
            creditOrDebitManager = new QNetworkAccessManager(this);
            connect(creditOrDebitManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(showDebitOrCreditSlot(QNetworkReply*)));
            replyCreditOrDebit=creditOrDebitManager->get(request);

            //Go next page
            ui->stackedWidget->setCurrentIndex(2);
            //ui->labelInfo->setText("");
        }
        //empty variables and labels
        cardnumberForLabel="";
        pincodeForLabel="";
        iForLogin=0;
        ui->labelCardnumber->setText(cardnumberForLabel);
        ui->labelPincode->setText(pincodeForLabel);
    }

    //Delete later
    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::showDebitOrCreditSlot(QNetworkReply *replyCreditOrDebit)
{
    response_dataCreditOrDebit=replyCreditOrDebit->readAll();
    qDebug()<<response_dataCreditOrDebit;

    //Parse json
    QJsonDocument jsonresponse = QJsonDocument::fromJson(response_dataCreditOrDebit);
    if (jsonresponse.isNull() || !jsonresponse.isObject()) {
        qDebug() << "Error";
        return;
    }

    QJsonObject jsonObj2 = jsonresponse.object();

    idcustomer = jsonObj2["idcustomer"].toInt();
    idcard = jsonObj2["idcard"].toInt();
    type = jsonObj2["type"].toString();
    fname = jsonObj2["fname"].toString();
    lname = jsonObj2["lname"].toString();

    ui->labelHeyAndName->setText("Welcome " + fname + " " + lname);

    //Ask credit or debit if it is necessessary
    if(type=="debit/credit"){
        //
        creditOrDebit *objCreditOrDebit = new creditOrDebit(this);
        objCreditOrDebit->setCustomerName(fname + " " + lname);
        objCreditOrDebit->setCustomersToken(customersToken);
        objCreditOrDebit->open();
    }
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

    ui->stackedWidget->addWidget(objBalance);
    ui->stackedWidget->addWidget(objLogin);
    ui->stackedWidget->addWidget(objTransactions);
    ui->stackedWidget->addWidget(objWithdrawal);

    //Timer
    loginTimer = new QTimer(this);
    connect(loginTimer, SIGNAL(timeout()), this, SLOT(stopwatchForTenSeconds()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

//----------------Main interface buttons------------------

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

    replyCreditOrDebit->deleteLater();
    creditOrDebitManager->deleteLater();

}
