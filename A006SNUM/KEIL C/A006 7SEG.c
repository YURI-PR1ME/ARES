/************************************************************************************************
*************************************************************************************************/


//调用头文件
#include "reg52.h"
#include "intrins.h"

//数据类型的宏定义
#define uch8 unsigned char
#define uint16 unsigned int


//IO端口配置


//函数声明
void delay(uint16 a);


//变量定义
uch8 code data_dis[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};



//主程序
main()
{
 	uch8 i,k=0x01;
	//初始化


	//循环执行程序     
	 while(1)
	 {
		k=0x01;
	 	for(i=0;i<8;i++)
		{
		 	P2=0x00;
			P0=data_dis[i];
			P2=k;
			delay(200);
			k=_crol_(k,1);
		}

	 }

}


//延时函数
void delay(uint16 a)
{
	uch8 b;
	while(a--)
	{
		for(b=120;b>0;b--);
	}

}







