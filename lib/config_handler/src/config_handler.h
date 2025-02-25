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
      int typeMorseKey = 1; // Default Straight Key
      int typeEvent    = 0; // Defualt Mouse
      int leftEvent    = 1; // Default Right Klick
      int rightEvent   = 2; // N/A with Straight Key 
      uint8_t buffer[64];

   

  
  public:
      void init();
      void writeConfig2Memory();
      void readConfigFromMemory();
      int getTypeEvent();
      int getLeftEvent();
      int getRightEvent();
      int getTypeMorseKey();
      void setTypeEvent(int typeEvent);
      void setLeftEvent(int leftEvent);
      void setRightEvent(int rightEvent);
      void setTypeMorseKey(int typeMorseKey);
  };
  extern Config myConfig;
}

#endif // CONFIG_HANDLER_H