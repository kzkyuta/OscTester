#ifndef RECEIVERTABAREA_H
#define RECEIVERTABAREA_H
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QLayout>


class ReceiverTabArea : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiverTabArea(int, QWidget* = nullptr);
//    ~ReceiverTabArea();
    static uint8_t tabNum;
    uint8_t getTabNum();
private slots:
//    void filter();

private:
    int port;
    QLineEdit *filter;
    QTextEdit *receivedMsg;
    QVBoxLayout *parentLayout;
};

#endif // RECEIVERTABAREA_H
