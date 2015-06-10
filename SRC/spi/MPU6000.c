


#include "MPU6000.h"
#include "stm32f4xx.h"
#include "main.h"

int16_t MPU6000_FIFO[6][11];
extern SPI_HandleTypeDef Spi1Handle;
int16_t ax=1,ay=2,az=3,gx=4,gy=5,gz=6;


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
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         // 启动外部引脚中断


    //寄存器初始化

    MPU6000_Reset(0x80);
	HAL_Delay(10);
	MPU6000_setClockSource(0x03);
	HAL_Delay(1);
	MPU6000_SPIEnabled(0x10);
	HAL_Delay(1);
	MPU6000_setSampleRateDIV(0x07);
    HAL_Delay(1);
	MPU6000_setDLPH(0x06);
	HAL_Delay(1);
	MPU6000_setFullScaleGyroRange(0x10);
	MPU6000_setFullScaleAccelRange(0x08);
	HAL_Delay(1);
    MPU6000_ITEnabled(0x01);
	HAL_Delay(1);
	MPU6000_setITMode(0x30);
	HAL_Delay(1);
}



uint8_t MPU6000_RW(uint8_t TxData)
{
    uint8_t RxData;
    HAL_SPI_TransmitReceive(&Spi1Handle, &TxData, &RxData, 1, 0x5000);
    return RxData;
}

void MPU6000_Reset(uint8_t date)
{

   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_PWR_MGMT_1);	//写地址
   MPU6000_RW(date);
   delay_us(); // 应该为1us
   MPU6000_CS_DISABLE();
}

void MPU6000_setClockSource(uint8_t source)    //设置时钟源
{

   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_PWR_MGMT_1);	//
   MPU6000_RW(source);
   delay_us();
   MPU6000_CS_DISABLE();
}




void MPU6000_SPIEnabled(uint8_t enabled)
{
   MPU6000_CS_ENABLE();
   //delay_us(1);
   MPU6000_RW(MPU6000_RA_USER_CTRL);
   MPU6000_RW(enabled);
   delay_us();
   MPU6000_CS_DISABLE();
}

void MPU6000_setSampleRateDIV(uint8_t rate)
{
   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_SMPRT_DIV);
   MPU6000_RW(rate);
   delay_us();
   MPU6000_CS_DISABLE();
}



void MPU6000_setDLPH(uint8_t rate)
{
   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_CONFIG);
   MPU6000_RW(rate);
   delay_us();
   MPU6000_CS_DISABLE();
}



void MPU6000_setFullScaleGyroRange(uint8_t range)
{
   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_GYRO_CONFIG);
   MPU6000_RW(range);
   delay_us();
   MPU6000_CS_DISABLE();
}

void MPU6000_setFullScaleAccelRange(uint8_t range)
{
   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_ACCEL_CONFIG);
   MPU6000_RW(range);
   delay_us();
   MPU6000_CS_DISABLE();
}


void MPU6000_setITMode(uint8_t mode)
{

   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_INT_PIN_CFG);
   MPU6000_RW(mode);
   delay_us();
   MPU6000_CS_DISABLE();
}

void MPU6000_ITEnabled(uint8_t enabled)
{
   MPU6000_CS_ENABLE();
   MPU6000_RW(MPU6000_RA_INT_ENABLE);
   MPU6000_RW(enabled);
   delay_us();
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
	delay_us();
	MPU6000_CS_DISABLE();
}


void MPU6000_newValues(int16_t accelx,int16_t accely,int16_t accelz,
                        int16_t gyrox,int16_t gyroy,int16_t gyroz)
{
   unsigned char i ;
   int32_t sum=0;
   for(i=1;i<10;i++)	 //FIFO 操作
   {
     MPU6000_FIFO[0][i-1]=MPU6000_FIFO[0][i];
     MPU6000_FIFO[1][i-1]=MPU6000_FIFO[1][i];
     MPU6000_FIFO[2][i-1]=MPU6000_FIFO[2][i];
     MPU6000_FIFO[3][i-1]=MPU6000_FIFO[3][i];
     MPU6000_FIFO[4][i-1]=MPU6000_FIFO[4][i];
     MPU6000_FIFO[5][i-1]=MPU6000_FIFO[5][i];
   }
   MPU6000_FIFO[0][9]=accelx;//??D?μ?êy?Y·???μ? êy?Yμ?×?oó??
   MPU6000_FIFO[1][9]=accely;
   MPU6000_FIFO[2][9]=accelz;
   MPU6000_FIFO[3][9]=gyrox;
   MPU6000_FIFO[4][9]=gyroy;
   MPU6000_FIFO[5][9]=gyroz;

   sum=0;
   for(i=0;i<10;i++)	//?óμ±?°êy×éμ?o?￡??ùè????ù?μ
   {
     sum+=MPU6000_FIFO[0][i];
   }
   MPU6000_FIFO[0][10]=sum/10;

   sum=0;
   for(i=0;i<10;i++)
   {
     sum+=MPU6000_FIFO[1][i];
   }
   MPU6000_FIFO[1][10]=sum/10;

   sum=0;
   for(i=0;i<10;i++)
   {
     sum+=MPU6000_FIFO[2][i];
   }
   MPU6000_FIFO[2][10]=sum/10;

   sum=0;
   for(i=0;i<10;i++)
   {
     sum+=MPU6000_FIFO[3][i];
   }
   MPU6000_FIFO[3][10]=sum/10;

   sum=0;
   for(i=0;i<10;i++)
   {
     sum+=MPU6000_FIFO[4][i];
   }
   MPU6000_FIFO[4][10]=sum/10;

   sum=0;
   for(i=0;i<10;i++)
   {
     sum+=MPU6000_FIFO[5][i];
   }
   MPU6000_FIFO[5][10]=sum/10;



    DebugPrint("accx = %d\r\n",MPU6000_FIFO[0][10]);
 //   DebugPrint("accy = %d\r\n",MPU6000_FIFO[1][10]);
 //   DebugPrint("accz = %d\r\n",MPU6000_FIFO[2][10]);
 //   DebugPrint("gyrx = %d\r\n",MPU6000_FIFO[3][10]);
 //   DebugPrint("gyry = %d\r\n",MPU6000_FIFO[4][10]);
 //   DebugPrint("gyrz = %d\r\n",MPU6000_FIFO[5][10]);

}


void MPU6000_RAW_READY(int16_t *accx, int16_t *accy, int16_t *accz,
                        int16_t *gyrx, int16_t *gyry, int16_t *gyrz)
{
   uint8_t MPU_buff[14]={0};
   int16_t Lastax,Lastay,Lastaz,Lastgx,Lastgy,Lastgz;

   SPI_MPU_Read(MPU_buff,MPU6000_RA_ACCEL_XOUT_H,14);

   Lastax=(((int16_t)MPU_buff[0]) << 8) | MPU_buff[1];
   Lastay=(((int16_t)MPU_buff[2]) << 8) | MPU_buff[3];
   Lastaz=(((int16_t)MPU_buff[4]) << 8) | MPU_buff[5];
//跳过温度ADC
   Lastgx=(((int16_t)MPU_buff[8]) << 8) | MPU_buff[9];
   Lastgy=(((int16_t)MPU_buff[10]) << 8) | MPU_buff[11];
   Lastgz=(((int16_t)MPU_buff[12]) << 8) | MPU_buff[13];

   MPU6000_newValues(Lastax,Lastay,Lastaz,Lastgx,Lastgy,Lastgz);

   *accx=MPU6000_FIFO[0][10];
   *accy=MPU6000_FIFO[1][10];
   *accz=MPU6000_FIFO[2][10];
   *gyrx=MPU6000_FIFO[3][10];
   *gyry=MPU6000_FIFO[4][10];
   *gyrz=MPU6000_FIFO[5][10];

}

void delay_us(void)
{
    uint16_t i = 16800;
    while(i--);
    while(i--);
    while(i--);
    while(i--);
    while(i--);

    while(i--);
    while(i--);
    while(i--);
    while(i--);
    while(i--);

}


void EXTI15_10_IRQHandler(void)
{


    if(__HAL_GPIO_EXTI_GET_IT(MPU_DRDY_PIN) != RESET)
      {
        __HAL_GPIO_EXTI_CLEAR_IT(MPU_DRDY_PIN);

        MPU6000_RAW_READY(&ax,&ay,&az,&gx,&gy,&gz);
      }

}

