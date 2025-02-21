#ifndef CREDITORDEBIT_H
#define CREDITORDEBIT_H

#include "withdrawal.h"

#include <QDialog>

//For http
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class creditOrDebit;
}

class creditOrDebit : public QDialog
{
    Q_OBJECT

public:
    explicit creditOrDebit(QWidget *parent = nullptr);
    ~creditOrDebit();

    void setCustomerName(const QString &newCustomerName); // setter for customer's name
    void setCustomersToken(const QByteArray &newCustomersToken);
    void setCardnumber(int newCardnumber);
    void searchAccessRights(int, QByteArray);

    //TIMER
    void startTimer(); // timer function for inactivity
    void stopTimer(); // stop timer function

private slots:
    void on_btnDebit_clicked();
    void on_btnCredit_clicked();
    void handleResponseSlot();
    void onButtonPressed();             // in case of some button is pressed, stop inactivity timer
    void handleTimeout();               // if timer runs downs, return to main menu


private:
    Ui::creditOrDebit *ui;

    //timer for inactivity
    QTimer *creditOrDebitTimer;

    QString customerName;
    QByteArray customersToken;
    int cardnumber;
    QString chosen;

    //For http
    QNetworkAccessManager *creditOrDebitManager;
    QNetworkReply *reply;
    QByteArray response_data;

    // to store account info
    QVector<QPair<int, QString>> accounts;
    int firstId;
    QString firstType;
    int secondId;
    QString secondType;

    // valitut tilit
    QString chosenAccountType;
    int chosenAccountId;
    QString btnType;


signals:
    void selectedAccount(QString, int);
    void logoutSignal();
};

#endif // CREDITORDEBIT_H
