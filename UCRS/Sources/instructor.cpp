#include "../Headers/instructor.h"
#include "../Headers/course.h"
#include <vector>

QString Instructor::getInstructorID() const
{
    return id;
}
void Instructor::setInstructorID(QString id)
{
    id = id;
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
