#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include "stm32f4xx_hal_conf.h"
#include "led.h"
#include "uart.h"



#if 1
    #define __DEBUG_PRINTF__
#endif


#ifdef __DEBUG_PRINTF__
    #define DebugPos()   printf("file:%s(%d),function:%s\n",__FILE__,__LINE__,__FUNCTION__);
    #define DebugPrint  printf

#else
    #define DebugPos()
    #define DebugPrint(strFormat, ...)

#endif


#endif


