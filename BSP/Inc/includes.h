#ifndef __INCLUDES_H__
#define __INCLUDES_H__



/************************************STD***************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>





/************************************HAL***************************************/
#include "stm32f4xx_hal.h"

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"



/************************************APP***************************************/
#include "global_define.h"
#include "bsp.h"
#include "app_runflag.h"
#include "app_timer.h"




/************************************BSP***************************************/
#include "usart_bsp.h"
#include "pwm_bsp.h"
#include "usart1_bsp.h"
#include "usart3_bsp.h"
#include "uart5_bsp.h"
#include "hmc5983.h"


#endif
