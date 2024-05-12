#include "userprofile.h"
#include "ui_userprofile.h"
#include <iostream>
using namespace std;

string activity23(int type,int value){
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


UserProfile::UserProfile(QWidget *parent,SocialNetworkApp*app1,User*user1)
    : QDialog(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    this->app = app1;
    this->user = user1;

    string s = user->getName();
    ui->username->setText(QString::fromStdString(s));

    QStringList labels;
    labels << "Date" << "Post ID" << "Name" << "Description" << "Activity";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    // Get the user's posts
    Post** posts = user->getPosts();
    int totalPosts = user->getTotalPosts();

    // Set the row count
    ui->tableWidget->setRowCount(totalPosts);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Setting up total likes and posts
    int totalLikes=0;
    for (int i = 0; i < user->getTotalPosts(); ++i) {
        totalLikes+=posts[i]->getLikes();
    }
    ui->numberPosts->setText(QString::number(user->getTotalPosts()));
    ui->numberLikes->setText(QString::number(totalLikes));

    for (int i = 0; i < totalPosts; ++i)
    {
        if(posts[i] != nullptr){
            Date tempDate = posts[i]->getPostDate();
            string dateString = to_string(tempDate.getDate()) + "-" + to_string(tempDate.getMonth()) + "-" + to_string(tempDate.getYear());

            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dateString)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(posts[i]->getPostID())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(user->getName())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(posts[i]->getDescription())));
            string activityString = activity23(posts[i]->getActivityType(), posts[i]->getActivityValue());
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(activityString)));
        }
        else{
            cout << "Post was null!" << endl;
        }
    }
}


UserProfile::~UserProfile()
{
    delete ui;
}


void UserProfile::on_tableWidget_cellDoubleClicked(int row, int column)
{
    // Initialize strings a, b, c, and d
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

    Post* tempPost;
    Post** tempPosts;
    User** tempUsers = app->getUsers();
    for (int i = 0; i < app->returnTotalUsers(); ++i) {
        if(tempUsers[i]->getName()==c){
            tempPosts = tempUsers[i]->getPosts();
            for (int j = 0; j < tempUsers[i]->getTotalPosts(); ++j) {
                if(tempPosts[j]->getPostID() == stoi(b)){
                    tempPost = tempPosts[j];
                    break;
                }
            }
            if(tempPost != nullptr) {
                break;
            }
        }
    }

    if(tempPost != nullptr) {
        postview = new PostView(this, app->getOwner(), a, b, c, d, e, tempPost,app);
        postview->show();
    } else {
        cout<<"post was null";
    }
}
