#include "osctester.h"


OscTester::OscTester(QWidget *parent) :
    QMainWindow(parent),
    _oscSender(new QOSCSender("127.0.0.1", 10002, this)),
    ui(new Ui::OscTester)
{
    ui->setupUi(this);
}

OscTester::~OscTester()
{
    delete ui;
}

void OscTester::on_sendMessage_clicked(){
    _oscSender = new QOSCSender(ui->ip->text(), ui->port->text().toInt(), this);
    InputConverter* inputMessage = new InputConverter(ui->oscMessage->text());
    inputMessage->setMessage();
    _oscSender->send(inputMessage->getMessage());

//    QString a = ui->oscMessage->text();
//    QStringList as = a.split(" ");  // TODO: make a class to manage the input data for oscSender
//    if(as[0].left(0) == "/"){
//        qInfo() << "OK!";
//    }
//    QOSCMessage *message = new QOSCMessage(as[0]);

//    message->addInt(as[1].toInt());  // TODO: needed to chacke if the input is int or not
//    message->addInt(as[2].toInt());
//    message->addInt(as[3].toInt());
//    _oscSender->send(message);


}
