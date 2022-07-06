
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

#include "BSP.h"
#include "LedAndButton.h"
#include "Dataconfigure.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


Led_Typedef Led;
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 * @param
 * @retval None
 */
void LED_Time_10ms(void)
{

  Led.u32LedBlinkTime++;

  if (Led.u32LedBlinkTime == 25)
  {
    Led.u8LedBlinkFlag = 1;
  }

  if (Led.u32LedBlinkTime == 50)
  {
    Led.u8LedBlinkFlag = 0;
    Led.u32LedBlinkTime = 0;
  }
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_State(void)
{
  if (0x01 == Led.u8LedBlinkFlag)
  {
    LL_GPIO_SetOutputPin(LED_RED_GPIO, LED_RED_PIN);
    LL_GPIO_SetOutputPin(LED_GREEN_GPIO, LED_GREEN_PIN);
    LL_GPIO_SetOutputPin(LED_ORG_GPIO, LED_ORG_PIN);
    LL_GPIO_SetOutputPin(LED_YELLOW_GPIO, LED_YELLOW_PIN);
  }
  else
  {
    LL_GPIO_ResetOutputPin(LED_RED_GPIO, LED_RED_PIN);
    LL_GPIO_ResetOutputPin(LED_GREEN_GPIO, LED_GREEN_PIN);
    LL_GPIO_ResetOutputPin(LED_ORG_GPIO, LED_ORG_PIN);
    LL_GPIO_ResetOutputPin(LED_YELLOW_GPIO, LED_YELLOW_PIN);
  }
}
/**
  * @brief
  * @param
  * @retval None
  */
#if 0
void LED_StateUpdate_Nms(uint8_t u8Nms)
{
    if ( !Led.u8LedCount )
    {        
        Led.u8LedCount = u8Nms;

        sTM1617.pu8Led[0] = Led.u16Mask&0xFF;
        sTM1617.pu8Led[1] = (Led.u16Mask>>8)&0xFF;
        TM16XX_LEDControl(&sTM1617, TM16XX_CMD_DISPLAY_ON); 
    }
}
#endif
/**
  * @brief
  * @param
  * @retval None
  */
void LED_SetBlinkFrequence(uint8_t u8Frequence)
{
    Led.u8LedBlinkFrequence = u8Frequence;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t LED_BlinkState( uint8_t u8BlinkStateCnt)
{
    static uint8_t u8BlinkCnt;

    if ( Led.u8LedBlinkTime )
    {
        return !OK;
    }

    Led.u8LedBlinkTime = Led.u8LedBlinkFrequence;

    u8BlinkCnt++;
    
    if ( u8BlinkCnt > u8BlinkStateCnt )
    {
        u8BlinkCnt = 0;
    }

    Led.u8BlinkState = u8BlinkCnt;

    return OK;
}

#if 0
Led_Typedef Led;
/* Private function prototypes -----------------------------------------------*/


/**
  * @brief
  * @param
  * @retval None
  */
void LED_Time_10ms(void)
{
    if ( Led.u8LedCount )
    {
        Led.u8LedCount--;
    }

    if ( Led.u8LedBlinkTime )
    {
        Led.u8LedBlinkTime--;
    }
}

/**
  * @brief
  * @param
  * @retval None
  */
void LED_State(void)
{        

}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_StateUpdate_Nms(uint8_t u8Nms)
{
    if ( !Led.u8LedCount )
    {        
        Led.u8LedCount = u8Nms;

        sTM1617.pu8Led[0] = Led.u16Mask&0xFF;
        sTM1617.pu8Led[1] = (Led.u16Mask>>8)&0xFF;
        TM16XX_LEDControl(&sTM1617, TM16XX_CMD_DISPLAY_ON); 
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_SetBlinkFrequence(uint8_t u8Frequence)
{
    Led.u8LedBlinkFrequence = u8Frequence;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t LED_BlinkState( uint8_t u8BlinkStateCnt)
{
    static uint8_t u8BlinkCnt;

    if ( Led.u8LedBlinkTime )
    {
        return !OK;
    }

    Led.u8LedBlinkTime = Led.u8LedBlinkFrequence;

    u8BlinkCnt++;
    
    if ( u8BlinkCnt > u8BlinkStateCnt )
    {
        u8BlinkCnt = 0;
    }

    Led.u8BlinkState = u8BlinkCnt;

    return OK;
}
#endif
/*END OF FILE****/
