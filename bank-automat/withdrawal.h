#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

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

    QNetworkReply *reply;
    QByteArray response_data;
    QNetworkAccessManager *WithdrawalManager;
    QByteArray response_Withdrawal;

    QByteArray receivedToken;
    int customerId;
    QString accountType;

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
    void backMainSignal();

private slots:
    void handleNetworkReply();
    void on_btn_20e_clicked();
    void on_btn_40e_clicked();
    void on_btn_60e_clicked();
    void on_btn_100e_clicked();
    void on_btn_otherAmount_clicked();

public slots:
    void getToken(QByteArray token); // receive token
    void getCustomer(int idcustomer, QString type);
};

#endif // WITHDRAWAL_H
