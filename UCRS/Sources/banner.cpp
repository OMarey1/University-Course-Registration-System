#include "../Headers/banner.h"
#include "../Headers/admin.h"
#include "../Headers/student.h"
#include "../Headers/instructor.h"
#include <fstream>
#include <QDebug>

bool Banner::saveUsersData()
{
    ofstream file("users.txt");

    if (!file.is_open()){
        return false;
    }
    // Write Rows Count At the Top of the file to fix the Loading issue casues by file.eof()
    int rowsCount = users.size();
    file << rowsCount << endl;
    // Header
    file << "Name Username Password Role ID Courses Number Courses IDs\n";

    for (auto& user: users) {
        file << user.second->getName().toStdString() << " "
             << user.second->getUsername().toStdString() << " "
             << user.second->getPassword().toStdString() << " "
             << user.second->getRole() << " "
             << user.second->getID().toStdString() << " ";
        vector<Course*> userCourses;
        if (user.second->getRole() == STUDENT) {
            userCourses = dynamic_cast<Student*>(user.second)->getCourses();
        } else if (user.second->getRole() == INSTRUCTOR) {
            userCourses = dynamic_cast<Instructor*>(user.second)->getCourses();
        }
        if (user.second->getRole() != ADMIN) {
            file << userCourses.size() << " " ;
            // for (auto& course: userCourses) {
            // file << course.getID() << " ";
            // }
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

    ifstream file("users.txt");

    if (!file.is_open()){
        return false;
    }

    int rowsCount;
    file >> rowsCount;
    qDebug() << rowsCount;

    string header;
    getline(file, header);
    string skipHeadaer;
    for(int i=0; i<9; i++) {
        file >> skipHeadaer;
        // qDebug() << headerFake;
    }

    int row = 0;
    while (row != rowsCount) {
        userCourses.clear();
        file >> name >> username >> password >> role >> id;
        // qDebug() << name;
        // qDebug() << username;
        // qDebug() << password;
        // qDebug() << role;
        role = (UserRole) role;
        if (role != ADMIN){
            file >> coursesNum;
            // Because of this I have to load the Courses from the file before loading the users
            for (int i = 0; i < coursesNum; ++i) {
                string courseId;
                file >> courseId;
                try {
                    userCourses.push_back(courses.at(QString::fromStdString(courseId)));
                } catch (const std::out_of_range&) {
                    qDebug() << "Missing course:" << courseId;
                    return false;
                }

            }
            if (role == STUDENT) {
                loadedUser = new Student(QString::fromStdString(name),QString::fromStdString(username),QString::fromStdString(password),QString::fromStdString(id), userCourses);
            } else if (role == INSTRUCTOR) {
                loadedUser = new Instructor(QString::fromStdString(name),QString::fromStdString(username),QString::fromStdString(password),QString::fromStdString(id), userCourses);
            }
        } else {
            loadedUser = new Admin(QString::fromStdString(name),QString::fromStdString(username),QString::fromStdString(password),QString::fromStdString(id));
        }
        users[QString::fromStdString(username)] = loadedUser;
        row++;
    }

    if(users.empty()) {
        return false;
    }
    return true;
}

Banner::Banner() {
    thisUser = nullptr;
    isAdmin = false;
    // User* adminUser = new Admin("Omar", "admin", "admin123");
    // users[adminUser->getUsername()] = adminUser;
    // qDebug() << users["admin"];
    // saveData();
    // loadData();
    if (!loadData()) {
        // default admin
        Admin* adminUser = new Admin("Omar", "admin", "admin123", "900158261");
        users[adminUser->getUsername()] = adminUser;
        // saveData();
    }
}

Banner::~Banner()
{
    saveData(); // Delete later when I add the save button on the ui
    // Free the memory
    delete thisUser;
    for (auto& u : users) delete u.second;
    for (auto& c : courses) delete c.second;
}

User *Banner::getCurrentUser()
{
    return thisUser;
}

int Banner::login(const QString &uname, const QString &pass)
{
    try {
        thisUser = users.at(uname);
        // qDebug() << thisUser;
        // qDebug() << thisUser->getPassword();
        // qDebug() << pass;
        if (thisUser->getPassword() == pass) {
            if (thisUser->getRole() == ADMIN) {
                isAdmin = true;
                // Admin
                // qDebug() << "Admin";
                return 1;
            } else {
                // Student or Instructor
                // qDebug() << "Student or Instructor";
                return 2;
            }
        } else {
            // Wrong Password
            // qDebug() << "Wrong Password";
            return 0;
        }
    } catch (const std::out_of_range & e) {
        // Username is not registered;
        return -1;
    }
}

void Banner::logout()
{
    thisUser=nullptr;
    isAdmin=false;
}

bool Banner::addUser(User *user)
{
    if(users[user->getUsername()]) {
        return false;
    } else {
        users[user->getUsername()] = user;
        return true;
    }
}

int Banner::deleteUser(const QString &username)
{
    try {
        if (thisUser->getUsername() == username){
            throw invalid_argument("Cannot delete the current admin!");
        }
        users.erase(username);
        return 1;
    } catch (const invalid_argument& e) {
        return 0;
    }
}

bool Banner::updateUser(const QString &username, const QString &name, const QString &pass, const QString &id)
{
    try {
        if (users.at(username)){
            users[username]->update(name,pass,id);
            return true;
        }
    } catch (const out_of_range & e) {
        // Username is not found;
        return false;
    }
    catch (...) {
        return false;
    }
}

User *Banner::search(const QString &username)
{
    try {
        return users.at(username);
    } catch (const out_of_range & e) {
        // Username is not found;
        return nullptr;
    }
}

// vector<User *> Banner::listUsers()
// {
//     qDebug() << users.size();
//     vector<User*> usersList;
//     usersList.resize(users.size());
//     for(const auto& u: users) {
//         usersList.push_back(u.second);
//     }
//     return usersList;
// }

map<QString, User*> Banner::listUsers() {
    return users;
}

bool Banner::validatePassword(const QString &pass)
{
    if (pass.length() != 8) {
        return false;
    }

    for (const QChar c: pass){
        if (!isalnum(c.toLatin1())){
            return false;
        }
    }
    return true;
}

bool Banner::loadData()
{
    // if (loadCoursesData()){
    if (loadUsersData()){
        return true;
    } else {
        return false;
    }
    // } else {
    // return false;
    // }
}

bool Banner::saveData()
{
    // if (saveCoursesData()){
    if (saveUsersData()){
        return true;
    } else {
        return false;
    }
    // } else {
    // return false;
    // }
}
