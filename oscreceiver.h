#ifndef OSCRECEIVER_H
#define OSCRECEIVER_H

#include <QMainWindow>
#include <QTabWidget>
#include "receivertabarea.h"

namespace Ui {
class OscReceiver;
}

class OscReceiver : public QMainWindow
{
    Q_OBJECT

public:
    explicit OscReceiver(QWidget *parent = nullptr);
    ~OscReceiver();
    QTabWidget *tabArea = nullptr;
    QVector<ReceiverTabArea*> tabCotents;

    static bool getWindowStatus();
    static void setWindowStatus(bool);

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();

private:
    Ui::OscReceiver *ui;
    void addreceiverTab();
    static bool windowStatus;
    void closeEvent(QCloseEvent *event);
};

#endif // OSCRECEIVER_H
