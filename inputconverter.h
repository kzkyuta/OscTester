#ifndef INPUTCONVERTER_H
#define INPUTCONVERTER_H

#include <QObject>
#include "qoscmessage.h"
#include <QDebug>

class InputConverter
{
public:
    InputConverter(QString);
    ~InputConverter();
    int getEleNum();
    void setMessage();
    QOSCMessage* getMessage();
private:
    QString _row_data;
    QString _address;
    int eleNum;
    QOSCMessage* _message;
    bool cast_int_result;
    bool cast_float_result;
    bool cast_string_result;
};

#endif // INPUTCONVERTER_H
