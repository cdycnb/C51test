#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "adc0809_driver.h"

/* 数码管引脚定义 */
sbit L3=P2^0;       //数码管位选信号-第4位(最高位)
sbit L2=P2^1;       //数码管位选信号-第3位
sbit L1=P2^2;       //数码管位选信号-第2位
sbit L0=P2^3;       //数码管位选信号-第1位(最低位)

/* 函数声明 */
void Display(uint value);
void Delaytms(uint time);

#endif
