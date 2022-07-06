
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_H_
#define __KEY_H_

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"

/*******************************************************************************/
/*******************     差值上报限值                        ********************/
/*******************************************************************************/
#define  DIFFERENCE_CH2O_LIMIT    (2)     //差值上报限值
#define  DIFFERENCE_CO2_LIMIT     (20)    //差值上报限值
#define  DIFFERENCE_H_LIMIT       (1)     //差值上报限值
#define  DIFFERENCE_T_LIMIT       (1)     //差值上报限值
#define  DIFFERENCE_PM100_LIMIT   (2)     //差值上报限值
#define  DIFFERENCE_PM25_LIMIT    (2)     //差值上报限值
#define  DIFFERENCE_PM10_LIMIT    (2)     //差值上报限值
/*******************************************************************************/
/*******************     传感器数据限值                        ********************/
/*******************************************************************************/
#define  CH2O_VALUE_MAX                 (1500)       //CH2O最大值
#define  CH2O_VALUE_MIN                 (0)          //CH2O最小值
     
#define  CO2_VALUE_MAX                  (5000)       //CO2最大值
#define  CO2_VALUE_MIN                  (400)        //CO2最小值
     
#define  H_VALUE_MAX                    (200)        //湿度最大值
#define  H_VALUE_MIN                    (0)          //湿度最小值

#define  T_VALUE_MAX                    (1250+500)   //温度最大值
#define  T_VALUE_MIN                    (0+500)      //温度最小值

#define  PM_VALUE_MAX                   (500)        //PM值最大值
#define  PM_VALUE_MIN                   (0)          //PM值最小值
/*******************************************************************************/
/*******************     传感器数据限值                        ********************/
/*******************************************************************************/



#define u32SendTimeInterval  (1*1000)  //1S

#define RANDOMREPORT_TIME_MAX   (600*1000)   //随机上报时间最大值  10分钟
#define RANDOMREPORT_TIME_MIN   (300*1000)   //随机上报时间最小值  5分钟


typedef enum
{
    eENOCEAN_DIFFERENCESEND_IDLE       = 0x00,     //差值闲置状态
    eENOCEAN_DIFFERENCESEND_WAIT       = 0x01,     //差值等待发送
    eENOCEAN_DIFFERENCESEND_CO2        = 0x02,     //差值发送CO2
    eENOCEAN_DIFFERENCESEND_CH2O       = 0x03,     //差值发送CH2O
    eENOCEAN_DIFFERENCESEND_H          = 0x04,      //差值发送湿度
    eENOCEAN_DIFFERENCESEND_T          = 0x05,      //差值发送温度 
    eENOCEAN_DIFFERENCESEND_PM10       = 0x06,      //差值发送PM1
    eENOCEAN_DIFFERENCESEND_PM25       = 0x07,      //差值发送PM25
    eENOCEAN_DIFFERENCESEND_PM100      = 0x08,      //差值发送PM10

    Enocean_Send_FaultCode             = 0x09,      //发送故障码

}eEnoceanStateDifference_TYPE;

typedef enum
{
    eENOCEAN_PROACTIVESEND_IDLE       = 0x10,     //主动闲置状态
    eENOCEAN_PROACTIVESEND_WAIT       ,           //主动等待发送
    eENOCEAN_PROACTIVESEND_CO2        ,           //主动发送CO2
    eENOCEAN_PROACTIVESEND_CH2O       ,           //主动发送CH2O
    eENOCEAN_PROACTIVESEND_H          ,           //主动发送湿度
    eENOCEAN_PROACTIVESEND_T          ,           //主动发送温度 
    eENOCEAN_PROACTIVESEND_PM10       ,           //主动发送PM1
    eENOCEAN_PROACTIVESEND_PM25       ,           //主动发送PM25
    eENOCEAN_PROACTIVESEND_PM100      ,           //主动发送PM10

}eEnoceanStateProactive_TYPE;

//空气质量等级
typedef enum
{
    eAIR_QUALITY_EXCELLENT = 0,   // 优
    eAIR_QUALITY_GOOD ,           // 良
    eAIR_QUALITY_MODERATE,       // 中
    eAIR_QUALITY_POOR,            // 差

} airQuality_t;

//  数组中 0-故障  1-CH2O  2-CO2  3-H（湿度）  4-T（温度）  5-PM100  6-PM25  7-PM10
typedef struct
{
	eEnoceanStateProactive_TYPE   eRunStateProactive;
    eEnoceanStateDifference_TYPE  eRunStateDifference;

    airQuality_t        eAirQuality;        //空气等级
    airQuality_t        eCO2AirQuality;    //CO2等级
    airQuality_t        eCH2OAirQuality;  //ch2O等级
    airQuality_t        ePM25AirQuality;  //PM2.5等级
    airQuality_t        ePM10AirQuality;  //PM10等级

    uint8_t  u8Count;
    //uint8_t  u8ProactiveReportingFlag[8];   //各传感器主动上报标志 

    uint8_t u8ProactiveReportFlagErr;        //故障上报标志
    uint8_t u8ErrRestoreFlag;                //故障恢复标志restore


    uint8_t u8DifferenceReportFlagCH2O;      //差值上报标记 CH2O
    uint8_t u8DifferenceReportFlagCO2;       //差值上报标记 CO2
    uint8_t u8DifferenceReportFlagH;         //差值上报标记 H
    uint8_t u8DifferenceReportFlagT;         //差值上报标记 T
    uint8_t u8DifferenceReportFlagPM10;      //差值上报标记 PM10
    uint8_t u8DifferenceReportFlagPM25;      //差值上报标记 PM25
    uint8_t u8DifferenceReportFlagPM100;     //差值上报标记 PM100


    uint16_t u16LastDataCH2O;      //CH2O上次数据
    uint16_t u16LastDataCO2;       //CO2上次数据
    uint16_t u16LastDataH;         //湿度上次数据
    uint16_t u16LastDataT;         //温度上次数据
    uint16_t u16LastDataPM10;      //PM1上次数据
    uint16_t u16LastDataPM25;      //PM2.5上次数据
    uint16_t u16LastDataPM100;     //PM10上次数据

    uint16_t u16DataCH2O;          //CH2O数据
    uint16_t u16DataCO2;           //CO2数据
    uint16_t u16DataH;             //湿度数据
    uint16_t u16DataT;             //温度数据
    uint16_t u16DataPM10;          //PM1数据
    uint16_t u16DataPM25;          //PM2.5数据
    uint16_t u16DataPM100;         //PM10数据

    
    uint16_t u16CalibrationCH2O;      //CH2O校准值
    uint16_t u16CalibrationCO2;       //CO2校准值
    uint16_t u16CalibrationH;         //湿度校准值
    uint16_t u16CalibrationT;         //温度校准值
    uint16_t u16CalibrationPM10;      //PM1校准值
    uint16_t u16CalibrationPM25;      //PM2.5校准值
    uint16_t u16CalibrationPM100;     //PM10校准值

    uint8_t u8PMSTestFlag;                  //PMS测试标记  

    uint32_t u32DifferenceSendWait;
	uint16_t u16ReadPeriod;
	uint32_t u32ReadWait;
    uint16_t u16FaultCodeSendWait;  //故障码上报计数
    uint32_t u32RandomNumberSeed;   //随机数种子
    uint8_t  u8BootReportFlag;      //开机上报标记
    uint32_t u32BootReportCount;    //开机上报计数

    uint16_t u16CH2OSendWait;
    uint16_t u16CO2SendWait;
    uint16_t u16HSendWait;
    uint16_t u16TSendWait;
    uint16_t u16PM25SendWait;

    uint16_t u16HumidityDifferece;     //湿度差值
    uint16_t u16TemperatureDifferece;  //温度差值
    uint16_t u16CH2ODifferece;   //CH2O差值
    uint16_t u16CO2Differece;    //CO2差值
    uint16_t u16PM100Differece;  //PM100差值
    uint16_t u16PM25Differece;   //PM25差值
    uint16_t u16PM10Differece;   //PM10差值


    //uint32_t u32SendTimeInterval
    
}ReportedData_Typedef;

extern ReportedData_Typedef ReportedData;


/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void EnOceanProactiveReporting(ReportedData_Typedef *pReportedData);//Enocean主动上报
/**
   * @brief
   * @param
   * @retval
   */
void Enocean_Tick1ms(ReportedData_Typedef *pReportedData);
/**
   * @brief
   * @param
   * @retval
   */
uint32_t RandomReport_Time(void);  //随机上报时间
/**
   * @brief
   * @param
   * @retval
   */
uint8_t Air_Quality_Grade(ReportedData_Typedef *pReportedData);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SensorProactiveReporting(void);  //传感器主动上报
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void EnOceanDifferenceReport(ReportedData_Typedef *pReportedData);  //Enocean差值上报
/**
   * @brief
   * @param    //1.校准值  2.采样值
   * @retval
   */
uint16_t CalibrationValue_Processing(uint16_t u16CalibrationValue,uint16_t u16CollectionValue);  //校准值处理
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FaultHandling(void);//故障处理
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */        
void OverrunDataDeal(void);//处理超过限值的数据


#endif