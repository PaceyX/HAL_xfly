#include "stm32f4xx_hal.h"
#include "max21100.h"




/**
*	@brief	CS Pin Enable.
*	@retval	none.
*/
void MAX_CS_Enable(void)
{
	HAL_GPIO_WritePin(MAX_CS_GPIO_Port, MAX_CS_Pin, GPIO_PIN_RESET);
}

/**
*	@brief	CS Pin Disable.
*	@retval	none.
*/
void MAX_CS_Disable(void)
{
	HAL_GPIO_WritePin(MAX_CS_GPIO_Port, MAX_CS_Pin, GPIO_PIN_SET);
}
