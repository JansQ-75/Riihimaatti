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
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btnWithdrawal_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_btnTransactions_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


//Go back button
void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//Logout button
void MainWindow::on_btnLogout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//Start view button
void MainWindow::on_btnStart_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//Login button
void MainWindow::on_btnLogin_clicked()
{
    //Create a json obejct
    QJsonObject jsonObj;

    //Read user's input for a cardnumber and pin code
    jsonObj.insert("cardnumber", ui->textCardnumber->text());
    jsonObj.insert("pin", ui->textPincode->text());

    //
    QString site_url="http://localhost:3000/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply=loginManager->post(request, QJsonDocument(jsonObj).toJson());

    //ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    //reply's answer to response_data
    response_data=reply->readAll();
    
    //Print token
    qDebug()<<response_data;

    //Delete later
    reply->deleteLater();
    loginManager->deleteLater();
}

