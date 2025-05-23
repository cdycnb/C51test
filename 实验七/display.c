#include "display.h"

// 共阳极数码管段码表：0-9
uchar code mode[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

/* 数码管显示函数 */
void Display(uint value)
{
    uint a, b, c;
    // 将0-255的ADC值转换为0.00-5.00V的显示值
    a = value / 51;             //整数部分
    b = (value * 10 / 51) % 10; //小数点后第一位
    c = (value * 100 / 51) % 10;//小数点后第二位
    
    // 位选和段选控制，动态显示4位数码管
    L3=0; L2=1; L1=1; L0=1; //选中第4位
    P1 = 0x00;           //显示"0"
    Delaytms(2);            //延时2ms
    
    L3=1; L2=0; L1=1; L0=1; //选中第3位
    P1=mode[a]&0x7f;        //显示整数部分，并点亮小数点
    Delaytms(2);
    
    L3=1; L2=1; L1=0; L0=1; //选中第2位
    P1= mode[b];            //显示小数第一位
    Delaytms(2);
    
    L3=1; L2=1; L1=1; L0=0; //选中第1位
    P1=mode[c];             //显示小数第二位
    Delaytms(2);
}

/* 延时函数 */
static void Delaytms(uint time)
{
    uint i,j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 125; j++); //1ms基准延时
}
