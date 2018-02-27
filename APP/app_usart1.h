#ifndef __APP_USART1_H__
#define __APP_USART1_H__




typedef struct
{
	uint16_t offset;		/* Accumulate the received data and find frame head. */
	u8 * buffer;
	u16 size;
}Comm1_FrameType;




void Comm1_Init(UART_HandleTypeDef *huart);
uint8_t Comm1_SendData(uint8_t * buff, uint16_t len);

void Comm1_RecceivePack(void);



#endif
