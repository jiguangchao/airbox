/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ERROR_LIB_H__
#define __ERROR_LIB_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "..\..\MCU\platform.h"
/* USER CODE END Includes */


#define ENOCEAN_GET_WRONG_CHIPID_ERROR                 (0x01)
#define ENOCEAN_GET_WRONG_BASEID_ERROR                 (0x02)
#define ENOCEAN_CAN_NOT_GET_ID_ERROR                   (0x04)

#define SYS_ENOCEAN_HW_BASEID_ERR_MASK                 (0x04000000)
#define SYS_ENOCEAN_HW_CHIPID_ERR_MASK                 (0x02000000)

#define SYS_RUN_FAULT_MASK                             (SYS_ENOCEAN_HW_BASEID_ERR_MASK|SYS_ENOCEAN_HW_CHIPID_ERR_MASK)

#define SYS_TCM310_ERR                                 (0x00010000)
/* ########################## Assert Selection ############################## */

/*******************************************************************/ 

/****************************END MAIN DEFINES*******************************/



/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrSendSetTime(uint32_t *pu32ErrTime,uint32_t u32ErrTimeSet);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrOverSetTime(uint32_t *pu32ErrOverTime,uint32_t u32ErrOverTimeSet);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t ErrOverTime(uint32_t u32ErrTime);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrTriggerTime(uint32_t *pu32ErrTime);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrSetByCnt(uint8_t *pu8ErrCnt,uint8_t u8ErrCntMax,uint32_t *pu32Err,uint32_t u32ErrMask);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrSet(uint32_t *pu32Err,uint32_t u32ErrMask);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrClear(uint8_t *pu8ErrCnt,uint32_t *pu32Err,uint32_t u32ErrMask);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t ErrGetStatus(uint32_t u32Err,uint32_t u32ErrMask);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t ErrSendMessage(uint32_t *pu32ErrTime,uint32_t u32ErrTimeMax,uint32_t u32Err,uint32_t u32ErrMask);


#endif /* __ERROR_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
