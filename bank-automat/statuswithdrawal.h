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

    void setStatusText(QString);
    void setErrorText();
    void setNetworkError();
    void setAmount(const QString &newAmount);

private:
    Ui::StatusWithdrawal *ui;
    QString amount;

};

#endif // STATUSWITHDRAWAL_H
