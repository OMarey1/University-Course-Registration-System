#include "../Headers/ccpage.h"
#include "ui_ccpage.h"
#include "../Headers/course.h"
#include "../Headers/messages.h"
#include "../Headers/instructor.h"

CCPage::CCPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CCPage)
{
    ui->setupUi(this);
}

CCPage::~CCPage()
{
    delete ui;
}

void CCPage::setBanner(Banner *b)
{
    banner = b;
    // Add Instructors
    auto users = banner->listUsers();
    for (const auto& user : users) {
        if (user.second->getRole() == INSTRUCTOR) {
            ui->instructorComboBox->addItem(user.second->getUsername());
        }
    }
    ui->depComboBox->clear();
    auto deps = banner->getDeps();
    for (const auto& dep : deps) {

        ui->depComboBox->addItem(dep);

    }
}

void CCPage::on_clearButton_clicked()
{
    ui->namelineEdit->setText("");
    ui->idlineEdit->setText("");
    ui->creditHoursInput->setValue(ui->creditHoursInput->minimum());
    ui->capacityInput->setValue(ui->capacityInput->minimum());
    ui->instructorComboBox->setCurrentIndex(0);
    ui->dayComboBox->setCurrentIndex(0);
    ui->timeComboBox->setCurrentIndex(0);
    ui->depComboBox->setCurrentIndex(0);
}


// void CCPage::on_createCourseButton_clicked()
// {

//     if (!isInputsFilled()){
//         showError(this, "You have to fill all the inputs fields");
//         return;
//     }

//     Instructor* instructor = dynamic_cast<Instructor*>(banner->searchUser(instructorUsername));
//     if (!instructor) {
//         showError(this, "Selected instructor not found!");
//         return;
//     }

//     Course* newCourse = new Course(id,name,creditHours,instructor,capacity,schedule,dep);

//     if (banner->createCourse(newCourse)) {
//         showSuccess(this, "New course has been created!");
//         this->close();
//     } else {
//         delete newCourse;
//         showError(this, "Entered Course ID already exists!");
//     }

// }


void CCPage::on_createCourseButton_clicked()
{
    if (!isInputsFilled()){
        showError(this, "You have to fill all the inputs fields");
        return;
    }

    Instructor* instructor = dynamic_cast<Instructor*>(banner->searchUser(instructorUsername));
    if (!instructor) {
        showError(this, "Selected instructor not found!");
        return;
    }

    // Check for duplicate course ID
    if (banner->searchCourse(id)) {
        showError(this, "A course with this ID already exists!");
        return;
    }

    // Check for schedule conflict for instructor
    const auto& allCourses = banner->listCourses();
    for (const auto& [_, course] : allCourses) {
        if (course->getInstructor() == instructor &&
            course->getScheduleTime() == schedule) {
            showError(this, "Schedule conflict: The instructor is already assigned to a course at this time.");
            return;
        }
    }

    // All checks passed; create course
    Course* newCourse = new Course(id, name, creditHours, instructor, capacity, schedule, dep);

    if (banner->createCourse(newCourse)) {
        showSuccess(this, "New course has been created!");
        this->close();
    } else {
        delete newCourse;
        showError(this, "Course creation failed due to an unknown error.");
    }
}

bool CCPage::isInputsFilled()
{
    name = ui->namelineEdit->text();
    id = ui->idlineEdit->text();
    creditHours = ui->creditHoursInput->value();
    instructorUsername =  ui->instructorComboBox->currentText();
    capacity = ui->capacityInput->value();
    day = ui->dayComboBox->currentText();
    time = ui->timeComboBox->currentText();
    dep = ui->depComboBox->currentText();
    schedule = day + "-" + time;

    if(name == "")
        return false;
    if(id == "")
        return false;
    if(instructorUsername == "")
        return false;
    if(day == "")
        return false;
    if(time == "")
        return false;
    if(dep == "")
        return false;

    return true;
}

