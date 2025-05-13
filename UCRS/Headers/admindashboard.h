#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include "banner.h"
#include "admin.h"
#include <QDialog>

namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();
    void setBanner(Banner* b);
    void fillUsersTable();
    void fillCoursesTable();

private slots:
    void on_logoutButton_clicked();

    void on_reloadTableButton_clicked();

    void on_addUserButton_clicked();

    void on_editUserButton_clicked();

    void on_saveButton_clicked();

    void onChildDialogClosed(int result);

    void on_addCourseButton_clicked();

    void on_reloadCoursesButton_clicked();

    void on_editCourseButton_clicked();

private:
    Ui::AdminDashboard *ui;
    Banner* banner;
    Admin* admin;
};

#endif // ADMINDASHBOARD_H
