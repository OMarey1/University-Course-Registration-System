#include "loginpage.h"
#include "ui_loginpage.h"
#include <QDebug>

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);

}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::setBanner(Banner *b)
{
    banner = b;
}

void LoginPage::on_loginButton_clicked()
{
    int loginResult;
    username = ui->usernameLineEdit->text();
    password = ui->passwordLineEdit->text();
    loginResult = banner->login(username, password);
    qDebug() << loginResult;
    switch (loginResult) {
    case -1:
    case 0:
        // Wrong Password;
        showError(this, "You have entered a wrong username or password");
        break;
    case 1:
        // Admin
        showSuccess(this, "Admin Logged in");
        break;
    case 2:
        // Student or Instructor
        showSuccess(this, "Regular user Logged in");
    }
}
