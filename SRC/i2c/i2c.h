#ifndef __I2C_H
#define __I2C_H

#include "stm32f4xx_hal.h"

#include "stm32f4xx_hal_conf.h"


#define    I2C2_SCL_GPIO_CLK_ENABLE()       __GPIOB_CLK_ENABLE()
#define    I2C2_SDA_GPIO_CLK_ENABLE()       __GPIOB_CLK_ENABLE()
#define    I2C2_CLK_ENABLE()                __I2C2_CLK_ENABLE()

#define    I2C2_SCL_PIN                     GPIO_PIN_10
#define    I2C2_SCL_PORT                    GPIOB
#define    I2C2_SCL_AF                      GPIO_AF4_I2C2

#define    I2C2_SDA_PIN                     GPIO_PIN_11
#define    I2C2_SDA_PORT                    GPIOB
#define    I2C2_SDA_AF                      GPIO_AF4_I2C2



void I2C2_Init(void);



#endif // __i2c_H

