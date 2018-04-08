#include "stm32f4xx_hal.h"
#include "max21100.h"
#include "spi.h"


typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}DofTypeDef;

DofTypeDef gyro;
DofTypeDef acc;

uint8_t MaxRetStatus;

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



/**
*	@brief	Write data to register.
*	@param	reg : the register.
*			data : the config data.
*/
uint8_t MAX21100_WriteReg(uint8_t reg, uint8_t data)
{
	uint8_t status;
	
	MAX_CS_Enable();
	HAL_SPI_Transmit(&hspi1, &reg,1,0xFFFFFF);
	HAL_SPI_Transmit(&hspi1, &data,1,0xFFFFFF);
	MAX_CS_Disable();
	return status;

}

/**
*	@brief	Read data from register.
*	@param	reg : the register.
*	@retval	data.
*/
uint8_t MAX21100_ReadReg(uint8_t reg)
{
	uint8_t reg_value;
	
	MAX_CS_Enable();
	reg = reg|0x80;	
	
	HAL_SPI_Transmit(&hspi1, &reg, 1, 0xFFFF);
	HAL_SPI_Receive(&hspi1, &reg_value, 1, 0xFFFF);
	MAX_CS_Disable();
	return (reg_value); 
}

/**************************实现函数********************************************
*函数原型:	  void HMC59X3_getID(char id[3])
*功　　能:	   读取芯片的ID
输入参数：     	ID存放的数组
输出参数：  无
*******************************************************************************/
uint8_t GET_MAX21100_ID(void) 
{
	return MAX21100_ReadReg(MAX21100_WHO_AM_I);
}  

/**
*	@brief	MAX21100 Init.
*/
void Max21100_Init(void)
{
	MaxRetStatus = GET_MAX21100_ID();
	
	MAX21100_WriteReg(MAX21100_POWER_CFG, MAX21100_POWER_CFG_DATA);
	HAL_Delay(100);

	//关闭从IIC
	MAX21100_WriteReg(MAX21100_I2C_CFG, MAX21100_I2C_CFG_DATA);
	HAL_Delay(100);	
	
}

void MAX21100_UpdateData(void)
{
	gyro.x=((((int16_t)MAX21100_ReadReg(MAX_GYRO_X_H)) << 8) | MAX21100_ReadReg(MAX_GYRO_X_L));
	gyro.y=((((int16_t)MAX21100_ReadReg(MAX_GYRO_Y_H)) << 8) | MAX21100_ReadReg(MAX_GYRO_Y_L)) ;
	gyro.z=((((int16_t)MAX21100_ReadReg(MAX_GYRO_Z_H)) << 8) | MAX21100_ReadReg(MAX_GYRO_Z_L)) ;
	
	acc.x=((((int16_t)MAX21100_ReadReg(MAX_ACC_X_H)) << 8)   | MAX21100_ReadReg(MAX_ACC_X_L)) ;
	acc.y=((((int16_t)MAX21100_ReadReg(MAX_ACC_Y_H)) << 8)   | MAX21100_ReadReg(MAX_ACC_Y_L)) ;
	acc.z=((((int16_t)MAX21100_ReadReg(MAX_ACC_Z_H)) << 8)   | MAX21100_ReadReg(MAX_ACC_Z_L)) ;
}

