#include <reg51.h>

void delayms(unsigned char ms)	
{						
	unsigned char i;
	while(ms--)
	{
		for(i = 0; i < 120; i++);
	}
}

main()
{
	unsigned char LED;
	LED = 0xfe;	  //0xfe = 1111 1110
 	while(1)
	{
	      
    	 P1 = LED;
		 delayms(250);
		 LED = LED << 1;    //ѭ������1λ��������һ��LED "<<"Ϊ����λ
		 if(LED == 0x00 )	 
		 { P1 = LED; LED = 0xfe;  delayms(250);  } // 0xfe = 1111 1110
	}
}

