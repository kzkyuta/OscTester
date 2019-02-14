#ifndef SENDCONTAINER_H
#define SENDCONTAINER_H

#include <QObject>
#include <QFrame>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include "inputconverter.h"
#include "qoscsender.h"

class SendContainer : public QFrame
{
    QHBoxLayout *layout1;
    QPushButton *sendButton;
    QLineEdit *msg;
    QLineEdit *port;
    QLineEdit *ip;
    uint8_t id;
    QOSCSender *_oscSender;
public:
    explicit SendContainer(uint8_t, QWidget*);
    SendContainer(const SendContainer &);
    uint8_t getId();
private slots:
    void sendOscMessage();
};

#endif // SENDCONTAINER_H
