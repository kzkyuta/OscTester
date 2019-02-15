#ifndef RECEIVERTABAREA_H
#define RECEIVERTABAREA_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QLayout>
#include <QTime>
#include "qoscreceiver.h"

class ReceiverTabArea : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiverTabArea(int, QWidget* = nullptr);
    static uint8_t tabNum;
    uint8_t getTabNum();
    QOSCReceiver *oscReceiver;
private slots:
//    void filter();
    void onMessageReceived(QOSCMessage *msg);

private:
    int port;
    QLineEdit *filter;
    QTextEdit *receivedMsg;
    QVBoxLayout *parentLayout;
};

#endif // RECEIVERTABAREA_H
