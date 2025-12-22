/********************************************************************************************
*********************************************************************************************/

//加载头文件
#include "reg52.h"
#include "intrins.h"




//宏定义
#define uint8 unsigned int
#define uch8 unsigned char


//单片IO口配置
sbit led=P1^0;

//函数声明
void delay(uint8 a);


void main()
{
	uch8 i;
    P2=0x01;//0000 0001
	while(1)
	{
		for(i=7;i>0;i--)//0000 0010，1000 0000
		{
			delay(150);
			P2=_crol_(P2,1);
		}
        for(i=7;i>0;i--)
		{
			delay(150);
			P2=_cror_(P2,1);
		}

	}
}

void delay(uint8 a)
{
	uint8 b;
	while(a--)
	{
		for(b=120;b>0;b--);
	}
}
