#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "environment.h"

Withdrawal::Withdrawal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Withdrawal)
{
    ui->setupUi(this);

    objStatus = new StatusWithdrawal(this);

    WithdrawalManager = new QNetworkAccessManager(this);
}

Withdrawal::~Withdrawal()
{
    delete ui;
    WithdrawalManager->deleteLater();
}

void Withdrawal::getToken(QByteArray token)
{
    receivedToken = token;
    qDebug() << "Token received in Withdrawal: " <<token;
}

void Withdrawal::CustomerDataSlot(int idbank_account, QString bank_account_number, QString account_type, double balance, double credit_limit, int idcustomer, QString fname, QString lname, QString address, QString phone)
{

    // print customer information
    ui->label_ownerName->setText("CUSTOMER:\n" + fname + " " + lname + "\n" + address + "\n" + phone);

    // print account info
    accountType = account_type;
    qDebug() << "account type: " + accountType;

    // different print depending on type (debit or credit)
    // tää pitää ehkä siirtää toiseen slottiin mihin tulee creditOrdebitistä tieto myös
    if (accountType == "debit") {
    ui->label_balance->setText("ACCOUNT:\n" + bank_account_number + "\nBalance: " + QString::number(balance) + " €");
    } else {
        ui->label_balance->setText("ACCOUNT:\n" + bank_account_number + "\nAvailable balance: " + QString::number(credit_limit-balance) + " €\nCredit limit: " + QString::number(credit_limit) + " €");
    }

    // set id for bank account
    bankAccountId = idbank_account;
}

void Withdrawal::LoginDataSlot(int idcard)
{
    cardId = idcard;
    qDebug()<<"Withdrawalissa saatu kortin id: " + QString::number(cardId);
}

void Withdrawal::on_btn_20e_clicked()
{

    // API request
    QString site_url=Environment::base_url()+"/transactions/" + accountType + "/" + QString::number(bankAccountId) + "/" + QString::number(cardId) + "/20";
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));

    // make GET request
    QNetworkReply *reply = WithdrawalManager->get(request);
    qDebug()<<"tehtiin nosto 20e"<<reply;

    //reply->deleteLater();

    objStatus->setStatusText(20);
    objStatus->open();

    emit backMainSignal();
}


void Withdrawal::on_btn_40e_clicked()
{
    // API request
    QString site_url=Environment::base_url()+"/transactions/" + accountType + "/" + QString::number(bankAccountId) + "/" + QString::number(cardId) + "/40";
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));

    // make GET request
    QNetworkReply *reply = WithdrawalManager->get(request);
    qDebug()<<"tehtiin nosto 40e"<<reply;

    //reply->deleteLater();

    objStatus->setStatusText(40);
    objStatus->open();

    emit backMainSignal();
}


void Withdrawal::on_btn_60e_clicked()
{
    // API request
    QString site_url=Environment::base_url()+"/transactions/" + accountType + "/" + QString::number(bankAccountId) + "/" + QString::number(cardId) + "/60";
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));

    // make GET request
    QNetworkReply *reply = WithdrawalManager->get(request);
    qDebug()<<"tehtiin nosto 60e"<<reply;

    //reply->deleteLater();

    objStatus->setStatusText(60);
    objStatus->open();

    emit backMainSignal();
}


void Withdrawal::on_btn_100e_clicked()
{
    // API request
    QString site_url=Environment::base_url()+"/transactions/" + accountType + "/" + QString::number(bankAccountId) + "/" + QString::number(cardId) + "/100";
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));

    // make GET request
    QNetworkReply *reply = WithdrawalManager->get(request);
    qDebug()<<"tehtiin nosto 100e";

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        QByteArray response_data = reply->readAll();
        qDebug() << "API ResponseDataJaninaaaa: " << response_data;

        if (response_data == "1") {
            objStatus->setStatusText(100);
            objStatus->exec();
        } else {
            qDebug() << "Withdrawal failed";
            objStatus->setErrorText();
            objStatus->exec();
        }

        reply->deleteLater(); // Clean up reply
    });



    //reply->deleteLater();

    emit backMainSignal();
}


void Withdrawal::on_btn_otherAmount_clicked()
{    
    emit backMainSignal();
}

