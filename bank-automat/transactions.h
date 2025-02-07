#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QWidget>
#include<QtNetwork>
#include<QNetworkAccessManager>
#include<QJsonDocument>

namespace Ui {
class Transactions;
}

class Transactions : public QWidget
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = nullptr);
    //Transactions(QString transaction_date, double withdrawal, QString bank_account_number, int cardnumber);
    //Transactions();
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

    //For http token
    QNetworkAccessManager *transactionManager;
    QNetworkReply *replyData;
    QByteArray response_data;

    //For object list
    int i;
QList<Transactions*> transactionsList;
    QString transaction_date;
    double withdrawal;
    QString bank_account_number;
    int cardnumber;

public slots:
    void getToken(QByteArray token);
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString);

private slots:
    void dbDataSlot(QNetworkReply *replyData);

signals:
    void backMain();
};

#endif // TRANSACTIONS_H
