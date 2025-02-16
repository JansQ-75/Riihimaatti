#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "environment.h"

Withdrawal::Withdrawal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Withdrawal)
{
    ui->setupUi(this);

    // define objects
    objStatus = new StatusWithdrawal(this);
    objOtherAmount = new OtherAmountWithdrawal(this);
    inactivityTimer = new QTimer(this);
    WithdrawalManager = new QNetworkAccessManager(this);

    //connect: signal to withdraw other amount
    connect(objOtherAmount, &OtherAmountWithdrawal::withdrawOtherAmount, this, &Withdrawal::withdrawOtherAmountSlot);
    // connect signal to timeout (=returning main menu)
    connect(inactivityTimer, &QTimer::timeout, this, &Withdrawal::handleTimeout);

    // make list of push buttons
    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    //connect button' clicked() signals to slot for reseting timer if necessary
    for (QPushButton* button : buttons) {
        connect(button, &QPushButton::pressed, this, &Withdrawal::onButtonPressed);
    }
}

Withdrawal::~Withdrawal()
{
    delete ui;

    WithdrawalManager->deleteLater();

    delete objOtherAmount;
    objOtherAmount=nullptr;

    delete objStatus;
    objStatus=nullptr;

    delete inactivityTimer;
    inactivityTimer=nullptr;
}

void Withdrawal::setDualAccountType(const QString &newDualAccountType)
{
    dualAccountType = newDualAccountType; // store selected account type from dual card
}

void Withdrawal::setDualAccountId(int newDualAccountId)
{
    dualAccountId = newDualAccountId; // store selected account id from dual card
}

void Withdrawal::makeWithdrawal(QString amount)
{

    // API request
    QString site_url=Environment::base_url()+"/transactions/" + accountType + "/" + QString::number(bankAccountId) + "/" + QString::number(cardId) + "/" + amount;
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));

    // make GET request
    QNetworkReply *reply = WithdrawalManager->get(request);

    // get reply for creating conditions for showing withdrawal status to customer
    connect(reply, &QNetworkReply::finished, this, [this, reply, amount]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Network error occurred: " << reply->errorString();
            objStatus->setNetworkError();
            objStatus->exec();
            reply->deleteLater();
            return;
        }

        QByteArray response_data = reply->readAll();

        if (response_data.trimmed() == "1") {  // Trim spaces/newlines if necessary // when query is successful, it returns 1 affected row
            objStatus->setStatusText(amount);
            objStatus->exec();
        } else {
            qDebug() << "Withdrawal failed";
            objStatus->setErrorText();
            objStatus->exec();
        }
        reply->deleteLater();

    });

    emit backMainSignal(); // return to main menu
    inactivityTimer->stop(); // stop timer
}

void Withdrawal::startTimer()
{
    // Go back to main menu if customer hasn't pressed any button within 10 seconds
    inactivityTimer->start(10000); //start timer
}

void Withdrawal::stopTimer()
{
    inactivityTimer->stop();
}

void Withdrawal::getToken(QByteArray token)
{
    receivedToken = token; // store token
}

void Withdrawal::CustomerDataSlot(int idbank_account, QString bank_account_number, QString account_type, double balance, double credit_limit, int idcustomer, QString fname, QString lname, QString address, QString phone)
{

    // print customer information
    ui->label_ownerName->setText("CUSTOMER:\n" + fname + " " + lname + "\n" + address + "\n" + phone);

    // conditions for setting account type
    if (cardType == "debit/credit") {
        // in case of dual card, use values customer has selected
        accountType = dualAccountType;
        bankAccountId = dualAccountId;
    } else {
        // in case of debit or credit card, use values provided by login
        accountType = account_type;
        bankAccountId = idbank_account;
    }

    // print account info
    // different print depending on account type (debit or credit)
    if (accountType == "debit") {
    ui->label_balance->setText("DEBIT ACCOUNT:\nBalance: " + QString::number(balance) + " €");
    } else {
        ui->label_balance->setText("CREDIT ACCOUNT:\nAvailable balance: " + QString::number(credit_limit-balance) + " €\nCredit limit: " + QString::number(credit_limit) + " €");
    }


}

void Withdrawal::LoginDataSlot(int idcard, QString cardtype)
{
    // store values
    cardId = idcard;
    cardType = cardtype;
}

void Withdrawal::on_btn_20e_clicked()
{
    // Withdraw 20e
    makeWithdrawal("20");
}


void Withdrawal::on_btn_40e_clicked()
{
    // Withdraw 40e
    makeWithdrawal("40");
}


void Withdrawal::on_btn_60e_clicked()
{
    // Withdraw 60e
    makeWithdrawal("60");
}


void Withdrawal::on_btn_100e_clicked()
{
    // Withdraw 100e
    makeWithdrawal("100");
}


void Withdrawal::on_btn_otherAmount_clicked()
{
    // Open pop up for entering custom amount
    objOtherAmount->exec();
}

void Withdrawal::onButtonPressed()
{
    // stop timer
    inactivityTimer->stop();
}

void Withdrawal::handleTimeout()
{
    // Logout after inactivity for 10 seconds
    emit logOutSignal();
}

void Withdrawal::withdrawOtherAmountSlot(QString otherAmount)
{
    // withdraw custom amount entered by customer
    makeWithdrawal(otherAmount);
}

