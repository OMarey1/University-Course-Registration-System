#ifndef EUPAGE_H
#define EUPAGE_H

#include "banner.h"
#include <QDialog>

namespace Ui {
class eupage;
}

class eupage : public QDialog
{
    Q_OBJECT

public:
    explicit eupage(QWidget *parent = nullptr);
    ~eupage();
    void setBanner(Banner* b);

private slots:

    void on_deleteButton_clicked();

private:
    Ui::eupage *ui;
    Banner* banner;
    QString username;
};

#endif // EUPAGE_H
