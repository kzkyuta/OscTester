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
    Q_OBJECT // マクロ、継承する際に必要

private:
    QHBoxLayout *layout1;
    QPushButton *sendButton;
    QLineEdit *msg;
    QLineEdit *port;
    QLineEdit *ip;
    uint8_t id;
    QOSCSender *_oscSender;
public:
    explicit SendContainer(uint8_t, QWidget*);
    ~SendContainer();
    SendContainer(const SendContainer &);

    uint8_t getId();
    QString getMsg();
    QString getPort();
    QString getIp();

    void setMsg(QString);
    void setPort(QString);
    void setIp(QString);

private slots:
    void sendOscMessage();
};

#endif // SENDCONTAINER_H
