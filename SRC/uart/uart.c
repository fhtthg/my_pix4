
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "uart.h"

#include "led.h"



UART_HandleTypeDef UartHandle;

void UART7_Init(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct;
 //   UART_HandleTypeDef  UartHandle;

    UART7_RX_GPIO_CLK_ENABLE();
    UART7_TX_GPIO_CLK_ENABLE();

    UART7_CLK_ENABLE();

    // tx
    GPIO_InitStruct.Pin       = UART7_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    HAL_GPIO_Init(UART7_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = UART7_RX_PIN;
   // GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    HAL_GPIO_Init(UART7_RX_GPIO_PORT, &GPIO_InitStruct);


    UartHandle.Instance        = UART7;

    UartHandle.Init.BaudRate   = 9600;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;

    if(HAL_UART_Init(&UartHandle) != HAL_OK)
    {
    /* Initialization Error */
        Error_Handler();
    }

   // HAL_NVIC_SetPriority(UART7_IRQn, 0, 1);
   // HAL_NVIC_EnableIRQ(UART7_IRQn);
   HAL_Delay(500);
    HAL_UART_Transmit(&UartHandle, "\n\r UART7 is ok!!!\n\r", 19, 5000);

}


int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}


void UART7_IRQHandler(void)

{
 // HAL_UART_IRQHandler(& UartHandle);
 //   uint8_t c;
//	HAL_UART_Receive(&UartHandle, (uint8_t *)c, 1, 5000);
//	printf("%c",c);    //将接受到的数据直接返回打印
  //  printf("test");    //将接受到的数据直接返回打印
}


static void Error_Handler(void)
{
    while(1)
	{
        LED_Toggle(LED_AMBER);
        HAL_Delay(500);
    }
}

