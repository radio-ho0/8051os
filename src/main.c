#include <at89x52.h>
#include "lcd1602.h"
#include "core.h"

// to show  string
__code char  str1[] = " Hello World!!! ";	
__code char  str2[] = "Practice mk perfect";
__code char  str3[] = "$status$:: ";
__code char  str_task[] = "running task:  ";


void main(void)
{
    InitLcd1602();
    LcdShowStr(2, 0, str1);
    LcdShowStr(0, 1, str2);
    LcdShowStr(0, 1, str3);

//    DisplayListChar("hello ele1000!!!");
    ShowStr(str_task);

    timer_init();
    task_init();

    for(;;){
        task_schedu();
        do_task();
    }
}



