/////////////////////////////////////////////////////////////////////////
///  \file lf310.cpp
/// \brief This is the USB HID driver for the Logitech F310 game pad
///
/// \author Alan Ford
/////////////////////////////////////////////////////////////////////////
#include "lf310.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Parse a HID data report from the Logitech F310
///////////////////////////////////////////////////////////////////////////////
void LF310::ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
    if (HIDUniversal::VID != LF310_VID || HIDUniversal::PID != LF310_PID) // Make sure the right device is actually connected
        return;
    memcpy(&lf310Data, buf, min(len, MFK_CASTUINT8T sizeof(lf310Data)));    
    static LF310DataButtons oldButtonState;
    if (lf310Data.btn.val != oldButtonState.val) { // Check if anything has changed
        buttonClickState.val = lf310Data.btn.val & ~oldButtonState.val; // Update click state variable
        oldButtonState.val = lf310Data.btn.val;
    }
}
