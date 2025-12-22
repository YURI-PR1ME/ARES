/****************************
plca014.c:Âß¼­¿ØÖÆ³ÌĞò
void plc(void):Âß¼­¿ØÖÆº¯Êı
*****************************/

#include "config.h"


uint16 num;//0-9999

void plc()
{
	if(v_key==0x0e)
	{
		num++;
		if(num>9999){num=0;}
	}

	if(v_key==0x0d)
	{
		if(num>0)
		{
			num--;
		}
		else
		{
			num=9999;
		}				
	}

	if(v_key==0x0b)
	{
		num=0;
	}

	dis_dat_smg8[3]=num/1000;
	dis_dat_smg8[2]=num/100%10;
	dis_dat_smg8[1]=num%100/10;
	dis_dat_smg8[0]=num%10;


}
