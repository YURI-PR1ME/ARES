#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

// 定义数码管段码表（对应汇编中的 Q0181 处的数据）
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 全灭
uchar code table[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 
    0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF
};

// 内存变量定义
uchar display_buf[8]; // 显示缓冲区 (对应汇编中 10H-17H)
uchar backup_buf[8];  // 备份缓冲区 (对应汇编中 08H-0FH)
uchar current_pos = 0; // 当前编辑位置 (对应汇编中的 1CH)
uchar key_val = 0;    // 按键值 (对应汇编中的 1BH)

// 延时子程序 (对应汇编 Q0168)
void delay(uint t) {
    while(t--);
}

// 刷新数码管显示 (对应汇编 Q00D6)
void refresh_display() {
    uchar i;
    uchar scan_bit = 0x80; // 从最高位或最低位开始扫描
    for(i = 0; i < 8; i++) {
        P2 = 0; // 消隐
        P0 = table[display_buf[i]]; // 送段码
        P2 = scan_bit; // 送位选
        delay(100);    // 扫描延时
        
        // 位选循环右移 (对应汇编 RR A)
        if(scan_bit == 0x01) scan_bit = 0x80;
        else scan_bit >>= 1;
    }
}

// 获取按键输入 (对应汇编 Q010C)
uchar get_key() {
    uchar temp;
    P1 = 0x0F;        // 设置低4位为输入
    temp = P1 & 0x0F;
    if(temp != 0x0F) { // 检测到按键按下
        delay(1000);   // 消抖
        temp = P1 & 0x0F;
        if(temp != 0x0F) {
            uchar val = temp;
            // 等待按键释放并持续显示
            while((P1 & 0x0F) != 0x0F) {
                refresh_display();
            }
            return val; // 返回键值
        }
    }
    return 0x0F; // 无键按下
}

// 按键逻辑处理 (对应汇编 Q008F)
void process_key(uchar k) {
    if(k == 0x0E) { // 某个特定按键：光标右移/数值增加
        current_pos++;
        if(current_pos > 7) current_pos = 7;
        display_buf[current_pos] = current_pos; 
    } 
    else if(k == 0x0D) { // 某个特定按键：回退/清零
        if(current_pos >= 0) {
            display_buf[current_pos] = 0x0A; // 显示空白
            if(current_pos > 0) current_pos--;
        }
    }
    else if(k == 0x0B) { // 某个特定按键：重置/复制
        uchar i;
        current_pos = 0;
        for(i = 0; i < 8; i++) {
            display_buf[i] = backup_buf[i];
        }
    }
}

// 初始化缓冲区 (对应汇编 Q0142)
void init_buffer() {
    uchar i;
    for(i = 0; i < 8; i++) {
        backup_buf[i] = 0x0A; // 汇编 Q0176 定义的初始数据
        display_buf[i] = backup_buf[i];
    }
  display_buf[0] = 0x00;
    current_pos = 0;
}

// 主程序
void main() {
    // 汇编开头的内存清理逻辑
    init_buffer();
    
    while(1) {
        key_val = get_key();
        if(key_val != 0x0F) {
            process_key(key_val);
        }
        refresh_display();
    display_buf[0] =0 ;
    }
}
