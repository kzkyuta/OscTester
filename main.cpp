#include "osctester.h"
#include "oscreceiver.h"
//#include "oscsender.h"
#include <QApplication>
#include <QMenu>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OscTester x;
//    OscSender v;
//    OscReceiver w;


    x.show();
//    x.setHidden(true);
//    v.show();
//    w.show();

    return a.exec();
}
