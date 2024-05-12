#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include "availableusers.h"
#include"usernameerror.h"
#include"homepage.h"
#include "myClasses.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QDialog
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr,SocialNetworkApp *app = nullptr);
    ~LoginPage();

private slots:
    void on_viewUsers_clicked();
    void on_loginButton_clicked();
private:
    Ui::LoginPage *ui;
    AvailableUsers* users;
    SocialNetworkApp*app;
    UsernameError*popup;
    HomePage*page;
};

#endif // LOGINPAGE_H
