#ifndef OSCTESTER_H
#define OSCTESTER_H

#include "qoscsender.h"

#include <QMainWindow>
#include <vector>

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
