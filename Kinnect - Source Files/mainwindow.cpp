#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>

MainWindow::MainWindow(QWidget *parent,SocialNetworkApp *app1)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->app=app1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    login = new LoginPage(this,app);
    std::cout<<app->returnTotalUsers();
    this->close();
    login->show();
}
