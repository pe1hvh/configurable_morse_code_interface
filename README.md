Multiplatform Morse Code Interface
==================================

Introduction
---------------

Multiplatform Morse Code Interface for LCWO, PCWFistCheck, VBand etc. In collaboration with the [Online Configurator](https://www.pe1hvh.nl/cw_online_configurator/) is it an interface for al programms or apps that using a mouse or keyboard.

 
See for more information: [Home page project Multiplatform Morse Code Interface ](https://www.pe1hvh.nl/?cursus=morse-multiplatform-interface)

This interface used the same hardware as described on the USB/HID Interface ([The Gadet](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet)).


How it works
------------

When the interface is connected to a USB port, the interface program waits for an initial key press (from the Morse key).

- If this key press less than 2 seconds, the inerface program will proceed with either the default values or the configuration values specified using the online configurator.
- If longer than 2 seconds, the program waits for a connection with on [Online Configurator](https://www.pe1hvh.nl/cw_online_configurator/). 


The Online configurator will wait until you choose the correct USB device/port (in this case the Seeeduino XIAO ).

After the connection is established you can specify the type of Morse key and set up the interface for:
- Mouse emulation, or
- Keyboard emulation

Depending on the chosen emulation, you can select, for example, the right/left mouse button or right/left Ctrl key.

For to stop te configuration :
- press the morse key short or
- close the online configurator. 

It will store the configuration in permantent memory of the interface.


Building Interface and STL file
-------------------------------

![image](https://github.com/user-attachments/assets/cddb993a-dabf-4d2f-94d4-71d31f3f7a09)

For this project pin 6, 7  and ground is used.

![image](https://github.com/user-attachments/assets/9772ca79-4dc4-4013-a776-0f0fd51553f1)

The STL files for the 3d printed Seeeduino case, can be found on [morse-code-usbhid-interface-the-gadet](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet).


Visual Code and PlatformIO
-------------------------

For this project I used Visual Code as IDE with the PlatformIO plugin. 
PlatformIO requires that functions be declared before they are called in the code. This is because PlatformIO uses a more standard C++ compilation process, which adheres strictly to the requirement that functions must be declared before use.

For using the ArduinoIDE the code is converted and placed in a separated folder in this repository. See the paragraph ArduinoIDE.


SonarLint
---------

For writing cleancode, the Sonarlint plug-in is installed in Visual Code. SonarLint is an open-source code analysis tool that serves several important functions to help developers write cleaner, safer, and higher-quality code. There is no need, for using all sonarlint rules but the most important are enabled.


ArduinoIDE
----------
This code is converted to compatible code for de ArduinoIDE and its placed in the folder arduino_ide as an Arduino project.

 Add Seeeduino XIAO to your Arduino IDE
 Click on File > Preference, and fill Additional Boards Manager URLs with the next url: https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 and use your library managers to install the folow libraries;
 - Keyboard
 - Mouse
 - Simple Web Serial
 - Arduino Json
 - FlasStorage SAMD


Related Websites
---------------

- [For STL files](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet)
- [VBand](https://hamradio.solutions/vband/)
- [Seeeduino](https://wiki.seeedstudio.com/Seeed_Arduino_Boards/)
- [PCW FistCheck](https://www.qsl.net/dj7hs/download.htm)
- [Learn Morse Code online(LCWO)](https://lcwo.net/)
- [Online CW Multiplatform Morse Code Interface Configurator](https://www.pe1hvh.nl/cw_online_configurator/)
- [Home page project Multiplatform Morse Code Interface ](https://www.pe1hvh.nl/?cursus=morse-multiplatform-interface)


Browser support
---------------

The Online Configurator will work with the follow browsers;

- Chrome: Fully supports WebUSB since version 617. It also supports Web Serial API14.
- Edge: Supports WebUSB since version 797.
- Opera: Supports WebUSB7.
- Android browsers: Chrome for Android fully supports WebUSB5. 

FireFox don´t support yet the WebUSB Serial/API.


OS support
----------

It will work with the next desktop operating systems;

- Windows (>= 8.1)
- macOS
- Linux
- ChromeOS

You can use the interface with your smartphone, only you cannot use the online configurator on your smartphone. 


Notes and Warning
-----------------

While the morse code interface used the Keyboard.print() or Keyboard.press() command, the Arduino board takes over your keyboard! Make sure you have control before you use the command. 

73 [PE1HVH ](https://www.pe1hvh.nl)

