#include "../Headers/cupage.h"
#include "ui_cupage.h"
#include "../Headers/admin.h"
#include "../Headers/student.h"
#include "../Headers/instructor.h"
#include "../Headers/messages.h"

cupage::cupage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cupage)
{
    ui->setupUi(this);
}

cupage::~cupage()
{
    delete ui;
}

void cupage::setBanner(Banner *b)
{
    banner = b;
}

void cupage::on_createUserButton_clicked()
{
    if (!isInputsFilled()){
        showError(this, "You have to fill all the inputs fields");
        return;
    }

    User* newUser = nullptr;

    if(!banner->validatePassword(password)){
        showError(this, "Password is not valid!\nEnsure passwords consist of 8 characters and numbers.");
        return;
    }

    switch (role) {
    case ADMIN:
        newUser = new Admin(name, username, password, id);
        break;
    case STUDENT:
        newUser = new Student(name, username, password, id, std::vector<Course*>{});
        break;
    case INSTRUCTOR:
        newUser = new Instructor(name, username, password, id, std::vector<Course*>{});
        break;
    }
    if (banner->addUser(newUser)) {
        showSuccess(this, "New user has been created!");
        this->close();
    } else {
        delete newUser;
        showError(this, "Entered username is already registered!");
    }

}

bool cupage::isInputsFilled()
{
    name = ui->namelineEdit->text();
    username = ui->usernamelineEdit->text();
    password = ui->passwordlineEdit->text();
    id = ui->idlineEdit->text();
    QString roleText = ui->rolecomboBox->currentText();
    if (roleText == "Admin")
        role = ADMIN;
    else if (roleText == "Student")
        role = STUDENT;
    else
        role = INSTRUCTOR;

    if(name == "")
        return false;
    if(username == "")
        return false;
    if(password == "")
        return false;
    if(id == "")
        return false;

    return true;
}



void cupage::on_clearButton_clicked()
{
    ui->namelineEdit->setText("");
    ui->usernamelineEdit->setText("");
    ui->passwordlineEdit->setText("");
    ui->idlineEdit->setText("");
    ui->rolecomboBox->setCurrentIndex(0);
}

