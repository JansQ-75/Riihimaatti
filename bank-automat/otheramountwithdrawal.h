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

    //TIMER
    void startTimer(); // timer function for inactivity
    void stopTimer(); // stop timer function

private:
    Ui::OtherAmountWithdrawal *ui;
    QString amountForLineEdit;

    //timer for inactivity
    QTimer *OtherAmountTimer;

private slots:
    void pressed_number();
    void pressed_OK();
    void onButtonPressed();             // in case of some button is pressed, stop inactivity timer
    void handleTimeout();               // if timer runs downs, return to main menu


signals:
    void withdrawOtherAmount(QString);
    void logoutSignal();
};

#endif // OTHERAMOUNTWITHDRAWAL_H
