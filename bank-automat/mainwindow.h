#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//For http
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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

    void on_btnStart_clicked();

    void loginSlot(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    //For http
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

};
#endif // MAINWINDOW_H
