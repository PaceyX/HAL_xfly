#include "stm32f4xx_hal.h"
#include "ms5611_temp.h"
#include "spi.h"
#include <math.h>
#include <stdlib.h>



MS5611TypeDef MS5611;

uint16_t PromData[8];
uint32_t PressureADC = 0, TemperatureADC = 0;
float HeightOffsest = 0;

uint8_t MS5611_ReadWriteReg(uint8_t reg)
{
	uint8_t ret_value;
	HAL_SPI_TransmitReceive(&hspi1, &reg, &ret_value, 1, 10);
	return (ret_value);
}

/**
*	@brief	Reset moudle.
*	@note	the moudle must be reset after power-on.
*/
void MS5611_Reset(void)
{
	MS_CS_ENABLE;
	MS5611_ReadWriteReg(CMD_RESET);		/* Must reset after power-on. */
	MS_CS_DISABLE;
}

/**
*	@brief	Read factory calibration data.
*/
void MS5611_ReadProm(void)
{
	uint8_t rx_buf[2] = {0,0};
	
	for(int i = 0; i < 8; i++)
	{
		MS_CS_ENABLE;
		MS5611_ReadWriteReg(CMD_PROM_BASE + i*2);
		rx_buf[0] = MS5611_ReadWriteReg(0x00);
		rx_buf[1] = MS5611_ReadWriteReg(0x00);
		PromData[i] = ((uint16_t)(rx_buf[0] << 8) | rx_buf[1]);
		HAL_Delay(1);
		MS_CS_DISABLE;
	}
}

/**
*	@brief	Read 24 bits ADC value fafter convertion.
*	@retval	the adc value.
*/
uint32_t MS5611_ReadADC(void)
{
	uint8_t rx_buf[3];
	
	MS_CS_ENABLE;
	MS5611_ReadWriteReg(CMD_ADC_24_BITS);
	rx_buf[0] = MS5611_ReadWriteReg(0x00);
	rx_buf[1] = MS5611_ReadWriteReg(0x00);
	rx_buf[2] = MS5611_ReadWriteReg(0x00);
	MS_CS_DISABLE;
	return ((uint32_t)(rx_buf[0] << 16) | (rx_buf[1] << 8) | rx_buf[2]);
}

static void StartTempConvert(void)
{
	MS_CS_ENABLE;
	MS5611_ReadWriteReg(CMD_D2_OSR_4096);
	MS_CS_DISABLE;
}
	
static void StartPressureConvert(void)
{
	MS_CS_ENABLE;
	MS5611_ReadWriteReg(CMD_D1_OSR_4096);
	MS_CS_DISABLE;
}

void MS5611_UpdateData(void)
{
	static uint8_t count = 0;
	static uint32_t last_time = 0;
	
	if(count == 0)
	{
		StartTempConvert();
		last_time = HAL_GetTick();
		count = 1;
	}
	else if(count == 1 && (abs(HAL_GetTick() - last_time) > 10))	/* wait 10ms. */
	{
		TemperatureADC = MS5611_ReadADC();
		last_time = HAL_GetTick();
		count = 2;
	}
	else if(count == 2 && (abs(HAL_GetTick() - last_time) > 10))
	{
		StartPressureConvert();
		last_time = HAL_GetTick();
		count = 3;
	}
	else if(count == 3 && (abs(HAL_GetTick() - last_time) > 10))
	{
		PressureADC = MS5611_ReadADC();
		last_time = HAL_GetTick();
		count = 4;
	}
	else if(count == 4 && (abs(HAL_GetTick() - last_time) > 10))
	{
		count = 0;
	}
}

