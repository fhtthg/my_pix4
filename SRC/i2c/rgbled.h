#ifndef __RGBLED_H
#define __RGBLED_H

#include "stm32f4xx_hal.h"

#include "stm32f4xx_hal_conf.h"



#define TCA62724_REG_BLUE   0x81
#define TCA62724_REG_GREEN  0x82
#define TCA62724_REG_RED    0x83
#define TCA62724_REG_PWM3   0x84

#define TCA62714_PWM_0      0x00        // 0/15 //¹ØµÆ
#define TCA62714_PWM_1      0x01
#define TCA62714_PWM_2      0x02
#define TCA62714_PWM_3      0x03
#define TCA62714_PWM_4      0x04
#define TCA62714_PWM_5      0x05
#define TCA62714_PWM_6      0x06
#define TCA62714_PWM_7      0x07
#define TCA62714_PWM_8      0x08
#define TCA62714_PWM_9      0x09
#define TCA62714_PWM_10     0x0A
#define TCA62714_PWM_11     0x0B
#define TCA62714_PWM_12     0x0C
#define TCA62714_PWM_13     0x0D
#define TCA62714_PWM_14     0x0E
#define TCA62714_PWM_15     0x0F        // ×îÁÁ


void RGBLED_Init(void);









#endif // __RGBLED_H


