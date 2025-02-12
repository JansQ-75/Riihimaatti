#include "otheramountwithdrawal.h"
#include "ui_otheramountwithdrawal.h"
#include "withdrawal.h"

OtherAmountWithdrawal::OtherAmountWithdrawal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OtherAmountWithdrawal)
{
    ui->setupUi(this);

    //connect: when button is pressed, go to the pressed number slot.
    connect(ui->btn1,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn2,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn3,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn4,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn5,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn6,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn7,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn8,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn9,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btn0,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btnClear,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_number);
    connect(ui->btnOK,&QPushButton::clicked, this, &OtherAmountWithdrawal::pressed_OK);

}

OtherAmountWithdrawal::~OtherAmountWithdrawal()
{
    delete ui;
}

void OtherAmountWithdrawal::pressed_number()
{
    /*
     * What button was pressed?
    */
    QPushButton *pressedButton=qobject_cast<QPushButton*>(sender());  //this makes sure it was really push button who sent the signal
    QString textFromButton=pressedButton->text();
    //if we want it to int add .toInt()


    //If button was "clear"
    if(textFromButton == "Clear"){
        //clears written amount
        ui->textAmount->setText("");
    } else {
        // add numbers to lineEdit
        amountForLineEdit = amountForLineEdit + textFromButton;
        //Numbers to label
        ui->textAmount->setText(amountForLineEdit);
    }


}

void OtherAmountWithdrawal::pressed_OK()
{
    emit withdrawOtherAmount(amountForLineEdit);
    this->close();
}
