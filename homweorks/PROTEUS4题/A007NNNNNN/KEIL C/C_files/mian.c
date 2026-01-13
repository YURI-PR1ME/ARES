#include <reg51.h>
#include <intrins.h>

// 定义端口
#define SEG_PORT P0      // 段码输出端口
#define BIT_PORT P2      // 位选输出端口

// 数码管段码表（共阳数码管，根据原汇编代码段码表）
// 原段码表：10H,0CH,0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H
// 对应数字：   ,   ,  0 ,  1 ,  2 ,  3 , 4 , 5 , 6 ,  7
const unsigned char seg_code[10] = {
    0xC0,  // 0
    0xF9,  // 1
    0xA4,  // 2
    0xB0,  // 3
    0x99,  // 4
    0x92,  // 5
    0x82,  // 6
    0xF8,  // 7
    0x80,  // 8
    0x90   // 9
};

// 显示缓冲区（8位数码管）
unsigned char display_buffer[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// 延时函数（对应原汇编Q017F）
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 120; j++);
}

// 数码管显示函数（动态扫描）
void display_digits() {
    unsigned char i;
    unsigned char bit_select = 0x01;  // 从第一位开始
    
    for(i = 0; i < 8; i++) {
        // 关闭所有数码管（消隐）
        BIT_PORT = 0x00;
        
        // 输出段码
        SEG_PORT = seg_code[display_buffer[i]];
        
        // 输出位选信号
        BIT_PORT = bit_select;
        
        // 延时（原程序使用Q017F延时）
        delay_ms(2);  // 调整延时时间可改变扫描频率
        
        // 位选左移一位，选择下一个数码管
        bit_select <<= 1;
    }
}

// 初始化函数（对应原汇编初始化部分）
void init() {
    // 初始化显示缓冲区为01234567
    unsigned char i;
    for(i = 0; i < 8; i++) {
        display_buffer[i] = i;
    }
    
    // 初始化端口
    SEG_PORT = 0xFF;
    BIT_PORT = 0x00;
}

// 主函数（对应原程序主循环）
void main() {
    init();  // 初始化
    
    while(1) {
        display_digits();  // 循环显示
    }
}
