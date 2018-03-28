#ifndef __MAX21100_H__
#define __MAX21100_H__


//extern DofTypeDef gyro;
//extern DofTypeDef acc;



//Common 
#define MAX_DEVICE_ID		0x20
#define MAX_REVISION_ID		0x21
#define MAX_BANK_SELECT		0x22
#define MAX_SYSTEM_STATUS	0x23
#define MAX_GYRO_X_H		0x24
#define MAX_GYRO_X_L		0x25
#define MAX_GYRO_Y_H		0x26
#define MAX_GYRO_Y_L		0x27
#define MAX_GYRO_Z_H		0x28
#define MAX_GYRO_Z_L		0x29
#define MAX_ACC_X_H			0x2A
#define MAX_ACC_X_L			0x2B
#define MAX_ACC_Y_H			0x2C
#define MAX_ACC_Y_L			0x2D
#define MAX_ACC_Z_H			0x2E
#define MAX_ACC_Z_L			0x2F
#define MAX_TEMP_H			0x36
#define MAX_TEMP_L			0x37
#define MAX_FIFO_COUNT		0x3C
#define MAX_FIFO_STATUS		0x3D
#define MAX_FIFO_DATA		0x3E
#define MAX_RST_REG			0x3F



//BANK0
#define MAX21100_POWER_CFG      		0x00 
#define MAX21100_GYRO_CFG1      		0x01 
#define MAX21100_GYRO_CFG2      		0x02 
#define MAX21100_GYRO_CFG3      		0x03 
#define MAX21100_PWR_ACC_CFG      	0x04 
#define MAX21100_ACC_CFG1      			0x05 
#define MAX21100_ACC_CFG2        		0x06 
#define MAX21100_MAG_SLV_CFG     		0x07
#define MAX21100_MAG_SLV_ADD        0x08 
#define MAX21100_MAG_SLV_REG     		0x09
#define MAX21100_MAG_MAP_REG        0x0A 
#define MAX21100_I2C_MST_ADD     		0x0B
#define MAX21100_I2C_MST_DATA    		0x0C 
#define MAX21100_MAG_OFS_X_MSB     	0x0D
#define MAX21100_MAG_OFS_X_LSB     	0x0E
#define MAX21100_MAG_OFS_Y_MSB     	0x0F
#define MAX21100_MAG_OFS_Y_LSB     	0x10 
#define MAX21100_MAG_OFS_Z_MSB     	0x11
#define MAX21100_MAG_OFS_Z_LSB     	0x12
#define MAX21100_DR_CFG           	0x13
#define MAX21100_IO_CFG      				0x14
#define MAX21100_I2C_PAD     				0x15
#define MAX21100_I2C_CFG           	0x16
#define MAX21100_FIFO_TH           	0x17
#define MAX21100_FIFO_CFG          	0x18
#define MAX21100_DSYNC_CFG     			0x1A
#define MAX21100_DSYNC_CNT     			0x1B
#define MAX21100_ITF_OTP          	0x1C

#define MAX21100_POWER_CFG_DATA       0x7F    
#define MAX21100_I2C_CFG_DATA          0X01




void Max21100_Init(void);
void MAX21100_UpdateData(void);





#endif

