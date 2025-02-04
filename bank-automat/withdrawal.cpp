#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "environment.h"

Withdrawal::Withdrawal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Withdrawal)
{
    ui->setupUi(this);
    WithdrawalManager = new QNetworkAccessManager(this);
}

Withdrawal::~Withdrawal()
{
    delete ui;
}


void Withdrawal::handleNetworkReply()
{
    qDebug() << "handlataan";

    QByteArray response_data = reply->readAll();
    QJsonDocument jsonresponse = QJsonDocument::fromJson(response_data);

    if (jsonresponse.isNull() || !jsonresponse.isObject()) {
        qDebug() << "Error: Invalid JSON response";
        reply->deleteLater();
        return;
    }

    QJsonObject jsonObj = jsonresponse.object();

    // Safely extract data
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

    // print customer information
    ui->label_ownerName->setText("CUSTOMER:\n" + fname + " " + lname + "\n" + address + "\n" + phone);

    // print account info
    accountType = account_type;
    qDebug() << "account type: " + accountType;

    // account type is debit
    if (accountType == "debit") {
    ui->label_balance->setText("ACCOUNT:\n" + bank_account_number + "\nBalance: " + QString::number(balance) + " €");
    } else {
        ui->label_balance->setText("ACCOUNT:\n" + bank_account_number + "\nAvailable balance: " + QString::number(credit_limit-balance) + " €\nCredit limit: " + QString::number(credit_limit) + " €");
    }

    // delete later
    reply->deleteLater();
    WithdrawalManager->deleteLater();
}


void Withdrawal::getToken(QByteArray token)
{
    receivedToken = token;
    qDebug() << "Token received in Withdrawal: " <<token;
}

void Withdrawal::getCustomer(int idcustomer, QString type)
{

    customerId = idcustomer;
    qDebug() << "Customers id: " <<customerId;


    // API request
    QString site_url=Environment::base_url()+"/bank_account/by-customerId/" + QString::number(customerId);
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));

    // make GET request
    reply = WithdrawalManager->get(request);

    // connect to slot for handling response
    connect(reply, &QNetworkReply::finished, this, &Withdrawal::handleNetworkReply);

}

void Withdrawal::on_btn_20e_clicked()
{

    emit backMainSignal();
}


void Withdrawal::on_btn_40e_clicked()
{
    emit backMainSignal();
}


void Withdrawal::on_btn_60e_clicked()
{
    emit backMainSignal();
}


void Withdrawal::on_btn_100e_clicked()
{
    emit backMainSignal();
}


void Withdrawal::on_btn_otherAmount_clicked()
{
    emit backMainSignal();
}

