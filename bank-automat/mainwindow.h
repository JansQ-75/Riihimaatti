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

    void onButtonPressed();             // in case of some button is pressed, stop inactivity timer

    void on_btnStart_clicked();
    void goBackSlot();
    void getTokenSlot(QByteArray customersToken);
    void getCustomerData(int);
    void getAccountData(int);
    void receivedCustomerInfo(QNetworkReply *reply);
    void receivedAccountInfo(QNetworkReply *reply);
    void getDualSelections(QString, int);
    void getDataFromLoginSlot(int idcustomer, int idcard, QString type, QString fname, QString lname, int idbankAccount);
    void timerLogoutSlot(); // inits logout after timeout

private:
    Ui::MainWindow *ui;

    Balance *objBalance;
    Login *objLogin;
    Transactions *objTransactions;
    Withdrawal *objWithdrawal;
    creditOrDebit *objcreditOrDebit;

    // timer for inactivity
    void startMainTimer();
    QTimer *mainTimer; // 30s timer, for main menu inactivity
    void stopWidgetTimers(); // to stop timers in other widgets

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
    QString picture;


signals:
    // to send Tokens to widgets
    void sendTokenToWidget(QByteArray customersToken);

    // to get Login data to widgets
    void sendLoginData(int idcustomer, QString type);
    void sendLoginDataWithdrawal(int, QString);

    // to send customer data to widgets
    void sendCustomerData(int, QString, QString, QString, QString, QString);

    // to send account data to widgets
    void sendAccountData(int, QString, QString, double, double);

    // To logout after timeout
    void logoutSignal();

};
#endif // MAINWINDOW_H
