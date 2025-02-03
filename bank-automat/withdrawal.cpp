#include "withdrawal.h"
#include "ui_withdrawal.h"

Withdrawal::Withdrawal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Withdrawal)
{
    ui->setupUi(this);
}

Withdrawal::~Withdrawal()
{
    delete ui;
}
