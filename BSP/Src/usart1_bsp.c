/**
******************************************************************************
* @file     app_usart1.c
* @author  Pacey
* @date     2018/02/24
* @brief 	  Print SYS Info.
* @attention Copyright (C) 2016 Inmotion
******************************************************************************
*/

#include "stm32f4xx_hal.h"
#include "usart.h"
#include <stdbool.h>
#include "global_define.h"
#include "usart_bsp.h"


typedef struct
{
	uint16_t offset;		/* Accumulate the received data and find frame head. */
	u8 * buffer;
	u16 size;
}Comm1_FrameType;



/* DMA-Usart3 Config. */
#define USART1_BUFF_SIZE	128
uint8_t USART1_RxBuffer[USART1_BUFF_SIZE];
static CommUsartType CommUsart = {NULL};


/* Comm3 Frame Info Init. */
static Comm1_FrameType Comm1Rx;
static uint8_t Comm1RxBuffer[32];


/**
*	@brief	Initialize DMA-USART Config.
*	@param	USART Handle.
*/
void Comm1_Init(UART_HandleTypeDef *huart)
{
	/*Comm1 Frame Info Init. */
	Comm1Rx.offset = 0;
	Comm1Rx.buffer = Comm1RxBuffer;
	Comm1Rx.size = sizeof(Comm1RxBuffer);
	
	/* Usart1-DMA Config. */
	CommUsart.buffer_size = USART1_BUFF_SIZE;			/* Config USART3 DMA Buffer Size. */
	CommUsart.dma_rx_buffer = USART1_RxBuffer;			/* Config Receive Buffer address. */
	CommUsart.huart = huart;							/* Get Usart Handle. */
	
	BSP_CommUsartInit(&CommUsart, huart);					/* Init DMA Config. */
}


/**
*	@brief	USART1 Send Data.
*	@param	buff: the data will be send.
*			len:  data length.
*/
uint8_t Comm1_SendData(uint8_t * buff, uint16_t len)
{
	return BSP_CommUsartSendData(&CommUsart, buff, len);
}



void Comm1_RecceivePack(void)
{
	uint8_t * data;
	uint32_t len;
	Comm1_FrameType * hc = &Comm1Rx;
	
	if(BSP_CommUsartRecvData(&CommUsart, &data, &len))
	{
		for(int i = 0; i<len; i++)
		{
			if(hc->offset >= hc->size)		hc->offset = 0;
			Comm1_SendData("aaa",3);
			//...
		}
	}
}

