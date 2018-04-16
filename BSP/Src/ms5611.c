#include "stm32f4xx_hal.h"
#include "ms5611.h"
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

void MS5611_Calculate(void)
{
	int32_t dT = (int32_t)TemperatureADC - ((int32_t)PromData[5] << 8);
	int32_t TEMP = 2000 + (dT * PromData[6] >> 23);
	int64_t OFF = ((uint32_t)PromData[2] << 16) + ((PromData[4] * (int64_t)dT) >> 7);
	int64_t SENS = (PromData[1] << 15) + ((PromData[3] * (int64_t)dT) >> 8);
	
	int64_t T2 = 0, OFF2 = 0, SENS2 = 0;
	int32_t delt;
	
	if(TEMP < 2000)
	{
		T2 = (dT * dT) >> 31;
		delt = TEMP - 2000; 
		OFF2 = 5 * ((delt *delt) >> 1);
		SENS2 = 5 * ((delt *delt) >> 2);
		
		if(TEMP < -1500)
		{
			delt = TEMP + 1500;
			OFF2 = OFF2 + 7 * delt * delt;
			SENS2 = SENS2 + 11 * ((delt * delt) >> 1);
		}
	}
	
	TEMP = TEMP - T2;
	OFF = OFF - OFF2;
	SENS = SENS - SENS2;
	/* calculate pressure. */
	MS5611.pressure = ((PressureADC * (SENS >> 21) - OFF) >> 15);
	MS5611.temperature = TEMP;
	MS5611.height = (float)((1.0f - pow((MS5611.pressure) / 101325.0f, 0.190295f)) * 44330);
}

void MS5611_Init(void)
{
	MS5611_Reset();
	HAL_Delay(10);
	MS5611_ReadProm();
	HAL_Delay(500);
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
		MS5611_Calculate();
		count = 0;
	}
}

