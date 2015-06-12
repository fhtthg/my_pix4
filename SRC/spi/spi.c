

#include "spi.h"


SPI_HandleTypeDef Spi1Handle;


void SPI1_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    SPI1_GPIO_CLK_ENABLE();
    SPI1_CLK_ENABLE();

    /* SPI SCK GPIO pin configuration  */
    GPIO_InitStruct.Pin       = SPI1_SCK_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = SPI1_SCK_AF;
    HAL_GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);

    /* SPI MISO GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPI1_MISO_PIN;
    GPIO_InitStruct.Alternate = SPI1_MISO_AF;

    HAL_GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);

    /* SPI MOSI GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPI1_MOSI_PIN;
    GPIO_InitStruct.Alternate = SPI1_MOSI_AF;
    HAL_GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStruct);

    //
    HAL_GPIO_WritePin(SPI1_SCK_GPIO_PORT, SPI1_SCK_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SPI1_MISO_GPIO_PORT, SPI1_MISO_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SPI1_MOSI_GPIO_PORT, SPI1_MOSI_PIN, GPIO_PIN_SET);

    /*##-3- Configure the NVIC for SPI #########################################*/
   // HAL_NVIC_SetPriority(SPI1_IRQn, 4, 0);
   // HAL_NVIC_EnableIRQ(SPI1_IRQn);


    Spi1Handle.Instance               = SPI1;
    Spi1Handle.Init.Direction         = SPI_DIRECTION_2LINES;   // 双线模式
    Spi1Handle.Init.Mode              = SPI_MODE_MASTER;        // 主
    Spi1Handle.Init.DataSize          = SPI_DATASIZE_8BIT;      // 8位模式

    Spi1Handle.Init.CLKPolarity       = SPI_POLARITY_HIGH;       // 时钟空闲模式高电平
    Spi1Handle.Init.CLKPhase          = SPI_PHASE_2EDGE;        //
    Spi1Handle.Init.NSS               = SPI_NSS_SOFT;           // 软件片选模式
    // 84M/128= 656.25KHz
    Spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    Spi1Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;       //最高位优先
    Spi1Handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED; //关CRC
    Spi1Handle.Init.CRCPolynomial     = 7;                          //
    Spi1Handle.Init.TIMode            = SPI_TIMODE_DISABLED;    //Ti通信模式

    HAL_SPI_Init(&Spi1Handle);
    __HAL_SPI_ENABLE(&Spi1Handle);     // 启动 SPI1 外设


}


void SPI1_SENSORS_CTRL_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    GYRO_CS_CLK_ENABLE();
    ACCEL_MAG_CS_CLK_ENABLE();
    BARO_CS_CLK_ENABLE();

    // L3GD20
    GPIO_InitStruct.Pin       = GYRO_CS_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GYRO_CS_PORT, &GPIO_InitStruct);

    // LSM303D
    GPIO_InitStruct.Pin       = ACCEL_MAG_CS_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(ACCEL_MAG_CS_PORT, &GPIO_InitStruct);

    // MS5611
    GPIO_InitStruct.Pin       = BARO_CS_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(BARO_CS_PORT, &GPIO_InitStruct);

}



void SENSORS_INT_ON()
{




}


void SENSORS_INT_OFF()
{




}




