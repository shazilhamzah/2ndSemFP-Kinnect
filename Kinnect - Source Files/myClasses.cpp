#include"myClasses.h"
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
using namespace std;


/*

USER

*/

User::User(string s, double n) : name(s), user_id(n), posts(nullptr), totalPosts(0), friend_list(nullptr), totalFriends(0), pages(nullptr), totalPages(0), memories(nullptr), totalMemories(0) {
    this->user_id = n;
    this->name = s;
    this->totalMemories = 0;
}


void User::setName(string s){
    this->name=s;
}

void User::setUserID(double n){
    this->user_id = n;
}

string User::getName(){
    return this->name;
}

double User::getUserID(){
    return this->user_id;
}

bool User::addFriend(User* friendPtr){
    // Check if friendPtr is already in the friend list
    for (int i = 0; i < totalFriends; ++i) {
        if (friend_list[i] == friendPtr) {
            return false; // Friend already exists in the list
        }
    }

    // If friend is not in the list, add the friend
    User** temp = new User*[totalFriends + 1];
    for (int i = 0; i < totalFriends; ++i) {
        temp[i] = friend_list[i];
    }
    temp[totalFriends] = friendPtr;
    delete[] friend_list;
    friend_list = temp;
    ++totalFriends;
    return true; // Friend added successfully
}

void User::printFriends(){
    cout << "\n\nFriend list:\n";
    for (int i = 0; i < totalFriends; ++i) {
        cout << friend_list[i]->getName() << endl;
    }
}

void User::addPost(User*user,string s,int type,int value,Date*& systemDate){
    Post** temp = new Post * [totalPosts + 1];
    for (int i = 0; i < totalPosts; ++i) {
        temp[i] = posts[i];
    }
    temp[totalPosts] = new Post(*this);
    temp[totalPosts]->setDescription(s);
    temp[totalPosts]->setActivity(type,value);
    cout<<endl<<"I am posting: "<<user->getName()<<endl;
    temp[totalPosts]->setOwner(user);
    int a = systemDate->getDate();
    int b = systemDate->getMonth();
    int c = systemDate->getYear();
    temp[totalPosts]->setDate(a,b,c);
    printFriends();
    delete[] posts;
    posts = temp;
    ++totalPosts;
}


void User::viewHomePage() {
    cout<<"Viewing home page"<<endl;
    for (int i = 0; i < totalFriends; i++)
    {
        int n = friend_list[i]->totalPosts;
        for (int j = 0; j < n; j++)
        {
            Date temp = friend_list[i]->posts[j]->getPostDate();
            cout << friend_list[i]->posts[j]->getPostID() << "\t" << friend_list[i]->posts[j]->getDescription() << endl;
            cout<<temp.getDate()<<"-"<<temp.getMonth()<<"-"<<temp.getYear()<<endl;
        }
    }
    cout<<endl;
}

int User::getTotalPosts(){
    return totalPosts;
}

User** User::getFriendList(){
    return this->friend_list;
}

int User::getTotalFriends(){
    return this->totalFriends;
}

Post** User::getPosts(){
    return this->posts;
}

bool User::addPage(Page* pageToAdd){
    for (int i = 0; i < this->totalPages; ++i) {
        if (this->pages[i]->getName() == pageToAdd->getName()) {
            return false;
        }
    }
    Page** temp = new Page * [this->totalPages + 1];
    for (int i = 0; i < this->totalPages; ++i) {
        temp[i] = this->pages[i];
    }
    temp[this->totalPages] = pageToAdd;
    delete[] this->pages;
    this->pages = temp;
    ++this->totalPages;
    return true;
}

int User::getTotalPages(){
    return this->totalPages;
}

Page** User::getPages(){
    return this->pages;
}

void User::addMemories(Memory*memory){
    cout<<"Checkpoint e"<<endl;
    Memory** temp = new Memory * [this->totalMemories + 1];
    for (int i = 0; i < this->totalMemories; ++i) {
        temp[i] = this->memories[i];
        cout<<this->memories[i]->getPost()->getDescription()<<endl;
    }
    cout<<"Checkpoint f"<<endl;
    temp[this->totalMemories] = memory;
    delete[] this->memories;
    cout<<"Checkpoint g"<<endl;
    this->memories = temp;
    ++this->totalMemories;
    cout<<"Checkpoint h"<<endl;
}

int User::getTotalMemories(){
    return this->totalMemories;
}

Memory** User::getMemories(){
    return this->memories;
}

/*

SOCIAL NETWORK APP

*/


int SocialNetworkApp::getTotalUsers(){
    ifstream UserFile;
    UserFile.open("Users.txt");

    if (!UserFile.is_open()) {
        cout << "File is not open in getTotalUsers FUNCTION!!" << endl;
        return 0;
    }
    else {
        cout << "File is open" << endl;
    }
    int n;
    UserFile >> n;
    UserFile.close();
    this->totalUsers = n;
    return n;
}

void SocialNetworkApp::addUsers(){
    ifstream UserFile;
    UserFile.open("Users.txt");
    string s; double n1=0;
    UserFile >> n1;

    if (!UserFile.is_open()) {
        cout << "File is not open in addUsers function!!" << endl;
        return;
    }
    else {
        cout << "File is open" << endl;
    }
    users = new User*[this->totalUsers];
    for (int i = 0; i < this->totalUsers; i++)
    {
        UserFile >> n1;
        UserFile >> s;
        users[i] = new User(s, n1);
        cout << n1 << "\t";
        users[i]->setUserID(n1);
        cout << s << endl;
        users[i]->setName(s);
    }
    UserFile.close();
}

User** SocialNetworkApp::getUsers(){
    return this->users;
}

int SocialNetworkApp::returnTotalUsers(){
    return this->totalUsers;
}

bool SocialNetworkApp::setCurrentUser(string s){
    bool userFound = false;
    for (int i = 0; i < this->totalUsers; i++)
    {
        if (users[i]->getName() == s)
        {
            userFound = true;
            this->user = users[i];
            return true;
        }
    }
    cout << "User not found, Try again!" << endl;
    return false;
}

User* SocialNetworkApp::getOwner(){
    return user;
}

int SocialNetworkApp::addFriend(string s) {
    int n;
    for (int i = 0; i < this->totalUsers; i++)
    {
        if (users[i]->getName() == s)
        {
            if (users[i]==user)
            {
                cout << "You can not friend yourself! Try again!";
                return 2;
            }
            n = user->addFriend(users[i]);
            user->printFriends();
            if(!n){
                return 4;
            }
            return 1;
        }
    }
    cout << "User not found, Try again!" << endl;
    return 3;
}

void SocialNetworkApp::addUserPost(User*user,string s,int type,int value){
    user->addPost(user,s,type,value,date);
}

Date* SocialNetworkApp::getDateObject(){
    return this->date;
}

void SocialNetworkApp::setDateObject(){
    time_t now = time(0);
    tm* timeinfo = localtime(&now);

    // Extract the date, month, and year
    int year = 1900 + timeinfo->tm_year;
    int month = 1 + timeinfo->tm_mon;
    int day = timeinfo->tm_mday;

    date = new Date();
    date->setDate(day);
    date->setMonth(month);
    date->setYear(year);
}
/*

POST

*/

int Post::key = 1;


Post::Post(const User& user) : owner(new User(user)), likes(0), totalLikes(0), totalComments(0), comments(nullptr) {
    this->post_id = key;
    likedPeopleOnPost=nullptr;
    key++;
}

void Post::setDescription(string s) {
    this->description = s;
}

void Post::setActivity(int type,int value){
    this->activityType = type;
    this->activityValue = value;
}


double Post::getPostID(){
    return this->post_id;
}

string Post::getDescription(){
    return this->description;
}

int Post::getActivityType(){
    return this->activityType;
}

int Post::getActivityValue(){
    return this->activityValue;
}

void Post::setDate(int day,int month, int year){
    this->date.setDate(day);
    this->date.setMonth(month);
    this->date.setYear(year);
}

Date Post::getPostDate(){
    return date;
}

void Post::addLikeOnPost(User* whoLiked){
    for (int i = 0; i < totalLikes; ++i) {
        if (likedPeopleOnPost[i] == whoLiked) {
            return;
        }
    }
    User** temp = new User * [totalLikes + 1];
    for (int i = 0; i < totalLikes; ++i) {
        temp[i] = likedPeopleOnPost[i];
    }
    temp[totalLikes] = whoLiked;
    delete[] likedPeopleOnPost;
    likedPeopleOnPost = temp;
    ++totalLikes;
}

User* Post::getPostOwner(){
    return this->owner;
}

int Post::getLikes(){
    return this->totalLikes;
}

void Post::setOwner(User* user){
    this->owner = user;
}

User** Post::getLikedPeople(){
    return this->likedPeopleOnPost;
}

void Post::addCommentOnPost(Comment* comment){
    Comment** temp = new Comment * [totalComments + 1];
    for (int i = 0; i < totalComments; ++i) {
        temp[i] = comments[i];
    }
    temp[totalComments] = comment;
    delete[] comments;
    comments = temp;
    ++totalComments;
}

int Post::getTotalComments(){
    return this->totalComments;
}

/*

DATE

*/

void Date::setDate(int n){
    this->date = n;
}

void Date::setMonth(int n){
    this->month = n;
}

void Date::setYear(int n){
    this->year = n;
}

int Date::getDate(){
    return this->date;
}

int Date::getMonth(){
    return this->month;
}

int Date::getYear(){
    return this->year;
}

/*

COMMENTS

*/

void Comment::setComment(string s){
    cout<<"I am at checkpoint 2-a"<<endl;
    this->comment = s;
    cout<<"I am at checkpoint 2-b"<<endl;
}

string Comment::getComment(){
    return this->comment;
}

void Comment::setDate(Date* date1){
    this->date = date1;
}

void Comment::setWhoCommented(User* user){
    this->whoCommented = user;
}

User* Comment::getWhoCommented(){
    return this->whoCommented;
}

Comment** Post::getComments(){
    return this->comments;
}




/*

PAGE

*/

int Page::key = 1;

Post** Page::getPosts(){
    return this->posts;
}

void Page::addPost(Post* postToAdd){
    Post** temp = new Post * [this->totalPostsInPage + 1];
    for (int i = 0; i < this->totalPostsInPage; ++i) {
        temp[i] = this->posts[i];
    }
    temp[this->totalPostsInPage] = postToAdd;
    delete[] this->posts;
    this->posts = temp;
    ++this->totalPostsInPage;
}

int Page::getTotalPosts(){
    return this->totalPostsInPage;
}

string Page::getName(){
    return this->name;
}

void Page::setName(string s){
    this->name = s;
    this->PageID = key;
    key++;
}

void Page::setID(int n){
    this->PageID = n;
}

int Page::getID(){
    return this->PageID;
}

/*

MEMORY

*/

Memory::Memory(Post* post1, Date* oldDate1){
    this->post = post1;
    this->oldDate = oldDate1;
}

Date* Memory::getOldDate(){
    return this->oldDate;
}

Post* Memory::getPost(){
    return this->post;
}

void Memory::setOldDate(Date*date){
    this->oldDate = date;
}

void Memory::setPost(Post*post1){
    this->post = post1;
}
