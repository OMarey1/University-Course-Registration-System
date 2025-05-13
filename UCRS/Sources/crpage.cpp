#include "../Headers/crpage.h"
#include "ui_crpage.h"
#include "../Headers/instructor.h"
#include <QMessageBox>
#include <QTableWidgetItem>

CRPage::CRPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRPage),
    m_banner(nullptr),
    m_currentStudent(nullptr)
{
    ui->setupUi(this);

    // Configure tables
    ui->coursesTable->setColumnCount(3);
    ui->coursesTable->setHorizontalHeaderLabels({"ID", "Course Name", "Schedule"});
    ui->registeredTable->setColumnCount(3);
    ui->registeredTable->setHorizontalHeaderLabels({"ID", "Course Name", "Schedule"});

    // Connect signals
    connect(ui->registerButton, &QPushButton::clicked, this, &CRPage::handleRegistration);
    connect(ui->dropButton, &QPushButton::clicked, this, &CRPage::handleCourseDrop);
    connect(ui->searchButton, &QPushButton::clicked, this, &CRPage::handleSearch);
    connect(ui->coursesTable, &QTableWidget::itemSelectionChanged, this, &CRPage::updateCourseDetails);
    connect(ui->registeredTable, &QTableWidget::itemSelectionChanged, this, &CRPage::updateRegisteredCourseDetails);
}

CRPage::~CRPage()
{
    delete ui;
}

void CRPage::setBanner(Banner* bannerSystem)
{
    m_banner = bannerSystem;
    refreshAvailableCourses();
}

void CRPage::setStudent(Student* student)
{
    m_currentStudent = student;
    if (m_currentStudent) {
        setWindowTitle(windowTitle() + " - " + m_currentStudent->getName());
        refreshRegisteredCourses();
    }
}

void CRPage::refreshAvailableCourses(const QString& filter)
{
    ui->coursesTable->setRowCount(0);
    if (!m_banner || !m_currentStudent) return;

    const auto allCourses = m_banner->listCourses();
    const auto registeredCourses = m_currentStudent->getCourses();

    for (const auto& [id, course] : allCourses) {
        // Filter logic
        if (!filter.isEmpty() &&
            !course->getCourseID().contains(filter, Qt::CaseInsensitive) &&
            !course->getCourseName().contains(filter, Qt::CaseInsensitive)) {
            continue;
        }

        // Skip already registered courses
        if (isAlreadyRegistered(course)) continue;

        // Add to table
        int row = ui->coursesTable->rowCount();
        ui->coursesTable->insertRow(row);

        auto* idItem = new QTableWidgetItem(course->getCourseID());
        auto* nameItem = new QTableWidgetItem(course->getCourseName());
        auto* scheduleItem = new QTableWidgetItem(course->getScheduleTime());

        if (course->isFull()) {
            idItem->setFlags(idItem->flags() & ~Qt::ItemIsEnabled);
            idItem->setToolTip("Course full");
            nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEnabled);
            scheduleItem->setFlags(scheduleItem->flags() & ~Qt::ItemIsEnabled);
        }

        ui->coursesTable->setItem(row, 0, idItem);
        ui->coursesTable->setItem(row, 1, nameItem);
        ui->coursesTable->setItem(row, 2, scheduleItem);
    }
}

void CRPage::refreshRegisteredCourses()
{
    ui->registeredTable->setRowCount(0);
    if (!m_currentStudent) return;

    for (Course* course : m_currentStudent->getCourses()) {
        int row = ui->registeredTable->rowCount();
        ui->registeredTable->insertRow(row);

        ui->registeredTable->setItem(row, 0, new QTableWidgetItem(course->getCourseID()));
        ui->registeredTable->setItem(row, 1, new QTableWidgetItem(course->getCourseName()));
        ui->registeredTable->setItem(row, 2, new QTableWidgetItem(course->getScheduleTime()));
    }
}

void CRPage::handleRegistration() {
    auto selectedItems = ui->coursesTable->selectedItems();
    if (selectedItems.isEmpty() || !m_currentStudent || !m_banner) {
        showError("Please select a course to register.");
        return;
    }
    int row = selectedItems.first()->row();
    QString courseId = ui->coursesTable->item(row, 0)->text();
    Course* course = m_banner->searchCourse(courseId);
    if (!course) {
        showError("Course not found.");
        return;
    }
    if (isAlreadyRegistered(course)) {
        showError("You are already registered for this course.");
        return;
    }
    if (hasScheduleConflict(course)) {
        showError("Schedule conflict detected.");
        return;
    }
    if (course->enrollStudent(m_currentStudent)) {
        m_currentStudent->registerCourse(course);
        showSuccess("Successfully registered for the course.");
    } else {
        showError("Course is full. You have been added to the waiting list.");
    }
    refreshAvailableCourses();
    refreshRegisteredCourses();
}

void CRPage::handleCourseDrop() {
    auto selectedItems = ui->registeredTable->selectedItems();
    if (selectedItems.isEmpty() || !m_currentStudent || !m_banner) {
        showError("Please select a course to drop.");
        return;
    }
    int row = selectedItems.first()->row();
    QString courseId = ui->registeredTable->item(row, 0)->text();
    Course* course = m_banner->searchCourse(courseId);
    if (!course) {
        showError("Course not found.");
        return;
    }
    if (!m_currentStudent->dropCourse(course)) {
        showError("You are not registered for this course.");
        return;
    }
    course->dropStudent(m_currentStudent);
    showSuccess("Course dropped successfully.");
    refreshAvailableCourses();
    refreshRegisteredCourses();
}

void CRPage::handleSearch() {
    QString filter = ui->searchLineEdit->text();
    refreshAvailableCourses(filter);
}

void CRPage::updateCourseDetails() {
    auto selectedItems = ui->coursesTable->selectedItems();
    if (selectedItems.isEmpty() || !m_banner) return;
    int row = selectedItems.first()->row();
    QString courseId = ui->coursesTable->item(row, 0)->text();
    Course* course = m_banner->searchCourse(courseId);
    if (course) displayCourseInfo(course);
}

void CRPage::updateRegisteredCourseDetails() {
    auto selectedItems = ui->registeredTable->selectedItems();
    if (selectedItems.isEmpty() || !m_banner) return;
    int row = selectedItems.first()->row();
    QString courseId = ui->registeredTable->item(row, 0)->text();
    Course* course = m_banner->searchCourse(courseId);
    if (course) displayCourseInfo(course);
}

void CRPage::displayCourseInfo(Course* course) {
    if (!course) return;
    QString info = QString("Course ID: %1\nName: %2\nInstructor: %3\nSchedule: %4\nCredits: %5\nCapacity: %6\nEnrolled: %7\nDepartment: %8")
                       .arg(course->getCourseID())
                       .arg(course->getCourseName())
                       .arg(course->getInstructor() ? course->getInstructor()->getName() : "N/A")
                       .arg(course->getScheduleTime())
                       .arg(course->getCreditHours())
                       .arg(course->getCapacity())
                       .arg(course->getEnrolledStudents().size())
                       .arg(course->getDepartment());
    QMessageBox::information(this, "Course Details", info);
}

void CRPage::showError(const QString& message) {
    QMessageBox::warning(this, "Error", message);
}

void CRPage::showSuccess(const QString& message) {
    QMessageBox::information(this, "Success", message);
}

bool CRPage::hasScheduleConflict(Course* newCourse) const {
    if (!m_currentStudent) return false;
    for (Course* course : m_currentStudent->getCourses()) {
        if (course->getScheduleTime() == newCourse->getScheduleTime()) {
            return true;
        }
    }
    return false;
}

bool CRPage::isAlreadyRegistered(Course* course) const {
    if (!m_currentStudent) return false;
    for (Course* c : m_currentStudent->getCourses()) {
        if (c == course) return true;
    }
    return false;
}
