#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

class Student : public User
{
public:
    Student(const QString& n, const QString& uname, const QString& pass, UserRole r):  User(n, uname, pass, r){};
};

#endif // STUDENT_H
