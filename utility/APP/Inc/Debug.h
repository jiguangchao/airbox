
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H__
#define __DEBUG_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/*******************************************************************/ 

/****************************END MAIN DEFINES*******************************/




 
//extern uint8_t HardwareDebugType;



/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void DebugPageInit(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void DebugInit(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Run(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t Debug_PageSlideEvent(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t Debug_PageUpdateEvent(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Dectect(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Switch(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_LedAndKey(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Relay_030(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Relay_070(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Usart(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_BlinkLed(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Enocean(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_DirectCurrent_030(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_DirectCurrent_070(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_GetSystemClock(LL_RCC_ClocksTypeDef *SystemClockT);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_MenuFlash(void);
/**
  * @brief
  * @param
  * @retval None
  */
void RelayDebug(void);

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
