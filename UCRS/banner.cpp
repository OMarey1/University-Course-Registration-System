#include "banner.h"
#include "admin.h"
#include "student.h"
#include "instructor.h"
#include <fstream>

bool Banner::saveUsersData()
{
    ofstream file("users.csv");

    if (!file.is_open()){
        return false;
    }

    // Header
    file << "Name\tUsername\tPassword\tRole\tID\tCourses Number\tCourses IDs\n";

    for (auto& user: users) {
        file << user.second->getName().toStdString() << "\t"
             << user.second->getUsername().toStdString() << "\t"
             << user.second->getPassword().toStdString() << "\t"
             << user.second->getRole() << "\t";
        if (user.second->getRole() != ADMIN) {
            file << user.second->getID() << "\t";
            vector<Course*> userCourses = user.second->getCourses();
            file << userCourses.size() << "\t" ;
            for (auto& course: userCourses) {
                // file << course.getID() << " ";
            }
        }
        file << endl;
    }
    file.close();
    return true;
}

bool Banner::loadUsersData()
{
    string name, username, password, id;
    int role, coursesNum;
    vector<Course*> userCourses;
    User *loadedUser;

    ifstream file("users.csv");

    if (!file.is_open()){
        return false;
    }

    string header;
    getline(file, header);

    while (!file.eof()) {
        file >> name >> username >> password >> role;
        role = (UserRole) role;
        if (role != ADMIN){
            file >> id >> coursesNum;
            // Because of this I have to load the Courses from the file before loading the users
            for (int i = 0; i < coursesNum; ++i) {
                string courseId;
                file >> courseId;
                userCourses.push_back(courses.at(QString::fromStdString(courseId)));
            }
            if (role == STUDENT) {
                loadedUser = new Student(QString::fromStdString(name),QString::fromStdString(username),QString::fromStdString(password),QString::fromStdString(id), userCourses);
            } else if (role == INSTRUCTOR) {
                loadedUser = new Instructor(QString::fromStdString(name),QString::fromStdString(username),QString::fromStdString(password),QString::fromStdString(id), userCourses);
            }
        }
    }

    return true;
}

Banner::Banner() {
    thisUser = nullptr;
    isAdmin = false;
    loadData();
}

Banner::~Banner()
{
    saveData(); // Delete later when I add the save button on the ui
    // Free the memory
    delete thisUser;
    for (auto& u : users) delete u.second;
    for (auto& c : courses) delete c.second;
}

int Banner::login(const QString &uname, const QString &pass)
{
    try {
        // thisUser = users.at(uname.toStdString());
        if (thisUser->getPassword() == pass) {
            if (thisUser->getRole() == ADMIN) {
                isAdmin = true;
                // Admin
                return 1;
            } else {
                // Student or Instructor
                return 2;
            }
        } else {
            // Wrong Password
            return 0;
        }
    } catch (const std::out_of_range & e) {
        // Username is not registered;
        return -1;
    }
}

bool Banner::loadData()
{
    // loadCoursesData();
    loadUsersData();
}

bool Banner::saveData()
{
    saveUsersData();
}
