////////////////////////////////////////////////////////////////////////////////
/// \file  lf310.h
/// \brief Holds data structures and class declarations
///
/// Author: Alan Ford
////////////////////////////////////////////////////////////////////////////////

#if !defined(__LF310_H__)
#define __LF310_H__

#include <hiduniversal.h>

#define LF310_VID    0x046D
#define LF310_PID    0xC216

///////////////////////////////////////////////////////////////////////////////
/// \brief Gamepad codes for various Dpad states
///////////////////////////////////////////////////////////////////////////////
enum DPADEnum {
    DPAD_UP = 0x0,
    DPAD_RIGHT = 0x2,
    DPAD_DOWN = 0x4,
    DPAD_LEFT = 0x6,
    DPAD_OFF = 0x8,
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Data structure containing states of all buttons
///////////////////////////////////////////////////////////////////////////////
union LF310DataButtons {
    struct {
        uint8_t dPad        : 4;
        uint8_t Xbutton     : 1;
        uint8_t Abutton     : 1;
        uint8_t Bbutton     : 1;
        uint8_t Ybutton     : 1;
        
        uint8_t LBbutton    : 1;
        uint8_t RBbutton    : 1;
        uint8_t LTbutton    : 1;
        uint8_t RTbutton    : 1;
        uint8_t Backbutton  : 1;
        uint8_t Startbutton : 1;
        uint8_t LJSP        : 1;  // Left Joystick "push"
        uint8_t RJSP        : 1;  // Right Joystick "push"
    } __attribute__((packed));
    uint16_t val;
} __attribute__((packed));

/////////////////////////////////////////////////////////////////////////
/// \brief  Data structure received from USB when a game pad event occurs
/////////////////////////////////////////////////////////////////////////
struct LF310Data {
      uint8_t X;
      uint8_t Y;
      uint8_t Z;
      uint8_t Rz;
   LF310DataButtons btn;
  union {
    uint8_t Extra;
    struct{
      uint8_t nonfunc     : 3;
      uint8_t mode        : 1;
      uint8_t nonfunc2    : 4;
    };
  };
  //uint8_t Byte7;
  //uint8_t Byte8;
};

/////////////////////////////////////////////////////////////////////////
/// \brief  Class extending the USB HID driver to model the behavior of the LF310
/////////////////////////////////////////////////////////////////////////
class LF310 : public HIDUniversal {
public:
    LF310(USB *p): HIDUniversal(p) {
        // initialize the data structure to nominal values;
        lf310Data.btn.dPad = DPAD_OFF;
        lf310Data.X = 128;
        lf310Data.Y = 128;
        lf310Data.Z = 128;
        lf310Data.Rz = 128;
    };
    bool connected() {
        return HIDUniversal::isReady() && HIDUniversal::VID == LF310_VID && HIDUniversal::PID == LF310_PID;
    };
    //void setLeds(uint16_t leds);
    LF310Data lf310Data;
    LF310DataButtons buttonClickState;
    
private:
    void ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf); // Called by the HIDUniversal library
    uint8_t OnInitSuccessful() { // Called by the HIDUniversal library on success
        if (HIDUniversal::VID != LF310_VID || HIDUniversal::PID != LF310_PID) // Make sure the right device is actually connected
            return 1;
        //setLeds(0);
        return 0;
    };
};

#endif // __LogitechF310_H__
