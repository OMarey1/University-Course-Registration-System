#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "course.h"
#include <vector>
using namespace std;

class Student : public User
{
private:
    QString id;
    vector<Course*> registeredCourses;
public:
    Student(const QString& n, const QString& uname, const QString& pass, const QString& id, vector<Course*> courses):  User(n, uname, pass, STUDENT){this->id; this->registeredCourses = courses;};
    int getID() override {/*return id;*/}
    vector<Course*> getCourses() override {/*return courses;*/}
};

#endif // STUDENT_H
