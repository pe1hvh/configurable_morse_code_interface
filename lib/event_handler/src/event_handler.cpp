#include <Arduino.h>
#include "event_handler.h"

namespace NsEvent {

   /**************************************************************/
    /* @brief initHandler set init values for the MouseHandler  
       @param typeMorseKey the type of morse key
       @param leftEvent  
       @param rightEvent 
    */
    /*************************************************************/
 
    void MouseHandler::initHandler(u_int8_t  typeMorseKey, u_int8_t  leftEvent, u_int8_t  rightEvent) {

            this->typeMorseKey = typeMorseKey;
            this->leftEvent    = leftEvent;
            this->rightEvent   = rightEvent;
            
            Mouse.begin();
    }

    /*****************************************************/
    /* @brief handleMorseKey Handles the Mouse click 
       @param pinDot
       @param pinDash
    */
    /*****************************************************/
    void MouseHandler::handleMorseKey(int pinDot ,int pinDash) {
    
             if(pinDot == LOW)                        {      //pin==LOW  => is closed (activated )
                 Mouse.press(this->leftEvent);              
              } else {
                Mouse.release();
              }  
              
              if(pinDash == LOW)                      {      //pin==LOW  => is closed (activated )  
                 Mouse.press(this->rightEvent);     
              }  else {                                      //pin==HIGH => is open ( deactived )
                 Mouse.release();
              } 
               
     }



    /**************************************************************/
    /* @brief initHandler set init values for the KeyboardHandler 
       @param typeMorseKey the type of morse key
       @param leftEvent  
       @param rightEvent 
    */
    /**************************************************************/
    void KeyboardHandler::initHandler(u_int8_t  typeMorseKey, u_int8_t  leftEvent, u_int8_t  rightEvent)  {

            this->typeMorseKey = typeMorseKey;
            this->leftEvent    = leftEvent;
            this->rightEvent   = rightEvent;
           
            Keyboard.begin();
    }



    /*****************************************************/
    /* @brief KeyboardHandler Handles the key press           
       @param pinDot
       @param pinDash
    */
    /*****************************************************/
    void KeyboardHandler::handleMorseKey(int pinDot ,int pinDash) {
      
      if(pinDot == LOW) {                       //pin==LOW  => is closed (activated )
          Keyboard.press(this->leftEvent);     
       }  else {                                //pin==HIGH => is open ( deactivated )
          Keyboard.release(this->leftEvent);
       }
       
       if(pinDash == LOW) {                     //pin==LOW  => is closed (activated )  
          Keyboard.press(this->rightEvent);    
       }  else {                                //pin==HIGH => is open ( deactivated )
          Keyboard.release(this->rightEvent);
       }  
}
    


    BaseHandler* myObjectHandler = nullptr;  // Declare the pointer to the BaseHandler class and initialize it to nullptr
                                             // myObjectHandler is the pointer that hold the address of a BaseHandler object.
                                             // it is initiazed to nullptr, meaning it currently do not point (now) to any object

}