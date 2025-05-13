#include "../Headers/eupage.h"
#include "ui_eupage.h"
#include "../Headers/messages.h"

eupage::eupage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::eupage)
    , banner(nullptr)
{
    ui->setupUi(this);
    setEditState(false);
}

eupage::~eupage()
{
    delete ui;
}

void eupage::setBanner(Banner *b)
{
    banner = b;
}


void eupage::on_deleteButton_clicked()
{
    int status = banner->deleteUser(username);

    if(status == 1) {
        showSuccess(this, "User has been deleted!");
        this->close();
    }else if (status == 0) {
        showError(this, "Cannot delete the current admin!");
    }
}


void eupage::on_searchButton_clicked()
{
    username = ui->usernamelineEdit->text();
    if(username == "") {
        showError(this, "You have to fill the username field");
        return;
    }
    user = banner->searchUser(username);
    if(user){
        setEditState(true);
        ui->namelineEdit->setText(user->getName());
        ui->passwordlineEdit->setText(user->getPassword());
        ui->idlineEdit->setText(user->getID());
        // ui->rolecomboBox->setCurrentIndex(user->getRole());
    } else {
        showError(this, "Entered username is not found!");
    }
}


void eupage::on_cancelButton_clicked()
{
    user = nullptr;
    setEditState(false);


    ui->usernamelineEdit->setText("");
    ui->namelineEdit->setText("");
    ui->passwordlineEdit->setText("");
    ui->idlineEdit->setText("");
    // ui->rolecomboBox->setCurrentIndex(0);
}


void eupage::on_clearButton_clicked()
{
    ui->namelineEdit->setText("");
    ui->passwordlineEdit->setText("");
    ui->idlineEdit->setText("");
    // ui->rolecomboBox->setCurrentIndex(0);
}


void eupage::on_updateButton_clicked()
{
    if (!isInputsFilled()){
        showError(this, "You have to fill all the inputs fields");
        return;
    }

    if(!banner->validatePassword(password)){
        showError(this, "Password is not valid!\nEnsure passwords consist of 8 characters and numbers.");
        return;
    }

    if (banner->updateUser(username,name,password,id)) {
        showSuccess(this, "User has been updated!");
        this->close();
    } else {
        showError(this, "Entered username is not found!");
    }

}


void eupage::setEditState(bool state) {
    ui->usernamelineEdit->setEnabled(!state);
    ui->searchButton->setEnabled(!state);

    ui->cancelButton->setEnabled(state);
    ui->updateButton->setEnabled(state);
    ui->deleteButton->setEnabled(state);
    ui->clearButton->setEnabled(state);

    ui->namelineEdit->setEnabled(state);
    ui->passwordlineEdit->setEnabled(state);
    ui->idlineEdit->setEnabled(state);
    // ui->rolecomboBox->setEnabled(state);
}

bool eupage::isInputsFilled()
{
    name = ui->namelineEdit->text();
    password = ui->passwordlineEdit->text();
    id = ui->idlineEdit->text();

    // QString roleText = ui->rolecomboBox->currentText();
    // if (roleText == "Admin")
    //     role = ADMIN;
    // else if (roleText == "Student")
    //     role = STUDENT;
    // else
    //     role = INSTRUCTOR;

    if(name == "")
        return false;
    if(password == "")
        return false;
    if(id == "")
        return false;

    return true;
}
