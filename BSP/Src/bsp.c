#include "includes.h"






void BSP_Init(void)
{
    Comm1_Init(&huart1);
    Comm3_Init(&huart3);
    Comm5_Init(&huart5);
    BSP_PWMChannelStart();
	HMC5983_Init();
	HAL_TIM_Base_Start_IT(&htim6);
	BSP_GPIO_SonicInit();
	Max21100_Init();
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);	/* turn off green light. */
	MS5611_Init();
}
