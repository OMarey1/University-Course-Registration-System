#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include "banner.h"
#include "messages.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginPage;
}
QT_END_NAMESPACE

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    void setBanner(Banner* b);

private slots:
    void on_loginButton_clicked();

    void onChildDialogClosed(int result);


private:
    Ui::LoginPage *ui;
    Banner* banner;
    QString username;
    QString password;
};
#endif // LOGINPAGE_H
