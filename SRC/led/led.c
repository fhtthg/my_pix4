#include "led.h"


GPIO_TypeDef* GPIO_PORT[LEDn] ={ LED_AMBER_GPIO_PORT };

const uint16_t GPIO_PIN[LEDn] ={ LED_AMBER_PIN };


void LED_Init(Led_TypeDef Led)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // ¿ªÊ±ÖÓ
    LED_AMBER_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN[Led];
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIO_PORT[Led],&GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIO_PORT[Led],GPIO_PIN[Led],GPIO_PIN_RESET);


}


void LED_Off(Led_TypeDef Led)
{
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
}

void LED_On(Led_TypeDef Led)
{
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
}


void LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
}


