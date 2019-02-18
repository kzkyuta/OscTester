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
    receivedMsg->setFontFamily("Arial");
    receivedMsg->setFontPointSize(13);
    receivedMsg->setFontWeight(1);

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
    msgOut.append(time.toString("MM/dd/hh:mm:ss") + " - ");
    msgOut.append(msg->getAddress() + ":");
    qInfo() << "a";

    for(int i = 0; i < msg->getSize(); i++){
        msgOut.append(" " + msg->getReceivedData(i));
        qInfo() << msg->getReceivedData(i);
    }
    receivedMsg->append(msgOut);
}
