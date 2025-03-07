/******************************************************/
/*
       Title:   Multipurpose Morse Interface with a SeeeduinoXIAO.
      Author:   JA van Hernen, www.pe1hvh.nl
        Date:   5 Jan 2025
     Version:   1.0
    Hardware:   Seeeduino XIAO samd
       Legal:   Copyright (c) 2025  JA van Hernen.
                Open Source under the terms of the MIT License.

  Description

  Simple program to generate a key keystroke or mouseclick with your favorite morse key and morse learning program

  After adding the interface to a computer USB port, the program wait for a initial key Event



  Used hardware as describe at  https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadget

  Add Seeeduino to your Arduino IDE
        Click on File > Preference, and fill Additional Boards Manager URLs with the url below:
        https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
        and use your library managers to install the keyboard library.


   Notes and Warnings

   When you use the Keyboard.print() command, the Arduino takes over your keyboard!
   Make sure you have control before you use the command.

*/
#include "main.h"

void commitFlash(){
  EEPROM.commit();
}
int readFlash(int index) {
  return EEPROM.read(index);
}
void writeFlash(int index, int value) {
  EEPROM.write(index, value);
}

/****************************************************/
/* @brief setup
   1. set the pin mode
   2. read config values from memory
   3. calculated first morse key press
   4. conditional set the config values
   5. setup the event handler depending on the config values
*/
/****************************************************/

void setup() {
  
  pinMode(inPin6, INPUT_PULLUP);
  pinMode(inPin7, INPUT_PULLUP);

  NsConfigurator::myConfig.init();                               // read configutation values from permanent memory or set default values
  NsConfigurator::myTimer.init();                                // calculated first morse key press

  if (NsConfigurator::myTimer.getKeyPressDuration() > 2000 ) {   // default (empty eeprom,reed is #FF) 
      maintainWebUSB();                                          // Handles the communication between interface and webpage
      NsConfigurator::myConfig.writeConfig2Memory();             // Conditional write configuration to permanent memory
  }


  if (NsConfigurator::myConfig.getTypeEvent() == 0) {
    NsEvent::myObjectHandler = new NsEvent::MouseHandler();
  } else {
    NsEvent::myObjectHandler = new NsEvent::KeyboardHandler();
  }

  NsEvent::myObjectHandler->initHandler(
        NsConfigurator::myConfig.getTypeMorseKey(),
        NsConfigurator::myConfig.getLeftEvent(),
        NsConfigurator::myConfig.getRightEvent()
  );

}

/****************************************************/
/* @brief loop
   1. Do Determine the status of pin6 and pin 7
   2. Depending the override of the ObjectHandler
      the type of event is mouse click or keyboard key
*/
/****************************************************/
void loop() {

  NsEvent::myObjectHandler->handleMorseKey(digitalRead(inPin6), digitalRead(inPin7));

}
