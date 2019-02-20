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

void OscTester::on_importJson_clicked()
{

}

void OscTester::on_exportJson_clicked(){
    // Generate File Save Dialog
    QString fileName = QFileDialog::getSaveFileName(this,
                        tr("Save Json"), "",
                        tr("Json (*.json);;All Files (*)"));
    if(fileName=="")
    {   //CANCEL
        return;
    }

    // set Json File Data
    QJsonObject jsonObjParent, jsonObjChild;
    QJsonArray jsonArr;
    for(int i =0; i < containers.size(); i++){
        jsonObjChild["address"] = containers[i]->getMsg();
        jsonObjChild["port"] = containers[i]->getPort();
        jsonObjChild["ip"] = containers[i]->getIp();
        jsonArr.append(jsonObjChild);
    }
    jsonObjParent["ontainerList"] = jsonArr;
    QJsonDocument jsonDoc(jsonObjParent);

    // get QByteArray data from jsonDoc
    QByteArray data(jsonDoc.toJson());

    // Write Data on file which user named
    QFile saveFile(fileName);
    saveFile.open(QIODevice::WriteOnly);
    saveFile.write(data);
    saveFile.close();
}
