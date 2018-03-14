#ifndef __USART1_BSP_H__
#define __USART1_BSP_H__









void Comm1_Init(UART_HandleTypeDef *huart);
uint8_t Comm1_SendData(uint8_t * buff, uint16_t len);

void Comm1_RecceivePack(void);
int fputc(int ch, FILE *f);


#endif
