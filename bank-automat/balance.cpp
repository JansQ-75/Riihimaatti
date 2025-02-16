#include "balance.h"
#include "ui_balance.h"
#include "environment.h"
#include <QStandardItemModel>

Balance::Balance(QWidget *parent)
    : QWidget(parent)
, ui(new Ui::Balance)
{
    ui->setupUi(this);

    // timer setup
    BalanceTimer = new QTimer(this);
    connect(BalanceTimer, &QTimer::timeout, this, &Balance::handleTimeout);
}

Balance::~Balance()
{
    delete ui;
}

void Balance::startBalanceTimer()
{
    //start timer
    BalanceTimer->start(10000);
}

void Balance::stopBalanceTimer()
{
    //stop timer
    BalanceTimer->stop();
}

void Balance::resetBalanceTimer()
{
    // restart timer
    BalanceTimer->start(10000);
}

void Balance::handleTimeout()
{
    emit backStartScreen();
}

void Balance::anyBtnPressed()
{
    this->resetBalanceTimer();
}

void Balance::setDualAccountType( const QString &newDualAccountType)
{
    dualAccountType = newDualAccountType;
}

double Balance::getBalance() const
{
    return balance;
}

void Balance::setBalance(const double newBalance)
{
    balance = newBalance;
}

void Balance::setCardtype(const QString &newCardtype)
{
    cardtype = newCardtype;
}

void Balance::CustomerDataSlot(int idbank_account, QString bank_account_number, QString account_type, double balance, double credit_limit, int idcustomer, QString fname, QString lname, QString address, QString phone)
{
    QString accountType;
    ui->labelCustomer->setText("CUSTOMER:\n" + fname + " " + lname + "\n" + address + "\n" + phone);

    // conditions for setting account type
    // if (cardtype== "debit/credit") {
    //     // if dual card, use selected value
    //     accountType = dualAccountType;
    // } else {
    //     // in case of debit or credit card, use values provided by login
    //     accountType = account_type;
    // }

    // different print depending on account type (debit or credit) show balance
     if (account_type == "debit") {
            ui->labelBalance->setText("DEBIT ACCOUNT:\nBalance: " + QString::number(balance) + " €");
        } else {
            ui->labelBalance->setText("CREDIT ACCOUNT:\nAvailable balance: " + QString::number(credit_limit-balance) + " €\nCredit limit: " + QString::number(credit_limit) + " €");
        }
    }

void Balance::on_BtnToTransactions_clicked()
{
    emit openTransactions();
}

