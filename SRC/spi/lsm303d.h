#ifndef __LSM303D_H
#define __LSM303D_H

#include "stm32f4xx_hal_conf.h"
#include <stdio.h>


typedef struct {
	int32_t timestamp;
	int16_t accel_x_raw;
	int16_t accel_y_raw;
	int16_t accel_z_raw;
	int16_t temperature_raw;
    uint8_t flag;
}LSM303D_ACC_report;


typedef struct {
	int32_t timestamp;
	int16_t mag_x_raw;
	int16_t mag_y_raw;
	int16_t mag_z_raw;
	int16_t temperature_raw;
    uint8_t flag;
}LSM303D_MAG_report;




#define LSM303D_CS_PIN                      GPIO_PIN_15
#define LSM303D_CS_PORT                     GPIOC
#define LSM303D_CS_CLK_ENABLE()             __GPIOC_CLK_ENABLE()

#define LSM303D_ACC_DRDY_PIN                GPIO_PIN_4
#define LSM303D_ACC_DRDY_PORT               GPIOB
#define LSM303D_ACC_DRDY_CLK_ENABLE()       __GPIOB_CLK_ENABLE()

#define LSM303D_MAG_DRDY_PIN                GPIO_PIN_1
#define LSM303D_MAG_DRDY_PORT               GPIOB
#define LSM303D_MAG_DRDY_CLK_ENABLE()       __GPIOB_CLK_ENABLE()



#define LSM303D_OUT_TEMP_L			        0x05
#define LSM303D_OUT_TEMP_H			        0x06
#define LSM303D_STATUS_M			        0x07
#define LSM303D_OUT_X_L_M          	        0x08
#define LSM303D_OUT_X_H_M          	        0x09
#define LSM303D_OUT_Y_L_M          	        0x0A
#define LSM303D_OUT_Y_H_M		    	    0x0B
#define LSM303D_OUT_Z_L_M			        0x0C
#define LSM303D_OUT_Z_H_M			        0x0D





#define LSM303D_INT_CTRL_M			        0x12
#define LSM303D_INT_SRC_M			        0x13

#define LSM303D_REG_CTRL0                   0x1F
#define LSM303D_REG_CTRL1                   0x20
#define LSM303D_REG_CTRL2                   0x21
#define LSM303D_REG_CTRL3                   0x22
#define LSM303D_REG_CTRL4                   0x23
#define LSM303D_REG_CTRL5                   0x24
#define LSM303D_REG_CTRL6                   0x25
#define LSM303D_REG_CTRL7                   0x26



#define LSM303D_STATUS_A			        0x27
#define LSM303D_OUT_X_L_A			        0x28
#define LSM303D_OUT_X_H_A			        0x29
#define LSM303D_OUT_Y_L_A			        0x2A
#define LSM303D_OUT_Y_H_A			        0x2B
#define LSM303D_OUT_Z_L_A			        0x2C
#define LSM303D_OUT_Z_H_A			        0x2D


///////////////////////////////////////////////////////////////////
#define REG1_RATE_BITS_A		((1<<7) | (1<<6) | (1<<5) | (1<<4))
#define REG1_POWERDOWN_A		((0<<7) | (0<<6) | (0<<5) | (0<<4))
#define REG1_RATE_3_125HZ_A		((0<<7) | (0<<6) | (0<<5) | (1<<4))
#define REG1_RATE_6_25HZ_A		((0<<7) | (0<<6) | (1<<5) | (0<<4))
#define REG1_RATE_12_5HZ_A		((0<<7) | (0<<6) | (1<<5) | (1<<4))
#define REG1_RATE_25HZ_A		((0<<7) | (1<<6) | (0<<5) | (0<<4))
#define REG1_RATE_50HZ_A		((0<<7) | (1<<6) | (0<<5) | (1<<4))
#define REG1_RATE_100HZ_A		((0<<7) | (1<<6) | (1<<5) | (0<<4))
#define REG1_RATE_200HZ_A		((0<<7) | (1<<6) | (1<<5) | (1<<4))
#define REG1_RATE_400HZ_A		((1<<7) | (0<<6) | (0<<5) | (0<<4))
#define REG1_RATE_800HZ_A		((1<<7) | (0<<6) | (0<<5) | (1<<4))
#define REG1_RATE_1600HZ_A		((1<<7) | (0<<6) | (1<<5) | (0<<4))

#define REG1_BDU_UPDATE			(1<<3)
#define REG1_Z_ENABLE_A			(1<<2)
#define REG1_Y_ENABLE_A			(1<<1)
#define REG1_X_ENABLE_A			(1<<0)

#define REG2_ANTIALIAS_FILTER_BW_BITS_A	((1<<7) | (1<<6))
#define REG2_AA_FILTER_BW_773HZ_A		((0<<7) | (0<<6))
#define REG2_AA_FILTER_BW_194HZ_A		((0<<7) | (1<<6))
#define REG2_AA_FILTER_BW_362HZ_A		((1<<7) | (0<<6))
#define REG2_AA_FILTER_BW_50HZ_A		((1<<7) | (1<<6))

#define REG2_FULL_SCALE_BITS_A	((1<<5) | (1<<4) | (1<<3))
#define REG2_FULL_SCALE_2G_A	((0<<5) | (0<<4) | (0<<3))
#define REG2_FULL_SCALE_4G_A	((0<<5) | (0<<4) | (1<<3))
#define REG2_FULL_SCALE_6G_A	((0<<5) | (1<<4) | (0<<3))
#define REG2_FULL_SCALE_8G_A	((0<<5) | (1<<4) | (1<<3))
#define REG2_FULL_SCALE_16G_A	((1<<5) | (0<<4) | (0<<3))

#define REG5_ENABLE_T			(1<<7)

#define REG5_RES_HIGH_M			((1<<6) | (1<<5))
#define REG5_RES_LOW_M			((0<<6) | (0<<5))

#define REG5_RATE_BITS_M		((1<<4) | (1<<3) | (1<<2))
#define REG5_RATE_3_125HZ_M		((0<<4) | (0<<3) | (0<<2))
#define REG5_RATE_6_25HZ_M		((0<<4) | (0<<3) | (1<<2))
#define REG5_RATE_12_5HZ_M		((0<<4) | (1<<3) | (0<<2))
#define REG5_RATE_25HZ_M		((0<<4) | (1<<3) | (1<<2))
#define REG5_RATE_50HZ_M		((1<<4) | (0<<3) | (0<<2))
#define REG5_RATE_100HZ_M		((1<<4) | (0<<3) | (1<<2))
#define REG5_RATE_DO_NOT_USE_M	((1<<4) | (1<<3) | (0<<2))

#define REG6_FULL_SCALE_BITS_M	((1<<6) | (1<<5))
#define REG6_FULL_SCALE_2GA_M	((0<<6) | (0<<5))
#define REG6_FULL_SCALE_4GA_M	((0<<6) | (1<<5))
#define REG6_FULL_SCALE_8GA_M	((1<<6) | (0<<5))
#define REG6_FULL_SCALE_12GA_M	((1<<6) | (1<<5))


#define REG7_CONT_MODE_M		((0<<1) | (0<<0))


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void LSM303D_Init(void);
void LSM303D_CS_ENABLE(void);
void LSM303D_CS_DISABLE(void);
uint8_t LSM303D_RW(uint8_t TxData);
void LSM303D_SET(uint8_t setAddr,uint8_t setData);
void EXTI4_IRQHandler(void);
void LSM303D_SPI_Read(uint8_t *Buffer, uint8_t ReadAddr,uint8_t NumByteToRead);
void LSM303D_ACC_READY(LSM303D_ACC_report *pLSM303D_ACC_report);

void LSM303D_MAG_READY(LSM303D_MAG_report *pLSM303D_MAG_report);

#endif  // __LSM303D_H

