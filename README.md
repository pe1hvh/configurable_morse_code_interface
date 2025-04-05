DIY Configurable USB/HID Morse Code Interface
=========================================

Introduction
---------------

DIY Configurable USB Morse Code Interface for LCWO, PCWFistCheck, VBand, MorseMania etc. In collaboration with the [Online Configurator](https://www.pe1hvh.nl/cw_online_configurator/) , this interface allows you to use your favorite Morse key with various programs and apps, instead of relying on a mouse or keyboard.

Please note that not all browsers support WebUSB. Refer to the Browser Support section in this Readme doc for more information.


How it works
------------
When the interface is connected to a USB port, the interface program waits for an initial key press (from the Morse key).

- If this key press lasts less than 2 seconds, the interface program will proceed with either the default values or the configuration values specified using the online configurator.
- If it lasts longer than 2 seconds, the program will wait for a connection with the Online Configurator.

The Online Configurator will prompt you to select the correct USB device/port (in this case, the Seeeduino XIAO).

![Screenshot from 2025-03-09 11-30-51](https://github.com/user-attachments/assets/c781a801-44ea-4a94-9a6c-0e3ee48cc7ab)

![Screenshot from 2025-03-09 11-31-09](https://github.com/user-attachments/assets/0dfd3497-205b-4ffa-8709-518750ce7462)

![Screenshot from 2025-03-09 11-31-28](https://github.com/user-attachments/assets/e0835b47-2d2a-43db-a988-c7be1d194d7e)

Once the connection is established, you can specify the type of Morse key and configure the interface for:

- Mouse emulation, or
- Keyboard emulation.

Depending on the chosen emulation mode, you can assign actions such as the right/left mouse button or the right/left Ctrl key.

To stop the configuration process (don´t forget to send the new configuration to the XIAO):

- Press the Morse key briefly, or
- Close the Online Configurator.

The configuration will be stored in the interface's permanent memory.


Hardware/STL File
-----------------

This project only needs a micro jack, some wire, a USB-C/USB cable, and of course a Seeeduino XIAO SAMD21.

![image](https://github.com/user-attachments/assets/cddb993a-dabf-4d2f-94d4-71d31f3f7a09)

For this project, pins 6,7 and ground are used.

![image](https://github.com/user-attachments/assets/9772ca79-4dc4-4013-a776-0f0fd51553f1)

The STL files for the 3D-printed Seeeduino case can be found on [morse-code-usbhid-interface-the-gadget](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadget).

![image](https://github.com/user-attachments/assets/a50c0f38-e94b-45de-b255-eb27cef3a264)


Visual Code and PlatformIO
-------------------------

For this project, I used Visual Studio Code as the IDE with the PlatformIO plugin. PlatformIO requires functions to be declared before they are called in the code. This is because PlatformIO uses a more standard C++ compilation process, which strictly adheres to the requirement that functions must be declared before use.

For using the Arduino IDE, the code is converted and placed in a separate folder in this repository. See the Arduino IDE paragraph for more details.


SonarLint
---------

For writing clean code, the SonarLint plugin is installed in Visual Studio Code. SonarLint is an open-source code analysis tool that helps developers write cleaner, safer, and higher-quality code. While it's not necessary to use all SonarLint rules, the most important ones are enabled.

ArduinoIDE
----------
This code is converted to be compatible with the Arduino IDE and is placed in the arduino_ide folder as an Arduino project.

To add Seeeduino XIAO to your Arduino IDE:
1. Click on File > Preferences
2. Fill "Additional Boards Manager URLs" with the following URL: https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
3. Use your library manager to install the following libraries:
- Keyboard
- Mouse
- Simple Web Serial (confirm to install dependencies too, if asked)
- Arduino_Json
- FlashStorage_SAMD



Related Websites
---------------

- [For STL files](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet)
- [Seeeduino](https://wiki.seeedstudio.com/Seeed_Arduino_Boards/)
- [Home page project Multiplatform Morse Code Interface ](https://www.pe1hvh.nl/?cursus=configurable_morse_code_interface)
- [Online CW Multiplatform Morse Code Interface Configurator](https://www.pe1hvh.nl/cw_online_configurator/)

  
Examples of software and webpages working with this interface
------------------------------------------------------------

- [VBand](https://hamradio.solutions/vband/)
- [PCW FistCheck](https://www.qsl.net/dj7hs/download.htm)
- [Learn Morse Code online(LCWO)](https://lcwo.net/)
- [Morsecode.me](https://beta.morsecode.me/#/rooms/1)
- [Morse Keyer V5.3](https://morse-rss-news.sourceforge.net/)
- [MorsePower CWCom](https://morsepower.blogspot.com/2016/08/cwcom-program-to-communicate-using.html)
- [F6DM Cw Player](http://f6dqm.free.fr/soft/cwplayer/en/cwplayer.htm)
- [LKMT: CW - Morse Code Reading Trainer](https://dm2fue.darc.de/index.html#Download_Section) 


Browser support
---------------

The Online Configurator will work with the following browsers:
- Chrome: Fully supports WebUSB since version. It also supports Web Serial API.
- Edge: Supports WebUSB since version.
- Opera: Supports WebUSB.
- Android browsers: Chrome for Android fully supports WebUSB.

Firefox doesn't support WebUSB or Web Serial API yet


OS support
----------

It will work with the following desktop operating systems:
- Windows (>= 8.1)
- macOS
- Linux
- ChromeOS

You can use the interface with your smartphone, but you cannot use the online configurator on your smartphone.


Notes and Warning
-----------------

While the Morse code interface uses the Keyboard.print() or Keyboard.press() command, the Arduino board takes over your keyboard! Make sure you have control before you use the command.

73 [PE1HVH ](https://www.pe1hvh.nl)
