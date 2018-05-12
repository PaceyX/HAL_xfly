#ifndef __FLASH_BSP_H__
#define __FLASH_BSP_H__

#include "stm32f4xx_hal.h"


#define STM32_FLASH_SIZE        1024  
#define STM32_FLASH_WREN        1    
#define CONFIG_ADDRESS     	0x8019000            // 0x8011800  旧版是此地址


uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  

void STMFLASH_WriteLenByte(uint32_t WriteAddr, uint32_t DataToWrite, uint16_t Len );	      
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr, uint16_t Len );					                    	
void STMFLASH_Write( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite );		
void STMFLASH_Read( uint32_t ReadAddr, uint16_t * pBuffer, uint16_t NumToRead );   
void STMFLASH_Read32(uint32_t ReadAddr, uint32_t *pBuffer, uint16_t NumToRead);

#endif 


