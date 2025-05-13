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
    bool loadCoursesData();
<<<<<<< HEAD
    bool updateCourseReferences();
=======
>>>>>>> 5c1cd429df271dfcc89f040589f70f3862f8ff8a
public:
    Banner();
    ~Banner();
    User* getCurrentUser();
    int login(const QString& uname, const QString& pass);
    void logout();
    bool addUser(User* user);
    int deleteUser(const QString& username);
    bool updateUser(const QString& username, const QString& name, const QString& pass, const QString& id);
    User* searchUser(const QString& username);
    map<QString, User*> listUsers();
    bool validatePassword(const QString& pass);
<<<<<<< HEAD
    bool createCourse(Course* course);
    // bool deleteCourse (const QString& id);
    // Course searchCourse();
    map<QString, Course*> listCourses();
    // bool generateReport();
=======
    bool createCourse(Course course);
    bool deleteCourse (const QString& id);
    Course searchCourse();
    bool generateReport();
>>>>>>> 5c1cd429df271dfcc89f040589f70f3862f8ff8a
    bool loadData();
    bool saveData();
};

#endif // BANNER_H
