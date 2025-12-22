

#include "config.h"
#include "intrins.h"

uch8 code dis_code[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff
};
uch8 dis_init[]=
{
 	0,10,10,10,10,10,10,10
};
uch8 dis_dat[8];
uch8 en_smg;

void display_smg()
{
	uch8 i;

	en_smg=0x80;
	for(i=0;i<8;i++)
	{
		P2=0X00;
		P0=dis_code[dis_dat[i]];
		P2=en_smg;
		delay1ms(5);
		en_smg=_cror_(en_smg,1);
	}

}
