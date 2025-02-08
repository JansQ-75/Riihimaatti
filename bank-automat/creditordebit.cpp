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
    searchAccessRights(cardnumber, customersToken);
    qDebug()<<"napissa tiedot: "<<chosenDebitId<<chosenDebitType;

}


void creditOrDebit::on_btnCredit_clicked()
{
    this->close();
}

void creditOrDebit::handleResponseSlot()
{
    response_data = reply->readAll();
    qDebug() << "Raw API Response:" << response_data;
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

            accounts.append(qMakePair(idBankAccount, accountType)); // Store both

            qDebug() << "Stored Account - ID:" << idBankAccount << ", Type:" << accountType;
        }
        qDebug()<<"tallennetut vektorit"<<accounts;
        firstId = accounts[0].first;
        firstType = accounts[0].second;

        secondId = accounts[1].first;
        secondType = accounts[1].second;

        if (firstType == "debit") {
            chosenDebitType = firstType;
            chosenDebitId = firstId;
        } else if (secondType == "debit") {
            chosenDebitType = secondType;
            chosenDebitId = secondId;
        } else if (firstType == "credit") {
            chosenCreditType = firstType;
            chosenCreditId = firstId;
        } else if (secondType == "credit") {
            chosenCreditType = secondType;
            chosenCreditId = secondId;
        } else {
            qDebug() << "Not debit accounts available.";
        }

        qDebug()<<"Debitiin valitut muuttujat: "<<chosenDebitType<<" ja "<<chosenDebitId;

        this->close();

        reply->deleteLater();

    }

}

void creditOrDebit::setCardnumber(int newCardnumber)
{
    cardnumber = newCardnumber;
    qDebug()<<"kortinnumero CorD: "<<cardnumber;
}

void creditOrDebit::searchAccessRights(int cardnumber, QByteArray token)
{
    qDebug()<<"funktiossa kortti: "<<cardnumber;
    qDebug()<<"funktiossa token: "<<token;

    // API request
    QString site_url=Environment::base_url()+"/bank_account/cardAccess/" + QString::number(cardnumber);
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader("Authorization", "Bearer " + token);

    qDebug() << "Authorization Header: " << "Bearer " + token;

    // create reply
    reply = creditOrDebitManager->get(request); // line 99

    connect(creditOrDebitManager, &QNetworkAccessManager::finished, this, &creditOrDebit::handleResponseSlot);
}


void creditOrDebit::setCustomersToken(const QByteArray &newCustomersToken)
{
    customersToken = newCustomersToken;
    qDebug()<<"CorD token: "<<customersToken;
}

void creditOrDebit::setCustomerName(const QString &newCustomerName)
{
    customerName = newCustomerName;
    ui->labelChooseName->setText(customerName + ", \nchoose which one could you like to use");
}

