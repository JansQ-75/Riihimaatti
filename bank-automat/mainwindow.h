#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLogin_clicked();

    void on_btnBalance_clicked();

    void on_btnTransactions_clicked();

    void on_btnWithdrawal_clicked();

    void on_btnBack_clicked();

    void on_btnLogout_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
