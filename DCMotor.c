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

int left;
int right;
int speedLev;

void Sys_Init()
{
	TMOD = 0x10;			//定时器1做为8位计数器
	IE = 0x88;

	TH1 = 0xfc;
	TL1 = 0x66;
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
	speedLev = 0;

	//P3 = 0xff;
}

void CtrlSpeed()				//中间对称地分离P3口的数据，控制两侧电机
{
	led0 = sensor0;
	led1 = sensor1;
	led2 = sensor2;
	led3 = sensor3;
	led4 = sensor4;
	led5 = sensor5;
	led6 = sensor6;
	led7 = sensor7;

	right = 1;
	left = 1;

	if(sensor0 == 1 && sensor7 == 0)
	{
		//led0 = 0;			 //亮
		//led1 = 1;		  	 //不亮
		right = 1;
		left = 0;
	}
	if(sensor0 == 0 && sensor7 == 1)
	{
		//led0 = 1;			 //不亮
		//led1 = 0;			 //亮
		right = 0;
		left = 1;
	}

	if(sensor1 == 1 && sensor6 == 0)
	{
		right = 1;
		left = 0;
	}
	if(sensor1 == 0 && sensor6 == 1)
	{
		right = 0;
		left = 1;
	}

	if(sensor2 == 1 && sensor5 == 0)
	{
		right = 1;
		left = 0;
	}
	if(sensor2 == 0 && sensor5 == 1)
	{
		right = 0;
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
	TH1 = 0xfc;
	TL1 = 0x66;

	count++;
	if(count >= cycleN)
	{
		count = 0;
	}

	if(count >= 0 && count < pwmN)
	{
		/*leftPwm1 = 1;
		leftPwm2 = 0;
		rightPwm1 = 1;
		rightPwm2 = 0;*/

		if (left == 1 && right == 0)
		{
			leftPwm1 = 1;
			//leftPwm2 = 0;
			rightPwm1 = 0;
			//rightPwm2 = 0;
		}
		if (left == 0 && right == 1)
		{
			leftPwm1 = 0;
			//leftPwm2 = 0;
			rightPwm1 = 1;
			//rightPwm2 = 0;
		}
		if ( (left == 0 && right == 0) || (left == 1 && right == 1) )
		{
			leftPwm1 = 1;
			rightPwm1 = 1;
		}
	}
	else
	{
		leftPwm1 = 0;
		//leftPwm2 = 0;
		rightPwm1 = 0;
		//rightPwm2 = 0;
	}
}
