#include <reg51.h>

#define uchar unsigned char  
#define uint  unsigned int  

uint cycleN;
uint pwmN;
uint count;
sbit leftPwm1 = P0^0;          	//PWM信号输出
sbit leftPwm2 = P0^1;
sbit rightPwm1 = P0^2;
sbit rightPwm2 = P0^3;

sbit led0 = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led3 = P1^3;
sbit led4 = P1^4;
sbit led5 = P1^5;
sbit led6 = P1^6;
sbit led7 = P1^7;
sbit sensor0 = P3^0;
sbit sensor1 = P3^1;
sbit sensor2 = P3^2;
sbit sensor3 = P3^3;
sbit sensor4 = P3^4;
sbit sensor5 = P3^5;
sbit sensor6 = P3^6;
sbit sensor7 = P3^7;

uint left;
uint right;

void Sys_Init()
{
	TMOD = 0x10;			//定时器1做为16位计数器，工作在方式1
	IE = 0x88;

	TH1 = 0xf8;
	TL1 = 0xcd;		  		//2000us
	TR1 = 1;	
}

void Var_Init()
{	
	cycleN = 8;
	pwmN = 8;
	count = 0;

	leftPwm1 = 1;
	leftPwm2 = 0;
	rightPwm1 = 1;
	rightPwm2 = 0;

	left = 1;
	right = 1;
}

void CtrlSpeed()				//中间对称地分离P3口的数据，控制两侧电机
{	
	if((sensor0 == 1 && sensor7 == 0) || (sensor1 == 1 && sensor6 == 0) || (sensor2 == 1 && sensor5 == 0))
	{
		left = 0;
		right = 1;
	}
	else if((sensor0 == 0 && sensor7 == 1) || (sensor1 == 0 && sensor6 == 1) || (sensor2 == 0 && sensor5 == 1))
	{
		left = 1;
		right = 0;
	}
	else
	{
		right = 1;
		left = 1;
	}
}

main()
{
	Sys_Init();
	Var_Init();

 	while(1)
	{
		CtrlSpeed();
	}
}

void Timer1_Int() interrupt 3 	//中断程序
{
	TH1 = 0xf8;
	TL1 = 0xcd;

	count++;
	if(count >= cycleN)
	{
		count = 0;
	}

	if(count >= 0 && count < pwmN)
	{
		leftPwm1 = left;
		rightPwm1 = right;
	}
	else
	{
		leftPwm1 = 0;
		rightPwm1 = 0;
	}
}
