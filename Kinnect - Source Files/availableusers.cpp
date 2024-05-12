#include "availableusers.h"
#include "ui_availableusers.h"
#include "myClasses.h"
#include <iostream>
using namespace std;


string activity1(int type,int value);
AvailableUsers::AvailableUsers(QWidget *parent,Post* post,bool isPostView)
    : QDialog(parent)
    , ui(new Ui::AvailableUsers)
{
    if(isPostView){
        cout<<"I am here!"<<endl;
        ui->setupUi(this);
        ui->labelpara->setText("Likes");
        cout<<"I am at checkpoint 1"<<endl;
        User** temp = post->getLikedPeople();
        int n = post->getLikes();
        ui->tableWidget->setRowCount(post->getLikes());
        for (int i = 0; i < n; ++i) {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(temp[i]->getUserID())));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(temp[i]->getName())));
        }
    }
    else{
        ui->setupUi(this);
        SocialNetworkApp app1;
        int n = app1.getTotalUsers();
        app1.addUsers();
        User** temp = app1.getUsers();
        ui->tableWidget->setRowCount(n);
        for (int i = 0; i < n; ++i) {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(temp[i]->getUserID())));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(temp[i]->getName())));
        }

        for (int i = 0; i < n; ++i) {
            delete temp[i];
        }
        delete temp;
    }

}

void AvailableUsers::setMessage(string a){
    ui->labelpara->setText(QString::fromStdString(a));
    ui->tableWidget->clear();
}

void AvailableUsers::fromAddPage(User*user){
    int n = user->getTotalPages();
    Page**temp = user->getPages();
    ui->tableWidget->setRowCount(n);
    for (int i = 0; i < n; ++i) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(temp[i]->getID())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(temp[i]->getName())));
    }
}

void AvailableUsers::fromPageView(Page* page){
    int n = page->getTotalPosts();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(n);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(5);
    QStringList labels;
    labels << "Date" << "Post ID" << "Name" << "Description" << "Activity";
    ui->tableWidget->setHorizontalHeaderLabels(labels);


    Post** temp = page->getPosts();
    ui->labelpara->setText("Posts from"+QString::fromStdString(page->getName()));
    for (int i = 0; i < n; ++i) {
        string s = activity1(temp[i]->getActivityType(),temp[i]->getActivityValue());
        Date tempDate = temp[i]->getPostDate();
        string d = to_string(tempDate.getDate())+"-"+to_string(tempDate.getMonth())+"-"+to_string(tempDate.getYear());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(d)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(temp[i]->getPostID())));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromStdString(temp[i]->getPostOwner()->getName())));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::fromStdString(temp[i]->getDescription())));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::fromStdString(s)));
    }
}

AvailableUsers::~AvailableUsers()
{
    delete ui;
}



