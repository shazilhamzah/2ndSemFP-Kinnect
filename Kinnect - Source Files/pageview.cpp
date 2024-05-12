#include "pageview.h"
#include "ui_pageview.h"
#include "myClasses.h"
#include <iostream>
using namespace std;

PageView::PageView(QWidget *parent,SocialNetworkApp*apptemp)
    : QDialog(parent)
    , ui(new Ui::PageView)
{
    ui->setupUi(this);
    app = apptemp;
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row = 0;
    User** users = app->getUsers();
    int totalRows = 0;
    int totalUsers = app->returnTotalUsers();
    for (int i = 0; i < totalUsers; ++i) {
        User* user = users[i];
        totalRows += user->getTotalPages();
    }
    ui->tableWidget->setRowCount(totalRows);
    for (int i = 0; i < totalUsers; ++i) {
        User* user = users[i];
        int totalPages = user->getTotalPages();
        Page** pages = user->getPages();
        for (int j = 0; j < totalPages; ++j) {
            Page* page = pages[j];
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(page->getID())));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::fromStdString(page->getName())));
            cout << "Page ID: " << page->getID() << ", Name: " << page->getName() << endl;
            row++;
        }
    }
}

PageView::~PageView()
{
    delete ui;
}


void PageView::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    if (item) {
        int pageID = item->text().toInt();
        Page *tempPage = nullptr;
        User **users = app->getUsers();
        int totalUsers = app->returnTotalUsers();
        for (int i = 0; i < totalUsers; ++i) {
            User *user = users[i];
            int totalPages = user->getTotalPages();
            Page **pages = user->getPages();
            for (int j = 0; j < totalPages; ++j) {
                if (pages[j]->getID() == pageID) {
                    tempPage = pages[j];
                    break;
                }
            }
            if (tempPage) {
                break;
            }
        }
        if (tempPage) {
            listPage = new PagePostsList(this,tempPage,app);
            listPage->show();
        }
        else {
            cout<<"Error in PageView::on_tableWidget_cellDoubleClicked function!"<<endl;
            return;
        }
    }
}

