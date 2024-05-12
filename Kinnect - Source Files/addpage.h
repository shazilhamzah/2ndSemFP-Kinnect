#ifndef ADDPAGE_H
#define ADDPAGE_H

#include <QDialog>
#include "myClasses.h"
#include "usernameerror.h"
#include "availableusers.h"

namespace Ui {
class AddPage;
}

class AddPage : public QDialog
{
    Q_OBJECT

public:
    explicit AddPage(QWidget *parent = nullptr,User*user = nullptr);
    string getNewPageName();
    ~AddPage();

private slots:
    void on_addBtn_clicked();
    void on_viewPages_clicked();

signals:

private:
    Ui::AddPage *ui;
    User* owner;
    UsernameError* popup;
    AvailableUsers* page;
    string newPageName="";
};

#endif // ADDPAGE_H
