#ifndef __PWM_BSP_H__
#define __PWM_BSP_H__


/*********************************************************/
/*
PWM_IN1		PWM_IN2		PWM_IN3		PWM_IN4
T3C1		T3C2		T3C3		T3C4

PWM_IN5		PWM_IN6		PWM_IN7		PWM_IN8
T4C1		T4C2		T4C3		T4C4

*/
/*********************************************************/


void BSP_PWMChannelStart(void);

void PWM_IN_Init(void);
void TIM3_RxCallBack(void);
void TIM4_RxCallBack(void);






#endif
