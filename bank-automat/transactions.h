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

    void setDualAccountId(int newDualAccountId); // set account id once customer has selected debit or credit

    void setCardType(const QString &newCardType); // set card type for conditions regarding dual card

    void startTimer(); // timer function for inactivity
    void stopTimer(); // stop timer function

private:
    Ui::Transactions *ui;

    //timer for inactivity
    QTimer *inactivityTimer;

    QByteArray receivedToken;

    //For table model
    QStandardItemModel *table_model;
    int startingIndex = 0;
    int lastindex = 10;
    int runningIndex = 0;
    int error=0;

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

    // dual card data
    int dualAccountId;
    QString cardType;

    void updateData(int);

public slots:
    void getToken(QByteArray token);
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString);

private slots:
    void dbDataSlot(QNetworkReply *replyData);

    void on_btnUp_clicked();
    void on_btnDown_clicked();

    void onButtonPressed();             // in case of some button is pressed, stop inactivity timer
    void handleTimeout();               // if timer runs downs, return to main menu


signals:
    void backMain();
    void logoutSignal();    // for logging out after inactivity for 10s
};

#endif // TRANSACTIONS_H
