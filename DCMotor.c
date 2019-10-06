#include <reg51.h>

#define uchar unsigned char  
#define uint  unsigned int  

uint highN1;
uint lowN1;
uint highN2;
uint lowN2;
uint cycleN;
uint count;
sbit pwm1 = P0^0;          	//PWM信号输出
sbit pwm2 = P0^1;
sbit pwm3 = P0^2;
sbit pwm4 = P0^3;

void Sys_Init()
{
	TMOD = 0x10;			//定时器1做为8位计数器
	IE = 0x88;

	TH1 = 0xFC;
	TL1 = 0x66;
	TR1 = 1;
}

void Var_Init()
{	
	highN1 = 0;
	lowN1 = 200;
	highN2 = 250;
	lowN2 = 450;
	cycleN = 6;
	count = 0;

	pwm1 = 1;
	pwm2 = 0;
}

main()
{
	Sys_Init();
	Var_Init();

 	while(1)
	{
		/*pwm1 = 1;
		pwm2 = 0;*/
	}
}

void Timer1_Int() interrupt 3 	//中断程序
{
	TH1 = 0xFC;
	TL1 = 0x66;

	count++;
	if(count >= cycleN)
	{
		count = 0;
	}
	/*if(count >= highN1 && count < lowN1)
	{
		pwm1 = 1;
		pwm2 = 0;
	}
	if((count >= lowN1 && count < highN2) || (count >= lowN2 && count < cycleN))
	{
		pwm1 = 0;
		pwm2 = 0;
	}
	if(count >= highN2 && count < lowN2)
	{
		pwm1 = 0;
		pwm2 = 1;
	}*/
	if(count >= 0 && count < 3)
	{
		pwm1 = 1;
		pwm2 = 0;
		pwm3 = 0;
		pwm4 = 0;
	}
	else
	{
		pwm1 = 0;
		pwm2 = 0;
		pwm3 = 1;
		pwm4 = 0;
	}
}
