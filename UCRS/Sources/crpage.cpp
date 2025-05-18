#include "../Headers/crpage.h"
#include "ui_crpage.h"
#include "Headers/dashboard.h"
#include "../Headers/instructor.h"
#include "../Headers/student.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <algorithm>
#include <queue>

CRPage::CRPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRPage),
    m_banner(nullptr),
    m_currentStudent(nullptr)
{
    ui->setupUi(this);

    // Configure available courses table
    ui->coursesTable->setColumnCount(4);
    ui->coursesTable->setHorizontalHeaderLabels({"ID", "Course Name", "Schedule", "Instructor"});
    ui->coursesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->coursesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->coursesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->coursesTable->verticalHeader()->setVisible(false);

    // Configure registered courses table
    ui->registeredTable->setColumnCount(4);
    ui->registeredTable->setHorizontalHeaderLabels({"ID", "Course Name", "Schedule", "Instructor"});
    ui->registeredTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->registeredTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->registeredTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->registeredTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->registeredTable->verticalHeader()->setVisible(false);

    // Connect signals
    connect(ui->registerButton, &QPushButton::clicked, this, &CRPage::handleRegistration);
    connect(ui->dropButton, &QPushButton::clicked, this, &CRPage::handleCourseDrop);
    connect(ui->searchButton, &QPushButton::clicked, this, &CRPage::handleSearch);
    connect(ui->coursesTable, &QTableWidget::itemSelectionChanged, this, &CRPage::updateCourseDetails);
    connect(ui->registeredTable, &QTableWidget::itemSelectionChanged, this, &CRPage::updateRegisteredCourseDetails);

    // Initial table population
    refreshAvailableCourses();
    refreshRegisteredCourses();
}

CRPage::~CRPage()
{
    delete ui;
}

void CRPage::setBanner(Banner* bannerSystem)
{
    m_banner = bannerSystem;
    if (m_banner) {
        refreshAvailableCourses();
    }
}

void CRPage::setStudent(Student* student)
{
    m_currentStudent = student;
    if (m_currentStudent) {
        setWindowTitle(windowTitle() + " - " + m_currentStudent->getName());
        refreshAvailableCourses();
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
        // Filter logic - only search by course ID
        if (!filter.isEmpty() &&
            !course->getCourseID().contains(filter, Qt::CaseInsensitive)) {
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
        auto* instructorItem = new QTableWidgetItem(course->getInstructor() ?
                                                        course->getInstructor()->getName() : "Not Assigned");

        // Set tooltips for full courses
        if (course->isFull()) {
            // Check if student is in waiting list
            const auto& waitingList = course->getWaitingList();
            bool inWaitingList = std::find(waitingList.begin(), waitingList.end(), m_currentStudent) != waitingList.end();

            if (inWaitingList) {
                // Calculate position in waiting list
                int position = 0;
                for (const auto& student : waitingList) {
                    if (student == m_currentStudent) {
                        break;
                    }
                    position++;
                }

                QString waitingListMsg = QString("Course full - You are in waiting list (Position: %1)").arg(position + 1);
                idItem->setToolTip(waitingListMsg);
                nameItem->setToolTip(waitingListMsg);
                scheduleItem->setToolTip(waitingListMsg);
                instructorItem->setToolTip(waitingListMsg);

                // Set text color to indicate waiting list status
                QColor waitingListColor(255, 165, 0); // Orange color for waiting list
                idItem->setForeground(waitingListColor);
                nameItem->setForeground(waitingListColor);
                scheduleItem->setForeground(waitingListColor);
                instructorItem->setForeground(waitingListColor);
            } else {
                QString fullMsg = "Course full - Click to join waiting list";
                idItem->setToolTip(fullMsg);
                nameItem->setToolTip(fullMsg);
                scheduleItem->setToolTip(fullMsg);
                instructorItem->setToolTip(fullMsg);

                // Set text color to indicate full status
                QColor fullColor(255, 0, 0); // Red color for full courses
                idItem->setForeground(fullColor);
                nameItem->setForeground(fullColor);
                scheduleItem->setForeground(fullColor);
                instructorItem->setForeground(fullColor);
            }
        }

        // Set items in table
        ui->coursesTable->setItem(row, 0, idItem);
        ui->coursesTable->setItem(row, 1, nameItem);
        ui->coursesTable->setItem(row, 2, scheduleItem);
        ui->coursesTable->setItem(row, 3, instructorItem);
    }

    // Sort by course ID
    ui->coursesTable->sortItems(0);
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
        ui->registeredTable->setItem(row, 3, new QTableWidgetItem(course->getInstructor() ?
                                                                      course->getInstructor()->getName() : "Not Assigned"));
    }

    // Sort by course ID
    ui->registeredTable->sortItems(0);
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

    // Check if already registered
    if (isAlreadyRegistered(course)) {
        showError("You are already registered for this course.");
        return;
    }

    // Check if already in waiting list
    const auto& waitingList = course->getWaitingList();
    if (std::find(waitingList.begin(), waitingList.end(), m_currentStudent) != waitingList.end()) {
        showError("You are already in the waiting list for this course.");
        return;
    }

    // Check schedule conflicts
    if (hasScheduleConflict(course)) {
        showError("Schedule conflict detected with your registered courses.");
        return;
    }

    // Check credit hours limit
    int totalCredits = course->getCreditHours();
    for (Course* c : m_currentStudent->getCourses()) {
        totalCredits += c->getCreditHours();
    }
    if (totalCredits > 21) { // Maximum 21 credit hours per semester
        showError("Registration would exceed the maximum credit hours limit (21).");
        return;
    }

    if (course->enrollStudent(m_currentStudent)) {
        m_currentStudent->registerCourse(course);
        showSuccess("Successfully registered for the course.");
    } else {
        // Student was added to waiting list inside enrollStudent()
        const auto& waitingList = course->getWaitingList();

        int position = 0;
        for (Student* s : waitingList) {
            if (s == m_currentStudent) break;
            ++position;
        }

        showSuccess(QString("Course is full. You have been added to the waiting list (Position: %1).").arg(position + 1));
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

    // Drop the course and process waiting list
    course->dropStudent(m_currentStudent);
    // showSuccess("Course dropped successfully.");

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
    if (!m_currentStudent || !newCourse) return false;

    // Parse the new course schedule
    QStringList newSchedule = newCourse->getScheduleTime().split(" ");
    if (newSchedule.size() < 2) return false;

    QString newDays = newSchedule[0];
    QString newTime = newSchedule[1];

    // Parse new course time
    QStringList newTimeParts = newTime.split("-");
    if (newTimeParts.size() != 2) return false;

    QString newStart = newTimeParts[0];
    QString newEnd = newTimeParts[1];

    // Check against all registered courses
    for (Course* course : m_currentStudent->getCourses()) {
        QStringList schedule = course->getScheduleTime().split(" ");
        if (schedule.size() < 2) continue;

        QString days = schedule[0];
        QString time = schedule[1];

        // Check if days overlap
        bool daysOverlap = false;
        for (QChar day : newDays) {
            if (days.contains(day)) {
                daysOverlap = true;
                break;
            }
        }

        if (!daysOverlap) continue;

        // Check if times overlap
        QStringList timeParts = time.split("-");
        if (timeParts.size() != 2) continue;

        QString start = timeParts[0];
        QString end = timeParts[1];

        if ((newStart >= start && newStart < end) ||
            (newEnd > start && newEnd <= end) ||
            (newStart <= start && newEnd >= end)) {
            return true;
        }
    }
    return false;
}

bool CRPage::isAlreadyRegistered(Course* course) const {
    if (!m_currentStudent || !course) return false;
    const auto& courses = m_currentStudent->getCourses();
    return std::find(courses.begin(), courses.end(), course) != courses.end();
}

void CRPage::on_backButton_clicked()
{
    Dashboard* d = new Dashboard(NULL);
    d->setBanner(m_banner);
    this->close();
    d->show();
}

