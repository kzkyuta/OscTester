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
    void addreceiverTab(QString);

    static bool getWindowStatus();
    static void setWindowStatus(bool);

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();

//    void on_clearSelectedTab_clicked();

    void on_clearAll_clicked();

private:
    Ui::OscReceiver *ui;
    void closeEvent(QCloseEvent *event);
    static bool windowStatus;
};

#endif // OSCRECEIVER_H
