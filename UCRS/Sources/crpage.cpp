#include "../Headers/crpage.h"
#include "ui_crpage.h"

CRPage::CRPage(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CRPage)
{
    ui->setupUi(this);
}


CRPage::~CRPage()
{
    delete ui;
}

void CRPage::setBanner(Banner *b)
{
    banner = b;
}
