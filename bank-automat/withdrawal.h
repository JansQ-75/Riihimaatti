#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include "otheramountwithdrawal.h"
#include "statuswithdrawal.h"

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

    // setters for account type and id
    void setDualAccountType(const QString &newDualAccountType);
    void setDualAccountId(int newDualAccountId);

    void makeWithdrawal(QString); // function for making withdrawal

    void startTimer(); // timer function for inactivity
    void stopTimer(); // stop timer function

private:
    Ui::Withdrawal *ui;

    //timer for inactivity
    QTimer *inactivityTimer;

    // Defining objects
    StatusWithdrawal *objStatus;
    OtherAmountWithdrawal *objOtherAmount;


    QNetworkAccessManager *WithdrawalManager;   // NetworkAccess Manager
    QByteArray response_Withdrawal;             //variable for response data

    QByteArray receivedToken;   // for storing token
    int customerId;             // for storing customer id
    QString accountType;        // for storing account type
    int bankAccountId;          // for storing bank account id
    int cardId;                 // for storing card id
    QString cardType;           // for storing card type

    //dual card info
    QString dualAccountType;    // for storing account type
    int dualAccountId;          // for storing account id



signals:
    void backMainSignal();  // for returning main menu
    void logOutSignal();    // for logging out after inactivity for 10s

private slots:
    void on_btn_20e_clicked();          // withdraw 20e
    void on_btn_40e_clicked();          // withdraw 40e
    void on_btn_60e_clicked();          // withdraw 60e
    void on_btn_100e_clicked();         // withdraw 100e
    void on_btn_otherAmount_clicked();  // withdraw custom amount
    void onButtonPressed();             // in case of some button is pressed, stop inactivity timer
    void handleTimeout();               // if timer runs downs, return to main menu


public slots:
    void getToken(QByteArray token); // receive token
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString);
    void LoginDataSlot(int, QString);
    void withdrawOtherAmountSlot(QString);
};

#endif // WITHDRAWAL_H
