    #include "../Headers/course.h"
#include "../Headers/student.h"
#include "../Headers/instructor.h"
#include <algorithm>

using namespace std;

Course::Course(const QString& id, const QString& name, unsigned int credits,
               Instructor* instructor, unsigned int cap, const QString& time,
               const QString& dept)
    : courseID(id), courseName(name), creditHours(credits), instructor(instructor),
    capacity(cap), scheduleTime(time), department(dept) {}

QString Course::getCourseID() const { return courseID; }

QString Course::getCourseName() const { return courseName; }

unsigned int Course::getCreditHours() const {
    return creditHours;
}

Instructor* Course::getInstructor() const {
    return instructor;
}

unsigned int Course::getCapacity() const {
    return capacity;
}

QString Course::getScheduleTime() const { return scheduleTime; }

QString Course::getDepartment() const { return department; }

vector<Student*> Course::getEnrolledStudents() const {
    return enrolledStudents;
}

vector<Student*> Course::getWaitingList() const {
    vector<Student*> waitingListVector;
    waitingListVector.reserve(waitingList.size());

    queue<Student*> temp = waitingList;
    while (!temp.empty()) {
        waitingListVector.push_back(temp.front());
        temp.pop();
    }
    return waitingListVector;
}

queue<Student *> Course::getWaitingListQueue() const
{
    return waitingList;
}

void Course::setInstructor(Instructor* instr) {
    instructor = instr;
}

void Course::setEnrolledStudents(const vector<Student*>& students) {
    enrolledStudents = students;
}

void Course::setWaitingList(const queue<Student*>& waiting) {
    waitingList = waiting;
}

void Course::update(const QString &name, unsigned int credits, Instructor *instr, unsigned int cap, const QString &time, const QString &dept)
{
    courseName = name;
    creditHours = credits;
    instructor = instr;
    capacity = cap;
    scheduleTime = time;
    department = dept;

}

int Course::getEnrolledStudentsNumber()const
{
    return static_cast<int>(enrolledStudents.size());

}

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

// bool Course::checkScheduleConflict(const QString& otherSchedule) const {
//     return scheduleTime == otherSchedule;
// }

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
