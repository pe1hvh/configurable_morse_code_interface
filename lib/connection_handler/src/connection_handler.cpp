
#include "connection_handler.h"

namespace NsConnection {
  
    SimpleWebSerial WebSerial;
    int typeMorseKey = 0;
    int typeEvent = 0;
    int leftEvent = 1;
    int rightEvent = 2;

    /******************************************/
    /* @brief  Send Initial Values to Webpage */
    /******************************************/
    void sendInitialValues(JSONVar data) {
        data["typeMorseKey"] = typeMorseKey;
        data["typeEvent"] = typeEvent;
        data["leftEvent"] = leftEvent;
        data["rightEvent"] = rightEvent;
        WebSerial.send("get_initial_values", data);
    }

    /******************************************/
    /* @brief  Update Values from Webpage     */
    /******************************************/
    void updateValues(JSONVar data) {
        typeMorseKey = data["typeMorseKey"];
        typeEvent = data["typeEvent"];
        leftEvent = data["leftEvent"];
        rightEvent = data["rightEvent"];

        // You might want to add some error checking here to make sure the values are valid
        NsConfigurator::myConfig.setTypeMorseKey(typeMorseKey);
        NsConfigurator::myConfig.setTypeEvent(typeEvent);
        NsConfigurator::myConfig.setLeftEvent(leftEvent);
        NsConfigurator::myConfig.setRightEvent(rightEvent);
    }

    /*****************************************************************/
    /* @brief Handled the communication between interface and webpage */
    /*****************************************************************/
    void maintainWebUSB() {
        WebSerial.check();
        delay(200);
    }


    /******************************************/
    /* @brief Setting the connection          */
    /******************************************/
    void getConfig() {
        if (NsConfigurator::myConfig.getTypeMorseKey() < 3) {
            typeMorseKey = NsConfigurator::myConfig.getTypeMorseKey();
            typeEvent = NsConfigurator::myConfig.getTypeEvent();
            leftEvent = NsConfigurator::myConfig.getLeftEvent();
            rightEvent = NsConfigurator::myConfig.getRightEvent();
        }
    }

    /******************************************/
    /* @brief Setting the connection          */
    /******************************************/
    void setConnection() {
        getConfig();
        Serial.begin(115200);
        while (!Serial) {
            delay(200);
        }
        WebSerial.on("get_initial_values", sendInitialValues);
        WebSerial.on("update_values", updateValues);
    }
}