#include "transactions.h"
#include "ui_transactions.h"

Transactions::Transactions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Transactions)
{
    ui->setupUi(this);
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::getToken(QByteArray token)
{
    receivedToken = token; //ilman bearer
}

void Transactions::CustomerDataSlot(int idbank_account, QString bank_account_number, QString account_type, double balance, double credit_limit, int idcustomer, QString fname, QString lname, QString address, QString phone)
{

    // print customer information
    ui->labelCustomer->setText("CUSTOMER:\n" + fname + " " + lname + "\n" + address + "\n" + phone);

}
