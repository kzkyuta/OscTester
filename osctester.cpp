#include "osctester.h"
#include "ui_osctester.h"


OscTester::OscTester(QWidget *parent) :
    QMainWindow(parent),
//    _oscSender(new QOSCSender("127.0.0.1", 10002, this)),
    ui(new Ui::OscTester),
    _oscReceiver(new QOSCReceiver(10001, this))
//    _scroll(new VerticalScrollArea(nrows,ncols, this))
{
    connect(_oscReceiver, SIGNAL(messageReceived(QOSCMessage*)), this, SLOT(onMessageReceived(QOSCMessage*)));
//    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    _scroll = new VerticalScrollArea(1, 4, this);
    _oscReceiver->start();
    ui->setupUi(this);
    ui->verticalLayout_2->addWidget(_scroll);
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

void OscTester::on_addContainer_clicked(){
//    SendContainer a(i,this);
    SendContainer * container = new SendContainer(i-1, this);
    containers.append(container);
    _scroll->addWidget(container,i,1);
    qInfo() << containers[i-1]->getId();
    i ++;
}
