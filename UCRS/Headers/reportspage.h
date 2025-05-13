#ifndef REPORTSPAGE_H
#define REPORTSPAGE_H

#include "Headers/student.h"
#include "banner.h"
#include "user.h"
#include "student.h"
#include <QDialog>

namespace Ui {
class ReportsPage;
}

class ReportsPage : public QDialog
{
    Q_OBJECT

public:
    explicit ReportsPage(QWidget *parent = nullptr);
    ~ReportsPage();
    void setBanner(Banner * b);




private slots:
    void on_generatePushButton_clicked();

    void on_exportPushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::ReportsPage *ui;
    Banner * banner;
    User * user;
    Student * student;
};

#endif // REPORTSPAGE_H
