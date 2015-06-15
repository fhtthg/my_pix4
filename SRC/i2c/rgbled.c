

#include    "rgbled.h"



extern I2C_HandleTypeDef I2c2Handle;


void RGBLED_Init(void)
{
    uint8_t aTxBuffer[5];

    // 蓝色最低亮度
    aTxBuffer[0]=0x01,  //地址 连续开
    aTxBuffer[1]=0x01,  // 蓝
    aTxBuffer[2]=0x00,  // 绿
    aTxBuffer[3]=0x00,  // 红
    aTxBuffer[4]=0x03,  // 开关

    HAL_I2C_Master_Transmit(&I2c2Handle,
     (uint16_t)0xAA, (uint8_t*)aTxBuffer, 5, 10000);
}


