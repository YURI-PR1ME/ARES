#include <reg51.h>
#include <intrins.h>

// ?????
sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;

// ???? - ??????08H?09H
unsigned char data counter08;  // ??08H
unsigned char data state09;    // ??09H

// ???? - ??????Q0090
void delay(unsigned int r7, unsigned int r6) {
    while (r7 != 0 || r6 != 0) {
        unsigned char r5 = 0x78;
        
        // ??????
        do {
            // ?????
        } while (--r5 != 0);
        
        // ??r7?r6???
        if (r7 != 0) {
            r7--;
            if (r7 == 0 && r6 != 0) {
                r6--;
            }
        }
    }
}

// ??1???? - ????Q0031
void state1(void) {
    while (1) {
        if (counter08 < 12) {  // 0x0C = 12
            P0_1 = ~P0_1;  // ??P0.1
            
            delay(0x2C, 0x01);  // ??
            
            counter08++;
            
            if (counter08 == 6) {
                P0_2 = 1;  // ??P0.2
            }
        } else {
            counter08 = 0;
            state09 = 3;  // ?????3
            return;
        }
    }
}

// ??2???? - ????0019-002F
void state2(void) {
    P0_0 = 1;
    P0_1 = 1;
    P0_2 = 0;
    P0_3 = 0;
    P0_4 = 1;
    P0_5 = 1;
    
    delay(0xB8, 0x0B);  // ??
    
    state09 = 2;  // ?????2
}

// ??3???? - ????Q0054
void state3(void) {
    P0_0 = 0;
    P0_1 = 1;
    P0_2 = 1;
    P0_3 = 1;
    P0_4 = 1;
    P0_5 = 0;
    
    delay(0xD0, 0x07);  // ??
    
    state09 = 4;  // ?????4
}

// ??4???? - ????Q006C
void state4(void) {
    while (1) {
        if (counter08 < 12) {  // 0x0C = 12
            P0_4 = ~P0_4;  // ??P0.4
            
            delay(0x2C, 0x01);  // ??
            
            counter08++;
            
            if (counter08 == 6) {
                P0_5 = 1;  // ??P0.5
            }
        } else {
            counter08 = 0;
            state09 = 1;  // ?????1
            return;
        }
    }
}

// ?????? - ????Q0009
void main_loop(void) {
    while (1) {
        switch (state09) {
            case 1:
                state2();  // ??:???state09=1?????state2()???
                break;
                
            case 2:
                state1();
                break;
                
            case 3:
                state3();
                break;
                
            case 4:
                state4();
                break;
                
            default:
                // ???????
                break;
        }
    }
}

// ????? - ????Q00A6?Q0003
void init(void) {
    unsigned char i;
    unsigned char *ptr;
    
    // ?????? 00H-7FH
    ptr = (unsigned char *)0x00;
    for (i = 0; i < 0x7F; i++) {
        *ptr++ = 0;
    }
    
    // ??????
    SP = 0x09;
    
    // ?????
    counter08 = 0;
    state09 = 1;  // ?????1
}

// ???
void main(void) {
    init();          // ???
    main_loop();     // ?????
}