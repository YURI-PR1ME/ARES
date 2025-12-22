/************************************************************************************************** 
input.c:开关量输入程序如单个按键，按钮、接近开关等
***************************************************************************************************/


#include "config.h"


bit  key_set_tab,key_add,key_sub,key_enter;
bit  I0,I1,I2,I3;

 

//加键
bit input_k0()
{
	bit a=0;
	k0=1;
	if(k0==0)
	{
		delay1ms(1);
		if(k0==0)
		{
			while(!k0){display(discode);}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}

//加键
bit input_k1()
{
	bit a=0;
	k1=1;
	if(k1==0)
	{
		delay1ms(1);
		if(k1==0)
		{
			while(!k1){display(discode);}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}

//减键
bit input_k2()
{
	bit a=0;
	k2=1;
	if(k2==0)
	{
		delay1ms(1);
		if(k2==0)
		{

			
			while(!k2)
			{
				display(discode);
			}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}

//回车键
bit input_k3()
{
	bit a=0;
	k3=1;
	if(k3==0)
	{
		delay1ms(1);
		if(k3==0)
		{
			while(!k3){display(discode);}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}

//自动接近开关
bit input_in0()
{
	bit a=0;
	in0=1;
	if(in0==0)
	{
		delay1ms(10);
		if(in0==0)
		{
			//while(!in0){display(discode);}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}

//送料到位接近开关
bit input_in1()
{
	bit a=0;
	in1=1;
	if(in1==0)
	{
		delay1ms(10);
		if(in1==0)
		{
			//while(!in1){display(discode);}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}

//送料退到位接近开关
bit input_in2()
{
	bit a=0;
	in2=1;
	if(in2==0)
	{
		delay1ms(10);
		if(in2==0)
		{
			//while(!in2){display(discode);}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}

//手动开关
bit input_in3()
{
	bit a=0;
	in3=1;
	if(in3==0)
	{
		delay1ms(10);
		if(in3==0)
		{
			while(!in3){display(discode);}
			a=1;
			return(a);
		}
		else
		{
			a=0;
			return(a);
		}
	}
	else
	{
		a=0;
		return(a);
	}
}
void input_all()
{
	key_set_tab=input_k0();
	key_add=input_k1();
	key_sub=input_k2();
	key_enter=input_k3();
	I0=input_in0();
	I1=input_in1();
	I2=input_in2();
	I3=input_in3();
}
