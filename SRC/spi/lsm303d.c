#include "lsm303d.h"
#include "MPU6000.h"
#include "stm32f4xx.h"
#include "main.h"



LSM303D_ACC_report  LSM303D_ACC_report1;
LSM303D_MAG_report  LSM303D_MAG_report1;

extern SPI_HandleTypeDef Spi1Handle;

uint16_t    LSM303D_RD_CNT;


void LSM303D_Init(void)
{
    // IO初始化
    GPIO_InitTypeDef  GPIO_InitStruct;

    //LSM303D  片选IO
    LSM303D_CS_CLK_ENABLE();
    GPIO_InitStruct.Pin       = LSM303D_CS_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(LSM303D_CS_PORT, &GPIO_InitStruct);
    LSM303D_CS_DISABLE();

    //LSM303D DRDY引脚 --外部中断 上升沿触发
    LSM303D_ACC_DRDY_CLK_ENABLE();
    GPIO_InitStruct.Pin       = LSM303D_ACC_DRDY_PIN;       // GPIO4 入口有讲究 需注意
    GPIO_InitStruct.Mode      = GPIO_MODE_IT_RISING; // 中断模式 上升沿中断
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(LSM303D_ACC_DRDY_PORT, &GPIO_InitStruct);

    LSM303D_MAG_DRDY_CLK_ENABLE();
    GPIO_InitStruct.Pin       = LSM303D_MAG_DRDY_PIN;       // GPIO1 入口有讲究 需注意
    GPIO_InitStruct.Mode      = GPIO_MODE_IT_RISING; // 中断模式 上升沿中断
    GPIO_InitStruct.Pull      = GPIO_PULLUP;        // spi片选低有效，上拉保证稳定
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(LSM303D_MAG_DRDY_PORT, &GPIO_InitStruct);

    //外部中断初始化  acc_int
    HAL_NVIC_SetPriority(EXTI4_IRQn, 4, 0); // 设置外部引脚中断
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);         // 启动外部引脚中断

    // mag_int
    HAL_NVIC_SetPriority(EXTI1_IRQn, 4, 0); // 设置外部引脚中断
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);         // 启动外部引脚中断


    // 初始化LSM303D需要使用SPI1  但已被MPU6000占用
    // 为了防碰撞 因此需要先关掉SPI1上已经完成初始化的芯片的 RD中断
    MPU6000_INT_DISABLE();

    // 开始初始化LSM303D

    LSM303D_SET(LSM303D_REG_CTRL0, 0x80);    // 复位
    HAL_Delay(10); // 10MS  // 瞎猜的 未查手册
    LSM303D_SET(LSM303D_REG_CTRL0, 0x00);   // 关掉复位，不使用FIFO, 不使用高通滤波器
    HAL_Delay(1);
            //  acc800HZ  不更新ACC直到之前的数据被读取  使能加速度计
    LSM303D_SET(LSM303D_REG_CTRL1,
    REG1_RATE_800HZ_A | REG1_BDU_UPDATE | REG1_Z_ENABLE_A | REG1_Y_ENABLE_A | REG1_X_ENABLE_A);
    HAL_Delay(1);

    // ACC抗混叠滤波50Hz  +-8g  关闭自测   4线SPI
    // 抗混叠配合软件滤波使用 非常重要
    LSM303D_SET(LSM303D_REG_CTRL2,REG2_AA_FILTER_BW_50HZ_A | REG2_FULL_SCALE_8G_A );
    HAL_Delay(1);


    //使能温度传感  磁高分辨率 采样频率 100Hz   关中断寄存器保持
    LSM303D_SET(LSM303D_REG_CTRL5,
    REG5_ENABLE_T | REG5_RES_HIGH_M | REG5_RATE_100HZ_M);
    HAL_Delay(1);

    // 使能MAG  连续转换模式   剩余功能均置零关闭
    LSM303D_SET(LSM303D_REG_CTRL6,  REG6_FULL_SCALE_2GA_M);
    HAL_Delay(1);

    // MAG range 2
    LSM303D_SET(LSM303D_REG_CTRL7,  REG7_CONT_MODE_M);
    HAL_Delay(1);

    // 高电平中断
    LSM303D_SET(LSM303D_INT_CTRL_M, 0x08);
    HAL_Delay(1);

    // 开中断
    LSM303D_SET(LSM303D_REG_CTRL3, 0x04);  // DRDY on ACCEL on INT1
    HAL_Delay(1);
    LSM303D_SET(LSM303D_REG_CTRL4, 0x04);  // DRDY on MAG on INT2
    HAL_Delay(1);


    MPU6000_INT_ENABLE();       // 完成配置 重新开启被关掉的中断

    DebugPrint("LSM303D初始化完成!\r\n");

}



void LSM303D_CS_ENABLE(void)
{
    HAL_GPIO_WritePin(LSM303D_CS_PORT, LSM303D_CS_PIN, GPIO_PIN_RESET);
}

void LSM303D_CS_DISABLE(void)
{
    HAL_GPIO_WritePin(LSM303D_CS_PORT, LSM303D_CS_PIN, GPIO_PIN_SET);
}


uint8_t LSM303D_RW(uint8_t TxData)
{
    uint8_t RxData;
    HAL_SPI_TransmitReceive(&Spi1Handle, &TxData, &RxData, 1, 0x5000);
    return RxData;
}

void LSM303D_SET(uint8_t setAddr,uint8_t setData)
{
   LSM303D_CS_ENABLE();
   LSM303D_RW(setAddr);	//写地址
   LSM303D_RW(setData); // 写数据
   LSM303D_CS_DISABLE();
}






void EXTI4_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(LSM303D_ACC_DRDY_PIN) != RESET)
      {

       // LSM303D_ACC_READY(&LSM303D_ACC_report1);

        __HAL_GPIO_EXTI_CLEAR_IT(LSM303D_ACC_DRDY_PIN);
      }

}


void LSM303D_SPI_Read(uint8_t *Buffer, uint8_t ReadAddr,uint8_t NumByteToRead)
{
    uint8_t i;
    LSM303D_CS_ENABLE();
    LSM303D_RW(ReadAddr|=0xC0);  // 读 连续模式
    for(i=0;i<NumByteToRead;i++)
	{
        Buffer[i]=LSM303D_RW(0xFF);
    }
	LSM303D_CS_DISABLE();

}



void LSM303D_ACC_READY(LSM303D_ACC_report *pLSM303D_ACC_report)
{
    uint8_t LSM303D_ACC_buff[6]={0};

    LSM303D_SPI_Read( LSM303D_ACC_buff, LSM303D_OUT_X_L_A, 6);

    pLSM303D_ACC_report->timestamp = HAL_GetTick();
    pLSM303D_ACC_report->accel_x_raw =      (((int16_t)LSM303D_ACC_buff[1]) << 8) | LSM303D_ACC_buff[0];
    pLSM303D_ACC_report->accel_y_raw =      (((int16_t)LSM303D_ACC_buff[2]) << 8) | LSM303D_ACC_buff[2];
    pLSM303D_ACC_report->accel_z_raw =      (((int16_t)LSM303D_ACC_buff[3]) << 8) | LSM303D_ACC_buff[4];


    LSM303D_SPI_Read( LSM303D_ACC_buff, LSM303D_OUT_TEMP_L, 2);
    pLSM303D_ACC_report->temperature_raw =  (((int16_t)LSM303D_ACC_buff[1]) << 8) | LSM303D_ACC_buff[0];
    pLSM303D_ACC_report->flag = 1;
}



void EXTI1_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(LSM303D_MAG_DRDY_PIN) != RESET)
      {

        LSM303D_MAG_READY(&LSM303D_MAG_report1);
        LSM303D_RD_CNT++;
        __HAL_GPIO_EXTI_CLEAR_IT(LSM303D_MAG_DRDY_PIN);
      }

}

void LSM303D_MAG_READY(LSM303D_MAG_report *pLSM303D_MAG_report)
{
    uint8_t LSM303D_MAG_buff[6]={0};

    LSM303D_SPI_Read( LSM303D_MAG_buff, LSM303D_OUT_X_L_M, 6);

    pLSM303D_MAG_report->timestamp = HAL_GetTick();
    pLSM303D_MAG_report->mag_x_raw =      (((int16_t)LSM303D_MAG_buff[1]) << 8) | LSM303D_MAG_buff[0];
    pLSM303D_MAG_report->mag_y_raw =      (((int16_t)LSM303D_MAG_buff[2]) << 8) | LSM303D_MAG_buff[2];
    pLSM303D_MAG_report->mag_z_raw =      (((int16_t)LSM303D_MAG_buff[3]) << 8) | LSM303D_MAG_buff[4];

    LSM303D_SPI_Read( LSM303D_MAG_buff, LSM303D_OUT_TEMP_L, 2);
    pLSM303D_MAG_report->temperature_raw =  (((int16_t)LSM303D_MAG_buff[1]) << 8) | LSM303D_MAG_buff[0];
    pLSM303D_MAG_report->flag = 1;
}

