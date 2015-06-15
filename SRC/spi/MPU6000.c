


#include "MPU6000.h"
#include "stm32f4xx.h"
#include "main.h"



MPU_report  MPU_report1;
extern SPI_HandleTypeDef Spi1Handle;
uint16_t    MPU_RD_CNT;


void MPU6000_Init(void)
{
    // IO初始化
    GPIO_InitTypeDef  GPIO_InitStruct;

    //MPU6000  片选IO
    MPU_CS_CLK_ENABLE();
    GPIO_InitStruct.Pin       = MPU_CS_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(MPU_CS_PORT, &GPIO_InitStruct);
    MPU6000_CS_DISABLE();

    //MPU6000 DRDY引脚 --外部中断 上升沿触发
    MPU_DRDY_CLK_ENABLE();
    GPIO_InitStruct.Pin       = MPU_DRDY_PIN;       // GPIO15 入口有讲究 需注意
    GPIO_InitStruct.Mode      = GPIO_MODE_IT_RISING; // 中断模式 上升沿中断
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(MPU_DRDY_PORT, &GPIO_InitStruct);

    //外部中断初始化
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 4, 0); // 设置外部引脚中断
    MPU6000_INT_ENABLE();


    //寄存器初始化
    MPU6000_SET(MPUREG_PWR_MGMT_1,0x80);        // 复位
    HAL_Delay(10);                              // 等待10ms
    MPU6000_SET(MPUREG_PWR_MGMT_1,0x03);    //设置时钟源为陀螺仪的Z轴
    HAL_Delay(1);
    MPU6000_SET(MPUREG_USER_CTRL,0x10);     //使能SPI总线 屏蔽I2C //关闭了FIFO
    HAL_Delay(1);
    MPU6000_SET(MPUREG_SMPLRT_DIV,0x00);    //采样分频器 典型值0x00(1kHz);
    //MPU6000_SET(MPUREG_SMPLRT_DIV,0xF9);    //采样分频器 典型值0xFA(4Hz);
    HAL_Delay(1);
    MPU6000_SET(MPUREG_CONFIG,0x03);        //低通滤波频率 0x03设为42Hz
    HAL_Delay(1);
    MPU6000_SET(MPUREG_GYRO_CONFIG,0x18);   //陀螺仪最大量程 +-2000度/秒 ，不自检
    HAL_Delay(1);
    MPU6000_SET(MPUREG_ACCEL_CONFIG,0x10);  //加速度计最大量程  +-8g ，不自检
    HAL_Delay(1);
    MPU6000_SET(MPUREG_INT_ENABLE, 0x01);   //开数据中断，即传感器数据准备好以后就出发中断
    HAL_Delay(1);
    MPU6000_SET(MPUREG_INT_PIN_CFG, 0x30);  //配置终端模式，高电平出发，读寄存器就消除中断
    HAL_Delay(1);

    DebugPrint("MPU6000初始化完成!\r\n");

}



void MPU6000_INT_ENABLE(void)
{
   HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void MPU6000_INT_DISABLE(void)
{
   HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}


uint8_t MPU6000_RW(uint8_t TxData)
{
    uint8_t RxData;
    HAL_SPI_TransmitReceive(&Spi1Handle, &TxData, &RxData, 1, 0x5000);
    return RxData;
}

void MPU6000_SET(uint8_t setAddr,uint8_t setData)
{
   MPU6000_CS_ENABLE();
   MPU6000_RW(setAddr);	//写地址
   MPU6000_RW(setData); // 写数据
   MPU6000_CS_DISABLE();
}





void MPU6000_CS_ENABLE(void)
{
    HAL_GPIO_WritePin(MPU_CS_PORT, MPU_CS_PIN, GPIO_PIN_RESET);
}

void MPU6000_CS_DISABLE(void)
{
    HAL_GPIO_WritePin(MPU_CS_PORT, MPU_CS_PIN, GPIO_PIN_SET);
}






void SPI_MPU_Read(uint8_t *Buffer, uint8_t ReadAddr,uint8_t NumByteToRead)
{
 	uint8_t i;
    MPU6000_CS_ENABLE();
    MPU6000_RW(ReadAddr|=0x80);         //

    for(i=0;i<NumByteToRead;i++)
	{
        Buffer[i]=MPU6000_RW(0xFF);
    }
	MPU6000_CS_DISABLE();
}




void MPU6000_RAW_READY(MPU_report *pMPU_report)
{
   uint8_t MPU_buff[14]={0};

   SPI_MPU_Read(MPU_buff,MPUREG_ACCEL_XOUT_H,14);

   pMPU_report->timestamp = HAL_GetTick();
   pMPU_report->accel_x_raw =      (((int16_t)MPU_buff[0]) << 8) | MPU_buff[1];
   pMPU_report->accel_y_raw =      (((int16_t)MPU_buff[2]) << 8) | MPU_buff[3];
   pMPU_report->accel_z_raw =      (((int16_t)MPU_buff[4]) << 8) | MPU_buff[5];
   pMPU_report->temperature_raw =  (((int16_t)MPU_buff[6]) << 8) | MPU_buff[7];
   pMPU_report->gyro_x_raw =       (((int16_t)MPU_buff[8]) << 8) | MPU_buff[9];
   pMPU_report->gyro_y_raw =       (((int16_t)MPU_buff[10]) << 8) | MPU_buff[11];
   pMPU_report->gyro_z_raw =       (((int16_t)MPU_buff[12]) << 8) | MPU_buff[13];
   pMPU_report->flag = 1;
}


void EXTI15_10_IRQHandler(void)
{


    if(__HAL_GPIO_EXTI_GET_IT(MPU_DRDY_PIN) != RESET)
      {
        MPU6000_RAW_READY(&MPU_report1);
        MPU_RD_CNT++;
        __HAL_GPIO_EXTI_CLEAR_IT(MPU_DRDY_PIN);
      }

}



