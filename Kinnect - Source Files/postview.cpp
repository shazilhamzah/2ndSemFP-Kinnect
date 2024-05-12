#include "postview.h"
#include "ui_postview.h"
#include "myClasses.h"
#include <iostream>
#include "availableusers.h"
#include "viewcomments.h"
using namespace std;

PostView::PostView(QWidget *parent, User* currentUser1, string date, string postID, string name, string description, string activity, Post* postGot,SocialNetworkApp*app1,bool FromOwn)
    : QDialog(parent)
    , ui(new Ui::PostView)
{
    cout<<"Checkpoint 1-a crossed!"<<endl;
    ui->setupUi(this);
    cout<<"Checkpoint 2-a crossed!"<<endl;
    this->postowner = postGot->getPostOwner();
    cout<<"Checkpoint 3-a crossed!"<<endl;
    this->currentUser = currentUser1;
    cout<<"Checkpoint 4-a crossed!"<<endl;
    this->post = postGot;
    this->app = app1;

    if(currentUser->getUserID()!=postowner->getUserID()){
        ui->viewComments_2->hide();
    }
    cout<<"Checkpoint 5-a crossed!"<<endl;
    if(postowner!=nullptr){
        ui->labelpara->setText(QString::fromStdString(postowner->getName()) + " #" + QString::number(postowner->getUserID()));
    }
    else{
        cout<<"Null found!"<<endl;
    }
    cout<<"Checkpoint 6-a crossed!"<<endl;
    ui->date->setText(QString::fromStdString(date));
    ui->postid->setText("#"+QString::fromStdString(postID));
    cout<<"Checkpoint 7-a crossed!"<<endl;
    ui->textEdit->setText(QString::fromStdString(description));
    cout<<"Checkpoint 8-a crossed!"<<endl;
}

PostView::~PostView()
{
    delete ui;
}

void PostView::on_likeBtn_clicked()
{
    if(post->getLikes()==10){
        errorPage = new UsernameError(this);
        errorPage->setErrorMessage("ERROR!","LIKES LIMIT OF 10 REACHED!");
        errorPage->show();
        return;
    }
    post->addLikeOnPost(currentUser);
}


void PostView::on_viewlikesBtn_clicked()
{
    likedPeopleView = new AvailableUsers(this,post,true);
    likedPeopleView->show();
}


void PostView::on_postbtn_clicked()
{
    string s = ui->comment->text().toStdString();
    Comment* comment = new Comment();
    Date* tempDate = app->getDateObject();
    cout<<"I am at checkpoint 1"<<endl;
    comment->setComment(s);
    cout<<"I am at checkpoint 2"<<endl;
    comment->setDate(tempDate);
    cout<<"I am at checkpoint 3"<<endl;
    comment->setWhoCommented(currentUser);
    cout<<"I am at checkpoint 4"<<endl;
    post->addCommentOnPost(comment);
    cout<<"I am at checkpoint 5"<<endl;
    cout<<post->getTotalComments();
    cout<<"I am at checkpoint 6"<<endl;
}


void PostView::on_viewComments_clicked()
{
    cout<<"I am at checkpoint 16"<<endl;
    viewCommentsPage = new ViewComments(this,post);
    cout<<"I am at checkpoint 17"<<endl;
    viewCommentsPage->show();
}


void PostView::on_viewComments_2_clicked()
{
    Date* tempDate = app->getDateObject();
    Date* oldDate = new Date();
    cout<<"Checkpoint a"<<endl;
    oldDate->setDate(post->getPostDate().getDate());
    oldDate->setMonth(post->getPostDate().getMonth());
    oldDate->setYear(post->getPostDate().getYear());
    cout<<"Checkpoint b"<<endl;
    Memory* memorytemp = new Memory(post,oldDate);
    cout<<"Checkpoint c"<<endl;
    currentUser->addMemories(memorytemp);
    cout<<"Checkpoint d"<<endl;
}
