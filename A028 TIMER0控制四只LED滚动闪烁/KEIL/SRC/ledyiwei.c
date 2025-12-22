/********************************************
ledyiwei.c:通过按键K1KK3K4控制LED移位点亮
void ledyiwei();通过按键K1KK3K4控制LED移位点亮
*********************************************/

#include "config.h"
#include "intrins.h"

uch8 led8_red,led8_gre;

void ledyiwei()
{
	if(key1==1)//k1控制红色LED向下移位点亮
	{
		led8_red=_crol_(led8_red,1);//移位
		P0=led8_red;                //输出控制码点亮
	}

	if(key2==1)//K2控制红色LED向上移位点亮
	{
		led8_red=_cror_(led8_red,1);
		P0=led8_red;
	}

	if(key3==1)//K3控制绿色LED向下移位点亮
	{
		led8_gre=_crol_(led8_gre,1);
		P2=led8_gre;
	}

	if(key4==1)//K4控制绿色LED向上移位点亮
	{
		led8_gre=_cror_(led8_gre,1);
		P2=led8_gre;
	}

}
