#include "stm32f4xx_hal.h"
#include "w25q32.h"
#include "spi.h"

ExtraFlashTypedef W25Q;
FlashInfoTypefdef W25QFlash;

uint8_t W25Q_ReadWriteByte(uint8_t reg)
{
	uint8_t ret_value;
	HAL_SPI_TransmitReceive(&hspi3, &reg, &ret_value, 1, 10);
	return (ret_value);
}

uint32_t W25Q_FlashTransfer(uint8_t * send_buffer, uint8_t * recv_buffer, uint32_t len)
{
	uint8_t data;
	while(len--)
	{
		data = send_buffer ? *send_buffer++ : W25Q_DUMMY_BYTE;
		W25Q_ReadWriteByte(data);
		data = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
		if(recv_buffer)
		{
			*recv_buffer++ = data;
		}
	}
	return len;
}

void W25Q_WriteEnable(void)
{
	W25Q_CS_Enable;
	W25Q_ReadWriteByte(W25Q_WRITE_ENABLE);
	W25Q_CS_Disable;
}

void W25Q_WriteDisable(void)
{
    W25Q_CS_Enable;
    W25Q_ReadWriteByte(W25Q_WRITE_DISABLE);
    W25Q_CS_Disable;
}

void Flash_WaitForEnd(void)
{
    uint8_t FLASH_Status = 0;

    do
    {
        W25Q_CS_Enable;
		
        W25Q_ReadWriteByte(W25Q_READ_STATUS);
        FLASH_Status = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
		
       	W25Q_CS_Disable;
    }
    while (FLASH_Status & W25Q_STATUS_BUSY);
}

void W25Q_FlashSectorErase(uint32_t address, uint8_t state)
{
	uint8_t FLASH_Status = 0;
	
	W25Q_WriteEnable();
	
	W25Q_CS_Enable;
	W25Q_ReadWriteByte(W25Q_SECTOR_ERASE);
	W25Q_ReadWriteByte((address & 0xFF0000) >> 16);
	W25Q_ReadWriteByte((address & 0xFF00) >> 8);
	W25Q_ReadWriteByte(address & 0xFF);
	W25Q_CS_Disable;
	
	/* wait to end. */
	if(state)
	{
		do
		{
			W25Q_CS_Enable;
			W25Q_ReadWriteByte(W25Q_READ_STATUS);
			FLASH_Status = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
			W25Q_CS_Disable;
		}
		while (FLASH_Status & W25Q_STATUS_BUSY);
	}
}
	
void W25Q_FlashPageRead(uint32_t address, uint8_t * buffer, uint32_t lenght)
{
	W25Q_CS_Enable;
	
	W25Q_ReadWriteByte(W25Q_READ_DATA);
	W25Q_ReadWriteByte((address & 0xFF0000) >> 16);
	W25Q_ReadWriteByte((address& 0xFF00) >> 8);
	W25Q_ReadWriteByte(address & 0xFF);
	
	while(lenght--)
	{
		*buffer = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
		buffer++;
	}
	W25Q_CS_Disable;
}


void Flash_PageWrite(uint32_t address,uint8_t* buffer,  uint32_t lenght)
{
	uint8_t ret_value;
	
	W25Q_CS_Enable;
	W25Q_WriteEnable();
	
	W25Q_ReadWriteByte(W25Q_PAGE_WRITE);
	W25Q_ReadWriteByte((address & 0xFF0000) >> 16);
	W25Q_ReadWriteByte((address & 0xFF00) >> 8);
	W25Q_ReadWriteByte(address & 0xFF);
	
	while (lenght--)
    {
        ret_value = W25Q_ReadWriteByte(*buffer);
        buffer++;
    }
	
	W25Q_CS_Disable;
}

void W25Q_FlashSectorsRead(uint32_t address,uint8_t * buffer,uint16_t count)
{
	uint16_t i=0;
	
	for(i = 0;i < count; i++)
	{
		W25Q_FlashPageRead(address,buffer,W25QFlash.sector_size);
		buffer += W25QFlash.sector_size;
		address += W25QFlash.sector_size;
	}
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
	
	if(W25Q.manufacturer == W25Q_MANUFACTORER_ID)
	{
		W25QFlash.sector_size = 4096;   
		
		if(W25Q.capacity == (JEDEC_W25Q32_DW&0xff))
		{
			W25QFlash.sector_count = 1024;
		}
		W25QFlash.capacity = W25QFlash.sector_size * W25QFlash.sector_count;
	}
	else
	{
		/* print error debug info. */
	}
}


void flash_test(void)
{
	uint8_t write_buffer[200];
	uint8_t read_buffer[200];
	uint32_t address0 = 0, address1 = 0;
	
	for(uint32_t i; i<200; i++)
	{
		write_buffer[i] = i;
	}
	
	Flash_PageWrite(address0, write_buffer, 100);
	Flash_WaitForEnd();
	
	W25Q_FlashPageRead(address1, read_buffer,100);

}



