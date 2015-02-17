#ifndef  _LCD1602_H_
#define _LCD1602_H_

#include <at89x52.h>
typedef unsigned int uint;


void LcdWaitReady();
void LcdWriteCmd(unsigned char cmd);
void LcdWriteDat(unsigned char dat);
void LcdSetCursor(unsigned char x, unsigned char y);
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);
void ShowStr(unsigned char* str);
void InitLcd1602(void);
void LcdShowNum(uint x, uint y, uint number);

#endif
