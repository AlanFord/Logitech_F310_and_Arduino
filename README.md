# Logitech_F310_and_Arduino
This documents a USB HID driver that permits using the Logitech F310 gamepad with an Arduino.

The goal here is to permit the use of the Logitech F310 gamepad with an Arduino (Uno or Mega) by way of the 
Arduino USB Host Shield.  (other USB host shields may also work, but I don't have them to test).

## Prerequisites
Install a modern version of the Arduino IDE.  I'm using Version 1.8.7.

Install the USB Host Shield Library 2.0, or update it to the latest version.  This can be accomplished in the Arduino
IDE by using the Tools Menu, Manage Libraries, ...

Get a USB Host Shield and an F310 gamepad.

**Important!**  There is a little switch on the bottom of the Logitech F310 controller that can be positioned at either "X"
or "D".  **It must be set to "D".**

## Patch the USB Host Shield Library 2.0
A bug has been identified in the USB Host Shield Library 2.0, Version 1.3.2 that needs to be patched before
the Logitech F310 gamepad can be used.  The patch is documented here 
https://github.com/felis/USB_Host_Shield_2.0/pull/438

A patched version of the file usb.cpp is found in the "library_patch" folder.  Copy this into the install folder for the 
USB Host Shield Library 2.0 and you will be fixed up.  The install folder is different on various computers.  On a Mac
it's `Documents/Arduino/libraries/USB_Host_Shield_Library_2.0/`.  In Windows 10 it's
`My Documents\Arduino\libraries\USB_Host_Shield_Library_2.0\`.

## Try the Demo Code
The demo code is located in the lf310 folder.  It is a HID-based USB driver, similar to the SRWS1 sample code that
ships with the library.
