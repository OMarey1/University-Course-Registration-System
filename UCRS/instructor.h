#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"

class Instructor : public User
{
public:
    Instructor(const QString& n, const QString& uname, const QString& pass, UserRole r):  User(n, uname, pass, r){};
};

#endif // INSTRUCTOR_H
