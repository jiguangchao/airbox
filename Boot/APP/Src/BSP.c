

/*!
*****************************************************************
						$Name$
						$Revision: 27601 $
						$Date: 2015-03-02 16:20:57 +0200 (Fr, 18 Jun 2010) $
	\file 				Enocean_ESP.c
	\brief 				MSG management related functions
	\author 			zhoujinbang


    <b>Company:</b>\n	menred automation\n
修改记录
1、
2、
3、
4、
5、
6、
*****************************************************************/

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
/* Includes ------------------------------------------------------------------*/
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"



uint8_t              u8TM16XXLedBuff[19];


//sTM16XX_Typedef      sTM1617;
Radio_Typedef        Radio={0};


#if 0
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XXInterfaceInit(void)
{
    sTM1617.HWPort.pSetStbHigh    = BSP_TM16XX_SetSTBHigh;
    sTM1617.HWPort.pSetStbLow     = BSP_TM16XX_SetSTBLow;
    
    sTM1617.HWPort.pSetClkHigh    = BSP_TM16XX_SetClkHigh;
    sTM1617.HWPort.pSetClkLow     = BSP_TM16XX_SetClkLow;
    
    sTM1617.HWPort.pSetDataInput  = BSP_TM16XX_SetDataInput;
    sTM1617.HWPort.pSetDataOutput = BSP_TM16XX_SetDataOut;
    sTM1617.HWPort.pGetDataGpio   = BSP_TM16XX_GetDataGpio;
    sTM1617.HWPort.pSetDataLow    = BSP_TM16XX_SetDataLow;
    sTM1617.HWPort.pSetDataHigh   = BSP_TM16XX_SetDataHigh;
    
    sTM1617.HWPort.pWait          = Nop_Delay;
    
    sTM1617.pu8Button             = &u8TM16XXLedBuff[14];
    sTM1617.pu8Led                = u8TM16XXLedBuff;
}
#endif

    /**
    * @brief  per CPU Cycle = 12 OS Cyscles = 0.75us (16MHz System Clock frequency)
    * @param
    * @retval None
    */   
    void EnOcean_HardwareReset(void)
    {
        uint8_t u8i;
        ENOCEAN_HARDWARE_RST_ENABLE();
        for (u8i = 0; u8i<255; u8i++)
        {
        }
        //HAL_Delay(2);
        
        ENOCEAN_HARDWARE_RST_DISABLE();
        for (u8i = 0; u8i<255; u8i++)
        {
        }
        //HAL_Delay(1);
    }

    /**
     * @brief  
     * @param
     * @retval None
     */
    void EnOceanModuleInit(void)
    {

        EnOceanRun.pu8Reapter = &u8EnOceanRepeater;
        EnOceanRun.pu32RemanCode = &u32EnOceanRemanCode;

        EnOceanInit();

        EnOceanRun.pStart = BSP_EnOceanSendStart;
        EnOceanRun.pStop = BSP_EnOceanSendStop;
        EnOceanRun.pEnOceanReset = EnOcean_HardwareReset;
        EnOceanRun.pEnOceanError = EnOceanModuleError;

        EnOcean_HardwareReset();
        BSP_EnOceanUsartDMA_Init(Esp3Tx.u8Buff);
        BSP_EnOceanUSART_Init(57600, LL_USART_STOPBITS_1, LL_USART_PARITY_NONE);
        EnOcean_InitGetInfo(&Radio);
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    void EnOceanModuleError(uint16_t u16Err)
    {
                
        #ifndef HW_DEBUG
            IWDG_Reload();
        #endif
        //return OK;
    }

/**
  * @brief  
  * @param
  * @retval None
  */
#if 0
uint32_t GetRandomNum(uint32_t *pu32RngNum,uint32_t u32VarRand,uint32_t u32Base)
{
    if ( LL_RNG_IsActiveFlag_DRDY(RNG) )
    //while ( LL_RNG_IsActiveFlag_DRDY(RNG) )
    {
        *pu32RngNum = LL_RNG_ReadRandData32(RNG);
        *pu32RngNum %= u32VarRand;
        *pu32RngNum += u32Base;

        return OK;
    }
    return !OK;
}
#endif


/*****************************END OF FILE****/
