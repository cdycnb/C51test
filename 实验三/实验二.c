#include <reg51.h> // 针对C51的头文件
#include <stdio.h>

unsigned char time = 0; // 时间变量
unsigned char x = 0; // 循环变量

// 数码管显示数组，存储0-9的8段码，这里只用到1-8
unsigned char code num_code[9] = {
    0xC0, // 0  11110000
    0xF9, // 1  11111001
    0xA4, // 2  10100100
    0xB0, // 3  10110000
    0x99, // 4  10011001
    0x92, // 5  10010010
    0x82, // 6  10000010
    0xF8, // 7  11111000
    0x80  // 8  10000000
};

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

void Delay100us()		//@12MHz
{
	unsigned char i, j;

	i = 2;
	j = 33;
	do
	{
		while (--j);
	} while (--i);
}

void delay(unsigned int t)	//@12MHz
{
    while (t--){
        Delay1ms();
    };
}

void shumaguan(){
    x++;
    if(x == 9){
        x = 1;
    }
    // 只片选一个数码管，其他不片选
    P1 = 0xFF; // 初始化P1端口为高电平
    P1= ~(1 << (x - 1)); // 设置P1的相应位为低电平（片选）
    P0 = num_code[x]; // 根据x的值从数组中读取相应的8段码并显示
    delay(100); // 延时1秒
}

void main(){
    P0 = 0x00; // 初始化P0口为输出状态
    P1 = 0xFF; // 初始化P1端口为高电平（不片选任何数码管）
    while(1){
        shumaguan();
    }
}
