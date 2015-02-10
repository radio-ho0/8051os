#include <at89x52.h>
//#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "lcd1602.h"

task_t tasks[TASK_MAX];
__sbit __at 0x95  TRIG; // P1_1
__sbit __at 0x96  ECHO;

char* __code num_array[] = {
    "0", "1", "2", "3", "4",
    "5", "6", "7", "8", "9",
};

// TODO:
//void add_task( ..... );

unsigned char TASK_NUM_POS = 15;
extern int count = 0;
int j = 0;
char todo_flag = 0;
void (*todo_task)(void);

inline void taskReport(int num);
void timer_init(void)
{
    TMOD &= 0xf0;
    TMOD |= 0x00;
    ET0 = 1;
    TR0 = 1;
    TL0 = TL0_0;
    TH0 = TH0_0;
    EA = 1;

}


void task_manager(void) __interrupt(1)
{

    TL0 = TL0_0;
    TH0 = TH0_0;

    up_task_date();

    count++;
    if(count >= TIMER_1S){ // 1s
    //    P0 = ~P0;
    
        count = 0;
    }
}

void task_init(void)
{
    EA = 0;
    for(j = 0; j< TASK_MAX; ++j){
        tasks[j].runit = 0;
        tasks[j].delay = 0;
    }
//    tasks[0].runit = &task1;
//    tasks[0].delay = 200;
    app_add(&task1, 300);
    app_add(&task2, 500);

//    tasks[2].runit = &task3;
 //   tasks[2].delay = 500;
 
    app_add(&task3, TIMER_1S);
    app_add(&task4, 330);
    for(j = 0; j< TASK_MAX; ++j){
        tasks[j].counter = 0;
    }

    EA = 1;

}

void task_schedu(void)
{
    EA = 0;

    for(j = 0; j< TASK_MAX; ++j){
        if(  (tasks[j].counter >= tasks[j].delay ) && (tasks[j].runit)){
            tasks[j].counter = 0;
//            tasks[j].runit();
            todo_task = tasks[j].runit;
            todo_flag = 1;

        }

    }

    EA = 1;

}

void do_task(void)
{
    EA = 0;
    if( todo_flag ){
        todo_flag = 0;
        todo_task();
    }
    EA = 1;

    gotosleep();

}

void app_add(void (*task)(), int delay )
{

   int  index = 0;
    EA = 0;

    while( (tasks[index].runit ) && (index < TASK_MAX)){
        ++index;
    }

    if(index == TASK_MAX){
        return;
    }

            tasks[index].runit = task;
            tasks[index].delay = delay;
    EA = 1;
}

void up_task_date(void)
{
    for(j = 0; j< TASK_MAX; ++j){
        if(tasks[j].runit){
            ++tasks[j].counter;
        }
    }

}

void gotosleep(void)
{

    PCON |= 0x01;

}

void task1(void)
{
    P2 =~P2;
    LcdShowStr(TASK_NUM_POS - 1, 2, "&");
    taskReport(1);
}

void task2(void)
{
    P0 = ~P0;
    LcdShowStr(TASK_NUM_POS - 1, 2, "^");
    taskReport(2);
}

void task3(void)
{
    P3 = ~P3;
    LcdShowStr(TASK_NUM_POS - 1, 2, "-");
    taskReport(3);
}

void task4(void)
{
}
//
// /* itoa:  convert n to characters in s */
// void itoa(int n, char s[])
// {
//     int i, sign;
// 
//     if ((sign = n) < 0)  /* record sign */
//         n = -n;          /* make n positive */
//     i = 0;
//     do {       /* generate digits in reverse order */
//         s[i++] = n % 10 + '0';   /* get next digit */
//     } while ((n /= 10) > 0);     /* delete it */
//     if (sign < 0)
//         s[i++] = '-';
//     s[i] = '\0';
//     reverse(s);
// }
//  
// 
// /* reverse:  reverse string s in place */
// void reverse(char s[])
// {
//     int i, j;
//     char c;
// 
//     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
//         c = s[i];
//         s[i] = s[j];
//         s[j] = c;
//     }
// }
void taskReport(int num)
{
    LcdShowStr(TASK_NUM_POS - 1, 0, num_array[num]);
}
