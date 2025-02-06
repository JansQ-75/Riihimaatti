#include "environment.h"
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
    //Customer data to label
    ui->labelCustomer->setText("CUSTOMER:\n" + fname + " " + lname + "\n" + address + "\n" + phone);

    //GET TRANSACTION DATA
    QString site_url=Environment::base_url()+"/transactions/" + QString::number(idbank_account);
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer " + receivedToken));
    transactionManager = new QNetworkAccessManager(this);
    connect(transactionManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(dbDataSlot(QNetworkReply*)));
    replyData=transactionManager->get(request);

}

void Transactions::dbDataSlot(QNetworkReply *replyData)
{
    response_data=replyData->readAll();
    qDebug()<<response_data;

    replyData->deleteLater();
    transactionManager->deleteLater();

}
