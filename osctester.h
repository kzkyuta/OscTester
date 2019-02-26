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
#include <QPointer>
#include "qoscbundle.h"
#include "verticalscrollarea.h"
#include "sendcontainer.h"
#include "aboutosctesterapp.h"

namespace Ui {
class OscTester;
}

class OscTester : public QMainWindow
{
    Q_OBJECT

public:
    explicit OscTester(QWidget *parent = nullptr);
    ~OscTester();

    // for layouts
    QOSCReceiver *_oscReceiver;
    VerticalScrollArea *_scroll;
    QVector<SendContainer*> containers;

    // for osc sending function.
    QString BundleIp;
    QString Bundleport;
    QOSCSender *bundleSender;
    QOSCBundle *bundleMessage;
    bool checkBundleSender(QVector<SendContainer*>, QVector<int>);
    bool setBundleMessage(QOSCBundle*, QVector<SendContainer*>, QVector<int>);

private:
    Ui::OscTester *ui;
    void closeEvent(QCloseEvent *event);

    // window management
    QPointer<QAction> alwaysOnTop;
    bool windowStatus;
    void windowLayoutinit();
    void menuInit();

private slots:
    // osc sender function
    void on_addContainer_clicked();
    void on_importJson_clicked();
    void on_exportJson_clicked();

    // window management
    void showSenderWindow();
    void showReveiverWindow();
    void showAboutApp();
    void alwaysOnTopCheck();

protected:
    // for sending osc command.
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

    // argument for osc receiver and it's instance will be generate on this class.
    OscReceiver w;
    AboutOscTesterApp a;

    // for on top of window function.
    Qt::WindowFlags flags = nullptr;
};

#endif // OSCTESTER_H
