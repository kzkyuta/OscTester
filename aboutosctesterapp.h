#ifndef ABOUTOSCTESTERAPP_H
#define ABOUTOSCTESTERAPP_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class AboutOscTesterApp;
}

class AboutOscTesterApp : public QDialog
{
    Q_OBJECT

public:
    explicit AboutOscTesterApp(QWidget *parent = nullptr);
    ~AboutOscTesterApp();
    static bool getWindowStatus();
    static void setWindowStatus(bool);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AboutOscTesterApp *ui;
    static bool windowStatus;
};

#endif // ABOUTOSCTESTERAPP_H
