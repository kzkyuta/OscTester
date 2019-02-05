#include "osctester.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OscTester w;
    w.show();

    return a.exec();
}
