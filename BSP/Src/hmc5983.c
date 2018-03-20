#include "hmc5983.h"
#include "iic_bsp.h"
#include "i2c.h"


uint8_t Magnetic[6];
uint8_t HmcRetStatus;

void HMC5983_Init(void)
{
	uint8_t cmd;
	
	cmd = 0x70;
	HmcRetStatus = BSP_IICMemoryWrite(&hi2c1, HMC5983_ADDRESS, HMC5983_CFG_A, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 10);
	cmd = 0xA0;
	HmcRetStatus = BSP_IICMemoryWrite(&hi2c1, HMC5983_ADDRESS, HMC5983_CFG_B, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 10);
	cmd = 0x00;
	HmcRetStatus = BSP_IICMemoryWrite(&hi2c1, HMC5983_ADDRESS, HMC5983_MODE, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 10);
	HAL_Delay(100);
}

void HMC5983_ReadMag(void)
{
	HmcRetStatus = BSP_IICMemoryRead(&hi2c1, HMC5983_ADDRESS, HMC5983_X_MSB,I2C_MEMADD_SIZE_8BIT, Magnetic, 6, 10);
	HAL_Delay(80);		/* wait convert completion. */
}
