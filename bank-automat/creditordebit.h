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

private slots:
    void on_btnDebit_clicked();
    void on_btnCredit_clicked();

private:
    Ui::creditOrDebit *ui;

    QString customerName;
    QByteArray customersToken;
    QString chosen;




};

#endif // CREDITORDEBIT_H
