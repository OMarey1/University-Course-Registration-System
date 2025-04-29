#include "student.h"
#include "Course.h"
#include <vector>
using namespace std;

Student::Student(): studentID(0){};
Student::Student(int ID):studentID(ID){};
int Student::getStudentID() const{
    return studentID;
}
void Student::setStudentID(int ID){
    studentID=ID;
}
bool Student::registerCourse(Course*course){
    if (course == nullptr) {
        return false;
    }
    for (size_t i = 0; i < registeredCourses.size(); i++){
        if(registeredCourses[i] == course){
            return false;
        }
    }
    registeredCourses.push_back(course);
    return true;
}
bool Student::dropCourse(Course*course){
    if (course == nullptr){
        return false;
    }
    for(size_t i = 0; i < registeredCourses.size();i++){
        if(registeredCourses[i] == course) {
            registeredCourses[i] = registeredCourses.back();
            registeredCourses.pop_back();
            return true;
        }
    }
    return false;
}
vector <Course*> Student::getCourses() const {
    return registeredCourses;
}
Student::~Student(){}
