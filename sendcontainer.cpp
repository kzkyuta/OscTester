#include "sendcontainer.h"

SendContainer::SendContainer(uint8_t id, QWidget *parent)
    :QFrame(parent), id(id)
{
    // set frame default size
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    setMinimumSize(0,65);
    setFrameShape(Panel);

    // make a grid instance in QFrame
    QHBoxLayout *layout1 = new QHBoxLayout(this);
    QVBoxLayout* layout2 = new QVBoxLayout();
    QHBoxLayout* layout3 = new QHBoxLayout();

    QPushButton *sendButton = new QPushButton("send");
    sendButton->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    sendButton->setMinimumSize(60,60);

    QLineEdit *msg = new QLineEdit(this);
    msg->setPlaceholderText("OSC Message");

    QLineEdit *port = new QLineEdit(this);
    port->setPlaceholderText("port");

    QLineEdit *ip = new QLineEdit(this);
    ip->setPlaceholderText("IP Adress");

    layout3->addWidget(port);
    layout3->addWidget(ip);
    layout2->addWidget(msg);
    layout2->addLayout(layout3);
    layout1->addLayout(layout2);
    layout1->addWidget(sendButton);

//    formGrid->setContentsMargins(0,0,0,0);
//    formGrid->setAlignment(Qt::AlignHCenter);
//    formGrid->addWidget(msg, 0,0,0,2);
//    formGrid->addWidget(port, 1,0);
//    formGrid->addWidget(ip, 1,1);
//    formGrid->addWidget(sendButton, 0,2,2,2);
}

