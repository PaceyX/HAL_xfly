#ifndef __LED_BSP_H__
#define __LED_BSP_H__


#include "stm32f4xx_hal.h"




/******************************************************************************************/

#define 	CLK_H()			HAL_GPIO_WritePin(RGB_CLK_GPIO_Port,RGB_CLK_Pin, GPIO_PIN_SET)    
#define 	CLK_L()			HAL_GPIO_WritePin(RGB_CLK_GPIO_Port,RGB_CLK_Pin, GPIO_PIN_RESET)   

#define 	SDI_H()			HAL_GPIO_WritePin(RGB_SDI_GPIO_Port,RGB_SDI_Pin, GPIO_PIN_SET)
#define 	SDI_L() 		HAL_GPIO_WritePin(RGB_SDI_GPIO_Port,RGB_SDI_Pin, GPIO_PIN_RESET)

#define 	LE_H()			HAL_GPIO_WritePin(RGB_LE_GPIO_Port,RGB_LE_Pin, GPIO_PIN_SET)
#define 	LE_L()			HAL_GPIO_WritePin(RGB_LE_GPIO_Port,RGB_LE_Pin, GPIO_PIN_RESET)

#define 	Delay_us(num)	for(int i = num*10; i>0; i--)
#define 	Delay_ms(num)	HAL_Delay(num)




/********************************command list*********************************************/
#define 	command_WRITE_SWITCH 						0
#define 	command_DATA_LATCH 							1
#define 	command_GLOBAL_LATCH 						2
#define 	command_WRITE_CONFIGURATION 				3
#define 	command_READ_CONFIGURATION 					4
#define 	command_OPEN_ERROR_DETECTION 				5
#define 	command_SHORT_ERROR_DETECTION 				6
#define 	command_COMBINED_ERROR_DETECTION 			7
#define 	command_END_ERROR_DETECTION 				8
#define 	command_THERMAL_ERROR_READING 				9
#define 	command_NO_COMMAND 							10
#define 	NUMs_1642									0X1
#define 	LED1642_IC1
//#define 	LED1642_IC2
//#define 	LED1642_IC3



#define PWMresolution16         0x0000  //0xxx xxxx xxxx xxxx
#define PWMresolution12         0x8000  //8xxx xxxx xxxx xxxx
#define Default_PWMresolution   PWMresolution12   
//
#define GradualOpDelayEnable    0x0000  //x0xx xxxx xxxx xxxx
#define GradualOpDelayDisable   0x4000  //x1xx xxxx xxxx xxxx
#define DefaultGradualOpDelay   GradualOpDelayEnable
//
#define SDOdelayEnable          0x2000  //xx1x xxxx xxxx xxxx
#define SDOdelayDisable         0x0000  //xx0x xxxx xxxx xxxx
#define DefaultSDOdelay         SDOdelayDisable
//
#define RiseFallTime030n020     0x0000  //xxx0 0xxx xxxx xxxx
#define RiseFallTime100n040     0x0800  //xxx0 1xxx xxxx xxxx
#define RiseFallTime140n080     0x1000  //xxx1 0xxx xxxx xxxx
#define RiseFallTime180n150     0x1800  //xxx1 1xxx xxxx xxxx
#define DefaultRiseFallTime     RiseFallTime140n080
//
#define AutoShutdownEnable      0x0400  //xxxx x1xx xxxx xxxx
#define AutoShutdownDisable     0x0000  //xxxx x0xx xxxx xxxx
#define DefaultAutoShutdown     AutoShutdownDisable
//
#define DetectionThresh1p8V     0x0000  //xxxx xx00 xxxx xxxx
#define DetectionThresh2p5V     0x0100  //xxxx xx01 xxxx xxxx      
#define DetectionThresh3p0V     0x0200  //xxxx xx10 xxxx xxxx
#define DetectionThresh3p5V     0x0300  //xxxx xx11 xxxx xxxx
#define DefaultDetectionThresh  DetectionThresh3p5V
//
#define ErrDetectionMode        0x0000  //xxxx xxxx 0xxx xxxx
#define ReservedMode            0x0080  //xxxx xxxx 1xxx xxxx
#define DefaultErrMode          ReservedMode
//
#define LowCurrentRange         0x0000  //xxxx xxxx x0xx xxxx
#define HighCurrentRange        0x0040  //xxxx xxxx x1xx xxxx
#define DefaultCurrentRange     HighCurrentRange



void SendData(char command, unsigned short dat);
void LDI_UseNewLEDmap(unsigned short LEDmap[]);
void LEDs_ColorAdjust(unsigned char num, uint8_t Red_level, uint8_t Green_Level, uint8_t Blue_Level);
void LEDsSetConfig(void);

void bright_test(void);
void run_led_test(void);


#endif
