#include <REGX51.H>
#include <intrins.h>
#define LCD_DataPort P0
sbit LCD_RS=P2^0;//仿真使用
sbit LCD_RW=P2^1;
sbit LCD_E=P2^2;
// 定义LCD延时函数，适用于12MHz时钟
void LCD_Delay()		
{
 unsigned char i, j;

 i = 12;
 j = 169;
 do
 {
  while (--j);
 } while (--i);
}

// 写入命令到LCD
void LCD_WriteCommand(unsigned char Command)
{
 LCD_RS=0;//命令状态
 LCD_RW=0;
 LCD_DataPort=Command;
 LCD_E=1;//E引脚用于同步数据传输
 LCD_Delay();
 LCD_E=0;//执行命令
 LCD_Delay();
}
 
// 写入数据到LCD
void LCD_WriteData(unsigned char Data)
{
 LCD_RS=1;//写入模式
 LCD_RW=0;
 LCD_DataPort=Data;
 LCD_E=1;
 LCD_Delay();
 LCD_E=0;
 LCD_Delay();
}
 
// 设置LCD显示位置
void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
 if(Line==1)
 {
  LCD_WriteCommand(0x80|(Column-1));
 }
 else if(Line==2)
 {
  LCD_WriteCommand(0x80|(Column-1+0x40));
 }//LCd有两行输出，每行的列数为16
}
// 初始化LCD
void LCD_Init()
{
 LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
 LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
 LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
 LCD_WriteCommand(0x01);//光标复位，清屏
}

// 在指定位置显示字符串
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String)
{
 unsigned char i;
 LCD_SetCursor(Line, Column);
 for(i=0; String[i]!='\0'; i++)
 {
  LCD_WriteData(String[i]);
 }
}
 
// 主函数，程序入口
void main(){
 LCD_Init();//初始化LCD1602
 LCD_ShowString(1, 4, "qwq >_< ");//调用LCD_ShowString函数
 LCD_ShowString(2, 4, "(-_-)//|-|");
 while(1);
}