#include "led.h"


GPIO_TypeDef* GPIO_PORT[LEDn] ={ LED_AMBER_GPIO_PORT };
const uint16_t GPIO_PIN[LEDn] ={ LED_AMBER_PIN };


void LED_Init(Led_TypeDef Led)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 开时钟
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




//VDD_BRICK_VALID
//VDD_SERVO_VALID
//VBUS_BALID   检测引脚初始化
static void VDD_VALID_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 开时钟
    GPIO_VDD_BRICK_VALID_CLK_ENABLE();
    GPIO_VDD_SERVO_VALID_CLK_ENABLE();
    GPIO_VBUS_VALID_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_VDD_BRICK_VALID_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIO_VDD_BRICK_VALID_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_VDD_SERVO_VALID_PIN;
    HAL_GPIO_Init(GPIO_VDD_SERVO_VALID_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_VBUS_VALID_PIN;
    HAL_GPIO_Init(GPIO_VDD_SERVO_VALID_PORT,&GPIO_InitStruct);

}

void Display_Power(void)
{
    GPIO_PinState       VDD_BRICK_VALID;
    GPIO_PinState       VDD_SERVO_VALID;
    GPIO_PinState       VBUS_VALID;

    VDD_BRICK_VALID = HAL_GPIO_ReadPin(GPIO_VDD_BRICK_VALID_PORT,GPIO_VDD_BRICK_VALID_PIN);
    VDD_SERVO_VALID = HAL_GPIO_ReadPin(GPIO_VDD_SERVO_VALID_PORT,GPIO_VDD_SERVO_VALID_PIN);
    VBUS_VALID = HAL_GPIO_ReadPin(GPIO_VBUS_VALID_PORT,GPIO_VBUS_VALID_PIN);

    if( VDD_BRICK_VALID == GPIO_PIN_RESET)
    {
        DebugPrint("VDD_BRICK_VALID -- 电源由电池提供\r\n");
    }


    if( VDD_SERVO_VALID == GPIO_PIN_RESET)
    {
        DebugPrint("VDD_SERVO_VALID -- 电源由电调提供\r\n");
    }

    if( VBUS_VALID == GPIO_PIN_RESET)
    {
        DebugPrint("VDD_BRICK_VALID -- 电源由USB提供\r\n");
    }

}



static void VDD_CTRL_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 开时钟
    GPIO_VDD_5V_PERIPH_EN_CLK_DISABLE();    // 低有效
    GPIO_VDD_3V3_SENSORS_EN_CLK_ENABLE();   // 高有效
    GPIO_VDD_5V_HIPOWER_OC_CLK_ENABLE();    // OC  低有效
    GPIO_VDD_5V_PERIPH_OC_CLK_ENABLE();     //  OC  低有效


    GPIO_InitStruct.Pin = GPIO_VDD_5V_PERIPH_EN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIO_VDD_5V_PERIPH_EN_PORT,&GPIO_InitStruct);
    VDD_5V_PERIPH_EN_ENABLE();

    GPIO_InitStruct.Pin = GPIO_VDD_3V3_SENSORS_EN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIO_VDD_3V3_SENSORS_EN_PORT,&GPIO_InitStruct);
    VDD_3V3_SENSORS_EN_ENABLE();



    GPIO_InitStruct.Pin = GPIO_VDD_5V_HIPOWER_OC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIO_VDD_5V_HIPOWER_OC_PORT,&GPIO_InitStruct);
    VDD_5V_HIPOWER_OC_ENABLE();

    GPIO_InitStruct.Pin = GPIO_VDD_5V_PERIPH_OC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIO_VDD_5V_PERIPH_OC_PORT,&GPIO_InitStruct);
    VDD_5V_PERIPH_OC_ENABLE();

}


// 低有效
void VDD_5V_PERIPH_EN_ENABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_5V_PERIPH_EN_PORT, GPIO_VDD_5V_PERIPH_EN_PIN,GPIO_PIN_RESET);
    DebugPrint("VDD_5V_PERIPH_EN -- 已使能\r\n");
}

void VDD_5V_PERIPH_EN_DISABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_5V_PERIPH_EN_PORT, GPIO_VDD_5V_PERIPH_EN_PIN,GPIO_PIN_SET);
    DebugPrint("VDD_5V_PERIPH_EN -- 已关闭\r\n");
}

// 高使能
void VDD_3V3_SENSORS_EN_ENABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_3V3_SENSORS_EN_PORT, GPIO_VDD_3V3_SENSORS_EN_PIN,GPIO_PIN_SET);
    DebugPrint("VDD_3V3_SENSORS_EN -- 已使能\r\n");
}

void VDD_3V3_SENSORS_EN_DISABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_3V3_SENSORS_EN_PORT, GPIO_VDD_3V3_SENSORS_EN_PIN,GPIO_PIN_RESET);
    DebugPrint("VDD_3V3_SENSORS_EN -- 已关闭\r\n");
}


// 高使能
void VDD_5V_HIPOWER_OC_ENABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_5V_HIPOWER_OC_PORT, GPIO_VDD_5V_HIPOWER_OC_PIN,GPIO_PIN_SET);
    DebugPrint("VDD_5V_HIPOWER_OC -- 已使能\r\n");
}

void VDD_5V_HIPOWER_OC_DISABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_5V_PERIPH_OC_PORT, GPIO_VDD_5V_PERIPH_OC_PIN,GPIO_PIN_RESET);
    DebugPrint("VDD_5V_HIPOWER_OC -- 已关闭\r\n");
}


void VDD_5V_PERIPH_OC_ENABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_5V_PERIPH_OC_PORT, GPIO_VDD_5V_PERIPH_OC_PIN,GPIO_PIN_SET);
    DebugPrint("VDD_5V_HIPOWER_OC -- 已使能\r\n");
}

void VDD_5V_PERIPH_OC_DISABLE(void)
{
    HAL_GPIO_WritePin(GPIO_VDD_5V_PERIPH_OC_PORT, GPIO_VDD_5V_PERIPH_OC_PIN,GPIO_PIN_RESET);
    DebugPrint("VDD_5V_HIPOWER_OC -- 已关闭\r\n");
}


void POWER_Init(void)
{
    //  三路电源检测
    VDD_VALID_Init();
    Display_Power();

    //打开主控能控制的各路电源
    VDD_CTRL_Init();
}

