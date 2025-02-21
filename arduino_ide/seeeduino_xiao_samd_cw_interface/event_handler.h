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
        int leftEvent;
        int rightEvent;
    
      public:
        virtual void handleMorseKey(int pinDot, int pinDash) = 0;
        virtual void initHandler(int typeMorseKey, int leftEvent, int rightEvent) = 0;
        virtual ~BaseHandler() = default;
    };
    
    /*****************************************************/
    /* @brief The Mouse Handler                          */
    /*****************************************************/
    class MouseHandler : public BaseHandler {
      private:
        int typeMorseKey;
        int leftEvent;
        int rightEvent;
    
      public:
        void initHandler(int tMorseKey, int lEvent, int rEvent) override;
        void handleMorseKey(int pinDot, int pinDash) override;
    };
    
    /*****************************************************/
    /* @brief The KeyboardHandler                        */
    /*****************************************************/
    class KeyboardHandler : public BaseHandler {
      private:
        int typeMorseKey;
        int leftEvent;
        int rightEvent;
    
      public:
        void initHandler(int tMorseKey, int lEvent, int rEvent) override;
        void handleMorseKey(int pinDot, int pinDash) override;
    };
    
    // Global pointer to BaseHandler
    extern BaseHandler* myObjectHandler;
}

#endif // EVENT_HANDLER_H