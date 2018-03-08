#ifndef __USART_BSP_H__
#define __USART_BSP_H__



#include <stdbool.h>




typedef struct{
    UART_HandleTypeDef *huart;			/* Specify handle. */
    uint32_t tx_tc_flag;						/* Transmittion Complete flag. */
    uint8_t* dma_rx_buffer;					/* DMA Receive Buffer. */
    uint16_t buffer_size;					/* DMA Receive Buffer Size. */
    uint32_t offset;							/* Offset specify. */
}CommUsartType;



void BSP_CommUsartInit(CommUsartType *hcomm, UART_HandleTypeDef *huart);
uint8_t BSP_CommUsartSendData(CommUsartType *hcomm, const uint8_t *data, uint16_t len);
bool BSP_CommUsartCanSendData(CommUsartType *hcomm);
bool BSP_CommUsartRecvData(CommUsartType *hcomm, uint8_t **pbuf, uint32_t* plen);
bool BSP_CommUsartRecvDataByLength(CommUsartType *hcomm, uint8_t *buf, uint32_t len, uint32_t timeout);
void BSP_CommUsartEnableIT(CommUsartType *hcomm, bool en);
HAL_StatusTypeDef BSP_UserUartTransmitDMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t tx_tc_flag);






#endif
