#include "viewcomments.h"
#include "ui_viewcomments.h"
#include <iostream>
using namespace std;

ViewComments::ViewComments(QWidget *parent,Post*post)
    : QDialog(parent)
    , ui(new Ui::ViewComments)
{
    cout<<"I am at checkpoint 1"<<endl;
    ui->setupUi(this);
    ui->toEdit->setText(QString::fromStdString(post->getPostOwner()->getName())+"'s");
    ui->commentors->setColumnCount(3);
    QStringList labels;
    labels << "UserID" << "Username" << "Comment";
    ui->commentors->setHorizontalHeaderLabels(labels);
    cout<<"I am at checkpoint 2"<<endl;
    int totalPosts = 0;
    Comment** tempComments = post->getComments();
    cout<<tempComments[0]->getWhoCommented()->getName()<<endl;
    int totalComments = post->getTotalComments();
    cout<<"Total comments: "<<totalComments<<endl; // Debugging
    cout<<"I am at checkpoint 3"<<endl;
    // Set the row count
    ui->commentors->setRowCount(post->getTotalComments());
    ui->commentors->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cout<<"I am at checkpoint 4-bbbbb"<<endl;
    int row = 0;
    for (int i = 0; i < totalComments; ++i)
    {
        ui->commentors->setItem(i,0,new QTableWidgetItem(QString::number(tempComments[i]->getWhoCommented()->getUserID())));
        cout<<tempComments[i]->getWhoCommented()->getUserID()<<endl;
        ui->commentors->setItem(i,1,new QTableWidgetItem(QString::fromStdString(tempComments[i]->getWhoCommented()->getName())));
        cout<<tempComments[i]->getWhoCommented()->getName()<<endl;
        ui->commentors->setItem(i,2,new QTableWidgetItem(QString::fromStdString(tempComments[i]->getComment())));
        cout<<tempComments[i]->getComment()<<endl;
    }
}

ViewComments::~ViewComments()
{
    delete ui;
}
