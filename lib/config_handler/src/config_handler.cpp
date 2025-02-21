#include "config_handler.h" 
#include "functions.h"

namespace NsConfigurator {
    
  
    /******************************************/
    /* @brief The initTimer                   */   
    /******************************************/
    void Timer::initTimer() {
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
        
          typeMorseKey = readFlash(0); // 0 = straight key, 1 = cuty, 2=paddle
          typeEvent    = readFlash(1); // 0 = mouse, 1 = keyboard
          leftEvent    = readFlash(2); // left_key or left mouse click 
          rightEvent   = readFlash(3); // right_key or right mouse click 
     
     }
  

 
    /******************************************/
    /* @brief The constructor                 */   
    /******************************************/     
     void Config::initConfig() {
         readConfigFromMemory();
     }
     

     
 
    void Config::writeConfig2Memory() {
      
          bool changed = false; 

          if (readFlash(0) != typeMorseKey) { writeFlash(0, typeMorseKey); changed = true;}
          if (readFlash(1) != typeEvent)    { writeFlash(1, typeEvent);    changed = true;}
          if (readFlash(2) != leftEvent)    { writeFlash(2, leftEvent);    changed = true;}
          if (readFlash(3) != rightEvent)   { writeFlash(3, rightEvent);   changed = true;}

          if(changed) commitFlash();  // Commiting the values
     
     }
     
    /******************************************/
    /* The Getters                            */
    /******************************************/     
      int Config::getTypeEvent(){
        return typeEvent;
     } 

     int Config::getLeftEvent(){
        return leftEvent;
     }
     
     int Config::getRightEvent(){
        return rightEvent;
     }  

     int Config::getTypeMorseKey(){
        return typeMorseKey;
     } 

    /******************************************/
    /* The setters                            */
    /******************************************/     
      void Config::setTypeEvent(int xTypeEvent){
        typeEvent = typeEvent ;
     } 

     void Config::setLeftEvent( int xLeftEvent){
        leftEvent = xLeftEvent;
     }
     
     void Config::setRightEvent( int xRightEvent){
        rightEvent = xRightEvent;
     }  

     void Config::setTypeMorseKey( int xMorseKey){
        typeMorseKey = xMorseKey;
     } 

     Config myConfig;
}     
            