#include "ccpage.h"
#include "ui_ccpage.h"

CCPage::CCPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CCPage)
{
    ui->setupUi(this);
}

CCPage::~CCPage()
{
    delete ui;
}
