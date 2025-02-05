#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QWidget>

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
public slots:
    void getToken(QByteArray token);
    void CustomerDataSlot(int, QString, QString, double, double, int, QString, QString, QString, QString);

signals:
    void backMain();
};

#endif // TRANSACTIONS_H
