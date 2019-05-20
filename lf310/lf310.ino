/*
 Example sketch for the Logitech F310 gamepad
 */

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <SPI.h>
#include "lf310.h"

USB Usb;
LF310 lf310(&Usb);

void setup() {
        Serial.begin(115200);
#if !defined(__MIPSEL__)
        while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
        Serial.println("Starting Logitech F310 gamepad");

        if (Usb.Init() == -1)
                Serial.println("OSC did not start.");
                
        // Set this to higher values to enable more debug information
        // minimum 0x00, maximum 0xff, default 0x80
        // UsbDEBUGlvl = 0xff;

        delay(200);
}

   uint8_t oldX = 128;
   uint8_t oldY = 128;
   uint8_t oldZ = 128;
   uint8_t oldRz = 128;
 
void loop() {
    /*
     * These four variable hold the "old" values of the joysticks so that action can be taken
     * only if they change.
     */
 
    Usb.Task();
    if (lf310.connected()) {

        if (lf310.lf310Data.X != oldX) {
          Serial.print("Left Joystick X: ");
          Serial.println(lf310.lf310Data.X);
          oldX = lf310.lf310Data.X;
        }

        if (lf310.lf310Data.Y != oldY) {
          Serial.print("Left Joystick Y: ");
          Serial.println(lf310.lf310Data.Y);
          oldY = lf310.lf310Data.Y;
        }

        if (lf310.lf310Data.Z != oldZ) {
          Serial.print("Right Joystick X: ");
          Serial.println(lf310.lf310Data.Z);
          oldZ = lf310.lf310Data.Z;
        }

        if (lf310.lf310Data.Rz != oldRz) {
          Serial.print("Right Joystick Y: ");
          Serial.println(lf310.lf310Data.Rz);
          oldRz = lf310.lf310Data.Rz;
        }

      
        if (lf310.buttonClickState.Xbutton) {
            lf310.buttonClickState.Xbutton= 0; // Clear event
            Serial.println(F("X button"));
        }
      
        if (lf310.buttonClickState.Abutton) {
            lf310.buttonClickState.Abutton= 0; // Clear event
            Serial.println(F("A button"));
        }
      
        if (lf310.buttonClickState.Bbutton) {
            lf310.buttonClickState.Bbutton= 0; // Clear event
            Serial.println(F("B button"));
        }
      
        if (lf310.buttonClickState.Ybutton) {
            lf310.buttonClickState.Ybutton= 0; // Clear event
            Serial.println(F("Y button"));
        }
      
        if (lf310.buttonClickState.LBbutton) {
            lf310.buttonClickState.LBbutton= 0; // Clear event
            Serial.println(F("LB button"));
        }
      
        if (lf310.buttonClickState.RBbutton) {
            lf310.buttonClickState.RBbutton= 0; // Clear event
            Serial.println(F("RB button"));
        }
      
        if (lf310.buttonClickState.LTbutton) {
            lf310.buttonClickState.LTbutton= 0; // Clear event
            Serial.println(F("LT button"));
        }
      
        if (lf310.buttonClickState.RTbutton) {
            lf310.buttonClickState.RTbutton= 0; // Clear event
            Serial.println(F("RT button"));
        }
      
        if (lf310.buttonClickState.Backbutton) {
            lf310.buttonClickState.Backbutton= 0; // Clear event
            Serial.println(F("Back button"));
        }
      
        if (lf310.buttonClickState.Startbutton) {
            lf310.buttonClickState.Startbutton= 0; // Clear event
            Serial.println(F("Start button"));
        }
      
        if (lf310.buttonClickState.LJSP) {
            lf310.buttonClickState.LJSP= 0; // Clear event
            Serial.println(F("Left Joystick deprressed"));
        }
      
        if (lf310.buttonClickState.RJSP) {
            lf310.buttonClickState.RJSP= 0; // Clear event
            Serial.println(F("Right Joystick deprressed"));
        }
        
        switch (lf310.lf310Data.btn.dPad) {
            case DPAD_UP:
                Serial.println(F("Up"));
                break;
            case DPAD_RIGHT:
                Serial.println(F("Right"));
                break;
            case DPAD_DOWN:
                Serial.println(F("Down"));
                break;
            case DPAD_LEFT:
                Serial.println(F("Left"));
                break;
            case DPAD_OFF:
                break;
            default:
                Serial.print(F("Unknown state: "));
                PrintHex<uint8_t > (lf310.lf310Data.btn.dPad, 0x80);
                Serial.println();
                break;
        }
    }
}
