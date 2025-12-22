


#include "config.h"


void sound(uch8 t,uch8 f)
{
	uch8 i;
	for(i=0;i<t;i++)
	{
	 	beep = ~beep;
		delay1ms(f);
	}
//	beep = 0;
}
