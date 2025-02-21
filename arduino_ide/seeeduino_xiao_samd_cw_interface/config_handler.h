#ifndef CONFIG_HANDLER_H_
#define CONFIG_HANDLER_H_

#include <Arduino.h>
#include "pin_handler.h"

namespace NsConfigurator {

  // Timer class declaration
  class Timer {
  private:
      unsigned long keyPressStartTime;
      unsigned long keyPressDuration;

  public:
      void initTimer();
      unsigned long getKeyPressDuration();
  };
  extern Timer myTimer;
  
  // Config class declaration
  class Config {
  private:
      int typeMorseKey;
      int typeEvent;
      int leftEvent;
      int rightEvent;
      uint8_t buffer[64];

     

  
  public:
      void initConfig();
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