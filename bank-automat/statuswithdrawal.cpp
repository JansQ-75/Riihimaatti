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

void StatusWithdrawal::setAmount(int newAmount)
{
    amount = newAmount;
}

void StatusWithdrawal::setStatusText(int amount)
{

    ui->label_status->setText("Withdrawal was successful\nHere is " + QString::number(amount) + " € for you");

    // timer for closing popup
    QTimer::singleShot(5000, this, &QWidget::close);

}
