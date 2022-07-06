
/*!
*****************************************************************
$Name$
$Revision: 
$Date: 
\file 
\brief  
\author zhoujinbang


<b>Company:</b>\nmenred automation\n
修改记录
1、
2、
3、
4、
5、
6、
*****************************************************************/

/*============================ INCLUDES ======================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"

/* User App */
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
//#include "RS485Expand.h"

#include "EnOceanCascade.h"

#include "Debug.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 


//Dev_Typedef DevE;
/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/




/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */





#ifdef HW_DEBUG


/**
  * @brief
  * @param
  * @retval None
  */
void NVM_SelfTest(void)
{


}
/**
  * @brief
  * @param
  * @retval None
  */
void LearnTabDebug(void)
{
    LearnInfoTab.u8nrIDs                        = 4;

    LearnInfoTab.entry[0].u32SrcId              = 0x050101BA;
    LearnInfoTab.entry[0].u8EepRorg             = 0xF6;
    LearnInfoTab.entry[0].u8EepFun              = 0x02;
    LearnInfoTab.entry[0].u8EepType             = 0x01;
    LearnInfoTab.entry[0].LrnDev.RPS.u1LrnType  = 0x00;
    LearnInfoTab.entry[0].LrnDev.RPS.u5Channel  = 0x00;
    LearnInfoTab.entry[0].LrnDev.RPS.u2OutMode  = 0x00;
    LearnInfoTab.entry[0].LrnDev.RPS.u3Key      = 0x05;

    LearnInfoTab.entry[1].u32SrcId              = 0x050101BA;
    LearnInfoTab.entry[1].u8EepRorg             = 0xF6;
    LearnInfoTab.entry[1].u8EepFun              = 0x02;
    LearnInfoTab.entry[1].u8EepType             = 0x01;
    LearnInfoTab.entry[1].LrnDev.RPS.u1LrnType  = 0x00;
    LearnInfoTab.entry[1].LrnDev.RPS.u5Channel  = 0x01;
    LearnInfoTab.entry[1].LrnDev.RPS.u2OutMode  = 0x00;
    LearnInfoTab.entry[1].LrnDev.RPS.u3Key      = 0x05;

    LearnInfoTab.entry[2].u32SrcId              = 0x050101BA;
    LearnInfoTab.entry[2].u8EepRorg             = 0xF6;
    LearnInfoTab.entry[2].u8EepFun              = 0x02;
    LearnInfoTab.entry[2].u8EepType             = 0x01;
    LearnInfoTab.entry[2].LrnDev.RPS.u1LrnType  = 0x00;
    LearnInfoTab.entry[2].LrnDev.RPS.u5Channel  = 0x02;
    LearnInfoTab.entry[2].LrnDev.RPS.u2OutMode  = 0x00;
    LearnInfoTab.entry[2].LrnDev.RPS.u3Key      = 0x05;

    LearnInfoTab.entry[3].u32SrcId              = 0x050101BA;
    LearnInfoTab.entry[3].u8EepRorg             = 0xF6;
    LearnInfoTab.entry[3].u8EepFun              = 0x02;
    LearnInfoTab.entry[3].u8EepType             = 0x01;
    LearnInfoTab.entry[3].LrnDev.RPS.u1LrnType  = 0x00;
    LearnInfoTab.entry[3].LrnDev.RPS.u5Channel  = 0x03;
    LearnInfoTab.entry[3].LrnDev.RPS.u2OutMode  = 0x00;
    LearnInfoTab.entry[3].LrnDev.RPS.u3Key      = 0x05;
}




/******************************************************************************************************************************/
/******************************************************************************************************************************/
/******************************************************************************************************************************/
/*-------------------------------------------------------STM32G070------------------------------------------------------------*/
/******************************************************************************************************************************/
/******************************************************************************************************************************/
/******************************************************************************************************************************/


#ifdef STM32G070xx

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Relay_070(void)
{
    
    
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */

void Debug_DirectCurrent_070(void)
{
    
    
}
#endif
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */

void Debug_Switch(void)
{
    uint8_t SWState[5] = {0};
    

    SWState[0] = LL_GPIO_IsInputPinSet(SWITCH1_GPIO, SWITCH1_PIN);
    SWState[1] = LL_GPIO_IsInputPinSet(SWITCH2_GPIO, SWITCH2_PIN);
    SWState[2] = LL_GPIO_IsInputPinSet(SWITCH3_GPIO, SWITCH3_PIN);
    SWState[3] = LL_GPIO_IsInputPinSet(SWITCH4_GPIO, SWITCH4_PIN);
   // SWState[4] = LL_GPIO_IsInputPinSet(SWITCH5_GPIO, SWITCH5_PIN);


}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */

void Debug_LedAndKey(void)
{
        
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Enocean(void)
{    
#if 0
    uint8_t u8KeyState[5] = {0};
    EnoceanTxContent_Typedef EnoceanSend;

    TM1617_ReadKey(u8KeyState);
    /* 1  KS5 = 1 */
    if ( (0x01 == u8KeyState[2]) && (0x00 == u8KeyState[3]) )
    {
        EnoceanSend.u8Cmd        = eQUEUE_TEST_TELEGRAM;

        EnoceanSend.u8ChannelID  = 0xAA;
        EnoceanSend.u8BaseID     = 0xBB;
        
        EnoceanSend.u8PageID     = 0xDD;    
        EnoceanSend.u8RegisterID = 0xCC;
        EnoceanSend.u32DstID     = ENOCEAN_BROADCAST_ID;
        EnOceanAddData2Queue(&EnoceanSend);
    }
#endif
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_Usart(void)
{
    /* 
    static uint32_t u32RCont;
    static uint8_t u8Temp;
    uint8_t u8DispData[2] = {0}; 
    if ( u32RCont != RS485Expand.Frame.u32SendCount )
    {
        if ( u8Temp )
        {
            u8Temp = 0;
            u8DispData[0] = 0xF0;
            u8DispData[1] = 0x0F;
            TM16XX_LEDControl(u8DispData, CMD_DISPLAY_OFF);
        }
        else
        {
            u8Temp = 1;
            u8DispData[0] = 0xF0;
            u8DispData[1] = 0x0F;
            TM16XX_LEDControl(u8DispData, CMD_DISPLAY_ON);
        }
        u32RCont = RS485Expand.Frame.u32SendCount;
    }
	*/
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_BlinkLed(void)
{
    
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Debug_GetSystemClock(LL_RCC_ClocksTypeDef *SystemClockT)
{
    LL_RCC_GetSystemClocksFreq(SystemClockT);
}


#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/




