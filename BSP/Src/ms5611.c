#include "stm32f4xx_hal.h"
#include "ms5611.h"
#include "spi.h"
#include "stdio.h"
#include "math.h"


typedef struct{

		int32_t pressure;//单位Pa
		int32_t temperature;//temperature/100为摄氏度值
		float  BaroAlt;      //单位米
	  float BaroAltOffset;
				
}BARO_TYPE;

BARO_TYPE MS5611;

uint32_t ms5611_ut;  
uint32_t ms5611_up;  
uint16_t MS5611_prom[8];
float MS5611_LAST;

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
uint8_t MS5611_ReadWriteReg(uint8_t reg)
{
	uint8_t reg_value;
	HAL_SPI_TransmitReceive(&hspi1, &reg, &reg_value, 1, 10);
	return (reg_value);
}

void MS5611_Reset(void)
{
    MS_CS_Enable();
	MS5611_ReadWriteReg(MS5611_CMD_RESET);
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
		MS5611_ReadWriteReg(MS5611_CMD_PROM_BASE + i * 2);
		rxbuf[0] = MS5611_ReadWriteReg(0X00);
		rxbuf[1] = MS5611_ReadWriteReg(0X00);
		MS5611_prom[i] = rxbuf[0] << 8 | rxbuf[1];
		HAL_Delay(1);
		MS_CS_Disable();
	}
	
}


/******************************************************************
						 读取24位ADC值
******************************************************************/
static uint32_t ms5611_read_adc(void)
{
    uint8_t rxbuf[3];
	MS_CS_Enable();
	MS5611_ReadWriteReg(CMD_ADC_READ);
	rxbuf[0] = MS5611_ReadWriteReg(0X00);
	rxbuf[1] = MS5611_ReadWriteReg(0X00);
	rxbuf[2] = MS5611_ReadWriteReg(0X00);
	MS_CS_Disable();
    return (rxbuf[0] << 16) | (rxbuf[1] << 8) | rxbuf[2];
}

/******************************************************************
									  开始温度转换
******************************************************************/
void ms5611_start_ut(void)
{
    MS_CS_Enable();
	MS5611_ReadWriteReg(CMD_ADC_CONV + CMD_ADC_D2 + MS5611_OSR);
	MS_CS_Disable();
}

/******************************************************************
									  开始气压转换
******************************************************************/
void ms5611_start_up(void)
{
	MS_CS_Enable(); 
	MS5611_ReadWriteReg(CMD_ADC_CONV + CMD_ADC_D1 + MS5611_OSR);
	MS_CS_Disable();

}

/******************************************************************
									 读取气压值
******************************************************************/
void ms5611_get_up(void)
{
    ms5611_up = ms5611_read_adc();
}


/******************************************************************
									  读取温度值
******************************************************************/
void ms5611_get_ut(void)
{
    ms5611_ut = ms5611_read_adc();
}

/******************************************************************
									  计算气压、温度
******************************************************************/
static float ms5611_calculate(void)
{	
		int32_t  off2 = 0, sens2 = 0, delt; 

    int32_t dT = (int32_t)ms5611_ut - ((int32_t)MS5611_prom[5] << 8);
    int64_t off = ((uint32_t)MS5611_prom[2] << 16) + (((int64_t)dT * MS5611_prom[4]) >> 7);
    int64_t sens = ((uint32_t)MS5611_prom[1] << 15) + (((int64_t)dT * MS5611_prom[3]) >> 8);
    MS5611.temperature = 2000 + (((int64_t)dT * MS5611_prom[6]) >> 23);

    if (MS5611.temperature < 2000) // temperature lower than 20degC 
		{ 
        delt = MS5611.temperature - 2000;
        delt = 5*delt * delt;
        off2 = delt >> 1;
        sens2 = delt >> 2;
        if (MS5611.temperature < -1500) // temperature lower than -15degC
				{		
            delt = MS5611.temperature + 1500;
            delt = delt * delt;
            off2  += 7 * delt;
            sens2 += (11 * delt) >> 1;
        }
    }
    off  -= off2; 
    sens -= sens2;
    MS5611.pressure = (((ms5611_up * sens ) >> 21) - off) >> 15;		
		return  (float)((1.0f - pow((MS5611.pressure) / 101325.0f, 0.190295f)) * 44330);// 米
}

#define MS5611_FILTER_NUM 10					//滑动滤波长度
float MS5611_BUF[MS5611_FILTER_NUM];
/******************************************************************
									  滑动滤波
******************************************************************/
static void MS5611_filter(void)
{
	static uint8_t filter_cnt=0;
	float temp=0.0f;
	uint8_t i;	
	
	MS5611_BUF[filter_cnt] = MS5611_LAST;//更新滑动窗口数组


	for(i=0;i<MS5611_FILTER_NUM;i++)
	{
		temp += MS5611_BUF[i];

	}

	MS5611.BaroAlt = temp / MS5611_FILTER_NUM;


	filter_cnt++;
	if(filter_cnt==MS5611_FILTER_NUM)	filter_cnt=0;
}

/******************************************************************
									  得到海拔高度
******************************************************************/
void MS5611_Cal(void)
{

	MS5611_LAST = ms5611_calculate() - MS5611.BaroAltOffset;
	MS5611_filter();
}

/**
*	@brief	Init.
*/
void MS5611_Init(void)
{
	float sum = 0.0f;
	
	MS5611.BaroAltOffset = 0.0f;
	MS5611_Reset();
	HAL_Delay(10);	
	MS5611_ReadProm();
	HAL_Delay(500);
	
	//MS5611校正
	for(int i=0;i<10;i++)
	{

		ms5611_start_ut();
		HAL_Delay(10);
		ms5611_get_ut();   //400us
		HAL_Delay(10);
		ms5611_start_up();
		HAL_Delay(10);
		ms5611_get_up();
		MS5611_Cal();   //400us
		sum +=MS5611_LAST;
		HAL_Delay(100);

	}
	MS5611.BaroAltOffset = sum / 10.0f;

}

void MS5611_GetData(void)
{
	ms5611_start_ut();
	HAL_Delay(10);
	ms5611_get_ut(); 
	HAL_Delay(10);
	ms5611_start_up();
	HAL_Delay(10);
	ms5611_get_up();
	MS5611_Cal();  
}
