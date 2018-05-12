#ifndef __W25Q32_H__
#define __W25Q32_H__


typedef struct{
	uint8_t manufacturer;
	uint8_t memory;
	uint8_t capacity;
} ExtraFlashTypedef;

extern ExtraFlashTypedef W25Q;

typedef struct
{
    uint8_t initialized;
    uint16_t sector_size;
    uint16_t sector_count;
    uint32_t capacity;
} FlashInfoTypefdef;


#define W25Q_CS_Enable		HAL_GPIO_WritePin(W25Q_NSS_GPIO_Port, W25Q_NSS_Pin, GPIO_PIN_RESET)
#define W25Q_CS_Disable		HAL_GPIO_WritePin(W25Q_NSS_GPIO_Port, W25Q_NSS_Pin, GPIO_PIN_SET)

#define W25Q_MANUFACTORER_ID	0xEF

/* Register. */
#define W25Q_WRITE_ENABLE	0x06
#define	W25Q_WRITE_DISABLE	0x04
#define W25Q_READ_STATUS	0X05
#define W25Q_WRITE_STATUS	0X01
#define W25Q_READ_DATA		0x03
#define W25Q_FAST_READ		0x0B
#define W25Q_DEVICE_ID		0x9F
#define W25Q_PAGE_WRITE		0x02
#define W25Q_SECTOR_ERASE	0x20

/* Status - bit. */
#define W25Q_STATUS_BUSY	0x01
#define W25Q_STATUS_WRITE_PROTECT	0x02
#define W25Q_STATUS_BP0		0x04
#define W25Q_STATUS_BP1		0x08
#define W25Q_STATUS_BP2		0x10
#define W25Q_STATUS_TP		0x20
#define W25Q_STATUS_SEC		0x40
#define W25Q_STATUS_SRP0	0x80

/* Dummy Byte. */
#define W25Q_DUMMY_BYTE		0xFF

#define JEDEC_W25Q32_DW     (0x6016) /* W25Q32DW */


void W25Q_Init(void);
void flash_test(void);











#endif
