#include "distancer.h"
#include <compiler.h>
SBIT(TRIG, 0xb0, 2);
SBIT(ECHO, 0xb0, 3);
int L = 0;
void UltStart()
{
    char i;
    TRIG = 1;
    for ( i = 0; i < 45; i++ ) {
        ;
    }
    TRIG = 0; 
}

void UltInit()
{
    TMOD &= 0x0f;
    TMOD |= 0x10;           //设T0为方式1；
    TH1 = 0;
    TL1 = 0; 
    TR1 = 1;  
    ET1 = 1;               //允许T0中断
    EA = 1;                //开启总中断
    TRIG = 0;
}

void UltCount()
{
    float time = 0.0;

    while(!ECHO);                //等待高电平
    TR1 = 1;                   //打开计时器
    while(ECHO);                 //等待低电平
    TR1 = 0;                   //关闭计时器

    time = TH1 * 256.0 + TL1;      //计算时间
    //L = 0.18446*time;
    //L = 1 *time;
    //L = (time * 2 ) / 9;
    L = time * 0.18746;
    TH1 = 0;                   //重置计时器
    TL1 = 0;
}

void ShowDistance()
{
    LcdShowNum(1, 2, L);
}
