#ifndef OSCSENDER_H
#define OSCSENDER_H

#include "qoscsender.h"
#include "qoscreceiver.h"
#include "inputconverter.h"
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
class OscSender;
}

class OscSender : public QMainWindow
{
    Q_OBJECT

public:
    explicit OscSender(QWidget *parent = nullptr);
    ~OscSender();

    QString BundleIp;
    QString Bundleport;

    QOSCReceiver *_oscReceiver;
    VerticalScrollArea *_scroll;
    QVector<SendContainer*> containers;
    bool checkBundleSender(QVector<SendContainer*>, QVector<int>);
    bool setBundleMessage(QOSCBundle*, QVector<SendContainer*>, QVector<int>);

    QOSCSender *bundleSender;
    QOSCBundle *bundleMessage;

    static bool getWindowSatus();
    static void setWindowSatus(bool);

private:
    Ui::OscSender *ui;
    void closeEvent(QCloseEvent *event);
    static bool windowStatus;

protected:
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

private slots:
    void on_addContainer_clicked();
    void on_importJson_clicked();
    void on_exportJson_clicked();
};

#endif // OSCSENDER_H
