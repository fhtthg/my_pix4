#ifndef __LED_H
#define __LED_H

#include "stm32f4xx_hal.h"
#include "main.h"

typedef enum
{
  LED_AMBER = 0
}Led_TypeDef;


#define LEDn                                 1    // 定义LED 个数
#define LED_AMBER_PIN                        GPIO_PIN_12
#define LED_AMBER_GPIO_PORT                  GPIOE
#define LED_AMBER_GPIO_CLK_ENABLE()          __GPIOE_CLK_ENABLE()
#define LED_AMBER_GPIO_CLK_DISABLE()         __GPIOE_CLK_DISABLE()

void LED_Init(Led_TypeDef Led);
void LED_Off(Led_TypeDef Led);
void LED_On(Led_TypeDef Led);
void LED_Toggle(Led_TypeDef Led);


#define GPIO_VDD_BRICK_VALID_PIN                    GPIO_PIN_5
#define GPIO_VDD_BRICK_VALID_PORT                   GPIOB
#define GPIO_VDD_BRICK_VALID_CLK_ENABLE()           __GPIOB_CLK_ENABLE()
#define GPIO_VDD_BRICK_VALID_CLK_DISABLE()          __GPIOB_CLK_DISABLE()

#define GPIO_VDD_SERVO_VALID_PIN                    GPIO_PIN_7
#define GPIO_VDD_SERVO_VALID_PORT                   GPIOB
#define GPIO_VDD_SERVO_VALID_CLK_ENABLE()           __GPIOB_CLK_ENABLE()
#define GPIO_VDD_SERVO_VALID_CLK_DISABLE()          __GPIOB_CLK_DISABLE()

#define GPIO_VBUS_VALID_PIN                         GPIO_PIN_0
#define GPIO_VBUS_VALID_PORT                        GPIOC
#define GPIO_VBUS_VALID_CLK_ENABLE()                __GPIOC_CLK_ENABLE()
#define GPIO_VBUS_VALID_CLK_DISABLE()               __GPIOC_CLK_DISABLE()


#define GPIO_VDD_5V_PERIPH_EN_PIN                   GPIO_PIN_8
#define GPIO_VDD_5V_PERIPH_EN_PORT                  GPIOA
#define GPIO_VDD_5V_PERIPH_EN_CLK_ENABLE()          __GPIOA_CLK_ENABLE()
#define GPIO_VDD_5V_PERIPH_EN_CLK_DISABLE()         __GPIOA_CLK_DISABLE()


#define GPIO_VDD_3V3_SENSORS_EN_PIN                 GPIO_PIN_3
#define GPIO_VDD_3V3_SENSORS_EN_PORT                GPIOE
#define GPIO_VDD_3V3_SENSORS_EN_CLK_ENABLE()        __GPIOE_CLK_ENABLE()
#define GPIO_VDD_3V3_SENSORS_EN_CLK_DISABLE()       __GPIOE_CLK_DISABLE()


#define GPIO_VDD_5V_HIPOWER_OC_PIN                  GPIO_PIN_10
#define GPIO_VDD_5V_HIPOWER_OC_PORT                 GPIOE
#define GPIO_VDD_5V_HIPOWER_OC_CLK_ENABLE()         __GPIOE_CLK_ENABLE()
#define GPIO_VDD_5V_HIPOWER_OC_CLK_DISABLE()        __GPIOE_CLK_DISABLE()

#define GPIO_VDD_5V_PERIPH_OC_PIN                   GPIO_PIN_15
#define GPIO_VDD_5V_PERIPH_OC_PORT                  GPIOE
#define GPIO_VDD_5V_PERIPH_OC_CLK_ENABLE()          __GPIOE_CLK_ENABLE()
#define GPIO_VDD_5V_PERIPH_OC_CLK_DISABLE()         __GPIOE_CLK_DISABLE()


void VDD_5V_PERIPH_EN_ENABLE(void);
void VDD_5V_PERIPH_EN_DISABLE(void);
// 高使能
void VDD_3V3_SENSORS_EN_ENABLE(void);
void VDD_3V3_SENSORS_EN_DISABLE(void);


void VDD_5V_HIPOWER_OC_ENABLE(void);
void VDD_5V_HIPOWER_OC_DISABLE(void);

void VDD_5V_PERIPH_OC_ENABLE(void);
void VDD_5V_PERIPH_OC_DISABLE(void);



void POWER_Init(void);



#endif  /* __LED_H */

