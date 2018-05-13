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
    W25Q_CS_Enable;
	W25Q_ReadWriteByte(W25Q_READ_STATUS);
	
    do
    {
        FLASH_Status = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
    }
    while (FLASH_Status & W25Q_STATUS_BUSY);
	
	W25Q_CS_Disable;
}

void W25Q_FlashSectorErase(uint32_t address)
{
	W25Q_WriteEnable();
	
	Flash_WaitForEnd();
	
	W25Q_CS_Enable;
	
	W25Q_ReadWriteByte(W25Q_SECTOR_ERASE);
	W25Q_ReadWriteByte((address & 0xFF0000) >> 16);
	W25Q_ReadWriteByte((address & 0xFF00) >> 8);
	W25Q_ReadWriteByte(address & 0xFF);
	W25Q_CS_Disable;
	
	Flash_WaitForEnd();
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

void W25Q_FLASH_PageWrite(uint8_t * pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	W25Q_WriteEnable();
	W25Q_CS_Enable;
	W25Q_ReadWriteByte(W25Q_PAGE_WRITE);
	
	W25Q_ReadWriteByte((WriteAddr & 0xFF0000) >> 16);
	W25Q_ReadWriteByte((WriteAddr & 0xFF00) >> 8);
	W25Q_ReadWriteByte(WriteAddr & 0xFF);
	
	if(NumByteToWrite > W25Q_PAGE_SIZE)
	{
		NumByteToWrite = W25Q_PAGE_SIZE;
	}
	
	while (NumByteToWrite--)
	{
		W25Q_ReadWriteByte(*pBuffer);
		pBuffer++;
	}
	
	W25Q_CS_Disable;
	Flash_WaitForEnd();
}

void W25Q_FLASH_BufferWrite(uint8_t * pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	
	Addr = WriteAddr % W25Q_PAGE_SIZE;
	count = W25Q_PAGE_SIZE - Addr;
	NumOfPage =  NumByteToWrite / W25Q_PAGE_SIZE;
	NumOfSingle = NumByteToWrite % W25Q_PAGE_SIZE;
	
	if(Addr == 0)
	{
		if(NumOfPage == 0)
		{
			W25Q_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
		}
		else
		{
			while(NumOfPage--)
			{
				W25Q_FLASH_PageWrite(pBuffer, WriteAddr, W25Q_PAGE_SIZE);
				WriteAddr += W25Q_PAGE_SIZE;
				pBuffer += W25Q_PAGE_SIZE;
			}
			W25Q_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
		}
	}
	else
	{
		if(NumOfPage == 0)
		{
			if(NumOfSingle > count)
			{
				temp = NumOfSingle - count;
				W25Q_FLASH_PageWrite(pBuffer, WriteAddr, count);
				WriteAddr +=  count;
				pBuffer += count;
				W25Q_FLASH_PageWrite(pBuffer, WriteAddr, temp);
			}
			else
			{
				W25Q_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
			}
		}
		else
		{
			NumByteToWrite -= count;
			NumOfPage =  NumByteToWrite / W25Q_PAGE_SIZE;
			NumOfSingle = NumByteToWrite % W25Q_PAGE_SIZE;
			
			W25Q_FLASH_PageWrite(pBuffer, WriteAddr, count);
			WriteAddr +=  count;
			pBuffer += count;
			
			while (NumOfPage--)
			{
				W25Q_FLASH_PageWrite(pBuffer, WriteAddr, W25Q_PAGE_SIZE);
				WriteAddr +=  W25Q_PAGE_SIZE;
				pBuffer += W25Q_PAGE_SIZE;
			}
			
			if (NumOfSingle != 0)
			{
				W25Q_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
			}
		}
	}
}

void W25Q_FLASH_BufferRead(uint8_t * pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	W25Q_CS_Enable;
	
	W25Q_ReadWriteByte(W25Q_READ_DATA);
	W25Q_ReadWriteByte((ReadAddr & 0xFF0000) >> 16);
	W25Q_ReadWriteByte((ReadAddr& 0xFF00) >> 8);
	W25Q_ReadWriteByte(ReadAddr & 0xFF);	
	
	while (NumByteToRead--)
	{
		*pBuffer = W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
		pBuffer++;
	}
	
	W25Q_CS_Disable;
}

void W25Q_Init(void)
{
	W25Q_CS_Enable;
	W25Q_ReadWriteByte(W25Q_DUMMY_BYTE);
	W25Q_CS_Disable;
	W25Q_ReadID();
	
	W25Q_FlashSectorErase(FLASH_SectorToErase);
	
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

#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define BufferSize (countof(Tx_Buffer)-1)
uint8_t Tx_Buffer[] = " X-FLY·É¿Ø°åFLASHÍâ²¿´æ´¢Ð¾Æ¬µ÷ÊÔ¡£  X-FLYYYYYYYYYYYYYYYYYYYYYYYY";
uint8_t Rx_Buffer[BufferSize];


void flash_test(void)
{
	W25Q_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
	W25Q_FLASH_BufferWrite(Tx_Buffer, 252, BufferSize);
	
	W25Q_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
	
}



