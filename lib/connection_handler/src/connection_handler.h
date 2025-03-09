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
}

#endif