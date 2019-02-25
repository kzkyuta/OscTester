#ifndef OSCTESTER_H
#define OSCTESTER_H

#include "qoscsender.h"
#include "qoscreceiver.h"
#include "inputconverter.h"
#include "oscreceiver.h"

#include <QMainWindow>
#include <vector>
#include <QDebug>
#include <QTime>
#include <QCloseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMenuBar>
#include "qoscbundle.h"
#include "verticalscrollarea.h"
#include "sendcontainer.h"

namespace Ui {
class OscTester;
}

class OscTester : public QMainWindow
{
    Q_OBJECT
private:
    Ui::OscTester *ui;
    void closeEvent(QCloseEvent *event);
public:
    QString BundleIp;
    QString Bundleport;

    explicit OscTester(QWidget *parent = nullptr);
    ~OscTester();
    QOSCReceiver *_oscReceiver;
    VerticalScrollArea *_scroll;
    QVector<SendContainer*> containers;
    bool checkBundleSender(QVector<SendContainer*>, QVector<int>);
    bool setBundleMessage(QOSCBundle*, QVector<SendContainer*>, QVector<int>);

    QOSCSender *bundleSender;
    QOSCBundle *bundleMessage;

    bool windowStatus;

private slots:
    void on_addContainer_clicked();
    void on_importJson_clicked();
    void on_exportJson_clicked();
    void showSenderWindow();
    void showReveiverWindow();

protected:
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    OscReceiver w;
};

#endif // OSCTESTER_H
