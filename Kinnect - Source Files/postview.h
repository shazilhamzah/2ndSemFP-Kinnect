#ifndef POSTVIEW_H
#define POSTVIEW_H

#include <QDialog>
#include "myClasses.h"
#include "usernameerror.h"
#include "viewcomments.h"

class AvailableUsers;
namespace Ui {
class PostView;
}

class PostView : public QDialog
{
    Q_OBJECT

public:
    explicit PostView(QWidget *parent = nullptr,User*currentUser1 = nullptr,string a="",string b="",string c="",string d="",string e="",Post*postGot=nullptr,SocialNetworkApp*app=nullptr,bool FromOwn=false);
    ~PostView();

private slots:
    void on_likeBtn_clicked();
    void on_viewlikesBtn_clicked();

    void on_postbtn_clicked();

    void on_viewComments_clicked();

    void on_viewComments_2_clicked();

private:
    Ui::PostView *ui;
    User* postowner;
    Post* post;
    User* currentUser;
    AvailableUsers* likedPeopleView;
    UsernameError* errorPage;
    SocialNetworkApp*app;
    ViewComments* viewCommentsPage;
};

#endif // POSTVIEW_H
