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
/*GPIO初始化*/
void MX_GPIO_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
/*定时器初始化*/
void MX_TIM_Init(void);
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
void GPIO_Light_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
/* LED初始化 */
void GPIO_Light_Init_Test(void);
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
void GPIO_RS485MB_Init(void);
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
void GPIO_PMSA_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_CH2O_CO2_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_SHT20_IIC1_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void GPIO_EEPROM_IIC2_Init(void);
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
void TIM1_PWM_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void TIM3_PWM_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void TIM15_PWM_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
//void MX_TIM3_Init(void);
/*! \note
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void MX_TIM14_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
/* TIM17 init function */
void MX_TIM6_Init(void);
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


#endif

/* End of file */
