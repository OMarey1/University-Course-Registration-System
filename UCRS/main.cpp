#include <QApplication>
#include "crpage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CRPage w;  // Change this line
    w.show();
    return a.exec();
}
