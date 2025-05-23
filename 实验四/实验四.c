#include <reg51.h>
#include <stdio.h>

unsigned char int_count = 0;  // 中断次数计数器
// 数码管段码数组：用于显示0-9的数字
unsigned char seg_code[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void Delay1ms()		//@12MHz
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void Delay(unsigned int t) {
    while(t--){
				Delay1ms();
		};
}

// 中断服务程序（INT0中断）
void int0_isr(void) interrupt 0 {
    int_count++;
}

void Display(unsigned char tens, unsigned char units) {
    // 显示十位数
    P1 = 0x02;  // 假设P1的第二位控制十位数码管的位
    P0 = seg_code[tens];  // 根据十位数字选择相应的段码
    Delay(5);  // 保持显示一段时间

    // 显示个位数
    P1 = 0x01;  // 假设P1的第一位控制个位数码管的位
    P0 = seg_code[units];  // 根据个位数字选择相应的段码
    Delay(5);  // 保持显示一段时间
}

void main(void) {
    IT0 = 1;  // 设置INT0为下降沿触发
    EX0 = 1;  // 允许INT0中断
    EA = 1;  // 允许全局中断

    while (1) {
        Display((int_count / 10) % 10, int_count % 10);  // 显示中断次数的十位数和个位数
        Delay(5);  // 延时一段时间，防止数码管闪烁过快
    }
}
