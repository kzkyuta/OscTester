#include "osctester.h"
#include "oscreceiver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OscTester w;
    OscReceiver *oscReceiverWindow = new OscReceiver();

    oscReceiverWindow->show();
    w.show();

    return a.exec();
}
