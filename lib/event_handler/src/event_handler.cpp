#include <Arduino.h>
#include "event_handler.h"

namespace NsEvent {

    /*****************************************************/
    /* @brief The Mouse Handler                          */
    /*****************************************************/

 
    void MouseHandler::initHandler(int typeMorseKey, int leftEvent, int rightEvent) {

            this->typeMorseKey = typeMorseKey;
            this->leftEvent    = leftEvent;
            this->rightEvent   = rightEvent;
            
            Mouse.begin();
    }

    void MouseHandler::handleMorseKey(int pinDot ,int pinDash) {
    
             if(pinDot == LOW)                      { //pin==LOW  => is closed (activated )
                 Mouse.press(this->leftEvent);              // print a space on the monitor window    
              }else if(pinDash == LOW)              { //pin==LOW  => is closed (activated )  
                 Mouse.press(this->rightEvent);             // print a space on the monitor window    
              }  else {                               //pin==HIGH => is open ( deactived )
                 Mouse.release();
              }  
     }



    /*****************************************************/
    /* @brief The Keyboard Handler                       */
    /*****************************************************/

  
    void KeyboardHandler::initHandler(int typeMorseKey, int leftEvent, int rightEvent)  {

            this->typeMorseKey = typeMorseKey;
            this->leftEvent    = leftEvent;
            this->rightEvent   = rightEvent;
           
            Keyboard.begin();
    }


    void KeyboardHandler::handleMorseKey(int pinDot ,int pinDash) {
      
             if(pinDot == LOW)                      { //pin==LOW  => is closed (activated )
                 Keyboard.press(this->leftEvent);           // print a space on the monitor window    
              }else if(pinDash == LOW)              { //pin==LOW  => is closed (activated )  
                 Keyboard.press(this->rightEvent);          // print a space on the monitor window    
              }  else {                               //pin==HIGH => is open ( deactived )
                 Keyboard.releaseAll();
              }  
     }
    


    BaseHandler* myObjectHandler = nullptr;  // Declare the pointer to the BaseHandler class and initialize it to nullptr
                                             // myObjectHandler is the pointer that hold the address of a BaseHandler object.
                                             // it is initiazed to nullptr, meaning it currently do not point (now) to any object

}