/*!
*****************************************************************
                        $Name$
                        $Revision: 27279 $
                        $Date: 2015-03-03
    \file               Mixed_EEP.h
    \brief              EEP management functions prototypes
    \author             Zhoujinbang
    <b>Company:</b>\n   Menred GmbH\n
****************************************************************
*/
#ifndef _EEP_D201XX_H_
#define _EEP_D201XX_H_

#include "esp3_libCommon.h"
#include "..\Learn/EnOceanLearn.h"

#define EEP_D201XX_DIMMING_ENABLE                              (0)
#define RPS_TOG_REDUNDACY_TIME                                 (500)

#define PIR_LEARN_NO_KEY_TIME_DELAY_DEFAULT                    (3600)
/* channel power on state,Refer EEP:D2-01-XX, cmd = 0x02 */
typedef enum
{
    eCHANNEL_POWER_ON_DEFAULT_OFF = 0,
    eCHANNEL_POWER_ON_DEFAULT_ON,
    eCHANNEL_POWER_ON_DEFAULT_PREVIOUS,
}eChannelPowerOnDefault_TYPE;
/*
typedef enum
{
    eCHANNEL_STATE_IDLE = 0,
    eCHANNEL_STATE_ON ,
    eCHANNEL_STATE_OFF ,
    eCHANNEL_STATE_TOG ,

}eCHANNEL_STATE_TYPE;
*/

typedef enum
{
    eCHANNEL_VALUE_ON  = 100,
    eCHANNEL_VALUE_OFF = 0,
}eCHANNEL_VALUE_TYPE;

typedef enum
{
    eCHANNEL_STATE_IDLE = 0,
    eCHANNEL_STATE_ON ,
    eCHANNEL_STATE_OFF ,
    eCHANNEL_STATE_TOG ,
    
    //eDALI_CMD_STD_ON                       ,
    eDALI_CMD_STD_OFF                       ,
    eDALI_CMD_STD_UP                        ,
    eDALI_CMD_STD_DOWN                      ,  
    eDALI_CMD_STD_STEP_ON                   ,  
    eDALI_CMD_STD_STEP_DOWN                 ,  
    eDALI_CMD_STD_RECAL_MAX_LEVEL           ,  
    eDALI_CMD_STD_RECAL_MIN_LEVEL           ,
    eDALI_CMD_STD_STEP_DOWN_OFF             ,  
    eDALI_CMD_STD_ON_AND_STEP_UP            ,  
    eDALI_CMD_STD_ENABLE_DAPC_SEQUENCE      ,  
    eDALI_CMD_STD_GOTO_LAST_ACTIVE_LEVEL    ,

    eDALI_EXTENDED_CMD_COLOUR_T_COOLER      ,
    eDALI_EXTENDED_CMD_COLOUR_T_WARMER      ,
    //eDALI_EXTENDED_CMD_COLOUR_T_SET         ,

    //eDALI_CMD_RGB_SHIFT_UP                  ,
    //eDALI_CMD_RGB_SHIFT_DOWN                ,

    /* receive rock */
    eCMD_DIMMING_SET_LUX  ,
    eCMD_DIMMING_SET_INCREASE  ,// useful the dimming set, and auto increase
    eCMD_DIMMING_SET_DECREASE  ,// useful the dimming set, and auto decrease
    eCMD_DIMMING_SET_COLOR_T  ,
    eCMD_DIMMING_SET_RGB_ALL,
    eCMD_DIMMING_SET_INIT, 

}eCMD_LIGHT_TYPE;

typedef enum
{
    eRELAY_COIL_RELEASE_STATE = 0  ,
    eRELAY_COIL_START              ,
    eRELAY_COIL_WAIT_CNT           ,
    eRELAY_COIL_OUT                ,
    eRELAY_COIL_WAIT_RELEASE_STATE ,
    eRELAY_COIL_RELEASE_DELAY_STATE,
}eRELAY_COIL_TYPE;

typedef enum
{
    eDIMMING_TRIAC_CMOS_TYPE,    
    eDIMMING_DALI_LUX,
    eDIMMING_DALI_LUX_AND_COLOR,
    eDIMMING_DALI_RGB,
    eDIMMING_DALI_RGBW,
    eDIMMING_0_10V,
    eDIMMING_DALI_DT8_RGB,
}eDIMMING_TYPE;

typedef enum
{
    eIO_IDLE = 0,
    eIO_RELAY,
    eIO_DIMMING,
    eIO_ROCK,
    eIO_GPIO,
}eIO_TYPE;

enum
{
    eIO_0 = 0,
    eIO_1,
    eIO_2,
    eIO_3,
    eIO_4,
    eIO_5,
    eIO_6,
    eIO_7,
    eIO_8,
    eIO_9,
    eIO_10,
    eIO_11,
    eIO_12,
    eIO_13,
    eIO_14,
    eIO_15,
    eIO_16,
    eIO_17,
    eIO_18,
    eIO_19,
    eIO_20,
    eIO_21,
    eIO_22,
    eIO_23,
    eIO_24,
    eIO_25,
    eIO_26,
    eIO_27,
    eIO_28,
    eIO_29,
    eIO_30,    
};


//#pragma pack(1)
typedef struct
{
    /* 继电器线圈供电到触点闭合时间，一般小于5ms,用于触点闭合时计算时间 */
    uint8_t  u8CoilDelayOn;
    /* 继电器线圈断电到触点断开时间，一般小于5ms,用于触点断开时计算时间 */
    uint8_t  u8CoilDelayOff;
    
} RelaySet_Typedef;


typedef struct
{
    /* 调光时间1 */
    uint8_t u8DimmerTim1;
    /* 调光时间2 */
    uint8_t u8DimmerTim2;
    /* 调光时间3 */
    uint8_t u8DimmerTim3;

    uint8_t u8Time;
    //uint8_t u8RockTime;
    /* 线性值 */
    /* 调光起始值 */
    uint8_t :0;
    uint8_t u7LimitMin:7;
    uint8_t u1LimitMinSetFlag:1;
    /* 调光上次输出起始值 */    
    /* 调光最大值 */
    uint8_t :0;
    uint8_t u7LimitMax:7;
    uint8_t u1LimitMaxSetFlag:1;
    // 0: triac ; 1: dali lux ; 2: dali color T ; 3: dali rgb ; 4:Dali rgbw
    eDIMMING_TYPE  eType;

    uint8_t  u8ArcLevelStep;
    uint16_t u16LongChangeTime;
    uint16_t u16ColorTemperatureLongChangeTime;

    uint16_t u16ColorTemperatureMax;
    uint16_t u16ColorTemperatureMin;
    uint16_t u16ColorTemperatureStep;
    
    uint8_t  u8FadeTime;
    uint8_t  u8FadeRate;

    uint8_t  u8FailureLevel;    
    uint8_t  u8PowerOnLevel;
    uint8_t  u8PowerMaxLevel;
    uint8_t  u8PowerMinLevel;
    
    uint32_t  u32DALIGroupHighMask;
    uint32_t  u32DALIGroupLowMask;
    
    
} DimmerSet_Typedef;


typedef union
{
    struct
    {
        
        uint8_t u8Type                    ;

        uint8_t :0;        
        uint8_t u1TaughtInDevs           :1;
        uint8_t u2ExternalPushButton     :2; // only support switch 
        
        uint8_t u1LocalControl           :1;
        uint8_t u2DefaultState           :2;
        uint8_t u1State2Switch           :1;

        uint8_t u1PowerFailure           :1; // not support
        uint8_t :0;
        uint8_t u1PowerFailureDetection  :1; // not support
        uint8_t u1UserInterfaceIndication:1; // not support
        uint8_t u1Rock2Rps               :1;
        uint8_t u1SensorDisable          :1;

        uint8_t :0;
        uint16_t u16LightOnDisableTime;
        uint16_t u16LightOffDisableTime;

        uint16_t u16AutoOff                 ;
        uint16_t u16OffDelay                ;
        
        union
        {
            RelaySet_Typedef   Relay;
        
            DimmerSet_Typedef  Dimmer;        
        };
    };
    uint32_t u32Words[12];
}IOProfile_TYPE;
//#pragma anon_unions//在使用到带union的结构体定义时，在预定义部分一定要有“#pragma anon_unions”这样一句，否则编译通不过
typedef struct
{ 
    IOProfile_TYPE          ;

    uint8_t  u8DataUpdate   ;
    
    

} IOProfile_Typedef;

/************************************************************/ 

typedef struct
{
    //! 
    eRELAY_COIL_TYPE  eOutState;
    /* coil */

    /* 磁保持继电器线圈通电到释放计数器，单位 1ms */
    uint8_t  u8ReleaseCnt;   // !!!  1ms
    /* 继电器由关闭到打开保护时间 */
    uint8_t  u8ProtectDelayOn; //!!! 0.5s
    uint8_t  u8ProtectDelayOnSet; //!!! 0.5s
    /* 过零时触电保护数器 */
    uint8_t  u8CoilCnt;
    
    uint8_t  u8CoilDelayOnRun;
    uint8_t  u8CoilDelayOffRun;
    /*  */
    uint16_t u16CoilFbDetectOverCnt;
    /*  */
    uint8_t  u8CoilDetectState;
    //-----------
    uint16_t u16ZeroInterrupt2FbCnt;
    uint8_t  u8FbState;
    //uint8_t  u8CoilDelayOnTimeSetState;
    //-----------

    /*  */
    uint8_t  u8ACFbTimeCount;
    /*  */
    uint8_t  u8ACFbErrCnt;

    uint8_t  u8ZeroPiontCount;

} RelayRun_Typedef;


typedef struct
{
    //uint8_t  u8Value;
    //uint8_t  u8VldSetValue;
    
    uint16_t u16ColorTemperature;

    uint8_t   u8HSV_Saturation;
    uint16_t  u16HSV_Hue;

    uint8_t  u8RedValue;
    uint8_t  u8GreenValue;
    uint8_t  u8BlueValue;
    //uint8_t  u8WhiteValue;

} DimmerRun_Typedef;



typedef struct
{   
    
    //! 
    eCMD_LIGHT_TYPE   eOutCmd;
    //eCMD_LIGHT_TYPE   eOutCmdPre;
    //eCMD_LIGHT_TYPE   u8CmdRedundacyTime;
    uint8_t  :0;
    uint8_t           u8NeedProcess:1;
    uint8_t           u1LrnType    :1;
    uint8_t           u2OutMode    :2;
    uint8_t           u3Key        :3;
    uint8_t  :0;
    uint8_t           u1RockProcess:1;
    uint8_t           u2RockState  :2;
    uint8_t           u3RockLongState:3; 
    uint8_t  :0;

    uint8_t           u8Event;
    uint16_t          u16RedundacyTime ;
    uint16_t          u16RockTime;    
    uint32_t          u32ID;


    uint32_t          u32RandSendPeriod;

    //! 
    //eRELAY_COIL_TYPE  eRelayOutState;

    uint8_t           :0;
    uint8_t           u1ConfigSearch:1;
    //! 
    uint8_t           u1AutoOffState:1;
    //! 
    uint8_t           u1OffDelayState:1;
    //!
    uint8_t           u2ErrCount:2;
    uint8_t           u2ErrorLevel:2;

    uint16_t  :0;    
    
    //! 
    uint8_t  u8ExeValue;
    //! 
    uint8_t  u8OutValue;
    //!
    uint8_t  u8OutTime;
    //! 
    uint16_t u16AutoOff;
    //! 
    uint16_t u16OffDelay;
    //! 
    uint16_t u16LightOnDisableTime;
    //! 
    uint16_t u16LightOffDisableTime;
          
    union
    {
        //! 
        RelayRun_Typedef    Relay;
    
        DimmerRun_Typedef   Dimmer;
    
    };
} IORun_Typedef;
//! 

//#pragma pack()

/******************************************************************/

/***********************************************************************/
 
/***********************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChannelNumMax(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_SettingsSaveNVM(IOProfile_Typedef *pIOProfile,uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_SetOneChannelCmdBy4BSPIR(ID_SEARCH_TYPE *pSearchOut,uint8_t *p8Data,IORun_Typedef *pIO);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_SetAllChannelCmdByPIR(Radio_Typedef *pRadio,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetSensorDisableTimeByManual(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChannelCmdByRPSLeftInfo(Radio_Typedef const *pRadio,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChannelCmdByRPSRightInfo(Radio_Typedef const *pRadio,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetChanneByRPSReleaseInfo(Radio_Typedef const *pRadio,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetRelayCmdByRPSInfo(IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_SetAllChannelCmdBy1BS(Radio_Typedef const *pRadio,IORun_Typedef *pIO);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetChanneAutoOffTime(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval
  */
uint8_t EEPD201XX_GetChanneAutoOffValue(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval
  */
uint8_t EEPD201XX_GetChanneOffDelayValue(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval
  */
uint8_t EEPD201XX_GetChannelAutoOffAndDelayOff(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChanneCmdByVLDInfo(Radio_Typedef const *pRadio);

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_ReceiveAndResponse(Radio_Typedef *pRadio,IOProfile_Typedef *pIOProfile,IORun_Typedef *pIO);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t VLD_ActuatorResponseProcess(uint8_t *p8Data,uint8_t u8Cmd,uint8_t u8Channel,IOProfile_Typedef *pIOProfile,IORun_Typedef *pIO);

/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetOutputCmd_01(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile,IORun_Typedef *pIO);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetLocal_02(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorQueryStatusResponse_04(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile,IORun_Typedef *pIO,uint8_t u8Value);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetExternalInterfaceSettingsCmd_0B(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorExternalInterfaceSettingsResponseCmd_0D(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_ActuatorExtendFunctionCmd_0F(uint8_t *p8Data,uint8_t u8ChannelMax,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetDimmingLimitsCmd_0F00(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorDimmingLimitsQueryCmd_0F01(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_ActuatorDimmingLimitsResponseCmd_0F02(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile);


#endif
