#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "balance.h"
#include "login.h"
#include "transactions.h"
#include "withdrawal.h"
#include "creditordebit.h"

#include <QMainWindow>
#include <QTimer>

//For http
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnBalance_clicked();
    void on_btnTransactions_clicked();
    void on_btnWithdrawal_clicked();
    void on_btnBack_clicked();
    void on_btnLogout_clicked();

    void stopwatchForTenSeconds();

    void on_btnStart_clicked();
    void goBackSlot();
    void getDataFromLoginSlot(int idcustomer, int idcard, QString type, QString fname, QString lname);
    void getTokenSlot(QByteArray customersToken);

private:
    Ui::MainWindow *ui;

    Balance *objBalance;
    Login *objLogin;
    Transactions *objTransactions;
    Withdrawal *objWithdrawal;
    creditOrDebit *objcreditOrDebit;

    QTimer *loginTimer;

    //For customer
    int idcustomer;
    int idcard;
    QString type;
    QString fname;
    QString lname;

signals:
    // to send Tokens to widgets
    void sendTokenToWithdrawal(QByteArray customersToken);

    // to get data to widgets
    void sendLoginData(int idcustomer, QString type);

};
#endif // MAINWINDOW_H
