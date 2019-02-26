#include "sendcontainer.h"

SendContainer::SendContainer(QWidget *parent)
    :QFrame(parent)
{
    layoutInit();

    containerNum ++;

    connect(sendButton, SIGNAL(clicked()), this, SLOT(on_sendButton_clicked()));
    connect(sendButton, SIGNAL(pressed()), this, SLOT(on_sendButton_pressed()));
    connect(sendButton, SIGNAL(released()), this, SLOT(on_sendButton_released()));
    connect(commandInput, SIGNAL(textChanged(const QString &)), this, SLOT(on_changed_text()));
    connect(msg, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_returnPressed()));
}

SendContainer::~SendContainer(){}

// Number of Containers
uint8_t SendContainer::containerNum = 0;

void SendContainer::on_sendButton_clicked(){
    this->sendOscMessage();
}

void SendContainer::on_lineEdit_returnPressed(){
    this->sendOscMessage();
    changeContainerColor(true);
}

void SendContainer::on_sendButton_pressed(){
    changeContainerColor(true);
}

void SendContainer::on_sendButton_released(){
    changeContainerColor(false);
}

void SendContainer::sendOscMessage(){
    InputConverter inputMessage = InputConverter(msg->text());
    inputMessage.setMessage();
    if(!ip->text().isNull() && !port->text().isNull()){
        if(!ip->text().isEmpty() && !port->text().isEmpty()){
            _oscSender = new QOSCSender(ip->text(), port->text().toInt(), this);
            _oscSender->sendMessage(inputMessage.getMessage());
            delete _oscSender;
        }
    }
}

QString SendContainer::getComm(){
    return commandInput->text();
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

void SendContainer::setComm(QString command){
    commandInput->setText(command);
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

void SendContainer::on_changed_text(){
    commandInput->setText(commandInput->text().toUpper());
}

void SendContainer::changeContainerColor(bool state){
    if(state) this->setStyleSheet("#SendContainerFrame {background-color: darkgray;}");
    else this->setStyleSheet("");
}

QOSCMessage* SendContainer::outOscMessage(){
    InputConverter inputMessage = InputConverter(msg->text());
    inputMessage.setMessage();
    return inputMessage.getMessage();
}

//void SendContainer::keyPressEvent(QKeyEvent* event){
//    if(event->key() == Qt::Key_Return) {
//        changeContainerColor(true);
//    }
//}

void SendContainer::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Return) {
        changeContainerColor(false);
    }
}

void SendContainer::layoutInit(){
    // set frame default size
    this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    this->setMinimumSize(0,65);
    this->setFrameShape(Panel);

    // This may be related to some bug. it seems change object name.
    // This is for reference to change stype.
    this->setObjectName("SendContainerFrame");

    // make a grid instance in QFrame
    layout1 = new QHBoxLayout(this);
    QVBoxLayout* layout2 = new QVBoxLayout();
    QHBoxLayout* layout3 = new QHBoxLayout();

    sendButton = new QPushButton("send");
    sendButton->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    sendButton->setMinimumSize(60,60);

    commandInput = new QLineEdit(this);
    commandInput->setMaxLength(1);
    commandInput->setAlignment(Qt::AlignCenter);
    commandInput->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    commandInput->setFixedSize(50,50);
    commandInput->setStyleSheet("color:gray; font-size: 25px;");

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
    layout1->addWidget(commandInput);
    layout1->addLayout(layout2);
    layout1->addWidget(sendButton);
}
