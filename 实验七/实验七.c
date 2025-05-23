#include "adc0809_driver.h"
#include "display.h"
#include <stdio.h>
#include <reg52.h>
uint V = 0; // 存储ADC转换结果

/* 主函数 */
void main()
{
    // 系统初始化
    ADC0809_Init();
    
    while(1)
    {
        // 读取ADC值并显示
        V = ADC0809_Read();
        Display(V);
    }    
}
