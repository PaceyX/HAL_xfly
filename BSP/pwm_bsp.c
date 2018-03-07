#include "includes.h"





void BSP_PWMChannelStart(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);					/* TIM1: Channel 1-4 */
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3 | TIM_CHANNEL_4);	/* TIM5: Channel 3-4 */
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3 | TIM_CHANNEL_4);	/* TIM4: Channel 3-4 */
	
}

