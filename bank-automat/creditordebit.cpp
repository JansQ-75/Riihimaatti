#include "creditordebit.h"
#include "environment.h"
#include "mainwindow.h"
#include "ui_creditordebit.h"

creditOrDebit::creditOrDebit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditOrDebit)
{
    ui->setupUi(this);
    creditOrDebitManager = new QNetworkAccessManager(this);


}

creditOrDebit::~creditOrDebit()
{
    delete ui;
}


void creditOrDebit::on_btnDebit_clicked()
{
    btnType = "debit"; // set debit to selected type
    searchAccessRights(cardnumber, customersToken); // calling function to get the bank account type and id

}


void creditOrDebit::on_btnCredit_clicked()
{
    btnType = "credit"; // set credit to selected type
    searchAccessRights(cardnumber, customersToken); // calling function to get the bank account type and id
}

void creditOrDebit::handleResponseSlot()
{
    response_data = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    if (jsonResponse.isNull() || !jsonResponse.isArray()) {
        qDebug() << "Error: Response is not a valid JSON array";
        return;
    } else {

        QJsonArray jsonArray = jsonResponse.array();
        accounts.clear();

        for (const QJsonValue &value : jsonArray) {
            if (!value.isObject()) continue;

            QJsonObject jsonObj = value.toObject();

            int idBankAccount = jsonObj["idbank_account"].toInt();
            QString accountType = jsonObj["account_type"].toString();

            accounts.append(qMakePair(idBankAccount, accountType)); // Store both account infos
        }

        // store values to variables
        firstId = accounts[0].first;
        firstType = accounts[0].second;

        secondId = accounts[1].first;
        secondType = accounts[1].second;

        // check which account is selected type and store values to variables
        if (firstType == btnType) {
            chosenAccountType = firstType;
            chosenAccountId = firstId;
        } else if (secondType == btnType) {
            chosenAccountType = secondType;
            chosenAccountId = secondId;
        } else {
            qDebug() << "Not debit accounts available.";
        }

        // send selected values to Withdrawal
        emit selectedAccount(chosenAccountType, chosenAccountId);

        reply->deleteLater();

        // close window if all went well
        accept();

    }

}

void creditOrDebit::setCardnumber(int newCardnumber)
{
    cardnumber = newCardnumber; // store cardnumber
}

void creditOrDebit::searchAccessRights(int cardnumber, QByteArray token)
{

    // API request to find out access rights to accounts
    QString site_url=Environment::base_url()+"/bank_account/cardAccess/" + QString::number(cardnumber);
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader("Authorization", "Bearer " + token);

    // create reply
    reply = creditOrDebitManager->get(request);

    // connect to slot to handle response
    connect(creditOrDebitManager, &QNetworkAccessManager::finished, this, &creditOrDebit::handleResponseSlot);
}


void creditOrDebit::setCustomersToken(const QByteArray &newCustomersToken)
{
    customersToken = newCustomersToken; // store token
}

void creditOrDebit::setCustomerName(const QString &newCustomerName)
{
    customerName = newCustomerName; // store name
    ui->labelChooseName->setText(customerName + ", \nPlease select Debit or Credit"); // print "hello text" to window
}

