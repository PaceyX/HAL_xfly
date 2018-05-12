
#include "flash_bsp.h"


#if STM32_FLASH_SIZE < 256
  #define STM_SECTOR_SIZE  1024 
#else 
  #define STM_SECTOR_SIZE	 2048
#endif


#if STM32_FLASH_WREN	 
static uint16_t STMFLASH_BUF [ STM_SECTOR_SIZE / 2 ];
static FLASH_EraseInitTypeDef EraseInitStruct;
#endif


uint16_t STMFLASH_ReadHalfWord ( uint32_t faddr )
{
	return *(__IO uint16_t*)faddr; 
}

uint32_t STMFLASH_ReadWord ( uint32_t faddr )
{
	return *(__IO uint32_t*)faddr; 
}

#if STM32_FLASH_WREN	   

void STMFLASH_Write_NoCheck ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )   
{ 			 		 
	uint16_t i;	
	
	for(i=0;i<NumToWrite;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,WriteAddr,pBuffer[i]);
	  WriteAddr+=2;                                    
	}  
} 


void STMFLASH_Write ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )	
{
  uint32_t SECTORError = 0;
	uint16_t secoff;	   
	uint16_t secremain; 
 	uint16_t i;    
	uint32_t secpos;	   
	uint32_t offaddr;   
	
	if(WriteAddr<FLASH_BASE||(WriteAddr>=(FLASH_BASE+1024*STM32_FLASH_SIZE)))return;
	
	HAL_FLASH_Unlock();						
	
	offaddr=WriteAddr-FLASH_BASE;		
	secpos=offaddr/STM_SECTOR_SIZE;			
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		
	secremain=STM_SECTOR_SIZE/2-secoff;		
	if(NumToWrite<=secremain)secremain=NumToWrite;
	
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		for(i=0;i<secremain;i++)
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;  
		}
		if(i<secremain)
		{


      EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
      EraseInitStruct.PageAddress   = secpos*STM_SECTOR_SIZE+FLASH_BASE;
      EraseInitStruct.NbPages       = 1;
      HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);

			for(i=0;i<secremain;i++)
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		}
    else
    {
      STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);			   
		}
    if(NumToWrite==secremain)break;
		else
		{
			secpos++;				
			secoff=0;				 	 
		   	pBuffer+=secremain;  	
			WriteAddr+=secremain;		   
		   	NumToWrite-=secremain;	
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;
			else secremain=NumToWrite;
		}	 
	};	
	HAL_FLASH_Lock();
}
#endif


void STMFLASH_Read ( uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead )   	
{
	uint16_t i;
	
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);
		ReadAddr+=2;
	}
}

void STMFLASH_Read32(uint32_t ReadAddr, uint32_t *pBuffer, uint16_t NumToRead)
{
	uint16_t i;
	
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);
		ReadAddr+=4;
	}
}

