#include "receivertabarea.h"

ReceiverTabArea::ReceiverTabArea(int portNum, QWidget* parent)
    :QWidget(parent), port(portNum), oscReceiver(new QOSCReceiver(port, this))
{
    tabNum++;
    connect(oscReceiver, SIGNAL(messageReveived(QOSCMessage*)), this, SLOT(onMessageReceived(QOSCMessage*)));
    oscReceiver->start();

    parentLayout = new QVBoxLayout(this);
    filter = new QLineEdit();
    receivedMsg = new QTextEdit();

    filter->setPlaceholderText("Insert filter sentence.");
    parentLayout->addWidget(filter);
    parentLayout->addWidget(receivedMsg);
}

uint8_t ReceiverTabArea::getTabNum(){
    return tabNum;
}

void ReceiverTabArea::onMessageReceived(QOSCMessage *msg){
    QDateTime time = QDateTime::currentDateTime();
    QString msgOut;
    msgOut.append(time.toString("MM/dd/hh:mm:ss") + " ");
    msgOut.append(msg->getAddress());
    receivedMsg->append(msgOut);
}
