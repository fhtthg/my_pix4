
#include "stm32f4xx_hal.h"
#include "uart.h"

#include "led.h"



UART_HandleTypeDef UartHandle;

void UART7_Init(void)
{
    // 中断方式 调试未成功
    GPIO_InitTypeDef    GPIO_InitStruct;

    UART7_RX_GPIO_CLK_ENABLE();
    UART7_TX_GPIO_CLK_ENABLE();

    UART7_CLK_ENABLE();

    GPIO_InitStruct.Pin       = UART7_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART7;
    HAL_GPIO_Init(UART7_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = UART7_RX_PIN;
   // GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;

    GPIO_InitStruct.Alternate = GPIO_AF8_UART7;
    HAL_GPIO_Init(UART7_RX_GPIO_PORT, &GPIO_InitStruct);

 //   HAL_NVIC_SetPriority(UART7_IRQn,0,1);
 //   HAL_NVIC_EnableIRQ(UART7_IRQn);


    UartHandle.Instance        = UART7;
    UartHandle.Init.BaudRate   = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;

    HAL_UART_Init(&UartHandle);
   // __HAL_UART_ENABLE_IT(UartHandle,UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);

    HAL_NVIC_SetPriority(UART7_IRQn, 14, 0);
    HAL_NVIC_EnableIRQ(UART7_IRQn);

}


int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;


}


void UART7_IRQHandler(void)

{
    uint32_t tmp1 = 0;
    uint8_t c;
    tmp1 = __HAL_UART_GET_IT_SOURCE(&UartHandle, UART_IT_RXNE);
    if(tmp1 != RESET)
    {
        c = (UartHandle.Instance->DR);
        printf("%c",c);
    }

}


