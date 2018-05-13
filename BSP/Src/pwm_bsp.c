#include "stm32f4xx_hal.h"
#include "tim.h"
#include "gpio.h"


uint16_t RemoteControl[8];

void BSP_PWMChannelStart(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);					/* TIM1: Channel 1-4 */
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);	/* TIM5: Channel 3-4 */
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);	/* TIM8: Channel 3-4 */
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	
}

void PWM_IN_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_4);
	
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_4);
}


void TIM3_RxCallBack(void)
{
	static uint16_t temp_cnt1,temp_cnt1_2,temp_cnt2,temp_cnt2_2,temp_cnt3,temp_cnt3_2,temp_cnt4,temp_cnt4_2;
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_CC1))
	{
		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_CC1); 
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC1OF);
		if(GPIOC->IDR & GPIO_PIN_6)
		{
			
			temp_cnt1 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
		}
		else
		{
			temp_cnt1_2 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
			if(temp_cnt1_2>=temp_cnt1)
				RemoteControl[0] = temp_cnt1_2-temp_cnt1;
			else
				RemoteControl[0] = 0xffff-temp_cnt1+temp_cnt1_2+1;
		}		
	}
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_CC2))
	{
		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_CC2); 
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC2OF);
		if(GPIOC->IDR & GPIO_PIN_7)
		{
			
			temp_cnt2 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_2);
		}
		else
		{
			temp_cnt2_2 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_2);
			if(temp_cnt2_2>=temp_cnt2)
				RemoteControl[1] = temp_cnt2_2-temp_cnt2;
			else
				RemoteControl[1] = 0xffff-temp_cnt2+temp_cnt2_2+1;
		}		
	}
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_CC3))
	{
		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_CC3); 
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC3OF);
		if(GPIOB->IDR & GPIO_PIN_0)
		{
			
			temp_cnt3 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_3);
		}
		else
		{
			temp_cnt3_2 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_3);
			if(temp_cnt3_2>=temp_cnt3)
				RemoteControl[2] = temp_cnt3_2-temp_cnt3;
			else
				RemoteControl[2] = 0xffff-temp_cnt3+temp_cnt3_2+1;
		}
	}
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_CC4))
	{
		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_CC4); 
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC4OF);
		if(GPIOB->IDR & GPIO_PIN_1)
		{
			
			temp_cnt4 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_4);
		}
		else
		{
			temp_cnt4_2 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_4);
			if(temp_cnt4_2>=temp_cnt4)
				RemoteControl[3] = temp_cnt4_2-temp_cnt4;
			else
				RemoteControl[3] = 0xffff-temp_cnt4+temp_cnt4_2+1;
		}
	}
}

void TIM4_RxCallBack(void)
{
	static uint16_t temp_cnt5,temp_cnt5_2,temp_cnt6,temp_cnt6_2,temp_cnt7,temp_cnt7_2,temp_cnt8,temp_cnt8_2;
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim4, TIM_IT_CC1))
	{
		__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_CC1); 
		__HAL_TIM_CLEAR_FLAG(&htim4, TIM_FLAG_CC1OF);
		if(GPIOD->IDR & GPIO_PIN_12)
		{
			temp_cnt5 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
		}
		else
		{
			temp_cnt5_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
			if(temp_cnt5_2>=temp_cnt5)
				RemoteControl[4] = temp_cnt5_2-temp_cnt5;
			else
				RemoteControl[4] = 0xffff-temp_cnt5+temp_cnt5_2+1;
		}		
	}
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim4, TIM_IT_CC2))
	{
		__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_CC2); 
		__HAL_TIM_CLEAR_FLAG(&htim4, TIM_FLAG_CC2OF);
		if(GPIOD->IDR & GPIO_PIN_13)
		{
			temp_cnt6 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_2);
		}
		else
		{
			temp_cnt6_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_2);
			if(temp_cnt6_2>=temp_cnt6)
				RemoteControl[5] = temp_cnt6_2-temp_cnt6;
			else
				RemoteControl[5] = 0xffff-temp_cnt6+temp_cnt6_2+1;
		}		
	}
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim4, TIM_IT_CC3))
	{
		__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_CC3); 
		__HAL_TIM_CLEAR_FLAG(&htim4, TIM_FLAG_CC3OF);
		if(GPIOD->IDR & GPIO_PIN_14)
		{
			temp_cnt7 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_3);
		}
		else
		{
			temp_cnt7_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_3);
			if(temp_cnt7_2>=temp_cnt7)
				RemoteControl[6] = temp_cnt7_2-temp_cnt7;
			else
				RemoteControl[6] = 0xffff-temp_cnt7+temp_cnt7_2+1;
		}		
	}
	
	if(__HAL_TIM_GET_IT_SOURCE(&htim4, TIM_IT_CC4))
	{
		__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_CC4); 
		__HAL_TIM_CLEAR_FLAG(&htim4, TIM_FLAG_CC4OF);
		if(GPIOD->IDR & GPIO_PIN_15)
		{
			temp_cnt8 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_4);
		}
		else
		{
			temp_cnt8_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_4);
			if(temp_cnt8_2>=temp_cnt8)
				RemoteControl[7] = temp_cnt8_2-temp_cnt8;
			else
				RemoteControl[7] = 0xffff-temp_cnt8+temp_cnt8_2+1;
		}		
	}
}
