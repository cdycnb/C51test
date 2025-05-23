#include <reg51.h>

// 按键定义
sbit KEY1 = P3^0;  // 亮度25%
sbit KEY2 = P3^1;  // 亮度50%
sbit KEY3 = P3^2;  // 亮度75%
sbit KEY4 = P3^3;  // 亮度100%

// LED输出端口
#define LED P2

// 全局变量
unsigned char brightness = 4;  // 默认亮度等级4（100%）
unsigned char led_pattern = 0xfe;  // 初始LED模式（第一个LED亮）

// 延时函数 - 基准延时单位
void delay(unsigned int time) {
    unsigned int i, j;
    for(i=0; i<time; i++)
        for(j=0; j<1275; j++);  // 基准延时单位
}

// 按键检测与消抖处理
void check_keys() {
    // 检测按键1 - 25%亮度
    if(!KEY1) { 
        delay(20);  // 消抖延时
        if(!KEY1) { 
            brightness = 1;  // 设置亮度等级1
            while(!KEY1);  // 等待按键释放
        }
    }
    
    // 检测按键2 - 50%亮度
    if(!KEY2) { 
        delay(20);  // 消抖延时
        if(!KEY2) { 
            brightness = 2;  // 设置亮度等级2
            while(!KEY2);  // 等待按键释放
        }
    }
    
    // 检测按键3 - 75%亮度
    if(!KEY3) { 
        delay(20);  // 消抖延时
        if(!KEY3) { 
            brightness = 3;  // 设置亮度等级3
            while(!KEY3);  // 等待按键释放
        }
    }
    
    // 检测按键4 - 100%亮度
    if(!KEY4) { 
        delay(20);  // 消抖延时
        if(!KEY4) { 
            brightness = 4;  // 设置亮度等级4
            while(!KEY4);  // 等待按键释放
        }
    }
}

// 亮度控制延时函数
void brightness_delay() {
    unsigned int i;
    
    // 根据亮度等级调整PWM占空比
    for(i = 0; i < 100; i++) {
        switch(brightness) {
            case 1:  // 25%亮度
                LED = led_pattern;  // 输出LED模式
                delay(1);           // 亮1个单位
                LED = 0xFF;         // 熄灭所有LED
                delay(3);           // 灭3个单位
                break;
                
            case 2:  // 50%亮度
                LED = led_pattern;  // 输出LED模式
                delay(2);           // 亮2个单位
                LED = 0xFF;         // 熄灭所有LED
                delay(2);           // 灭2个单位
                break;
                
            case 3:  // 75%亮度
                LED = led_pattern;  // 输出LED模式
                delay(3);           // 亮3个单位
                LED = 0xFF;         // 熄灭所有LED
                delay(1);           // 灭1个单位
                break;
                
            case 4:  // 100%亮度
                LED = led_pattern;  // 输出LED模式
                delay(4);           // 亮4个单位
                break;
        }
    }
}

// 更新流水灯模式
void update_led_pattern() {
    // 判断是否所有LED都熄灭了
    if(led_pattern == 0xFF) {
        led_pattern = 0xFE;  // 重新开始，第一个LED亮
    } else {
        // 左移一位，最低位补1（实现流水效果）
        led_pattern = (led_pattern << 1) | 0x01;
    }
}

void main() {
    P1 = 0xFF;  // 启用P1口上拉电阻（按键输入）
    LED = 0x00; // 初始化LED端口
    
    // 启动前的初始效果
    brightness_delay();
    LED = 0xFE;  // 初始LED模式
    
    while(1) {
        check_keys();         // 检测按键输入
        brightness_delay();   // 执行亮度控制延时
        update_led_pattern(); // 更新LED显示模式
    }
}