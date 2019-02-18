#include "receivertabarea.h"

ReceiverTabArea::ReceiverTabArea(unsigned int portNum, QWidget* parent)
    :QWidget(parent),
      oscReceiver(new QOSCReceiver(portNum, this)),
      port(portNum)
{
    tabNum++;
    oscReceiver->
    connect(oscReceiver, SIGNAL(messageReceived(QOSCMessage*)), this, SLOT(onMessageReceived(QOSCMessage*)));
    oscReceiver->start();

    parentLayout = new QVBoxLayout(this);
    filter = new QLineEdit();
    receivedMsg = new QTextEdit();

    filter->setPlaceholderText("Insert filter sentence.");
    parentLayout->addWidget(filter);
    parentLayout->addWidget(receivedMsg);
}

ReceiverTabArea::~ReceiverTabArea(){}

uint8_t ReceiverTabArea::getTabNum(){
    return tabNum;
}

void ReceiverTabArea::onMessageReceived(QOSCMessage* msg){
    QDateTime time = QDateTime::currentDateTime();
    QString msgOut;
    msgOut.append(time.toString("MM/dd/hh:mm:ss") + " ");
    msgOut.append(msg->getAddress());
    receivedMsg->append(msgOut);
}
