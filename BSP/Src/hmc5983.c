#include "hmc5983.h"
#include "iic_bsp.h"
#include "i2c.h"

uint8_t send = 0x98;

void HMC5983_Init(void)
{
	HAL_StatusTypeDef ret;
	
	ret = BSP_IICMemoryWrite(&hi2c1, HMC5983_ADDRESS, HMC5983_CFG_A, 1, &send, 1, 10);
	HAL_Delay(10);
	if(ret == HAL_OK)
	{
		HAL_Delay(2);
	}
//	IIC_Write_1Byte(HMC5983_ADDRESS,HMC5983_CFG_A,0x98);
//		delay_ms(25);
		
}
