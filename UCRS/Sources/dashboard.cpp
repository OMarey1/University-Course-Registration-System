#include "../Headers/dashboard.h"
#include "Headers/instructor.h"
#include "Headers/reportspage.h"
#include "ui_dashboard.h"
#include <QDate>
#include "../Headers/banner.h"
#include"../Headers/cmpage.h"
#include"../Headers/crpage.h"
#include "../Headers/user.h"
#include "../Headers/instructor.h"

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

    Instructor* instructor = dynamic_cast<Instructor*>(user);
    if(instructor)
    {
        ui->registerCoursesButton->hide();
    }

    ui->welcomeLabel->setText("Welcome, " + name + "!");

    QString currentDate = QDate::currentDate().toString("dddd, MMMM d, yyyy");
    ui->dateTimeLabel->setText(currentDate);
}
void Dashboard::on_manageCoursesButton_clicked()
{
    //CMPage* cm=new CMPage(this);
    //cm->setBanner(banner);
    //this -> close();
    //cm -> show();
}


void Dashboard::on_reportsButton_clicked()
{
    ReportsPage* r= new ReportsPage(this);
    r -> setBanner(banner);
    this -> close();
    r -> show();
}


void Dashboard::on_registerCoursesButton_clicked()
{
    //CRPage* cr = new CRPage(this);
    //cr->setBanner(banner);
    //this -> close();
    //cr -> show();
}

