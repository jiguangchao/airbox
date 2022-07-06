

#ifndef __BSP_H__
#define __BSP_H__


/*============================ INCLUDES ======================================*/


/*============================ MACROS ========================================*/
//#define IIC_NOTE       (0)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"
/* Includes ------------------------------------------------------------------*/



extern Radio_Typedef   Radio;

extern SHT20_Typedef SHT20;

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void SHT20_InterfaceInit(void);
/*! \note  
 *  \param  ;
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XXInterfaceInit(void);
/**
* @brief
* @param
* @retval None
*/
void EnOcean_HardwareReset(void);
/**
  * @brief  
  * @param
  * @retval None
  */
void EnOceanModuleInit(void);

/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanModuleError(uint16_t u16Err);
/**
  * @brief  
  * @param
  * @retval None
  */
//uint32_t GetRandomNum(uint32_t *pu32RngNum,uint32_t u32VarRand,uint32_t u32Base);
    





#endif

/*****************************END OF FILE****/