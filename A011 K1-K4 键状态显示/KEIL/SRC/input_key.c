/*************************************************
**input_key.c:属于独立按键输入检测程序文件
**bit input_k1(),检测K1按键的程序
**bit input_k2(),检测K2按键的程序
**bit input_k3(),检测K3按键的程序
**bit input_k4(),检测K4按键的程序
**************************************************/

#include "config.h"

bit key1,key2,key3,key4;//k1-k4键值

bit input_k1()
{
		
	k1=1;//0、要先给端口写1
	if(k1==0)//1、判断按键按下
	{ 
		delay1ms(15);//2、延时消除抖动
	    if(k1==0)//3、再次判断这个按键是否按下
		{
			while(!k1);//4、检测按键释放
            return(1);//5、返回键值
		}
		else
		{
			return(0);
		}
	}
	else
	{
		return(0);
	}
}

bit input_k2()
{
		
	k2=1;//0、要先给端口写1
	if(k2==0)//1、判断按键按下
	{ 
		delay1ms(15);//2、延时消除抖动
	    if(k2==0)//3、再次判断这个按键是否按下
		{
			while(!k2);//4、检测按键释放
            return(1);//5、返回键值
		}
		else
		{
			return(0);
		}
	}
	else
	{
		return(0);
	}
}

bit input_k3()
{
		
	k3=1;//0、要先给端口写1
	if(k3==0)//1、判断按键按下
	{ 
		delay1ms(15);//2、延时消除抖动
	    if(k3==0)//3、再次判断这个按键是否按下
		{
			while(!k3);//4、检测按键释放
            return(1);//5、返回键值
		}
		else
		{
			return(0);
		}
	}
	else
	{
		return(0);
	}
}

bit input_k4()
{
		
	k4=1;//0、要先给端口写1
	if(k4==0)//1、判断按键按下
	{ 
		delay1ms(15);//2、延时消除抖动
	    if(k4==0)//3、再次判断这个按键是否按下
		{
			while(!k4);//4、检测按键释放
            return(1);//5、返回键值
		}
		else
		{
			return(0);
		}
	}
	else
	{
		return(0);
	}
}
