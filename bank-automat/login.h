#ifndef LOGIN_H
#define LOGIN_H

#include "creditordebit.h"


#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;

    creditOrDebit *objCreditOrDebit;

    QString cardnumberForLabel;
    QString pincodeForLabel;
    int iForLogin =0;


    QTimer *loginTimer;

    //For http token
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QByteArray customersToken;

    //For http credit or debit
    QNetworkAccessManager *creditOrDebitManager;
    QNetworkReply *replyCreditOrDebit;
    QByteArray response_dataCreditOrDebit;

    //For customer
    int idcustomer;
    int idcard;
    QString type;
    QString fname;
    QString lname;

private slots:
    void pressed_number();
    void pressed_login();

    void loginSlot(QNetworkReply *reply);
    void showDebitOrCreditSlot(QNetworkReply *replyCreditOrDebit);

signals:
    void backMain();
    void sendToken(QByteArray customersToken);
    void RetrieveCustomerData(int idcustomer);
};

#endif // LOGIN_H
