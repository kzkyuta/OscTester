#ifndef SENDCONTAINER_H
#define SENDCONTAINER_H

#include <QObject>
#include <QFrame>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include "inputconverter.h"
#include "qoscsender.h"
#include <QKeyEvent>

class SendContainer : public QFrame
{
    Q_OBJECT

private:
    // for layout
    QHBoxLayout *layout1;
    QPushButton *sendButton;
    QLineEdit *msg;
    QLineEdit *port;
    QLineEdit *ip;
    QOSCSender *_oscSender;

    void layoutInit();

public:
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

    // for sending osc message
    void sendOscMessage();
    QOSCMessage* outOscMessage();

    void changeContainerColor(bool);

    // for key input. this will be used at OscTester class.
    QLineEdit *commandInput;

private slots:
    void on_sendButton_clicked();  // send Osc Message
    void on_sendButton_pressed();
    void on_sendButton_released();
    void on_changed_text();
    void on_lineEdit_returnPressed();  // send Osc Message

protected:
//    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
};

#endif // SENDCONTAINER_H
