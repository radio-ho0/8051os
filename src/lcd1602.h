
#include <at89x52.h>
void LcdWaitReady();
void LcdWriteCmd(unsigned char cmd);
void LcdWriteDat(unsigned char dat);
void LcdSetCursor(unsigned char x, unsigned char y);
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);
void showStr(unsigned char* str);
void InitLcd1602(void);
