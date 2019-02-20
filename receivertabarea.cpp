#include "receivertabarea.h"

ReceiverTabArea::ReceiverTabArea(unsigned int portNum, QWidget* parent)
    :QWidget(parent),
      oscReceiver(new QOSCReceiver(portNum, this)),
      parentLayout(new QVBoxLayout(this)),
      filterInput(new QLineEdit()),
      receivedMsgOutput(new QPlainTextEdit()),
      port(portNum)
{
    tabNum++;
    oscReceiver->connect(oscReceiver, SIGNAL(messageReceived(QOSCMessage*)), this, SLOT(onMessageReceived(QOSCMessage*)));
    oscReceiver->start();

    receivedMsgOutput->setReadOnly(false);

    filterInput->setPlaceholderText("Insert filter sentence.");
    parentLayout->addWidget(filterInput);
    parentLayout->addWidget(receivedMsgOutput);
    connect(filterInput, SIGNAL(textChanged(const QString &)), this, SLOT(onChangedText()));

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

    for(int i = 0; i < msg->getSize(); i++){
        msgOut.append(" " + msg->getReceivedData(i));
    }
    receivedMsgs.push_back(msgOut);
    this->showReceivedMsg();
}

void ReceiverTabArea::onChangedText(){
    showReceivedMsg();
}

bool ReceiverTabArea::msgFilter(int i){
    QString searchString = filterInput->text();
    if(searchString.isEmpty()) return true;
    if(receivedMsgs[i].toStdString().find(searchString.toStdString()) == std::string::npos)
        return false;
    else
        return true;
}

void ReceiverTabArea::showReceivedMsg(){
    receivedMsgOutput->clear();
    for(int i =0; i < receivedMsgs.size(); i++){
        if(!this->msgFilter(i)){
            QString grayText = QString("<FONT COLOR=gray>%1</FONT>").arg(receivedMsgs[i]);
            receivedMsgOutput->appendHtml(grayText);
        }else{
            QString whiteText = QString("<FONT COLOR=white>%1</FONT>").arg(receivedMsgs[i]);
            receivedMsgOutput->appendHtml(whiteText);
        }
    }
}
