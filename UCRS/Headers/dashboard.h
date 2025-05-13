#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "banner.h"
#include "messages.h"
#include <QDialog>

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();
    void setBanner(Banner* b);

private slots:
    void on_reportsButton_clicked();

    void on_registerCoursesButton_clicked();

    void on_signOutButton_clicked();

private:
    Ui::Dashboard *ui;
    Banner* banner;
};

#endif // DASHBOARD_H
