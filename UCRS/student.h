#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "Course.h"
#include<vector>
using namespace std;


class Student : public User
{
private:
    int studentID;
    vector <Course*> registeredCourses;

public:
    Student();
    Student(int ID);
    int getStudentID() const;
    void setStudentID(int ID);
    bool registerCourse(Course* course);
    bool dropCourse(Course* course);
    vector<Course*> getCourses() const;

    ~Student();
};

#endif // STUDENT_H
