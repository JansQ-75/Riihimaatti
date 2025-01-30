#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "creditordebit.h"

#include "login.h"

#include <QMainWindow>

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
    void on_btnLogin_clicked();

    void on_btnBalance_clicked();

    void on_btnTransactions_clicked();

    void on_btnWithdrawal_clicked();

    void on_btnBack_clicked();

    void on_btnLogout_clicked();

    void on_btnStart_clicked();

    void loginSlot(QNetworkReply *reply);

    void pressed_number();

    void showDebitOrCreditSlot(QNetworkReply *replyCreditOrDebit);

private:
    Ui::MainWindow *ui;

    //For http token
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QString cardnumberForLabel;
    QString pincodeForLabel;
    int iForLogin =0;
    int pincodeTries =0;
    bool pincodeLocked=false;

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

};
#endif // MAINWINDOW_H
