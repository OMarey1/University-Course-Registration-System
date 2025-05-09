#include "../Headers/student.h"
#include "../Headers/course.h"
#include <vector>
using namespace std;

QString Student::getStudentID() const
{
    return id;
}
void Student::setStudentID(QString ID)
{
   id = ID;
}
bool Student::registerCourse(Course *course)
{
    if (course == nullptr)
    {
        return false;
    }
    for (size_t i = 0; i < registeredCourses.size(); i++)
    {
        if (registeredCourses.at(i) == course)
        {
            return false;
        }
    }
    registeredCourses.push_back(course);
    return true;
}
bool Student::dropCourse(Course *course)
{
    if (course == nullptr)
    {
        return false;
    }
    for (size_t i = 0; i < registeredCourses.size(); i++)
    {
        if (registeredCourses.at(i) == course)
        {
            registeredCourses.at(i) = registeredCourses.back();
            registeredCourses.pop_back();
            return true;
        }
    }
    return false;
}
vector<Course *> Student::getCourses() const
{
    return registeredCourses;
}
Student::~Student() {}
