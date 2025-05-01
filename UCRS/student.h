#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "course.h"
#include <vector>
using namespace std;

class Student : public User
{
private:
    vector<Course*> registeredCourses;
public:
    Student(const QString& n, const QString& uname, const QString& pass, const QString& id, vector<Course*> courses):  User(n, uname, pass, id, STUDENT){this->registeredCourses = courses;};
    vector<Course*> getCourses() {return registeredCourses;}
};

#endif // STUDENT_H
