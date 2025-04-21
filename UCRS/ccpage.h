#ifndef CCPAGE_H
#define CCPAGE_H

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

private:
    Ui::CCPage *ui;
};

#endif // CCPAGE_H
