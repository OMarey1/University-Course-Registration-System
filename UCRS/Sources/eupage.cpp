#include "../Headers/eupage.h"
#include "ui_eupage.h"
#include "../Headers/messages.h"

eupage::eupage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::eupage)
    , banner(nullptr)
{
    ui->setupUi(this);
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
    username =ui->usernamelineEdit->text();
    if(username == "") {
        showError(this, "You have to fill all the inputs fileds");
        return;
    }

    if(banner->deleteUser(username)) {
        showSuccess(this, "User has been deleted!");
        this->close();
    } else {
        showError(this, "Entered username is not found!");
    }
}

