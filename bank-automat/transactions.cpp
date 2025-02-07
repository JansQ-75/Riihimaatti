#include "environment.h"
#include "transactions.h"
#include "ui_transactions.h"

#include <QStandardItemModel>

Transactions::Transactions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Transactions)
{
    ui->setupUi(this);
}

Transactions::Transactions(QString transaction_date, double withdrawal, QString bank_account_number, int cardnumber)
{
    //Set values
    this->setTransaction_date(transaction_date);
    this->setWithdrawal(withdrawal);
    this->setBank_account_number(bank_account_number);
    this->setCardnumber(cardnumber);

}

Transactions::~Transactions()
{
    delete ui;
}

QString Transactions::getTransaction_date() const
{
    return transaction_date;
}

void Transactions::setTransaction_date(const QString &newTransaction_date)
{
    transaction_date = newTransaction_date;
}

double Transactions::getWithdrawal() const
{
    return withdrawal;
}

void Transactions::setWithdrawal(double newWithdrawal)
{
    withdrawal = newWithdrawal;
}

QString Transactions::getBank_account_number() const
{
    return bank_account_number;
}

void Transactions::setBank_account_number(const QString &newBank_account_number)
{
    bank_account_number = newBank_account_number;
}

int Transactions::getCardnumber() const
{
    return cardnumber;
}

void Transactions::setCardnumber(int newCardnumber)
{
    cardnumber = newCardnumber;
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

    //Parse json
    QJsonDocument jsonresponse = QJsonDocument::fromJson(response_data);

    //Check whether it is empty and array
    if (jsonresponse.isNull() || !jsonresponse.isArray()) {
        qDebug() << "Error";
        return;
    }

    //Array
    QJsonArray jsonArr01 = jsonresponse.array();

    //Get objects from array

    QJsonObject jsonObj01 = jsonArr01.at(0).toObject();

    transaction_date = jsonObj01["transaction_date"].toString();
    withdrawal = jsonObj01["withdrawal"].toDouble(); //O
    bank_account_number = jsonObj01["bank_account_number"].toString();
    cardnumber = jsonObj01["cardnumber"].toInt();
    qDebug() << transaction_date;
    qDebug() << withdrawal;
    qDebug() << bank_account_number;
    qDebug() << cardnumber;


    Transactions objtransaction1 = Transactions(transaction_date, withdrawal, bank_account_number, cardnumber);

    QList<Transactions*> transactionsList;
    transactionsList.append(&objtransaction1);

    //Transactions objtransaction2 = Transactions(transaction_date, withdrawal, bank_account_number, cardnumber);
    //transactionsList.append(&objtransaction2);
/*
    QStandardItemModel *table_model = new QStandardItemModel(transactionsList.size(),4);

    //Strech columns
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Set headers for a table view
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Transaction date"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Withdrawal"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Bank account"));
    table_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Card number"));


    //QString transaction_date, double withdrawal, QString bank_account_number, int cardnumber
    for (int row = 0; row < transactionsList.size(); ++row) {
        QStandardItem *itemtransaction_date = new QStandardItem(transactionsList[row]->getTransaction_date());
        table_model->setItem(row, 0, itemtransaction_date);

        QStandardItem *itemwithdrawal = new QStandardItem(QString::number(transactionsList[row]->getWithdrawal()));
        table_model->setItem(row, 1, itemwithdrawal);

        QStandardItem *itembank_account = new QStandardItem(transactionsList[row]->getBank_account_number());
        table_model->setItem(row, 2, itembank_account);

        QStandardItem *itemcardnumber = new QStandardItem(QString::number(transactionsList[row]->getCardnumber()));
        table_model->setItem(row, 3, itemcardnumber);


    }


    ui->tableView->setModel(table_model);
*/
    replyData->deleteLater();
    transactionManager->deleteLater();
}
