/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

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
/*Timer parameter*/
typedef struct
{
    //uint8_t u8Timer_1ms;
    uint32_t u32ms;
    uint8_t u8Cnt_1ms;
    uint8_t u8Cnt_10ms;
    uint8_t u8Cnt_100ms;
    uint8_t u8Timer_100us;
    uint8_t u8Timer_1ms;
    uint8_t u8Timer_10ms;
    uint8_t u8Timer_100ms;
    uint8_t u8Timer_1s;
    uint8_t _u8Second180;

}Timer_Flag_Typedef;

extern Timer_Flag_Typedef TimerFlag;
extern uint8_t u8ModbusPhyAdd;
extern uint8_t u8Parity;
extern uint8_t u8Stops;
extern uint8_t u8BaudID;
extern uint8_t  u8UpdatePort;
extern uint8_t u8CascadePhyAdd;
extern uint16_t u16EnOceanSendLastWaitTime;
/**
  * @brief
  * @param
  * @retval None
  */
void RS485_GetConfigParameter(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void RPL4xInit(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_10ms(void);
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM16_Interrupt_1ms(void);
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM17_Interrupt_100us(void);


/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM14_Interrupt_1ms(void);
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM3_Interrupt_100us(void);

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
