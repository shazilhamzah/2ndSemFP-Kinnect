#include "homepage.h"
#include "ui_homepage.h"
#include "loginpage.h"
#include "addfriends.h"
#include "pageview.h"
#include <string>

#include<iostream>
using namespace std;

string activity(int type,int value){
    string s;
    if(type==0){
        return "NULL";
    }
    if(type==1){
        if(value==1){
            s="Feeling Happy";
            return s;
        }
        else if(value==2){
            s="Feeling Sad";
            return s;
        }
        else if(value==3){
            s="Feeling Exceited";
            return s;
        }
        else{
            return "NULL";
        }
    }
    else if(type==2){
        if(value==1){
            s="Thinking about life";
            return s;
        }
        else if(value==2){
            s="Thinking about Future";
            return s;
        }
        else if(value==3){
            s="Thinking about meaning of Life";
            return s;
        }
        else{
            return "NULL";
        }
    }
    else if(type==3){
        if(value==1){
            s="Making money";
            return s;
        }
        else if(value==2){
            s="Making art";
            return s;
        }
        else if(value==3){
            s="Making memories";
            return s;
        }
        else{
            return "NULL";
        }
    }
    else if(type==4){
        if(value==1){
            s="Celebrating birthday";
            return s;
        }
        else if(value==2){
            s="Celebrating Halloween";
            return s;
        }
        else if(value==3){
            s="Celebrating Success";
            return s;
        }
        else{
            return "NULL";
        }
    }
    return s;
}

HomePage::HomePage(QWidget *parent, SocialNetworkApp *app1, LoginPage *loginPage)
    : QDialog(parent),
    ui(new Ui::HomePage),
    app(app1),
    login(loginPage),
    owner(app->getOwner())
{
    ui->setupUi(this);


    User** temp = app->getUsers();
    this->login = loginPage;
    this->owner = app->getOwner();
    string s = owner->getName();
    ui->usernameLabel->setText(QString::fromStdString(s));
    ui->activityType->addItem("None", 0);
    ui->activityType->addItem("Feeling",1);
    ui->activityType->addItem("Thinking",2);
    ui->activityType->addItem("Making",3);
    ui->activityType->addItem("Celebrating",4);
    connect(ui->activityType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HomePage::updateComboBoxValue);



    ui->pageValue->addItem("None");
    ui->pageValue->addItem("<New Page>");
    Page**temp34 = owner->getPages();
    for (int i = 0; i < owner->getTotalPages(); ++i) {
        ui->pageValue->addItem(QString::fromStdString(temp34[i]->getName()));
    }




    ui->tableWidget->setColumnCount(5);
    QStringList labels;
    labels << "Date" << "Post ID" << "Name" << "Description" << "Activity";
    ui->tableWidget->setHorizontalHeaderLabels(labels);




    // Populate the table with posts
    int totalPosts = 0;
    User **friendList = owner->getFriendList();
    int totalFriends = owner->getTotalFriends();
    for (int i = 0; i < totalFriends; ++i)
    {
        totalPosts += friendList[i]->getTotalPosts();
    }

    // Set the row count
    ui->tableWidget->setRowCount(totalPosts);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int row = 0;
    for (int i = 0; i < totalFriends; ++i)
    {
        Post **posts = friendList[i]->getPosts();
        int totalPosts = friendList[i]->getTotalPosts();
        Date temp;
        for (int j = 0; j < totalPosts; ++j)
        {
            temp = posts[j]->getPostDate();
            string d = to_string(temp.getDate())+"-"+to_string(temp.getMonth())+"-"+to_string(temp.getYear());
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::fromStdString(d)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(posts[j]->getPostID())));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(friendList[i]->getName())));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(posts[j]->getDescription())));
            string h = activity(posts[j]->getActivityType(),posts[j]->getActivityValue());
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(h)));
            ++row;
        }
    }
}

HomePage::~HomePage()
{ 
    delete ui;
}

void HomePage::on_logoutBtn_clicked()
{
    // Close current homepage window
    close();
    this->owner = nullptr;

    // Option 1 (Re-create and show login page):
    LoginPage* loginPage = new LoginPage(nullptr, app); // Create new instance
    loginPage->show(); // Show login page
}

void HomePage::on_addFriendsBtn_clicked()
{
    addFriends = new AddFriends(this,app);
    addFriends->show();
}

void HomePage::updateComboBoxValue(int index) {
    ui->activityValue->clear();
     int type = ui->activityType->currentData().toInt();
    switch (type) {
     case 0:
        break;
    case 1: // Feeling
        ui->activityValue->addItem("None", 0);
        ui->activityValue->addItem("Happy",1);
        ui->activityValue->addItem("Sad",2);
        ui->activityValue->addItem("Excited",3);
        break;
    case 2: // Thinking
        ui->activityValue->addItem("None", 0);
        ui->activityValue->addItem("About life",1);
        ui->activityValue->addItem("About future",2);
        ui->activityValue->addItem("About meaning of life",3);
        break;
    case 3: // Making
        ui->activityValue->addItem("None", 0);
        ui->activityValue->addItem("Money",1);
        ui->activityValue->addItem("Art",2);
        ui->activityValue->addItem("Memories",3);
        break;
    case 4: // Celebrating
        ui->activityValue->addItem("None", 0);
        ui->activityValue->addItem("A birthday",1);
        ui->activityValue->addItem("Halloween",2);
        ui->activityValue->addItem("Success",3);
        break;
    default:
        break;
    }
}

void HomePage::on_addPostBtn_2_clicked()
{
    QString selectedPageName = ui->pageValue->currentText();
    Page** pages = owner->getPages();
    int totalPages = owner->getTotalPages();
    Page* selectedPage = nullptr;
    for (int i = 0; i < totalPages; ++i) {
        if (QString::fromStdString(pages[i]->getName()) == selectedPageName) {
            selectedPage = pages[i];
            break;
        }
    }
    usernameError = new UsernameError(this);
    usernameError->setErrorMessage("Success","Post added Successfuly!");
    usernameError->show();

    string p = ui->description->toPlainText().toStdString();
    int type = ui->activityType->currentData().toInt();
    int value = ui->activityValue->currentData().toInt();
    if(selectedPage!=nullptr){
        Post* newPost = new Post(*owner);
        Date* datetemp = app->getDateObject();
        newPost->setDescription(p);
        newPost->setActivity(type, value);
        newPost->setDate(datetemp->getDate(),datetemp->getMonth(),datetemp->getYear());
        app->addUserPost(owner, p, type, value);
        selectedPage->addPost(newPost);
    }
    else{
        app->addUserPost(owner, p, type, value);
    }
    owner->viewHomePage();
}


void HomePage::on_tableWidget_cellDoubleClicked(int row, int column)
{
    // Initialize strings a, b, c, and d
    string a, b, c, d, e;

    // Iterate through all columns
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QTableWidgetItem *item = ui->tableWidget->item(row, col);
        if (item) {
            QString cellText = item->text();
            if (!cellText.isEmpty()) {
                // Check the column to determine what data to save
                switch (col) {
                case 0: // Post ID column
                    a = cellText.toStdString();
                    break;
                case 1: // Name column
                    b = cellText.toStdString();
                    break;
                case 2: // Description column
                    c = cellText.toStdString();
                    break;
                case 3: // Activity column
                    d = cellText.toStdString();
                    break;
                case 4:
                    e = cellText.toStdString();
                    break;
                default:
                    break;
                }
            }
        }
    }

    Post* tempPost;
    Post** tempPosts;
    User** tempUsers = app->getUsers();
    for (int i = 0; i < app->returnTotalUsers(); ++i) {
        if(tempUsers[i]->getName()==c){
            tempPosts = tempUsers[i]->getPosts();
            for (int j = 0; j < tempUsers[i]->getTotalPosts(); ++j) {
                if(tempPosts[j]->getPostID() == stoi(b)){
                    tempPost = tempPosts[j];
                    break;
                }
            }
            if(tempPost != nullptr) {
                break;
            }
        }
    }


    if(tempPost != nullptr) {
        postview = new PostView(this, owner, a, b, c, d, e, tempPost,app);
        postview->show();
    } else {
        cout<<"post was null";
    }
}




void HomePage::on_refreshBtn_clicked()
{
    this->close();
    HomePage *newHomePage = new HomePage(this, app, login);
    newHomePage->show();
}


void HomePage::on_allPages_clicked()
{
    pageview = new PageView(this,app);
    pageview->show();
}


void HomePage::on_YourPosts_clicked()
{
    this->myProfile = new UserProfile(this,app,owner);
    myProfile->show();
}


void HomePage::on_viewMemories_clicked()
{
    memoryView = new MemoryView(this,app,owner);
    memoryView->show();
}

void HomePage::on_pageValue_activated(int index) {
    QString selectedItem = ui->pageValue->itemText(index);
    if (selectedItem == "<New Page>") {
        addpagePage = new AddPage(this,owner);
        addpagePage->show();
    }
}
