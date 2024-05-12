#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>
#include "myClasses.h"
#include "addfriends.h"
#include "postview.h"
#include "addpage.h"
#include "pageview.h"
#include "userprofile.h"
#include "memoryview.h"
#include "usernameerror.h"

class LoginPage;

namespace Ui {
class HomePage;
}

class HomePage : public QDialog
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr,SocialNetworkApp *app = nullptr,LoginPage*loginPage=nullptr);
    LoginPage* login;
    ~HomePage();

private slots:
    void on_logoutBtn_clicked();
    void updateComboBoxValue(int index);
    void on_addFriendsBtn_clicked();
    void on_addPostBtn_2_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_refreshBtn_clicked();
    // void on_newPage_clicked();
    void on_allPages_clicked();
    void on_YourPosts_clicked();
    void on_viewMemories_clicked();
    void on_pageValue_activated(int index);

private:
    Ui::HomePage *ui;
    SocialNetworkApp*app;
    AddFriends* addFriends;
    PostView* postview;
    User* owner;
    AddPage* addpagePage;
    PageView* pageview;
    UserProfile*myProfile;
    MemoryView*memoryView;
    UsernameError*usernameError;
};

#endif // HOMEPAGE_H
