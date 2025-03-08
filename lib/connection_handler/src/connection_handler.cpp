#include "global_vars.h"
#include "connection_handler.h"

SimpleWebSerial WebSerial;

namespace NsConnection {


    /******************************************/
    /*
      @brief  get type of start text
      @param startText 
    */
    /******************************************/
    const char* getStartText(uint8_t startText) {
        switch (startText){ 
            case 1:  return "Saved configuration";
            case 2:  return "Seeeduino received "; 
            default: return "Unkown start text  ";
        }

    }

    /******************************************/
    /*
      @brief  get name of type morse key
      @param typeMorseKey 
    */
    /******************************************/
    const char* getNameMorseKey(uint8_t typeMorseKey){

        switch (typeMorseKey){ 
            case 1:  return "Straight Key";
            case 2:  return "Sidesweeper "; 
            case 3:  return "Paddle      "; 
            default: return "Unkown      ";
        }
    }

 
    /******************************************/
    /* 
       @brief  get name of type event
       @param typeEvent
    */
    /******************************************/
    const char* getNameTypeEvent(uint8_t typeEvent) {

        switch (typeEvent){ 
            case 0:  return "Mouse   ";
            case 1:  return "Keyboard"; 
            default: return "Unkown  ";
        }
    }

    /******************************************/
    /* 
        @brief  get name event
        @param event
    */    
    /******************************************/
    const char* getNameEvent(uint8_t event) {

        switch (event){ 
            case 1:   return  "Left Click      "; 
            case 2:   return  "Right Click     "; 
            case 4:   return  "Middle Click    ";

            case 128: return "Left Control Key "; 
            case 129: return "Left Shift Key   "; 
            case 130: return "Left Alt Key     "; 
            case 132: return "Right Control Key";
            case 133: return "Right Shift Key  ";
            case 134: return "Right Alt Key    "; 
            default:  return "Unkown           ";
        }
    }

    /******************************************/
    /* 
        @brief setSnprintf set the communication row
               Dependig on the type of key the return message is slightly shorter.
               Is the type of Morse Key 3 then the function use both right and left event. (it used both pins).
               Otherwise it use only the left (pin6) event.
        @param startText The start text can be saved configuration or seeeduino received
        @param typeMorseKey The type of morse key
        @param typeEvent  Mouse or keyboard
        @param rightEvent depending of type event
        @param leftEvent  depending of type event
        @return str char  string concatenated for sending to the html page


    */    
    /******************************************/
    const char* setSnprintf(uint8_t startText,uint8_t typeMorseKey, uint8_t typeEvent, uint8_t rightEvent, uint8_t leftEvent) {
        static char str[150];
        if(typeMorseKey==3) {
                snprintf(str, sizeof(str), "%s; Type Key : %s, Type Event : %s, Event 1 (pin6) : %s, Event 2 (pin7): %s.",
                                            getStartText(startText),
                                            getNameMorseKey(typeMorseKey), 
                                            getNameTypeEvent(typeEvent),
                                            getNameEvent(rightEvent), 
                                            getNameEvent(leftEvent));
        } else {
                snprintf(str, sizeof(str), "%s; Type Key : %s, Type Event : %s, Event 1 (pin6) : %s.",
                                            getStartText(startText),
                                            getNameMorseKey(typeMorseKey), 
                                            getNameTypeEvent(typeEvent),
                                            getNameEvent(rightEvent));
       }  
       return str;      
    }
    

    /******************************************/
    /* @brief  Send Initial Values to Webpage */
    /******************************************/
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
            strcpy(str,setSnprintf(1, data[0],data[1],data[2],data[3]));
            WebSerial.send("status", str );
            delay(500);
             // Next set de initial values for the html page
            JsonDocument doc;
            JsonArray jsonArray = doc.to<JsonArray>();
            for (int i = 0; i < 4; i++) {
                jsonArray.add(data[i]);
            }
            serializeJson(doc, str);
            WebSerial.send("initial_values", str );

        } else {
            WebSerial.send("status","niet geconfigureerd" );
        }    
    }

    /******************************************/
    /* @brief Update Values from Webpage   
       @param data the Json string
    */
    /******************************************/
    void updateValues(JSONVar data) {
        const char* json = data;
        JsonDocument doc;
        deserializeJson(doc, json);

        NsConfigurator::myConfig.setTypeMorseKey(doc["typeMorseKey"].as<uint8_t>());    // set type of Morse Key in object myConfig
        NsConfigurator::myConfig.setTypeEvent(doc["typeEvent"].as<uint8_t>());          // set type of Event in object myConfig
        NsConfigurator::myConfig.setLeftEvent(doc["leftEvent"].as<uint8_t>());          // set left event in object myConfig
        NsConfigurator::myConfig.setRightEvent(doc["rightEvent"].as<uint8_t>());        // set right event in object myConfig
        delay(1000);
        
        char str[150];
        strcpy(str,setSnprintf(2, NsConfigurator::myConfig.getTypeMorseKey()
                                , NsConfigurator::myConfig.getTypeEvent()
                                , NsConfigurator::myConfig.getRightEvent()
                                , NsConfigurator::myConfig.getLeftEvent()  ) );               
    
        WebSerial.send("status", str );
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

        WebSerial.on("update_values", updateValues);
        while (Serial) {                                                      // untill keypressed
              WebSerial.check();
              delay(10);
              if (digitalRead(inPin6) == LOW || digitalRead(inPin7) == LOW) { // Key Pressed
                delay(25);                                                    // simple method against bouncing
                Serial.end();
             }
        }

    } // end maintainWebUsb

} // end namespace