#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QWidget>

namespace Ui {
class Withdrawal;
}

class Withdrawal : public QWidget
{
    Q_OBJECT

public:
    explicit Withdrawal(QWidget *parent = nullptr);
    ~Withdrawal();

private:
    Ui::Withdrawal *ui;
};

#endif // WITHDRAWAL_H
