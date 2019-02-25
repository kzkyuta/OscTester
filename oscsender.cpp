#include "oscsender.h"
#include "ui_oscsender.h"

bool OscSender::windowStatus = false;

OscSender::OscSender(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OscSender)
{
    windowStatus = true;
    _scroll = new VerticalScrollArea(3, 1, this);
    ui->setupUi(this);
    ui->verticalLayout->addWidget(_scroll);
}

OscSender::~OscSender()
{
    delete ui;
}

bool OscSender::getWindowSatus(){
    return windowStatus;
}

void OscSender::setWindowSatus(bool status){
    windowStatus = status;
}

void OscSender::closeEvent(QCloseEvent *event){
    // TODO: the correct way to finish the program.
    windowStatus = false;
}

void OscSender::on_addContainer_clicked(){
    containers.append(new SendContainer(this));
    _scroll->addWidget(containers.back(), SendContainer::containerNum, 1);
}

void OscSender::on_importJson_clicked(){
    // Open file Dialog and get file name
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Json File"),
                "C://",
                "All files (*.*);; Json File (*.json)");
    if(fileName=="")
    {   //CANCEL
        return;
    }

    // open file and set ReadOnly mode
    QFile openFile(fileName);
    openFile.open(QIODevice::ReadOnly);

    // input all data to QByteArray data
    QByteArray data = openFile.readAll();
    // read as json
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    QJsonObject jsonObj(jsonDoc.object());
    // get Array data
    QJsonArray jsonArr = jsonObj.value("containerList").toArray();
    // set all values on sendcontainer class.
    for(int i = 0; i < jsonArr.size(); i++){
        containers.append(new SendContainer(this));
        _scroll->addWidget(containers.back(), SendContainer::containerNum, 1);
        QJsonObject temp = jsonArr[i].toObject();
        containers[SendContainer::containerNum - 1]->setMsg(temp["address"].toString());
        containers[SendContainer::containerNum - 1]->setPort(temp["port"].toString());
        containers[SendContainer::containerNum - 1]->setIp(temp["ip"].toString());
    }
}

void OscSender::on_exportJson_clicked(){
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

void OscSender::keyPressEvent(QKeyEvent* event){
    QVector<int> selectedContainers;
    for(int i = 0; i < SendContainer::containerNum; i ++){
        if(event->key() == containers[i]->commandInput->text()[0].unicode()){
            containers[i]->changeContainerColor(true);
            selectedContainers.append(i);
        }
    }
    if(selectedContainers.size() == 0) return;
    else if(selectedContainers.size() == 1){
        containers[selectedContainers[0]]->sendOscMessage();
    }else{
        if(checkBundleSender(containers, selectedContainers)){
            bundleSender = new QOSCSender(BundleIp, Bundleport.toInt(), this);
            bundleMessage = new QOSCBundle();
            if(setBundleMessage(bundleMessage, containers, selectedContainers)){
                bundleSender->sendBundle(*bundleMessage);
            }
            delete bundleMessage;
            delete bundleSender;
        }else{
            for(int i = 0; i < SendContainer::containerNum; i++){
                containers[i]->changeContainerColor(false);
            }
            return;
        }
    }
}

void OscSender::keyReleaseEvent(QKeyEvent* event){
    for(int i = 0; i < SendContainer::containerNum; i ++){
        if(event->key() == containers[i]->commandInput->text()[0].unicode()){
            containers[i]->changeContainerColor(false);
        }
    }
}

bool OscSender::checkBundleSender(QVector<SendContainer *> containers, QVector<int> selectedMsg){
    BundleIp = containers[selectedMsg[0]]->getIp();
    Bundleport = containers[selectedMsg[0]]->getPort();

    if((!BundleIp.isNull() && !Bundleport.isNull()) && (!BundleIp.isEmpty() && !Bundleport.isEmpty())){
        foreach(int containerNum, selectedMsg){
            if(BundleIp == containers[selectedMsg[containerNum]]->getIp() &&
                    Bundleport == containers[selectedMsg[containerNum]]->getPort()){
                return true;
            }else{
                QMessageBox::warning(this, tr("Error"), tr("please match Port or IP values."));
                return false;
            }
        }
    }else{
        QMessageBox::warning(this, tr("Error"), tr("Put Port number and Ip"));
        return false;
    }
}

bool OscSender::setBundleMessage(QOSCBundle* bundleMessage, QVector<SendContainer*> containers, QVector<int> selectedMsg){
    foreach(int containerNum, selectedMsg){
        try {
            bundleMessage->addMessage(containers[containerNum]->outOscMessage());
        } catch (...) {
            QMessageBox::warning(this, tr("Error"), tr("Could not add OscMessages to bundle container"));
            return false;
        }
    }
    return true;
}

