#include "stm32f4xx_hal.h"
#include "ms5611.h"
#include "spi.h"


uint16_t MS5611_prom[8];

/**
*	@brief	CS Pin Enable.
*	@retval	none.
*/
static void MS_CS_Enable(void)
{
	HAL_GPIO_WritePin(MS_CS_GPIO_Port, MS_CS_Pin, GPIO_PIN_RESET);
}

/**
*	@brief	CS Pin Disable.
*	@retval	none.
*/
static void MS_CS_Disable(void)
{
	HAL_GPIO_WritePin(MS_CS_GPIO_Port, MS_CS_Pin, GPIO_PIN_SET);
}

/**
*	@brief	Write data to register.
*	@param	reg : the register.
*			data : the config data.
*/
uint8_t MS5611_WriteReg(uint8_t reg)
{
	return HAL_SPI_Transmit(&hspi1, &reg,1,0xFFFFFF);
}

/**
*	@brief	Read data from register.
*	@param	reg : the register.
*	@retval	data.
*/
uint8_t MS5611_ReadReg(uint8_t reg)
{
	uint8_t reg_value;
	HAL_SPI_Transmit(&hspi1, &reg, 1, 0xFFFF);
	return HAL_SPI_Receive(&hspi1, &reg_value, 1, 0xFFFF);; 
}

/**
*	@brief	Reset target.
*/
void MS5611_Reset(void)
{
	MS_CS_Enable();
	MS5611_WriteReg(MS5611_CMD_RESET);		/* MS5611 Reset. */
	MS_CS_Disable();
}

/**
*	@brief	Read prom.
*/
void MS5611_ReadProm(void)
{
	uint8_t rxbuf[2] = {0,0};
	
	for(int i = 0; i < 8; i++)
	{
		MS_CS_Enable();
		MS5611_WriteReg(MS5611_CMD_PROM_BASE + i * 2);
		rxbuf[0] = MS5611_ReadReg(0x00);
		rxbuf[1] = MS5611_ReadReg(0x00);
		MS5611_prom[i] = rxbuf[0] << 8 | rxbuf[1];
		HAL_Delay(1);
		MS_CS_Disable();		
	}
}

/**
*	@brief	Init.
*/
void MS5611_Init(void)
{
	MS5611_Reset();
	MS5611_ReadProm();
}

