/************************************************************************************************** 
PLC.c:系统控制流程程序：设置操作和动作控制
***************************************************************************************************/


#include "config.h"

bit mode,cyc_work,Q1_1,Q1_0;//模式标志，工作循环中标志，送切料进标志，退标志
uch8 n=0,m=0;
uch8 delay_time[8];//定时器延时值
uint16 num_work;//计件


void plc(void)
{
//工作模式判断
	if((key_set_tab==1)&(mode==0))//在工作模式下长按确定键进入设置模式，在设置模式下长按确定键退出设置模式回到工作模式
	{
		mode=1;
		key_set_tab=0;
	}

//设置模式
	if(mode==1)
	{
		if(key_set_tab==1)
		{
			n++;
			if(n>7){n=0;}
		}
	
		if(key_enter==1)//
		{
			mode=0;
			for(m=0;m<8;m++)
			{
				write_add(m,delay_time[m]);
				delay1ms(1);
			}
			key_enter=0;
		}

        if(key_add==1)
		{
			delay_time[n]++;
			if(delay_time[n]>99)
			{
				delay_time[n]=1;
			}
			key_add=0;
		}
        if(key_sub==1)
	 	{
			delay_time[n]--;
			if(delay_time[n]<1)
			{
				delay_time[n]=99;
			}
			key_sub=0;
		}


		discode[0]=segcode[10];//将显示参数赋值给显示参量
		discode[1]=segcode[n+1]&0x7f;
		discode[2]=segcode[delay_time[n]/10];
		discode[3]=segcode[delay_time[n]%10];
	}

//工作模式
	if(mode==0)
	{
		if(((I0==1)|(I3==1))&(cyc_work==0))//工作周期触发，并计件
		{
			num_work++;
			if(num_work>9999){num_work=0;}
			cyc_work=1;
			T00_K=1;
		}
		if(cyc_work==1)//延时开始工作
		{
			
			if(T00_B==1)//送切料气缸开始送料，同时送料台上升。
			{
				Q0=0;
				Q1=0;
				Q1_0=1;
	
				T00_B=0;//定时器T00复位

		
				T01_K=1;//启动T01定时器
			}
		
		
			if(T01_B==1)//送切料气缸送料到1/4，送原料
			{
				Q2=0;
	
				T01_B=0;//定时器T01复位

			}	
	
			if((I1==1)&(Q1_0==1))//送切料气缸送料到位碰到行程开关2，压料失电
			{
		
				Q3=1;
				Q1_0=0;
	
				T02_K=1;//启动T02定时器
			}	
		
			
			if(T02_B==1)//送切料气缸与送原料同时退
			{
				Q1=1;
				Q2=1;
	
				Q1_1=1;//送料退标志
	
				T02_B=0;//定时器T02复位

		
				T03_K=1;//启动T03定时器					
			}
	
			if((T03_B==1)&(I1==0))//送切料气缸退到1/4，下降
			{
				Q0=1;
	
				T03_B=0;//定时器T03复位
			}
	
	
			if((I2==1)&(Q1_1==1))//送切料气缸退到位，压料气缸动作，延迟一定时间，
			{
				Q3=0;
				Q1_1=0;//清除送料退标志
		
				T04_K=1;//启动T04定时器	
			}

			if(T04_B==1)//切料气缸动作
			{
				Q4=0;
	
				T04_B=0;//定时器T04复位

				T05_K=1;//启动T05定时器	
			}
		
			if(T05_B==1)//切料气缸动作
			{
				Q4=1;
	
				T05_B=0;//定时器T05复位
		
				cyc_work=0;//清除循环标志位
			}
		}		
		

		discode[0]=segcode[num_work/1000];//获得计件显示码
		discode[1]=segcode[num_work%1000/100];
		discode[2]=segcode[num_work%100/10];
		discode[3]=segcode[num_work%10];
	}
}
