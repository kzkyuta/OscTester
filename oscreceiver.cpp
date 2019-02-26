#include "oscreceiver.h"
#include "ui_oscreceiver.h"
#include <QMessageBox>

uint8_t ReceiverTabArea::tabNum = 0;

bool OscReceiver::windowStatus = false;

OscReceiver::OscReceiver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OscReceiver)
{
    ui->setupUi(this);
    ReceiverTabArea::tabNum = 0;
    windowStatus = true;
}

OscReceiver::~OscReceiver()
{
    QApplication::quit();
    exit(EXIT_SUCCESS);
    delete ui;
}

void OscReceiver::closeEvent(QCloseEvent *event){
    // TODO: the correct way to finish the program.
    windowStatus = false;
}

bool OscReceiver::getWindowStatus(){
    return windowStatus;
}
void OscReceiver::setWindowStatus(bool status){
    windowStatus = status;
}

void OscReceiver::on_pushButton_clicked(){
    addreceiverTab();
}

void OscReceiver::on_lineEdit_returnPressed(){
    addreceiverTab();
}

void OscReceiver::addreceiverTab(){
    QString portString = ui->lineEdit->text();
    bool isSuccess;
    unsigned int portNum = portString.toInt(&isSuccess, 10);
    if(!isSuccess) return;
    ui->lineEdit->clear();

    // if the selected port was used already, program shows error dialog
    try {
        tabCotents.append(new ReceiverTabArea(portNum,this));
    } catch (...) {
        QMessageBox::warning(this, tr("Error"), tr("This port is already used"));
        return;
    }

    if(tabArea == nullptr){
        tabArea = new QTabWidget(this);
        ui->verticalLayout->addWidget(tabArea);
    }
    tabArea->addTab(tabCotents.back(), portString);
}
