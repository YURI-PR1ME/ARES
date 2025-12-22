/**********************************************
sta_key.c:按键状态显示程序文件
void sta_key();按键状态显示函数

**********************************************/


#include "config.h"


void sta_key()
{
	if(v_key==0x0e){P0=0xfe;}//K1键按下，D1亮
	if(v_key==0x0d){P0=0xfd;}//K2键按下，D2亮
	if(v_key==0x0b){P0=0xfb;}//K3键按下，D3亮
	if(v_key==0x07){P0=0xf7;}//K4键按下，D4亮
	if(v_key==0x0f){P0=0xff;}//按键释放或者没有键按下，灯灭
}
