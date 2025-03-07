#ifndef CONFIG_HANDLER_H_
#define CONFIG_HANDLER_H_

#include <Arduino.h>


namespace NsConfigurator {

  // Timer class declaration
  class Timer {
  private:
      unsigned long keyPressStartTime;
      unsigned long keyPressDuration;

  public:
      void init();
      unsigned long getKeyPressDuration();
  };
  extern Timer myTimer;
  
 
 
  // Config class declaration
  class Config {
  private:
      uint8_t typeMorseKey = 1; // 1. straight key 2. swipper 3. paddle
      uint8_t typeEvent    = 1; // Defualt Mouse
      uint8_t leftEvent    = 128; // Default Right Klick
      uint8_t rightEvent   = 128; // N/A with Straight Key 
    
  public:
      void init();
      void writeConfig2Memory();
      void readConfigFromMemory();
      uint8_t getTypeEvent();
      uint8_t getLeftEvent();
      uint8_t getRightEvent();
      uint8_t getTypeMorseKey();
      void setTypeEvent(uint8_t typeEvent);
      void setLeftEvent(uint8_t leftEvent);
      void setRightEvent(uint8_t rightEvent);
      void setTypeMorseKey(uint8_t typeMorseKey);
  };

  extern Config myConfig;
  
}

#endif // CONFIG_HANDLER_H