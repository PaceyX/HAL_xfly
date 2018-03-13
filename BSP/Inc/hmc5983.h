#ifndef __HMC5983_H__
#define __HMC5983_H__




#define HMC5983_ADDRESS         0x3C

// Register
#define HMC5983_CFG_A			0x00
#define HMC5983_CFG_B			0x01 
#define HMC5983_MODE 			0x02
#define HMC5983_X_M 			0x03
#define HMC5983_X_L 			0x04 
#define HMC5983_Z_M   		0x05
#define HMC5983_Z_L   		0x06
#define HMC5983_Y_M  			0x07
#define HMC5983_Y_L   		0x08 
#define HMC5983_STATUS 		0x09
#define HMC5983_ID_A			0x0A
#define HMC5983_ID_B			0x0B
#define HMC5983_ID_C			0x0C
#define HMC5983_TEMP_M		0x31
#define HMC5983_TEMP_L		0x32





void HMC5983_Init(void);











#endif

