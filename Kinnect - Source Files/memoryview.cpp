#include "memoryview.h"
#include "ui_memoryview.h"
#include <iostream>
using namespace std;


string activity122(int,int);
MemoryView::MemoryView(QWidget *parent,SocialNetworkApp*app1,User*user1)
    : QDialog(parent)
    , ui(new Ui::MemoryView)
{
    ui->setupUi(this);
    this->app=app1;
    this->owner=user1;

    User** friendList = owner->getFriendList();
    int totalFriends = owner->getTotalFriends();
    int n = 0,row=0;
    for (int i = 0; i < owner->getTotalFriends(); ++i) {
        n+=friendList[i]->getTotalMemories();
    }
    cout<<"Total Memories: "<<n<<endl;
    ui->tableWidget->setRowCount(n);

    for (int i = 0; i < totalFriends; ++i)
    {
        Memory **posts = friendList[i]->getMemories();
        int totalMemories = friendList[i]->getTotalMemories();
        Date temp,*temp1;
        for (int j = 0; j < totalMemories; ++j)
        {
            temp = posts[j]->getPost()->getPostDate();
            temp1 = app->getDateObject();
            string d = to_string(temp.getDate())+"-"+to_string(temp.getMonth())+"-"+to_string(temp.getYear());
            cout<<"Date: "<<d<<endl;
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(friendList[i]->getName())));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(posts[j]->getPost()->getPostID())));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(posts[j]->getPost()->getDescription())));
            string h = activity122(posts[j]->getPost()->getActivityType(),posts[j]->getPost()->getActivityValue());
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(h)));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString::fromStdString(d)));
            string e = to_string(temp1->getDate())+"-"+to_string(temp1->getMonth())+"-"+to_string(temp1->getYear());
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::fromStdString(e)));
            ++row;
        }
    }
}

MemoryView::~MemoryView()
{
    delete ui;
}

string activity122(int type,int value){
    string s;
    if(type==0){
        return "NULL";
    }
    if(type==1){
        if(value==1){
            s="Feeling Happy";
            return s;
        }
        else if(value==2){
            s="Feeling Sad";
            return s;
        }
        else if(value==3){
            s="Feeling Exceited";
            return s;
        }
        else{
            return "NULL";
        }
    }
    else if(type==2){
        if(value==1){
            s="Thinking about life";
            return s;
        }
        else if(value==2){
            s="Thinking about Future";
            return s;
        }
        else if(value==3){
            s="Thinking about meaning of Life";
            return s;
        }
        else{
            return "NULL";
        }
    }
    else if(type==3){
        if(value==1){
            s="Making money";
            return s;
        }
        else if(value==2){
            s="Making art";
            return s;
        }
        else if(value==3){
            s="Making memories";
            return s;
        }
        else{
            return "NULL";
        }
    }
    else if(type==4){
        if(value==1){
            s="Celebrating birthday";
            return s;
        }
        else if(value==2){
            s="Celebrating Halloween";
            return s;
        }
        else if(value==3){
            s="Celebrating Success";
            return s;
        }
        else{
            return "NULL";
        }
    }
    return s;
}
