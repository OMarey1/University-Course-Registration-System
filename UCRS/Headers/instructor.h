#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"

class Course;

class Instructor : public User
{
private:
    vector<Course *> assignedCourses;

public:
    Instructor(const QString &n, const QString &uname, const QString &pass, const QString &id, vector<Course *> courses) : User(n, uname, pass, id, INSTRUCTOR) { this->assignedCourses = courses; };
    QString getInstructorID() const;
    void setInstructorID(QString id);
    bool addCourse(Course *course);
    bool removeCourse(Course *course);
    vector<Course *> getCourses() const;
    ~Instructor();
};

#endif // INSTRUCTOR_H
