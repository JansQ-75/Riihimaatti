#include "creditordebit.h"
#include "environment.h"
#include "ui_creditordebit.h"

creditOrDebit::creditOrDebit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditOrDebit)
{
    ui->setupUi(this);
}

creditOrDebit::~creditOrDebit()
{
    delete ui;
}


void creditOrDebit::on_btnDebit_clicked()
{
    //ota talteen käyttäjän valinta
    QString chosen ="debit";

    this->close();

}


void creditOrDebit::on_btnCredit_clicked()
{
    //ota talteen käyttäjän valinta
    QString chosen ="credit";

    this->close();
}


void creditOrDebit::setCustomersToken(const QByteArray &newCustomersToken)
{
    customersToken = newCustomersToken;
    qDebug()<<customersToken;
}

void creditOrDebit::setCustomerName(const QString &newCustomerName)
{
    customerName = newCustomerName;
    ui->labelChooseName->setText(customerName + ", \nchoose which one could you like to use");
}

