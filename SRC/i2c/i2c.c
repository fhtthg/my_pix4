
#include  "i2c.h"



I2C_HandleTypeDef I2c2Handle;



void I2C2_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    I2C2_SCL_GPIO_CLK_ENABLE();
    I2C2_SDA_GPIO_CLK_ENABLE();
    I2C2_CLK_ENABLE();

    GPIO_InitStruct.Pin       = I2C2_SCL_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = I2C2_SCL_AF;
    HAL_GPIO_Init(I2C2_SCL_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2C2_SDA_PIN;
    GPIO_InitStruct.Alternate = I2C2_SDA_AF;
    HAL_GPIO_Init(I2C2_SDA_PORT, &GPIO_InitStruct);


    I2c2Handle.Instance             = I2C2;
    I2c2Handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    I2c2Handle.Init.ClockSpeed      = 100000;
    I2c2Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    I2c2Handle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    I2c2Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    I2c2Handle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLED;
    I2c2Handle.Init.OwnAddress1     = 0xAA; // Tca62724 默认初始地址
 //   I2c2Handle.Init.OwnAddress2     = 0x81; // Tca62724 默认初始地址
    HAL_I2C_Init(&I2c2Handle);





}

