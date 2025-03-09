#include "global_vars.h"
#include "connection_handler.h"

SimpleWebSerial WebSerial;

namespace NsConnection {

    /**********************************************************/
    /* @brief  Send Initial Values to the Online Configurator */
    /**********************************************************/
    void sendInitialValues() {
        int data[4];
        char str[150];

        data[0] =  NsConfigurator::myConfig.getTypeMorseKey();
        data[1] =  NsConfigurator::myConfig.getTypeEvent();
        data[2] =  NsConfigurator::myConfig.getLeftEvent();
        data[3] =  NsConfigurator::myConfig.getRightEvent();
      
        if( data[0] == 1 || data[0] == 2 ||data[0] == 3 ) {
            delay(100);
            // First sent the status to the html page   
            WebSerial.send("status", "Connected.");
            delay(500);
             // Next set de initial values for the Online Configurator
            JsonDocument doc;
            JsonArray jsonArray = doc.to<JsonArray>();
            for (int i = 0; i < 4; i++) {
                jsonArray.add(data[i]);
            }
            serializeJson(doc, str);
            WebSerial.send("initial_values", str );

        } else {
            WebSerial.send("status","N/A." );
        }    
    }

    /************************************************/
    /* @brief Update Values from Online Configurator   
       @param data the Json string
    */
    /************************************************/
    void updateValues(JSONVar data) {
        const char* json = data;
        JsonDocument doc;
        deserializeJson(doc, json);

        NsConfigurator::myConfig.setTypeMorseKey(doc["typeMorseKey"].as<uint8_t>());    // set type of Morse Key in object myConfig
        NsConfigurator::myConfig.setTypeEvent(doc["typeEvent"].as<uint8_t>());          // set type of Event in object myConfig
        NsConfigurator::myConfig.setLeftEvent(doc["leftEvent"].as<uint8_t>());          // set left event in object myConfig
        NsConfigurator::myConfig.setRightEvent(doc["rightEvent"].as<uint8_t>());        // set right event in object myConfig
        delay(500);
        WebSerial.send("status", "Data Received." );
    }


    /******************************************/
    /* @brief Setting the connection          */
    /******************************************/
    void maintainWebUSB() {
       
        Serial.begin(57600);
        while (!Serial) {                                                     // until connection is made
            delay(100);                                                      
        }
     
        delay(100);
        sendInitialValues();
        delay(100);

        WebSerial.on("update_values", updateValues);                          // set the callback function
        while (Serial) {                                                      // untill keypressed
              WebSerial.check();
              delay(10);
              if (digitalRead(inPin6) == LOW || digitalRead(inPin7) == LOW) { // Key Pressed
                delay(25);                                                    // simple method against bouncing
                Serial.end();
             }
        }
    } 

} // end namespace