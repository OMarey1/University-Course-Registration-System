#include "dashboard.h"
#include "ui_dashboard.h"
#include <QDate>

Dashboard::Dashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    // These will be set after setBanner() is called
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setBanner(Banner *b)
{
    banner = b;

    // 1. Get the current user (assuming Banner has getCurrentUser())
    User* user = banner->getCurrentUser();
    QString name = user ? user->getName() : "User";

    // 2. Set the welcome label text (replace "welcomeLabel" with your QLabel's objectName)
    ui->welcomeLabel->setText("Welcome, " + name + "!");

    // 3. Set the date label text (replace "dateTimeLabel" with your QLabel's objectName)
    QString currentDate = QDate::currentDate().toString("dddd, MMMM d, yyyy");
    ui->dateTimeLabel->setText(currentDate);
}
