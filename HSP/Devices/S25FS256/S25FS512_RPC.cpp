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

#include "S25FS512_RPC.h"
#include "S25FS512.h"
#include "StringInOut.h"
#include "StringHelper.h"
#include "Peripherals.h"
#include "SDFileSystem.h"

int S25FS512_Reset(char argStrs[32][32], char replyStrs[32][32]) {
  uint32_t reply[1];
  Peripherals::s25FS512()->reset();
  reply[0] = 0x80;
  FormatReply32(reply, sizeof(reply) / sizeof(uint32_t), replyStrs);
  return 0;
}

int S25FS512_EnableHWReset(char argStrs[32][32], char replyStrs[32][32]) {
  uint32_t reply[1];
  Peripherals::s25FS512()->enableHWReset();
  reply[0] = 0x80;
  FormatReply32(reply, sizeof(reply) / sizeof(uint32_t), replyStrs);
  return 0;
}

int S25FS512_SpiWriteRead(char argStrs[32][32], char replyStrs[32][32]) {
  uint8_t args[16];
  uint8_t reply[16];
  uint8_t writeNumber;
  uint8_t readNumber;
  // get the number of bytes to write
  ProcessArgs(argStrs, args, 1);
  writeNumber = args[0];
  ProcessArgs(argStrs, args, writeNumber + 2);
  readNumber = args[writeNumber + 1];
  FormatReply(reply, readNumber, replyStrs);
  return 0;
}

int S25FS512_SpiWriteRead4Wire(char argStrs[32][32], char replyStrs[32][32]) {
  uint8_t args[16];
  uint8_t reply[16];
  uint8_t writeNumber;
  uint8_t readNumber;
  // get the number of bytes to write
  ProcessArgs(argStrs, args, 1);
  writeNumber = args[0];
  ProcessArgs(argStrs, args, writeNumber + 2);
  readNumber = args[writeNumber + 1];
  FormatReply(reply, readNumber, replyStrs);
  return 0;
}

int S25FS512_ReadPage(char argStrs[32][32], char replyStrs[32][32]) {
  uint32_t args[2];
  uint32_t reply[1];
  ProcessArgs32(argStrs, args, sizeof(args) / sizeof(uint32_t));
  reply[0] = 0x80;
  FormatReply32(reply, sizeof(reply) / sizeof(uint32_t), replyStrs);
  return 0;
}

//int S25FS512_ReadPagesBinary(char argStrs[32][32], char replyStrs[32][32]) {
//  uint32_t args[2];
//  uint32_t reply[1];
//  uint8_t pageData[256];
//
//  uint32_t startPage;
//  uint32_t endPage;
//  uint32_t page;
//
//  ProcessArgs32(argStrs, args, sizeof(args) / sizeof(uint32_t));
//  startPage = args[0];
//  endPage = args[1];
//  for (page = startPage; page <= endPage; page++) {
//    Peripherals::s25FS512()->readPages_Helper(page, page, pageData, 0);
//    putBytes256Block(pageData, 1);
//  }
//  reply[0] = 0x80;
//  FormatReply32(reply, sizeof(reply) / sizeof(uint32_t), replyStrs);
//  return 0;
//}
extern char dataFileName[32];
int S25FS512_ReadPagesBinary(char argStrs[32][32], char replyStrs[32][32]) {
  uint32_t args[2];
  uint32_t reply[1];
  uint8_t pageData[256];

  uint32_t startPage;
  uint32_t endPage;
  uint32_t page;

  ProcessArgs32(argStrs, args, sizeof(args) / sizeof(uint32_t));
  startPage = args[0];
  endPage = args[1];
  FILE *fp = NULL;
  fp = fopen(dataFileName, "rb");
  for (page = startPage-0x12; page <= endPage-0x12; page++) {
	memset(pageData, 0xffffffff, sizeof(pageData));
	printf("reading from page %d\r\n", page);
	if (fp != NULL) {
		fseek(fp,page*256,SEEK_SET);
		uint8_t count = 0;
		while(!feof(fp))
		{
			printf(".");
			pageData[count++] = (unsigned char) fgetc(fp);
			if (count == 0) break;
		};
	}
	printf("\r\nEND\r\n");
	putBytes256Block(pageData, 1);
  }
  if (fp != NULL) fclose(fp);
  reply[0] = 0x80;
  FormatReply32(reply, sizeof(reply) / sizeof(uint32_t), replyStrs);
  return 0;
}

int S25FS512_ReadId(char argStrs[32][32], char replyStrs[32][32]) {
  char str[32];
  uint8_t data[128];
  Peripherals::s25FS512()->readIdentification(data, sizeof(data));
  Peripherals::s25FS512()->readIdentification(data, sizeof(data));
  sprintf(str, "%02X%02X%02X%02X", data[0], data[1], data[2], data[3]);
  strcpy(replyStrs[0], str);
  return 0;
}
int SDCard_IsReady(char argStrs[32][32], char replyStrs[32][32]) {
	
	DigitalIn *detect = Peripherals::SDDetect();
	
	bool isReady = false;
	
	if(detect->read())
	{
		isReady = false;
		strcpy(replyStrs[0], "not_ok");
		return 0;
	}

	Peripherals::sdFS()->disk_initialize();
	FILE *fp = fopen("/sd/test", "r");
	if ( fp != NULL)
		isReady = true;
	else
	{
		FILE *fp = fopen("/sd/test", "w");
		if ( fp != NULL)
			isReady = true;
	}
	
	if (fp != NULL) fclose(fp);
	
	if (isReady)
		strcpy(replyStrs[0], "ok");
	else
		strcpy(replyStrs[0], "not_ok");
	return 0;
}
