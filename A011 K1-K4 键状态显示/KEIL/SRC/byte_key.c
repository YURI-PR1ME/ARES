/*****************************************
byte_key.c:字节操作的键盘检测程序文件
uch8 byte_key():字节操作的键盘检测函数
*******************************************/

#include "config.h"

uch8 v_key;

uch8 byte_key()
{
	uch8 v0_key;	

	P1=0x0f;//0.给端口写1

	if((P1&0x0f)!=0x0f)//1、判断是否有键按下
	{
		delay1ms(15);//2、延时防抖

		if((P1&0x0f)!=0x0f)//3、再次判断有键按下
		{
			v0_key=P1&0x0f;	
			return(v0_key);//5、返回键值
//			while((P1&0x0f)!=0x0f);//4、判断按键释放			
//	 		return(v0_key);//5、返回键值
		}
		else
		{
			return(0x0f);
		}
	}
	else
	{
		return(0x0f);
	}		
}
