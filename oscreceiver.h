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

private slots:
    void on_pushButton_clicked();

private:
    Ui::OscReceiver *ui;
};

#endif // OSCRECEIVER_H
