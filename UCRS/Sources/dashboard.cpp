#include "../Headers/dashboard.h"
#include "Headers/instructor.h"
#include "Headers/reportspage.h"
#include "ui_dashboard.h"
#include <QDate>
#include "../Headers/banner.h"
#include"../Headers/cmpage.h"
#include"../Headers/crpage.h"
#include "../Headers/user.h"
#include "../Headers/instructor.h"
#include "../Headers/loginpage.h"

Dashboard::Dashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setBanner(Banner *b)
{
    banner = b;
    auto courses=banner->listCourses();


    User* user = banner->getCurrentUser();
    QString name = user ? user->getName() : "User";

    ui->label->setText(QString::number(courses.size()));

    Instructor* instructor = dynamic_cast<Instructor*>(user);
    if(instructor)
    {
        auto instructorWorkload= instructor->getCourses();
        ui->registerCoursesButton->hide();
        ui->groupBox_3->setTitle("Instructors Workload");
        ui->label_3->setText(QString::number(instructorWorkload.size()));
    }
    Student* student= dynamic_cast<Student*>(user);
    if(student)
    {
        auto numberOfRegisteredCoursesStudent= student->getCourses();
        ui->groupBox_3->setTitle("Number of Registered Courses");
        ui->label_3->setText(QString::number(numberOfRegisteredCoursesStudent.size()));
    }

    ui->welcomeLabel->setText("Welcome, " + name + "!");

    QString currentDate = QDate::currentDate().toString("dddd, MMMM d, yyyy");
    ui->dateTimeLabel->setText(currentDate);
}
void Dashboard::on_reportsButton_clicked()
{
    ReportsPage* r= new ReportsPage(NULL);
    r -> setBanner(banner);
    this -> close();
    r -> show();
}


void Dashboard::on_registerCoursesButton_clicked()
{
    CRPage* cr = new CRPage(NULL);
    cr->setBanner(banner);
    this -> close();
    cr -> show();
}


void Dashboard::on_signOutButton_clicked()
{
    LoginPage* l = new LoginPage(NULL);
    l->setBanner(banner);
    this->close();
    l->show();
}

