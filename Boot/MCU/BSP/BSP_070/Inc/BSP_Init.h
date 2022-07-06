#ifndef _BSP_INIT_H_
#define _BSP_INIT_H_


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void Nop_Delay(uint16_t delay); 
/** System Clock Configuration
*/
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void);
/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through 
        * the Code Generation settings)
*/
void MX_GPIO_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_NotUse_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_KEY_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_DALI_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_DCOut_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_RS485Expand_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_RS485MB_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_RS485Cascade_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_EnOceanReset_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_EnOceanUsart_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_IIC_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_Light_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_TM1617_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_Switch_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void AC_Zero_Feedback_GPIO_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
/* TIM16 init function */
//void MX_TIM16_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void MX_TIM3_Init(void);
/*! \note
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void MX_TIM14_Init(void);
/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
void MX_IWDG_Init(void);
/**
  * @brief IWDG reload 
  * @param None
  * @retval None
  */
void IWDG_Reload(void);
/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
void MX_RNG_Init(void);
/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
void MX_DMA_Init(void);
/**
 * @brief 
 * @param
 * @retval None
 */
void BSP_DeInitAll(void);

#endif

/* End of file */
