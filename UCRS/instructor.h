#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"

class Instructor : public User
{
private:
    QString id;
    vector<Course*> assignedCourses;
public:
    Instructor(const QString& n, const QString& uname, const QString& pass, const QString& id, vector<Course*> courses):  User(n, uname, pass, INSTRUCTOR){this->id; this->assignedCourses = courses;};
    int getID() override {/*return id;*/}
    vector<Course*> getCourses() override {/*return courses;*/}
};

#endif // INSTRUCTOR_H
