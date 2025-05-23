#include <reg52.h>
#include "dac0832_driver.h"

// DAC0832控制引脚定义
sbit DAC0832_CS = P1^0;  // 片选信号
sbit DAC0832_WR = P1^1;  // 写入信号
sbit DAC0832_XFER = P1^2; // 传输控制信号

// DAC0832初始化函数
void DAC0832_Init(void)
{
    DAC0832_CS = 1;
    DAC0832_WR = 1;
    DAC0832_XFER = 1;
}

// DAC0832数据转换函数
void DAC0832_Convert(unsigned char value)
{
    DAC0832_CS = 0;  // 选中DAC0832
    DAC0832_WR = 0;  // 允许写入
    P0 = value;      // 输出数据到P0口
    DAC0832_WR = 1;  // 锁存数据
    DAC0832_CS = 1;  // 取消选中
}
