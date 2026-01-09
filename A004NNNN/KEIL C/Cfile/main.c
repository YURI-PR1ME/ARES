#include <reg51.h>

// ???????????????
// 08H ???????????
unsigned char data counter_var _at_ 0x08; 
// 09H ?????????? (State Machine)
unsigned char data state_var   _at_ 0x09; 

// ?? P0 ???,???? (?????LED)
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;

/**
 * ???? (?????? Q0090)
 * ??????? R6(??), R7(??)
 * ???? R5 = 0x78 (120)
 */
void Delay(unsigned int count) {
    unsigned char i;
    // ????:????
    while (count > 0) {
        count--;
        i = 120; // 0x78
        while (i > 0) {
            i--;
        }
    }
}

void main() {
    // ???? Q0003
    counter_var = 0;
    state_var = 1;

    while (1) {
        // ???? Q0009: ?????
        // ???????? 09H ?????
        
        switch (state_var) {
            
            // ==========================================
            // ?? 1 (???? Q0019)
            // ==========================================
            case 1:
                LED1 = 1; // SETB P0.0
                LED2 = 1; // SETB P0.1
                LED3 = 0; // CLR P0.2
                LED4 = 0; // CLR P0.3
                LED5 = 1; // SETB P0.4
                LED6 = 1; // SETB P0.5
                
                // R6=0B, R7=B8 -> 0x0BB8 = 3000
                Delay(3000); 
                
                state_var = 2; // ????? 2
                break;

            // ==========================================
            // ?? 2 (???? Q0031)
            // ==========================================
            case 2:
                // ????:????? >= 12 (0x0C),????
                while (counter_var < 12) {
                    LED2 = !LED2; // CPL P0.1 (??)
                    
                    // R6=01, R7=2C -> 0x012C = 300
                    Delay(300);   
                    
                    counter_var++; // INC 08H
                    
                    // ?? CJNE A,#06H, Q0031 (?????6??,??6???)
                    if (counter_var == 6) {
                        LED3 = 1; // SETB P0.2
                    }
                }
                
                // ???? 2 ??? (Q004C)
                counter_var = 0;
                state_var = 3;
                break;

            // ==========================================
            // ?? 3 (???? Q0054)
            // ==========================================
            case 3:
                LED1 = 0; // CLR P0.0
                LED2 = 1; // SETB P0.1
                LED3 = 1; // SETB P0.2
                LED4 = 1; // SETB P0.3
                LED5 = 1; // SETB P0.4
                LED6 = 0; // CLR P0.5
                
                // R6=07, R7=D0 -> 0x07D0 = 2000
                Delay(2000);
                
                state_var = 4;
                break;

            // ==========================================
            // ?? 4 (???? Q006C)
            // ==========================================
            case 4:
                // ????? 2 ????,????? LED ??
                while (counter_var < 12) {
                    LED5 = !LED5; // CPL P0.4
                    
                    // R6=01, R7=2C -> 0x012C = 300
                    Delay(300);
                    
                    counter_var++;
                    
                    if (counter_var == 6) {
                        LED6 = 1; // SETB P0.5
                    }
                }
                
                // ???? 4 ??? (Q0087)
                counter_var = 0;
                state_var = 1; // ???? 1,????
                break;
        }
    }
}