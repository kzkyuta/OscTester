#ifndef OSCTESTER_H
#define OSCTESTER_H

#include "qoscsender.h"
#include "qoscreceiver.h"
#include "inputconverter.h"

#include <QMainWindow>
#include <vector>
#include <QDebug>
#include <QTime>
#include <QCloseEvent>
#include "verticalscrollarea.h"
#include "sendcontainer.h"

namespace Ui {
class OscTester;
}

class OscTester : public QMainWindow
{
    Q_OBJECT
private:
    QOSCSender *_oscSender;
    Ui::OscTester *ui;
    void closeEvent(QCloseEvent *event);

public:
    int nrows = 1;
    int ncols = 5;
    int i = 0;
    explicit OscTester(QWidget *parent = nullptr);
    ~OscTester();
    QOSCReceiver *_oscReceiver;
    VerticalScrollArea *_scroll;

private slots:
    void on_sendMessage_clicked();
    void onMessageReceived(QOSCMessage *msg);

    void on_addContainer_clicked();
//    void slotGetNumber();


};

#endif // OSCTESTER_H
