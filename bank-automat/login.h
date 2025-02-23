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
    void startLoginTimer();
    void stopLoginTimer();

private:
    Ui::Login *ui;

    creditOrDebit *objCreditOrDebit;

    QString cardnumberForLabel;
    QString pincodeForLabel;
    int iForLogin =0;

    // TIMER
    QTimer *loginTimer;
    void resetLoginTimer();

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
    int idbankAccount;

private slots:
    void pressed_number();
    void pressed_login();

    // Timer functions
    void onAnyButtonPressed();  // in case of some button is pressed, stop inactivity timer
    void handleTimeout();       // if timer runs downs, return to main menu


    void loginSlot(QNetworkReply *reply);
    void showDebitOrCreditSlot(QNetworkReply *replyCreditOrDebit);

public slots:
    void getDualCardInfo(QString dualAccountType, int dualAccountId);

signals:
    void backMain();
    void backStartScreen();
    void sendToken(QByteArray customersToken);
    void RetrieveCustomerData(int);
    void RetrieveAccountData(int);
    void sendDualInfoToMain(QString, int);
    void sendDataToMain(int idcustomer, int idcard, QString type, QString fname, QString lname, int idbankAccount);
};

#endif // LOGIN_H
