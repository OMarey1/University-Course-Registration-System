#include "loginpage.h"
#include "admindashboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPage w;
    w.show();
    AdminDashboard ad;
    ad.show();
    return a.exec();
}
