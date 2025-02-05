#include "environment.h"
#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    //connect: when button is pressed, go to the pressed number slot.
    connect(ui->btn1,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn2,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn3,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn4,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn5,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn6,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn7,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn8,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn9,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btn0,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btnClear,&QPushButton::clicked, this, &Login::pressed_number);
    connect(ui->btnLogin,&QPushButton::clicked, this, &Login::pressed_login);
}

Login::~Login()
{
    delete ui;
}



void Login::pressed_number()
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

        /*
        if(){
            loginTimer->stop();

        }
       */
    }
}

void Login::pressed_login()
{
    //Create a json obejct
    QJsonObject jsonObj;

    //Read user's input for a cardnumber and pin code
    jsonObj.insert("cardnumber", ui->labelCardnumber->text());
    jsonObj.insert("pin", ui->labelPincode->text());

    //Without environment --> QString site_url="http://localhost:3000/login";
    QString site_url=Environment::base_url()+"/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply=loginManager->post(request, QJsonDocument(jsonObj).toJson());
}


void Login::loginSlot(QNetworkReply *reply)
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

            // send Token to other widgets
            emit sendToken(customersToken);

            //Go next page
            emit backMain();

            ui->labelInfo->setText("");
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

void Login::showDebitOrCreditSlot(QNetworkReply *replyCreditOrDebit)
{
    response_dataCreditOrDebit=replyCreditOrDebit->readAll();
    //qDebug()<<response_dataCreditOrDebit;

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

    //Ask credit or debit if it is necessessary
    if(type=="debit/credit"){
        //
        creditOrDebit *objCreditOrDebit = new creditOrDebit(this);
        objCreditOrDebit->setCustomerName(fname + " " + lname);
        objCreditOrDebit->setCustomersToken(customersToken);
        objCreditOrDebit->open();
    }

    //Data to mainwindow
    emit RetrieveCustomerData(idcustomer);

    //Delete later
    replyCreditOrDebit->deleteLater();
    creditOrDebitManager->deleteLater();
}
