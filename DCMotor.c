#include <reg51.h>

#define uchar unsigned char  
#define uint  unsigned int  

uint cycleN;
uint pwmN;
uint count;
sbit leftPwm1 = P0^0;          	//PWM�ź����
sbit leftPwm2 = P0^1;
sbit rightPwm1 = P0^2;
sbit rightPwm2 = P0^3;
uint LeftData[4];
uint RightData[4];
bit left;
bit right;
uint speedLev;

void Sys_Init()
{
	TMOD = 0x10;			//��ʱ��1��Ϊ8λ������
	IE = 0x88;

	TH1 = 0xfc;
	TL1 = 0x66;
	TR1 = 1;

	P3 = 0xff;
}

void Var_Init()
{	
	cycleN = 6;
	pwmN = 3;
	count = 0;

	leftPwm1 = 1;
	leftPwm2 = 0;
	rightPwm1 = 1;
	rightPwm2 = 0;

	left = true;
	right = true;
	speedLev = 0;
}

void CtrlSpeed()				//�м�ԳƵط���P3�ڵ����ݣ�����������
{
	uint i;
	LeftData[0] = P3^0;
	LeftData[1] = P3^1;
	LeftData[2] = P3^2;
	LeftData[3] = P3^3;
	RightData[0] = P3^7;
	RightData[1] = P3^6;
	RightData[2] = P3^5;
	RightData[3] = P3^4;

	for(i = 0;i < 4;i++)
	{
		if(LeftData[i] > RightData[i])
		{
			speedLev = speedLev + (4 - i);
		}
		if (LeftData[i] < RightData[i])
		{
			speedLev = speedLev - (4 - i);
		}
	}

	if (speedLev > 0)		//��ഫ������⵽���ߣ��Ҳ�����							
	{
		left = false;
		right = true;	
	}
	if (speedLev < 0)		//�Ҳഫ������⵽���ߣ��������
	{
		left = true;
		right = false;
	}
	if (speedLev == 0)
	{
		left = true;
		right = true;
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

void Timer1_Int() interrupt 3 	//�жϳ���
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
		if (left == true && right == false)
		{
			leftPwm1 = 1;
			leftPwm2 = 0;
			rightPwm1 = 0;
			rightPwm2 = 0;
		}
		if (left == false && right == true)
		{
			leftPwm1 = 0;
			leftPwm2 = 0;
			rightPwm1 = 1;
			rightPwm2 = 0;
		}
		else
		{
			leftPwm1 = 1;
			leftPwm2 = 0;
			rightPwm1 = 1;
			rightPwm2 = 0;
		}
	}
	else
	{
		leftPwm1 = 0;
		leftPwm2 = 0;
		rightPwm1 = 0;
		rightPwm2 = 0;
	}
}
