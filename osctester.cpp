#include "osctester.h"
#include "ui_osctester.h"

OscTester::OscTester(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OscTester)
{
    _scroll = new VerticalScrollArea(3, 1, this);
    ui->setupUi(this);
    ui->verticalLayout_2->addWidget(_scroll);
}

OscTester::~OscTester()
{
    delete ui;
}

void OscTester::closeEvent(QCloseEvent *event){
    // TODO: the correct way to finish the program.
    QApplication::quit();
    event->ignore();
    exit(EXIT_SUCCESS);
//    exit(EXIT_FAILURE);
}

void OscTester::on_addContainer_clicked(){
    containers.append(new SendContainer(i-1, this));
    _scroll->addWidget(containers.back(),i-1,1);
    i ++;
}
