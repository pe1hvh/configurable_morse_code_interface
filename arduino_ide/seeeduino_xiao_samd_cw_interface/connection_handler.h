#ifndef CONNECTION_HANDLER_H_
#define CONNECTION_HANDLER_H_

#include <Arduino.h>
#include <SimpleWebSerial.h>
#include <ArduinoJson.h>
#include "config_handler.h"

namespace NsConnection {


    extern int typeMorseKey;
    extern int typeEvent;
    extern int leftEvent;
    extern int rightEvent;

    void sendInitialValues(JSONVar data);
    void updateValues(JSONVar data);
    void maintainWebUSB();
    void getConfig();
    void setConnection();

}
#endif