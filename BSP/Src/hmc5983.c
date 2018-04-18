#include "hmc5983.h"
#include "iic_bsp.h"
#include "i2c.h"


short Magnetic[6];
uint8_t Magnetic2[6];
uint8_t HmcRetStatus;

void HMC5983_Init(void)
{
	uint8_t cmd;
	
	cmd = 0x7C;
	HmcRetStatus = BSP_IICMemoryWrite(&hi2c1, HMC5983_ADDRESS, HMC5983_CFG_A, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 10);
	cmd = 0xC0;
	HmcRetStatus = BSP_IICMemoryWrite(&hi2c1, HMC5983_ADDRESS, HMC5983_CFG_B, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 10);
	cmd = 0x00;
	HmcRetStatus = BSP_IICMemoryWrite(&hi2c1, HMC5983_ADDRESS, HMC5983_MODE, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 10);
	HAL_Delay(100);
}

void HMC5983_ReadMag(void)
{
	static u32 last_time = 0;
	
	if(HAL_GetTick() - last_time > 80)	last_time = HAL_GetTick();
	else  return;
	
	HmcRetStatus = BSP_IICMemoryRead(&hi2c1, HMC5983_ADDRESS, HMC5983_X_MSB,I2C_MEMADD_SIZE_8BIT, Magnetic2, 6, 10);

}
