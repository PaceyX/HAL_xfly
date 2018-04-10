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
	uint8_t reg_value;
	
	MS_CS_Enable();

	HAL_SPI_Transmit(&hspi1, &reg, 1, 0xFFFF);
	HAL_SPI_Receive(&hspi1, &reg_value, 1, 0xFFFF);
	MS_CS_Disable();
	
	return reg_value;
}

/**
*	@brief	Read data from register.
*	@param	reg : the register.
*	@retval	data.
*/
//uint8_t MS5611_ReadReg(uint8_t reg)
//{
//	uint8_t reg_value;
//	HAL_SPI_Transmit(&hspi1, &reg, 1, 0xFFFF);
//	return HAL_SPI_Receive(&hspi1, &reg_value, 1, 0xFFFF); 
//}


void MS5611_MultiRead(uint8_t Reg, uint8_t *Val, uint8_t cnt)
{
	uint8_t i;
	
	MS_CS_Enable();
	MS5611_WriteReg(Reg);
	
	for(i=0;i<cnt;i++)
	{
		HAL_SPI_Transmit(&hspi1, 0x00, 1, 0xFFFF);
		HAL_SPI_Receive(&hspi1, Val, 1, 0xFFFF); 
		Val++;
	}
	MS_CS_Disable();
}


/**
*	@brief	Read prom.
*/
void MS5611_ReadProm(void)
{
	uint8_t buf[2] = {0,0};
	
	for(int i = 0; i < 8; i++)
	{
		MS5611_MultiRead((MS5611_CMD_PROM_BASE + i * 2), buf, 2);
		MS5611_prom[i] = (uint16_t)buf[0] << 8 | buf[1];	
	}
}

/**
*	@brief	Init.
*/
void MS5611_Init(void)
{
	MS5611_WriteReg(MS5611_CMD_RESET);
	MS5611_ReadProm();
}

