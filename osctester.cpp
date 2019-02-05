#include "osctester.h"
#include "ui_osctester.h"
#include <QDebug>

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
    QString a = ui->oscMessage->text();
    QStringList as = a.split(" ");  // TODO: make a class to manage the input data for oscSender
    QOSCMessage *message = new QOSCMessage(as[0]);

    message->addInt(as[1].toInt());  // TODO: needed to chacke if the input is int or not
    message->addInt(as[2].toInt());
    message->addInt(as[3].toInt());
    _oscSender->send(message);

    qInfo() << as;
}
