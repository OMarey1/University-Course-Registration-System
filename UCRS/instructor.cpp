#include "instructor.h"
#include "Course.h"
#include <vector>

Instructor::Instructor() : instructorID(0) {};
Instructor::Instructor(int ID)
{
    instructorID = ID;
}
int Instructor::getInstructorID() const
{
    return instructorID;
}
void Instructor::setInstructorID(int id)
{
    instructorID = id;
}
bool Instructor::addCourse(Course *course)
{
    if (course == nullptr)
    {
        return false;
    }
    for (size_t i = 0; i < assignedCourses.size(); i++)
    {
        if (assignedCourses.at(i) == course)
        {
            return false;
        }
    }
    assignedCourses.push_back(course);
    return true;
}
bool Instructor::removeCourse(Course *course)
{
    if (course == nullptr)
    {
        return false;
    }
    for (size_t i = 0; i < assignedCourses.size(); i++)
    {
        if (assignedCourses.at(i) == course)
        {
            assignedCourses.at(i) = assignedCourses.back();
            assignedCourses.pop_back();
        }
    }
    return false;
}
vector<Course *> Instructor::getCourses() const
{
    return assignedCourses;
}
Instructor::~Instructor() {};
