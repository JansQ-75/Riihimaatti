#ifndef BALANCE_H
#define BALANCE_H

#include "transactions.h"
#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Balance;
}

class Balance : public QWidget
{
    Q_OBJECT

public:
    explicit Balance(QWidget *parent = nullptr);
    ~Balance();
    void setDualAccountType(const QString &newDualAccountType);
    double getBalance () const;
    void setBalance (double newBalance);
    void setCardtype(const QString &newCardtype);
    void startBalanceTimer();
    void stopBalanceTimer();

private:
    Ui::Balance *ui;

//Timer
    QTimer *BalanceTimer;
    void resetBalanceTimer();

//For viewing balance
    double balance;
    QString dualAccountType;
    QString cardtype;

public slots:
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString, QString);


private slots:
    void on_BtnToTransactions_clicked();
//Timer
    void handleTimeout();
    void anyBtnPressed();

signals:
    void backMain();
    void openTransactions();
    void backStartScreen();

};

#endif // BALANCE_H
