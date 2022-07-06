/*******************************************************************
*
*    DESCRIPTION:
*
*    AUTHOR:
*
*    HISTORY:
*
*    DATE:
*
*******************************************************************/


#include "..\..\BSP_Include.h"

LL_RCC_ClocksTypeDef RCC_Clocks;

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}


#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void Nop_Delay(uint16_t delay)
{
    volatile uint16_t u16Wait;
    u16Wait = delay;
    while(u16Wait)
    {
        u16Wait--;
    }
}

/** System Clock Configuration
*/
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
    {
      Error_Handler();  
    };

    /* HSE configuration and activation */
    LL_RCC_HSE_Enable();
    while(LL_RCC_HSE_IsReady() != 1)
    {
    };

    /* Main PLL configuration and activation */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_2, 32, LL_RCC_PLLR_DIV_3);
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while(LL_RCC_PLL_IsReady() != 1)
    {
    };

    /* Set AHB prescaler*/
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

    /* Sysclk activation on the main PLL */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
    };

    /* Set APB1 prescaler*/
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_Init1msTick(64000000);
    LL_SetSystemCoreClock(64000000);
    /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
    LL_SetSystemCoreClock(64000000);
    LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
    LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART4);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    /* GPIO Ports Clock Enable */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);    
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
    
    /*
    if ( FCLK != RCC_Clocks.SYSCLK_Frequency )
    {
        Error_Handler();  
    }
    if ( FCLK != RCC_Clocks.HCLK_Frequency )
    {
        Error_Handler();  
    }
    if ( FCLK != RCC_Clocks.PCLK1_Frequency )
    {
        Error_Handler();  
    }
    */
}
/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through 
        * the Code Generation settings)
*/
void MX_GPIO_Init(void)
{
    GPIO_KEY_Init();
    GPIO_Light_Init();

    GPIO_EnOceanReset_Init();
    GPIO_EnOceanUsart_Init();
    GPIO_RS485MB_Init();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
/* KEY初始化 */
void GPIO_KEY_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = KEY_LRN1_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(KEY_LRN1_GPIO, &GPIO_InitStruct);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
/* LED初始化 */
void GPIO_Light_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /**/
    GPIO_InitStruct.Pin = LED_RED_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(LED_RED_GPIO, &GPIO_InitStruct);
    /**/
    GPIO_InitStruct.Pin = LED_GREEN_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(LED_GREEN_GPIO, &GPIO_InitStruct);
    /**/
    GPIO_InitStruct.Pin = LED_ORG_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(LED_ORG_GPIO, &GPIO_InitStruct);
    /**/
    GPIO_InitStruct.Pin = LED_YELLOW_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(LED_YELLOW_GPIO, &GPIO_InitStruct);
    /**/
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
/* RS485  UART1 */
void GPIO_RS485MB_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /**/
    GPIO_InitStruct.Pin = RS485_MODBUS_DE_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(RS485_MODBUS_DE_GPIO, &GPIO_InitStruct);
    /* Peripheral clock enable */

    GPIO_InitStruct.Pin = RS485_MODBUS_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(RS485_MODBUS_TX_GPIO, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = RS485_MODBUS_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(RS485_MODBUS_RX_GPIO, &GPIO_InitStruct);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
/* TCM_310  UART3*/
void GPIO_EnOceanReset_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /**/
    GPIO_InitStruct.Pin = ENOCEAN_RST_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(ENOCEAN_RST_GPIO, &GPIO_InitStruct);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
/* TCM_310  UART3*/
void GPIO_EnOceanUsart_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = ENOCEAN_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
    LL_GPIO_Init(ENOCEAN_TX_GPIO, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ENOCEAN_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
    LL_GPIO_Init(ENOCEAN_RX_GPIO, &GPIO_InitStruct);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void MX_TIM3_Init(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

    /* TIM3 interrupt Init */
    NVIC_SetPriority(TIM3_IRQn, 0);
    NVIC_EnableIRQ(TIM3_IRQn);

    TIM_InitStruct.Prescaler        = 63;
    TIM_InitStruct.CounterMode      = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload       = 99;
    TIM_InitStruct.ClockDivision    = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter= 0;
    LL_TIM_Init(TIM3, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM3);
    /*
    LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM3);
    */
    LL_TIM_EnableIT_UPDATE(TIM3);
    /* Enable counter */
    LL_TIM_EnableCounter(TIM3);
}
/*! \note
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void MX_TIM14_Init(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM14);

    /* TIM14 interrupt Init */
    NVIC_SetPriority(TIM14_IRQn, 0);
    NVIC_EnableIRQ(TIM14_IRQn);

    TIM_InitStruct.Prescaler        = 63;
    TIM_InitStruct.CounterMode      = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload       = 999;
    TIM_InitStruct.ClockDivision    = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter= 0;
    LL_TIM_Init(TIM14, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM14);

    LL_TIM_EnableIT_UPDATE(TIM14);
    /* Enable counter */
    LL_TIM_EnableCounter(TIM14);
}
/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
void MX_IWDG_Init(void)
{
    LL_IWDG_Enable(IWDG);
    LL_IWDG_EnableWriteAccess(IWDG);
    LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_16);
    LL_IWDG_SetReloadCounter(IWDG, 4095);
    while (LL_IWDG_IsReady(IWDG) != 1)
    {
    }

    LL_IWDG_SetWindow(IWDG, 4095);
    LL_IWDG_ReloadCounter(IWDG);
}
/**
  * @brief IWDG reload 
  * @param None
  * @retval None
  */
void IWDG_Reload(void)
{
    LL_IWDG_ReloadCounter(IWDG);
}
/**
 * @brief 
 * @param
 * @retval None
 */
void BSP_DeInitAll(void)
{
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk; /* Disable SysTick Timer */
    LL_RCC_DeInit();
    HAL_DeInit();

    LL_USART_DeInit(ENOCEAN_USART);
    //LL_USART_DeInit(RS485_MODBUS_USART);
    //LL_USART_DeInit(RS485_CASCADE_USART);
    LL_TIM_DeInit(TIM14);
    LL_TIM_DeInit(TIM3);
    LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    //LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
    LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
    LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
    LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
    LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_3);
    LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_4);
    LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_5);
    //LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_6);
    //LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_7);
}
/* End of file */

