#include "reportspage.h"  // Change this line
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReportsPage w;  // Change this line
    w.show();
    return a.exec();
}
