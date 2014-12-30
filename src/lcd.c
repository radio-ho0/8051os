#include <at89x52.h>
#include "lcd.h"
void WriteDataLCD(char WDLCD)
{
	LCD_Data = WDLCD;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 1;		
	delay_us(100);
	LCD_E = 0;
	delay_us(100);
}

void WriteCommandLCD(char WCLCD)
{
	LCD_Data = WCLCD;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_E = 1;
	delay_us(100);	
	LCD_E = 0;
	delay_us(100);
}

void LCDInit(void)	
{
	WriteCommandLCD(0x38);	
	WriteCommandLCD(0x06);
	WriteCommandLCD(0x0c);	// blink cursor 

	WriteCommandLCD(0x01);	//  clear screen
	delay_us(5000);
}

void DisplayListChar(char *DData)
{
	char x;
	x = 0;
	while (DData[x] != 0)
	{
		WriteDataLCD(DData[x]);
		x++;
	}
}

void delay_us(unsigned int t)
{  
    int  i;
    EA = 0;
    TMOD &= 0x0f;
    TMOD |= 0x10;        
   //for(i=0;i<20;i++)  
   for(i=0;i<2;i++)  
    {
      TH1 = (65536-t) / 256; 
      TL1 = (65536-t) % 256;
      TR1 = 1;       
	  while(TF1 == 0);
	  TF1 = 0;       
      TR1 = 0;      
    }
   EA  = 1;
}

void writewhere(unsigned char pos)
{
    WriteCommandLCD(pos |(0x80 + 0x40));
}

void writeline1(void)
{
    WriteCommandLCD(0x80);	
}
void writeline2(void)
{
    WriteCommandLCD(0x80 + 0x40);	
}
