#ifndef CCPAGE_H
#define CCPAGE_H

#include "banner.h"
#include <QDialog>

namespace Ui {
class CCPage;
}

class CCPage : public QDialog
{
    Q_OBJECT

public:
    explicit CCPage(QWidget *parent = nullptr);
    ~CCPage();
    void setBanner(Banner* b);

private slots:
    void on_clearButton_clicked();

    void on_createCourseButton_clicked();

private:
    Ui::CCPage *ui;
    Banner* banner;
    QString name;
    QString id;
    unsigned int creditHours;
    QString instructorUsername;
    unsigned int capacity;
    QString day;
    QString time;
    QString schedule;
    QString dep;

    bool isInputsFilled();
};

#endif // CCPAGE_H
