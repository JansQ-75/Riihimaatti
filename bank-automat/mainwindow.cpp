#include "environment.h"
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
    //Without environment --> QString site_url="http://localhost:3000/login";
    QString site_url=Environment::base_url()+"/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply=loginManager->post(request, QJsonDocument(jsonObj).toJson());

}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    //reply's answer to response_data
    response_data=reply->readAll();

    //Server errors
    if(response_data.length()<2){
        qDebug()<<"Server error";
        //Print it to ui
        ui->labelInfo->setText("Server problems");
    //Database errors
    } else if (response_data=="Internal Server Error"){
        qDebug()<<"Database error";
        //Print it to ui
        ui->labelInfo->setText("Database problems");
    //Login OK
    } else {
        if(response_data=="Unauthorized"||response_data=="Card number doesn't exist" ){
            //Print error
            qDebug()<<response_data;
            ui->labelInfo->setText("Wrong card number or pin code");
        } else if (response_data.length()>30){
            //Print token
            qDebug()<<response_data;
            ui->labelInfo->setText("Login successful");
            //Go next page
            ui->stackedWidget->setCurrentIndex(2);
        }
    }

    //Delete later
    reply->deleteLater();
    loginManager->deleteLater();
}

