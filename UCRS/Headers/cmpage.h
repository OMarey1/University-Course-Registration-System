#ifndef CMPAGE_H
#define CMPAGE_H

#include <QDialog>
#include "banner.h"

namespace Ui {
class CMPage;
}

class CMPage : public QDialog
{
    Q_OBJECT

public:
    explicit CMPage(QWidget *parent = nullptr);
    ~CMPage();
    void setBanner(Banner* b);

private slots:
    void on_addCourseButton_clicked();
    void on_editCourseButton_clicked();
    void on_deleteCourseButton_clicked();
    void on_searchButton_clicked();
    void on_coursesTable_itemSelectionChanged();

private:
    Ui::CMPage *ui;
    Banner* banner;
    void populateCoursesTable(const QString& instructorFilter = "", const QString& departmentFilter = "", const QString& timeFilter = "");
};

#endif // CMPAGE_H
