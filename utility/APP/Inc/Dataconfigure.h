

#ifndef _DATA_CONFIGURE_H_
#define _DATA_CONFIGURE_H_

#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"
//#include "KeyLedDipDectTemp.h"

/**********************************************************************************************************************/
#define AIRBOX_HW_VERSION                                            (0x0042)
#define AIRBOX_FW_VERSION                                            (0x0042)

#define FLASH_LOG_ADD                                                 (0x0801F000)
#define FLASH_CFG_ADD                                                 (0x0801E800)
#define FLASH_LOG_OFFSET                                              (0x20)
#define FLASH_CFG_OFFSET                                              (0x50)

             


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* Modbus register and enocean msc regisiter segment */
/* Use Chip ID */
/* EEP: D201XX channel is from 0 to 30 */
/* Use Chip ID */
/* Modbus register and enocean msc regisiter segment */
/* Use Chip ID */
/*******************************************************************************************/
/* Channel range description */
/*
1. 0 is the dev channel
2. 1--4 is the relay channel of controller with 4channel
3. 5 -- 30, and 0x70 -- 0x79 is the cascade slaver relay channel
4. 0x7A -- 0x8D is the dimming channel triac or dali
*/
#define DEV_CHANNEL                                                 (0x00)

/**********************************************************************************************************************/





/* Use base ID resever 0x20 -- 0x6F for HVAC and Rock */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/**********************************************************************************************************************/
#define MODBUS_MAX_REG_NUMS                                         (255)


/* Use modbus reg resever 0x2000 -- 0x6FFF for HVAC and Rock */

/**********************************************************************************************************************/
/********************* Data reg permission mask *******************************************/
/**********************************************************************************************************************/
#define REG_PERMISSION_N                                            (0x00)//参数保留
#define REG_PERMISSION_X                                            (0x04)//参数可执行
#define REG_PERMISSION_R                                            (0x02)//参数可读
#define REG_PERMISSION_W                                            (0x01)//参数可写
#define REG_VALUE_RANGE_ENABLE                                      (1)
#define REG_VALUE_RANGE_DISABLE                                     (0)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* 0 -- 255 dev have max 256 parameter */

#define MB_INPUT_BASE                                               (0x00)
#define MB_HOLD_BASE                                                (0x00)



#define MB_EQUIPMENT_BASE                                           (0x00)  
#define MB_SENSOR_BASE                                              (0x00)                          

/* dev read */
/* dev run can only read */

#define MB_INPUT_SOFT_YEAR_MONTH                                      (MB_EQUIPMENT_BASE+0x01)  //软件版本号年月
#define MB_INPUT_SOFT_DAY_VERSION                                     (MB_EQUIPMENT_BASE+0x02)  //软件版本号日期版本
#define MB_INPUT_SYSTEM_VOLT                                          (MB_EQUIPMENT_BASE+0x03)  //系统MCU电压
#define MB_INPUT_ENOCEAN_RSSI                                         (MB_EQUIPMENT_BASE+0x04)  //Enocean RSSI值
#define MB_INPUT_WIFI_RSSI                                            (MB_EQUIPMENT_BASE+0x05)  //WIFI RSSI值

#define MB_INPUT_DEVICE_RUNNING_TIME                                  (MB_EQUIPMENT_BASE+0x20)  //设备运行时间
#define MB_INPUT_DEVICE_RUNNING_HIGH_TIME                             (MB_EQUIPMENT_BASE+0x20)  //设备运行时间高16位
#define MB_INPUT_DEVICE_RUNNING_LOW_TIME                              (MB_EQUIPMENT_BASE+0x21)  //设备运行时间低16位

#define MB_INPUT_CH2O_RUNNING_TIME                                    (MB_SENSOR_BASE+0x22)     //甲醛运行时间
#define MB_INPUT_CH2O_RUNNING_HIGH_TIME                               (MB_SENSOR_BASE+0x22)     //甲醛运行时间高16位
#define MB_INPUT_CH2O_RUNNING_LOW_TIME                                (MB_SENSOR_BASE+0x23)     //甲醛运行时间低16位

#define MB_INPUT_CO2_RUNNING_TIME                                     (MB_SENSOR_BASE+0x24)     //CO2运行时间
#define MB_INPUT_CO2_RUNNING_HIGH_TIME                                (MB_SENSOR_BASE+0x24)     //CO2运行时间高16位
#define MB_INPUT_CO2_RUNNING_LOW_TIME                                 (MB_SENSOR_BASE+0x25)     //CO2运行时间低16位

#define MB_INPUT_PMSA03_RUNNING_TIME                                  (MB_SENSOR_BASE+0x26)     //PM2.5运行时间
#define MB_INPUT_PMSA03_RUNNING_HIGH_TIME                             (MB_SENSOR_BASE+0x26)     //PM2.5运行时间高16位
#define MB_INPUT_PMSA03_RUNNING_LOW_TIME                              (MB_SENSOR_BASE+0x27)     //PM2.5运行时间低16位

//#define MB_INPUT_DEVICE_RUNNING_TIME                                  (MB_EQUIPMENT_BASE+0x28)  //设备运行时间
//#define MB_INPUT_CH2O_RUNNING_TIME                                    (MB_SENSOR_BASE+0x29)     //甲醛运行时间
//#define MB_INPUT_CO2_RUNNING_TIME                                     (MB_SENSOR_BASE+0x2A)     //CO2运行时间
//#define MB_INPUT_PMSA03_RUNNING_TIME                                  (MB_SENSOR_BASE+0x2B)     //PM2.5运行时间
#define MB_INPUT_SENSOR_RUNNING_TIME                                  (MB_SENSOR_BASE+0x2C)     //设备、甲醛、CO2PM2.5、运行时间

#define MB_INPUT_COMMUNICATION_FAULT                                  (MB_SENSOR_BASE+0x2D)     //通信故障
#define MB_INPUT_DEVICE_FAULT                                         (MB_EQUIPMENT_BASE+0x2E)  //设备故障
#define MB_INPUT_SENSOR_STATUS                                        (MB_SENSOR_BASE+0x2F)     //传感器状态

#define MB_INPUT_TEMPERATURE_VALUE                                    (MB_SENSOR_BASE+0x30)     //温度值 --- 温度范围(-40~125℃ + 50℃ ) * 10 + 10%的校准参数 --- 90~1925
#define MB_INPUT_HUMIDITY_VALUE                                       (MB_SENSOR_BASE+0x31)     //湿度值 --- 湿度范围(0~100 %RH) * 2 + 10%的校准参数 --- 0~220
#define MB_INPUT_CO2_VALUE                                            (MB_SENSOR_BASE+0x32)     //CO2值 --- 最大值暂定8000 测量范围: 0-5000ppm 
#define MB_INPUT_PM1_VALUE                                            (MB_SENSOR_BASE+0x33)     //PM1.0值
#define MB_INPUT_PM25_VALUE                                           (MB_SENSOR_BASE+0x34)     //PM2.5值
#define MB_INPUT_PM10_VALUE                                           (MB_SENSOR_BASE+0x35)     //PM10值
#define MB_INPUT_CH2O_VALUE                                           (MB_SENSOR_BASE+0x36)     //CH2O(甲醛)值
#define MB_INPUT_SENSOR_VALUE                                         (MB_SENSOR_BASE+0x37)     //所有传感数据(温度、湿度、CO2、PM1.0、PM2.5、PM10、CH2O)
#define MB_INPUT_AIR_QUALITY                                          (MB_SENSOR_BASE+0x38)     //空气质量等级   

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* dev write */

/* dev set */
    //读写参数
#define MB_HOLD_SET_ADDR                                              (MB_EQUIPMENT_BASE + 0x80)//设置地址
#define MB_HOLD_SET_BAUD                                              (MB_EQUIPMENT_BASE + 0x81)//设置波特率

#define MB_HOLD_TIME_RESET_PASSWORD                                   (MB_EQUIPMENT_BASE + 0x82)//时间复位密码
#define MB_HOLD_TIME_RESET_HIGH_PASSWORD                              (MB_EQUIPMENT_BASE + 0x82)//时间复位密码高16位
#define MB_HOLD_TIME_RESET_LOW_PASSWORD                               (MB_EQUIPMENT_BASE + 0x83)//时间复位密码低16位

#define MB_HOLD_DEVICE_RESET_TIMES                                    (MB_EQUIPMENT_BASE + 0x84)//设备运行时间复位次数
#define MB_HOLD_CO2_RESET_TIMES                                       (MB_SENSOR_BASE + 0x85)   //CO2运行时间复位次数
#define MB_HOLD_CH2O_RESET_TIMES                                      (MB_SENSOR_BASE + 0x86)   //甲醛运行时间复位次数
#define MB_HOLD_PMSA03_RESET_TIMES                                    (MB_SENSOR_BASE + 0x87)   //PM2.5运行时间复位次数

#define MB_HOLD_CH2O_FACTORY_TIME                                     (MB_SENSOR_BASE + 0x88)   //甲醛出厂时间
#define MB_HOLD_CH2O_FACTORY_YEAR_MONTH                               (MB_SENSOR_BASE + 0x88)   //甲醛出厂时间年月
#define MB_HOLD_CH2O_FACTORY_DAY                                      (MB_SENSOR_BASE + 0x89)   //甲醛出厂时间日

#define MB_HOLD_CH2O_INSTALL_TIME                                     (MB_SENSOR_BASE + 0x8A)   //甲醛安装时间
#define MB_HOLD_CH2O_INSTALL_YEAR_MONTH                               (MB_SENSOR_BASE + 0x8A)   //甲醛安装时间年月
#define MB_HOLD_CH2O_INSTALL_DAY                                      (MB_SENSOR_BASE + 0x8B)   //甲醛安装时间日

#define MB_HOLD_485MB_ADD                                             (MB_SENSOR_BASE + 0x8C)   //485地址设置
#define MB_HOLD_485MB_BAUD                                            (MB_SENSOR_BASE + 0x8D)   //485波特率设置
#define MB_HOLD_485MB_STOPS                                           (MB_SENSOR_BASE + 0x8E)   //485停止位设置
#define MB_HOLD_485MB_PARITY                                          (MB_SENSOR_BASE + 0x8F)   //485奇偶校验位设置

#define MB_HOLD_TEMPERATURE_CALIB                                     (MB_SENSOR_BASE + 0x90)   //温度校准
#define MB_HOLD_HUMIDITY_CALIB                                        (MB_SENSOR_BASE + 0x91)   //湿度校准
#define MB_HOLD_CO2_CALIB                                             (MB_SENSOR_BASE + 0x92)   //CO2校准
#define MB_HOLD_PM1_CALIB                                             (MB_SENSOR_BASE + 0x93)   //PM1.0校准
#define MB_HOLD_PM25_CALIB                                            (MB_SENSOR_BASE + 0x94)   //PM2.5校准
#define MB_HOLD_PM10_CALIB                                            (MB_SENSOR_BASE + 0x95)   //PM10校准
#define MB_HOLD_CH2O_CALIB                                            (MB_SENSOR_BASE + 0x96)   //CH2O(甲醛) 校准
#define MB_HOLD_LED_SWITCH                                            (MB_EQUIPMENT_BASE + 0x97)//LED指示关闭
#define MB_HOLD_ENOCEAN_REAPTER                                       (MB_EQUIPMENT_BASE + 0x98)//Enocean Reapter

#define MB_HOLD_AIRBOX_RESET_FACTORY_SETTINGS                         (MB_SENSOR_BASE + 0x99)   //AirBox恢复出厂设置

#define VOID_RWPARAM_RESET_FACTORY_SETTINGS                           (MB_SENSOR_BASE + 0xA0)   //传感器恢复出厂设置

#define MB_HOLD_SENSOR_REFRESH                                        (MB_SENSOR_BASE + 0xB0)   //传感器刷新

#define MB_HOLD_NEW_WIND_SYS_MODE                                     (MB_EQUIPMENT_BASE + 0xE0)//新风系统采用自动或手动控制 --- 0为自动，1为手动
#define MB_HOLD_NEW_WIND_SYS_SWITCH                                   (MB_EQUIPMENT_BASE + 0xE1)//APP对新风系统开关机控制 --- 0为开机，1为关机
#define MB_HOLD_NEW_WIND_SYS_SWITCH_STATUS                            (MB_EQUIPMENT_BASE + 0xE2)//新风系统开关机状态反馈 --- 0为开机，1为关机
#define MB_HOLD_NEW_WIND_SYS_WIND_SPEED                               (MB_EQUIPMENT_BASE + 0xE3)//新风系统高、中、低速控制 --- 0:无风,1:低风,2:中风,3:高风,4为无效值
#define MB_HOLD_NEW_WIND_SYS_STATUS                                   (MB_EQUIPMENT_BASE + 0xE4)//新风系统风机运行状态反馈 --- 0为关闭，1为运行
#define MB_HOLD_NEW_WIND_SYS_FILTER_ELEMENT                           (MB_EQUIPMENT_BASE + 0xE5)//新风系统滤芯更换提醒 --- 0不需更换，1需要更换
#define MB_HOLD_NEW_WIND_SYS_FAULT                                    (MB_EQUIPMENT_BASE + 0xE6)//新风系统设备故障 --- 0正常，1故障



/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* Detect the EnOcean send count for MSC*/


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/********************** switch page start *****************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/**********************************************************************************************************************/
//#pragma pack(1)


typedef struct
{
  uint8_t u8FactorySetCount;//出厂设置计数  
  uint8_t u8FactorySetFlag; //出厂设置标记

  uint8_t u8CfgUpdateFlag; //配置更新标记
  uint8_t u8LogUpdateFlag; //日志更新标记
  uint8_t u8SaveCount; //保存计数

  uint32_t u32FlashWriteTime;  //写入等待

  uint32_t u32CRCTest;

}eFLASH_RunTypedef;

typedef union 
{
  struct
  {
    uint32_t u32ResetPassword;

    /* Use for just HAVC output for fan coil */
    /* If only use the parameters for setting VRV system or control panel can be close the hvac output */
    uint8_t u8RadioInterval;
    uint8_t u8Repeater;
    uint8_t u8LedSwtichFalg;
    uint8_t u8BlockCnt;

    uint8_t u8ModbusPhyAdd;
    eUSART_PARITY_TYPE eParity;
    eUSART_STOP_TYPE eStops;
    eUSART_BAUD_ID_TYPE eBaudRateID;

    uint32_t u32RemanCode;
    uint32_t u32EnOceanChipID;
    uint32_t u32EnOceanBaseID;

    uint16_t u16FlashWriteSuccessCount; //Flash写入成功计数
    uint16_t u16FlashWriteFailCount;    //Flash写入失败计数

    uint16_t u16FlashReadSuccessCount; //Flash读取成功计数
    uint16_t u16FlashReadFailCount;    //Flash读取失败计数

    //uint16_t u16CalibrationCode[8]; //各传感器校准值
    uint16_t u16Calibration;          //填补位置
    uint16_t u16CalibrationCH2O;      //CH2O校准值
    uint16_t u16CalibrationCO2;       //CO2校准值
    uint16_t u16CalibrationH;         //湿度校准值
    uint16_t u16CalibrationT;         //温度校准值
    uint16_t u16CalibrationPM10;      //PM1校准值
    uint16_t u16CalibrationPM25;      //PM2.5校准值
    uint16_t u16CalibrationPM100;     //PM10校准值
  };

    uint32_t u32Words[15];
    uint8_t  u8Bytes[60];
}HWCfg_Typedef;

typedef union 
{
  struct
  {
    uint32_t u32PowerOnCount;   //开机次数
    uint32_t u32RunTime;        //运行时间
    uint32_t u32SoftFaultCount; //软故障计数
    uint32_t u32BlockCnt;       //块标志
  };

    uint32_t u32Words[5];
    uint8_t  u8Bytes[20];

}HWLogInfo_Typedef;

typedef struct
{
    uint32_t            u32BuildYYMMDD;
    uint32_t            u32BuildHHMMSS;
    uint16_t            u16HWVersion;
    uint16_t            u16FWVersion;

    uint8_t             u8EraseFlag;

    uint32_t            u32Error;                   //故障
    uint16_t            u16CleanErrorFlagTime;      //清除错误标志时间 
    uint8_t             u8ErrorSendTime;            //故障发送时间
    uint8_t             u8EnOceanError;


    uint16_t            u16CommunicationFault;      //通信故障
    uint16_t            u16DebiceFault;             //设备故障
    uint16_t            u16AirQuality;              //空气质量等级

    uint16_t            u16CO2Value;                //CO2值
    uint16_t            u16CH2OValue;               //CH2O值
    uint16_t            u16TemperatureValue;        //温度值
    uint16_t            u16HumidityValue;           //湿度值
    uint16_t            u16PM1Value;                //PM1.0值
    uint16_t            u16PM25Value;               //PM2.5值
    uint16_t            u16PM100Value;              //PM10值

    //uint8_t             u8RelayOutputChannel;
    
    uint8_t             u8CfgUpdate;               //配置更新
    uint8_t             u8LogUpdate;               //日志更新
    uint8_t             u8SaveCount;               //保存计数 
}DevRun_Typedef;

#ifdef HW_DEBUG    
    typedef struct 
    {

        uint32_t            u32EnOceanRxID;
        uint32_t            u32EnOceanRxCount;    
        uint32_t            u32EnOceanRPSID;
        uint32_t            u32EnOceanRPSRxCount;
        uint32_t            u32EnOcean4BSID;
        uint32_t            u32EnOcean4BSRxCount;
        uint32_t            u32EnOcean1BSID;
        uint32_t            u32EnOcean1BSRxCount;
        uint32_t            u32EnOceanVLDID;
        uint32_t            u32EnOceanVLDRxCount;
        uint32_t            u32EnOceanMSCID;
        uint32_t            u32EnOceanMSCRxCount;

        uint32_t            u32TransmitCount[4];
        uint32_t            u32TouchPressedID[4];
        uint32_t            u32TouchReleaseID[4];
        uint32_t            u32TouchRPSCount[4];

    }DevDebug_Typedef;
#endif

typedef struct
{
    uint8_t             u8State;
    uint8_t             u8LearnState;
    uint8_t             u8LearnChannel;
    uint8_t             u8LearnMode;
    uint8_t             u8LearnSuccessTime;
    uint8_t             u8LearnAutoSendEEPTime;
	uint8_t             u8LearnSendEvent;
}DevManual_Typedef;


typedef struct
{
    HWCfg_Typedef       Cfg;
    HWLogInfo_Typedef   Log;
    DevRun_Typedef         ;

#ifdef HW_DEBUG
    DevDebug_Typedef       ;    
#endif

    DevManual_Typedef;

}Dev_Typedef;




//#pragma pack()
/*******************************************************************************/
/*******************************************************************************/


/*******************************************************************************/
/*******************************************************************************/
extern Dev_Typedef               Dev;
extern eFLASH_RunTypedef         FLASHRUN;




/* Clover Dev Setting */
extern const RegTab_Typedef DevRegTab[];


/* Clover Rock Setting */


uint8_t Dev_GetRegTabSize(void);


/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_DevRunSave(void);
/**
   * @brief
   * @param
   * @retval
   */
void FLASH_ChannelUpdate(uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
void HardWareLoadDefaultSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettingsByReset(void);

/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultData(void);
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultEnable(void);

/*************************************************************************/
/**************************FLASHRUN *****************************************/
/*************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_FactorySettings(void);  //FLASHRUN 写入出厂设置参数
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadWrite_LOG(void); //FLASH读写日志
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Read_PowerOn(void);


/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWLog(uint32_t u32add);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_ReadHWCfg(uint32_t u32add);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_ReadDevDataCheck(HWCfg_Typedef *pHWInfo);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_CfgDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_CfgDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
 void FLASH_Write_Cfg(void);
 /**
  * @brief
  * @param
  * @retval None
  */
void FLASH_Write_LogDeal(void);
/**
  * @brief
  * @param
  * @retval None
  */
 void FLASH_Write_Log(void);
 /**
  * @brief
  * @param
  * @retval None
  */
uint8_t FLASH_Read_LogDeal(void);
#if 0
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_CFG_Write_Manage(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_CFG_Read_Manage(HWCfg_Typedef *pHWCfg);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_LOG_Write_Manage(void);
/**
  * @brief
  * @param
  * @retval None
  */
void FLASH_LOG_Read_Manage(HWLogInfo_Typedef *pHWLog);

#endif











#endif

