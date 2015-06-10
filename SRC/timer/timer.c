


#include "stm32f4xx_hal.h"
#include "led.h"



TIM_HandleTypeDef    Tim5Handle;

uint8_t Timer5cnt = 0;

void TIM5_Init(void)
{


    // ¿ªÊ±ÖÓ
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



/*
    if(Timer5cnt >= 250)
    {
        Timer5cnt = 0;
    }
    else
    {
        Timer5cnt++;
    }

    if(Timer5cnt == 0)
    {
*/
        LED_Toggle(LED_AMBER);
 //   }

//     uint32_t tickstart = 0;
//    tickstart = HAL_GetTick();
//    printf("test",tickstart);

}


