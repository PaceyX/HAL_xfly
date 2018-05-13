#include "stm32f4xx_hal.h"
#include "usart.h"


#include "usart_bsp.h"
#include <stdio.h>
#include "usart_user.h"




/******************************************************************************/
/*								USART1										  */
/******************************************************************************/
typedef struct
{
	uint16_t offset;		/* Accumulate the received data and find frame head. */
	u8 * buffer;
	u16 size;
}Comm1_FrameType;


/* DMA-Usart3 Config. */
#define USART1_BUFF_SIZE	128
uint8_t USART1_RxBuffer[USART1_BUFF_SIZE];
static CommUsartType CommUsart1 = {NULL};

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
	CommUsart1.buffer_size = USART1_BUFF_SIZE;			/* Config USART3 DMA Buffer Size. */
	CommUsart1.dma_rx_buffer = USART1_RxBuffer;			/* Config Receive Buffer address. */
	CommUsart1.huart = huart;							/* Get Usart Handle. */
	
	BSP_CommUsartInit(&CommUsart1, huart);					/* Init DMA Config. */
}

/**
*	@brief	USART1 Send Data.
*	@param	buff: the data will be send.
*			len:  data length.
*/
uint8_t Comm1_SendData(uint8_t * buff, uint16_t len)
{
	return BSP_CommUsartSendData(&CommUsart1, buff, len);
}

void Comm1_RecceivePack(void)
{
	uint8_t * data;
	uint32_t len;
	Comm1_FrameType * hc = &Comm1Rx;
	
	if(BSP_CommUsartRecvData(&CommUsart1, &data, &len))
	{
		for(int i = 0; i<len; i++)
		{
			if(hc->offset >= hc->size)		hc->offset = 0;
			Comm1_SendData("aaa",3);
			//...
		}
	}
}

int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
//	Comm1_SendData((uint8_t *)&ch, sizeof(ch));
	return ch;
}


/******************************************************************************/
/*								USART3										  */
/******************************************************************************/
typedef struct
{
	uint16_t offset;		/* Accumulate the received data and find frame head. */
	uint8_t * buffer;
	uint16_t size;
}Comm3_FrameType;


/* DMA-Usart3 Config. */
#define USART3_BUFF_SIZE	128
uint8_t USART3_RxBuffer[USART3_BUFF_SIZE];
static CommUsartType CommUsart3 = {NULL};

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
	CommUsart3.buffer_size = USART3_BUFF_SIZE;			/* Config USART3 DMA Buffer Size. */
	CommUsart3.dma_rx_buffer = USART3_RxBuffer;			/* Config Receive Buffer address. */
	CommUsart3.huart = huart;							/* Get Usart Handle. */
	
	BSP_CommUsartInit(&CommUsart3, huart);					/* Init DMA Config. */
}

/**
*	@brief	USART3 Send Data.
*	@param	buff: the data will be send.
*			len:  data length.
*/
uint8_t Comm3_SendData(uint8_t * buff, uint16_t len)
{
	return BSP_CommUsartSendData(&CommUsart3, buff, len);
}

void Comm3_RecceivePack(void)
{
	uint8_t * data;
	uint32_t len;
	Comm3_FrameType * hc = &Comm3Rx;
	
	if(BSP_CommUsartRecvData(&CommUsart3, &data, &len))
	{
		for(int i = 0; i<len; i++)
        {
            if(hc->offset >= hc->size)		hc->offset = 0;
            Comm3_SendData("aaa",3);
//			FactoryDataRecv(hc, data[i]);		
		}
	}
}


/******************************************************************************/
/*								UART5 										  */
/******************************************************************************/
static uint8_t UartCommData = 0;

/**
* @brief  Transmittion layer Initialization.
* @param  huart: Uart Handle.
* @retval success or not.
*/
bool Comm5_Init(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&huart5, &UartCommData, 1);
	
    return true;
}

/**
* @brief  Transmit and Receive.
* @param  data : Data.
* @param  len : Data Length. 
* @retval None
*/
u8 Comm5_SendData(u8 *data, u16 len)
{
	HAL_UART_Transmit(&huart5, data, len, 10);
	HAL_UART_Receive_IT(&huart5,&UartCommData,1);
	return true;
}

/**
*	@brief	User Callback function.
*/
void UART5_RxIRQCallback(void)
{
//	static uint8_t count = 0;

//	SetLedFlash(2);
//	
//	if(UPLOAD_TO_SERVER_ENABLE && UartCommData == 0x01 && count == 0)
//	{
//		count++;
//	}
//	else if(count == 1 && UartCommData == 0x0D)
//	{
//		count = 0;
//		csComServer.recvive_ack = 1;
//	}
//	
	HAL_UART_Receive_IT(&huart5,&UartCommData,1);			/* After receive data, then open receive IT. */

}


