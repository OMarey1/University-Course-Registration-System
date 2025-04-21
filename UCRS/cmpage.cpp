#include "cmpage.h"
#include "ui_cmpage.h"

CMPage::CMPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CMPage)
{
    ui->setupUi(this);
}

CMPage::~CMPage()
{
    delete ui;
}
