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

private:
    Ui::Withdrawal *ui;

    StatusWithdrawal *objStatus;
    OtherAmountWithdrawal *objOtherAmount;

    //QByteArray response_data;
    QNetworkAccessManager *WithdrawalManager;
    QByteArray response_Withdrawal;

    QByteArray receivedToken;
    int customerId;
    QString accountType;
    int bankAccountId;
    int cardId;



signals:
    void backMainSignal();

private slots:
    void on_btn_20e_clicked();
    void on_btn_40e_clicked();
    void on_btn_60e_clicked();
    void on_btn_100e_clicked();
    void on_btn_otherAmount_clicked();


public slots:
    void getToken(QByteArray token); // receive token
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString);
    void LoginDataSlot(int);
    void withdrawOtherAmountSlot(QString);
};

#endif // WITHDRAWAL_H
