#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "environment.h"

Withdrawal::Withdrawal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Withdrawal)
{
    ui->setupUi(this);

    objStatus = new StatusWithdrawal(this);
    objOtherAmount = new OtherAmountWithdrawal(this);

    WithdrawalManager = new QNetworkAccessManager(this);

    //connect: signal to withdraw other amount
    connect(objOtherAmount, &OtherAmountWithdrawal::withdrawOtherAmount, this, &Withdrawal::withdrawOtherAmountSlot);

}

Withdrawal::~Withdrawal()
{
    delete ui;
    WithdrawalManager->deleteLater();
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
    QString type;
    int accountId;

    // conditions for setting account type and id
    if (cardType == "debit/credit") {
        // in case of dual card, use values customer has selected
        type = dualAccountType;
        accountId = dualAccountId;
    } else {
        // in case of debit or credit card, use values provided by login
        type = accountType;
        accountId = bankAccountId;
    }

    // API request
    QString site_url=Environment::base_url()+"/transactions/" + type + "/" + QString::number(accountId) + "/" + QString::number(cardId) + "/" + amount;
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));

    // make GET request
    QNetworkReply *reply = WithdrawalManager->get(request);


    qDebug()<<"responsedataa withdrawalissa"<<reply;

    qDebug()<<"tehtiin nosto "<<amount<<"e";

    // Let customer know if the withdrawal was successful
    objStatus->setStatusText(amount);
    objStatus->open();

    emit backMainSignal(); // return to main menu
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

void Withdrawal::LoginDataSlot(int idcard, QString cardtype)
{
    cardId = idcard;
    cardType = cardtype;
    qDebug()<<"Withdrawalissa saatu kortin id: " + QString::number(cardId);
}

void Withdrawal::on_btn_20e_clicked()
{
    makeWithdrawal("20");
}


void Withdrawal::on_btn_40e_clicked()
{
    makeWithdrawal("40");
}


void Withdrawal::on_btn_60e_clicked()
{
    makeWithdrawal("60");
}


void Withdrawal::on_btn_100e_clicked()
{
    makeWithdrawal("100");
}


void Withdrawal::on_btn_otherAmount_clicked()
{
    objOtherAmount->exec();
}

void Withdrawal::withdrawOtherAmountSlot(QString otherAmount)
{
    makeWithdrawal(otherAmount);
}

