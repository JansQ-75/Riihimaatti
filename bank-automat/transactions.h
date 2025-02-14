#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include<QWidget>
#include<QtNetwork>
#include<QNetworkAccessManager>
#include<QJsonDocument>
#include <QStandardItemModel>

namespace Ui {
class Transactions;
}

class Transactions : public QWidget
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = nullptr);
    ~Transactions();

    //Set and get methods
    QString getTransaction_date() const;
    void setTransaction_date(const QString &newTransaction_date);

    double getWithdrawal() const;
    void setWithdrawal(double newWithdrawal);

    QString getBank_account_number() const;
    void setBank_account_number(const QString &newBank_account_number);

    int getCardnumber() const;
    void setCardnumber(int newCardnumber);

private:
    Ui::Transactions *ui;

    QByteArray receivedToken;

    //For table model
    QStandardItemModel *table_model;
    int startingIndex = 0;
    int lastindex = 10;
    int runningIndex = 0;

    //For http
    QNetworkAccessManager *transactionManager;
    QNetworkReply *replyData;
    QByteArray response_data;

    //For object list
    QList<Transactions*> transactionsList;
    QString transaction_date;
    double withdrawal;
    QString bank_account_number;
    int cardnumber;

    void updateData(int);

public slots:
    void getToken(QByteArray token);
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString);

private slots:
    void dbDataSlot(QNetworkReply *replyData);

    void on_btnUp_clicked();
    void on_btnDown_clicked();

signals:
    void backMain();
    void addObjectsSignal(QJsonArray jsonArr);
};

#endif // TRANSACTIONS_H
