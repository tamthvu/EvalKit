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
#ifndef S25FS512_H_
#define S25FS512_H_

#include "mbed.h"
#include "QuadSpiInterface.h"

class S25FS512 {
public:
  S25FS512(QuadSpiInterface *_quadSpiInterface);
  ~S25FS512(void);

  QuadSpiInterface *quadSpiInterface;

  /** Initialize the driver
  */
  int init(void);

  /** Detect the presence of the flash device
  */
  uint8_t detect(void);

  /** Read the identification of the flash
  */
  int8_t readIdentification(uint8_t *dataArray, uint8_t length);

  /** Bulk erase the flash device
  */
  int8_t bulkErase_Helper(void);

  /** Erase Parameter Sectors
  */
  int8_t parameterSectorErase_Helper(uint32_t address);

  /** Write a Page
  */
  int8_t writePage_Helper(uint32_t pageNumber, uint8_t *buffer,
                          uint32_t offset);

  /** Read a Page
  * @param
  */
  int8_t readPages_Helper(uint32_t startPageNumber, uint32_t endPageNumber,
                          uint8_t *buffer, uint32_t offset);

  /** Erase a Sector
  @param address Address of sector to erase
  */

  int8_t sectorErase_Helper(uint32_t address);
  /** Scans through byte pointer for a page worth of data to see if the page is all FFs
  @param ptr Byte pointer to buffer to scan
  @return Returns a 1 if the page is empty, 0 if it is not all FFs
  */
  uint32_t isPageEmpty(uint8_t *ptr);
  
  /** Issue a software reset to the flash device
  */

  uint8_t reset(void);
  /** Enable a hardware reset
  */

  uint8_t enableHWReset(void);
  /** Read the id byte of this device
  */

  void readID(uint8_t *id);

private:
  int8_t reg_write_read_multiple_quad_last(uint8_t *dataIn, uint8_t numberIn, uint8_t *dataOut, uint8_t numberOut, uint8_t last);
  int8_t reg_write_read_multiple_quad(uint8_t *dataIn, uint8_t numberIn, uint8_t *dataOut, uint8_t numberOut);
  int8_t reg_write_read_multiple_4Wire(uint8_t *bufferOut, uint8_t numberOut, uint8_t *bufferIn, uint8_t numberIn);
  uint8_t spiWriteRead (uint8_t writeNumber,uint8_t *writeData, uint8_t readNumber, uint8_t *readData);
  uint8_t spiWriteRead4Wire(uint8_t writeNumber,uint8_t *writeData, uint8_t readNumber, uint8_t *readData);

  int8_t writeAnyRegister(uint32_t address, uint8_t data);
  int8_t writeAnyRegister4Wire(uint32_t address, uint8_t data);
  int8_t writeRegisters(void);
  uint8_t wren(void);
  int setQuadMode(void);
  int wren4Wire(void);
  // int8_t setQuadMode();
  int8_t readAnyRegister(uint32_t address, uint8_t *data, uint32_t length);
  int8_t bulkErase(void);
  int8_t pageProgram(uint32_t address, uint8_t *buffer);
  int8_t quadIoRead_Pages(uint32_t address, uint8_t *buffer, uint32_t numberOfPages);
  int8_t checkBusy(void);
  void waitTillNotBusy(void);
  int8_t sectorErase(uint32_t address);
  int8_t parameterSectorErase(uint32_t address);
  void wait_1mS(void);
  void wait_100uS(void);
  void wait_10mS(void);
};
#endif /* S25FS512_H_ */

