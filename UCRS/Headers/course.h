#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <vector>
#include <queue>

using namespace std;

class Student;
class Instructor;

class Course {
private:
    QString courseID;
    QString courseName;
    unsigned int creditHours;
    Instructor* instructor;
    unsigned int capacity;
    QString scheduleTime;
    QString department;
    vector<Student*> enrolledStudents;
    queue<Student*> waitingList;
public:
    Course(const QString& id, const QString& name, unsigned int credits,
           Instructor* instructor, unsigned int cap, const QString& time,
           const QString& dept);
    
    // Getters
    QString getCourseID() const;
    QString getCourseName() const;
    unsigned int getCreditHours() const;
    Instructor* getInstructor() const;
    unsigned int getCapacity() const;
    QString getScheduleTime() const;
    QString getDepartment() const;
    vector<Student*> getEnrolledStudents() const;
    vector<Student*> getWaitingList() const;

    // Setters
    void setInstructor(Instructor* instr);
    void setEnrolledStudents(const vector<Student*>& students);
    void setWaitingList(const queue<Student*>& waiting);
    
    // Course operations
    bool enrollStudent(Student* student);
    bool dropStudent(Student* student);
    bool checkScheduleConflict(const string& otherSchedule) const;
    bool isFull() const;
    void processWaitingList();
};

#endif // COURSE_H
