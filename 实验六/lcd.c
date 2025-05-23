#include "lcd.h"

/*汉字字模数据*/


/*延时函数*/
void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

/*检测忙状态*/
void CheckBusy(void)
{
    LCD_DATA=0X00;
    RS=0;
    RW=1;
    E=1;
	Delay(10);
    while(LCD_DATA&0x80);
    E=0;
}

/*写命令*/
void WriteCommand(unsigned char cmd)
{
	CheckBusy();
    RS=0;
    RW=0;
    E=1;
    LCD_DATA=cmd;
    E=0;
	Delay(10);
}

/*写数据*/
void WriteData(unsigned char dat)
{
	CheckBusy();
    RS=1;
    RW=0;
    E=1;
    LCD_DATA=dat;
    E=0;
	Delay(10);
}

/*设置页地址*/
void SetPage(unsigned char page)
{
	page|=0xB8;
	WriteCommand(page); 
}

/*设置列地址*/
void SetColumn(unsigned char column)
{
	column|=0x40;
	WriteCommand(column);
}

/*选择屏幕*/
void SelectScreen(unsigned char screen)
{
	switch(screen)
	{
		case 0:CS1=0;CS2=0;break;
		case 1:CS1=0;CS2=1;break;
		case 2:CS1=1;CS2=0;break;
		default:CS1=0;CS2=0;break;
	}
}

/*LCD初始化*/
void LCD_Init(void)
{
	CheckBusy();
	Delay(10);
	SelectScreen(0);
	Delay(10);
	WriteCommand(0x01);
	Delay(10);
	WriteCommand(0x0C);
	Delay(10);
	WriteCommand(0x06);
	Delay(10);
}

/*显示字符*/
void Display_char(unsigned char screen,unsigned char page,unsigned char column,unsigned char *p)
{
	unsigned char i=0;
	SelectScreen(screen);
	SetPage(page);
	SetColumn(column);
	for(i=0;i<16;i++)
	{
		WriteData(p[i]);
	}
	SetPage(page+1);
	SetColumn(column);
	for(i=0;i<16;i++)
	{
		WriteData(p[i+16]);
	}
}

/*清屏*/
void LCD_ClearScreen(void) 
{
    WriteCommand(0x01);
    Delay(1);
}

/*显示字符串*/
void LCD_ShowString(unsigned char screen,unsigned char page,unsigned char column,char *str)
{
	unsigned char i=0;
	SelectScreen(screen);
	SetPage(page);
	SetColumn(column);
	for(i=0;i<8;i++)
	{
		WriteData(str[i]);
	}
	SetPage(page+1);
	SetColumn(column);
	for(i=0;i<8;i++)
	{
		WriteData(str[i+8]);
	}
}
