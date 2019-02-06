#ifndef OSCTESTER_H
#define OSCTESTER_H

#include "qoscsender.h"
#include "qoscreceiver.h"
#include "inputconverter.h"
#include "ui_osctester.h"

#include <QMainWindow>
#include <vector>
#include <QDebug>
#include <QTime>
#include <QCloseEvent>

namespace Ui {
class OscTester;
}

class OscTester : public QMainWindow
{
    Q_OBJECT

public:
    explicit OscTester(QWidget *parent = nullptr);
    ~OscTester();

private slots:
    void on_sendMessage_clicked();

private:
    QOSCSender *_oscSender;
    Ui::OscTester *ui;

};

#endif // OSCTESTER_H
