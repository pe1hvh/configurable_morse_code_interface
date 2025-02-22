#include "config_handler.h" 
#include "eeprom_handler.h"
#include "global_vars.h"

namespace NsConfigurator {
    
  
    /******************************************/
    /* @brief The initTimer                   */   
    /******************************************/
    void Timer::init() {
         while (digitalRead(inPin6) == HIGH && digitalRead(inPin7)==HIGH) {
            //key is not Press
            delay(25);                // simple method against bouncing
         }
         // Key Press, record the start time
         keyPressStartTime = millis();
          
         // Wait for the Key to be released
         while (digitalRead(inPin6) == LOW || digitalRead(inPin7) == LOW) {
            // Key still Pressed, keep waiting
            delay(25);                // simple method against bouncing
         }
          
         // Key released, calculate the duration
         keyPressDuration = (millis() - keyPressStartTime);  
    }

    /******************************************/
    /* @brief The getter for keyEventDuration */   
    /******************************************/
    unsigned long Timer::getKeyPressDuration(){
         return keyPressDuration;
    }
          
    Timer myTimer;

    /*****************************************************/
    /* @brief The Configurator                           */
    /*****************************************************/
    
    void Config::readConfigFromMemory() {
        
      this->typeMorseKey = readFlash(0); // 0 = straight key, 1 = cuty, 2=paddle
      this->typeEvent    = readFlash(1); // 0 = mouse, 1 = keyboard
      this->leftEvent    = readFlash(2); // left_key or left mouse click 
      this->rightEvent   = readFlash(3); // right_key or right mouse click 
     
     }
  

 
    /******************************************/
    /* @brief The constructor                 */   
    /******************************************/     
     void Config::init() {
         readConfigFromMemory();
     }
     

     
 
    void Config::writeConfig2Memory() {
      
          bool changed = false; 

          if (readFlash(0) != this->typeMorseKey) { writeFlash(0, this->typeMorseKey); changed = true;}
          if (readFlash(1) != this->typeEvent)    { writeFlash(1, this->typeEvent);    changed = true;}
          if (readFlash(2) != this->leftEvent)    { writeFlash(2, this->leftEvent);    changed = true;}
          if (readFlash(3) != this->rightEvent)   { writeFlash(3, this->rightEvent);   changed = true;}

          if(changed) commitFlash();  // Commiting the values
     
     }
     
    /******************************************/
    /* The Getters                            */
    /******************************************/     
      int Config::getTypeEvent(){
        return this->typeEvent;
     } 

     int Config::getLeftEvent(){
        return this->leftEvent;
     }
     
     int Config::getRightEvent(){
        return this->rightEvent;
     }  

     int Config::getTypeMorseKey(){
        return this->typeMorseKey;
     } 

    /******************************************/
    /* The setters                            */
    /******************************************/     
      void Config::setTypeEvent(int typeEvent){
        this->typeEvent = typeEvent ;
     } 

     void Config::setLeftEvent( int leftEvent){
        this->leftEvent = leftEvent;
     }
     
     void Config::setRightEvent( int rightEvent){
       this->rightEvent = rightEvent;
     }  

     void Config::setTypeMorseKey( int morseKey){
       this->typeMorseKey = morseKey;
     } 

     Config myConfig;
}     
            