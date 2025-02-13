#include "environment.h"
#include "transactions.h"
#include "ui_transactions.h"

#include <QStandardItemModel>

Transactions::Transactions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Transactions)
{
    ui->setupUi(this);
    //Transactions *objtra= new Transactions();
}


Transactions::~Transactions()
{
    delete ui;

    //Delete the list
    qDeleteAll(transactionsList);
    transactionsList.clear();

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

    //Parse json
    QJsonDocument jsonresponse = QJsonDocument::fromJson(response_data);

    //Check whether it is empty and array
    if (jsonresponse.isNull() || !jsonresponse.isArray()) {
        qDebug() << "Error";
        return;
    }

    //Array
    QJsonArray jsonArr = jsonresponse.array();

    //Get objects from array
    for(int i=0; i<jsonArr.size(); i++){
        //QJsonObject jsonObj0[i] = jsonArr01.at(i).toObject();

        transaction_date = jsonArr.at(i).toObject()["transaction_date"].toString();
        //Edit data
        QDateTime pretty_transaction_date = QDateTime::fromString(transaction_date, Qt::ISODate);
        pretty_transaction_date = pretty_transaction_date.toLocalTime();
        qDebug()<<pretty_transaction_date;

        //withdrawal = jsonArr.at(i).toObject()["withdrawal"].toDouble(); //O
        withdrawal =QString::number(jsonArr.at(i).toObject()["withdrawal"].toString().toDouble(), 'f', 2).toDouble();
        bank_account_number = jsonArr.at(i).toObject()["bank_account_number"].toString();
        cardnumber = jsonArr.at(i).toObject()["cardnumber"].toInt();

        //Create an object
        Transactions *objtransaction= new Transactions();

        //Add the data
        objtransaction->setTransaction_date(pretty_transaction_date.toString("dd.MM.yyyy hh:mm:ss"));
        objtransaction->setWithdrawal(withdrawal);
        objtransaction->setBank_account_number(bank_account_number);
        objtransaction->setCardnumber(cardnumber);

        //Add the object to the list
        transactionsList.append(std::move(objtransaction));
    }


    QStandardItemModel *table_model = new QStandardItemModel(10,4); //10 rows, 4 columns

    //Strech columns
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Set headers for a table view
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Transaction date"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Withdrawal"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Bank account"));
    table_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Card number"));


    //Add data to rows
    for (int row = 0; row < 10; ++row) {

        QStandardItem *itemtransaction_date = new QStandardItem(transactionsList[row]->getTransaction_date());
        table_model->setItem(row, 0, itemtransaction_date);

        QStandardItem *itemwithdrawal = new QStandardItem(QString::number(transactionsList[row]->getWithdrawal()));
        table_model->setItem(row, 1, itemwithdrawal);

        QStandardItem *itembank_account = new QStandardItem(transactionsList[row]->getBank_account_number());
        table_model->setItem(row, 2, itembank_account);

        QStandardItem *itemcardnumber = new QStandardItem(QString::number(transactionsList[row]->getCardnumber()));
        table_model->setItem(row, 3, itemcardnumber);
    }

    //emit addObjectsSignal(QList<Transactions>transactionsList);


    ui->tableView->setModel(table_model);

    replyData->deleteLater();
    transactionManager->deleteLater();
}

void Transactions::on_btnUp_clicked()
{
    //show newer


}


void Transactions::on_btnDown_clicked()
{
    //show older

}


/*
void Transactions::addObjectsSlot(QJsonArray jsonArr)
{
    //Add data to rows
    for (int row = 0; row < 10; ++row) {
        QStandardItem *itemtransaction_date = new QStandardItem(transactionsList[row]->getTransaction_date());
        table_model->setItem(row, 0, itemtransaction_date);

        QStandardItem *itemwithdrawal = new QStandardItem(QString::number(transactionsList[row]->getWithdrawal()));
        table_model->setItem(row, 1, itemwithdrawal);

        QStandardItem *itembank_account = new QStandardItem(transactionsList[row]->getBank_account_number());
        table_model->setItem(row, 2, itembank_account);

        QStandardItem *itemcardnumber = new QStandardItem(QString::number(transactionsList[row]->getCardnumber()));
        table_model->setItem(row, 3, itemcardnumber);
    }
}

*/
