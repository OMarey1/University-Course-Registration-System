#include "dashboard.h"
#include "ui_dashboard.h"
#include <QDate>

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

    User* user = banner->getCurrentUser();
    QString name = user ? user->getName() : "User";

    ui->welcomeLabel->setText("Welcome, " + name + "!");

    QString currentDate = QDate::currentDate().toString("dddd, MMMM d, yyyy");
    ui->dateTimeLabel->setText(currentDate);
}
