/***************************************
ex_int0.c:外部中断0的中断处理程序
ex_int0() interrupt 0 using 0:中断处理函数
init_ex_int0():int0外部中断初始化。
ex_int1() interrupt 2 using 0:中断处理函数
init_ex_int1():int1外部中断初始化。
****************************************/


#include "config.h"

void init_ex_int0()
{
	EA=1;//中断总开关
	EX0=1;//外部中断0开关
	
    IT0=1;//使用中断的初始化,1下降沿触发，0是低电平触发
}
void init_ex_int1()
{
	EA=1;//中断总开关
	EX1=1;//外部中断0开关
	
    IT1=1;//使用中断的初始化,1下降沿触发，0是低电平触发
}

void ex_int0() interrupt 0 using 0//外部中断0处理程序
{
	led=~led;//LED灯控制输出翻转
}
void ex_int1() interrupt 2 using 0//外部中断0处理程序
{
	lamp=~lamp;//照明灯控制输出翻转
}  
