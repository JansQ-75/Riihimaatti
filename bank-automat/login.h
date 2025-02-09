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
    int pincodeTries =0;
    bool pincodeLocked=false;


    QTimer *loginTimer;

    //For http token
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QByteArray token;

    //For http credit or debit
    QNetworkAccessManager *creditOrDebitManager;
    QNetworkReply *replyCreditOrDebit;
    QByteArray response_dataCreditOrDebit;

    //For customer
    int idcustomer;
    int idcard;
    int cardnumber;
    QString type;
    QString fname;
    QString lname;

private slots:
    void pressed_number();
    void pressed_login();

    void loginSlot(QNetworkReply *reply);
    void showDebitOrCreditSlot(QNetworkReply *replyCreditOrDebit);

public slots:
    void getDualCardInfo(QString dualAccountType, int dualAccountId);

signals:
    void backMain();
    void sendDataToMain(int idcustomer, int idcard, QString type, QString fname, QString lname);
    void sendToken(QByteArray customersToken);
    void RetrieveCustomerData(int idcustomer);
    void sendDualInfoToMain(QString, int);
};

#endif // LOGIN_H
