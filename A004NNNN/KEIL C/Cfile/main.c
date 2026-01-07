#include <reg51.h>
#include <intrins.h>  // ? _nop_() ????,??????

unsigned char status = 1;   // ??? (??? var09)
unsigned char counter = 0;  // ???? (??? var08)

void delay(unsigned char high, unsigned char low)
{
    unsigned char h = high;
    unsigned char l = low;
    volatile unsigned char i, k;  // volatile ??????????

    while (h || l)
    {
        if (l == 0)
        {
            if (h == 0) break;
            h--;
            l = 0xFF;
        }
        else
        {
            l--;
        }

        // ??????,??????(12MHz ???,???? 0.3~0.5s,??? 10~20s)
        // ????,?? k<10 ?? k<5;????,?? k<20
        for (k = 0; k < 10; k++)
        {
            i = 255;
            while (i--)
            {
                _nop_();  // ??????,??????
            }
        }
    }
}

void main(void)
{
    SP = 0x09;  // ??????

    status = 1;
    counter = 0;

    while (1)
    {
        switch (status)
        {
            case 1:  // ????(????????,??????)
                P0 = 0x33;               // ????????? 00110011
                delay(0xB8, 0x0B);        // ???
                status = 2;
                break;

            case 2:  // ???? 12 ?(??????)
                if (counter < 12)
                {
                    P0 ^= 0x02;          // ?? P0.1(????)
                    delay(0x2C, 0x01);   // ???(??????,?????)
                    counter++;
                    if (counter == 6)
                    {
                        P0 |= 0x04;      // ? SETB P0.2(??????)
                    }
                }
                else
                {
                    counter = 0;
                    status = 3;
                }
                break;

            case 3:  // ????(???????,?????)
                P0 = 0x3A;               // ????????? 00111010
                delay(0xD0, 0x07);       // ???
                status = 4;
                break;

            case 4:  // ?????? 12 ?(??????)
                if (counter < 12)
                {
                    P0 ^= 0x10;          // ?? P0.4(????)
                    delay(0x2C, 0x01);   // ???
                    counter++;
                    if (counter == 6)
                    {
                        P0 |= 0x20;      // ? SETB P0.5(??????)
                    }
                }
                else
                {
                    counter = 0;
                    status = 1;           // ????????
                }
                break;

            default:
                status = 1;
                break;
        }
    }
}