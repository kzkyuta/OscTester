#include "aboutosctesterapp.h"
#include "ui_aboutosctesterapp.h"

AboutOscTesterApp::AboutOscTesterApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutOscTesterApp)
{
    ui->setupUi(this);
    QPixmap pix("/Users/kozakiyuta/Qt/apps/OscTester/iconData/iconData.png");
    ui->label_pic->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));

}

AboutOscTesterApp::~AboutOscTesterApp()
{
    delete ui;
}

void AboutOscTesterApp::on_pushButton_clicked(){
    this->close();
}
