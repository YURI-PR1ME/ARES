#ifndef _KEY_H__
#define _KDY_H__
#define dataport P2
uchar sum;
uchar scan(uchar k)
{
  uchar re;
  switch (k)
  {
    case 1:re=0;break;
	case 2:re=1;break;
	case 4:re=2;break;
	default:break;
  }
  return re;
}
void keyscan(void)
{
  uchar m,n;
  dataport=0x07;
  delay11us(1);
  if(dataport!=0x07)
  {
    dataport=0x07;
	delay1ms(5);
	m=dataport&0x07;
	if(m!=0x07)
	{
	  m=m^0x07;
	  m=scan(m);
	  dataport=0x70;
	  delay11us(1);
	  n=dataport&0x70;
	  if(n!=0x70)
	  {
	    n=n>>4;
		n=n^0x07;
		n=scan(n);
		sum=3*m+n;
	  }
	}
	dataport=0x07;
	while(dataport!=0x07);
  }
}
