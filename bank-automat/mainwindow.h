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
    void getCustomerData(int idcustomer);
    void receivedCustomerInfo(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    Balance *objBalance;
    Login *objLogin;
    Transactions *objTransactions;
    Withdrawal *objWithdrawal;
    // creditOrDebit *objcreditOrDebit;

    QTimer *loginTimer;

    // store token
    QByteArray token;

    //HTTP
    QByteArray response_data;
    QNetworkAccessManager *MainWindowManager;

    //card info
    int idcard;
    QString type;

    //Customer info
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

signals:
    // to send Tokens to widgets
    void sendTokenToWidget(QByteArray customersToken);

    // to get Login data to widgets
    void sendLoginData(int idcustomer, QString type);
    void sendLoginDataWithdrawal(int);

    // to send customer data to widgets
    void sendCustomerData(int, QString, QString, double, double, int, QString, QString, QString, QString);

};
#endif // MAINWINDOW_H
