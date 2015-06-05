#ifndef __LED_H
#define __LED_H

#include "stm32f4xx_hal.h"

typedef enum
{
  LED_AMBER = 0
}Led_TypeDef;


#define LEDn                            1    // 定义LED 个数
#define LED_AMBER_PIN                        GPIO_PIN_12
#define LED_AMBER_GPIO_PORT                  GPIOE
#define LED_AMBER_GPIO_CLK_ENABLE()          __GPIOE_CLK_ENABLE();
#define LED_AMBER_GPIO_CLK_DISABLE()         __GPIOE_CLK_DISABLE();




void LED_Init(Led_TypeDef Led);
void LED_Off(Led_TypeDef Led);
void LED_On(Led_TypeDef Led);
void LED_Toggle(Led_TypeDef Led);


#endif  /* __LED_H */

