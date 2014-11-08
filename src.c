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

    TASK_MAX = 3,

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
int i;

typedef struct task task_t;

task_t tasks[3];

void task_schedu(void);
void up_task_date(void);
void task_init(void);

void task1(void);
void task2(void);
void task3(void);

// TODO:
//void add_task( ..... );


int count = 0;
void interrupt1(void)  __interrupt(1);

void main(void)
{
    task_init();
    count = 0;
    TMOD = 0x00;
    ET0 = 1;
    TR0 = 1;
    TL0 = TL0_0;
    TH0 = TH0_0;
    EA = 1;

	P0 = 0x81;

	for (;;) {
        task_schedu();
	}

}

void interrupt1(void) __interrupt(1)
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
    tasks[0].runit = &task1;
    tasks[0].delay = TIMER_1S;

    tasks[1].runit = &task2;
    tasks[1].delay = 400;

    tasks[2].runit = &task3;
    tasks[2].delay = 500;




    for(i = 0; i< TASK_MAX; ++i){
        tasks[i].counter = 0;
    }

}

void task_schedu(void)
{
    for(i = 0; i< TASK_MAX; ++i){
        if(  tasks[i].counter >= tasks[i].delay){
            tasks[i].runit();
            tasks[i].counter = 0;

        }

    }

}
void up_task_date(void)
{
    for(i = 0; i< TASK_MAX; ++i){
        ++tasks[i].counter;
    }

}

void task1(void)
{
    P2 =~P2;
}

void task2(void)
{
    P0 = ~P0;

}

void task3(void)
{
    P1 = ~P1;
}
