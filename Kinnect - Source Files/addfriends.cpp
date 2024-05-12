#include "addfriends.h"
#include "myClasses.h"
#include "ui_addfriends.h"
#include "usernameerror.h"
#include "userprofile.h"
#include <iostream>
using namespace std;

AddFriends::AddFriends(QWidget *parent,SocialNetworkApp* app1)
    : QDialog(parent)
    , ui(new Ui::AddFriends)
{
    ui->setupUi(this);
    this->app=app1;
    int n = app->returnTotalUsers();
    User** temp = app->getUsers();
    ui->tableWidget->setRowCount(n);
    for (int i = 0; i < n; ++i) {
        // ui->tableWidget->setItem(temp[i]->getUserID(),QString::fromStdString(temp[i]->getName()));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(temp[i]->getUserID())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(temp[i]->getName())));
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

AddFriends::~AddFriends()
{
    delete ui;
}

void AddFriends::on_addFriendsBtn_clicked()
{
    string s = ui->friendUsername->text().toStdString();
    int added = app->addFriend(s);
    if(added==1){
        this->errorPage = new UsernameError(this);
        errorPage->setErrorMessage("Success!","Friend added successfully ;>");
        errorPage->show();
    }
    else if(added==2){
        this->errorPage = new UsernameError(this);
        errorPage->setErrorMessage("Error!","You can not friend yourself ;<");
        errorPage->show();
    }
    else if(added==3){
        this->errorPage = new UsernameError(this);
        errorPage->show();
    }
    else if(added==4){
        this->errorPage = new UsernameError(this);
        errorPage->setErrorMessage("Error!","User already in your friend list ;<");
        errorPage->show();
    }
}


void AddFriends::on_tableWidget_cellDoubleClicked(int row, int column)
{
    // Get the QString from the clicked cell
    QTableWidgetItem* item = ui->tableWidget->item(row, column);
    if (item) {
        QString userName = item->text();

        // Find the corresponding User object inside the SocialNetworkApp
        int totalUsers = app->returnTotalUsers();
        User** users = app->getUsers();
        User* clickedUser = nullptr;
        for (int i = 0; i < totalUsers; ++i) {
            if (QString::fromStdString(users[i]->getName()) == userName ||
                QString::number(users[i]->getUserID()) == userName) {
                clickedUser = users[i];
                break;
            }
        }
        cout<<"User name here: "<<clickedUser->getName()<<endl;

        if (clickedUser) {
            // Open a new window and pass the SocialNetworkApp and User objects
            // Assuming you have a MainWindow class for the new window
            userWindow = new UserProfile(this, app, clickedUser);
            userWindow->show();
        } else {
            // User not found, handle the error
        }
    }
}
