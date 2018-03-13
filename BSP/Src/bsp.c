#include "includes.h"






void BSP_Init(void)
{
    Comm1_Init(&huart1);
    Comm3_Init(&huart3);
    Comm5_Init(&huart5);
    BSP_PWMChannelStart();
	HMC5983_Init();
}
