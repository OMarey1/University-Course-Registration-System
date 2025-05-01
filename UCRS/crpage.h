#ifndef CRPAGE_H
#define CRPAGE_H

#include <QDialog>
namespace Ui {
class CRPage;
}

class CRPage : public QDialog
{
    Q_OBJECT

public:
    explicit CRPage(QWidget *parent = nullptr);
    ~CRPage();

private:
    Ui::CRPage *ui;
};

#endif // CRPAGE_H
