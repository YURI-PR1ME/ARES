/************************************************************************************************** 
display.c:系统数码管显示程序

***************************************************************************************************/


#include "reg52.h"
#include "config.h"
//#include "intrins.h"


//共阳极数码管显示字形码
uch8 segcode[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//共阳极显示码
uch8 discode[4];



void display()
{
    P0=segcode[discode[0]];          //输出字形码到P0
    w1=1;         //开位选
    delay1ms(1);         //延时
    w1=0;         //关位选

	P0=segcode[discode[1]];
	w2=1;
    delay1ms(1);
    w2=0;

	P0=segcode[discode[2]];
	w3=1;
    delay1ms(1);
    w3=0;

	P0=segcode[discode[3]];
	w4=1;
    delay1ms(1);
    w4=0;    
}
