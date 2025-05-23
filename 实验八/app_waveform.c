#include "app_waveform.h"
#include "dac0832_driver.h"

// 全局变量定义
bit flag = 0; // 状态量：0=上升，1=下降
unsigned char counter = 0; // 软件计数器
void GenerateWaveform(void)//波形函数
{
    static unsigned char i; // 输入量D
    
    if(counter == 20)
    {
        counter = 0;
        if(flag == 0)//需要上升
        {
            for(i=0; i<=20; i++)		
            {
                DAC0832_Convert(i);//递增实现
            }			
            flag = 1;
        }
        else//需要下降
        { 
            for(i=19; i>=0; i--)
            {
                DAC0832_Convert(i);
            }
            flag = 0;
        }
    }
}