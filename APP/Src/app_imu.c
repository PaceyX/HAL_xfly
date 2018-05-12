#include "stm32f4xx_hal.h"
#include "app_imu.h"
#include "max21100.h"
#include "hmc5983.h"



volatile float q0, q1, q2, q3; 		/* 全局四元数 */
volatile float qa0, qa1, qa2, qa3;
volatile float exInt, eyInt, ezInt;  // 误差积分
volatile float integralFBx, integralFBy, integralFBz;
volatile uint32_t lastUpdate, now; // 采样周期计数 单位 us

void IMU_Init(void)
{
	volatile float temp, roll, pitch, yaw, yh, xh;
	uint8_t data_size = 100;
	
	// initialize quaternion
    q0 = 1.0f;  //初始化四元数
    q1 = 0.0f;
    q2 = 0.0f;
    q3 = 0.0f;
    qa0 = 1.0f;  //初始化四元数
    qa1 = 0.0f;
    qa2 = 0.0f;
    qa3 = 0.0f;
    exInt = 0.0;
    eyInt = 0.0;
    ezInt = 0.0;
    integralFBx = 0.0;
    integralFBy = 0.0;
    integralFBz	= 0.0;
	
	lastUpdate = HAL_GetTick();		/* 更新时间 */
	now = HAL_GetTick();
	
	/* 用加速度和罗盘初始化四元数 */
	for(int i = 0; i < data_size; i++)
	{
		HAL_Delay(3);
		MAX21100_UpdateData();
	}
}

