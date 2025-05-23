#include "adc0809_driver.h"

/* 初始化函数 */
void ADC0809_Init(void)
{
    // 初始化ADC0809控制引脚
    CS=0;
    CLK=0;
    WRITE=1;        //内部寄存器清零
    EOC=1;          //转换结束标志(未开始)
    READ=0;
    
    //配置定时器0为模式2(自动重装)
    TMOD=0x02;      //0000_0010 8位定时器，自动重装
    TH0=200;        //定时初值
    TL0=200;        //自动重装值
    EA=1;           //开总中断
    ET0=1;          //开定时器0中断
    TR0=1;          //启动定时器0
}

/* 定时器0中断服务函数 */
void Timer0_ISR() interrupt 1//定时器0产生中断时
{
    // 产生ADC0809所需时钟信号
    CLK=!CLK;
}
static void Delaytms(uint time)
{
    uint i,j = 0;
    for (i = 0;i < time;i++)
        for (;j < 125;j++);
}
/* 读取ADC值 */
uint ADC0809_Read(void)
{
    uint value;
    
    // 启动ADC0809转换
    CS=0;//片选信号，选择ADC0809
    READ=1;//不读取数据
    WRITE=1;    //START引脚先置高
    Delaytms(1);
    WRITE=0;    //START引脚下降沿触发转换
    Delaytms(1);
    WRITE=1;//一次转化结束
    
    while(EOC==0);  //等待转换完成(EOC变高)
    READ=0;         //使能输出，读取转换结果
    value=P0;       //读取ADC转换值
    
    return value;
}
