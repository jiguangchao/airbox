
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_LED_H__
#define __BSP_LED_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"


/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDPWM_RED(uint16_t PWMVlue);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDPWM_Green(uint16_t PWMVlue);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDPWM_ORG(uint16_t PWMVlue);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDPWM_Yellow(uint16_t PWMVlue);

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_RED(void);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_Green(void);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_ORG(void);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_Yellow(void);

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_RED(void);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_Green(void);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_ORG(void);
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_Yellow(void);




#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

