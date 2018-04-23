#include "includes.h"


void AppTask(void)
{
	RunFlagHandleTask();
	
	if(RunFlag.ms1)
	{
		Comm3_RecceivePack();
		Comm1_RecceivePack();
	}

	if(RunFlag.ms20)
	{
		ultraDistanceSampling();
	}
	
	if(RunFlag.ms4)
	{
		MAX21100_UpdateData();
		MS5611_UpdateData();
	}
	
	if(RunFlag.ms100)
	{
		HMC5983_ReadMag();
	}


	if(RunFlag.ms1000)
	{
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);
	}
}
