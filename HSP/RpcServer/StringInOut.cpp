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
#include "mbed.h"
#include "USBSerial.h"
#include "RpcFifo.h"
#include "RpcServer.h"
#include "StringInOut.h"
#include "Peripherals.h"

/// a running index that keeps track of where an incoming string has been
/// buffered to
static int lineBuffer_index = 0;
/// a flag that keeps track of the state of accumulating a string
static int getLine_State = GETLINE_WAITING;

/**
* @brief Place incoming USB characters into a fifo
* @param data_IN buffer of characters
* @param len length of data
*/
int fifoIncomingChars(uint8_t data_IN[], unsigned int len) {
  int i;
  for (i = 0; i < len; i++) {
    fifo_put8(GetUSBIncomingFifo(), data_IN[i]);
  }
  return 0;
}

/**
* @brief Check the USB incoming fifo to see if there is data to be read
* @return 1 if there is data to be read, 0 if data is not available
*/
int isReadReady(void) {
  if (fifo_empty(GetUSBIncomingFifo()) == 0)
    return 1;
  return 0;
}

/**
* @brief Clear the incoming USB read fifo
*/
void clearOutReadFifo(void) { fifo_clear(GetUSBIncomingFifo()); }

/**
* @brief Block until a character can be read from the USB
* @return the character read
*/
char getch(void) {
  uint8_t ch;
  // block until char is ready
  while (isReadReady() == 0) {
  }
  // read a char from buffer
  fifo_get8(GetUSBIncomingFifo(), &ch);
  return ch;
}

/**
* @brief Place incoming USB characters into a fifo
* @param lineBuffer buffer to place the incoming characters
* @param bufferLength length of buffer
* @return GETLINE_WAITING if still waiting for a CRLF, GETLINE_DONE
*/
int getLine(char *lineBuffer, int bufferLength) {
  uint8_t ch;

  USBSerial *serial = Peripherals::usbSerial();
  if (getLine_State == GETLINE_DONE) {
    getLine_State = GETLINE_WAITING;
  }
  if (serial->available() != 0) {
    ch = serial->_getc();
    if (ch != 0x0A && ch != 0x0D) {
      lineBuffer[lineBuffer_index++] = ch;
    }
    if (ch == 0x0D) {
      lineBuffer[lineBuffer_index++] = 0;
      lineBuffer_index = 0;
      getLine_State = GETLINE_DONE;
    }
    if (lineBuffer_index > bufferLength) {
      lineBuffer[bufferLength - 1] = 0;
      getLine_State = GETLINE_DONE;
    }
  }
  return getLine_State;
}

/**
* @brief Block until a fixed number of characters has been accumulated from the
* incoming USB
* @param lineBuffer buffer to place the incoming characters
* @param maxLength length of buffer
*/
void getStringFixedLength(uint8_t *lineBuffer, int maxLength) {
  uint8_t ch;
  int index = 0;
  // block until maxLength is captured
  while (1) {
    ch = getch();
    lineBuffer[index++] = ch;
    if (index == maxLength)
      return;
  }
}

/**
* @brief Output a string out the USB serial port
* @param str output this str the USB channel
*/
int putStr(const char *str) {
  Peripherals::usbSerial()->printf("%s", str); // fflush(stdout);
  // uint8_t *ptr;
  // uint8_t buffer[256];
  // int index = 0;
  /*	int length;
          ptr = (uint8_t *)str;
          length = strlen(str);

          Peripherals::usbSerial()->writeBlock(ptr,length);	*/
  return 0;
}

/**
* @brief Outut an array of bytes out the USB serial port
* @param data buffer to output
* @param length length of buffer
*/
int putBytes(uint8_t *data, uint32_t length) {
  int sendThis = 64;
  int sent = 0;
  int thisLeft;
  uint8_t *ptr = data;
  if (length < 64)
    sendThis = length;
  do {
    Peripherals::usbSerial()->writeBlock(ptr, sendThis);
    sent += sendThis;
    ptr += sendThis;
    thisLeft = length - sent;
    sendThis = 64;
    if (thisLeft < 64)
      sendThis = thisLeft;
  } while (sent != length);
  return 0;
}

/**
* @brief Outut 256 byte blocks out the USB serial using writeBlock bulk
* transfers
* @param data buffer of blocks to output
* @param length length of 256-byte blocks
*/
int putBytes256Block(uint8_t *data, int numberBlocks) {
  int i;
  uint8_t *ptr;
  ptr = data;
  const int BLOCK_SIZE = 32;
  const int FLASH_PAGE_SIZE = 256;
  for (i = 0; i < numberBlocks * (FLASH_PAGE_SIZE / BLOCK_SIZE); i++) {
    Peripherals::usbSerial()->writeBlock(ptr, BLOCK_SIZE);
    ptr += BLOCK_SIZE;
  }
  return 0;
}

