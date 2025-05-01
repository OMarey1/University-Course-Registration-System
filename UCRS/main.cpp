#include "loginpage.h"
#include "banner.h"
#include <QApplication>
#include "crpage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Banner banner;
    LoginPage w;
    w.setBanner(&banner);
    w.show();
    return a.exec();
}
