#include "../Headers/ccpage.h"
#include "ui_ccpage.h"
#include "../Headers/course.h"
#include "../Headers/messages.h"

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

void CCPage::on_clearButton_clicked()
{
    ui->namelineEdit->setText("");
    ui->idlineEdit->setText("");
    ui->creditHoursInput->setValue(ui->creditHoursInput->minimum());
    ui->capacityInput->setValue(ui->capacityInput->minimum());
    ui->instructorComboBox->setCurrentIndex(0);
    ui->dayComboBox->setCurrentIndex(0);
    ui->timeComboBox->setCurrentIndex(0);
    ui->depComboBox->setCurrentIndex(0);
}


void CCPage::on_createCourseButton_clicked()
{

    if (!isInputsFilled()){
        showError(this, "You have to fill all the inputs fields");
        return;
    }

    Instructor* instructor = dynamic_cast<Instructor*>( banner->search(instructorUsername));

    Course* newCourse = new Course(id,name,creditHours,instructor,capacity,schedule,dep);

    // if (banner->addCourse(newUser)) {
    //     showSuccess(this, "New course has been created!");
    //     this->close();
    // } else {
    //     delete newUser;
    //     showError(this, "Entered Course ID already exists!");
    // }

}

bool CCPage::isInputsFilled()
{
    name = ui->namelineEdit->text();
    id = ui->idlineEdit->text();
    creditHours = ui->creditHoursInput->value();
    instructorUsername =  ui->instructorComboBox->currentText();
    capacity = ui->capacityInput->value();
    day = ui->dayComboBox->currentText();
    time = ui->timeComboBox->currentText();
    dep = ui->depComboBox->currentText();
    schedule = day + "-" + time;

    if(name == "")
        return false;
    if(id == "")
        return false;
    if(instructorUsername == "")
        return false;
    if(day == "")
        return false;
    if(time == "")
        return false;
    if(dep == "")
        return false;

    return true;
}

