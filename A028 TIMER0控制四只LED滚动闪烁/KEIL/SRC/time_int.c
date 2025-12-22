#include "config.h"

uch8 i;	

void init_time0_int()
{
	TMOD = 0x01;
	TH0  = (65536-50000)/256;//50MS
	TL0  = (65536-50000)%256;
	EA=1;//IE   = 0x82;
	ET0=1;
	TR0  = 1;
} 

void time0_int() interrupt 1 
{
	

	TH0  = (65536-50000)/256;
	TL0  = (65536-50000)%256;
	i++;	
	if(i==10)//50ms*10=0.5s
	{led=~led;i=0;}
}
