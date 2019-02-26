#ifndef RECEIVERTABAREA_H
#define RECEIVERTABAREA_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLayout>
#include <QTime>
#include <QDebug>
#include <QPalette>
#include "qoscreceiver.h"

class ReceiverTabArea : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiverTabArea(unsigned int, QWidget* = nullptr);
    ~ReceiverTabArea();

    static uint8_t tabNum;
    uint8_t getTabNum();
    QOSCReceiver *oscReceiver;
    QLineEdit *filterInput;
    bool msgFilter(int);
    void showReceivedMsg();
    QVector<QString> receivedMsgs;

public slots:
    void onMessageReceived(QOSCMessage* msg);
    void onChangedText();  // connect to the line edit which contains filter words.

private:
    unsigned int port;
    QPlainTextEdit *receivedMsgOutput;
    QVBoxLayout *parentLayout;
    void layoutInit();
};

#endif // RECEIVERTABAREA_H
