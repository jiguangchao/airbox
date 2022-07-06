
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
//#include "KeyLedDipDectTemp.h"
#include "Dataconfigure.h"
#include "BSP_Switch.h"
#include "Key.h"
#include "Led.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
Key_Typedef KEY;
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief
  * @param
  * @retval None     
  */
void Key_Tick1ms(Key_Typedef *pKEY) //Key定时器
{
    if (pKEY->u32KeyTimer)
    {
        pKEY->u32KeyTimer--;
    }
    if (1 == pKEY->u16KeyStartCount)
    {
        pKEY->u16KeyPressTimer++;
    }
}
/**
  * @brief
  * @param
  * @retval None     
  */
void KeyEvent_Scanning(Key_Typedef *pKEY) //Key事件扫描
{
    pKEY->u8KeyState = KeyReadPin();

    switch (pKEY->eKeyEvent)
    {
    case eKEYEVENT_NONE:
        pKEY->eKeyEvent = eKEYEVENT_PRESS;
        break;

    case eKEYEVENT_PRESS: //Key按下
        if (pKEY->u8KeyState == 0)
        {
            pKEY->u32KeyTimer = KEY_JITTER_LIMIT_TIME;
            pKEY->eKeyEvent = eKEYEVENT_JITTER;
        }
        break;

    case eKEYEVENT_JITTER: //Key消抖
        if (pKEY->u32KeyTimer != 0)
        {
            break;
        }
        if (pKEY->u8KeyState == 0)
        {
            //pKEY->u32KeyTimer=KEY_JITTER_LIMIT_TIME;
            Dev.u8State = 2;

            pKEY->u16KeyStartCount = 1;
            //pKEY->eKeyEvent = eKEYEVENT_COUNT;
        }
        else if (1 == pKEY->u8KeyState)
        {
            pKEY->eKeyEvent = eKEYEVENT_COUNT;
        }
        break;

    case eKEYEVENT_COUNT: //Key计数

        if (pKEY->u16KeyPressTimer >= KEY_RESET_TIME)
        {
            LedRunMode_Blink(eLED_ALL , 15);
            DevLoadDefaultSettingsByReset();
            FLASHRUN.u8CfgUpdateFlag = 1;
            FLASHRUN.u8LogUpdateFlag = 1;

            pKEY->eKeyEvent = eKEYEVENT_END;
            break;
        }
        else if (pKEY->u16KeyPressTimer >= KEY_LONG_PRESS_TIME)
        {
            // pKEY->u32KeyTimer=KEY_JITTER_LIMIT_TIME;
            pKEY->u16KeyStartCount = 0;
            pKEY->u16KeyPressTimer = 0;

            pKEY->eHardWareTest = eHWTESTMODE_YES;

            pKEY->eKeyEvent = eKEYEVENT_END;
            break;
        }

        break;

    case eKEYEVENT_END: //Key计数
        pKEY->eKeyEvent = eKEYEVENT_PRESS;
        break;

    default:
        pKEY->eKeyEvent = eKEYEVENT_PRESS;
        break;
    }
}
