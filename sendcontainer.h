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
    QOSCSender *_oscSender;

public:
    QLineEdit *commandInput;
    explicit SendContainer(QWidget*);
    ~SendContainer();
    SendContainer(const SendContainer &);

    QString getMsg();
    QString getPort();
    QString getIp();

    void setMsg(QString);
    void setPort(QString);
    void setIp(QString);

    static uint8_t containerNum;
    void sendOscMessage();

private slots:
    void on_sendButton_clicked();
    void on_sendButton_pressed();
    void on_changed_text();
};

#endif // SENDCONTAINER_H
