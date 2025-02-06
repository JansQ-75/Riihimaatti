#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QWidget>
#include<QtNetwork>
#include<QNetworkAccessManager>
#include<QJsonDocument>

namespace Ui {
class Transactions;
}

class Transactions : public QWidget
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = nullptr);
    ~Transactions();

private:
    Ui::Transactions *ui;

    QByteArray receivedToken;

    //For http token
    QNetworkAccessManager *transactionManager;
    QNetworkReply *replyData;
    QByteArray response_data;

    QByteArray customersToken;
public slots:
    void getToken(QByteArray token);
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString);

private slots:
    void dbDataSlot(QNetworkReply *replyData);

signals:
    void backMain();
};

#endif // TRANSACTIONS_H
