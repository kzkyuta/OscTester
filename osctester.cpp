#include "osctester.h"


OscTester::OscTester(QWidget *parent) :
    QMainWindow(parent),
//    _oscSender(new QOSCSender("127.0.0.1", 10002, this)),
    _oscReceiver(new QOSCReceiver(10001, this)),
    ui(new Ui::OscTester)
{
    connect(_oscReceiver, SIGNAL(messageReceived(QOSCMessage*)), this, SLOT(onMessageReceived(QOSCMessage*)));
//    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    _oscReceiver->start();

    ui->setupUi(this);
}

OscTester::~OscTester()
{
    delete ui;
}

void OscTester::on_sendMessage_clicked(){
    // inputConverter converts input text to command for osc sender
    InputConverter* inputMessage = new InputConverter(ui->oscMessage->text());
    inputMessage->setMessage();

    if(!ui->ip->text().isNull() && !ui->port->text().isNull()) if(!ui->ip->text().isEmpty() && !ui->port->text().isEmpty()) {
        _oscSender = new QOSCSender(ui->ip->text(), ui->port->text().toInt(), this);
        _oscSender->send(inputMessage->getMessage());
    }

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

void OscTester::onMessageReceived(QOSCMessage *msg){
    QDateTime time = QDateTime::currentDateTime();
    QString msgOut;
    msgOut.append(time.toString("MM/dd/hh:mm:ss") + " ");
    msgOut.append(msg->getAddress());
    ui->receivedMsg->append(msgOut);
}

void OscTester::closeEvent(QCloseEvent *event){
    // TODO: the correct way to finish the program.
    QApplication::quit();
    event->ignore();
    exit(EXIT_SUCCESS);
//    exit(EXIT_FAILURE);
}
