#include "stm32f4xx_hal.h"
#include "app_imu.h"
#include "max21100.h"
#include "hmc5983.h"



volatile float q0, q1, q2, q3; 		/* ȫ����Ԫ�� */
volatile float qa0, qa1, qa2, qa3;
volatile float exInt, eyInt, ezInt;  // ������
volatile float integralFBx, integralFBy, integralFBz;
volatile uint32_t lastUpdate, now; // �������ڼ��� ��λ us

void IMU_Init(void)
{
	volatile float temp, roll, pitch, yaw, yh, xh;
	uint8_t data_size = 100;
	
	// initialize quaternion
    q0 = 1.0f;  //��ʼ����Ԫ��
    q1 = 0.0f;
    q2 = 0.0f;
    q3 = 0.0f;
    qa0 = 1.0f;  //��ʼ����Ԫ��
    qa1 = 0.0f;
    qa2 = 0.0f;
    qa3 = 0.0f;
    exInt = 0.0;
    eyInt = 0.0;
    ezInt = 0.0;
    integralFBx = 0.0;
    integralFBy = 0.0;
    integralFBz	= 0.0;
	
	lastUpdate = HAL_GetTick();		/* ����ʱ�� */
	now = HAL_GetTick();
	
	/* �ü��ٶȺ����̳�ʼ����Ԫ�� */
	for(int i = 0; i < data_size; i++)
	{
		HAL_Delay(3);
		MAX21100_UpdateData();
	}
}

