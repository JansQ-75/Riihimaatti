#include "statuswithdrawal.h"
#include "ui_statuswithdrawal.h"
#include <QTimer>

StatusWithdrawal::StatusWithdrawal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StatusWithdrawal)
{
    ui->setupUi(this);
}

StatusWithdrawal::~StatusWithdrawal()
{
    delete ui;
}

void StatusWithdrawal::setStatusText(QString amount)
{
    // set text for customer to see, if withdrawal was successful
    ui->label_status->setText("Withdrawal was successful\n\nHere is " + amount + " € for you");

    // timer for closing popup
    QTimer::singleShot(3000, this, &QWidget::close);

}

void StatusWithdrawal::setErrorText()
{
    ui->label_status->setText("Not enough balance\n\nWithdrawal failed");

    QTimer::singleShot(3000, this, &QWidget::close);
}

void StatusWithdrawal::setNetworkError()
{
    ui->label_status->setText("Network error occurred");

    QTimer::singleShot(3000, this, &QWidget::close);
}

void StatusWithdrawal::setAmount(const QString &newAmount)
{
    amount = newAmount;
}
