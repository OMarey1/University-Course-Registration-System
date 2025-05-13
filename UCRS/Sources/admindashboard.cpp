#include "../Headers/admindashboard.h"
#include "ui_admindashboard.h"
#include "../Headers/student.h"
#include "../Headers/instructor.h"
#include "../Headers/messages.h"
#include "../Headers/cupage.h"
#include "../Headers/eupage.h"
#include "../Headers/ccpage.h"
#include "../Headers/cmpage.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminDashboard),
    banner(nullptr)
{
    ui->setupUi(this);
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::setBanner(Banner *b)
{
    banner = b;
    admin = dynamic_cast<Admin*>(banner->getCurrentUser());
    ui->welcomeLabel->setText("Welcome, " + admin->getName());
    fillUsersTable();
    fillCoursesTable();
}

void AdminDashboard::on_logoutButton_clicked()
{
    if(confirmAction(this, "Continue logging out?")){
        banner->logout();
        this->close();
        QWidget* p = qobject_cast<QWidget*>(parent());
        if (p) {
            p->show();
        }
    }
}

void AdminDashboard::fillUsersTable()
{
    auto usersList = banner->listUsers();

    ui->userTableWidget->clearContents();
    ui->userTableWidget->setRowCount(0);

    const QStringList headers = {"ID", "Name", "Username", "Password Validity", "Courses Number", "Role"};
    ui->userTableWidget->setHorizontalHeaderLabels(headers);
    ui->userTableWidget->setColumnCount(headers.size());

    const int rowCount = usersList.size();
    // qDebug() << rowCount;
    ui->userTableWidget->setRowCount(usersList.size());
    int row = 0;
    for (const auto& u : usersList) {
        User* user = u.second;
        ui->userTableWidget->setItem(row, 0, new QTableWidgetItem(user->getID()));
        ui->userTableWidget->setItem(row, 1, new QTableWidgetItem(user->getName()));
        ui->userTableWidget->setItem(row, 2, new QTableWidgetItem(user->getUsername()));
        // ui->userTableWidget->setItem(row, 3, new QTableWidgetItem(admin->validatePassword(user->getPassword()) ? "Valid" : "Not Valid"));
         ui->userTableWidget->setItem(row, 3, new QTableWidgetItem(banner->validatePassword(user->getPassword()) ? "Valid" : "Not Valid"));
        QString roleText;
        if(u.second->getRole() == ADMIN){
            roleText = "Admin";
            ui->userTableWidget->setItem(row, 4, new QTableWidgetItem("-"));
        }
        else if (u.second->getRole() == STUDENT){
            roleText = "Student";
            Student* s = dynamic_cast<Student*>(user);
            ui->userTableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(s->getCourses().size())));
        }
        else {
            roleText= "Instructor";
            Instructor* ins = dynamic_cast<Instructor*>(user);
            ui->userTableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(ins->getCourses().size())));
        }
        ui->userTableWidget->setItem(row, 5, new QTableWidgetItem(roleText));
        row++;
    }
    ui->userTableWidget->resizeColumnsToContents();
}

void AdminDashboard::fillCoursesTable()
{
    auto coursesList = banner->listCourses();

    ui->courseTableWidget->clearContents();
    ui->courseTableWidget->setRowCount(0);

    const QStringList headers = {"ID", "Name", "Department", "Credit Hours", "Instructor", "Schedule", "Enrolled Students", "Waiting List"};
    ui->courseTableWidget->setHorizontalHeaderLabels(headers);
    ui->courseTableWidget->setColumnCount(headers.size());

    ui->courseTableWidget->setRowCount(coursesList.size());
    int row = 0;
    for (const auto& c : coursesList) {
        Course* course = c.second;
        ui->courseTableWidget->setItem(row, 0, new QTableWidgetItem(course->getCourseID()));
        ui->courseTableWidget->setItem(row, 1, new QTableWidgetItem(course->getCourseName()));
        ui->courseTableWidget->setItem(row, 2, new QTableWidgetItem(course->getDepartment()));
        ui->courseTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(course->getCreditHours())));
        ui->courseTableWidget->setItem(row, 4, new QTableWidgetItem(course->getInstructor()->getUsername()));
        ui->courseTableWidget->setItem(row, 5, new QTableWidgetItem(course->getScheduleTime()));
        ui->courseTableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(course->getEnrolledStudents().size())));
        ui->courseTableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(course->getWaitingList().size())));
        row++;
    }
    ui->courseTableWidget->resizeColumnsToContents();
}


void AdminDashboard::on_reloadTableButton_clicked()
{
    fillUsersTable();
}


void AdminDashboard::on_addUserButton_clicked()
{
    cupage* cu = new cupage(this);
    cu->setModal(true);
    // connect the dialog’s finished() to your slot
    connect(cu, &QDialog::finished, this, &AdminDashboard::onChildDialogClosed);
    cu->setBanner(banner);
    cu->show();
    cu->setAttribute(Qt::WA_DeleteOnClose);
}


void AdminDashboard::on_editUserButton_clicked()
{
    eupage* eu = new eupage(this);
    eu->setModal(true);
    // connect the dialog’s finished() to your slot
    connect(eu, &QDialog::finished, this, &AdminDashboard::onChildDialogClosed);
    eu->setBanner(banner);
    eu->show();
    eu->setAttribute(Qt::WA_DeleteOnClose);
}


void AdminDashboard::on_addCourseButton_clicked()
{
    CCPage* cc = new CCPage(this);
    cc->setModal(true);
    // connect the dialog’s finished() to your slot
    connect(cc, &QDialog::finished, this, &AdminDashboard::onChildDialogClosed);
    cc->setBanner(banner);
    cc->show();
    cc->setAttribute(Qt::WA_DeleteOnClose);
}

void AdminDashboard::on_editCourseButton_clicked()
{
    CMPage* cm = new CMPage(this);
    cm->setModal(true);
    // connect the dialog’s finished() to your slot
    connect(cm, &QDialog::finished, this, &AdminDashboard::onChildDialogClosed);
    cm->setBanner(banner);
    cm->show();
    cm->setAttribute(Qt::WA_DeleteOnClose);
}

void AdminDashboard::on_reloadCoursesButton_clicked()
{
    fillCoursesTable();
}

void AdminDashboard::on_saveButton_clicked()
{
    banner->saveData();
}

void AdminDashboard::onChildDialogClosed(int result)
{
    // if (result == QDialog::Accepted) {
    //     user clicked “OK” (or dlg->accept())
    // } else {
    //     user clicked “Cancel” or closed the window
    // }
    fillUsersTable();
    fillCoursesTable();
}

