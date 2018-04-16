#ifndef __MS5611_H__
#define __MS5611_H__


typedef struct{
	int32_t pressure;		/* Unit : Pa. */
	int32_t temperature;	/* Unit : .C. */
	float height;
}MS5611TypeDef;

extern MS5611TypeDef MS5611;

/* CS Config. */
#define MS_CS_ENABLE	HAL_GPIO_WritePin(MS_CS_GPIO_Port, MS_CS_Pin, GPIO_PIN_RESET)
#define MS_CS_DISABLE	HAL_GPIO_WritePin(MS_CS_GPIO_Port, MS_CS_Pin, GPIO_PIN_SET)

/* Command. */
#define CMD_RESET			0x1E
#define CMD_D1_OSR_256		0x40
#define CMD_D1_OSR_512		0x42
#define CMD_D1_OSR_1024		0x44
#define CMD_D1_OSR_2048		0x46
#define CMD_D1_OSR_4096		0x48
#define CMD_D2_OSR_256		0x50
#define CMD_D2_OSR_512		0x52
#define CMD_D2_OSR_1024		0x54
#define CMD_D2_OSR_2048		0x56
#define CMD_D2_OSR_4096		0x58
#define CMD_ADC_24_BITS		0x00
#define CMD_PROM_BASE		0xA0
#define CMD_PROM_FACTORY	0xA0
#define CMD_PROM_SENS		0xA2
#define CMD_PROM_OFF		0xA4
#define CMD_PROM_TCS		0xA6
#define CMD_PROM_TCO		0xA8
#define CMD_PROM_TREF		0xAA
#define CMD_PROM_TEMPSENS	0xAC
#define CMD_PROM_CRC		0xAE


void MS5611_Init(void);
void MS5611_UpdateData(void);

#endif
