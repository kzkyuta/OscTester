#include "receivertabarea.h"

ReceiverTabArea::ReceiverTabArea(int portNum, QWidget* parent)
    :QWidget(parent), port(portNum)
{
    tabNum++;
    parentLayout = new QVBoxLayout(this);
    filter = new QLineEdit();
    receivedMsg = new QTextEdit();

    filter->setPlaceholderText("Insert filter sentence.");
    parentLayout->addWidget(filter);
    parentLayout->addWidget(receivedMsg);
}

uint8_t ReceiverTabArea::getTabNum(){
    return tabNum;
}
