/******************************************
**display_smg8.c:8位数码管的显示程序文件
**void display_smg8(void)
**功能：8位数码管的显示
**IO:段码输出P0，位选口P2
**输入参数：显示内容uch8 dis_dat_smg8[8]，全局变量;
**输出参数：无。
**其他说明：
*******************************************/

#include "config.h"
#include "intrins.h"

uch8 code dis_code[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff
};  //0    1    2    3    4    5   6     7    8    9   (10)     

uch8 en_smg;
uch8 dis_dat_smg8[]=
{
	0,10,10,10,10,10,10,10
};
uch8 num;
void display_smg8()
{
	uch8 i;
	
	en_smg=0x80;
	for(i=0;i<8;i++)//8位数码管动态扫描显示
	{	
		P2=0x00;//1、关位选
		P0=dis_code[dis_dat_smg8[i]];//2、输出字形码
		P2=en_smg;//3、开位选
		delay1ms(5);//4、延时
		en_smg=_cror_(en_smg,1);//5、获取下一个位选
	}
}



