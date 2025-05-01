#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"
#include "course.h"

class Instructor : public User
{
private:
    vector<Course*> assignedCourses;
public:
    Instructor(const QString& n, const QString& uname, const QString& pass, const QString& id, vector<Course*> courses):  User(n, uname, pass, id, INSTRUCTOR){this->assignedCourses = courses;};
    vector<Course*> getCourses() {return assignedCourses;}
};

#endif // INSTRUCTOR_H
