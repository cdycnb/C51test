#ifndef __ADC0809_DRIVER_H__
#define __ADC0809_DRIVER_H__

#include<reg52.h>

#define uint unsigned int
#define uchar unsigned char

/* 引脚定义 */
sbit WRITE=P3^6;    //ADC写控制引脚
sbit READ=P3^7;     //ADC读控制引脚
sbit EOC=P3^0;      //转换结束状态引脚
sbit CLK=P3^1;      //时钟信号引脚
sbit CS=P2^7;       //片选信号引脚

/* 函数声明 */
void ADC0809_Init(void);
uint ADC0809_Read(void);


#endif
