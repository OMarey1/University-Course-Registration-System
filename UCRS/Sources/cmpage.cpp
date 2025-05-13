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

CMPage::CMPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CMPage)
    , banner(nullptr)
{
    ui->setupUi(this);
    connect(ui->editCourseButton, &QPushButton::clicked, this, &CMPage::on_editCourseButton_clicked);
    connect(ui->deleteCourseButton, &QPushButton::clicked, this, &CMPage::on_deleteCourseButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &CMPage::on_searchButton_clicked);
    connect(ui->coursesTable, &QTableWidget::itemSelectionChanged, this, &CMPage::on_coursesTable_itemSelectionChanged);
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

// void CMPage::on_addCourseButton_clicked() {
//     QDialog dialog(this);
//     QFormLayout form(&dialog);

//     QLineEdit *idLineEdit = new QLineEdit(&dialog);
//     QLineEdit *nameLineEdit = new QLineEdit(&dialog);
//     QSpinBox *creditsSpinBox = new QSpinBox(&dialog);
//     creditsSpinBox->setRange(1, 6);
//     QComboBox *instructorComboBox = new QComboBox(&dialog);
//     QSpinBox *capacitySpinBox = new QSpinBox(&dialog);
//     capacitySpinBox->setRange(1, 200);
//     QLineEdit *timeLineEdit = new QLineEdit(&dialog);
//     QLineEdit *deptLineEdit = new QLineEdit(&dialog);

//     if (banner) {
//         auto users = banner->listUsers();
//         for (const auto& userPair : users) {
//             User* user = userPair.second;
//             if (user->getRole() == INSTRUCTOR) {
//                 instructorComboBox->addItem(user->getName(), QVariant::fromValue(static_cast<Instructor*>(user)));
//             }
//         }
//     }

//     form.addRow("Course ID:", idLineEdit);
//     form.addRow("Course Name:", nameLineEdit);
//     form.addRow("Credits:", creditsSpinBox);
//     form.addRow("Instructor:", instructorComboBox);
//     form.addRow("Capacity:", capacitySpinBox);
//     form.addRow("Schedule Time:", timeLineEdit);
//     form.addRow("Department:", deptLineEdit);

//     QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
//     form.addRow(&buttonBox);

//     connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
//     connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

//     if (dialog.exec() == QDialog::Accepted) {
//         QString id = idLineEdit->text();
//         QString name = nameLineEdit->text();
//         unsigned int credits = creditsSpinBox->value();
//         Instructor* instructor = qvariant_cast<Instructor*>(instructorComboBox->currentData());
//         unsigned int capacity = capacitySpinBox->value();
//         QString time = timeLineEdit->text();
//         QString dept = deptLineEdit->text();

//         if (id.isEmpty() || name.isEmpty() || time.isEmpty() || dept.isEmpty() || !instructor) {
//             QMessageBox::warning(this, "Error", "All fields must be filled.");
//             return;
//         }

//         Course* newCourse = new Course(id.toStdString(), name.toStdString(), credits, instructor, capacity, time.toStdString(), dept.toStdString());
//         if (banner->createCourse(newCourse)) {
//             populateCoursesTable();
//         } else {
//             QMessageBox::warning(this, "Error", "Course ID already exists.");
//             delete newCourse;
//         }
//     }
// }

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
    QLineEdit *deptLineEdit = new QLineEdit(course->getDepartment(), &dialog);

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
    }

    form.addRow("Course ID:", idLineEdit);
    form.addRow("Course Name:", nameLineEdit);
    form.addRow("Credits:", creditsSpinBox);
    form.addRow("Instructor:", instructorComboBox);
    form.addRow("Capacity:", capacitySpinBox);
    form.addRow("Schedule Time:", timeLineEdit);
    form.addRow("Department:", deptLineEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        course->update(nameLineEdit->text(), creditsSpinBox->value(), qvariant_cast<Instructor*>(instructorComboBox->currentData()),capacitySpinBox->value(),timeLineEdit->text(), deptLineEdit->text());

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

    if (selectedItems.isEmpty()) return;

    int row = selectedItems.first()->row();
    QString courseId = ui->coursesTable->item(row, 0)->text();
    Course* course = banner->searchCourse(courseId);

    if (!course) return;

    vector<Student*> waitingList = course->getWaitingList();
    for (auto& student: waitingList){
        int wlRow = ui->waitingListTable->rowCount();
        ui->waitingListTable->insertRow(wlRow);
        ui->waitingListTable->setItem(wlRow, 0, new QTableWidgetItem(student->getName()));
        ui->waitingListTable->setItem(wlRow, 1, new QTableWidgetItem(student->getID()));
    }
}
