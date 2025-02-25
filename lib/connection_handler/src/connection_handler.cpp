
#include "connection_handler.h"

namespace NsConnection {
  
    SimpleWebSerial WebSerial;


    /******************************************/
    /* @brief  Send Initial Values to Webpage */
    /******************************************/
    void sendInitialValues(JSONVar data) {
        data["typeMorseKey"] = NsConfigurator::myConfig.getTypeMorseKey();
        data["typeEvent"]    = NsConfigurator::myConfig.getTypeEvent();
        data["leftEvent"]    = NsConfigurator::myConfig.getRightEvent();
        data["rightEvent"]   = NsConfigurator::myConfig.getLeftEvent();
        WebSerial.send("get_initial_values", data);
    }

    /******************************************/
    /* @brief  Update Values from Webpage     */
    /******************************************/
    void updateValues(JSONVar data) {
        NsConfigurator::myConfig.setTypeMorseKey(data["typeMorseKey"]);
        NsConfigurator::myConfig.setTypeMorseKey(data["typeEvent"]);
        NsConfigurator::myConfig.setTypeMorseKey(data["leftEvent"]);
        NsConfigurator::myConfig.setTypeMorseKey(data["rightEvent"]);

    }


    /******************************************/
    /* @brief Setting the connection          */
    /******************************************/
    void maintainWebUSB() {
       
        Serial.begin(115200);
        while (!Serial) {           // wait till connection
            delay(1000);
        }
        while (Serial) {
            WebSerial.check();
            delay(200);
            WebSerial.on("get_initial_values", sendInitialValues);
            WebSerial.on("update_values", updateValues);
        }
    }
}