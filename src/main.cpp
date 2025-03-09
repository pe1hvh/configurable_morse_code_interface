/******************************************************/
/*
       Title:   Configurable Morse Interface with a SeeeduinoXIAO.
      Author:   JA van Hernen, www.pe1hvh.nl
        Date:   9 March 2025
     Version:   1.0
    Hardware:   Seeeduino XIAO samd
       Legal:   Copyright (c) 2025  JA van Hernen.
                Open Source under the terms of the MIT License.

  Description


  After adding the interface to a computer USB port, the program wait for a initial key Event.
  One short keypress is works with the default settings. (default settings are for VBand)

  If you want to change the default settings see press the key initial more than 2 seconds.
  The interface will wait for a connection with the online configurator https://www.pe1hvh.nl/cw_online_configurator/
  With the Online configurator you can change settings for using by example PCWFistCheck or www.lcwo.net


  Notes and Warnings

  When you use the Keyboard.print() command, the Arduino takes over your keyboard!
  Make sure you have control before you use the command.

*/
#include "main.h"

/****************************************************/
/* @brief setup
   1. set the pin mode
   2. read config values from memoryor set default values
   3. calculated first morse key press
   4. conditional set the config values with the Online Configurator
   5. setup the event handler depending on the config values
*/
/****************************************************/

void setup() {
  
  pinMode(inPin6, INPUT_PULLUP);
  pinMode(inPin7, INPUT_PULLUP);

  NsConfigurator::myConfig.init();                               // Read configutation values from permanent memory or set default values
  NsConfigurator::myTimer.init();                                // Calculated first morse key press

  if (NsConfigurator::myTimer.getKeyPressDuration() > 2000 ) {   // set the configuration in collaboration with the Online Configurator
      NsConnection::maintainWebUSB();                            // Handles the communication between interface and Online Configurator
      NsConfigurator::myConfig.writeConfig2Memory();             // Write conditional the configuration values to permanent memory
  }


  if (NsConfigurator::myConfig.getTypeEvent() == 0) {            // Depending on the type event the code dynamically assigns either 
    NsEvent::myObjectHandler = new NsEvent::MouseHandler();      // a MouseHandler or a KeyboardHandler to myObjectHandler.
  } else {                                                       
    NsEvent::myObjectHandler = new NsEvent::KeyboardHandler();   
  }


  NsEvent::myObjectHandler->initHandler(                         // set the correct values to be used in the myObjectHandler
        NsConfigurator::myConfig.getTypeMorseKey(),
        NsConfigurator::myConfig.getLeftEvent(),
        NsConfigurator::myConfig.getRightEvent()
  );

}

/****************************************************/
/* @brief loop
   1. Do Determine the status of pin6 and pin 7
   2. Depending the override of the ObjectHandler
      the type of event is a mouse click or keyboard key
*/
/****************************************************/
void loop() {

  NsEvent::myObjectHandler->handleMorseKey(digitalRead(inPin6), digitalRead(inPin7));

}
