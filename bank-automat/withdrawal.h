#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QWidget>

//For http
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Withdrawal;
}

class Withdrawal : public QWidget
{
    Q_OBJECT

public:
    explicit Withdrawal(QWidget *parent = nullptr);
    ~Withdrawal();

private:
    Ui::Withdrawal *ui;

    QNetworkReply *reply;
    QByteArray response_data;
    QNetworkAccessManager *WithdrawalManager;
    QByteArray response_Withdrawal;

    QByteArray receivedToken;
    int customerId;

    int idbank_account;
    QString bank_account_number;
    QString account_type;
    double balance;
    double credit_limit;
    int idcustomer;
    QString fname;
    QString lname;
    QString address;
    QString phone;


    void getBalance();

private slots:
    void handleNetworkReply();

public slots:
    void getToken(QByteArray token); // receive token
    void getName(int idcustomer, QString fname, QString lname); // receive name for Hello-text
};

#endif // WITHDRAWAL_H
