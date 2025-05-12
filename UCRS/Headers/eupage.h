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

    void on_searchButton_clicked();

    void on_cancelButton_clicked();

    void on_clearButton_clicked();

    void on_updateButton_clicked();

private:
    Ui::eupage *ui;
    Banner* banner;
    QString name;
    QString username;
    QString password;
    QString id;
    // UserRole role;
    User* user;

    void setEditState(bool state);
    bool isInputsFilled();
};

#endif // EUPAGE_H
