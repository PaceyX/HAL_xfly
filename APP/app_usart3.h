#ifndef __APP_USART3_H__
#define __APP_USART3_H__


typedef struct
{
	uint16_t offset;		/* Accumulate the received data and find frame head. */
	uint8_t * buffer;
	uint16_t size;
}Comm3_FrameType;


void Comm3_Init(UART_HandleTypeDef *huart);
void Comm3_RecceivePack(void);

void uCommWithBoard_Task(void);










#endif
