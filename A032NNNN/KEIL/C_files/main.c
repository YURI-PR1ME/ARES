#include <reg51.h>

// 数码管段码表（共阳极，0-9）
code unsigned char seg_table[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,  // 0-4
    0x92, 0x82, 0xF8, 0x80, 0x90   // 5-9
};

unsigned char counter = 0;  // 计数器

void timer0_init(void) {
    TMOD = 0x06;  // 定时器0模式2（自动重装）
    TH0 = 0xFF;   // 重装值
    TL0 = 0xFF;   // 初值
    ET0 = 1;      // 使能定时器0中断
    TR0 = 1;      // 启动定时器0
}

void ext0_init(void) {
    EX0 = 1;      // 使能外部中断0
    IT0 = 1;      // 下降沿触发
}

void display_init(void) {
    P0 = 0x3F;    // 显示0
    P2 = 0x3F;    // 显示0
}

void timer0_isr(void) interrupt 1 {
    // 定时器0中断服务程序
    counter++;
    if (counter >= 100) {
        counter = 0;
    }
}

void ext0_isr(void) interrupt 0 {
    // 外部中断0服务程序
    counter = 0;
}

void main(void) {
    unsigned char tens, units;
    
    // 初始化堆栈指针（汇编中MOV SP,#08H）
    SP = 0x08;
    
    // 初始化
    display_init();
    timer0_init();
    ext0_init();
    
    // 设置中断优先级（汇编中MOV IP,#02H）
    IP = 0x02;  // 定时器0中断优先级高
    
    EA = 1;     // 全局中断使能
    
    while(1) {
        // 显示计数器值
        tens = counter / 10;
        units = counter % 10;
        
        // 显示十位数（P0口）
        P0 = ~seg_table[tens];  // 汇编中CPL A取反了
        
        // 显示个位数（P2口）
        P2 = ~seg_table[units];
    }
}
