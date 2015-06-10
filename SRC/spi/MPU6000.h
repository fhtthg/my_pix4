#ifndef __MPU6000_H
#define __MPU6000_H



#include "stm32f4xx_hal_conf.h"
#include <stdio.h>


#define MPU_CS_PIN                      GPIO_PIN_2
#define MPU_CS_PORT                     GPIOC
#define MPU_CS_CLK_ENABLE()             __GPIOC_CLK_ENABLE()

#define MPU_DRDY_PIN                    GPIO_PIN_15
#define MPU_DRDY_PORT                   GPIOD
#define MPU_DRDY_CLK_ENABLE()           __GPIOD_CLK_ENABLE()



#define MPU6000_RA_SMPRT_DIV            0x19
#define MPU6000_RA_CONFIG               0x1A
#define MPU6000_RA_GYRO_CONFIG          0x1B
#define MPU6000_RA_ACCEL_CONFIG         0x1C
#define MPU6000_RA_INT_PIN_CFG          0x37
#define MPU6000_RA_INT_ENABLE           0x38
#define MPU6000_RA_ACCEL_XOUT_H         0x3B
#define MPU6000_RA_USER_CTRL            0x6A
#define MPU6000_RA_PWR_MGMT_1           0x6B


void MPU6000_Init(void);
void MPU6000_CS_ENABLE(void);
void MPU6000_CS_DISABLE(void);
uint8_t MPU6000_RW(uint8_t TxData);
void MPU6000_Reset(uint8_t date);
void MPU6000_setClockSource(uint8_t source);   //…Ë÷√ ±÷”‘¥
void MPU6000_SPIEnabled(uint8_t enabled);
void MPU6000_setSampleRateDIV(uint8_t rate);
void MPU6000_setDLPH(uint8_t rate);
void MPU6000_setFullScaleGyroRange(uint8_t range);
void MPU6000_setFullScaleAccelRange(uint8_t range);
void MPU6000_setITMode(uint8_t mode);
void MPU6000_ITEnabled(uint8_t enabled);
void MPU6000_CS_ENABLE(void);
void MPU6000_CS_DISABLE(void);
void EXTI15_10_IRQHandler(void);
void SPI_MPU_Read(uint8_t *Buffer, uint8_t ReadAddr,uint8_t NumByteToRead);
void MPU6000_newValues(int16_t accelx,int16_t accely,int16_t accelz, int16_t gyrox,int16_t gyroy,int16_t gyroz);
void MPU6000_RAW_READY(int16_t *accx, int16_t *accy, int16_t *accz, int16_t *gyrx, int16_t *gyry, int16_t *gyrz);
void delay_us(void);


#endif // __MPU6000_H
