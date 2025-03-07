#include "global_vars.h"
#include "connection_handler.h"

//namespace NsConnection {
  
    SimpleWebSerial WebSerial;


    /******************************************/
    /* @brief  Send Initial Values to Webpage */
    /******************************************/
    void sendInitialValues() {
        int data[4];
        char str[100];

        data[0] =  NsConfigurator::myConfig.getTypeMorseKey();
        data[1] =  NsConfigurator::myConfig.getTypeEvent();
        data[2] =  NsConfigurator::myConfig.getLeftEvent();
        data[3] =  NsConfigurator::myConfig.getRightEvent();
      
        if( data[0] == 1 || data[0] == 2 ||data[0] == 3 ) {
            sprintf(str, "Geconfigureerd: Key %i , Event %i, RightEvent %i, LeftEvent %i ,", data[0], data[1], data[2], data[3]);
            WebSerial.send("status", str );
        } else {
            WebSerial.send("status","niet geconfigureerd" );
        }    
    }

    /******************************************/
    /* @brief  Update Values from Webpage     */
    /******************************************/
    void updateValues(JSONVar data) {
        const char* json = data;
        JsonDocument doc;
        deserializeJson(doc, json);

        NsConfigurator::myConfig.setTypeMorseKey(doc["typeMorseKey"].as<uint8_t>());
        NsConfigurator::myConfig.setTypeEvent(doc["typeEvent"].as<uint8_t>());
        NsConfigurator::myConfig.setLeftEvent(doc["leftEvent"].as<uint8_t>());
        NsConfigurator::myConfig.setRightEvent(doc["rightEvent"].as<uint8_t>());
        delay(1000);
        
        char str[100];
        sprintf(str, "Seeeduino heeft ontvangen: Key %i , Event %i, RightEvent %i, LeftEvent %i .", 
                                                                NsConfigurator::myConfig.getTypeMorseKey(), 
                                                                NsConfigurator::myConfig.getTypeEvent(), 
                                                                NsConfigurator::myConfig.getRightEvent(), 
                                                                NsConfigurator::myConfig.getLeftEvent());
        WebSerial.send("status", str );
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

        sendInitialValues();

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

//} // end namespace