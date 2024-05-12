#ifndef ADDFRIENDS_H
#define ADDFRIENDS_H
#include "myClasses.h"
#include "usernameerror.h"
#include "userprofile.h"
#include <QDialog>

namespace Ui {
class AddFriends;
}

class AddFriends : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriends(QWidget *parent = nullptr,SocialNetworkApp* app1=nullptr);
    ~AddFriends();

private slots:
    void on_addFriendsBtn_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::AddFriends *ui;
    SocialNetworkApp* app;
    UsernameError* errorPage;
    UserProfile* userWindow;
};

#endif // ADDFRIENDS_H
