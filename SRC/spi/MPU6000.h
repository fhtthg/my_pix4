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


// MPU 6000 registers
#define MPUREG_WHOAMI			0x75

#define MPUREG_SMPLRT_DIV		0x19
#define MPUREG_CONFIG			0x1A
#define MPUREG_GYRO_CONFIG		0x1B
#define MPUREG_ACCEL_CONFIG		0x1C
#define MPUREG_FIFO_EN			0x23
#define MPUREG_INT_PIN_CFG		0x37
#define MPUREG_INT_ENABLE		0x38
#define MPUREG_INT_STATUS		0x3A
#define MPUREG_ACCEL_XOUT_H		0x3B
#define MPUREG_ACCEL_XOUT_L		0x3C
#define MPUREG_ACCEL_YOUT_H		0x3D
#define MPUREG_ACCEL_YOUT_L		0x3E
#define MPUREG_ACCEL_ZOUT_H		0x3F
#define MPUREG_ACCEL_ZOUT_L		0x40
#define MPUREG_TEMP_OUT_H		0x41
#define MPUREG_TEMP_OUT_L		0x42
#define MPUREG_GYRO_XOUT_H		0x43
#define MPUREG_GYRO_XOUT_L		0x44
#define MPUREG_GYRO_YOUT_H		0x45
#define MPUREG_GYRO_YOUT_L		0x46
#define MPUREG_GYRO_ZOUT_H		0x47
#define MPUREG_GYRO_ZOUT_L		0x48
#define MPUREG_USER_CTRL		0x6A
#define MPUREG_PWR_MGMT_1		0x6B
#define MPUREG_PWR_MGMT_2		0x6C
#define MPUREG_FIFO_COUNTH		0x72
#define MPUREG_FIFO_COUNTL		0x73
#define MPUREG_FIFO_R_W			0x74
#define MPUREG_PRODUCT_ID		0x0C
#define MPUREG_TRIM1			0x0D
#define MPUREG_TRIM2			0x0E
#define MPUREG_TRIM3			0x0F
#define MPUREG_TRIM4			0x10




#define MPU_CLKSEL_IN_8M_OSC    0x00
#define MPU_CLKSEL_X_AXIS       0x01
#define MPU_CLKSEL_Y_AXIS       0x02
#define MPU_CLKSEL_Z_AXIS       0x03
#define MPU_CLKSEL_EX_32768_OSC 0x04
#define MPU_CLKSEL_EX_19M2_OSC  0x05
#define MPU_CLKSEL_STOP         0x07



typedef struct {
	int32_t timestamp;
	int16_t accel_x_raw;
	int16_t accel_y_raw;
	int16_t accel_z_raw;
	int16_t temperature_raw;
    int16_t gyro_x_raw;
	int16_t gyro_y_raw;
	int16_t gyro_z_raw;
    uint8_t flag;
}MPU_report;




void MPU6000_Init(void);

void MPU6000_INT_ENABLE(void);

void MPU6000_INT_DISABLE(void);

void MPU6000_CS_ENABLE(void);
void MPU6000_CS_DISABLE(void);
uint8_t MPU6000_RW(uint8_t TxData);
void MPU6000_SET(uint8_t setAddr,uint8_t setData);

void MPU6000_CS_ENABLE(void);
void MPU6000_CS_DISABLE(void);
void EXTI15_10_IRQHandler(void);
void SPI_MPU_Read(uint8_t *Buffer, uint8_t ReadAddr,uint8_t NumByteToRead);
void MPU6000_RAW_READY(MPU_report *pMPU_report);










#endif // __MPU6000_H
