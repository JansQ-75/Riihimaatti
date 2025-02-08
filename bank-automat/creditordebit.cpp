#include "creditordebit.h"
#include "environment.h"
#include "mainwindow.h"
#include "ui_creditordebit.h"

creditOrDebit::creditOrDebit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditOrDebit)
{
    ui->setupUi(this);


}

creditOrDebit::~creditOrDebit()
{
    delete ui;
}


void creditOrDebit::on_btnDebit_clicked()
{
    //ota talteen käyttäjän valinta
    chosen ="debit";
    this->close();

}


void creditOrDebit::on_btnCredit_clicked()
{
    this->close();
}

void creditOrDebit::handleResponseSlot()
{
    // QByteArray response_data = reply->readAll();
    // QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    // if (jsonResponse.isNull() || !jsonResponse.isArray()) {
    //     qDebug() << "Error: Response is not a valid JSON array";
    //     return;
    // } else {

    //     QJsonArray jsonArray = jsonResponse.array();
    //     accounts.clear();

    //     for (const QJsonValue &value : jsonArray) {
    //         if (!value.isObject()) continue;

    //         QJsonObject jsonObj = value.toObject();

    //         int idBankAccount = jsonObj["idbank_account"].toInt();
    //         QString accountType = jsonObj["account_type"].toString();

    //         accounts.append(qMakePair(idBankAccount, accountType)); // Store both

    //         qDebug() << "Stored Account - ID:" << idBankAccount << ", Type:" << accountType;
    //     }
    //     qDebug()<<"tallennetut vektorit"<<accounts;
    //     firstId = accounts[0].first;
    //     firstType = accounts[0].second;

    //     secondId = accounts[1].first;
    //     secondType = accounts[1].second;
    //     reply->deleteLater();
    //     //emit sendVariables(firstId, firstType, secondId, secondType);??
    // }

}

void creditOrDebit::setCardnumber(int newCardnumber)
{
    cardnumber = newCardnumber;
    qDebug()<<"kortinnumero CorD: "<<cardnumber;
}

void creditOrDebit::searchAccessRights(int cardnumber)
{
    // API request
    QString site_url=Environment::base_url()+"/bank_account/cardAccess/" + QString::number(cardnumber);
    QNetworkRequest request(site_url);

    // Authorization header
    request.setRawHeader(QByteArray("Authorization:"), QByteArray("Bearer " + customersToken));

    qDebug() << "Authorization Header: " << "Bearer " + customersToken;

    // create reply
    reply = creditOrDebitManager->get(request);

    //connect(CreditOrDebitManager, SIGNAL(finished(reply)), this, SLOT(handleResponseSlot(reply)));
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

