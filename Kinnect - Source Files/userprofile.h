#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QDialog>
#include "myClasses.h"
#include "postview.h"

namespace Ui {
class UserProfile;
}

class UserProfile : public QDialog
{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr,SocialNetworkApp*app=nullptr,User*user=nullptr);
    ~UserProfile();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::UserProfile *ui;
    SocialNetworkApp*app;
    User*user;
    PostView*postview;
};

#endif // USERPROFILE_H
