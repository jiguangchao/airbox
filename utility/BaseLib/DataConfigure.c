
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
#include "LightInclude.h"
#include "Dataconfigure.h"



#include "main.h"
#include "EnOceanCascade.h"
#include "RS485Modbus.h"
#include "EnOceanRock.h"



/*************************************************************************************/

/***********************************************************************************/

#pragma pack(1)
/* Clover Dev Setting */
const RegTab_Typedef DevRegTab[]=
{
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_HW_VERSION                ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FW_VERSION                ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FW_DATE                   ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FW_TIME                   ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_ERROR                     ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_RUN_TIME                  ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_ENOCEAN_RSSI              ,    0,     0xFF,          },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_POWER_ON_CNT              ,    0,     0xFFFF,        },    
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FAULT_CNT                 ,    0,     0xFFFF,        },

    {                 REG_PERMISSION_R,REG_VALUE_RANGE_ENABLE , MB_HOLD_LIGHT_NUMS                 ,    0,     3,             },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_LOCK_ENABLE                ,    0,     1,             },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_ENABLE , MB_HOLD_RESET_DEFAULT_CMD          ,    0,     0xFF,          },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_DISABLE, MB_HOLD_RESET_DEFAULT_PASSWORD     ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_DISABLE, MB_HOLD_RESET_DEFAULT_PASSWORD_L   ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_ENOCEAN_BASEID_H          ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_ENOCEAN_BASEID_L          ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_BASEID                    ,    0,     0xFFFF,        },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_BASEID_L                  ,    0,     0xFFFF,        },

    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_ADDRESS            ,    1,     31,            },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_BAUD               ,    0,     7,             },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_STOPS              ,    0,     1,             },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_PARITY             ,    0,     2,             },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_ENOCEAN_REAPER             ,    0,     2,             },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_REMANCODE          ,    0,     0xFFFF,        },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_REMANCODE_L        ,    0,     0xFFFF,        },
                                                                                                                             
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_SEND_PERIOD        ,  100,     0xFF,          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_TAUGHTINDEV        ,    0,     1,             },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_LIGHT_PROTECT_ON_DELAY     ,    0,     20,            },
    {REG_PERMISSION_R|REG_PERMISSION_W, REG_VALUE_RANGE_ENABLE, MB_HOLD_DALI_CHANNEL_NUMS          ,    0,     16,            },
    {REG_PERMISSION_R|REG_PERMISSION_W, REG_VALUE_RANGE_ENABLE, MB_HOLD_TRIAC_CHANNEL_NUMS         ,    0,     8,             },
    {REG_PERMISSION_R|REG_PERMISSION_W, REG_VALUE_RANGE_ENABLE, MB_HOLD_EXPAND_PANEL_NUMS          ,    0,     16,            },

    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_STATE             ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_CMD_WR_ALL        ,    0,     0xFFFF,        }, 

    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_CMD_ADDRESS       ,    0,     0xFFFF,        },     
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_ONLINE_MASK_0_16  ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_ONLINE_MASK_17_31 ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_ONLINE_MASK_32_47 ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_ONLINE_MASK_48_63 ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_DALI_BUS_SEARCH_NUMS       ,    0,     64,            },
    
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_EXPANDE_PANEL_BUTTON_NUMS  ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_EXPANDE_PANEL_RELATE_MASK  ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_EXPANDE_PANEL_SENSOR_TYPE  ,    0,     0xFFFF,        }, 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_EXPANDE_PANEL_MODE         ,    0,     0xFFFF,        },   
#ifdef HW_DEBUG
    
#endif

};


Radio_Typedef         ExpandRadio;

Dev_Typedef           Dev;
SlaverDI_Typedef      SlaverDI[LIGHT_CASCADE_NUMS_MAX];
ExpandPanel_Typedef   ExpandPanel[EXPAND_PANEL_NUMS_MAX];

IORun_Typedef         IORun[LIGHT_CHANNEL_NUMS];
IOProfile_Typedef     IOProfile[LIGHT_CHANNEL_NUMS];
IO_State_Typedef      IOState[LIGHT_CHANNEL_NUMS];

#ifdef CASCADE_MASTER   
    MasterExpandDevCfg_typedef MasterExpandDevCfg;     
    SlaverRelay_Typedef        SlaverRelay[SLAVE_RELAY_NUMS];    
#endif






/***********************************************************************************/

#pragma pack()

uint8_t Dev_GetRegTabSize(void)
{
    return sizeof(DevRegTab)/sizeof(DevRegTab[0]);
}


/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/**
  * @brief
  * @param
  * @retval None
  */
static uint8_t NVM_ReadDevDataCheck(HWCfg_Typedef *pHWInfo);
/**
  * @brief
  * @param
  * @retval None
  */
static uint8_t NVM_ReadIOProfileDataCheck(IOProfile_Typedef *pIOProfile);
/**
  * @brief
  * @param
  * @retval None
  */
static uint8_t NVM_ReadIOStateDataCheck(uint8_t u8ChannelValue);

/*============================ IMPLEMENTATION ================================*/

/**
  * @brief
  * @param
  * @retval None
  */
void NVM_DevRunSave(void)
{
    uint8_t i;

    Dev.Log.u32RunTime++;
    
    TimerFlag._u8Second180++;
    if ( TimerFlag._u8Second180 >= 180 )
    {
        TimerFlag._u8Second180 = 0;
        Dev.u8LogUpdate = 1;
    }
    
    for (i = 0; i < LIGHT_CHANNEL_NUMS; i++)
    {
        if (IOState[i].u8ExeValue > 0)
        {
            IOState[i].u32ChannelRunTime++;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettings(void)
{
    uint8_t i;
    

#ifdef CASCADE_MASTER    
    uint8_t j;
    
    Dev.Cfg.u32RemanCode                    = RM_DEFAULT_REMAN_CODE;
    
    Dev.Cfg.eBaudRateID                     = eBAUD_9600_ID;
    Dev.Cfg.eStops                          = eSTOP_1;
    Dev.Cfg.eParity                         = ePARITY_NONE;    
    
    Dev.Cfg.u8RadioInterval                 = RADIO_SEND_MIN_INTERVAl_DEFAULT;
    Dev.Cfg.u8Repeater                      = 0;    
    Dev.Cfg.u8DALIChannelNums               = DALI_OUT_NUMS;
    
    MasterExpandDevCfg.u8TriacChannelNums              = TRIAC_OUT_NUMS;
    MasterExpandDevCfg.u8ExpandPanelNums               = EXPAND_PANEL_NUMS_MAX;

    for ( i = 0; i < EXPAND_PANEL_NUMS_MAX; i++ )
    {
        MasterExpandDevCfg.u8ButtonNums[i] = 4;
        MasterExpandDevCfg.u8RelateMask[i] = 0x00;

        for (j = 0; j < EXPAND_PANEL_BUTTON_MAX_NUMS; j++)
        {
            MasterExpandDevCfg.u8Mode[i][j]       = 1;
            MasterExpandDevCfg.u8SensorType[i][j] = 1;
        }        
    }
    MasterExpandDevCfg.u8TraicID[0]         = 4; 
    MasterExpandDevCfg.u8TraicID[1]         = 4; 
    MasterExpandDevCfg.u8TraicID[2]         = 0; 
    MasterExpandDevCfg.u8TraicID[2]         = 0; 
#else 
    Dev.Cfg.u8DIRelateMask                  = 0x00;    

    for ( i = 0; i < SLAVE_DI_MAX; i++ )
    {
        Dev.Cfg.u8DISensorType[i] = 0;
        Dev.Cfg.u8DIMode[i]       = 0;
    }
#endif
    Dev.Cfg.u8LightProtectDelayOn           = RELAY_OFF_TO_ON_PROTECT_TIME_DEFAULT;// On delay 1S
    
    Dev.Cfg.u32ResetPassword                = 0x12345678;    
}
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultData(void)
{
    uint8_t i;

    DevLoadDefaultSettings();

    EnOceanDelLearnTabAll();
    for ( i = 0; i < RELAY_OUT_NUMS; i++ )
    {
        IOProfile[i].u8Type = eIO_RELAY;
    }
    for ( i = RELAY_OUT_NUMS; i < LIGHT_CHANNEL_NUMS; i++ )
    {
        IOProfile[i].u8Type = eIO_DIMMING;
    }

    for ( i = 0; i < LIGHT_CHANNEL_NUMS; i++ )
    {
        IOProfileLoadDefault(i);
        IOStatusLoadDefault(i);
    }        
}
/**
   * @brief
   * @param
   * @retval
   */
void NVM_ChannelUpdate(uint8_t u8Channel)
{    
    if ( 0 == u8Channel ) //
    {
        Dev.u8CfgUpdate = 1;
    }
    /* Must use "<=", because the MSC telegram relay channel is from 1 to 3 */
    else if ( u8Channel <= LIGHT_CHANNEL_NUMS )
    {
        IOProfile[u8Channel-1].u8DataUpdate = 1;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultEnable(void)
{
    uint8_t i;

    EnOceanSaveLearnTabEvent();

    NVM_ChannelUpdate(DEV_CHANNEL);

    for ( i = 0; i < LIGHT_CHANNEL_NUMS; i++ )
    {
        NVM_ChannelUpdate(i + 1);
        
        IOState[i].u8DataUpdate = 1;
    }
    
    Dev.u8ExpandUpdate = 1;

    #ifdef CASCADE_MASTER    
        RS485_GetConfigParameter();
        RS485ModbusInit(&RS485Modbus);    
        ExpandPanelUpdateSettings();
        ExpandPanelGetEnOceanBaseIDStart();
    #else    
        DI_UpdateSettings();
    #endif
}

/**
  * @brief
  * @param
  * @retval None
  */
void NVM_GetLightPowerOn(void)
{
    uint8_t u8I;

    for ( u8I = 0; u8I < LIGHT_CHANNEL_NUMS; u8I ++ )
    {
        if ( eCHANNEL_POWER_ON_DEFAULT_OFF == IOProfile[u8I].u2DefaultState )
        {
            IORun[u8I].u8ExeValue = 0x00;
        }
        else if (eCHANNEL_POWER_ON_DEFAULT_ON == IOProfile[u8I].u2DefaultState)
        {
            IORun[u8I].u8ExeValue = IOState[u8I].u8LuminValue;
        }
        else if ( eCHANNEL_POWER_ON_DEFAULT_PREVIOUS == IOProfile[u8I].u2DefaultState )
        {
            IORun[u8I].u8ExeValue = IOState[u8I].u8ExeValue;
        }

        IORun[u8I].u8OutValue                 = IORun[u8I].u8ExeValue;

        if ( 0xFFFFFFFF == IOState[u8I].u32ChannelChangeCnt )
        {
            IOState[u8I].u32ChannelChangeCnt = 0;
        }
		
        IORun[u8I].u32RandSendPeriod = 10000 + u8I*200;

        if ( eIO_RELAY == IOProfile[u8I].u8Type )
        {
            if ( IORun[u8I].u8OutValue > 0 )
            {
                IORun[u8I].eOutCmd = eCMD_STATE_ON;
            }
            else
            {
                IORun[u8I].eOutCmd = eCMD_STATE_OFF;
            }            
        }
        else if ( eIO_DIMMING == IOProfile[u8I].u8Type )
        {
            IORun[u8I].eOutCmd = eCMD_DIMMING_SET_INIT;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_ReadHWLog(void)
{
    HWLogInfo_Typedef HWLog;

    M24CXX_WRInit(NVM_HARDWARE_INFO_ADDRESS, HWLog.u8Bytes,sizeof(HWLogInfo_Typedef)/sizeof(uint8_t));  
    /* load the dev run info */
    if ( OK == M24CXX_EEPROMReadNBytes() )
    {        
        Dev.Log.u32RunTime          = HWLog.u32RunTime;
        Dev.Log.u32PowerOnCount     = HWLog.u32PowerOnCount + 1;       
        Dev.Log.u32SoftFaultCount   = HWLog.u32SoftFaultCount;                
        return;
    }

    M24CXX_WRInit(NVM_HARDWARE_INFO_OFFSET_BASE, HWLog.u8Bytes,sizeof(HWLogInfo_Typedef)/sizeof(uint8_t));
    /* load the dev run info */
    if ( OK == M24CXX_EEPROMReadNBytes() )
    {        
        Dev.Log.u32RunTime          = HWLog.u32RunTime;
        Dev.Log.u32PowerOnCount     = HWLog.u32PowerOnCount + 1;       
        Dev.Log.u32SoftFaultCount   = HWLog.u32SoftFaultCount;                
        return;
    }

    Dev.Log.u32RunTime          = 0;
    Dev.Log.u32PowerOnCount     = 1;       
    Dev.Log.u32SoftFaultCount   = 0;  

    Dev.u8LogUpdate             = 1;
}
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_ReadHWCfg(void)
{
    HWCfg_Typedef     HWCfg;

#ifndef CASCADE_MASTER    
    uint8_t i;
#endif    
//    uint8_t j;

    M24CXX_WRInit(NVM_DEV_CFG_ADDRESS, HWCfg.u8Bytes,sizeof(HWCfg_Typedef)/sizeof(uint8_t));
    /* load the dev cfg info */
    if ( OK == M24CXX_EEPROMReadNBytes() ) 
    {                       
        if ( OK == NVM_ReadDevDataCheck(&HWCfg) )
        {
            Dev.Cfg.u32ResetPassword      = HWCfg.u32ResetPassword;                                               
            Dev.Cfg.u8LightProtectDelayOn = HWCfg.u8LightProtectDelayOn;            
                        
        #ifdef CASCADE_MASTER                        
            Dev.Cfg.u8RadioInterval       = HWCfg.u8RadioInterval;
            Dev.Cfg.u8Repeater            = HWCfg.u8Repeater;                
            Dev.Cfg.eParity               = HWCfg.eParity;
            Dev.Cfg.eStops                = HWCfg.eStops;           
            Dev.Cfg.eBaudRateID           = HWCfg.eBaudRateID;            
            Dev.Cfg.u32RemanCode          = HWCfg.u32RemanCode;
            Dev.Cfg.u32EnOceanChipID      = HWCfg.u32EnOceanChipID;
            Dev.Cfg.u32EnOceanBaseID      = HWCfg.u32EnOceanBaseID;                        
            Dev.Cfg.u8DALIChannelNums     = HWCfg.u8DALIChannelNums;            
            Dev.Cfg.u32DALIHOnlineMask    = HWCfg.u32DALIHOnlineMask;
            Dev.Cfg.u32DALILOnlineMask    = HWCfg.u32DALILOnlineMask;
        #else 
            Dev.Cfg.u8DIRelateMask = HWCfg.u8DIRelateMask;    
            for ( i = 0; i < SLAVE_DI_MAX; i++ )
            {
                Dev.Cfg.u8DISensorType[i] = HWCfg.u8DISensorType[i];
                Dev.Cfg.u8DIMode[i]       = HWCfg.u8DIMode[i];        
            }
            
        #endif   
            return; 
        }        
    }

    M24CXX_WRInit(NVM_DEV_CFG_OFFSET_BASE, HWCfg.u8Bytes,sizeof(HWCfg_Typedef)/sizeof(uint8_t));

    /* load the dev cfg info */
    if ( OK == M24CXX_EEPROMReadNBytes() ) 
    {                       
        if ( OK == NVM_ReadDevDataCheck(&HWCfg) )
        {
            Dev.Cfg.u32ResetPassword      = HWCfg.u32ResetPassword;                                               
            Dev.Cfg.u8LightProtectDelayOn = HWCfg.u8LightProtectDelayOn;            
                                    
        #ifdef CASCADE_MASTER                
            Dev.Cfg.u8RadioInterval       = HWCfg.u8RadioInterval;
            Dev.Cfg.u8Repeater            = HWCfg.u8Repeater;                    
            Dev.Cfg.eParity               = HWCfg.eParity;
            Dev.Cfg.eStops                = HWCfg.eStops;           
            Dev.Cfg.eBaudRateID           = HWCfg.eBaudRateID;            
            Dev.Cfg.u32RemanCode          = HWCfg.u32RemanCode;
            Dev.Cfg.u32EnOceanChipID      = HWCfg.u32EnOceanChipID;
            Dev.Cfg.u32EnOceanBaseID      = HWCfg.u32EnOceanBaseID;            
            Dev.Cfg.u8DALIChannelNums     = HWCfg.u8DALIChannelNums;            
            Dev.Cfg.u32DALIHOnlineMask    = HWCfg.u32DALIHOnlineMask;
            Dev.Cfg.u32DALILOnlineMask    = HWCfg.u32DALILOnlineMask;
        #else 
            Dev.Cfg.u8DIRelateMask = HWCfg.u8DIRelateMask;    
            for ( i = 0; i < SLAVE_DI_MAX; i++ )
            {
                Dev.Cfg.u8DISensorType[i] = HWCfg.u8DISensorType[i];
                Dev.Cfg.u8DIMode[i]       = HWCfg.u8DIMode[i];        
            }    
        #endif    
            return; 
        }
    }

    Dev.u8CfgUpdate = 1;
}
#ifdef CASCADE_MASTER
    /**
     * @brief
     * @param
     * @retval None
     */
    void NVM_ReadExpandDevCfg(void)
    {
        uint8_t i;    
        uint8_t j;

        M24CXX_WRInit(NVM_DEV_EXPAND_CFG_ADDRESS, MasterExpandDevCfg.u8Bytes,sizeof(MasterExpandDevCfg_typedef)/sizeof(uint8_t));
        /* load the dev cfg info */
        if ( OK == M24CXX_EEPROMReadNBytes() ) 
        {       
            if ( MasterExpandDevCfg.u8ExpandPanelNums > 16 )
            {
                MasterExpandDevCfg.u8ExpandPanelNums = 16;
            }
            if ( MasterExpandDevCfg.u8TriacChannelNums > 8 )
            {
                MasterExpandDevCfg.u8TriacChannelNums = 8;
            }
            for ( i = 0; i < EXPAND_PANEL_NUMS_MAX; i++ )
            {
                
                if ( MasterExpandDevCfg.u8ButtonNums[i] > 6 )
                {
                    MasterExpandDevCfg.u8ButtonNums[i] = 4;
                }
                ExpandPanel[i].u8ButtonNums = MasterExpandDevCfg.u8ButtonNums[i];
                ExpandPanel[i].u8RelateMask = MasterExpandDevCfg.u8RelateMask[i];

                for (j = 0; j < EXPAND_PANEL_BUTTON_MAX_NUMS; j++)
                {                
                    //MasterExpandDevCfg.u8SensorType[i][j]
                    ExpandPanel[i].DI[j].u8SensorType = MasterExpandDevCfg.u8SensorType[i][j];

                    if ( MasterExpandDevCfg.u8Mode[i][j] > eBUTTON_MODE_PTM21X_90 )
                    {
                        MasterExpandDevCfg.u8Mode[i][j] = eBUTTON_MODE_TOGGLE_ONOFF;
                    }
                    ExpandPanel[i].DI[j].u8Mode       = MasterExpandDevCfg.u8Mode[i][j];
                }        
            }
            return;     
        }

        M24CXX_WRInit(NVM_DEV_EXPAND_CFG_OFFSET_BASE, MasterExpandDevCfg.u8Bytes,sizeof(MasterExpandDevCfg_typedef)/sizeof(uint8_t));

        /* load the dev cfg info */
        if ( OK == M24CXX_EEPROMReadNBytes() ) 
        {    
            if ( MasterExpandDevCfg.u8ExpandPanelNums > 16 )
            {
                MasterExpandDevCfg.u8ExpandPanelNums = 16;
            }
            if ( MasterExpandDevCfg.u8TriacChannelNums > 8 )
            {
                MasterExpandDevCfg.u8TriacChannelNums = 8;
            }
            for ( i = 0; i < EXPAND_PANEL_NUMS_MAX; i++ )
            {
                
                if ( MasterExpandDevCfg.u8ButtonNums[i] > 6 )
                {
                    MasterExpandDevCfg.u8ButtonNums[i] = 4;
                }
                ExpandPanel[i].u8ButtonNums = MasterExpandDevCfg.u8ButtonNums[i];
                ExpandPanel[i].u8RelateMask = MasterExpandDevCfg.u8RelateMask[i];

                for (j = 0; j < EXPAND_PANEL_BUTTON_MAX_NUMS; j++)
                {                
                    //MasterExpandDevCfg.u8SensorType[i][j]
                    ExpandPanel[i].DI[j].u8SensorType = MasterExpandDevCfg.u8SensorType[i][j];

                    if ( MasterExpandDevCfg.u8Mode[i][j] > eBUTTON_MODE_PTM21X_90 )
                    {
                        MasterExpandDevCfg.u8Mode[i][j] = eBUTTON_MODE_TOGGLE_ONOFF;
                    }
                    ExpandPanel[i].DI[j].u8Mode       = MasterExpandDevCfg.u8Mode[i][j];
                }        
            }                
            return;
        }

        Dev.u8ExpandUpdate = 1;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t NVM_ExpandDevWriteSetting(void)
    {
        if ( 1 == Dev.u8ExpandUpdate )
        {
            Dev.u8ExpandUpdate    = 2;
            M24CXX_WRInit(NVM_DEV_EXPAND_CFG_ADDRESS, MasterExpandDevCfg.u8Bytes,sizeof(MasterExpandDevCfg_typedef)/sizeof(uint8_t));
        }
        else if ( 2 == Dev.u8ExpandUpdate )
        {
            Dev.u8ExpandUpdate    = 0;
            M24CXX_WRInit(NVM_DEV_EXPAND_CFG_OFFSET_BASE, MasterExpandDevCfg.u8Bytes,sizeof(MasterExpandDevCfg_typedef)/sizeof(uint8_t));        
        }
        else
        {
            return OK;
        }  
        return !OK;
    }
#endif
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_ReadLightProfile(uint8_t u8Channel)
{
    M24CXX_WRInit(NVM_IO_PROFILE_BASE + u8Channel*NVM_IO_PROFILE_SIZE, IOProfile[u8Channel].u8Bytes,sizeof(IOProfile_Typedef)/sizeof(uint8_t));
    if ( OK == M24CXX_EEPROMReadNBytes() )
    {        
        if ( OK == NVM_ReadIOProfileDataCheck(&IOProfile[u8Channel]) )
        {
            return;
        }
        
    }
    M24CXX_WRInit(NVM_IO_PROFILE_OFFSET_BASE + u8Channel*NVM_IO_PROFILE_SIZE, IOProfile[u8Channel].u8Bytes,sizeof(IOProfile_Typedef)/sizeof(uint8_t));
    if ( OK == M24CXX_EEPROMReadNBytes() )
    {        
        if ( OK == NVM_ReadIOProfileDataCheck(&IOProfile[u8Channel]) )
        {
            return;
        }
        
    }
    
    IOProfile[u8Channel].u8DataUpdate = 1;   
}
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_ReadLightState(uint8_t u8Channel)
{
    M24CXX_WRInit(NVM_IO_STATUS_BASE + u8Channel*NVM_IO_STATUS_SIZE, IOState[u8Channel].u8Bytes,sizeof(IOSaveNVM_Typedef)/sizeof(uint8_t));
    /* load the light state from NVM */
    if ( OK == M24CXX_EEPROMReadNBytes() )
    {
        if ( OK == NVM_ReadIOStateDataCheck(IOState[u8Channel].u8ExeValue) )
        {
            return;
        }
        
    }
    M24CXX_WRInit(NVM_IO_STATUS_OFFSET_BASE + u8Channel*NVM_IO_STATUS_SIZE, IOState[u8Channel].u8Bytes,sizeof(IOSaveNVM_Typedef)/sizeof(uint8_t));
    /* load the light state from NVM */
    if ( OK == M24CXX_EEPROMReadNBytes() )
    {
        if ( OK == NVM_ReadIOStateDataCheck(IOState[u8Channel].u8ExeValue) )
        {
            return;
        }
        
    }
    
    IOState[u8Channel].u8DataUpdate = 1;
}
#ifdef CASCADE_MASTER 
    /**
     * @brief
     * @param
     * @retval None
     */
    void NVM_LoadSettings(void)
    {
        uint8_t i;
            
        NVM_ReadHWLog();
        SystemWait(10);
        NVM_ReadHWCfg();
        SystemWait(10);
    
        NVM_ReadExpandDevCfg();
        SystemWait(10);

        /* Get the learn infomation ,than copy to the learn tab */
        M24CXX_WRInit(NVM_LRN_TAB_ADDRESS, LearnInfoTab.u8Bytes,ID_ENTRY_BYTES);  
        M24CXX_EEPROMReadNBytes();
        SystemWait(10);
        /* load light info */
        for (i = 0; i < LIGHT_CHANNEL_NUMS; i++)
        {
            NVM_ReadLightProfile(i);
            SystemWait(10);
            NVM_ReadLightState(i);
            SystemWait(10);
        }
        
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    void NVM_WriteSettings(void)
    {
        
        if ( M24CXX_EEPROMWriteNBytes() )
        {
            return;
        }

        if ( 1 == Dev.u8SaveCount )
        {
            if ( OK == NVM_DevWriteSetting() )
            {
                Dev.u8SaveCount = 2;
            }
        }
        else if ( 2 == Dev.u8SaveCount )
        {
            if ( OK == NVM_LearnInfoTabWriteSetting() )
            {
                Dev.u8SaveCount = 3;
            }
        }
        else if ( 3 == Dev.u8SaveCount )
        {
            if ( OK == NVM_DevRunInfo() )
            {
                Dev.u8SaveCount = 4;
            }
        }
        else if ( 4 == Dev.u8SaveCount )
        {
            if ( OK == NVM_IOProfileWriteSetting() )
            {
                Dev.u8SaveCount = 5;
            }
        }
        else if ( 5 == Dev.u8SaveCount )
        {
            if ( OK == NVM_IOStateWriteSetting() )
            {
                Dev.u8SaveCount = 6;
            }
        }
        else if ( 6 == Dev.u8SaveCount)
        {
            if ( OK == NVM_ExpandDevWriteSetting() )
            {
                Dev.u8SaveCount = 1;
            }
        }
        else
        {
            Dev.u8SaveCount = 1;
        }
    }
#else
    /**
     * @brief
     * @param
     * @retval None
     */
    void NVM_LoadSettings(void)
    {
        uint8_t i;
            
        NVM_ReadHWLog();
        SystemWait(10);
        NVM_ReadHWCfg();
        SystemWait(10);
            
        /* Get the learn infomation ,than copy to the learn tab */
        M24CXX_WRInit(NVM_LRN_TAB_ADDRESS, LearnInfoTab.u8Bytes,ID_ENTRY_BYTES);  
        M24CXX_EEPROMReadNBytes();
        SystemWait(10);
        /* load light info */
        for (i = 0; i < LIGHT_CHANNEL_NUMS; i++)
        {
            NVM_ReadLightProfile(i);
            SystemWait(10);
            NVM_ReadLightState(i);
            SystemWait(10);
        }
        
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    void NVM_WriteSettings(void)
    {
        
        if ( M24CXX_EEPROMWriteNBytes() )
        {
            return;
        }

        if ( 1 == Dev.u8SaveCount )
        {
            if ( OK == NVM_DevWriteSetting() )
            {
                Dev.u8SaveCount = 2;
            }
        }
        else if ( 2 == Dev.u8SaveCount )
        {
            if ( OK == NVM_LearnInfoTabWriteSetting() )
            {
                Dev.u8SaveCount = 3;
            }
        }
        else if ( 3 == Dev.u8SaveCount )
        {
            if ( OK == NVM_DevRunInfo() )
            {
                Dev.u8SaveCount = 4;
            }
        }
        else if ( 4 == Dev.u8SaveCount )
        {
            if ( OK == NVM_IOProfileWriteSetting() )
            {
                Dev.u8SaveCount = 5;
            }
        }
        else if ( 5 == Dev.u8SaveCount )
        {
            if ( OK == NVM_IOStateWriteSetting() )
            {
                Dev.u8SaveCount = 1;
            }
        }    
        else
        {
            Dev.u8SaveCount = 1;
        }
    }
#endif
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_LearnInfoTabWriteSetting(void)
{    
    if ( EnOceanGetLearnEvent()  )
    {
        EnOceanClearLearnSaveEvent();
        M24CXX_WRInit(NVM_LRN_TAB_ADDRESS, LearnInfoTab.u8Bytes,ID_ENTRY_BYTES);        
    }

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_DevWriteSetting(void)
{
    if ( 1 == Dev.u8CfgUpdate )
    {
        Dev.u8CfgUpdate    = 2;
        M24CXX_WRInit(NVM_DEV_CFG_ADDRESS, Dev.Cfg.u8Bytes,sizeof(HWCfg_Typedef)/sizeof(uint8_t));
    }
    else if ( 2 == Dev.u8CfgUpdate )
    {
        Dev.u8CfgUpdate    = 0;
        M24CXX_WRInit(NVM_DEV_CFG_OFFSET_BASE, Dev.Cfg.u8Bytes,sizeof(HWCfg_Typedef)/sizeof(uint8_t));        
    }
    else
    {
        return OK;
    }  
    return !OK;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_IOProfileWriteSetting(void)
{
    static uint8_t u8ProfileCnt;

           
    if ( 1 == IOProfile[u8ProfileCnt].u8DataUpdate )
    {
        IOProfile[u8ProfileCnt].u8DataUpdate    = 2;
        M24CXX_WRInit(NVM_IO_PROFILE_BASE + u8ProfileCnt*NVM_IO_PROFILE_SIZE, IOProfile[u8ProfileCnt].u8Bytes,sizeof(IOProfile_Typedef)/sizeof(uint8_t));
    }
    else if ( 2 == IOProfile[u8ProfileCnt].u8DataUpdate )
    {
        IOProfile[u8ProfileCnt].u8DataUpdate    = 0;
        M24CXX_WRInit(NVM_IO_PROFILE_OFFSET_BASE + u8ProfileCnt*NVM_IO_PROFILE_SIZE, IOProfile[u8ProfileCnt].u8Bytes,sizeof(IOProfile_Typedef)/sizeof(uint8_t));
    }
    else
    {
        u8ProfileCnt++;
        if ( u8ProfileCnt >= LIGHT_CHANNEL_NUMS )
        {
            u8ProfileCnt = 0;
        }
        return OK;
    }
    
    return !OK;
    
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_IOStateWriteSetting(void)
{
    static uint8_t u8StateCnt;

    if ( 1 == IOState[u8StateCnt].u8DataUpdate )
    {
        IOState[u8StateCnt].u8DataUpdate    = 2;            
        M24CXX_WRInit(NVM_IO_STATUS_BASE + u8StateCnt*NVM_IO_STATUS_SIZE, IOState[u8StateCnt].u8Bytes,sizeof(IOSaveNVM_Typedef)/sizeof(uint8_t));
    }
    else if ( 2 == IOState[u8StateCnt].u8DataUpdate )
    {
        IOState[u8StateCnt].u8DataUpdate    = 0;    
        M24CXX_WRInit(NVM_IO_STATUS_OFFSET_BASE + u8StateCnt*NVM_IO_STATUS_SIZE, IOState[u8StateCnt].u8Bytes,sizeof(IOSaveNVM_Typedef)/sizeof(uint8_t));                
    }
    else
    {
        u8StateCnt++;
        if ( u8StateCnt >= LIGHT_CHANNEL_NUMS )
        {
            u8StateCnt = 0;
        }
        return OK;
    }

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_DevRunInfo(void)
{
    if ( 1 == Dev.u8LogUpdate  )
    {
        Dev.u8LogUpdate    = 2;
        M24CXX_WRInit(NVM_HARDWARE_INFO_ADDRESS, Dev.Log.u8Bytes,sizeof(HWLogInfo_Typedef)/sizeof(uint8_t));        
    }
    else if ( 2 == Dev.u8LogUpdate  )
    {
        Dev.u8LogUpdate = 0;
        M24CXX_WRInit(NVM_HARDWARE_INFO_OFFSET_BASE, Dev.Log.u8Bytes,sizeof(HWLogInfo_Typedef)/sizeof(uint8_t));        
    }
    else
    {
        Dev.u8LogUpdate = 0;
        return OK;
    }

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_ReadDevDataCheck(HWCfg_Typedef *pHWInfo)
{
    /* Use for just HAVC output for fan coil */                     
    /* If only use the parameters for setting VRV system or control panel can be close the hvac output */        
    //pHWInfo->u32ResetPassword
    if ( pHWInfo->u8LightProtectDelayOn > 10 )
    {
        pHWInfo->u8LightProtectDelayOn = 5;
    }
                                    
    #ifdef CASCADE_MASTER    
        
        if ( pHWInfo->u8RadioInterval < 100 )
        {
            pHWInfo->u8RadioInterval = 100;
        }
        if ( pHWInfo->u8Repeater > 2 )
        {
            pHWInfo->u8Repeater = 2;
        }
        
        if ( pHWInfo->eParity > ePARITY_ODD )
        {
            pHWInfo->eParity = ePARITY_NONE;
            return !OK;
        }

        if ( pHWInfo->eStops > eSTOP_2 )
        {       
            pHWInfo->eStops = eSTOP_1;
            return !OK;
        }

        if ( pHWInfo->eBaudRateID > eBAUD_115200_ID )
        {    
            pHWInfo->eBaudRateID = eBAUD_9600_ID;   
            return !OK;
        }          
                
        if ( pHWInfo->u8DALIChannelNums > 16 )
        {
            pHWInfo->u8DALIChannelNums = 16;
        }
        //Dev.Cfg.u32DALIHOnlineMask
        //Dev.Cfg.u32DALILOnlineMask
    #else 
        /*
        Dev.Cfg.u8DIRelateMask = HWCfg.u8DIRelateMask;    
        for ( i = 0; i < SLAVE_DI_MAX; i++ )
        {
            Dev.Cfg.u8DISensorType[i] = HWCfg.u8DISensorType[i];
            Dev.Cfg.u8DIMode[i]       = HWCfg.u8DIMode[i];        
        }
        */   
    #endif
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_ReadIOProfileDataCheck(IOProfile_Typedef *pIOProfile)
{
    if ( pIOProfile->u8Type > eIO_DIMMING)
    {
        return !OK;
    }
    if ( pIOProfile->u1TaughtInDevs > 1)
    {
        return !OK;
    }

    /* 调光时间1 */
    //pIOProfile->Dimmer.u8DimmerTim1;
    /* 调光时间2 */
    //pIOProfile->Dimmer.u8DimmerTim2;
    /* 调光时间3 */
    //pIOProfile->Dimmer.u8DimmerTim3;

    //pIOProfile->Dimmer.u8Time;
    //uint8_t u8RockTime;
    /* 线性值 */
    /* 调光起始值 */
    
    //pIOProfile->Dimmer.u7LimitMin;
    //pIOProfile->Dimmer.u1LimitMinSetFlag;
    /* 调光上次输出起始值 */    
    /* 调光最大值 */    
    if ( pIOProfile->Dimmer.u7LimitMax > 100 )
    {
        pIOProfile->Dimmer.u7LimitMax = 100;
    }
    //pIOProfile->Dimmer.u1LimitMaxSetFlag;
    // 0: triac ; 1: dali lux ; 2: dali color T ; 3: dali rgb ; 4:Dali rgbw
    if ( pIOProfile->Dimmer.eType > eDIMMING_DALI_DT8_RGBWF )
    {
        pIOProfile->Dimmer.eType = eDIMMING_DALI_LUX_AND_COLOR;
    }

    if ( ( 0 == pIOProfile->Dimmer.u8ArcLevelStep )||(pIOProfile->Dimmer.u8ArcLevelStep >= 100) )
    {
        pIOProfile->Dimmer.u8ArcLevelStep = 10;
    }
    
     
    if ( ( pIOProfile->Dimmer.u16LongChangeTime == 0 )||( pIOProfile->Dimmer.u16LongChangeTime > 5000 ) )
    {
        pIOProfile->Dimmer.u16LongChangeTime = 20;
    }
    if ( ( pIOProfile->Dimmer.u16ColorTemperatureLongChangeTime == 0 )||( pIOProfile->Dimmer.u16ColorTemperatureLongChangeTime > 5000 ) )
    {
        pIOProfile->Dimmer.u16ColorTemperatureLongChangeTime = 30;
    }    

    if ( pIOProfile->Dimmer.u16ColorTemperatureMax > 6500 )
    {
        pIOProfile->Dimmer.u16ColorTemperatureMax = 6500 ;
    }
    if ( pIOProfile->Dimmer.u16ColorTemperatureMin < 2700 )
    {
        pIOProfile->Dimmer.u16ColorTemperatureMin = 2700;
    }
    if ( pIOProfile->Dimmer.u16ColorTemperatureStep < 100 )
    {
        pIOProfile->Dimmer.u16ColorTemperatureStep = 100;
    }
    
    if ( pIOProfile->Dimmer.u8FadeTime > 15 )
    {
        pIOProfile->Dimmer.u8FadeTime = 2;
    }
    if ( pIOProfile->Dimmer.u8FadeRate > 15 )
    {
        pIOProfile->Dimmer.u8FadeRate = 7;
    }

    if ( pIOProfile->Dimmer.u8FadeValue > 200 )
    {
        pIOProfile->Dimmer.u8FadeValue = 10;
    }


    if ( pIOProfile->Dimmer.u8RGB_R_Group > 15 )
    {
        pIOProfile->Dimmer.u8RGB_R_Group = 0;
    }
    if ( pIOProfile->Dimmer.u8RGB_G_Group > 15 )
    {
        pIOProfile->Dimmer.u8RGB_G_Group = 0;
    }
    if ( pIOProfile->Dimmer.u8RGB_B_Group > 15 )
    {
        pIOProfile->Dimmer.u8RGB_B_Group = 0;
    }
    if ( pIOProfile->Dimmer.u8RGB_W_Group > 15 )
    {
        pIOProfile->Dimmer.u8RGB_W_Group = 0;
    }

    if ( pIOProfile->Dimmer.u8FailureLevel == 255 )
    {
        pIOProfile->Dimmer.u8FailureLevel = 0;  
    }
    if ( pIOProfile->Dimmer.u8PowerOnLevel == 255 )
    {
        pIOProfile->Dimmer.u8PowerOnLevel = 0;
    }

    if ( pIOProfile->Dimmer.u8PowerMaxLevel < pIOProfile->Dimmer.u8PowerMinLevel )
    {
        pIOProfile->Dimmer.u8PowerMaxLevel = 254;
        pIOProfile->Dimmer.u8PowerMinLevel = 1;
    }

    if ( 0xFF == pIOProfile->Dimmer.u8PowerMaxLevel )
    {
        pIOProfile->Dimmer.u8PowerMaxLevel = 254;
    }
    if ( 0xFF == pIOProfile->Dimmer.u8PowerMinLevel )
    {
        pIOProfile->Dimmer.u8PowerMinLevel = 1;
    }
    
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_ReadIOStateDataCheck(uint8_t u8ChannelValue)
{
    if ( u8ChannelValue > 0x64 )
    {
        return !OK;
    }
    return OK;
}

/* End of file */
