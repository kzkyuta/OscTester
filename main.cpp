#include "osctester.h"
#include "oscreceiver.h"
#include "oscsender.h"
#include <QApplication>
#include <QMenu>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    OscTester w;
    OscReceiver v;
    OscSender x;
    v.show();
//    w.show();
    x.show();

    return a.exec();
}
