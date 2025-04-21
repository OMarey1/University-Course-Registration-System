#ifndef REPORTSPAGE_H
#define REPORTSPAGE_H

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

private:
    Ui::ReportsPage *ui;
};

#endif // REPORTSPAGE_H
