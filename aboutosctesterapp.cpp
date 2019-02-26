#include "aboutosctesterapp.h"
#include "ui_aboutosctesterapp.h"

AboutOscTesterApp::AboutOscTesterApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutOscTesterApp)
{
    ui->setupUi(this);
    QPixmap pix("://resource/iconData.png");
    ui->label_pic->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));
}

AboutOscTesterApp::~AboutOscTesterApp()
{
    delete ui;
}

void AboutOscTesterApp::closeEvent(QCloseEvent *event){
    windowStatus = false;
}

bool AboutOscTesterApp::windowStatus = false;

bool AboutOscTesterApp::getWindowStatus(){
    return windowStatus;
}

void AboutOscTesterApp::setWindowStatus(bool status){
    windowStatus = status;
}

void AboutOscTesterApp::on_pushButton_clicked(){
    this->close();
}
