#ifndef __UART5_BSP_H__
#define __UART5_BSP_H__





bool Comm5_Init(UART_HandleTypeDef *huart);
u8 Comm5_SendData(u8 *data, u16 len);


void UART5_RxIRQCallback(void);











#endif
