#ifndef __IIC_BSP_H__
#define __IIC_BSP_H__

#include "global_define.h"



HAL_StatusTypeDef BSP_IICMemoryRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, 
        uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef BSP_IICMemoryWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, 
        uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef BSP_IICMemoryWriteByDMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef BSP_IICMemoryReadByDMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);














#endif
