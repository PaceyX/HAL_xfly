#ifndef __MS5611_H__
#define __MS5611_H__




#define MS5611_CMD_RESET        0x1E 

#define CMD_ADC_READ            0x00 // ADC read command
#define CMD_ADC_CONV            0x40 // ADC conversion command
#define CMD_ADC_D1              0x00 // ADC D1 conversion
#define CMD_ADC_D2              0x10 // ADC D2 conversion
#define CMD_ADC_256             0x00 // ADC OSR=256
#define CMD_ADC_512             0x02 // ADC OSR=512
#define CMD_ADC_1024            0x04 // ADC OSR=1024
#define CMD_ADC_2048            0x06 // ADC OSR=2048
#define CMD_ADC_4096            0x08 // ADC OSR=4096

#define MS5611_CMD_PROM_BASE    0xA0 // Prom read command

#define MS5611_OSR							0x08	//CMD_ADC_4096



void MS5611_Init(void);







#endif

