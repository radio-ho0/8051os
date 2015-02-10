#include <at89x52.h>

/* 
+--------+------+------+-----------+
|   P0   |  P1  | P2   |  P3       |
+--------+------+------+-----------+
|   0x80 | 0x90 | 0xA0 | 0xB0      |
+--------+------+------+-----------+
*/
__sfr __at 0x80 LED;
__sfr __at 0x90 NUM;
__sbit __at 0x80 LED1;

enum count_num{
    TIMER_1S = 200,

    TASK_MAX = 5,

};


#define TIMES (5000)

#define TH0_0 ((8192 - TIMES) >> 8 )
#define TL0_0 (8192 - TIMES)

struct task{
//    char* name;
    void (*runit)(void);
    int delay;                   // how long run once
    int counter;                 // task timer 
 //   int perioy;
};


typedef struct task task_t;
void task_schedu(void);
void up_task_date(void);
void task_init(void);
void task_manager(void)  __interrupt(1);
void timer_init(void);
void gotosleep(void);
void do_task(void);
void app_add(void (*task)(void), int delay);
//void itoa(int val, char* str);
//void reverse(char s[]);


void task1(void);
void task2(void);
void task3(void);
void task4(void);
