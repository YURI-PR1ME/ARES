/****************************
plca013.c:逻辑控制程序
void plc(void):逻辑控制函数
*****************************/

#include "config.h"

uch8 NO;//数码管号码0-7
uch8 i;

void plc()
{

	if(v_key==0x0e)//增位显示
	{
		NO++;//增位
		if(NO>7){NO=7;}
		dis_dat_smg8[NO]=NO;//显示
	}
	if(v_key==0x0d)//减位显示
	{
		if(NO>0)
		{
			dis_dat_smg8[NO]=10;//不显示	
			NO--;//减位
		}
	}
	if(v_key==0x0b)
	{
		NO=0;
		dis_dat_smg8[0]=0;
		for(i=1;i<8;i++)
			dis_dat_smg8[i]=10;
	}
/*
	if(v_key==0x07)
	{
		dis_dat_smg8[4]=4;
	}
*/
}
