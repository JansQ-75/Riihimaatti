#include "creditordebit.h"
#include "environment.h"
#include "mainwindow.h"
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
    chosen ="debit";
    this->close();

}


void creditOrDebit::on_btnCredit_clicked()
{
    //ota talteen käyttäjän valinta
    chosen ="credit";

    qDebug()<<chosen;


    this->close();
}


void creditOrDebit::setCustomersToken(const QByteArray &newCustomersToken)
{
    customersToken = newCustomersToken;
}

void creditOrDebit::setCustomerName(const QString &newCustomerName)
{
    customerName = newCustomerName;
    ui->labelChooseName->setText(customerName + ", \nchoose which one could you like to use");
}

