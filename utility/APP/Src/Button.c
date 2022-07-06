
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
#include "KeyLedDipDectTemp.h"
#include "Dataconfigure.h"
//#include "Button.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

Key_Typedef Key;
Led_Typedef Led;
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief
  * @param
  * @retval None
  */
#if 0
uint8_t KEY_Process(IORun_Typedef *pIO)
{
  /*
	uint8_t u8i;

    switch ( KEY_ReadState() )
	{
	case eKEY_EXE_IDLE:
		break;

    case eKEY_EXE_RELAY_TEST:
        
        if ( Key.pDev->u8LearnChannel < RELAY_OUT_NUMS)
        {
            pIO[Key.pDev->u8LearnChannel].eOutCmd = eCHANNEL_STATE_ON;   
            Key.pDev->u8LearnChannel++;         
        }
        else
        {
            Key.pDev->u8LearnChannel = 0;
            for (u8i = 0; u8i < RELAY_OUT_NUMS; u8i ++)
            {
                pIO[u8i].eOutCmd = eCHANNEL_STATE_OFF;                
            }
        }
        EEPD201XX_GetSensorDisableTimeByManual(Key.pDev->u8LearnChannel,pIO,IOProfile);
        
		break;


    case eKEY_EXE_RPT_CHANGE:
        Key.pDev->Cfg.u8Repeater++;
        if ( Key.pDev->Cfg.u8Repeater >= 2 )
        {
            Key.pDev->Cfg.u8Repeater = 0;
        }

        EnOcean_PushData2Queue(eQUEUE_MODIFY_REAPTER, NULL);
        Key.pDev->u8CfgUpdate = 1;
        break;
    case eKEY_EXE_LRN_MODE_CHANGE:
        Key.pDev->u8LearnMode++;
        if ( Key.pDev->u8LearnMode >= 4 )
        {
            Key.pDev->u8LearnMode = 0; 
        }
        break;
    case eKEY_EXE_CHANNEL_CHANGE:
        Key.pDev->u8LearnChannel++;
        if ( Key.pDev->u8LearnChannel >= 4 )
        {
            Key.pDev->u8LearnChannel = 0;
        }
        break;

	case eKEY_EXE_CLEAR_ALL:
		break;

    case eKEY_EXE_SEND_INFO:
		break;

    case eKEY_EXE_RESET:
		break;

    case eKEY_EXE_ADDRESS_SET:
        
    #ifdef CASCADE_MASTER
        Key.pDev->Cfg.u8ModbusPhyAdd++;
        if ( Key.pDev->Cfg.u8ModbusPhyAdd >= 32 )
        {
            Key.pDev->Cfg.u8ModbusPhyAdd = 17;
        }
    #else   
        Key.pDev->Cfg.u8CascadePhyAdd++; 
        if ( Key.pDev->Cfg.u8CascadePhyAdd >= 10 )
        {
            Key.pDev->Cfg.u8CascadePhyAdd = 1;
        }
        Key.pDev->u8CfgUpdate = 1;
    #endif
		break;
    
	default:
		break;
	}
  */
    return !OK;
}
#endif
/**
  * @brief
  * @param
  * @retval None
  */
#if 0
eKEY_VALUE_TYPE KEY_Scan(void)
{
    /*
    uint8_t         u8ButtonPin;
	eKEY_VALUE_TYPE eKeyPush;

    u8ButtonPin = 0;
    eKeyPush = eNONE_DOWN_VALUE;

    if (0 == LL_GPIO_IsInputPinSet(KEY_LRN1_GPIO,KEY_LRN1_PIN))
    {
        u8ButtonPin |= 0x01;
    }
    if (0 == LL_GPIO_IsInputPinSet(KEY_LRN2_GPIO,KEY_LRN2_PIN))
    {
        u8ButtonPin |= 0x02;
    }
    if (0 == LL_GPIO_IsInputPinSet(KEY_SET_GPIO,KEY_SET_PIN))
    {
        u8ButtonPin |= 0x04;
    }
    eKeyPush = (eKEY_VALUE_TYPE)u8ButtonPin;
   */

	//return eKeyPush;
}
#endif
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t KEY_ReadPinStatus(uint8_t *pu8Button)
{
    uint8_t u8Pin;
    static uint8_t u8PinCount;
    static uint8_t u8PinPre;

    u8Pin = KEY_Scan();

    if ( u8PinPre != u8Pin )
    {
        u8PinCount = 0;
    }
    else
    {
        if ( u8PinCount < 0xFF )
        {
            u8PinCount++;
        }
    }

    u8PinPre = u8Pin;

	if (u8PinCount < 50)
	{
        u8Pin = 0;
	}
    else
    {
        //u8Pin |= 0x80;
        //u8PinCount = 0;
        *pu8Button = u8Pin;
        return OK;
    }
	return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_ReadState(void)
{
    eKEY_EXE_TYPE eKeyExeState = eKEY_EXE_IDLE;

    if ( !Key.u16NoKeyExitCount )
    {        
        KEY_SetState(eSTATE_IDLE);
    }

    if ( OK != KEY_ReadPinStatus(&Key.u8Value) )
    {
        eKeyExeState = eKEY_EXE_IDLE;
        return eKeyExeState;
    }
    Key.u8Value &= 0x07;
    
    if ( eNONE_DOWN_VALUE != Key.u8Value )
    {                
        if ( Key.u8Value != Key.u8ValuePre )
		{
            Key.u16NoKeyExitCount = KEY_NO_EXIT_TIME;
            Key.u8ShortDownCount = 0;
            Key.u8LongDownCount = 0;            
            eKeyExeState = KEY_StateShort();
		}
        else
        {            
            eKeyExeState = KEY_StateLong();
		}        
	}
    else
    {
        Key.u8ShortDownCount = 0;
        Key.u8LongDownCount = 0;
    }
	
    Key.u8ValuePre = Key.u8Value;

    return eKeyExeState;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++ShortEvent+++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateShort(void)
{
	if ( eLRN1_KEY_VALUE == Key.u8Value )
	{
        return KEY_StateLrn1Short();
	}
#ifdef CASCADE_MASTER    
    else if ( eLRN2_KEY_VALUE == Key.u8Value )
	{
        return KEY_StateLrn2Short();
	}
    else if ( eREPEAT_KEY_VALUE == Key.u8Value )
	{
        return KEY_StateRepeatShort();
	}
#else
    else if ( eLRN2_KEY_VALUE == Key.u8Value )
    {
        return KEY_StateDIModeShort();
    }
#endif    
    else if ( eSET_KEY_VALUE == Key.u8Value )
	{
        return KEY_StateSetShort();
	}

    return eKEY_EXE_IDLE;
}
/**
  * @brief
  * @param
  * @retval None
  */
#if 0
eKEY_EXE_TYPE KEY_StateLrn1Short(void)
{
    if ( eSTATE_IDLE == (Key.pDev->u8State) )
    {
        return eKEY_EXE_RELAY_TEST;
    }
    else if ( eSTATE_LOCAL_CHANNEL_LRN == Key.pDev->u8State )
    {
        Key.u16NoKeyExitCount = KEY_NO_EXIT_TIME;
        return eKEY_EXE_CHANNEL_CHANGE;
    }    
    else if ( (eSTATE_RESET == Key.pDev->u8State) 
              || (eSTATE_QUERY_LOCAL_ADDRESS == Key.pDev->u8State) )
    {
        KEY_SetState(eSTATE_IDLE);
    }

    return eKEY_EXE_IDLE;
}
#endif

#if 0
#ifdef CASCADE_MASTER
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateLrn2Short(void)
    {
        if ( eSTATE_IDLE == Key.pDev->u8State )
        {
            return eKEY_EXE_EXPAND_CHANNEL_TEST;
        }
        else if ( eSTATE_EXPAND_CHANNEL_LRN == Key.pDev->u8State )
        {
            return eKEY_EXE_EXPAND_CHANNEL_CHANGE;
        }
        else if (  (eSTATE_RESET == Key.pDev->u8State ) 
                 ||(eSTATE_QUERY_LOCAL_ADDRESS == Key.pDev->u8State ) )
        {
            KEY_SetState(eSTATE_IDLE);
        }
        return eKEY_EXE_IDLE;
    }
#else
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateDIModeShort(void)
    {
        if ( eSTATE_IDLE == Key.pDev->u8State )
        {
            KEY_SetState(eSTATE_QUERY_DI_MODE);
        }
        else if (  (eSTATE_RESET == Key.pDev->u8State) 
                 ||(eSTATE_WAIT_SET_DI_MODE == Key.pDev->u8State) )
        {
            KEY_SetState(eSTATE_IDLE);
        }
        return eKEY_EXE_IDLE;
    }
#endif   

#endif
/**
  * @brief
  * @param
  * @retval None
  */
#if 0
eKEY_EXE_TYPE KEY_StateSetShort(void)
{
    if ( eSTATE_IDLE == Key.pDev->u8State )
    {
        Key.u16NoKeyExitCount = KEY_QUERY_TIME;
        KEY_SetState(eSTATE_QUERY_LOCAL_ADDRESS);
    }
    else if ( eSTATE_LOCAL_CHANNEL_LRN == Key.pDev->u8State)
    {
        Key.u16NoKeyExitCount = KEY_NO_EXIT_TIME;
        return eKEY_EXE_LRN_MODE_CHANGE;
    }
#ifdef CASCADE_MASTER    
    else if ( eSTATE_EXPAND_CHANNEL_LRN == Key.pDev->u8State )
    {
        return eKEY_EXE_LRN_MODE_CHANGE;        
    }
#endif        
    else if ( eSTATE_ADDRESS_WAIT_SET == Key.pDev->u8State )
    {
        Key.u16NoKeyExitCount = KEY_NO_EXIT_TIME;
        KEY_SetState(eSTATE_ADDRESS_SET);
    }
    else if ( eSTATE_ADDRESS_SET == Key.pDev->u8State )
    {
        Key.u16NoKeyExitCount = KEY_QUERY_TIME;
        return eKEY_EXE_ADDRESS_SET;
    }
    else if ( eSTATE_QUERY_LOCAL_ADDRESS == Key.pDev->u8State )
    {
        Key.u16NoKeyExitCount = KEY_QUERY_TIME;
    }    
    else if ( eSTATE_RESET == Key.pDev->u8State) 
    {
        KEY_SetState(eSTATE_IDLE);
    }

    return eKEY_EXE_IDLE;
}
#ifdef CASCADE_MASTER
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateRepeatShort(void)
    {
        if ( eSTATE_REPEAT == Key.pDev->u8State )
        {
            return eKEY_EXE_RPT_CHANGE;
        }
        return eKEY_EXE_IDLE;        
    }
#endif

#endif
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++LongEvent+++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateLong(void)
{
    if ( eLRN1_KEY_VALUE == Key.u8Value )
    {
        return KEY_StateLrn1Long();
    }
#ifdef CASCADE_MASTER    
    else if ( eLRN2_KEY_VALUE == Key.u8Value )
    {
        return KEY_StateLrn2Long();
    }
    else if ( eREPEAT_KEY_VALUE == Key.u8Value )
    {
        return KEY_StateRepeatLong();
    }
#else
    else if ( eLRN2_KEY_VALUE == Key.u8Value )
    {
        return KEY_StateDIModeLong();
    }
#endif    
    else if ( eSET_KEY_VALUE == Key.u8Value )
    {
        return KEY_StateSetLong();
    }
    
    return eKEY_EXE_IDLE;
}

/**
  * @brief
  * @param
  * @retval None
  */
#if 0
eKEY_EXE_TYPE KEY_StateLrn1Long(void)
{
    if ( Key.u8ShortDownCount >= KEY_SET_LRN_GOTO_TIME )
    {
        Key.u8LongDownCount += KEY_SET_LRN_GOTO_TIME;
        Key.u8ShortDownCount = 0;

        if ( Key.u8LongDownCount <= (KEY_SET_LRN_GOTO_TIME + 10) )
        {
            if ( ( eLEARN_STATUS_ADD_SUCCESS == Key.pDev->u8LearnState )||( eLEARN_STATUS_DEL_SUCCESS == Key.pDev->u8LearnState ) )
            {
                
            }
            else if ( eSTATE_IDLE == Key.pDev->u8State )
            {
                Key.pDev->u8LearnChannel = 0;
                Key.pDev->u8LearnState = eLEARN_STATUS_IDLE;
                KEY_SetState(eSTATE_LOCAL_CHANNEL_LRN);
            }
            else if ( eSTATE_LOCAL_CHANNEL_LRN == Key.pDev->u8State )
            {
                KEY_SetState(eSTATE_IDLE);
            }
            return eKEY_EXE_IDLE;
        }
        else if ( Key.u8LongDownCount >= KEY_RESET_TIME )
        {
            if ( eSTATE_LOCAL_CHANNEL_LRN == Key.pDev->u8State )
        	{
                KEY_SetState(eSTATE_RESET);
                return eKEY_EXE_CLEAR_ALL;
        	}
        }
    }

    return eKEY_EXE_IDLE;
}

#ifdef CASCADE_MASTER
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateLrn2Long(void)
    {
        if ( Key.u8ShortDownCount >= KEY_SET_LRN_GOTO_TIME )
        {
            Key.u8LongDownCount += KEY_SET_LRN_GOTO_TIME;
            Key.u8ShortDownCount = 0;

            if ( Key.u8LongDownCount <= (KEY_SET_LRN_GOTO_TIME + 10) )
            {
                if ( ( eLEARN_STATUS_ADD_SUCCESS == Key.pDev->u8LearnState )||( eLEARN_STATUS_DEL_SUCCESS == Key.pDev->u8LearnState ) )
                {
                    
                }
                else if ( eSTATE_IDLE == Key.pDev->u8State )
                {
                    Key.pDev->u8LearnChannel = 4;
                    Key.pDev->u8LearnState = eLEARN_STATUS_IDLE;
                    KEY_SetState(eSTATE_EXPAND_CHANNEL_LRN);
                }
                else if ( eSTATE_EXPAND_CHANNEL_LRN == Key.pDev->u8State  )
                {
                    KEY_SetState(eSTATE_IDLE);
                }
                return eKEY_EXE_IDLE;
            }
            
        }
        return eKEY_EXE_IDLE;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateRepeatLong(void)
    {
        if ( Key.u8ShortDownCount >= KEY_REPEAT_TIME )
        {
            if ( eSTATE_IDLE == Key.pDev->u8State )
            {
                KEY_SetState( eSTATE_REPEAT);
            }
        }
        return eKEY_EXE_IDLE;
    }
#else
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateDIModeLong(void)
    {
        if ( Key.u8ShortDownCount >= KEY_SET_LRN_GOTO_TIME )
        {
            Key.u8LongDownCount += KEY_SET_LRN_GOTO_TIME;
            Key.u8ShortDownCount = 0;

            if ( Key.u8LongDownCount <= (KEY_SET_LRN_GOTO_TIME + 10) )
            {
                if ( eSTATE_IDLE == Key.pDev->u8State )
                {
                    Key.pDev->u8LearnChannel = 4;
                    KEY_SetState(eSTATE_SET_DI_MODE);
                }
                else if ( (eSTATE_SET_DI_MODE == Key.pDev->u8State)  )
                {
                    KEY_SetState(eSTATE_IDLE);
                }
                return eKEY_EXE_IDLE;
            }
            
        }
        return eKEY_EXE_IDLE;
    }
#endif
#endif
/**
  * @brief
  * @param
  * @retval None
  */
#if 0
eKEY_EXE_TYPE KEY_StateSetLong(void)
{
    if ( Key.u8ShortDownCount >= KEY_LONG_TIME )
    {
        if ( eSTATE_QUERY_LOCAL_ADDRESS == Key.pDev->u8State )
        {
            KEY_SetState( eSTATE_ADDRESS_WAIT_SET);
        }
        else if ( eSTATE_ADDRESS_SET == Key.pDev->u8State )
        {
            KEY_SetState( eSTATE_IDLE);
        }
        
    }
    else
    {
        //Key.u16NoKeyExitCount = KEY_QUERY_TIME;    
    }
    return eKEY_EXE_IDLE;
} 
/**
  * @brief
  * @param
  * @retval None
  */
void KEY_SetState(uint8_t u8SetMenu)
{
    Key.pDev->u8State = (eRUN_STATE_TYPE)u8SetMenu;
    if ( eSTATE_IDLE == Key.pDev->u8State )
    {
        Led.u16Mask = 0;
        Key.pDev->u8LearnState = eLEARN_STATUS_IDLE;
    }

    if ( (eSTATE_IDLE != Key.pDev->u8State)&&(eSTATE_QUERY_LOCAL_ADDRESS != Key.pDev->u8State) )
    {
        Key.u16NoKeyExitCount = KEY_NO_EXIT_TIME;
    }    
}
#endif
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
  * @brief
  * @param
  * @retval None
  */
void KEY_Time_100ms(void)
{
    if ( Key.u8ShortDownCount < OVF_UINT8_VALUE )
    {
        Key.u8ShortDownCount++;
    }

    if ( Key.u16NoKeyExitCount )
    {
        Key.u16NoKeyExitCount--;
    }
}
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
#if 0
void LED_State(void)
{        
    switch ( Key.pDev->u8State )
    {
        case eSTATE_IDLE                   :
            LED_RelayRun(IORun);
            break;
        case eSTATE_LOCAL_CHANNEL_LRN     :
            if ( eLEARN_STATUS_ADD_SUCCESS == Key.pDev->u8LearnState )
            {
                LED_ManualLearnAddSuccess(Key.pDev->u8LearnChannel);
            }
            else if ( eLEARN_STATUS_DEL_SUCCESS == Key.pDev->u8LearnState )
            {
                LED_ManualLearnDelSuccess(Key.pDev->u8LearnChannel);
            }
            else
            {
                LED_ManualLearnChannel(Key.pDev->u8LearnChannel, Led.u8BlinkState);                
            }
            LED_BlinkState(1);
            LED_SetBlinkFrequence(50);
            LED_ManualLearnMode(Key.pDev->u8LearnMode);
            break;
       
    #ifdef CASCADE_MASTER
        case eSTATE_EXPAND_CHANNEL_LRN    :
            if ( eLEARN_STATUS_ADD_SUCCESS == Key.pDev->u8LearnState )
            {
                LED_ManualLearnAddSuccess(Key.pDev->u8LearnChannel);
            }
            else if ( eLEARN_STATUS_DEL_SUCCESS == Key.pDev->u8LearnState )
            {
                LED_ManualLearnDelSuccess(Key.pDev->u8LearnChannel);
            }
            else
            {
                LED_ManualLearnChannel(Key.pDev->u8LearnChannel, Led.u8BlinkState);
                
            }
            LED_BlinkState(1);
            LED_SetBlinkFrequence(50);
            LED_ManualLearnMode(Key.pDev->u8LearnMode);
            break;
            
        case eSTATE_REPEAT                 :
            LED_BlinkState(1);     
            LED_SetBlinkFrequence(50);
            LED_Repeat(Led.u8BlinkState);
            break;
    #else 
        case eSTATE_SET_DI_MODE:        
            break;
    #endif
        case eSTATE_RESET                  :
            LED_BlinkState(1);     
            LED_SetBlinkFrequence(50);
            LED_Reset(Led.u8BlinkState);
            break;        

        case eSTATE_ADDRESS_WAIT_SET     :
            LED_SetBlinkFrequence(50);
            LED_BlinkState( 6 );   
            if ( Led.u8BlinkState )
            {
                LED_ManualQueryAddress(Led.u8BlinkState%2);
            }
            else
            {
                LED_ManualQueryAddress(1);    
            }
            break;

        case eSTATE_QUERY_LOCAL_ADDRESS  :
        case eSTATE_ADDRESS_SET          :
            LED_ManualQueryAddress(1);
            break;
    }
    
    LED_StateUpdate_Nms(10);
}
#endif
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

        //sTM1617.pu8Led[0] = Led.u16Mask&0xFF;
        //sTM1617.pu8Led[1] = (Led.u16Mask>>8)&0xFF;
        //TM16XX_LEDControl(&sTM1617, TM16XX_CMD_DISPLAY_ON); 
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
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualQueryAddress(uint8_t u8BlinkState)
{
    uint8_t u8Add;

    #ifdef CASCADE_MASTER        
       // u8Add = Key.pDev->Cfg.u8ModbusPhyAdd - 17;
    #else
       // u8Add = Key.pDev->Cfg.u8CascadePhyAdd - 1;
    #endif

    const uint16_t u16SetAddress[] =
    {
        LED_GREEN_1_MASK,
        LED_GREEN_2_MASK,
        LED_GREEN_3_MASK,
        LED_GREEN_4_MASK,

        LED_GREEN_1_MASK|LED_GREEN_2_MASK,
        LED_GREEN_1_MASK|LED_GREEN_3_MASK,
        LED_GREEN_1_MASK|LED_GREEN_4_MASK,
        LED_GREEN_2_MASK|LED_GREEN_3_MASK,
        LED_GREEN_2_MASK|LED_GREEN_4_MASK,
        LED_GREEN_3_MASK|LED_GREEN_4_MASK,
        LED_GREEN_1_MASK|LED_GREEN_2_MASK|LED_GREEN_3_MASK,
        LED_GREEN_1_MASK|LED_GREEN_2_MASK|LED_GREEN_4_MASK,
        LED_GREEN_1_MASK|LED_GREEN_3_MASK|LED_GREEN_4_MASK,
        LED_GREEN_2_MASK|LED_GREEN_3_MASK|LED_GREEN_4_MASK,
        LED_GREEN_1_MASK|LED_GREEN_2_MASK|LED_GREEN_3_MASK|LED_GREEN_4_MASK,
    };

    if ( u8BlinkState )
    {
        Led.u16Mask = u16SetAddress[u8Add];
    }
    else
    {
        Led.u16Mask &= ~LED_ALL_MASK;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnMode(uint8_t u8LearnMode)
{
 
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnAddSuccess(uint8_t u8BlinkNum)
{
    //Led.u16Mask = u16LearnChannel[u8BlinkNum][0];
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnDelSuccess(uint8_t u8BlinkNum)
{
    //Led.u16Mask &= ~u16LearnChannel[u8BlinkNum][0];
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnChannel(uint8_t u8BlinkNum, uint8_t u8BlinkState)
{
    if ( u8BlinkState )
    {
        //Led.u16Mask = u16LearnChannel[u8BlinkNum][0];
    }
    else
    {
        //Led.u16Mask = u16LearnChannel[u8BlinkNum][1];
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ClearAllLearnID(uint8_t u8BlinkState)
{
    if ( u8BlinkState )
    {
        Led.u16Mask = LED_RED_1_MASK|LED_RED_2_MASK|LED_RED_3_MASK|LED_RED_4_MASK;
    }
    else
    {
        Led.u16Mask &= ~LED_ALL_MASK;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void LED_Reset(uint8_t u8BlinkState)
{
    if ( u8BlinkState )
    {
        Led.u16Mask = LED_ALL_MASK;
    }
    else
    {
        Led.u16Mask &= ~LED_ALL_MASK;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
/*
void LED_RelayRun(IORun_Typedef *pIO)
{
    const uint16_t u16ChannelStateLedMask[] = 
    {
        LED_RED_1_MASK, 
        LED_RED_2_MASK, 
        LED_RED_3_MASK, 
        LED_RED_4_MASK, 
    };

    uint8_t u8i = 0;

    for (u8i = 0; u8i < 4; u8i ++)
    {
        if ( pIO[u8i].u8OutValue )
        {
            Led.u16Mask |= u16ChannelStateLedMask[u8i];
        }
        else
        {
            Led.u16Mask &= ~u16ChannelStateLedMask[u8i];
        }
    }
}
*/
#ifdef CASCADE_MASTER
    /**
     * @brief
     * @param
     * @retval None
     */
    void LED_Repeat(uint8_t u8BlinkState)
    {
        switch ( Dev.Cfg.u8Repeater )
        {
        case 0:
            if ( u8BlinkState )
            {
                Led.u16Mask = LED_RED_1_MASK;
            }
            else
            {
                Led.u16Mask &= ~LED_ALL_MASK;
            }
            break;
        case 1:
            if ( u8BlinkState )
            {
                Led.u16Mask = LED_RED_2_MASK;
            }
            else
            {
                Led.u16Mask &= ~LED_ALL_MASK;
            }
            break;
        case 2:
            if ( u8BlinkState )
            {
                Led.u16Mask = LED_RED_1_MASK;
            }
            else
            {
                Led.u16Mask = LED_RED_2_MASK;
            }
            break;
        default:
            Led.u16Mask &= ~LED_ALL_MASK;
            break;
        } 
    }
#endif    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
