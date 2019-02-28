#include "qoscsender.h"
#include <QDebug>

QOSCSender::QOSCSender(QString remoteHostS, unsigned int remotePortUI, QObject *parent) :
    QObject(parent),
    _remoteHostS(remoteHostS),
    _remotePortUI(remotePortUI)
{
    setup();
}
void QOSCSender::setup()
{
    _socket = new UdpTransmitSocket(IpEndpointName(_remoteHostS.toStdString().c_str(), _remotePortUI));
}

void QOSCSender::send(QOSCMessage *message)
{
    char buffer[1024];
    osc::OutboundPacketStream packet(buffer, 1024);
    packet << osc::BeginBundleImmediate << osc::BeginMessage(message->getAddress().toStdString().c_str());
    foreach(QOSCArgument *argument, message->getArguments())
    {

        if(argument->_type == QOSCARGUMENT_INT)
        {
            packet << static_cast<QOSCArgument_int*>(argument)->_value;
        }
        else if(argument->_type == QOSCARGUMENT_FLOAT)
        {
            packet << (float) static_cast<QOSCArgument_float*>(argument)->_value;
        }
        else if(argument->_type == QOSCARGUMENT_STRING)
        {
            packet << static_cast<QOSCArgument_string*>(argument)->_value.toStdString().c_str();
        }
        else if(argument->_type == QOSCARGUMENT_BLOB)
        {
            osc::Blob b(static_cast<QOSCArgument_blob*>(argument)->_value, (unsigned long) static_cast<QOSCArgument_blob*>(argument)->_value.size());
            packet << b;
        }
        else if(argument->_type == QOSCARGUMENT_BOOL)
        {
            packet << static_cast<QOSCArgument_bool*>(argument)->_value;
        }
        else if(argument->_type == QOSCARGUMENT_IMPULSE)
        {
            osc::InfinitumType value;
            packet << value;
        }
        else if(argument->_type == QOSCARGUMENT_NULL)
        {
            osc::NilType value;
            packet << value;
        }
        else if(argument->_type == QOSCARGUMENT_TIME)
        {
            qDebug()<<"TODO"<<"oscSender type time";
        }
    }

    packet << osc::EndMessage
    << osc::EndBundle;
    _socket->Send(packet.Data(), packet.Size());

/*
    _socket->Send(message.getPacket()->Data(), message.getPacket()->Size());


    _packet.Clear();
    _packet << osc::BeginBundleImmediate << osc::BeginMessage(_address.toStdString().c_str());
    foreach(qTGOscArgument* argument, _arguments)
    {

        if(argument->_type == QTGOSCARGUMENT_INT)
        {
            _packet << static_cast<qTGOscArgument_int*>(argument)->_value;
        }
        else if(argument->_type == QTGOSCARGUMENT_FLOAT)
        {
            _packet << (float) static_cast<qTGOscArgument_float*>(argument)->_value;
        }
        else if(argument->_type == QTGOSCARGUMENT_BOOL)

        {
            _packet << static_cast<qTGOscArgument_bool*>(argument)->_value;
        }
        else if(argument->_type == QTGOSCARGUMENT_STRING)
        {
            _packet << static_cast<qTGOscArgument_string*>(argument)->_value.toStdString().c_str();
        }
    }
    */
}

void QOSCSender::send(QOSCBundle bundle)
{
//    _socket->Send(message.getPacket()->Data(), message.getPacket()->Size());
}

osc::OutboundPacketStream QOSCSender::makeBundlePacket(QOSCBundle bundle){
    char buffer[1024];
    osc::OutboundPacketStream packet(buffer, 1024);

    packet << osc::BeginBundleImmediate;
    foreach(QOSCMessage *message, bundle.getMessages()){

        packet << osc::BeginMessage(message->getAddress().toStdString().c_str());

        foreach(QOSCArgument* argument, message->getArguments()){

            if(argument->_type == QOSCARGUMENT_INT)
            {
                packet << static_cast<QOSCArgument_int*>(argument)->_value;
            }
            else if(argument->_type == QOSCARGUMENT_FLOAT)
            {
                packet << (float) static_cast<QOSCArgument_float*>(argument)->_value;
            }
            else if(argument->_type == QOSCARGUMENT_STRING)
            {
                packet << static_cast<QOSCArgument_string*>(argument)->_value.toStdString().c_str();
            }
            else if(argument->_type == QOSCARGUMENT_BLOB)
            {
                osc::Blob b(static_cast<QOSCArgument_blob*>(argument)->_value, (unsigned long) static_cast<QOSCArgument_blob*>(argument)->_value.size());
                packet << b;
            }
            else if(argument->_type == QOSCARGUMENT_BOOL)
            {
                packet << static_cast<QOSCArgument_bool*>(argument)->_value;
            }
            else if(argument->_type == QOSCARGUMENT_IMPULSE)
            {
                osc::InfinitumType value;
                packet << value;
            }
            else if(argument->_type == QOSCARGUMENT_NULL)
            {
                osc::NilType value;
                packet << value;
            }
            else if(argument->_type == QOSCARGUMENT_TIME)
            {
                qDebug()<<"TODO"<<"oscSender type time";
            }
        }
        packet << osc::EndMessage;

    }

    packet<< osc::EndBundle;

    return packet;
}

void QOSCSender::sendBundle(QOSCBundle bundle){
     osc::OutboundPacketStream packet = makeBundlePacket(bundle);
    _socket->Send(packet.Data(), packet.Size());
}

void QOSCSender::sendMessage(QOSCMessage *message)
{
    char buffer[1024];
    osc::OutboundPacketStream packet(buffer, 1024);
    packet << osc::BeginMessage(message->getAddress().toStdString().c_str());
    foreach(QOSCArgument *argument, message->getArguments())
    {

        if(argument->_type == QOSCARGUMENT_INT)
        {
            packet << static_cast<QOSCArgument_int*>(argument)->_value;
        }
        else if(argument->_type == QOSCARGUMENT_FLOAT)
        {
            packet << (float) static_cast<QOSCArgument_float*>(argument)->_value;
        }
        else if(argument->_type == QOSCARGUMENT_STRING)
        {
            packet << static_cast<QOSCArgument_string*>(argument)->_value.toStdString().c_str();
        }
        else if(argument->_type == QOSCARGUMENT_BLOB)
        {
            osc::Blob b(static_cast<QOSCArgument_blob*>(argument)->_value, (unsigned long) static_cast<QOSCArgument_blob*>(argument)->_value.size());
            packet << b;
        }
        else if(argument->_type == QOSCARGUMENT_BOOL)
        {
            packet << static_cast<QOSCArgument_bool*>(argument)->_value;
        }
        else if(argument->_type == QOSCARGUMENT_IMPULSE)
        {
            osc::InfinitumType value;
            packet << value;
        }
        else if(argument->_type == QOSCARGUMENT_NULL)
        {
            osc::NilType value;
            packet << value;
        }
        else if(argument->_type == QOSCARGUMENT_TIME)
        {
            qDebug()<<"TODO"<<"oscSender type time";
        }
    }

    packet << osc::EndMessage;
    _socket->Send(packet.Data(), packet.Size());
}

void QOSCSender::setRemoteHost(QString remoteHostS)
{
    _remoteHostS = remoteHostS;
}
void QOSCSender::setRemotePort(unsigned int remotePortUI)
{
    _remotePortUI = remotePortUI;
}
