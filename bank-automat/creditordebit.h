#ifndef CREDITORDEBIT_H
#define CREDITORDEBIT_H

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

    void setCustomerName(const QString &newCustomerName);
    void setCustomersToken(const QByteArray &newCustomersToken);
    void setCardnumber(int newCardnumber);
    void searchAccessRights(int, QByteArray);

private slots:
    void on_btnDebit_clicked();
    void on_btnCredit_clicked();
    void handleResponseSlot();

private:
    Ui::creditOrDebit *ui;

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
    QString chosenDebitType;
    int chosenDebitId;
    QString chosenCreditType;
    int chosenCreditId;
};

#endif // CREDITORDEBIT_H
