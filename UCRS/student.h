#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include <vector>
using namespace std;

class Course;

class Student : public User
{
private:
    vector<Course *> registeredCourses;

public:
    Student(const QString &n, const QString &uname, const QString &pass, const QString &id, vector<Course *> courses) : User(n, uname, pass, id, STUDENT) { this->registeredCourses = courses; };
    QString getStudentID() const;
    void setStudentID(QString ID);
    bool registerCourse(Course *course);
    bool dropCourse(Course *course);
    vector<Course *> getCourses() const;

    ~Student();
};

#endif // STUDENT_H
