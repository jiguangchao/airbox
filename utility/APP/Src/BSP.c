

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
#include "Led.h"

uint8_t u8I2C_Buff[256];
uint8_t u8TM16XXLedBuff[14];
uint8_t u8TM16XXKey[5];

uint8_t u8SHT20_HBuff[64];
uint8_t u8SHT20_TBuff[64];

Radio_Typedef Radio = {0};
SHT20_Typedef SHT20;

/*! \note  
    *  \param  
    *  \retval  
    *  \retval  
    */
void SHT20_InterfaceInit(void)
{
    SHT20.HwPort.pGetSdaGpio = BSP_SHT20_GetSdaGpio;
    SHT20.HwPort.pGetSclGpio = BSP_SHT20_GetSclGpio;
    SHT20.HwPort.pSetSclHigh = BSP_SHT20_SetSclHigh;
    SHT20.HwPort.pSetSclLow = BSP_SHT20_SetSclLow;
    SHT20.HwPort.pSetSdaHigh = BSP_SHT20_SetSdaHigh;
    SHT20.HwPort.pSetSdaLow = BSP_SHT20_SetSdaLow;

    SHT20.HwPort.pSetSdaInput = BSP_SHT20_SetSdaInput;
    SHT20.HwPort.pSetSdaOutput = BSP_SHT20_SetSdaOut;
    SHT20.HwPort.pWait = Nop_Delay;

    SHT20.p8HData = u8SHT20_HBuff;
    SHT20.p8TData = u8SHT20_TBuff;

    SHT20.eRunState = eSHT20_IDLE;

    I2C_init(&SHT20.HwPort);
    //SHT20_OperationTask(&SHT20, 300, 20);
}

/**
* @brief  per CPU Cycle = 12 OS Cyscles = 0.75us (16MHz System Clock frequency)
* @param
* @retval None
*/
void EnOcean_HardwareReset(void)
{
    volatile unsigned int num;

    ENOCEAN_HARDWARE_RST_ENABLE();
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
    }
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
    }
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
    }
    //HAL_Delay(2);

    ENOCEAN_HARDWARE_RST_DISABLE();
    for (num = 0; num < 0xFFFF; num++)
    {
        ;
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

    EnOceanRun.pu8Reapter = &Dev.Cfg.u8Repeater;
    EnOceanRun.pu32RemanCode = &Dev.Cfg.u32RemanCode;

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
    LED.u32EnoceanFaultCount++;
    
    if (LED.u32EnoceanFaultCount > 50000)
    {
        LedRunMode_FaultAlarm(eLED_RED_YELLOW);
        LED_runmode(&LED);

        if (LED.u32EnoceanFaultCount > 100000)
        {
            LED.u32EnoceanFaultCount = 0;
        }
        
    }
}

/*****************************END OF FILE****/
