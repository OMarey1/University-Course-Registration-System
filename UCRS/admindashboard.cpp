#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "cupage.h"
#include "eupage.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminDashboard),
    banner(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose);
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::setBanner(Banner *b)
{
    banner = b;
    admin = dynamic_cast<Admin*>(banner->getCurrentUser());
    fillUsersTable();
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
    qDebug() << rowCount;
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


void AdminDashboard::on_reloadTableButton_clicked()
{
    fillUsersTable();
}


void AdminDashboard::on_addUserButton_clicked()
{
    cupage* cu = new cupage(this);
    cu->setBanner(banner);
    cu->show();
}


void AdminDashboard::on_editUserButton_clicked()
{
    eupage* eu = new eupage(this);
    eu->setBanner(banner);
    eu->show();
}


void AdminDashboard::on_saveButton_clicked()
{
    banner->saveData();
}

