#ifndef __UART_H
#define __UART_H

#include "stm32f4xx_hal.h"
#include <stdio.h>

#define UART7_CLK_ENABLE()              __UART7_CLK_ENABLE()
#define DMA_UART7_CLK_ENABLE()          __DMA1_CLK_ENABLE()
#define UART7_RX_GPIO_CLK_ENABLE()      __GPIOE_CLK_ENABLE()
#define UART7_TX_GPIO_CLK_ENABLE()      __GPIOE_CLK_ENABLE()

#define UART7_FORCE_RESET()             __UART7_FORCE_RESET()
#define UART7_RELEASE_RESET()           __UART7_RELEASE_RESET()



/* Definition for USARTx Pins */
#define UART7_TX_PIN                    GPIO_PIN_8
#define UART7_TX_GPIO_PORT              GPIOE
#define UART7_RX_PIN                    GPIO_PIN_7
#define UART7_RX_GPIO_PORT              GPIOE









void UART7_Init(void);

int fputc(int ch, FILE *f);

void UART7_IRQHandler(void);




#endif /* __UART_H */

