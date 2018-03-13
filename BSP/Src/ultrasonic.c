/**
******************************************************************************
* @file    ultrasonic.c
* @author  Pacey
* @date    2018/03/13
* @brief   US015 ultrasonic distance module.
* @attention Copyright (C) X-FLY team.
******************************************************************************
*/

#include "stm32f4xx.h"


/**
*  @brief  
*/
void BSP_GPIO_SonicInit(void)
{
    
	
}

/**
*  @brief  Send start info.
*  @param  none.
*  @retval none.
*  @note   send 10us high level.
*/
void SendStartInfo(void)
{
	
}

/**
*  @brief  Get high level time.
*  @param  none.
*  @retval the high level time(us).
*  @note   Be called in timer interrupt per 10us.
*/
uint16_t ultraGetOutputCallBack(void)
{
	
}
