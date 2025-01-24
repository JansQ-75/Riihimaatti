#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//----------------Main interface buttons------------------

void MainWindow::on_btnBalance_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btnWithdrawal_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnTransactions_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//Login button
void MainWindow::on_btnLogin_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


//Go back button
void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//Logout button
void MainWindow::on_btnLogout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}