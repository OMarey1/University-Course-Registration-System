#include "loginpage.h"
#include "ui_loginpage.h"
#include "dashboard.h"
#include "admindashboard.h"
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
    QString uname = ui->usernameLineEdit->text();
    QString pass = ui->passwordLineEdit->text();
    int result = banner->login(uname, pass);
    if (result < 1) {
        showError(this, "Wrong username or password");
        return;
    }
    showSuccess(this, (result == 1) ? "Admin Logged in" : "User Logged in");
    if (result == 1) {
        AdminDashboard* ad = new AdminDashboard(this);
        ad->setBanner(banner);
        this->close();
        ad->show();
    } else {
        // open regular Dashboard
        Dashboard* d = new Dashboard(this);
        d->setBanner(banner);
        this->close();
        d->show();
    }
}
