/*******************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */
#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

#include "mbed.h"
#include "USBSerial.h"
#include "HspLed.h"
#include "MAX30001.h"
#include "S25FS512.h"
#include "PushButton.h"
#include "SDFileSystem.h"
/**
* This static class is used as a central locatoin for all devices on the HSP platform
* it gives (in-effect) a singleton interface for each device so that anywhere in code
* one can reference on of these devices
*/
class Peripherals {
public:
    static USBSerial *setUSBSerial(USBSerial * device) { mUSBSerial = device; return device; }
    static USBSerial *usbSerial(void) { return mUSBSerial; }

    static HspLed *hspLed(void) { return mHspLed; }
    static HspLed *setHspLed(HspLed *device) { mHspLed = device; return device; }

    static MAX30001 *max30001(void) { return mMAX30001; }
    static MAX30001 *setMAX30001(MAX30001 *device) { mMAX30001 = device; return device; }

    static Timer *timestampTimer(void) { return mTimestampTimer; }
    static Timer *setTimestampTimer(Timer *timer) { mTimestampTimer = timer; return timer; }

    static S25FS512 *s25FS512(void) { return mS25FS512; }
    static S25FS512 *setS25FS512(S25FS512 *s25FS512) { mS25FS512 = s25FS512; return s25FS512; }

    static PushButton *pushButton(void) { return mPushButton; }
    static PushButton *setPushButton(PushButton *pushButton) { mPushButton = pushButton; return pushButton; }
    
    static SDFileSystem *sdFS(void) { return mSD; }
    static SDFileSystem *setSdFS(SDFileSystem *SD) { mSD = SD; return SD; }
    
    static DigitalIn *SDDetect(void) { return mSDDetect; } 
    static DigitalIn *setSDDetect(DigitalIn *SDDetect) { mSDDetect = SDDetect; return SDDetect; }     

private:
    static USBSerial *mUSBSerial;
    static MAX30001 *mMAX30001;
    static HspLed *mHspLed;
    static Serial *mSerial;
    static Timer *mTimestampTimer;
    static S25FS512 *mS25FS512;
    static PushButton *mPushButton;
    static SDFileSystem *mSD;
    static DigitalIn *mSDDetect;
};

#endif // _PERIPHERALS_H_


