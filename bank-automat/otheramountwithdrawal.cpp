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



    //If button was "clear"
    if(textFromButton == "Clear"){
        amountForLineEdit.clear();      //clear variable
        ui->textAmount->setText("");    //clears written amount
        return;
    } else {
        // add numbers to lineEdit
        amountForLineEdit += textFromButton;
        //Numbers to label
        ui->textAmount->setText(amountForLineEdit);
    }


}

void OtherAmountWithdrawal::pressed_OK()
{
    int amount = amountForLineEdit.toInt(); // store selected amount as integer

    // check if selected amount is divisible by ten (smallest bill is 10€) and bigger than 0
    if ((amount%10)==0 && amount > 0) {
        emit withdrawOtherAmount(amountForLineEdit);
        amountForLineEdit.clear();  //clear variable
        ui->textAmount->clear();    //clears written amount
        this->close();
    } else {
        ui->label_errorText->setText("The amount can not be\nwithdrawn from account.\n\nPlease select a new amount.\n\nRemember that the smallest\n bill in automat is 10€");
        ui->textAmount->clear();    //clears written amount
        amountForLineEdit.clear();  //clear variable
    }

}
