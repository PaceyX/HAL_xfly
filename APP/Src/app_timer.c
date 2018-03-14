#include "stm32f4xx.h"
#include "ultrasonic.h"

uint8_t Flag_1s = 0;


void appTim6CallBack(void)
{
	static uint32_t count = 0;
	
	count++;
	if(count == 100*1000)
	{
		count = 0;
		Flag_1s = 1;
	}
	ultrasonicCallBack();
}
