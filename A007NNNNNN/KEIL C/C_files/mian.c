#include <reg51.h>
#include <intrins.h>

// ????
#define SEG_PORT P0  // ????
#define BIT_PORT P2  // ????

// ????
unsigned char display_buffer[4] = {0};  // ?????,???? 0x08-0x0B
unsigned char bit_select = 0x01;        // ????,?? 0x1F
unsigned char display_index = 0;        // ????,?? 0x1E
unsigned int timer_value = 0;           // ????,?? 0x1C-0x1D

// ???? (0-F)
const unsigned char seg_code[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90, // 9
    0x88, // A
    0x83, // b
    0xC6, // C
    0xA1, // d
    0x86, // E
    0x8E  // F
};

// ???? - ?? Q017F
void delay_ms(unsigned char ms) {
    while(ms--) {
        unsigned char i = 235;
        while(i--);
    }
}

// 16????? - ?? Q0113
unsigned int divide_16bit(unsigned int dividend, unsigned int divisor) {
    if(divisor == 0) return 0;
    
    if(divisor < 256) {
        // ?? Q0142-Q0167
        unsigned char high = (unsigned char)(dividend >> 8);
        unsigned char low = (unsigned char)(dividend & 0xFF);
        unsigned char divisor_byte = (unsigned char)divisor;
        
        // ????
        unsigned char quotient_high = high / divisor_byte;
        unsigned char remainder_high = high % divisor_byte;
        
        // ????
        unsigned int temp = (remainder_high << 8) + low;
        unsigned char quotient_low = temp / divisor_byte;
        unsigned char remainder_low = temp % divisor_byte;
        
        return (quotient_high << 8) | quotient_low;
    } else {
        // ?? Q0121-Q013E
        unsigned int quotient = 0;
        unsigned int remainder = 0;
        
        for(unsigned char i = 0; i < 16; i++) {
            remainder = (remainder << 1) | ((dividend >> 15) & 1);
            dividend <<= 1;
            quotient <<= 1;
            
            if(remainder >= divisor) {
                remainder -= divisor;
                quotient |= 1;
            }
        }
        
        return quotient;
    }
}

// ??????? - ?? Q008F-Q00E2
void update_display_buffer(void) {
    unsigned int value = timer_value;
    
    // ???? (??1000)
    display_buffer[0] = divide_16bit(value, 1000);
    value = timer_value % 1000;
    
    // ???? (??100)
    display_buffer[1] = divide_16bit(value, 100);
    value = value % 100;
    
    // ???? (??10)
    display_buffer[2] = divide_16bit(value, 10);
    
    // ??
    display_buffer[3] = value % 10;
    
    // ??????:??????????????????,????
    // ???????????????
    for(unsigned char i = 0; i < 4; i++) {
        display_buffer[i] = seg_code[display_buffer[i]];
    }
}

// ???? - ?? Q00E3-Q0112
void display_digits(void) {
    unsigned char i;
    
    for(i = 0; i < 4; i++) {
        // ???????
        BIT_PORT = 0x00;
        
        // ?????????
        unsigned char offset = i + 8;  // 0x08, 0x09, 0x0A, 0x0B
        unsigned char seg_index = display_buffer[i];
        
        // ?????
        SEG_PORT = seg_code[seg_index];
        
        // ????????
        BIT_PORT = bit_select;
        
        // ????
        delay_ms(1);
        
        // ??????
        bit_select = _crol_(bit_select, 1);
    }
}

// ????? - ?? Q0195
void system_init(void) {
    // ????????
    display_buffer[0] = 0;  // ??
    display_buffer[1] = 0;  // ??
    display_buffer[2] = 0;  // ??
    display_buffer[3] = 0;  // ??
    
    // ???????
    bit_select = 0x01;
    
    // ???????
    timer_value = 0;
    
    // ????
    SEG_PORT = 0xFF;
    BIT_PORT = 0x00;
}

// ??? - ?? Q018D-Q0193
void main(void) {
    // ?????
    system_init();
    
    // ???
    while(1) {
        // ???????
        update_display_buffer();
        
        // ????
        display_digits();
        
        // ??????
        timer_value++;
        if(timer_value > 9999) {
            timer_value = 0;
        }
    }
}