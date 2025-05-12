#ifndef BANNER_H
#define BANNER_H

#include "user.h"
#include "course.h"
#include <map>

using namespace std;

class Banner
{
private:
    map<QString, User*> users;
    map<QString, Course*> courses;
    User* thisUser;
    bool isAdmin;

    bool saveUsersData();
    bool loadUsersData();
    bool saveCoursesData();
    // bool loadCoursesData();
public:
    Banner();
    ~Banner();
    User* getCurrentUser();
    int login(const QString& uname, const QString& pass);
    void logout();
    bool addUser(User* user);
    int deleteUser(const QString& username);
    bool updateUser(const QString& username, const QString& name, const QString& pass, const QString& id);
    User* search(const QString& username);
    // vector<User*> listUsers();
    map<QString, User*> listUsers();
    bool validatePassword(const QString& pass);
    bool createCourse(Course* course);
    // bool deleteCourse (const QString& id);
    // Course searchCourse();
    // bool generateReport();
    bool loadData();
    bool saveData();
};

#endif // BANNER_H
