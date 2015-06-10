#ifndef __SPI_H
#define __SPI_H


#include "stm32f4xx_hal_conf.h"

#define SPI1_CLK_ENABLE()                __SPI1_CLK_ENABLE()
#define SPI1_GPIO_CLK_ENABLE()           __GPIOA_CLK_ENABLE()

#define SPI1_FORCE_RESET()               __SPI1_FORCE_RESET()
#define SPI1_RELEASE_RESET()             __SPI1_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPI1_SCK_PIN                     GPIO_PIN_5
#define SPI1_SCK_GPIO_PORT               GPIOA
#define SPI1_SCK_AF                      GPIO_AF5_SPI1

#define SPI1_MISO_PIN                    GPIO_PIN_6
#define SPI1_MISO_GPIO_PORT              GPIOA
#define SPI1_MISO_AF                     GPIO_AF5_SPI1

#define SPI1_MOSI_PIN                    GPIO_PIN_7
#define SPI1_MOSI_GPIO_PORT              GPIOA
#define SPI1_MOSI_AF                     GPIO_AF5_SPI1


////////////////////////////
// 传感器引脚--- 片选配置为输出 低有效
//            -- DRDY为中断引脚  上升沿中断
////////////////////////////
#define GYRO_CS_PIN                     GPIO_PIN_13
#define GYRO_CS_PORT                    GPIOC
#define GYRO_CS_CLK_ENABLE()            __GPIOC_CLK_ENABLE()


#define GYRO_DRDY_PIN                   GPIO_PIN_0
#define GYRO_DRDY_PORT                  GPIOB
#define GYRO_DRDY_CLK_ENABLE()          __GPIOC_CLK_ENABLE()




#define ACCEL_MAG_CS_PIN                GPIO_PIN_15
#define ACCEL_MAG_CS_PORT               GPIOC
#define ACCEL_MAG_CS_CLK_ENABLE()       __GPIOC_CLK_ENABLE()



#define ACCEL_DRDY_PIN                  GPIO_PIN_4
#define ACCEL_DRDY_PORT                 GPIOB
#define ACCEL_DRDY_CLK_ENABLE()         __GPIOB_CLK_ENABLE()

#define MAG_DRDY_PIN                    GPIO_PIN_1
#define MAG_DRDY_PORT                   GPIOB
#define MAG_DRDY_CLK_ENABLE()           __GPIOB_CLK_ENABLE()






#define BARO_CS_PIN                     GPIO_PIN_7
#define BARO_CS_PORT                    GPIOD
#define BARO_CS_CLK_ENABLE()            __GPIOD_CLK_ENABLE()



////////////////////////////////
//
////////////////////////////////





void SPI1_Init(void);
void SPI1_SENSORS_CTRL_Init(void);

#endif

