#ifndef CUPAGE_H
#define CUPAGE_H

#include "banner.h"
#include "user.h"
#include <QDialog>

namespace Ui {
class cupage;
}

class cupage : public QDialog
{
    Q_OBJECT

public:
    explicit cupage(QWidget *parent = nullptr);
    ~cupage();
    void setBanner(Banner* b);

private slots:
    void on_createUserButton_clicked();

private:
    Ui::cupage *ui;
    Banner* banner;
    QString name;
    QString username;
    QString password;
    QString id;
    UserRole role;

    bool isInputsFilled();
};

#endif // CUPAGE_H
