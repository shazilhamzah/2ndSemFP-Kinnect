    #ifndef MYCLASSES_H
#define MYCLASSES_H
#include<string>
using namespace std;

class User;
class Comment;
class Page;
class Memory;

class Date{
    int date;
    int month;
    int year;
public:
    void setDate(int);
    void setMonth(int);
    void setYear(int);
    int getDate();
    int getMonth();
    int getYear();
};

class Post{
    double post_id;
    User* owner;
    string description;
    int likes;
    User** likedPeopleOnPost;
    int totalLikes;
    static int key;
    int activityType;
    int activityValue;
    Date date;
    int totalComments;
    Comment** comments;

public:
    Post(const User& user);
    void setDescription(string s);
    void setActivity(int type,int value);
    double getPostID();
    string getDescription();
    int getActivityType();
    int getActivityValue();
    void setDate(int,int,int);
    Date getPostDate();
    void addLikeOnPost(User* whoLiked);
    int getLikes();
    User* getPostOwner();
    void setOwner(User*);
    User** getLikedPeople();
    ~Post();

    void addCommentOnPost(Comment* comment);
    int getTotalComments();
    Comment** getComments();
};

class User{
    double user_id;
    string name;
    User** friend_list;
    int totalFriends;
    Post** posts;
    int totalPosts;
    Page** pages;
    int totalPages;
    Memory** memories;
    int totalMemories;
public:
    User(string s,double n);
    void setUserID(double n);
    void setName(string n);
    string getName();
    double getUserID();
    bool addFriend(User* friendPtr);
    void printFriends();
    void addPost(User*,string s,int a,int b,Date*&);
    void viewHomePage();
    int getTotalPosts();
    User** getFriendList();
    int getTotalFriends();
    Post** getPosts();
    bool addPage(Page*);
    int getTotalPages();
    Page** getPages();
    void addMemories(Memory*);
    int getTotalMemories();
    Memory** getMemories();
};


class SocialNetworkApp{
    User** users;
    User* user;
    int totalUsers;
    Date* date;
public:
    int getTotalUsers();
    Date* getDateObject();
    void setDateObject();
    User** getUsers();
    static SocialNetworkApp instance;
    void addUsers();
    User* getOwner();
    void printUsers();
    bool setCurrentUser(string s);
    int returnTotalUsers();
    int addFriend(string s);
    void addUserPost(User*,string s,int type,int value);
};

class Page{
    Post** posts;
    string name;
    int totalPostsInPage;
    int PageID;
    static int key;
public:
    Post** getPosts();
    void addPost(Post*);
    int getTotalPosts();
    void setName(string);
    string getName();
    void setID(int);
    int getID();
};

class Comment{
    string comment;
    Date* date;
    User* whoCommented;
public:
    string getComment();
    void setComment(string);
    void setDate(Date*);
    void setWhoCommented(User*);
    User* getWhoCommented();
};

class Memory {
    Post* post;
    Date* oldDate;

public:
    Memory(Post* post, Date* oldDate);
    ~Memory();

    Post* getPost();
    Date* getOldDate();
    void setPost(Post* post);
    void setOldDate(Date* oldDate);
};

#endif // MYCLASSES_H
