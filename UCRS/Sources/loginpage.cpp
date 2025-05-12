#include "../Headers/loginpage.h"
#include "ui_loginpage.h"
#include "../Headers/dashboard.h"
#include "../Headers/admindashboard.h"
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
    // showSuccess(this, (result == 1) ? "Admin Logged in" : "User Logged in");
    if (result == 1) {
        AdminDashboard* ad = new AdminDashboard(this);
        connect(ad, &QDialog::finished, this, &LoginPage::onChildDialogClosed);
        ad->setBanner(banner);
        ad->show();
        // this->close();
        this->hide();
    } else {
        // open regular Dashboard
        Dashboard* d = new Dashboard(this);
        connect(d, &QDialog::finished, this, &LoginPage::onChildDialogClosed);
        d->setBanner(banner);
        d->show();
        d->setAttribute(Qt::WA_DeleteOnClose);
    }
}

void LoginPage::onChildDialogClosed(int result)
{
    // this->show();
    qDebug() << "Closing App";
    this->show();
    this->close();
}
