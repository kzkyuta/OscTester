#include "osctester.h"
#include "oscreceiver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OscTester w;
    OscReceiver *oscReceiverWindow = new OscReceiver();
    w.show();
    oscReceiverWindow->show();

    return a.exec();
}
