
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_SWITCH_H__
#define __BSP_SWITCH_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"


/**
 * @brief
 * @param
 * @retval None
 */
uint8_t SwitchScan(void);
/**
 * @brief
 * @param
 * @retval None
 */
void SwitchReadPinStatus(uint8_t *pu8Status);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t KeyReadPin(void);


#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
