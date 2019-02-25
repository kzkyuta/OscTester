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
    windowStatus = true;

    w.show();

    QMenuBar *menuBar = new QMenuBar(0);
    QMenu *fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction(tr("&Save"), this, SLOT(), QKeySequence::Open); // TODO: add function
    fileMenu->addAction(tr("&Save as"), this, SLOT(), QKeySequence::Close); // // TODO: add function

    QMenu *windowMenu = menuBar->addMenu("&Window");
    windowMenu->addAction(tr("&Sender"), this, SLOT(showSenderWindow()), QKeySequence::Save);
    windowMenu->addAction(tr("&Receiver"), this, SLOT(showReveiverWindow()), QKeySequence::Refresh);
    QMenu *viewMenu = menuBar->addMenu("&View");
    viewMenu->addAction(tr("&Always On Top"), this, SLOT(), QKeySequence::Refresh);
}

OscTester::~OscTester()
{
    delete ui;
}

void OscTester::closeEvent(QCloseEvent *event){
    // TODO: the correct way to finish the program.
    windowStatus = false;
//    QApplication::quit();
//    event->ignore();
//    exit(EXIT_SUCCESS);
}

void OscTester::on_addContainer_clicked(){
    containers.append(new SendContainer(this));
    _scroll->addWidget(containers.back(), SendContainer::containerNum, 1);
}

void OscTester::on_importJson_clicked(){  // TODO: file checker
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

void OscTester::keyPressEvent(QKeyEvent* event){
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

void OscTester::keyReleaseEvent(QKeyEvent* event){
    for(int i = 0; i < SendContainer::containerNum; i ++){
        if(event->key() == containers[i]->commandInput->text()[0].unicode()){
            containers[i]->changeContainerColor(false);
        }
    }
}

bool OscTester::checkBundleSender(QVector<SendContainer *> containers, QVector<int> selectedMsg){
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

bool OscTester::setBundleMessage(QOSCBundle* bundleMessage, QVector<SendContainer*> containers, QVector<int> selectedMsg){
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

void OscTester::showSenderWindow(){
    if(!windowStatus){
//    if(!OscSender::getWindowSatus()){
        this->show();
    }
}

void OscTester::showReveiverWindow(){
    if(!OscReceiver::getWindowStatus()){
        w.show();
    }
}
