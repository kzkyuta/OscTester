#include "osctester.h"
#include "ui_osctester.h"

OscTester::OscTester(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OscTester)
{
//    SendContainer::containerNum = 0;
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
    containers.append(new SendContainer(this));
    _scroll->addWidget(containers.back(), SendContainer::containerNum, 1);
}

void OscTester::on_importJson_clicked(){
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Json File"),
                "C://",
                "All files (*.*);; Json File (*.json)");
    if(fileName=="")
    {   //CANCEL
        return;
    }

    QFile openFile(fileName);
    openFile.open(QIODevice::ReadOnly);
    QByteArray data = openFile.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    QJsonObject jsonObj(jsonDoc.object());
    QJsonArray jsonArr = jsonObj.value("containerList").toArray();
    for(int i = 0; i < jsonArr.size(); i++){
        containers.append(new SendContainer(this));
        _scroll->addWidget(containers.back(), SendContainer::containerNum, 1);
        QJsonObject temp = jsonArr[i].toObject();
        containers[SendContainer::containerNum - 1]->setMsg(temp["address"].toString());
        containers[SendContainer::containerNum - 1]->setPort(temp["port"].toString());
        containers[SendContainer::containerNum - 1]->setIp(temp["ip"].toString());
    }
    qInfo() << SendContainer::containerNum;
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
    jsonObjParent["containerList"] = jsonArr;
    QJsonDocument jsonDoc(jsonObjParent);

    // get QByteArray data from jsonDoc
    QByteArray data(jsonDoc.toJson());

    // Write Data on file which user named
    QFile saveFile(fileName);
    saveFile.open(QIODevice::WriteOnly);
    saveFile.write(data);
    saveFile.close();
}
