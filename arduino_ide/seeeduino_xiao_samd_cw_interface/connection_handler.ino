#include "global_vars.h"
#include "connection_handler.h"

namespace NsConnection {
  
    SimpleWebSerial WebSerial;


    /******************************************/
    /* @brief  Send Initial Values to Webpage */
    /******************************************/
    void sendInitialValues() {
        JSONVar data;

        data["typeMorseKey"] = NsConfigurator::myConfig.getTypeMorseKey();
        data["typeEvent"]    = NsConfigurator::myConfig.getTypeEvent();
        data["leftEvent"]    = NsConfigurator::myConfig.getLeftEvent();
        data["rightEvent"]   = NsConfigurator::myConfig.getRightEvent();




    }

    /******************************************/
    /* @brief  Update Values from Webpage     */
    /******************************************/
    void updateValues(JSONVar data) {
        NsConfigurator::myConfig.setTypeMorseKey(data["typeMorseKey"]);
        NsConfigurator::myConfig.setTypeEvent(data["typeEvent"]);
        NsConfigurator::myConfig.setLeftEvent(data["leftEvent"]);
        NsConfigurator::myConfig.setRightEvent(data["rightEvent"]);

    }


    /******************************************/
    /* @brief Setting the connection          */
    /******************************************/
    void maintainWebUSB() {
       
        Serial.begin(57600);
        while (!Serial) {              // until connection is made
            delay(100);
        }
     
        delay(100);

        WebSerial.on("update_values", updateValues);

        while (Serial) {                 // untill keypressed
              WebSerial.check();
              delay(10);
              if (digitalRead(inPin6) == LOW || digitalRead(inPin7) == LOW) { // Key Pressed
                delay(25);                                                    // simple method against bouncing
                Serial.end();
             }
        }

    } // end maintainWebUsb

} // end namespace