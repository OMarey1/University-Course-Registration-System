#ifndef CRPAGE_H
#define CRPAGE_H
#include "banner.h"
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
    void setBanner(Banner* b);

private:
    Ui::CRPage *ui;
    Banner* banner;
};

#endif // CRPAGE_H
