#include "oscreceiver.h"
#include "ui_oscreceiver.h"

uint8_t ReceiverTabArea::tabNum = 0;

OscReceiver::OscReceiver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OscReceiver)
{
    ui->setupUi(this);
}

OscReceiver::~OscReceiver()
{
    delete ui;
}

void OscReceiver::on_pushButton_clicked(){
    QString portNum = ui->lineEdit->text();
    ui->lineEdit->clear();
    if(ReceiverTabArea::tabNum == 0){
//        tabArea = new ReceiverTabArea(portNum.toInt(), this);
        tabArea = new QTabWidget(this);
        ui->verticalLayout_2->addWidget(tabArea);
    }
    tabCotents.append(new ReceiverTabArea(portNum.toInt(),this));
    tabArea->addTab(tabCotents.back(), portNum);
}
