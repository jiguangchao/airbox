
#ifndef _BSP_INCLUDE_H_
#define _BSP_INCLUDE_H_


//#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <intrinsics.h>

#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_rng.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_flash.h"

#ifdef STM32G030xx
    #include ".\BSP_030\Inc\BSP_Init.h"
    #include ".\BSP_030\Inc\BSP_USART.h"    
#endif
#ifdef STM32G070xx
    #include ".\BSP_070\Inc\BSP_Init.h"
    #include ".\BSP_070\Inc\BSP_USART.h"
    
#endif

#include ".\BSP_IOMap.h"
#include ".\BSP_TM16XX.h"
#include ".\BSP_FLASH.h"
#include ".\BSP_BOOT.h"


#define NOP() nop()
/*
#ifndef OK
#define OK            (0)
#endif
*/
enum
{
    OK = 0,
};

typedef struct
{
    uint8_t  u3Permission :3;
    uint8_t  u1RangeEnable:1;

    uint8_t  u8RegID       ;
    uint16_t u16MinValue   ;
    uint16_t u16MaxValue   ;
}RegTab_Typedef;

#endif
