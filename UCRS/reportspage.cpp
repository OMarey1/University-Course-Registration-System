#include "reportspage.h"
#include "ui_reportspage.h"

ReportsPage::ReportsPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReportsPage)
{
    ui->setupUi(this);
}

ReportsPage::~ReportsPage()
{
    delete ui;
}
