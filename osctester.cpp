#include "osctester.h"
#include "ui_osctester.h"

OscTester::OscTester(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OscTester)
{
    this->windowLayoutinit();
    this->menuInit();

    // show oscReceiver
    w.show();

    readSettings();
}

OscTester::~OscTester()
{
    writeSettings();
    delete ui;
}

void OscTester::closeEvent(QCloseEvent *event){
    windowStatus = false;
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
    jsonFileImport(fileName);
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
    jsonFileExport(fileName);
}

void OscTester::jsonFileImport(QString fileName){

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
        containers[SendContainer::containerNum - 1]->setComm(temp["command"].toString());
        containers[SendContainer::containerNum - 1]->setMsg(temp["address"].toString());
        containers[SendContainer::containerNum - 1]->setPort(temp["port"].toString());
        containers[SendContainer::containerNum - 1]->setIp(temp["ip"].toString());
    }
}

void OscTester::jsonFileExport(QString fileName){
    // set Json File Data
    QJsonObject jsonObjParent, jsonObjChild;
    QJsonArray jsonArr;
    for(int i =0; i < containers.size(); i++){
        jsonObjChild["command"] = containers[i]->getComm();
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
    if(saveFile.open(QIODevice::WriteOnly | QIODevice::Append)){
        saveFile.write(data);
        saveFile.close();
    }
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
        this->show();
    }
}

void OscTester::showReveiverWindow(){
    if(!OscReceiver::getWindowStatus()){
        w.show();
    }
}

void OscTester::showAboutApp(){
    if(!AboutOscTesterApp::getWindowStatus()){
        a.show();
    }
}

void OscTester::alwaysOnTopCheck(){
    // change the window mode with Bitwise Operators
    if(alwaysOnTop->isChecked()) flags |= Qt::WindowStaysOnTopHint;
    else flags ^= Qt::WindowStaysOnTopHint;

    // set settings
    this->setWindowFlags(flags);
    w.setWindowFlags(flags);
    this->show();
    w.show();
}

void OscTester::windowLayoutinit(){
    _scroll = new VerticalScrollArea(3, 1, this);
    ui->setupUi(this);
    ui->verticalLayout_2->addWidget(_scroll);
    windowStatus = true;
}

void OscTester::menuInit(){

    QMenuBar *menuBar = new QMenuBar(0);
    QMenu *fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction(tr("&Save"), this, SLOT(), QKeySequence::Open);
    fileMenu->addAction(tr("&Save as"), this, SLOT(), QKeySequence::Close);

    fileMenu->addAction(tr("about.*"), this, SLOT(showAboutApp()));
//    fileMenu->addAction(tr("preferences"), this, SLOT(optionPanelView()));

    QMenu *windowMenu = menuBar->addMenu("&Window");
    windowMenu->addAction(tr("&Sender"), this, SLOT(showSenderWindow()), QKeySequence::Save);
    windowMenu->addAction(tr("&Receiver"), this, SLOT(showReveiverWindow()), QKeySequence::Refresh);

    alwaysOnTop = new QAction("Always on Top of Window", this);
    alwaysOnTop->setCheckable(true);
    alwaysOnTop->setChecked(false);
    connect(alwaysOnTop, SIGNAL(triggered()), this, SLOT(alwaysOnTopCheck()));

    QMenu *viewMenu = menuBar->addMenu("&View");
    viewMenu->addAction(alwaysOnTop);
}

void OscTester::writeSettings(){
    // instance for saving sate and geometry.
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,"KZK", "OSC Tester");
    // groupe for Sender window
    settings.beginGroup("Sender");
    settings.setValue("geometry", this->saveGeometry());
    settings.setValue("state", this->saveState());
    settings.setValue("containerNum", SendContainer::containerNum);
    settings.endGroup();

    // groupe for each container value
    for(int i = 0; i < SendContainer::containerNum; i++){
        settings.beginGroup("container" + QString::number(i));
        settings.setValue("command", containers[i]->getComm());
        settings.setValue("message", containers[i]->getMsg());
        settings.setValue("port", containers[i]->getPort());
        settings.setValue("ip", containers[i]->getIp());
        settings.endGroup();
    }

    // groupe for receiver
    settings.beginGroup("Receiver");
    settings.setValue("geometry", w.saveGeometry());
    settings.setValue("state", w.saveState());
    settings.setValue("containerNum", ReceiverTabArea::tabNum);
    for(int i = 0; i < ReceiverTabArea::tabNum; i++){
        settings.setValue("portNum" + QString::number(i), QString::number(w.tabCotents[i]->getPort()));
        settings.setValue("Filter" + QString::number(i), w.tabCotents[i]->getFilter());
    }
    settings.endGroup();
}

void OscTester::readSettings(){
    // instance for saving sate and geometry.
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,"KZK", "OSC Tester");

    // read data for geometry and state for sender window.
    this->restoreGeometry(settings.value("Sender/geometry").toByteArray());
    this->restoreState(settings.value("Sender/state").toByteArray());

    // read data for each containers
    for(int i = 0; i < settings.value("Sender/containerNum").toInt(); i++){
        // add sendContainer instance to vector list
        containers.append(new SendContainer(this));
        _scroll->addWidget(containers.back(), i + 1, 1);

        // read each data
        containers[i]->setComm(settings.value("container" + QString::number(i) + "/command").toString());
        containers[i]->setMsg(settings.value("container" + QString::number(i) + "/message").toString());
        containers[i]->setPort(settings.value("container" + QString::number(i) + "/port").toString());
        containers[i]->setIp(settings.value("container" + QString::number(i) + "/ip").toString());
    }

    // read data for receiver
    w.restoreGeometry(settings.value("Receiver/geometry").toByteArray());
    w.restoreState(settings.value("Receiver/state").toByteArray());

    // read each data
    for(int i = 0; i < settings.value("Receiver/containerNum").toInt(); i ++){
        w.addreceiverTab(settings.value("Receiver/portNum" + QString::number(i)).toString());
        w.tabCotents[i]->setFilter(settings.value("Receiver/Filter" + QString::number(i)).toString());
    }
}
