#include "../Headers/loginpage.h"
#include "../Headers/banner.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Banner banner;
    LoginPage w;
    w.setBanner(&banner);
    w.show();
    return a.exec();
}
