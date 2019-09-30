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
		 LED = LED << 1;    //循环左移1位，点亮下一个LED "<<"为左移位
		 if(LED == 0x00 )	 
		 { P1 = LED; LED = 0xfe;  delayms(250);  } // 0xfe = 1111 1110
	}
}

