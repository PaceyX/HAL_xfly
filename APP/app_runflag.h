#ifndef __APP_RUNFLAG_H__
#define __APP_RUNFLAG_H__





typedef struct{
	uint32_t Ms1Cnt;
	uint32_t Ms3Cnt;
    uint32_t Ms4Cnt;
	uint32_t Ms20Cnt;
	uint32_t Ms80Cnt;
    uint32_t Ms100Cnt;
    uint32_t Ms250Cnt;
    uint32_t Ms500Cnt;
    uint32_t Ms1000Cnt;
    uint8_t Ms1;
	uint8_t Ms3;
    uint8_t Ms4;
    uint8_t Ms20;
	uint8_t Ms80;
    uint8_t Ms100;
    uint8_t Ms250;
    uint8_t Ms500;
    uint8_t Ms1000;
}SYSFlagType;
extern SYSFlagType RunFlag;

void RunFlagInit(void);
void RunFlagHandleTask(void);













#endif
