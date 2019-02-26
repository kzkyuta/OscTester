#include "osctester.h"
#include "oscreceiver.h"
//#include "oscsender.h"
#include <QApplication>
#include <QMenu>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OscTester x;

    x.show();

    Q_INIT_RESOURCE(osctester);

    return a.exec();
}
