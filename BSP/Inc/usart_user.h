#ifndef __USART_USER_H__
#define __USART_USER_H__

#include "global_define.h"
#include <stdbool.h>

/******************************************************************************/
/*								USART1										  */
/******************************************************************************/

void Comm1_Init(UART_HandleTypeDef *huart);
uint8_t Comm1_SendData(uint8_t * buff, uint16_t len);

void Comm1_RecceivePack(void);
int fputc(int ch, FILE *f);



/******************************************************************************/
/*								USART3										  */
/******************************************************************************/
void Comm3_Init(UART_HandleTypeDef *huart);
uint8_t Comm3_SendData(uint8_t * buff, uint16_t len);
void Comm3_RecceivePack(void);



/******************************************************************************/
/*								UART5 										  */
/******************************************************************************/
bool Comm5_Init(UART_HandleTypeDef *huart);
u8 Comm5_SendData(u8 *data, u16 len);
void UART5_RxIRQCallback(void);



#endif
