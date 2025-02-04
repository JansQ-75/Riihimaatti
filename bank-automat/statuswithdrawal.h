#ifndef STATUSWITHDRAWAL_H
#define STATUSWITHDRAWAL_H

#include <QDialog>

namespace Ui {
class StatusWithdrawal;
}

class StatusWithdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit StatusWithdrawal(QWidget *parent = nullptr);
    ~StatusWithdrawal();

    void setAmount(int newAmount);
    void setStatusText(int);

private:
    Ui::StatusWithdrawal *ui;
    int amount;

};

#endif // STATUSWITHDRAWAL_H
