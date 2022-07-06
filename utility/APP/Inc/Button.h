
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEYLEDDIPDECTTEMP_H__
#define __KEYLEDDIPDECTTEMP_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "Dataconfigure.h"
#include "EnOceanlibInclude.h"

/* time */
#define KEY_SET_LRN_GOTO_TIME       (20)
#define KEY_QUERY_TIME              (100)
#define KEY_LONG_TIME               (50)
#define KEY_CLR_TIME                (100) // 10S
#define KEY_REPEAT_TIME             (100) // 10S
#define KEY_RESET_TIME              (100) // 10S
#define KEY_NO_EXIT_TIME            (300) // 300*100ms = 30S

#ifdef STM32G070xx    
    /* led */
    #define LED_RED_1_MASK                  (0x0400)
    #define LED_RED_2_MASK                  (0x0100)
    #define LED_RED_3_MASK                  (0x0040)
    #define LED_RED_4_MASK                  (0x0010)
    #define LED_GREEN_1_MASK                (0x0800)
    #define LED_GREEN_2_MASK                (0x0080)
    #define LED_GREEN_3_MASK                (0x0200)
    #define LED_GREEN_4_MASK                (0x0020)

#endif

#ifdef STM32G030xx
    /* led */
    #define LED_RED_1_MASK                 (0x0400)
    #define LED_RED_2_MASK                 (0x0080)
    #define LED_RED_3_MASK                 (0x0010)
    #define LED_RED_4_MASK                 (0x0020)
    #define LED_GREEN_1_MASK               (0x0800)
    #define LED_GREEN_2_MASK               (0x0100)
    #define LED_GREEN_3_MASK               (0x0200)
    #define LED_GREEN_4_MASK               (0x0040)
#endif

#define LED_ALL_MASK                    (0x0FF0)
#define LED_OFF_ALL_MASK                (0x0000)

typedef enum
{
    eNONE_DOWN_VALUE = 0,
    eLRN1_KEY_VALUE,
    eLRN2_KEY_VALUE,    
    eREPEAT_KEY_VALUE,
    eSET_KEY_VALUE,
}eKEY_VALUE_TYPE;

typedef enum
{
    eDIP_SWITCH_PIN1 = 0,
    eDIP_SWITCH_PIN2,
    eDIP_SWITCH_PIN3,
    eDIP_SWITCH_PIN4,
    eDIP_SWITCH_PIN5,
}eDIP_SWITCH_VALUE_TYPE;

typedef enum
{
    eSTATE_IDLE = 0,
    eSTATE_EXPAND_CHANNEL_TEST,

    eSTATE_LOCAL_CHANNEL_LRN,
    eSTATE_EXPAND_CHANNEL_LRN,
    eSTATE_QUERY_DI_MODE,
    eSTATE_WAIT_SET_DI_MODE, 
    eSTATE_SET_DI_MODE,
    eSTATE_REPEAT,    
    eSTATE_RESET,    
    eSTATE_QUERY_LOCAL_ADDRESS,
    eSTATE_ADDRESS_WAIT_SET,
    eSTATE_ADDRESS_SET,
}eRUN_STATE_TYPE;

typedef enum
{
    eKEY_EXE_IDLE = 0,
    eKEY_EXE_RELAY_TEST,
    eKEY_EXE_EXPAND_CHANNEL_TEST,
    eKEY_EXE_RPT_CHANGE,
    eKEY_EXE_LRN_MODE_CHANGE,
    eKEY_EXE_CHANNEL_CHANGE,
    eKEY_EXE_EXPAND_CHANNEL_CHANGE,
    eKEY_EXE_CLEAR_ALL,
    eKEY_EXE_SEND_INFO,
    eKEY_EXE_RESET,
    eKEY_EXE_ADDRESS_SET,
    eKEY_EXE_LOCAL_ADDRESS_INQUIRE,
}eKEY_EXE_TYPE;

typedef enum
{
    eDRY_CONTACT_CONTROL_RELAY1 = 0,
    eDRY_CONTACT_CONTROL_RELAY2,
    eDRY_CONTACT_CONTROL_DC,
    eDRY_CONTACT_CONTROL_DC_WITHOUT_RELAY,
    eRESERVED,
}eOUTPUT_EXE_TYPE;

typedef struct
{
    

    uint8_t             u8Value;
    uint8_t             u8ValuePre;

    uint8_t             u8ShortDownCount;
    uint8_t             u8LongDownCount;
    uint16_t            u16NoKeyExitCount;
    /*
    uint8_t             *pu8State;
	uint8_t             *pu8LearnState;
    uint8_t             *pu8LrnMode;
    uint8_t             *pu8Channel;
	uint8_t             *pu8LearnSuccessTime;
    uint8_t             *pu8SetAddress;
    */
    Dev_Typedef         *pDev;

} Key_Typedef;

typedef struct
{
    uint8_t             u8LedCount;
    uint8_t             u8LedBlinkTime;
    uint8_t             u8LedBlinkFrequence;
    uint8_t             u8BlinkState;

    uint16_t            u16Mask;

} Led_Typedef;


extern Key_Typedef Key;
extern Led_Typedef Led;
/********************************************************************************/
/********************************************************************************/
/*-------------------------------------Key--------------------------------------*/
/********************************************************************************/
/********************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_VALUE_TYPE KEY_Scan(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t KEY_ReadPinStatus(uint8_t *pu8Button);
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_ReadState(void);
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateShort(void);
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateLrn1Short(void);
#ifdef CASCADE_MASTER
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateLrn2Short(void);
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateLrn2Long(void);
#else
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateDIModeShort(void);
    /**
     * @brief
     * @param
     * @retval None
     */
    eKEY_EXE_TYPE KEY_StateDIModeLong(void);
#endif    
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateSetShort(void);
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateRepeatShort(void);
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateLong(void);
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateLrn1Long(void);

/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateSetLong(void);
/**
  * @brief
  * @param
  * @retval None
  */
eKEY_EXE_TYPE KEY_StateRepeatLong(void);
/**
  * @brief
  * @param
  * @retval None
  */
void KEY_Time_100ms(void);
/**
  * @brief
  * @param
  * @retval None
  */
void KEY_SetState(uint8_t u8SetMenu);

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t KEY_Process(IORun_Typedef *pIO);


/********************************************************************************/
/********************************************************************************/
/*----------------------------------Led-----------------------------------------*/
/********************************************************************************/
/********************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
void LED_State( void );
/**
  * @brief
  * @param
  * @retval None
  */
void LED_StateUpdate_Nms(uint8_t u8Nms);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_SetBlinkFrequence(uint8_t u8Frequence);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualQueryAddress(uint8_t u8BlinkState);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_Repeat(uint8_t u8BlinkState);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t LED_BlinkState(uint8_t u8BlinkStateCnt);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_RelayRun(IORun_Typedef *pIO);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ClearAllLearnID(uint8_t u8BlinkState);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_Reset(uint8_t u8BlinkState);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnMode(uint8_t u8LearnMode);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnAddSuccess(uint8_t u8BlinkNum);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnDelSuccess(uint8_t u8BlinkNum);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_ManualLearnChannel(uint8_t u8BlinkNum, uint8_t u8BlinkState);
/**
  * @brief
  * @param
  * @retval None
  */
void LED_Time_10ms(void);


#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
