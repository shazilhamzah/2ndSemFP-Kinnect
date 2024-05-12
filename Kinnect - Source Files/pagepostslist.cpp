#include "pagepostslist.h"
#include "ui_pagepostslist.h"
#include "myClasses.h"

#include <iostream>
using namespace std;

string activity1(int,int);
PagePostsList::PagePostsList(QWidget *parent,Page*page,SocialNetworkApp*app1)
    : QDialog(parent)
    , ui(new Ui::PagePostsList)
{
    ui->setupUi(this);
    this->app = app1;
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

string activity1(int type,int value){
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




PagePostsList::~PagePostsList()
{
    delete ui;
}

void PagePostsList::on_tableWidget_cellDoubleClicked(int row, int column)
{
    string a, b, c, d, e;
    // Iterate through all columns
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QTableWidgetItem *item = ui->tableWidget->item(row, col);
        if (item) {
            QString cellText = item->text();
            if (!cellText.isEmpty()) {
                // Check the column to determine what data to save
                switch (col) {
                case 0: // Post ID column
                    a = cellText.toStdString();
                    break;
                case 1: // Name column
                    b = cellText.toStdString();
                    break;
                case 2: // Description column
                    c = cellText.toStdString();
                    break;
                case 3: // Activity column
                    d = cellText.toStdString();
                    break;
                case 4:
                    e = cellText.toStdString();
                    break;
                default:
                    break;
                }
            }
        }
    }
    cout<<"Checkpoint 1 crossed!"<<endl;
    Post* tempPost;
    User* owner;
    User** tempUsers = app->getUsers();
    for (int i = 0; i < app->getTotalUsers(); ++i) {
        if (tempUsers[i]->getName() == c) {
            Post** tempPosts = tempUsers[i]->getPosts();
            for (int j = 0; j < tempUsers[i]->getTotalPosts(); ++j) {
                cout<<"\nI was in here!"<<endl;
                cout<<tempPosts[j]->getPostID()<<" "<<b;
                if (tempPosts[j]->getPostID() == stoi(b)+1) {
                    tempPost = tempPosts[j];
                    owner = tempUsers[i];
                    break;
                }
            }
            if (tempPost != nullptr && owner != nullptr) {
                cout<<"\nI was in here too!"<<endl;
                break;
            }
        }
    }

    cout<<a<<b<<c<<d<<e;
    cout<<"I was here!"<<endl;
    cout<<"post:"<<tempPost->getDescription();
    cout<<"Owner:"<<owner->getName();

    cout<<"Checkpoint 2 crossed!"<<endl;
    if (tempPost != nullptr && owner != nullptr) {
        PostView* postView = new PostView(this, owner, a, b, c, d, e, tempPost, app);
        postView->show();
    } else {
        if(tempPost==nullptr)
            cout<<"post"<<endl;
        else{
            cout<<"user"<<endl;
        }
        cout<<"Error occured!"<<endl;
    }
}



