#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__






#define TRIG_SET_LOW		HAL_GPIO_WritePin(ULTR_TRIG_GPIO_Port, ULTR_TRIG_Pin, GPIO_PIN_RESET);
#define TRIG_SET_HIGH		HAL_GPIO_WritePin(ULTR_TRIG_GPIO_Port, ULTR_TRIG_Pin, GPIO_PIN_SET);
#define READ_ECHO_PIN		HAL_GPIO_ReadPin(ULTR_ECHO_GPIO_Port, ULTR_ECHO_Pin)	


void ultraDistanceSampling(void);
void ultrasonicCallBack(void);
void BSP_GPIO_SonicInit(void);







#endif
