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
         this->keyPressStartTime = millis();
          
         // Wait for the Key to be released
         while (digitalRead(inPin6) == LOW || digitalRead(inPin7) == LOW) {
            // Key still Pressed, keep waiting
            delay(25);                // simple method against bouncing
         }
          
         // Key released, calculate the duration
         this->keyPressDuration = (millis() - this->keyPressStartTime);  
    }

    /******************************************/
    /* @brief The getter for keyEventDuration 
       @return keypress duration
    */   
    /******************************************/
    unsigned long Timer::getKeyPressDuration(){
         return this->keyPressDuration;
    }
          
    Timer myTimer;

    /*****************************************************/
    /* @brief The Configurator                           */
    /*****************************************************/
    void Config::readConfigFromMemory() {
      if( readFlash(0) == 1 || readFlash(0) == 2 || readFlash(0) == 3  ) {
    
         this->typeMorseKey = readFlash(0); // 1 = straight key, 2 = cuty, 3=paddle
         this->typeEvent    = readFlash(1); // 0 = mouse, 1 = keyboard
         this->leftEvent    = readFlash(2); // left_key or left mouse click 
         this->rightEvent   = readFlash(3); // right_key or right mouse click 
      } // else default values
   
   }
  

 
    /******************************************/
    /* @brief init calls the private methode
         readConfigFromMemory       
     */   
    /******************************************/     
     void Config::init() {
         readConfigFromMemory();
     }
     

     
    /*****************************************************/
    /* @brief writeConfig2Memory  
            Write the given values to permanent memory
            and commit the changes                 
    */
    /*****************************************************/
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
    uint8_t Config::getTypeEvent(){
        return this->typeEvent;
     } 

     uint8_t Config::getLeftEvent(){
        return this->leftEvent;
     }
     
     uint8_t Config::getRightEvent(){
        return this->rightEvent;
     }  

     uint8_t Config::getTypeMorseKey(){
        return this->typeMorseKey;
     } 

    /******************************************/
    /* The setters                            */
    /******************************************/     
      void Config::setTypeEvent( uint8_t typeEvent){
        this->typeEvent = typeEvent;
     } 

     void Config::setLeftEvent( uint8_t leftEvent){
        this->leftEvent = leftEvent;
     }
     
     void Config::setRightEvent( uint8_t rightEvent){
       this->rightEvent = rightEvent;
     }  

     void Config::setTypeMorseKey( uint8_t morseKey){
       this->typeMorseKey = morseKey;
     } 

     Config myConfig;
}     
            