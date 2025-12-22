

#include "config.h" 


void int0(void) interrupt 0
{
	num++;
	if(num>255){num=0;}
}
