#ifndef __USART3_BSP_H__
#define __USART3_BSP_H__





void Comm3_Init(UART_HandleTypeDef *huart);
uint8_t Comm3_SendData(uint8_t * buff, uint16_t len);
void Comm3_RecceivePack(void);











#endif
