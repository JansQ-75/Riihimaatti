#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "environment.h"

Withdrawal::Withdrawal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Withdrawal)
{
    ui->setupUi(this);
    //WithdrawalManager = new QNetworkAccessManager(this);
}

Withdrawal::~Withdrawal()
{
    delete ui;
}

void Withdrawal::getToken(QByteArray token)
{
    receivedToken = token;
}

void Withdrawal::CustomerDataSlot(int idbank_account, QString bank_account_number, QString account_type, double balance, double credit_limit, int idcustomer, QString fname, QString lname, QString address, QString phone)
{

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

