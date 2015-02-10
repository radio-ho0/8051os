#include "lcd1602.h"
void main(void)
{
    unsigned char str[] = "hello world!";

    InitLcd1602();
    LcdShowStr(2, 0, str);
    LcdShowStr(0, 1, "go!");

    for(;;){

    }

}
