#include "inputconverter.h"

InputConverter::InputConverter(QString m_string)
    : _row_data(m_string)
{
//    setMessage();
}

InputConverter::~InputConverter(){
}

void InputConverter::setMessage(){
    QStringList m_string_list = _row_data.split(" ");
    for(int i = 0; i< m_string_list.length(); i++){
        if(i == 0){
            if(m_string_list[i].left(1) == "/"){
                _message = new QOSCMessage(m_string_list[0]);
            }else{
                _message = new QOSCMessage("");
                return;  // TODO: return the status if the argument was correct or not.
            }
        }else{
            int argInt = m_string_list[i].toInt(&cast_int_result);
            qInfo() << cast_int_result;
            if(cast_int_result){
                qInfo() << argInt;
                _message->addInt(argInt);
                continue;
            }else{
                float argFloat = m_string_list[i].toFloat(&cast_float_result);
                if(cast_float_result){
                    _message->addFloat(argFloat);
                    continue;
                }else{
                    _message->addString(m_string_list[i]);
                }
            }
        }
    }
}

QOSCMessage* InputConverter::getMessage(){
    return _message;
}
