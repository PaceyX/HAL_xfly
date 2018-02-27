#include "includes.h"



static u8 UartCommData = 0;

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


