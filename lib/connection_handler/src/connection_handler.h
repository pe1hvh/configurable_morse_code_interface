#ifndef CONNECTION_HANDLER_H_
#define CONNECTION_HANDLER_H_

#include <Arduino.h>
#include <SimpleWebSerial.h>
#include <ArduinoJson.h>
#include "config_handler.h"

namespace NsConnection {

    void sendInitialValues();
    void updateValues(JSONVar data);
    void maintainWebUSB();
    const char* getStartText(uint8_t startText);
    const char* getNameMorseKey(uint8_t typeMorseKey);
    const char* getNameTypeEvent(uint8_t typeEvent);
    const char* getNameEvent(uint8_t event);

}

#endif