/**
******************************************************************************
* @file     app_usart3.c
* @author  Pacey
* @date     2018/02/24
* @brief 	  Communiction Moudle with board.
* @attention Copyright (C) 2016 Inmotion
******************************************************************************
*/

#include "includes.h"

/* DMA-Usart3 Config. */
#define USART3_BUFF_SIZE	128
uint8_t USART3_RxBuffer[USART3_BUFF_SIZE];
static CommUsartType CommUsart = {NULL};

/* Comm3 Frame Info Init. */
static Comm3_FrameType Comm3Rx;
static uint8_t Comm3RxBuffer[32];

/**
*	@brief	Initialize DMA-USART Config.
*	@param	USART Handle.
*/
void Comm3_Init(UART_HandleTypeDef *huart)
{
	/*Comm3 Frame Info Init. */
	Comm3Rx.offset = 0;
	Comm3Rx.buffer = Comm3RxBuffer;
	Comm3Rx.size = sizeof(Comm3RxBuffer);
	
	/* Usart3-DMA Config. */
	CommUsart.buffer_size = USART3_BUFF_SIZE;			/* Config USART3 DMA Buffer Size. */
	CommUsart.dma_rx_buffer = USART3_RxBuffer;			/* Config Receive Buffer address. */
	CommUsart.huart = huart;							/* Get Usart Handle. */
	
	BSP_CommUsartInit(&CommUsart, huart);					/* Init DMA Config. */
}

/**
*	@brief	USART3 Send Data.
*	@param	buff: the data will be send.
*			len:  data length.
*/
uint8_t Comm3_SendData(uint8_t * buff, uint16_t len)
{
	return BSP_CommUsartSendData(&CommUsart, buff, len);
}

void Comm3_RecceivePack(void)
{
	uint8_t * data;
	uint32_t len;
	Comm3_FrameType * hc = &Comm3Rx;
	
	if(BSP_CommUsartRecvData(&CommUsart, &data, &len))
	{
		for(int i = 0; i<len; i++)
		{
			if(hc->offset >= hc->size)		hc->offset = 0;
			Comm3_SendData("aaa",3);
//			FactoryDataRecv(hc, data[i]);		
		}
	}
}

/**
*	@brief	The task communiction with board.
*/
void uCommWithBoard_Task(void)
{
	
}

