#include "addpage.h"
#include "ui_addpage.h"
#include "myClasses.h"
#include "usernameerror.h"

AddPage::AddPage(QWidget *parent,User*user)
    : QDialog(parent)
    , ui(new Ui::AddPage)
{
    ui->setupUi(this);
    this->owner = user;
}

AddPage::~AddPage()
{
    delete ui;
}

void AddPage::on_addBtn_clicked()
{
    string s = ui->pageName->text().toStdString();
    Page* temp = new Page();
    temp->setName(s);
    bool set = owner->addPage(temp);
    if(set){
        newPageName = s;
        popup = new UsernameError(this);
        // owner->addPage(temp);
        popup->setErrorMessage("Success!","Page is added in your list ;>");
        popup->show();
    }
    else{
        popup = new UsernameError(this);
        popup->setErrorMessage("Error!","Name is already taken by you ;<");
        popup->show();
        delete temp;
    }
}

std::string AddPage::getNewPageName(){
    return newPageName;
}


void AddPage::on_viewPages_clicked()
{
    page = new AvailableUsers(this);
    page->setMessage("Your Pages");
    page->fromAddPage(owner);
    page->show();
}
