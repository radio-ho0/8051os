__sbit __at 0x90 LCD_RS;
__sbit __at 0x91 LCD_RW;
__sbit __at 0x92 LCD_E;
__sfr  __at 0xa0  LCD_Data;

void WriteDataLCD(char WDLCD);
void WriteCommandLCD(char WCLCD);

void LCDInit(void);
void ChangeCursor(char X, char Y);
void DisplayListChar(char *DData);

void delay_us(unsigned int t);
void writewhere(unsigned char pos);

void writeline1(void);
void writeline2(void);

