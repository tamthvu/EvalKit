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
#include "QuadSpiInterface.h"

/**
* @brief Constructor that accepts pin names for the QUAD SPI interface
* @param mosi master out slave in pin name
* @param miso master in slave out pin name
* @param sclk serial clock pin name
* @param cs chip select pin name
*/
QuadSpiInterface::QuadSpiInterface(PinName mosi, PinName miso, PinName sclk,
                                   PinName cs)
    : spi(mosi, miso, sclk), csPin(cs) {

    }

/**
* @brief Transmit and recieve QUAD SPI data
* @param tx_buf pointer to transmit byte buffer
* @param tx_size number of bytes to transmit
* @param rx_buf pointer to the recieve buffer
* @param rx_size number of bytes to recieve
* @param last flag to indicate if this is the last QUAD SPI transaction for the
* current chip select cycle
*/
int QuadSpiInterface::SPI_Transmit(const uint8_t *tx_buf, uint32_t tx_size,
                                   uint8_t *rx_buf, uint32_t rx_size,
                                   int last) {
  uint32_t i;
  int result = 0;
  int index = 0;
  // lower chip select
  csPin = 0;
  // write bytes out QUAD SPI
  spi.setQuadMode();
  for (i = 0; i < tx_size; i++) {
    rx_buf[index] = spi.write((int)tx_buf[i]);
    index++;
  }
  // read in bytes from QUAD SPI
  for (i = 0; i < rx_size; i++) {
    rx_buf[index] = (uint8_t)spi.read();
    index++;
  }
  // raise chip select if this is the last transaction
    if (last) csPin = 1;
  return result;
}

/**
* @brief Transmit and recieve QUAD SPI data
* @param tx_buf pointer to transmit byte buffer
* @param tx_size number of bytes to transmit
* @param rx_buf pointer to the recieve buffer
* @param rx_size number of bytes to recieve
* @param last flag to indicate if this is the last QUAD SPI transaction for the
* current chip select cycle
*/
int QuadSpiInterface::SPI_Transmit4Wire(const uint8_t *tx_buf, uint32_t tx_size,
                                        uint8_t *rx_buf, uint32_t rx_size,
                                        int last) {
  uint32_t i;
  int result = 0;
  int index = 0;
  // lower chip select
  csPin = 0;
  // write bytes out Single SPI
  spi.setSingleMode();
  for (i = 0; i < tx_size; i++) {
    rx_buf[index] = spi.write((int)tx_buf[i]);
    index++;
  }
  // raise chip select if this is the last transaction
    if (last) csPin = 1;
  return result;
}

