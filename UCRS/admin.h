#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "instructor.h"
#include <vector>
using namespace std;

class Admin : public User
{
public:
    Admin(const QString& n, const QString& uname, const QString& pass, UserRole r):  User(n, uname, pass, r){};
    bool createUser(const QString& n, const QString& uname, const QString& pass, UserRole r);
    bool deleteUser(const QString& uname);
    bool validatePassword(const QString& pass);
    bool createCourse(const QString& id, const QString& name, const QString& ch, Instructor* inst, unsigned int cap, const QString& time, const QString& dep);
    bool deleteCourse(const QString& id);
    vector<User*> listUsers();
    bool saveUsersData();
};

#endif // ADMIN_H
