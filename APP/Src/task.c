#include "includes.h"





void AppTask(void)
{
	Comm3_RecceivePack();
	Comm1_RecceivePack();
	if(Flag_1s)
	{
		Flag_1s = 0;
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
	}
	ultraDistanceSampling();
}
