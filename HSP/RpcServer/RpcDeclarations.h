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
#ifndef _RPCDECLARATIONS_H_
#define _RPCDECLARATIONS_H_

/// define the parts of a RPC.  ObjectName, MethodName and function
struct RPC_registeredProcedure {
    const char *objectName;
    const char *methodName;
    //enum eArgType argTypes[4];
    int (*func)(char args[32][32], char results[32][32]);
    struct RPC_registeredProcedure *next;
};

/// used to keep track of the head of the list and the end of a list
struct RPC_Object {
    struct RPC_registeredProcedure *head;
    struct RPC_registeredProcedure *last;
};

//example /I2c/WriteRead 1 A0 3 11 22 33 2
#define System_NAME "System"

/**
* @brief  /System/ReadVer
* @details Returns the version string of the FW that is currently running
* @details Example: /System/ReadVer
* @details The command returns a version string similar to this: "HSP FW Version 2.0.1f 8/23/16"
*/
struct RPC_registeredProcedure  Define_System_ReadVer = { System_NAME, "ReadVer", System_ReadVer };
/**
* @brief  /System/ReadBuildTime
* @details Returns the build string of the FW that is currently running, this is the time and date that the firmware was built
* @details Example: /System/ReadBuildTime
* @details The command returns a build string similar to this: "Build Time: Fri Jul 1 15:48:31 2016"
*/
struct RPC_registeredProcedure  Define_System_ReadBuildTime = { System_NAME, "ReadBuildTime", System_ReadBuildTime };

#define MAX30001_NAME "MAX30001"
#define MAX30003_NAME "MAX30003"

#define MAX31725_NAME "MAX31725"
#define MAX30205_NAME "MAX30205"

/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_WriteReg = { MAX30001_NAME, "WriteReg", MAX30001_WriteReg };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_ReadReg = { MAX30001_NAME, "ReadReg", MAX30001_ReadReg };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Start = { MAX30001_NAME, "Start", MAX30001_Start };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Stop = { MAX30001_NAME, "Stop", MAX30001_Stop };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Rbias_FMSTR_Init = { MAX30001_NAME, "Rbias_FMSTR_Init", MAX30001_Rbias_FMSTR_Init };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_CAL_InitStart = { MAX30001_NAME, "CAL_InitStart", MAX30001_CAL_InitStart };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_ECG_InitStart = { MAX30001_NAME, "ECG_InitStart", MAX30001_ECG_InitStart };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_ECGFast_Init = { MAX30001_NAME, "ECGFast_Init", MAX30001_ECGFast_Init };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_PACE_InitStart = { MAX30001_NAME, "PACE_InitStart", MAX30001_PACE_InitStart };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_BIOZ_InitStart = { MAX30001_NAME, "BIOZ_InitStart", MAX30001_BIOZ_InitStart };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_RtoR_InitStart = { MAX30001_NAME, "RtoR_InitStart", MAX30001_RtoR_InitStart };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Stop_ECG = { MAX30001_NAME, "Stop_ECG", MAX30001_Stop_ECG };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Stop_PACE = { MAX30001_NAME, "Stop_PACE", MAX30001_Stop_PACE };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Stop_BIOZ = { MAX30001_NAME, "Stop_BIOZ", MAX30001_Stop_BIOZ };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Stop_RtoR = { MAX30001_NAME, "Stop_RtoR", MAX30001_Stop_RtoR };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Stop_Cal = { MAX30001_NAME, "Stop_Cal", MAX30001_Stop_Cal };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Enable_ECG_LeadON = { MAX30001_NAME, "Enable_ECG_LeadON", MAX30001_Enable_ECG_LeadON };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Enable_BIOZ_LeadON = { MAX30001_NAME, "Enable_BIOZ_LeadON", MAX30001_Enable_BIOZ_LeadON };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_Read_LeadON = { MAX30001_NAME, "Read_LeadON", MAX30001_Read_LeadON };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_StartTest = { MAX30001_NAME, "StartTest", MAX30001_StartTest };
/**
* @brief  /MAX30101/SpO2mode_init fifo_waterlevel_mark sample_avg sample_rate pulse_width red_led_current ir_led_current
* @details This function sets up for the SpO2 mode. 
* @param fifo_waterlevel_mark
* @param sample_avg
* @param sample_rate
* @param pulse_width
* @param red_led_current
* @param ir_led_current
*/
struct RPC_registeredProcedure  Define_MAX30001_INT_assignment = { MAX30001_NAME, "INT_assignment", MAX30001_INT_assignment };

#define LOGGING_NAME "Logging"
/**
* @brief  /Logging/StartMissionDefine
* @details A command to send when you are starting to define a mission
*/
struct RPC_registeredProcedure  Define_Logging_StartMissionDefine = { LOGGING_NAME, "StartMissionDefine", Logging_RPC_StartMissionDefine };
/**
* @brief  /Logging/AppendMissionCmd missionString
* @details Specify a RPC command that is part of a mission
*/
struct RPC_registeredProcedure  Define_Logging_AppendMissionCmd = { LOGGING_NAME, "AppendMissionCmd", Logging_RPC_AppendMissionCmd };
/**
* @brief  /Logging/EndMissionDefine
* @details RPC command that indicated the end of defining a mission
*/
struct RPC_registeredProcedure  Define_Logging_EndMissionDefine = { LOGGING_NAME, "EndMissionDefine", Logging_RPC_EndMissionDefine };
/**
* @brief  /Logging/WriteMission
* @details Write the described mission to flash
*/
struct RPC_registeredProcedure  Define_Logging_WriteMission = { LOGGING_NAME, "WriteMission", Logging_RPC_WriteMission };
/**
* @brief  /Logging/ReadMission
* @details Read the mission from flash
*/
struct RPC_registeredProcedure  Define_Logging_ReadMission = { LOGGING_NAME, "ReadMission", Logging_RPC_ReadMission };
/**
* @brief  /Logging/EraseMission
* @details Erase the mission in flash
*/
struct RPC_registeredProcedure  Define_Logging_EraseMission = { LOGGING_NAME, "EraseMission", Logging_RPC_EraseMission };
/**
* @brief  /Logging/EraseWrittenSectors
* @details Erase the datalog in flash, this erases all of the datalog that has been written to the flash
*/
struct RPC_registeredProcedure  Define_Logging_EraseWrittenSectors = { LOGGING_NAME, "EraseWrittenSectors", Logging_EraseWrittenSectors };
/**
* @brief  /Logging/StartLoggingUsb
* @details Start streaming data through USB
*/
struct RPC_registeredProcedure  Define_Logging_StartLoggingUsb = { LOGGING_NAME, "StartLoggingUsb", Logging_StartLoggingUsb };
/**
* @brief  /Logging/StartLoggingFlash
* @details Start logging data to flash
*/
struct RPC_registeredProcedure  Define_Logging_StartLoggingFlash = { LOGGING_NAME, "StartLoggingFlash", Logging_StartLoggingFlash };
/**
* @brief  /Logging/GetLastWrittenPage
* @details Returns the last page that has been written to flash, this call searchs until it finds an empty flash page
*/
struct RPC_registeredProcedure  Define_Logging_GetLastWrittenPage = { LOGGING_NAME, "GetLastWrittenPage", Logging_GetLastWrittenPage };
/**
* @brief  /Logging/Start
* @details Starts a datalogging session into flash, allows the ability to start datalogging via RPC call
*/
struct RPC_registeredProcedure  Define_Logging_Start = { LOGGING_NAME, "Start", Logging_Start };

#define LED_NAME "Led"
/**
* @brief  /Led/On
* @details Turn on the HSP onboard LED
*/
struct RPC_registeredProcedure  Define_Led_On = { LED_NAME, "On", Led_On };
/**
* @brief  /Led/Off
* @details Turn off the HSP onboard LED
*/
struct RPC_registeredProcedure  Define_Led_Off = { LED_NAME, "Off", Led_Off };
/**
* @brief  /Led/Blink mS
* @details Start blinking the HSP onboard LED
* @param mS Blink using a mS period
*/
struct RPC_registeredProcedure  Define_Led_BlinkHz = { LED_NAME, "Blink", Led_BlinkHz };
/**
* @brief  /Led/Pattern pattern
* @details Rotate a 32-bit pattern through the LED so that specific blink patterns can be obtained
* @param pattern A 32-bit pattern to rotate through
*/
struct RPC_registeredProcedure  Define_Led_BlinkPattern = { LED_NAME, "Pattern", Led_BlinkPattern };

#define S25FS512_NAME "S25FS512"
#define SDCARD_NAME "SDCard"
/**
* @brief  /S25FS512/ReadId
* @details Rotate a 32-bit pattern through the LED so that specific blink patterns can be obtained
* @param pattern A 32-bit pattern to rotate through
*/
struct RPC_registeredProcedure  Define_S25FS512_ReadId = { S25FS512_NAME, "ReadId", S25FS512_ReadId };
/**
* @brief  /S25FS512/ReadPagesBinary startPage endPage
* @details Read a page from flash, return the data in binary (non-ascii)
* @param startPage The Starting page to read from
* @param endPage The last page to read from
*/
struct RPC_registeredProcedure  Define_S25FS512_ReadPagesBinary = { S25FS512_NAME, "ReadPagesBinary", S25FS512_ReadPagesBinary };
/**
* @brief  /S25FS512/Reset
* @details Issue a soft reset to the flash device
*/
struct RPC_registeredProcedure  Define_S25FS512_Reset = { S25FS512_NAME, "Reset", S25FS512_Reset };
/**
* @brief  /S25FS512/EnableHWReset
* @details Enable HW resets to the device
*/
struct RPC_registeredProcedure  Define_S25FS512_EnableHWReset = { S25FS512_NAME, "EnableHWReset", S25FS512_EnableHWReset };
/**
* @brief  /S25FS512/SpiWriteRead
* @details Write and read SPI to the flash device using Quad SPI
*/
struct RPC_registeredProcedure  Define_S25FS512_SpiWriteRead = { S25FS512_NAME, "SpiWriteRead", S25FS512_SpiWriteRead };
/**
* @brief  /S25FS512/SpiWriteRead4Wire
* @details Write and read SPI to the flash device using 4 wire
*/
struct RPC_registeredProcedure  Define_S25FS512_SpiWriteRead4Wire = { S25FS512_NAME, "SpiWriteRead4Wire", S25FS512_SpiWriteRead4Wire };
/**
* @brief  /SDCard/IsReady
* @details Check whether SD Card File System is accessible
*/
struct RPC_registeredProcedure  Define_SDCard_IsReady = { SDCARD_NAME, "IsReady", SDCard_IsReady };


#define TESTING_NAME "Testing"
/**
* @brief  /Testing/Test_S25FS512
* @details Start a testing sequence for this device, returns PASS and FAIL strings and detailed results of the test
*/
struct RPC_registeredProcedure  Define_Testing_Test_S25FS512 = { TESTING_NAME, "Test_S25FS512",  Test_S25FS512};

/**
* @brief  /Testing/Test_MAX30001
* @details Start a testing sequence for this device, returns PASS and FAIL strings and detailed results of the test
*/
struct RPC_registeredProcedure  Define_Testing_Test_MAX30001 = { TESTING_NAME, "Test_MAX30001", Test_MAX30001 };

#endif /* _RPCDECLARATIONS_H_ */

