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
#ifndef __SYS_ERROR_H__
#define __SYS_ERROR_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"
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





/**
  * @brief
  * @param
  * @retval None
  */
void SysytemError(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SysErrorTime_1000ms(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SysErrorNeedManualClear(void);

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SysErrorManualClearID(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SysErrorManualClear(void);
#endif /* __SYS_ERROR_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
