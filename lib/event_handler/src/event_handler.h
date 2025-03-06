#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <Arduino.h>
#include <Mouse.h>
#include <Keyboard.h>

namespace NsEvent {
    /*****************************************************/
    /* @brief The BaseHandler                            */
    /*****************************************************/
    class BaseHandler {
      private:
        u_int8_t typeMorseKey;
        u_int8_t leftEvent;
        u_int8_t rightEvent;
      
      public:
        virtual void initHandler(u_int8_t  typeMorseKey, u_int8_t  leftEvent, u_int8_t  rightEvent) = 0;
        virtual void handleMorseKey(int pinDot, int pinDash) = 0;
        virtual ~BaseHandler() = default;
    };
    
    /*****************************************************/
    /* @brief The Mouse Handler                          */
    /*****************************************************/
    class MouseHandler : public BaseHandler {
      private:
        u_int8_t typeMorseKey;
        u_int8_t leftEvent;
        u_int8_t rightEvent;
    
      public:
        void initHandler(u_int8_t  typeMorseKey, u_int8_t  leftEvent, u_int8_t  rightEvent) override;
        void handleMorseKey(int pinDot, int pinDash) override;
    };
    
    /*****************************************************/
    /* @brief The KeyboardHandler                        */
    /*****************************************************/
    class KeyboardHandler : public BaseHandler {
      private:
        u_int8_t typeMorseKey;
        u_int8_t leftEvent;
        u_int8_t rightEvent;
    
      public:
        void initHandler(u_int8_t  typeMorseKey, u_int8_t  leftEvent, u_int8_t  rightEvent) override;
        void handleMorseKey(int pinDot, int pinDash) override;
    };
    
    // Global pointer to BaseHandler
    extern BaseHandler* myObjectHandler;
}

#endif // EVENT_HANDLER_H