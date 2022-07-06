
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
#include "Dataconfigure.h"
#include "Led.h"

#include "main.h"
#include "EnOceanCascade.h"

/*************************************************************************************/

/***********************************************************************************/

const RegTab_Typedef DevRegTab[] =
    {
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_SOFT_YEAR_MONTH,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_SOFT_DAY_VERSION,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_SYSTEM_VOLT,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_ENOCEAN_RSSI,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_WIFI_RSSI,
            0,
            0xFFFF,
        },

        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_DEVICE_RUNNING_HIGH_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_DEVICE_RUNNING_LOW_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CH2O_RUNNING_HIGH_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CH2O_RUNNING_LOW_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CO2_RUNNING_HIGH_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CO2_RUNNING_LOW_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_PMSA03_RUNNING_HIGH_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_PMSA03_RUNNING_LOW_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_DEVICE_RUNNING_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CH2O_RUNNING_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CO2_RUNNING_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_PMSA03_RUNNING_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_SENSOR_RUNNING_TIME,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_COMMUNICATION_FAULT,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_DEVICE_FAULT,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_SENSOR_STATUS,
            0,
            0xFFFF,
        },

        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_TEMPERATURE_VALUE,
            0,
            125,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_HUMIDITY_VALUE,
            0,
            100,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CO2_VALUE,
            400,
            5000,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_PM1_VALUE,
            0,
            999,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_PM25_VALUE,
            0,
            999,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_PM10_VALUE,
            0,
            999,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_CH2O_VALUE,
            0,
            1500,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_SENSOR_VALUE,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R,
            REG_VALUE_RANGE_DISABLE,
            MB_INPUT_AIR_QUALITY,
            0,
            0xFFFF,
        },

        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_SET_ADDR,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_SET_BAUD,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_TIME_RESET_HIGH_PASSWORD,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_TIME_RESET_LOW_PASSWORD,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_DEVICE_RESET_TIMES,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CO2_RESET_TIMES,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CH2O_RESET_TIMES,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_PMSA03_RESET_TIMES,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CH2O_FACTORY_YEAR_MONTH,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CH2O_FACTORY_DAY,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CH2O_INSTALL_YEAR_MONTH,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CH2O_INSTALL_DAY,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_485MB_ADD,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_485MB_BAUD,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_485MB_STOPS,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_485MB_PARITY,
            0,
            0xFFFF,
        },                        
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_TEMPERATURE_CALIB,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_HUMIDITY_CALIB,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CO2_CALIB,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_PM1_CALIB,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_PM25_CALIB,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_PM10_CALIB,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_CH2O_CALIB,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_LED_SWITCH,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_ENOCEAN_REAPTER,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_AIRBOX_RESET_FACTORY_SETTINGS,
            0,
            0x1,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            VOID_RWPARAM_RESET_FACTORY_SETTINGS,
            0,
            0xFFFF,
        },

        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_SENSOR_REFRESH,
            0,
            0xFFFF,
        },

        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_NEW_WIND_SYS_MODE,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_NEW_WIND_SYS_SWITCH,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_NEW_WIND_SYS_SWITCH_STATUS,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_NEW_WIND_SYS_WIND_SPEED,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_NEW_WIND_SYS_STATUS,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_NEW_WIND_SYS_FILTER_ELEMENT,
            0,
            0xFFFF,
        },
        {
            REG_PERMISSION_R | REG_PERMISSION_W,
            REG_VALUE_RANGE_ENABLE,
            MB_HOLD_NEW_WIND_SYS_FAULT,
            0,
            0xFFFF,
        },

        /*
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_LOCK_ENABLE                ,    0,     1,                          },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_ENABLE , MB_HOLD_RESET_DEFAULT_CMD          ,    0,     0xFF,                       },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_DISABLE, MB_HOLD_RESET_DEFAULT_PASSWORD     ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_DISABLE, MB_HOLD_RESET_DEFAULT_PASSWORD_L   ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_CHIPID                    ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_CHIPID_L                  ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_BASEID                    ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_BASEID_L                  ,    0,     0xFFFF,                     },

    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_ADDRESS            ,    1,     31,                         },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_BAUD               ,    0,     7,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_STOPS              ,    0,     1,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_PARITY             ,    0,     2,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_ENOCEAN_REAPER             ,    0,     2,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_REMANCODE          ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_REMANCODE_L        ,    0,     0xFFFF,                     },
                                                                                                                                 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_SEND_PERIOD        ,  100,     0xFF,                       },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_TAUGHTINDEV        ,    0,     1,                          },
*/

};

#if 0
#pragma pack(1)
/* Clover Dev Setting */
const RegTab_Typedef DevRegTab[]=
{
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_HW_VERSION                ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FW_VERSION                ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FW_DATE                   ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FW_TIME                   ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_ERROR                     ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_RUN_TIME                  ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_ENOCEAN_RSSI              ,    0,     0xFF,                       },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_POWER_ON_CNT              ,    0,     0xFFFF,                     },    
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_FAULT_CNT                 ,    0,     0xFFFF,                     },

    
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_LOCK_ENABLE                ,    0,     1,                          },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_ENABLE , MB_HOLD_RESET_DEFAULT_CMD          ,    0,     0xFF,                       },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_DISABLE, MB_HOLD_RESET_DEFAULT_PASSWORD     ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_N,REG_VALUE_RANGE_DISABLE, MB_HOLD_RESET_DEFAULT_PASSWORD_L   ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_CHIPID                    ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_CHIPID_L                  ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_BASEID                    ,    0,     0xFFFF,                     },
    {                 REG_PERMISSION_R,REG_VALUE_RANGE_DISABLE, MB_INPUT_BASEID_L                  ,    0,     0xFFFF,                     },

    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_ADDRESS            ,    1,     31,                         },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_BAUD               ,    0,     7,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_STOPS              ,    0,     1,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_RS485MB_PARITY             ,    0,     2,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_ENABLE , MB_HOLD_ENOCEAN_REAPER             ,    0,     2,                          },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_REMANCODE          ,    0,     0xFFFF,                     },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_REMANCODE_L        ,    0,     0xFFFF,                     },
                                                                                                                                 
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_SEND_PERIOD        ,  100,     0xFF,                       },
    {REG_PERMISSION_R|REG_PERMISSION_W,REG_VALUE_RANGE_DISABLE, MB_HOLD_ENOCEAN_TAUGHTINDEV        ,    0,     1,                          },

#ifdef HW_DEBUG

#endif

};

#endif
/*
uint32_t CFG_ADD[9]      = {0x0801F800,0x0801F850,0x0801F8A0,0x0801F8F0,0x0801F940,0x0801F990,0x0801F9E0,0x0801FA30};
uint32_t CFG_COPY_ADD[9] = {0x0801FA80,0x0801FAD0,0x0801FB20,0x0801FB70,0x0801FBC0,0x0801FC10,0x0801FC60,0x0801FCB0};

uint32_t LOG_ADD[20]     = {
                            0x0801F000,0x0801F020,0x0801F040,0x0801F060,0x0801F080,0x0801F0A0,0x0801F0C0,0x0801F0E0,0x0801F100,0x0801F120,
                            0x0801F140,0x0801F160,0x0801F180,0x0801F000,0x0801F1A0,0x0801F1C0,0x0801F1E0,0x0801F200,0x0801F220,0x0801F240   
                           }; 
uint32_t LOG_COPY_ADD[20]= {
                            0x0801F260,0x0801F280,0x0801F2A0,0x0801F2C0,0x0801F2E0,0x0801F300,0x0801F320,0x0801F340,0x0801F360,0x0801F380,
                            0x0801F3A0,0x0801F3C0,0x0801F3E0,0x0801F400,0x0801F420,0x0801F440,0x0801F460,0x0801F480,0x0801F4A0,0x0801F4C0
                           };              
*/


eFLASH_RunTypedef FLASHRUN;
Dev_Typedef Dev;

/***********************************************************************************/

//#pragma pack()

uint8_t Dev_GetRegTabSize(void)
{
    return sizeof(DevRegTab) / sizeof(DevRegTab[0]);
}

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
#if 0
/**
  * @brief
  * @param
  * @retval None
  */
static uint8_t NVM_ReadLearnInfoDataCheck(void);
#endif
/**
  * @brief
  * @param
  * @retval None
  */


/*============================ IMPLEMENTATION ================================*/

/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_DevRunSave(void)
{
    //TimerFlag._u8Second180++;
    TimerFlag.u32Timer_1s++;

    if(FLASHRUN.u32FlashWriteTime != 0)
    {
        FLASHRUN.u32FlashWriteTime--;
    }

    if (TimerFlag.u32Timer_1s > 3600)
    {
        TimerFlag.u32Timer_1s = 0;
        Dev.Log.u32RunTime++; //运行时间1小时+1

        FLASHRUN.u8LogUpdateFlag = 1;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettings(void)
{

  
    Dev.Cfg.u32RemanCode = RM_DEFAULT_REMAN_CODE;

    Dev.Cfg.u8ModbusPhyAdd = 16;
    Dev.Cfg.eBaudRateID = eBAUD_9600_ID;
    Dev.Cfg.eStops = eSTOP_1;
    Dev.Cfg.eParity = ePARITY_NONE;

    Dev.Cfg.u8RadioInterval = 100; //RADIO_SEND_MIN_INTERVAl_DEFAULT;
    Dev.Cfg.u8Repeater = 0;

    Dev.Cfg.u32ResetPassword = 0x12345678;

    Dev.Cfg.u16Calibration      = 0x00;      
    Dev.Cfg.u16CalibrationCH2O  = 0x00;  
    Dev.Cfg.u16CalibrationCO2   = 0x00;   
    Dev.Cfg.u16CalibrationH     = 0x00;     
    Dev.Cfg.u16CalibrationT     = 0x00;     
    Dev.Cfg.u16CalibrationPM10  = 0x00;  
    Dev.Cfg.u16CalibrationPM25  = 0x00;  
    Dev.Cfg.u16CalibrationPM100 = 0x00; 

    Dev.Log.u32RunTime = 0;
    Dev.Log.u32PowerOnCount = 0;
    Dev.Log.u32SoftFaultCount = 0;

}
/**
  * @brief
  * @param
  * @retval None
  */
void PowerOnInitializationSensor(void)
{
    CH2O_CO2.eRunState = eCH2O_CO2_IDLE;
    CH2O_CO2.eCO2FaultCode = eCO2_NORMAL;
    CH2O_CO2.eCH2OFaultCode = eCH2O_NORMAL;

    PMSA.eRunState = ePMSA_IDLE;
    PMSA.eFaultCode = ePMSA_NORMAL;

    SHT20.eRunState = eSHT20_IDLE;
    SHT20.eFaultCode = eSHT20_NORMAL;

    LED.eLedID = eLED_INITIAL;
    LED.eRunMode = eLEDRUN_STANDBY;
    LED.eWorkMode = eLEDWORK_STANDBY;

}
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettingsByReset(void)  //出厂设置
{


    Dev.Cfg.u32RemanCode = RM_DEFAULT_REMAN_CODE;

    //Dev.Cfg.u8ModbusPhyAdd = 16;
    SwitchReadPinStatus(&Dev.Cfg.u8ModbusPhyAdd);
    Dev.Cfg.eBaudRateID = eBAUD_9600_ID;
    Dev.Cfg.eStops = eSTOP_1;
    Dev.Cfg.eParity = ePARITY_NONE;

    Dev.Cfg.u8RadioInterval = 100; //RADIO_SEND_MIN_INTERVAl_DEFAULT;
    Dev.Cfg.u8Repeater = 0;
    Dev.Cfg.u8LedSwtichFalg = 0;
    Dev.Cfg.u32ResetPassword = 0x12345678;

    Dev.Cfg.u16Calibration      = 0x00;      
    Dev.Cfg.u16CalibrationCH2O  = 0x00;  
    Dev.Cfg.u16CalibrationCO2   = 0x00;   
    Dev.Cfg.u16CalibrationH     = 0x00;     
    Dev.Cfg.u16CalibrationT     = 0x00;     
    Dev.Cfg.u16CalibrationPM10  = 0x00;  
    Dev.Cfg.u16CalibrationPM25  = 0x00;  
    Dev.Cfg.u16CalibrationPM100 = 0x00; 

    Dev.Log.u32RunTime = 0;
    Dev.Log.u32PowerOnCount = 0;
    Dev.Log.u32SoftFaultCount = 0;
}

/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultData(void)
{
    PowerOnInitializationSensor();

    //DevLoadDefaultSettings();

    EnOceanDelLearnTabAll();
}
/**
   * @brief
   * @param
   * @retval
   */
void FLASH_ChannelUpdate(uint8_t u8Channel)  //信道更新
{
    if (0 == u8Channel) //
    {
        Dev.u8CfgUpdate = 1;
    }
    /* Must use "<=", because the MSC telegram relay channel is from 1 to 3 */
}

/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultEnable(void)  //重置默认值
{
    EnOceanSaveLearnTabEvent();

    FLASH_ChannelUpdate(DEV_CHANNEL);
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_FactorySettings(void) //FLASHRUN 写入出厂设置参数
{
    uint8_t i;
    uint8_t u8BlockFlag;

    u8BlockFlag = 4;
    
    //Dev.Log.u32PowerOnCount++;

    DevLoadDefaultSettingsByReset();

    while (u8BlockFlag)
    {
        u8BlockFlag--;
        //Dev.Cfg.u8BlockCnt = u8BlockFlag;
        FLASH_Read_32Bit((FLASH_CFG_ADD + (u8BlockFlag * 0x200)), FLASH_CFG_READ_BUFF, sizeof(FLASH_CFG_READ_BUFF)/sizeof(uint32_t));

        if (0xFFFFFFFF != FLASH_CFG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_CfgDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(HWCfg_Typedef)/sizeof(uint32_t); i++)
                {
                    Dev.Cfg.u32Words[i] = FLASH_CFG_READ_BUFF[i + 1];  
                }
                Dev.Cfg.u16FlashReadSuccessCount++;
                return;
            }
            else
            {
                Dev.Cfg.u16FlashReadFailCount++;
            }
        }

        FLASH_Read_32Bit((FLASH_CFG_ADD + (u8BlockFlag * 0x200 + 0x100)), FLASH_CFG_READ_BUFF, sizeof(FLASH_CFG_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_CFG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_CfgDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(HWCfg_Typedef)/sizeof(uint32_t); i++)
                {
                    Dev.Cfg.u32Words[i] = FLASH_CFG_READ_BUFF[i + 1];
                }
                Dev.Cfg.u16FlashReadSuccessCount++;
                return;
            }
            else
            {
                Dev.Cfg.u16FlashReadFailCount++;
            }
        }

    }

    if (0 == u8BlockFlag)
    {
        Dev.Cfg.u8BlockCnt = 0;

        FLASH_Write_CfgDeal();
        if (OK != FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200)), FLASH_CFG_WRITE_BUFF, sizeof(FLASH_CFG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Cfg.u16FlashWriteFailCount++;
        }
        if (OK != FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_CFG_WRITE_BUFF, sizeof(FLASH_CFG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            Dev.Cfg.u16FlashWriteFailCount++;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadWrite_LOG(void) //FLASH读写日志
{
    uint8_t i;
    uint8_t u8BlockFlag;

    u8BlockFlag = 4;
    
    //Dev.Log.u32PowerOnCount++;

    DevLoadDefaultSettingsByReset();

    while (u8BlockFlag)
    {
        u8BlockFlag--;
        //Dev.Cfg.u8BlockCnt = u8BlockFlag;
        FLASH_Read_32Bit(FLASH_LOG_ADD + u8BlockFlag * 0x200, FLASH_LOG_READ_BUFF,  sizeof(FLASH_LOG_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_LOG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_LogDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(FLASH_LOG_READ_BUFF)/sizeof(uint32_t); i++)
                {
                    Dev.Log.u32Words[i] = FLASH_LOG_READ_BUFF[i + 1];  
                }
                //Dev.Cfg.u16FlashReadSuccessCount++;
                return;
            }

        }

        FLASH_Read_32Bit(FLASH_LOG_ADD + u8BlockFlag * 0x200 + 0x100, FLASH_LOG_READ_BUFF, sizeof(FLASH_LOG_READ_BUFF)/sizeof(uint32_t));
        if (0xFFFFFFFF != FLASH_LOG_READ_BUFF[0])
        {
            if (OK == FLASH_Read_LogDeal())
            {
                //Dev.Cfg.u8BlockCnt = u8BlockFlag;
                for (i = 0; i < sizeof(FLASH_LOG_READ_BUFF)/sizeof(uint32_t); i++)
                {
                    Dev.Log.u32Words[i] = FLASH_LOG_READ_BUFF[i + 1];  
                }
                //Dev.Cfg.u16FlashReadSuccessCount++;
                return;
            }
        }

    }

    if (0 == u8BlockFlag)
    {
        Dev.Log.u32BlockCnt = 0;

        FLASH_Write_LogDeal();
        if (OK != FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Log.u32BlockCnt * 0x200)), FLASH_LOG_WRITE_BUFF, sizeof(FLASH_LOG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            //Dev.Cfg.u16FlashWriteFailCount++;
        }
        if (OK != FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Log.u32BlockCnt * 0x200 + 0x100)), FLASH_LOG_WRITE_BUFF, sizeof(FLASH_LOG_WRITE_BUFF)/sizeof(uint32_t)))
        {
            //Dev.Cfg.u16FlashWriteFailCount++;
        }
    }
}


/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Erase(void)
{
    if (Dev.u8EraseFlag == 1)
    {
        if (Dev.Cfg.u8BlockCnt != 0)
        {
            FLASH_Remove_Page(FLASH_CFG_ADD);
            Dev.u8EraseFlag = 0;
        }
    }

    if(Dev.Cfg.u8BlockCnt > 3)
    {
        Dev.Cfg.u8BlockCnt = 0;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_CfgDeal(void)
{
    uint8_t i;
    //uint32_t u32Header;
    uint32_t u32Check;

    Dev.Cfg.u16FlashWriteSuccessCount++;
    FLASH_CFG_WRITE_BUFF [0] =  0xAA5555AA; 

    for (i = 0 ; i < sizeof(HWCfg_Typedef)/sizeof(uint32_t) ; i++)
    {
        FLASH_CFG_WRITE_BUFF[i+1] = Dev.Cfg.u32Words[i];
    }

    u32Check = FLASH_CRC32(FLASH_CFG_WRITE_BUFF,(sizeof(HWCfg_Typedef)/sizeof(uint32_t)+1));

    FLASH_CFG_WRITE_BUFF [sizeof(HWCfg_Typedef)/sizeof(uint32_t)+2] = u32Check;
    
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Cfg(void)
{
    if (FLASHRUN.u8CfgUpdateFlag == 1)
    {    
        if (Dev.u8EraseFlag == 1)
        {
            if (Dev.Cfg.u8BlockCnt != 0 || Dev.u8EraseFlag == 1)
            {
                FLASH_Remove_Page(FLASH_CFG_ADD);
                Dev.u8EraseFlag = 0;
            }
            
        }
        
        Dev.Cfg.u8BlockCnt++;

        if (Dev.Cfg.u8BlockCnt > 3)
        {
            Dev.Cfg.u8BlockCnt = 0;
        }
        /*
        if (Dev.Cfg.u8BlockCnt == 0 || Dev.u8EraseFlag == 1)
        {
            FLASH_Remove_Page(FLASH_CFG_ADD);
            Dev.u8EraseFlag = 0;
        }
        */

        FLASH_Write_CfgDeal();

        FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
        //FLASH_JustWrite_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
        FLASHRUN.u8CfgUpdateFlag = 2;
        FLASHRUN.u32FlashWriteTime = 2;
    }

    else if (FLASHRUN.u8CfgUpdateFlag == 2)
    {
        if (FLASHRUN.u32FlashWriteTime == 0)
        {
            FLASH_Write_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
            //FLASH_JustWrite_32Bit((FLASH_CFG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_CFG_WRITE_BUFF, (sizeof(HWCfg_Typedef) / sizeof(uint32_t) + 2));
            FLASHRUN.u8CfgUpdateFlag = 0;
            FLASHRUN.u32FlashWriteTime = 0;
        }
    }
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_CfgDeal(void)
{
    //uint8_t  i;
    uint32_t u32Check;

    u32Check = FLASH_CRC32(FLASH_CFG_READ_BUFF, (sizeof(HWCfg_Typedef)/sizeof(uint32_t)+1));
    //FLASHRUN.u32CRCTest = u32Check;
    if( 0xAA5555AA == FLASH_CFG_READ_BUFF[0])
    {
        if( u32Check == FLASH_CFG_READ_BUFF[(sizeof(HWCfg_Typedef)/sizeof(uint32_t)+2)] )
        {
            return OK;   
        }
        else
        {
            return !OK;
        }
    }
    else
    {
        return !OK;
    }
    //return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_LogDeal(void)
{
    uint8_t i;
    //uint32_t u32Header;
    uint32_t u32Check;

    //Dev.Cfg.u16FlashWriteSuccessCount++;
    FLASH_CFG_WRITE_BUFF [0] =  0xBB5555BB; 

    for (i = 0 ; i < (sizeof(HWLogInfo_Typedef)/sizeof(uint32_t)) ; i++)
    {
        FLASH_LOG_WRITE_BUFF[i+1] = Dev.Log.u32Words[i];
    }

    u32Check = FLASH_CRC32(FLASH_LOG_WRITE_BUFF,(sizeof(HWLogInfo_Typedef)/sizeof(uint32_t)+1));

    FLASH_CFG_WRITE_BUFF [(sizeof(HWLogInfo_Typedef)/sizeof(uint32_t)+2)] = u32Check;
    
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_Log(void)
{
    if (FLASHRUN.u8LogUpdateFlag == 1)
    {
        if (Dev.u8EraseFlag == 1)
        {
            if (Dev.Cfg.u8BlockCnt != 0)
            {
                FLASH_Remove_Page(FLASH_LOG_ADD);
            }
            Dev.u8EraseFlag = 0;
        }

        Dev.Cfg.u8BlockCnt++;

        if (Dev.Cfg.u8BlockCnt > 3)
        {
            Dev.Cfg.u8BlockCnt = 0;
        }

        FLASH_Write_LogDeal();
        FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8BlockCnt * 0x200)), FLASH_LOG_WRITE_BUFF, (sizeof(FLASH_LOG_WRITE_BUFF) / sizeof(uint32_t)));
        //FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_LOG_WRITE_BUFF, (sizeof(FLASH_LOG_WRITE_BUFF) / sizeof(uint32_t)));
        FLASHRUN.u8LogUpdateFlag = 2;
        FLASHRUN.u32FlashWriteTime = 2;
    }
    else if (FLASHRUN.u8LogUpdateFlag == 2)
    {
        if (FLASHRUN.u32FlashWriteTime == 0)
        {
            FLASH_Write_32Bit((FLASH_LOG_ADD + (Dev.Cfg.u8BlockCnt * 0x200 + 0x100)), FLASH_LOG_WRITE_BUFF, (sizeof(FLASH_LOG_WRITE_BUFF) / sizeof(uint32_t)));
            FLASHRUN.u8LogUpdateFlag = 0;
            FLASHRUN.u32FlashWriteTime = 0;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_LogDeal(void)
{
  
    uint32_t u32Check;
    uint32_t u32Num;

    u32Num = sizeof(FLASH_LOG_WRITE_BUFF)/sizeof(uint32_t);
    u32Check = FLASH_CRC32(FLASH_LOG_READ_BUFF,  (u32Num-1));
 
    if( 0xBB5555BB == FLASH_LOG_READ_BUFF[0])
    {
        if( FLASH_LOG_READ_BUFF[u32Num] == u32Check   )
        {
            return OK;   
        }
        else
        {
            return !OK;
        }
    }
    else
    {
        return !OK;
    }
    //return OK;
}

/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWLog(uint32_t u32add)
{
    HWLogInfo_Typedef HWLog;

    if ( OK == FLASH_ReadNBytes(u32add, HWLog.u32Words, sizeof(HWLogInfo_Typedef) / sizeof(uint32_t)) )
    {        
        //FLASH_LOG_Read_Manage(&HWLog);

        Dev.Log.u32RunTime          = HWLog.u32RunTime;
        Dev.Log.u32PowerOnCount     = HWLog.u32PowerOnCount;       
        Dev.Log.u32SoftFaultCount   = HWLog.u32SoftFaultCount;                
        return;
    }
 
}
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWCfg(uint32_t u32add)
{
    HWCfg_Typedef HWCfg;

    if (OK == FLASH_ReadNBytes(u32add, HWCfg.u32Words, sizeof(HWCfg_Typedef) / sizeof(uint32_t)))
    {
        //FLASH_CFG_Read_Manage(&HWCfg);
        if (OK == FLASH_ReadDevDataCheck(&HWCfg))
        {
            Dev.Cfg.u32ResetPassword = HWCfg.u32ResetPassword;

            Dev.Cfg.u8RadioInterval  = HWCfg.u8RadioInterval;
            Dev.Cfg.u8Repeater = HWCfg.u8Repeater;
            Dev.Cfg.u8LedSwtichFalg = HWCfg.u8LedSwtichFalg;

            Dev.Cfg.u8ModbusPhyAdd = HWCfg.u8ModbusPhyAdd;
            Dev.Cfg.eParity = HWCfg.eParity;
            Dev.Cfg.eStops = HWCfg.eStops;
            Dev.Cfg.eBaudRateID = HWCfg.eBaudRateID;

            Dev.Cfg.u32RemanCode = HWCfg.u32RemanCode;
            Dev.Cfg.u32EnOceanChipID = HWCfg.u32EnOceanChipID;
            Dev.Cfg.u32EnOceanBaseID = HWCfg.u32EnOceanBaseID;

            Dev.Cfg.u16Calibration      = HWCfg.u16Calibration     ;      
            Dev.Cfg.u16CalibrationCH2O  = HWCfg.u16CalibrationCH2O ;  
            Dev.Cfg.u16CalibrationCO2   = HWCfg.u16CalibrationCO2  ;   
            Dev.Cfg.u16CalibrationH     = HWCfg.u16CalibrationH    ;     
            Dev.Cfg.u16CalibrationT     = HWCfg.u16CalibrationT    ;     
            Dev.Cfg.u16CalibrationPM10  = HWCfg.u16CalibrationPM10 ;  
            Dev.Cfg.u16CalibrationPM25  = HWCfg.u16CalibrationPM25 ;  
            Dev.Cfg.u16CalibrationPM100 = HWCfg.u16CalibrationPM100; 
            
            return;
        }
    }
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_ReadDevDataCheck(HWCfg_Typedef *pHWInfo)
{
    /* Use for just HAVC output for fan coil */                     
    /* If only use the parameters for setting VRV system or control panel can be close the hvac output */        
        


    if ( pHWInfo->u8RadioInterval < 100 )
    {
        pHWInfo->u8RadioInterval = 100;
    }

    if ( pHWInfo->eParity > ePARITY_ODD )
    {
        pHWInfo->eParity = ePARITY_NONE;
        return !OK;
    }

    if ( ( pHWInfo->u8ModbusPhyAdd < 1 ) || ( pHWInfo->u8ModbusPhyAdd > 31 ) )
    {       
        pHWInfo->u8ModbusPhyAdd = 1; 
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
    if ( pHWInfo->u8Repeater > 2 )
    {
        pHWInfo->u8Repeater = 0;
        return !OK;
    }

    return OK;
}

/* End of file */
