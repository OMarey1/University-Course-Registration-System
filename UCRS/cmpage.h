#ifndef CMPAGE_H
#define CMPAGE_H

#include <QDialog>

namespace Ui {
class CMPage;
}

class CMPage : public QDialog
{
    Q_OBJECT

public:
    explicit CMPage(QWidget *parent = nullptr);
    ~CMPage();

private:
    Ui::CMPage *ui;
};

#endif // CMPAGE_H
