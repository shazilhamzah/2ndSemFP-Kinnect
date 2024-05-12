#include "loginpage.h"
#include "ui_loginpage.h"
#include "myClasses.h"
#include<iostream>
#include "usernameerror.h"
#include"homepage.h"
#include<string>
using namespace std;

LoginPage::LoginPage(QWidget *parent,SocialNetworkApp *app1)
    : QDialog(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    this->app = app1;
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_viewUsers_clicked()
{
    users = new AvailableUsers(this,nullptr,false);
    users->show();
}

// void LoginPage::on_loginButton_clicked()
// {
//     string s = ui->username->text().toStdString();
//     cout<<s<<endl;
//     bool set = app->setCurrentUser(s);
//     if(set){
//         cout<<"Set successful!!!";
//     }
//     else{
//         QMessageBox msgBox;
//         msgBox.setIcon(QMessageBox::Warning);
//         msgBox.setWindowTitle(tr("Invalid Username"));
//         msgBox.setText(tr("The username you have entered is incorrect. Please check if your username is valid!"));
//         msgBox.setStandardButtons(QMessageBox::Ok);
//         msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");
//         QObject::connect(&msgBox, &QMessageBox::finished, [&](){
//             msgBox.close();
//             ui->username->clear();
//         });
//         msgBox.exec();
//     }
// }
void LoginPage::on_loginButton_clicked()
{
    string s = ui->username->text().toStdString();
    cout<<s<<endl;
    bool set = app->setCurrentUser(s);
    if(!set){
        popup = new UsernameError(this);
        popup->show();
    }
    else{
        page = new HomePage(this,app,this);
        this->close();
        page->show();
    }
}
