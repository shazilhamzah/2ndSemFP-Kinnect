#ifndef AVAILABLEUSERS_H
#define AVAILABLEUSERS_H
#include "myClasses.h"

#include <QDialog>

class PostView;
namespace Ui {
class AvailableUsers;
}

class AvailableUsers : public QDialog
{
    Q_OBJECT

public:
    explicit AvailableUsers(QWidget *parent = nullptr,Post* post=nullptr, bool isPostView=false);
    void setMessage(string);
    void fromAddPage(User*);
    void fromPageView(Page* page);
    PostView* postviewPage;
    ~AvailableUsers();



private:
    Ui::AvailableUsers *ui;
};

#endif // AVAILABLEUSERS_H
