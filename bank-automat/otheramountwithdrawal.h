#ifndef OTHERAMOUNTWITHDRAWAL_H
#define OTHERAMOUNTWITHDRAWAL_H

#include <QDialog>

namespace Ui {
class OtherAmountWithdrawal;
}

class OtherAmountWithdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit OtherAmountWithdrawal(QWidget *parent = nullptr);
    ~OtherAmountWithdrawal();

private:
    Ui::OtherAmountWithdrawal *ui;
    QString amountForLineEdit;

private slots:
    void pressed_number();
    void pressed_OK();

signals:
    void withdrawOtherAmount(QString);
};

#endif // OTHERAMOUNTWITHDRAWAL_H
