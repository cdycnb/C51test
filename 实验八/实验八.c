#include <reg52.h>
#include "dac0832_driver.h"
#include "app_waveform.h"

/***********变量定义********************************/
unsigned char timer0_peroid=200;

//主函数，初始化DAC0832并配置定时器0中断
void main(void)
{	
    DAC0832_Init();
    TMOD=0x02;//in mode 2自动重装模式
    TH0=0-timer0_peroid;//
    TL0=0-timer0_peroid;//56
    TR0=1;//启动T0计时器
    PT0=1;//高级中断（优先级高于T0中断定时器0）
    ET0=1;//允许T0中断
    EA=1;//打开中断总开关
    
    while(1)
    {
        GenerateWaveform();
    }
}

//timer0中断函数，用于定时更新波形数据
void timer_0 () interrupt 1
{
    TH0=0-timer0_peroid;//56
    TL0=0-timer0_peroid;//56
    counter++;
}