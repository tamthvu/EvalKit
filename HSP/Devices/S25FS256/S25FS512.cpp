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

//
// Flash Non-Volatile Memory
// U27 S25FS512
// Nimitz SPIM1
//

#include "mbed.h"
#include "S25FS512.h"
#include "QuadSpiInterface.h"

#define IOMUX_IO_ENABLE              1

#define S25FS512_SPI_PORT            1
#define S25FS512_CS_PIN              0
#define S25FS512_CS_POLARITY         0
#define S25FS512_CS_ACTIVITY_DELAY   0
#define S25FS512_CS_INACTIVITY_DELAY 0
#define S25FS512_CLK_HI              4
#define S25FS512_CLK_LOW             4
#define S25FS512_ALT_CLK             0
#define S25FS512_CLK_POLARITY        0
#define S25FS512_CLK_PHASE           0
#define S25FS512_WRITE               1
#define S25FS512_READ                0

#define INT_PORT_B 3
#define INT_PIN_B 6

uint8_t flashBuffer[257 + 10];

//******************************************************************************
S25FS512::S25FS512(QuadSpiInterface *_quadSpiInterface) {
  this->quadSpiInterface = _quadSpiInterface;
}

//******************************************************************************
S25FS512::~S25FS512(void) {
}

//******************************************************************************
int S25FS512::init(void) {
  setQuadMode();
  return 0;
}

//******************************************************************************
int S25FS512::wren4Wire(void) {
  uint8_t cmdArray[8];
  // Send WREN
  cmdArray[0] = 0x06;
  wait_1mS();
  return reg_write_read_multiple_4Wire(cmdArray, 1, flashBuffer, 1);
}

//******************************************************************************
uint8_t S25FS512::wren(void) {
  uint8_t cmdArray[8];
  // Send WREN
  cmdArray[0] = 0x06;
  wait_1mS();
  return reg_write_read_multiple_quad(cmdArray, 1, flashBuffer, 0);
}

//******************************************************************************
int8_t S25FS512::reg_write_read_multiple_quad_last(uint8_t *bufferOut,
                                                   uint8_t numberOut,
                                                   uint8_t *bufferIn,
                                                   uint8_t numberIn,
                                                   uint8_t last) {
  int32_t success = 0;

  success = quadSpiInterface->SPI_Transmit( 
                       bufferOut, numberOut, 
                       bufferIn, numberIn, (int)last);

  if (success != 0) return -1;
  return 0;
}

//******************************************************************************
int8_t S25FS512::reg_write_read_multiple_4Wire(uint8_t *bufferOut,
                                               uint8_t numberOut,
                                               uint8_t *bufferIn,
                                               uint8_t numberIn) {
  int32_t success = 0;
  success = quadSpiInterface->SPI_Transmit4Wire(bufferOut, numberOut, bufferIn,
                                                numberIn, (int)1);

  if (success != 0) return -1;
  return 0;
}

//******************************************************************************
int8_t S25FS512::reg_write_read_multiple_quad(uint8_t *bufferOut,
                                              uint8_t numberOut,
                                              uint8_t *bufferIn,
                                              uint8_t numberIn) {
  int8_t ret;
  ret = reg_write_read_multiple_quad_last(bufferOut, numberOut, bufferIn,
                                          numberIn, 1);
  return ret;
}

//******************************************************************************
void S25FS512::readID(uint8_t *id) {
  uint8_t cmd = 0x9F;
  reg_write_read_multiple_quad(&cmd, 1, id, 4);
}

//******************************************************************************
int8_t S25FS512::writeAnyRegister(uint32_t address, uint8_t data) {
  uint8_t cmdArray[5];
  cmdArray[0] = 0x71;
  cmdArray[1] = (address >> 16) & 0xFF;
  cmdArray[2] = (address >> 8) & 0xFF;
  cmdArray[3] = (address >> 0) & 0xFF;
  cmdArray[4] = data;
  return reg_write_read_multiple_quad(cmdArray, 5, flashBuffer, 0);
}

int8_t S25FS512::writeAnyRegister4Wire(uint32_t address, uint8_t data) {
  uint8_t cmdArray[5];
  cmdArray[0] = 0x71;
  cmdArray[1] = (address >> 16) & 0xFF;
  cmdArray[2] = (address >> 8) & 0xFF;
  cmdArray[3] = (address >> 0) & 0xFF;
  cmdArray[4] = data;
  return reg_write_read_multiple_4Wire(cmdArray, 5, flashBuffer, 5);
}

//******************************************************************************
int8_t S25FS512::writeRegisters(void) {
  uint8_t cmdArray[3];
  wait_1mS();
  cmdArray[0] = 0x01;
  cmdArray[1] = 0x00;
  cmdArray[2] = 0x02; // set Quad to 1
  reg_write_read_multiple_quad(cmdArray, 3, flashBuffer, 0);
  return 0;
}

//******************************************************************************
int8_t S25FS512::readAnyRegister(uint32_t address, uint8_t *data,
                                 uint32_t length) {
  uint8_t cmdArray[4];
  cmdArray[0] = 0x65;
  cmdArray[1] = (address >> 16) & 0xFF;
  cmdArray[2] = (address >> 8) & 0xFF;
  cmdArray[3] = (address >> 0) & 0xFF;
  return reg_write_read_multiple_quad(cmdArray, 4, data, length);
}

//******************************************************************************
int8_t S25FS512::bulkErase(void) {
  uint8_t cmdArray[1];
  cmdArray[0] = 0x60;
  return reg_write_read_multiple_quad(cmdArray, 1, flashBuffer, 0);
}

//******************************************************************************
int8_t S25FS512::pageProgram(uint32_t address, uint8_t *buffer) {
  uint32_t i;
  uint8_t cmdArray[5 + 256];
  uint8_t *ptr;

  // for (i = 0; i < 256; i++) {
  //	dataArray[i] = i;
  //}
  cmdArray[0] = 0x02; // 0x71;
  //	cmdArray[1] = (address >> 24) & 0xFF;
  cmdArray[1] = (address >> 16) & 0xFF;
  cmdArray[2] = (address >> 8) & 0xFF;
  cmdArray[3] = (address >> 0) & 0xFF;
  for (i = 0; i < 256; i++) {
    cmdArray[4 + i] = buffer[i];
  }
  //	reg_write_read_multiple_quad(cmdArray,256 + 4,flashBuffer,256 + 4);

  ptr = cmdArray;
  reg_write_read_multiple_quad_last(ptr, 4 + 64, flashBuffer, 0, 0);
  wait_1mS();
  ptr += (4 + 64);
  reg_write_read_multiple_quad_last(ptr, 64, flashBuffer, 0, 0);
  wait_1mS();
  ptr += 64;
  reg_write_read_multiple_quad_last(ptr, 64, flashBuffer, 0, 0);
  wait_1mS();
  ptr += 64;
  reg_write_read_multiple_quad_last(ptr, 64, flashBuffer, 0, 1);
  wait_1mS();
  return 0;
}

//******************************************************************************
int8_t S25FS512::quadIoRead_Pages(uint32_t address, uint8_t *buffer,
                                  uint32_t numberOfPages) {
  uint8_t cmdArray[5];
  uint8_t *ptr;
  uint8_t last;
  uint32_t i;

  cmdArray[0] = 0xEB;
  cmdArray[1] = (address >> 16) & 0xFF;
  cmdArray[2] = (address >> 8) & 0xFF;
  cmdArray[3] = (address >> 0) & 0xFF;
  ptr = buffer;
  last = 0;
  // only send the command
  reg_write_read_multiple_quad_last(cmdArray, 4, ptr, 0, 0);
  wait_1mS();
  reg_write_read_multiple_quad_last(cmdArray, 0, ptr, 5, 0);
  wait_1mS();
  for (i = 0; i < numberOfPages; i++) {
    reg_write_read_multiple_quad_last(cmdArray, 0, ptr, 64, 0);
    wait_1mS();
    ptr += 64;
    reg_write_read_multiple_quad_last(cmdArray, 0, ptr, 64, 0);
    wait_1mS();
    ptr += 64;
    reg_write_read_multiple_quad_last(cmdArray, 0, ptr, 64, 0);
    wait_1mS();
    ptr += 64;
    // check if this is the last page
    if ((i + 1) == numberOfPages) {
      last = 1;
    }
    reg_write_read_multiple_quad_last(cmdArray, 0, ptr, 64, last);
    wait_1mS();
    ptr += 64;
  }
  return 0;
}

//******************************************************************************
int8_t S25FS512::checkBusy(void) {
  uint8_t cmdArray[5];
  cmdArray[0] = 0x05;
  reg_write_read_multiple_quad(cmdArray, 1, flashBuffer, 2);
  return flashBuffer[1] & 0x1;
}

//******************************************************************************
void S25FS512::waitTillNotBusy(void) {
  while (checkBusy() == 1) {
  }
}

//******************************************************************************
int8_t S25FS512::sectorErase(uint32_t address) {
  uint8_t cmdArray[5];
  cmdArray[0] = 0xD8;
  cmdArray[1] = (address >> 16) & 0xFF;
  cmdArray[2] = (address >> 8) & 0xFF;
  cmdArray[3] = (address >> 0) & 0xFF;
  return reg_write_read_multiple_quad(cmdArray, 4, flashBuffer, 0);
}

//******************************************************************************
int8_t S25FS512::parameterSectorErase(uint32_t address) {
  uint8_t cmdArray[5];
  cmdArray[0] = 0x20;
  cmdArray[1] = (address >> 16) & 0xFF;
  cmdArray[2] = (address >> 8) & 0xFF;
  cmdArray[3] = (address >> 0) & 0xFF;
  reg_write_read_multiple_quad(cmdArray, 4, flashBuffer, 0);
  return 0;
}

#define ONE_MS (32768 / 500)
#define ONEHUNDRED_US (32768 / 1000)
#define TEM_MS (32768 / 50)

//******************************************************************************
void S25FS512::wait_1mS(void) { 
 wait_ms(1); 
}

//******************************************************************************
void S25FS512::wait_100uS(void) { 
wait_us(100); 
}

//******************************************************************************
void S25FS512::wait_10mS(void) { 
wait_ms(10); 
}

//******************************************************************************
int8_t S25FS512::readIdentification(uint8_t *dataArray, uint8_t length) {
  // 4QIOR = 0x9F
  uint8_t cmdArray[1];
  cmdArray[0] = 0x9F; // read ID command
  return reg_write_read_multiple_quad(cmdArray, 1, dataArray, length);
}

//******************************************************************************
uint8_t S25FS512::reset(void) {
  uint8_t cmdArray[8];
  wait_1mS();
  cmdArray[0] = 0x66;
  reg_write_read_multiple_quad(cmdArray, 1, flashBuffer, 0);
  wait_1mS();
  cmdArray[0] = 0x99;
  reg_write_read_multiple_quad(cmdArray, 1, flashBuffer, 0);
  return 0;
}

//******************************************************************************
uint8_t S25FS512::enableHWReset(void) {
  uint8_t data[8];
  wait_1mS();
  // CR2V Configuration Register-2 Volatile
  // bit 5
  readAnyRegister(0x00800003, data, 8);
  writeAnyRegister(0x00800003, 0x64);
  return 0;
}

//******************************************************************************
uint8_t S25FS512::detect(void) {
  uint8_t array[8];
  uint8_t array2[8];

  // Send WREN
  wren();
  // Send WREN
  wren();
  // delay
  wait_1mS();
  // Send WREN
  wren();
  // delay
  wait_1mS();

  // Send write any register cmd
  writeAnyRegister(0x0003, 0x48);
  // delay
  wait_1mS();
  array[0] = 0x9F; // read ID command
  reg_write_read_multiple_quad(array, 1, array2, 7);
  return 0;
}

//******************************************************************************
int S25FS512::setQuadMode(void) {
  wait_1mS();
  wren4Wire();
  wait_1mS();
  writeAnyRegister4Wire(0x800002, 0x02); // set Quad = 1
  wait_1mS();
  wren4Wire();
  wait_1mS();
  writeAnyRegister4Wire(0x800003, 0x48); // set 8 latency, set QPI 4-4-4
}

//******************************************************************************
uint32_t S25FS512::isPageEmpty(uint8_t *ptr) {
  int i;
  for (i = 0; i < 256; i++) {
    if (ptr[i] != 0xFF)
      return 0;
  }
  return 1;
}

//******************************************************************************
int8_t S25FS512::parameterSectorErase_Helper(uint32_t address) {
  waitTillNotBusy();
  wait_100uS();
  wren();
  wait_100uS();
  parameterSectorErase(address);
  wait_100uS();
  waitTillNotBusy();
  wait_100uS();
  return 0;
}

//******************************************************************************
int8_t S25FS512::sectorErase_Helper(uint32_t address) {
  waitTillNotBusy();
  wait_100uS();
  wren();
  wait_100uS();
  if (address < 0x8000) {
    parameterSectorErase(address);
  } else {
    sectorErase(address);
  }
  wait_100uS();
  waitTillNotBusy();
  wait_100uS();
  return 0;
}

//******************************************************************************
int8_t S25FS512::bulkErase_Helper(void) {
  waitTillNotBusy();
  wait_100uS();
  wren();
  wait_100uS();
  bulkErase();
  wait_100uS();
  waitTillNotBusy();
  wait_100uS();
  return 0;
}

//******************************************************************************
// write a page worth of data (256 bytes) from buffer, offset defined where in
// the buffer to begin write
int8_t S25FS512::writePage_Helper(uint32_t pageNumber, uint8_t *buffer,
                                  uint32_t offset) {
  uint8_t *ptr;
  waitTillNotBusy();
  wait_1mS();
  wren();
  ptr = &buffer[offset];
  wait_1mS();
  pageProgram(pageNumber << 8, ptr);
  wait_1mS();
  return 0;
}

//******************************************************************************
// read pages from flash into buffer, offset defined where in the buffer use
int8_t S25FS512::readPages_Helper(uint32_t startPageNumber,
                                  uint32_t endPageNumber, uint8_t *buffer,
                                  uint32_t offset) {
  uint8_t *ptr;
  uint32_t page;
  ptr = &buffer[offset];
  for (page = startPageNumber; page <= endPageNumber; page++) {
    wait_100uS();
    quadIoRead_Pages((uint32_t)(page << 8), (uint8_t *)ptr, 1);
    ptr += 0x100;
  }
  return 0;
}

