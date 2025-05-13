#include "../Headers/banner.h"
#include "../Headers/admin.h"
#include "../Headers/student.h"
#include "../Headers/instructor.h"
#include <sstream>
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
    file << "Name|Username|Password|Role|ID|Courses_Number|Courses_IDs\n";

    for (auto& user: users) {
        file << user.second->getName().toStdString() << "|"
             << user.second->getUsername().toStdString() << "|"
             << user.second->getPassword().toStdString() << "|"
             << user.second->getRole() << "|"
             << user.second->getID().toStdString() << "|";
        vector<Course*> userCourses;
        if (user.second->getRole() == STUDENT) {
            userCourses = dynamic_cast<Student*>(user.second)->getCourses();
        } else if (user.second->getRole() == INSTRUCTOR) {
            userCourses = dynamic_cast<Instructor*>(user.second)->getCourses();
        }
        if (user.second->getRole() != ADMIN) {
            file << userCourses.size() << "|" ;
            for (auto& course: userCourses) {
            file << course->getCourseID().toStdString() << "|";
            }
        }
        file << endl;
    }
    file.close();
    return true;
}

bool Banner::loadUsersData()
{
    string line, name, username, password, id;
    int role, coursesNum;
    vector<Course*> userCourses;
    User *loadedUser;

    ifstream file("users.txt");

    if (!file.is_open()){
        return false;
    }

    int rowsCount;
    file >> rowsCount;
    // Skip header line
    getline(file, line);
    getline(file, line);

    int row = 0;
    while (row != rowsCount && getline(file, line)) {
        userCourses.clear();
        stringstream ss(line);
        string field;

        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, field, '|');
        role = stoi(field);
        getline(ss, id, '|');

        role = (UserRole) role;
        if (role != ADMIN){
            // Parse courses number
            getline(ss, field, '|');
            coursesNum = stoi(field);
            // Because of this I have to load the Courses from the file before loading the users
            for (int i = 0; i < coursesNum; ++i) {
                string courseId;
                getline(ss, courseId, '|');
                // qDebug() << courseId;
                try {
                    userCourses.push_back(courses.at(QString::fromStdString(courseId)));
                } catch (const std::out_of_range&) {
                    qDebug() << "Missing course:" << courseId;
                    // return false;
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

bool Banner::saveCoursesData()
{
    ofstream file("courses.txt");

    if (!file.is_open()){
        return false;
    }
    // Write Rows Count At the Top of the file to fix the Loading issue casues by file.eof()
    int rowsCount = courses.size();
    file << rowsCount << endl;
    // Header
    file << "ID|Name|Department|Credit_Hours|Capacity|Instructor_Username|Time|En_Students_Num|En_Students_Usernames|Waiting_Students_Num|Waiting_Students_Usernames\n";

    for (auto& course: courses) {
        file << course.second->getCourseID().toStdString() << "|"
             << course.second->getCourseName().toStdString() << "|"
             << course.second->getDepartment().toStdString() << "|"
             << course.second->getCreditHours() << "|"
             << course.second->getCapacity() << "|"
             << course.second->getInstructor()->getUsername().toStdString() << "|"
             << course.second->getScheduleTime().toStdString() << "|";

        file << course.second->getEnrolledStudents().size() << "|";
        for (auto& student: course.second->getEnrolledStudents()) {
            file << student->getUsername().toStdString() << "|";
        }

        file << course.second->getWaitingList().size() << "|";
        for (auto& student: course.second->getWaitingList()) {
            file << student->getUsername().toStdString() << "|";
        }
        file << endl;
    }
    file.close();
    return true;
}

bool Banner::loadCoursesData()
{
    QString empty = "";
    string line, name, id, schedule, dep, instructorUsername;
    unsigned int creditHours, capacity;
    int enStudentsNum, waitingStudentsNum;
    vector<Student*> enrolledStudents;
    queue<Student*> waitingList;
    Course *loadedCourse;

    ifstream file("courses.txt");

    if (!file.is_open()){
        return false;
    }

    int rowsCount;
    file >> rowsCount;
    // Skip header line
    getline(file, line);
    getline(file, line);

    int row = 0;
    while (row != rowsCount && getline(file, line)) {
        enrolledStudents.clear();
        waitingList = queue<Student*>();

        stringstream ss(line);
        string field;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, dep, '|');
        // Parse credit hours
        getline(ss, field, '|');
        creditHours = stoi(field);
        // Parse capacity
        getline(ss, field, '|');
        capacity = stoi(field);
        getline(ss, instructorUsername, '|');
        getline(ss, schedule, '|');

        // Create a temporary instructor pointer (will be updated later)
        Instructor* tempInstructor = new Instructor(empty, QString::fromStdString(instructorUsername), empty, empty, vector<Course*>());

        // Create the course with temporary instructor
        loadedCourse = new Course(
            QString::fromStdString(id),
            QString::fromStdString(name),
            creditHours,
            tempInstructor,
            capacity,
            QString::fromStdString(schedule),
            QString::fromStdString(dep)
            );

        // Read enrolled students
        getline(ss, field, '|');
        enStudentsNum = stoi(field);
        for (int i = 0; i < enStudentsNum; ++i) {
            string studentUsername;
            getline(ss, studentUsername, '|');
            // Create temporary student (will be updated later)
            Student* tempStudent = new Student(empty, QString::fromStdString(studentUsername), empty, empty, vector<Course*>());
            enrolledStudents.push_back(tempStudent);
        }
        loadedCourse->setEnrolledStudents(enrolledStudents);

        // Read waiting list
        getline(ss, field, '|');
        waitingStudentsNum = stoi(field);
        for (int i = 0; i < waitingStudentsNum; ++i) {
            string studentUsername;
            getline(ss, studentUsername, '|');
            // Create temporary student (will be updated later)
            Student* tempStudent = new Student(empty, QString::fromStdString(studentUsername), empty, empty, vector<Course*>());
            waitingList.push(tempStudent);
        }
        loadedCourse->setWaitingList(waitingList);

        // Add course to the map
        courses[QString::fromStdString(id)] = loadedCourse;
        row++;
    }

    if(courses.empty()) {
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

    departments = {"Accounting", "Architecture", "ALI", "Biology", "Chemistry", "CS&CE", "Business", "Economics", "Electronics", "Mechanical", "ELI", "Rhet"};
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

vector<QString> Banner::getDeps() const
{
    return departments;
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

User *Banner::searchUser(const QString &username)
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

bool Banner::createCourse(Course *course)
{
    if(courses[course->getCourseID()]) {
        return false;
    } else {
        courses[course->getCourseID()] = course;
        // Add the course to the instructor's assigned courses
        Instructor* instructor = course->getInstructor();
        if (instructor) {
            instructor->addCourse(course);
        }
        return true;
    }
}

bool Banner::deleteCourse(const QString &id)
{
    try {
        courses.erase(id);
        return 1;
    } catch (const invalid_argument& e) {
        return 0;
    }
}

Course *Banner::searchCourse(const QString &id)
{
    try {
        return courses.at(id);
    } catch (const out_of_range & e) {
        // Course is not found;
        return nullptr;
    }
}

map<QString, Course *> Banner::listCourses()
{
    return courses;
}

bool Banner::loadData()
{
    // First load courses without user references
    if (!loadCoursesData()) {
        return false;
    }

    // Then load users with their course references
    if (!loadUsersData()) {
        return false;
    }

    // Finally, update course references with user data
    if (!updateCourseReferences()) {
        return false;
    }

    return true;
}

bool Banner::updateCourseReferences()
{
    for (auto& course : courses) {
        // Update instructor reference
        QString instructorUsername = course.second->getInstructor()->getUsername();
        try {
            Instructor* instructor = dynamic_cast<Instructor*>(users.at(instructorUsername));
            if (instructor) {
                course.second->setInstructor(instructor);
            }
        } catch (const std::out_of_range&) {
            qDebug() << "Missing instructor:" << instructorUsername;
            return false;
        }

        // Update enrolled students references
        vector<Student*> enrolledStudents;
        for (auto& student : course.second->getEnrolledStudents()) {
            QString studentUsername = student->getUsername();
            try {
                Student* s = dynamic_cast<Student*>(users.at(studentUsername));
                if (s) {
                    enrolledStudents.push_back(s);
                }
            } catch (const std::out_of_range&) {
                qDebug() << "Missing enrolled student:" << studentUsername;
                return false;
            }
        }
        course.second->setEnrolledStudents(enrolledStudents);

        // Update waiting list references
        queue<Student*> waitingList;
        for (auto& student : course.second->getWaitingList()) {
            QString studentUsername = student->getUsername();
            try {
                Student* s = dynamic_cast<Student*>(users.at(studentUsername));
                if (s) {
                    waitingList.push(s);
                }
            } catch (const std::out_of_range&) {
                qDebug() << "Missing waiting student:" << studentUsername;
                return false;
            }
        }
        course.second->setWaitingList(waitingList);
    }
    return true;
}

bool Banner::saveData()
{
    if (saveCoursesData() && saveUsersData()){
        qDebug() << "Saved Data Successfully!";
        return true;
    } else {
        return false;
    }
}

map<QString,Instructor*> Banner::listInstructors()
{
    return instructors;
}
