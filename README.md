Morse Code Interface for VBand
==============================

Introduction
---------------

This interface used the same hardware as the USB/HID Interface (The Gadget) and the cw_lcwo_pcw_interface. k
  
Related Websites
---------------

- [For STL files and SeeeduinoXIAO pinout description](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet)
- [VBand](https://hamradio.solutions/vband/)
- [Seeeduino](https://wiki.seeedstudio.com/Seeed_Arduino_Boards/)

Description
---------------

In the intial setup the program wait for an input sign. Depending on an the input of your morse key it will used a act as straight key or paddle.
  
- using a single key => a pull down of the key and the insterface is set for the straight key;
- using a paddle => press the right paddle
  
Building Interface and STL file
-------------------------------

![image](https://github.com/user-attachments/assets/cddb993a-dabf-4d2f-94d4-71d31f3f7a09)

The STL files for the 3d printed Seeeduino case, you will found on morse-code-usbhid-interface-the-gadet

![image](https://github.com/user-attachments/assets/9772ca79-4dc4-4013-a776-0f0fd51553f1)


For this project pin 6, 7  and ground is used, so building this project you can use also the next software

- [morse-code-usbhid-interface-the-gadet](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet)
- [cw_lcwo_pcw_interface](https://github.com/pe1hvh/cw_lcwo_pcw_interface)


Notes and Warning
-----------------

When you use the Keyboard.print() or Keyboard.press() command, the Arduino board takes over your keyboard! Make sure you have control before you use the command. A pushbutton to toggle the keyboard control state is effective.

73 [PE1HVH ](https://www.pe1hvh.nl)

