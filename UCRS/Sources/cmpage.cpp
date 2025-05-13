#include "../Headers/cmpage.h"
#include "ui_cmpage.h"
#include "../Headers/instructor.h"
#include "../Headers/student.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QComboBox>
#include "../Headers/dashboard.h"

CMPage::CMPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CMPage)
    , banner(nullptr)
{
    ui->setupUi(this);
    // connect(ui->editCourseButton, &QPushButton::clicked, this, &CMPage::on_editCourseButton_clicked);
    // connect(ui->deleteCourseButton, &QPushButton::clicked, this, &CMPage::on_deleteCourseButton_clicked);
    // connect(ui->searchButton, &QPushButton::clicked, this, &CMPage::on_searchButton_clicked);
    // connect(ui->coursesTable, &QTableWidget::itemSelectionChanged, this, &CMPage::on_coursesTable_itemSelectionChanged);
}

CMPage::~CMPage()
{
    delete ui;
}

void CMPage::setBanner(Banner* b) {
    banner = b;
    populateCoursesTable();
}

void CMPage::populateCoursesTable(const QString& instructorFilter, const QString& departmentFilter, const QString& timeFilter) {
    if (!banner) return;

    ui->coursesTable->setRowCount(0);
    auto courses = banner->listCourses();

    for (const auto& pair : courses) {
        Course* course = pair.second;
        QString instructorName = course->getInstructor()->getName();
        QString department = course->getDepartment();
        QString schedule = course->getScheduleTime();

        if (!instructorFilter.isEmpty() && !instructorName.contains(instructorFilter, Qt::CaseInsensitive))
            continue;
        if (!departmentFilter.isEmpty() && department != departmentFilter)
            continue;
        if (!timeFilter.isEmpty() && schedule != timeFilter)
            continue;

        int row = ui->coursesTable->rowCount();
        ui->coursesTable->insertRow(row);
        ui->coursesTable->setItem(row, 0, new QTableWidgetItem(course->getCourseID()));
        ui->coursesTable->setItem(row, 1, new QTableWidgetItem(course->getCourseName()));
        ui->coursesTable->setItem(row, 2, new QTableWidgetItem(instructorName));
        ui->coursesTable->setItem(row, 3, new QTableWidgetItem(QString::number(course->getCreditHours())));
        ui->coursesTable->setItem(row, 4, new QTableWidgetItem(schedule));
        ui->coursesTable->setItem(row, 5, new QTableWidgetItem(QString::number(course->getCapacity())));
    }
}

void CMPage::on_editCourseButton_clicked() {
    QList<QTableWidgetItem*> selectedItems = ui->coursesTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a course to edit.");
        return;
    }

    int row = selectedItems.first()->row();
    QString courseId = ui->coursesTable->item(row, 0)->text();
    Course* course = banner->searchCourse(courseId);

    if (!course) {
        QMessageBox::warning(this, "Error", "Course not found.");
        return;
    }

    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit *idLineEdit = new QLineEdit(courseId, &dialog);
    idLineEdit->setReadOnly(true);
    QLineEdit *nameLineEdit = new QLineEdit(course->getCourseName(), &dialog);
    QSpinBox *creditsSpinBox = new QSpinBox(&dialog);
    creditsSpinBox->setValue(course->getCreditHours());
    QComboBox *instructorComboBox = new QComboBox(&dialog);
    QSpinBox *capacitySpinBox = new QSpinBox(&dialog);
    capacitySpinBox->setValue(course->getCapacity());
    QLineEdit *timeLineEdit = new QLineEdit(course->getScheduleTime(), &dialog);
    // QLineEdit *deptLineEdit = new QLineEdit(course->getDepartment(), &dialog);
    QComboBox *depComboBox = new QComboBox(&dialog);

    if (banner) {
        auto users = banner->listUsers();
        for (const auto& userPair : users) {
            User* user = userPair.second;
            if (user->getRole() == INSTRUCTOR) {
                instructorComboBox->addItem(user->getName(), QVariant::fromValue(static_cast<Instructor*>(user)));
                if (user == course->getInstructor()) {
                    instructorComboBox->setCurrentIndex(instructorComboBox->count() - 1);
                }
            }
        }

        auto deps = banner->getDeps();
        for (const auto& dep : deps) {

            depComboBox->addItem(dep);
            if (dep == course->getDepartment()) {
                depComboBox->setCurrentIndex(depComboBox->count() - 1);
            }
        }
    }

    form.addRow("Course ID:", idLineEdit);
    form.addRow("Course Name:", nameLineEdit);
    form.addRow("Credits:", creditsSpinBox);
    form.addRow("Instructor:", instructorComboBox);
    form.addRow("Capacity:", capacitySpinBox);
    form.addRow("Schedule Time:", timeLineEdit);
    form.addRow("Department:", depComboBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        course->update(nameLineEdit->text(), creditsSpinBox->value(), qvariant_cast<Instructor*>(instructorComboBox->currentData()),capacitySpinBox->value(),timeLineEdit->text(), depComboBox->currentText());

        banner->saveData();
        populateCoursesTable();
    }
}

void CMPage::on_deleteCourseButton_clicked() {
    QList<QTableWidgetItem*> selectedItems = ui->coursesTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a course to delete.");
        return;
    }

    int row = selectedItems.first()->row();
    QString courseId = ui->coursesTable->item(row, 0)->text();

    if (QMessageBox::question(this, "Confirm Delete", "Are you sure?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        if (banner->deleteCourse(courseId)) {
            populateCoursesTable();
        } else {
            QMessageBox::warning(this, "Error", "Delete failed.");
        }
    }
}

void CMPage::on_searchButton_clicked() {
    QString instructorFilter = ui->instructorSearch->text();
    QString departmentFilter = ui->departmentSearch->text();
    QString timeFilter = ui->timeSearch->text();
    populateCoursesTable(instructorFilter, departmentFilter, timeFilter);
}

void CMPage::on_coursesTable_itemSelectionChanged() {
    QList<QTableWidgetItem*> selectedItems = ui->coursesTable->selectedItems();
    ui->waitingListTable->setRowCount(0);
    ui->enrolledStudentsTable->setRowCount(0);

    if (selectedItems.isEmpty()) return;

    int row = selectedItems.first()->row();
    QString courseId = ui->coursesTable->item(row, 0)->text();
    Course* course = banner->searchCourse(courseId);

    if (!course) return;

    // Populate waiting students
    vector<Student*> waitingList = course->getWaitingList();
    for (auto& student: waitingList){
        int wlRow = ui->waitingListTable->rowCount();
        ui->waitingListTable->insertRow(wlRow);
        ui->waitingListTable->setItem(wlRow, 0, new QTableWidgetItem(student->getName()));
        ui->waitingListTable->setItem(wlRow, 1, new QTableWidgetItem(student->getID()));
    }

    // Populate enrolled students
    vector<Student*> enrolledStudents = course->getEnrolledStudents();
    for (auto& student: enrolledStudents) {
        int esRow = ui->enrolledStudentsTable->rowCount();
        ui->enrolledStudentsTable->insertRow(esRow);
        ui->enrolledStudentsTable->setItem(esRow, 0, new QTableWidgetItem(student->getName()));
        ui->enrolledStudentsTable->setItem(esRow, 1, new QTableWidgetItem(student->getID()));
    }
}

void CMPage::on_backPushButton_clicked()
{
    Dashboard* d = new Dashboard(NULL);
    d->setBanner(banner);
    this->close();
    d->show();
}

