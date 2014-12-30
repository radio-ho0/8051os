#include <at89x52.h>
#include "lcd.h"
#include "core.h"

// to show  string
__code char  str1[] = " Hello World!!! ";	
__code char  str2[] = "Practice mk perfect";
__code char  str_task[] = "running task:  ";


void main(void)
{
	LCDInit();	

    DisplayListChar(str1);
    writeline2();
    DisplayListChar(str2);

    writeline2();
//    DisplayListChar("hello ele1000!!!");
    DisplayListChar(str_task);

    timer_init();
    task_init();

    for(;;){
        task_schedu();
        do_task();
    }
}



