#include "stm32f4xx_hal.h"
#include "w25q32.h"
#include "spi.h"

ExtraFlashTypedef W25Q;

uint8_t W25Q_ReadWriteByte(uint8_t reg)
{
	uint8_t ret_value;
	HAL_SPI_TransmitReceive(&hspi3, &reg, &ret_value, 1, 10);
	return (ret_value);
}

uint8_t W25Q_ReadID(void)
{
	uint8_t buf[3];
	
	W25Q_CS_Enable;
	W25Q_ReadWriteByte(W25Q_DEVICE_ID);
	buf[0] = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
	buf[1] = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
	buf[2] = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
	W25Q_CS_Disable;
	
	W25Q.manufacturer = buf[0];
	W25Q.memory = buf[1];
	W25Q.capacity = buf[2];
	
	return W25Q.manufacturer;
}

void W25Q_Init(void)
{
	W25Q_CS_Enable;
	W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
	W25Q_CS_Disable;
	W25Q_ReadID();
}
