#include "sendcontainer.h"

SendContainer::SendContainer(QWidget *parent)
    :QFrame(parent)
{
    // set frame default size
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    setMinimumSize(0,65);
    setFrameShape(Panel);

    containerNum ++;

    // make a grid instance in QFrame
    layout1 = new QHBoxLayout(this);
    QVBoxLayout* layout2 = new QVBoxLayout();
    QHBoxLayout* layout3 = new QHBoxLayout();

    sendButton = new QPushButton("send");
    sendButton->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    sendButton->setMinimumSize(60,60);

    msg = new QLineEdit(this);
    msg->setPlaceholderText("OSC Message");

    port = new QLineEdit(this);
    port->setPlaceholderText("port");

    ip = new QLineEdit(this);
    ip->setPlaceholderText("IP Adress");

    layout3->addWidget(port);
    layout3->addWidget(ip);
    layout2->addWidget(msg);
    layout2->addLayout(layout3);
    layout1->addLayout(layout2);
    layout1->addWidget(sendButton);
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendOscMessage()));
}

SendContainer::~SendContainer(){}

// Number of Containers
uint8_t SendContainer::containerNum = 0;

void SendContainer::sendOscMessage(){
    InputConverter inputMessage = InputConverter(msg->text());
    inputMessage.setMessage();
    if(!ip->text().isNull() && !port->text().isNull()){
        if(!ip->text().isEmpty() && !port->text().isEmpty()){
            _oscSender = new QOSCSender(ip->text(), port->text().toInt(), this);
            _oscSender->send(inputMessage.getMessage());
            delete _oscSender;
        }
    }
}

QString SendContainer::getMsg(){
    return msg->text();
}

QString SendContainer::getPort(){
    return port->text();
}

QString SendContainer::getIp(){
    return ip->text();
}

void SendContainer::setMsg(QString message){
    msg->setText(message);
}

void SendContainer::setPort(QString portNum){
    port->setText(portNum);
}

void SendContainer::setIp(QString ipNum){
    ip->setText(ipNum);
}
