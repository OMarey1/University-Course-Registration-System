#include "reportspage.h"
#include "ui_reportspage.h"

ReportsPage::ReportsPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReportsPage)
{
    ui->setupUi(this);
    ui->comboBoxReportType->addItem("Student Schedule");
    ui->comboBoxReportType->addItem("Course Enrollment");
    ui->comboBoxReportType->addItem("Instructor Workload");

}

ReportsPage::~ReportsPage()
{
    delete ui;
}


