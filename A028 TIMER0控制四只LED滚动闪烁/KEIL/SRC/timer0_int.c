/****************************************
timer0_int.c:定时器0的中断程序
函数：
void init_timer0_int(void):定时器0的初始化函数
void timer0_int(void) interrupt 1:中断处理函数
****************************************/

#include "config.h"
#include "intrins.h"



//0.2ms定时器,累加计数200次
void init_timer0_int()
{
	TMOD=0x02;//1、定时器0的工作方式设置10：工作方式2，8位自动重装
	TH0=(256-200);//2、初值设置0.2ms,定时（256-200）(12M晶振，TCY=1US)
	TL0=(256-200);//定时（256-X）
	EA=1;//3、开中断
	ET0=1;//开定时器0中断
	TR0=1;//4、触发启动
}


void timer0_int() interrupt 1
{
	if(++i<35) return;//中断次数进行计数，35次
	i=0;
	switch(j)
	{
		case 0:led1=~led1;
			break;
		case 1:led2=~led2;
			break;
		case 2:led3=~led3;
			break;
		case 3:led4=~led4;
	}
	if(++k<200) return;	
	k=0;
	P0=0xff;//关闭LED
	j++;
	if(j>3) j=0;
}
