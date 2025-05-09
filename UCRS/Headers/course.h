#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <queue>

using namespace std;

class Student;
class Instructor;

class Course {
private:
    string courseID;
    string courseName;
    unsigned int creditHours;
    Instructor* instructor;
    unsigned int capacity;
    string scheduleTime;
    string department;
    vector<Student*> enrolledStudents;
    queue<Student*> waitingList;
public:
    Course(const string& id, const string& name, unsigned int credits,
           Instructor* instructor, unsigned int cap, const string& time,
           const string& dept);
    
    // Getters
    string getCourseID() const;
    string getCourseName() const;
    unsigned int getCreditHours() const;
    Instructor* getInstructor() const;
    unsigned int getCapacity() const;
    string getScheduleTime() const;
    string getDepartment() const;
    vector<Student*> getEnrolledStudents() const;
    queue<Student*> getWaitingList() const;
    
    // Course operations
    bool enrollStudent(Student* student);
    bool dropStudent(Student* student);
    bool checkScheduleConflict(const string& otherSchedule) const;
    bool isFull() const;
    void processWaitingList();
};

#endif // COURSE_H
