/**************************************************
ex_int.c:外部中断程序文件
void init_ex_int0(void):外部中断0的初始化函数
void init_ex_int1(void):外部中断1的初始化函数
void ex_int0() interrupt 0:外部中断0中断函数
void ex_int1() interrupt 2:外部中断1中断函数
***************************************************/

#include "config.h"

void init_ex_int0(void)
{
	EA=1;//1、开中断总开关
	EX0=1;//2、开使用中断分开关
	IT0=1;//3、设置外部中断信号的触发方式;1下降沿，0低电平
}

void init_ex_int1(void)
{
	EA=1;//1、开中断总开关
	EX1=1;//2、开使用中断分开关
	IT1=1;//3、设置外部中断信号的触发方式;1下降沿，0低电平
}

void ex_int0() interrupt 0
{
	led=~led;	
}

void ex_int1() interrupt 2
{
	lamp=~lamp;	
}
