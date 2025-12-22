/************************************************************************************************** 
24c02.c:存储器初始化读写程序
***************************************************************************************************/

#include "config.h"



void delay_2()
{ ; ; }

void start()//iic开始信号
{
	sda=1;	
	delay_2();
	scl=1;
	delay_2();
	sda=0;
	delay_2();
}
void stop()//IIc停止信号
{
	sda=0;
	delay_2();
	scl=1;
	delay_2();
	sda=1;
	delay_2();
}
void respons()  //iic应答信号
{
	uch8 i;
	scl=1;
	delay_2();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay_2();
}
void  ic_init()//iic初始化
{
 	scl=1;
 	delay_2();
	sda=1;
	delay_2();
}
void write_byte(uch8 date)//向iic写单个数据
{
	uch8 i,temp;
	temp=date;


	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		scl=0;
	    delay_2();
		sda=CY;
		delay_2();
		scl=1;
		delay_2();
	//	scl=0;
     //   delay();
	}
	scl=0;
	delay_2();
	sda=1;
	delay_2();
}
uch8 read_byte()//从iic读单个数据
{
	uch8 i,k;
	scl=0;
	delay_2();
	sda=1;
	delay_2();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay_2();	
		k=(k<<1)|sda;
		scl=0;
		delay_2();	
	}
	return k;
}
void write_add(uch8 address,uch8 date)//向iic固定地址写数据
{
	start();
	write_byte(0xa0);
	respons();       
	write_byte(address);
	respons();
	write_byte(date);
	respons();
	stop();
}
uch8 read_add(uch8 addr)//从iic固定地址读数据
{
	uch8 date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(addr);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	stop();
	return date;
}
