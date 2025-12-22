#ifndef _12864_H__
#define _12864_H__
sbit E=P1^2;  //使能端
sbit RW=P1^1;  //读写端 
sbit RS=P1^0;  //数据命令端口
sbit CS1=P1^3;
sbit CS2=P1^4;
/****检查液晶是否忙碌***/
void chekbusy12864(void)
 {
  uchar dat;
  RS=0;       //指令模式 
  RW=1;       //读数据
 do{
   P0=0x00;
   E=1;
   dat=P0&0x80;
   E=0;
  }while(dat!=0x00);
 }
 /****选屏****/
void choose12864(uchar i)//i是要写的屏.0是左屏,1是右屏,2是双屏
{
  switch (i)
  {
    case 0: CS1=0;CS2=1;break;
    case 1: CS1=1;CS2=0;break;
	case 2: CS1=0;CS2=0;break;
	default: break;
  }
}
/******写命令*****/
void cmd_w12864(uchar cmd)		//写命令
{
  chekbusy12864();
  RS=0;	            //指令模式
  RW=0;             //写模式
  E=1;
  P0=cmd;
  E=0;
}
/****写数据******/
void  dat_w12864(uchar dat)
{
  chekbusy12864();
  RS=1;
  RW=0;
  E=1;
  P0=dat;
  E=0;
}
/*****清屏*****/
void clear12864(void)
{
  uchar page,row;
  for(page=0xb8;page<0xc0;page++)
  {
    cmd_w12864(page);
	cmd_w12864(0x40);
	for(row=0;row<64;row++)
	 {
	   dat_w12864(0x00); 
	 }
  }
}
/***初始化****/
void init12864(void)
{
  chekbusy12864();
  cmd_w12864(0xc0);
  cmd_w12864(0x3f);
}
/**8X16字符的显示**/
void play8(uchar ch,uchar row,uchar page,uchar *adr)
{
  uchar i;
  choose12864(ch);
  page=page<<1;
  row=row*8;
  cmd_w12864(row+0x40);
  cmd_w12864(page+0xb8);
  for(i=0;i<8;i++)
  {
    dat_w12864(*(adr+i));
  }
  cmd_w12864(row+0x40);
  cmd_w12864(page+0xb9);
  for(i=8;i<16;i++)
  {
    dat_w12864(*(adr+i));
  }
}
/**16X16显示**/
play16(uchar ch,uchar row,uchar page,uchar *adr)
{
  uchar i;
  choose12864(ch);
  page=page<<1;					   
  row=row*8;
  cmd_w12864(row+0x40);
  cmd_w12864(page+0xb8);
  for(i=0;i<16;i++)
  {
    dat_w12864(*(adr+i));
  }
  cmd_w12864(row+0x40);
  cmd_w12864(page+0xb9);
  for(i=16;i<32;i++)
  {
    dat_w12864(*(adr+i));
  }
}
/*****读数据*****/
uchar dat_r12864(uchar page,uchar arrange)  //page页地址.arrange列地址)
{
  uchar dat;
  chekbusy12864();
  cmd_w12864(page+0xb8);
  cmd_w12864(arrange+0x40);
  P0=0xff;
  RW=1;
  RS=1;
  E=1;
  E=0;
  E=1;
  dat=P0;
  E=0;
  return(dat);
}
clear8(uchar x,uchar y,uchar ch)
{
  uchar i;
  choose12864(ch);
  cmd_w12864(x*8+0x40);
  cmd_w12864(y+0xb8);
  for(i=0;i<8;i++)
   {
     dat_w12864(0x00);
   }
   cmd_w12864(x*8+0x40);
   cmd_w12864(y+0xb9);
  for(i=0;i<16;i++)
   {
      dat_w12864(0x00);
   }
}
/**竖线**/
void vertical(uchar y1,uchar y2,uchar x)//y0表示起点,y1表示终点
{
  uchar i,sum=0;
  choose12864(1);
  if((y1/8)!=(y2/8))
  {
   for(i=0;i<(8-y1%8);i++)
   {
      sum=sum|((2<<((y1%8)+i)));
   }
  cmd_w12864(x+0x40);
  cmd_w12864(y1/8+0xb8);
  dat_w12864(sum);
  sum=0;
   for(i=0;i<(y2/8-y1/8-1);i++)
    {
     cmd_w12864(x+0x40);
	 cmd_w12864((y1/8)+0xb9+i);
	 dat_w12864(0xff);
    }
  for(i=0;i<=(y2%8);i++)
   {
     sum=sum|(2<<i);
   }
   cmd_w12864(x+0x40);
   cmd_w12864(y2/8+0xb8);
   dat_w12864(sum|1);
   sum=0;	
 }
 else
 {
   for(i=0;i<=y2-y1;i++)
    {
	  sum=sum|(2<<(i+(y1%8)));
	}
	cmd_w12864(0x40+x);
	cmd_w12864(0xb8+(y1/8));
	dat_w12864(sum);
 } 
}		 
/**点的显示**/
void dot(uchar x,uchar y)//所有的图形都在右屏上。
{
  uchar dat;
  choose12864(1);
  dat=dat_r12864(y/8,x);
  cmd_w12864(0x40+x);
  cmd_w12864(0xb8+y/8);
  dat_w12864((1<<(y%8))|dat);
}
/**温度对图形的转换**/
void change(void)
{
  static uchar n=63;
  uchar i,m,sum=0;
  m=temp[0]*10+temp[1]+(temp[2]+5)/10;
  if(m<60)
  {
   m=62-m;
   if(m<n)
   {
    vertical(m,63,60);
    }
   if(m>n)
   {
    if((m/8)>(n/8))
	{
	  cmd_w12864(n/8+0xb8);
	  cmd_w12864(0x40+60);
	  dat_w12864(0x00);
   	}
	for(i=0;i<(8-m%8);i++)
	   {
	   	 sum=sum+(2<<((m%8)+i));
	   }
	 cmd_w12864(m/8+0xb8);
	 cmd_w12864(0x40+60);
	 dat_w12864(sum);
	 n=m;
  }
  dot(60,3);
 }		   
}
#endif