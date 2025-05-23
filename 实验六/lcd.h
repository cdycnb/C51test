#ifndef LCD_H
#define LCD_H

#include <REGX52.H>

/*引脚定义*/
#define LCD_DATA P0
sbit E=P2^2;
sbit RW=P2^3;
sbit RS=P2^4;
sbit RST=P2^0;
sbit CS1=P2^5;
sbit CS2=P2^6;

/*函数声明*/
void CheckBusy(void);
void WriteCommand(unsigned char cmd);
void WriteData(unsigned char dat);
void SetPage(unsigned char page);
void SetColumn(unsigned char column);
void SelectScreen(unsigned char screen);
void LCD_Init(void);
void Delay(unsigned int xms);
void Display_char(unsigned char screen, unsigned char page, unsigned char column, unsigned char *p);
void LCD_ClearScreen(void);
void LCD_ShowString(unsigned char screen, unsigned char page, unsigned char column, char *str);

#endif
