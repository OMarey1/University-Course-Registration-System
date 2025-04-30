#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"
#include "Course.h"
#include <vector>
using namespace std;


class Instructor : public User
{
private:
    int instructorID;
    vector<Course*> assignedCourses;

public:
    Instructor();
    Instructor(int ID);
    int getInstructorID() const;
    void setInstructorID(int id);
    bool addCourse(Course* course);
    bool removeCourse(Course* course);
    vector<Course*> getCourses() const;
    ~Instructor();
};

#endif // INSTRUCTOR_H
