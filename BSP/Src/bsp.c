#include "includes.h"






void BSP_Init(void)
{
    Comm1_Init(&huart1);
    Comm3_Init(&huart3);
    Comm5_Init(&huart5);
	RunFlagInit();
	W25Q_Init();
	MS5611_Init();
	HMC5983_Init();
	Max21100_Init();
	BSP_GPIO_SonicInit();
	LEDsSetConfig();
	PWM_IN_Init();
    BSP_PWMChannelStart();
	
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);	/* turn off green light. */
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	
	LEDs_ColorAdjust(1,0,100,0);
	LEDs_ColorAdjust(2,0,100,100);
	LEDs_ColorAdjust(3,100,100,0);
	LEDs_ColorAdjust(4,100,50,0);
	LEDs_ColorAdjust(5,0,100,0);
}
