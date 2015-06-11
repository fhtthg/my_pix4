


#include "stm32f4xx_hal.h"
#include "led.h"
#include "mpu6000.h"

extern MPU_report  MPU_report1;


TIM_HandleTypeDef    Tim5Handle;

uint8_t Timer5cnt = 0;

void TIM5_Init(void)
{


    // 开时钟
    __TIM5_CLK_ENABLE();

   Tim5Handle.Instance = TIM5;
   Tim5Handle.Init.Period = 10000 - 1;
   Tim5Handle.Init.Prescaler = (uint32_t) 16800/2-1;
   Tim5Handle.Init.ClockDivision = 0;
   Tim5Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
   HAL_TIM_Base_Init(&Tim5Handle);
   HAL_TIM_Base_Start_IT(&Tim5Handle);


   HAL_NVIC_SetPriority(TIM5_IRQn,5,0);
   HAL_NVIC_EnableIRQ(TIM5_IRQn);

}



void TIM5_IRQHandler(void)
{

    __HAL_TIM_CLEAR_IT(&Tim5Handle, TIM_IT_UPDATE);
    LED_Toggle(LED_AMBER);

    //秒级 调试信息
    if(1 == MPU_report1.flag)
    {
        DebugPrint("MPU6000 ACCEL x=%d, y=%d, z=%d\r\n",
                    MPU_report1.accel_x_raw,
                    MPU_report1.accel_y_raw,
                    MPU_report1.accel_z_raw);


        DebugPrint("MPU6000 GYRO  x=%d, y=%d, z=%d\r\n\r\n",
                    MPU_report1.gyro_x_raw,
                    MPU_report1.gyro_y_raw,
                    MPU_report1.gyro_z_raw);
    }
}


