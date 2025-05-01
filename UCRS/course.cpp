#include "course.h"
#include <algorithm>

using namespace std;

Course::Course(const string& id, const string& name, unsigned int credits,
               Instructor* instructor, unsigned int cap, const string& time,
               const string& dept)
    : courseID(id), courseName(name), creditHours(credits), instructor(instructor),
      capacity(cap), scheduleTime(time), department(dept) {}

string Course::getCourseID() const { return courseID; }
string Course::getCourseName() const { return courseName; }
unsigned int Course::getCreditHours() const { return creditHours; }
Instructor* Course::getInstructor() const { return instructor; }
unsigned int Course::getCapacity() const { return capacity; }
string Course::getScheduleTime() const { return scheduleTime; }
string Course::getDepartment() const { return department; }
vector<Student*> Course::getEnrolledStudents() const { return enrolledStudents; }
queue<Student*> Course::getWaitingList() const { return waitingList; }

bool Course::enrollStudent(Student* student) {
    // Check if already enrolled
    for (Student* s : enrolledStudents) {
        if (s == student) return false;
    }
    
    if (enrolledStudents.size() < capacity) {
        enrolledStudents.push_back(student);
        return true;
    } else {
        waitingList.push(student);
        return false;
    }
}

bool Course::dropStudent(Student* student) {
    auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);
        processWaitingList();
        return true;
    }
    return false;
}

bool Course::checkScheduleConflict(const string& otherSchedule) const {
    return scheduleTime == otherSchedule;
}

bool Course::isFull() const {
    return enrolledStudents.size() >= capacity;
}

void Course::processWaitingList() {
    while (!waitingList.empty() && enrolledStudents.size() < capacity) {
        Student* student = waitingList.front();
        waitingList.pop();
        enrolledStudents.push_back(student);
    }
}
