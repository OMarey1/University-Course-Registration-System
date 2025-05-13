#pragma once
#ifndef CRPAGE_H
#define CRPAGE_H

#include <QDialog>
#include "banner.h"
#include "student.h"
#include "course.h"

namespace Ui {
class CRPage;
}

class CRPage : public QDialog
{
    Q_OBJECT

public:
    explicit CRPage(QWidget *parent = nullptr);
    ~CRPage();

    void setBanner(Banner* bannerSystem);
    void setStudent(Student* student);

private slots:
    void handleRegistration();
    void handleCourseDrop();
    void handleSearch();
    void updateCourseDetails();
    void updateRegisteredCourseDetails();

    void on_backButton_clicked();

private:
    Ui::CRPage *ui;
    Banner* m_banner;
    Student* m_currentStudent;

    void refreshAvailableCourses(const QString& filter = "");
    void refreshRegisteredCourses();
    void displayCourseInfo(Course* course);
    void showError(const QString& message);
    void showSuccess(const QString& message);

    bool hasScheduleConflict(Course* newCourse) const;
    bool isAlreadyRegistered(Course* course) const;
};

#endif // CRPAGE_H
