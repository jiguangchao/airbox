
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
/* User App */
#include "Dataconfigure.h"

#include "..\..\BSP_Include.h"

#include "main.h"

#include "RS485Modbus.h"
#include "PMSA003.h"
#include "CH2O_CO2.h"
//#include "SHT20.h"
#include "Led.h"
#include "Key.h"
#include "BSP.h"

#include "EnOceanCascade.h"
#include "EnOceanMSCCascade.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
ReportedData_Typedef ReportedData;

/* Private function prototypes -----------------------------------------------*/

/**
   * @brief
   * @param
   * @retval
   */
void Enocean_Tick1ms(ReportedData_Typedef *pReportedData)
{
    if (pReportedData->u32ReadWait)
    {
        pReportedData->u32ReadWait--;
    }
    if (pReportedData->u16ReadPeriod)
    {
        pReportedData->u16ReadPeriod--;
    }
    if (Dev.u16DebiceFault != 0 || Dev.u16CommunicationFault != 0)
    {
        pReportedData->u16FaultCodeSendWait++;
    }

    pReportedData->u32RandomNumberSeed++;

    if (pReportedData->u16CH2OSendWait)
    {
        pReportedData->u16CH2OSendWait--;
    }
    if (pReportedData->u16CO2SendWait)
    {
        pReportedData->u16CO2SendWait--;
    }
    if (pReportedData->u16HSendWait)
    {
        pReportedData->u16HSendWait--;
    }
    if (pReportedData->u16TSendWait)
    {
        pReportedData->u16TSendWait--;
    }
    if (pReportedData->u16PM25SendWait)
    {
        pReportedData->u16PM25SendWait--;
    }
    
}
/**
   * @brief
   * @param
   * @retval
   */
uint32_t RandomReport_Time(void)  //随机上报时间
{
    uint32_t time;
    srand(ReportedData.u32RandomNumberSeed);
    time= rand()%(RANDOMREPORT_TIME_MAX - RANDOMREPORT_TIME_MIN) +RANDOMREPORT_TIME_MIN;  //产生一个随机数

    return time;
}
/**
   * @brief
   * @param    //1.校准值  2.采样值
   * @retval
   */
uint16_t CalibrationValue_Processing(uint16_t u16CalibrationValue,uint16_t u16CollectionValue)  //校准值处理
{
    uint16_t u32difference;

    if (u16CalibrationValue > u16CollectionValue)
    {
        u32difference = (uint16_t)(u16CalibrationValue - u16CollectionValue);
    }
    else
    {
        u32difference = (uint16_t)(u16CollectionValue - u16CalibrationValue);
        u32difference = u32difference | 0x8000;
    }
    return u32difference;
}
/**
   * @brief
   * @param
   * @retval
   */
void CO2_Air_Quality_Grade(ReportedData_Typedef *pReportedData) //CO2
{
    //CO2评级   
    if ( eAIR_QUALITY_EXCELLENT == pReportedData->eCO2AirQuality )
    {
        if (Dev.u16CO2Value > 950) //差  1000
        {
             pReportedData->eCO2AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16CO2Value > 850) //一般   900
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16CO2Value > 750) //良好   700
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_GOOD;
        }

    }
    else if ( eAIR_QUALITY_GOOD == pReportedData->eCO2AirQuality )
    {
        if (Dev.u16CO2Value > 950) //差   1000
        {
             pReportedData->eCO2AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16CO2Value > 850) //一般  900
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16CO2Value < 650) //良好   700
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if ( eAIR_QUALITY_MODERATE == pReportedData->eCO2AirQuality )
    {
        if (Dev.u16CO2Value > 950) //差   1000
        {
             pReportedData->eCO2AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16CO2Value > 750) //良好   700
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_GOOD;
        }        
        else if (Dev.u16CO2Value < 650) //优秀   700
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if ( eAIR_QUALITY_POOR == pReportedData->eCO2AirQuality )
    {
        if (Dev.u16CO2Value > 850) //一般  900
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16CO2Value > 750) //良好   700
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_GOOD;
        }        
        else if (Dev.u16CO2Value < 650) //优秀   700
        {
            pReportedData->eCO2AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }        

}
/**
   * @brief
   * @param
   * @retval
   */
void CH2O_Air_Quality_Grade(ReportedData_Typedef *pReportedData) //CH2O
{
    //甲醛评级
    if (eAIR_QUALITY_EXCELLENT == pReportedData->eCH2OAirQuality)
    {
        if (Dev.u16CH2OValue > 100) //差
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16CH2OValue > 90) //一般
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16CH2OValue > 80) //良好
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_GOOD;
        }
    }
    else if (eAIR_QUALITY_GOOD == pReportedData->eCH2OAirQuality)
    {
        if (Dev.u16CH2OValue > 100) //差
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16CH2OValue > 90) //一般
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16CH2OValue < 75) //优秀
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if (eAIR_QUALITY_MODERATE == pReportedData->eCH2OAirQuality)
    {
        if (Dev.u16CH2OValue > 100) //差
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16CH2OValue > 80) //良好
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_GOOD;
        }
        else if (Dev.u16CH2OValue < 75) //优秀
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if (eAIR_QUALITY_POOR == pReportedData->eCH2OAirQuality)
    {
        if (Dev.u16CH2OValue > 90) //一般
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16CH2OValue > 80) //良好
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_GOOD;
        }
        else if (Dev.u16CH2OValue < 75) //优秀
        {
            pReportedData->eCH2OAirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
}
/**
   * @brief
   * @param
   * @retval
   */
void PM25_Air_Quality_Grade(ReportedData_Typedef *pReportedData) //PM2.5
{
     //PM2.5评级
    if (eAIR_QUALITY_EXCELLENT == pReportedData->ePM25AirQuality)
    {
        if (Dev.u16PM25Value > 150) //差
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16PM25Value > 75) //一般
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16PM25Value > 35) //良好
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_GOOD;
        }
    }
    else if (eAIR_QUALITY_GOOD == pReportedData->ePM25AirQuality)
    {
        if (Dev.u16PM25Value > 150) //差
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16PM25Value > 75) //一般
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16PM25Value < 30) //优秀
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if (eAIR_QUALITY_MODERATE == pReportedData->ePM25AirQuality)
    {
        if (Dev.u16PM25Value > 150) //差
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16PM25Value > 35) //良好
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_GOOD;
        }
        else if (Dev.u16PM25Value < 30) //优秀
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if (eAIR_QUALITY_POOR == pReportedData->ePM25AirQuality)
    {
        if (Dev.u16PM25Value > 75) //一般
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16PM25Value > 35) //良好
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_GOOD;
        }
        else if (Dev.u16PM25Value < 30) //优秀
        {
            pReportedData->ePM25AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
}
/**
   * @brief
   * @param
   * @retval
   */
void PM10_Air_Quality_Grade(ReportedData_Typedef *pReportedData) //PM10
{
     //PM2.5评级
    if (eAIR_QUALITY_EXCELLENT == pReportedData->ePM10AirQuality)
    {
        if (Dev.u16PM25Value > 150) //差
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16PM25Value > 75) //一般
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16PM25Value > 35) //良好
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_GOOD;
        }
    }
    else if (eAIR_QUALITY_GOOD == pReportedData->ePM10AirQuality)
    {
        if (Dev.u16PM25Value > 150) //差
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16PM25Value > 75) //一般
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16PM25Value < 30) //优秀
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if (eAIR_QUALITY_MODERATE == pReportedData->ePM10AirQuality)
    {
        if (Dev.u16PM25Value > 150) //差
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_POOR;
        }
        else if (Dev.u16PM25Value > 35) //良好
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_GOOD;
        }
        else if (Dev.u16PM25Value < 30) //优秀
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
    else if (eAIR_QUALITY_POOR == pReportedData->ePM10AirQuality)
    {
        if (Dev.u16PM25Value > 75) //一般
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_MODERATE;
        }
        else if (Dev.u16PM25Value > 35) //良好
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_GOOD;
        }
        else if (Dev.u16PM25Value < 30) //优秀
        {
            pReportedData->ePM10AirQuality = eAIR_QUALITY_EXCELLENT;
        }
    }
}

/**
   * @brief
   * @param
   * @retval
   */
uint8_t Air_Quality_Grade(ReportedData_Typedef *pReportedData) //空气质量评级
{
    CO2_Air_Quality_Grade(pReportedData);   //CO2
    CH2O_Air_Quality_Grade(pReportedData);  //CH2O
    PM25_Air_Quality_Grade(pReportedData);  //PM2.5
    PM10_Air_Quality_Grade(pReportedData);  //PM10

    if ( eAIR_QUALITY_POOR == pReportedData->eCH2OAirQuality || eAIR_QUALITY_POOR == pReportedData->eCO2AirQuality || eAIR_QUALITY_POOR == pReportedData->ePM10AirQuality || eAIR_QUALITY_POOR == pReportedData->ePM25AirQuality )
    {
        pReportedData->eAirQuality = eAIR_QUALITY_POOR;
        Dev.u16AirQuality=4;
        return OK;
    }   
    else if ( eAIR_QUALITY_MODERATE == pReportedData->eCH2OAirQuality || eAIR_QUALITY_MODERATE == pReportedData->eCO2AirQuality || eAIR_QUALITY_MODERATE == pReportedData->ePM10AirQuality || eAIR_QUALITY_MODERATE == pReportedData->ePM25AirQuality )
    {
        pReportedData->eAirQuality = eAIR_QUALITY_MODERATE;
        Dev.u16AirQuality=3;
        return OK;
    }  
    else if ( eAIR_QUALITY_GOOD == pReportedData->eCH2OAirQuality || eAIR_QUALITY_GOOD == pReportedData->eCO2AirQuality || eAIR_QUALITY_GOOD == pReportedData->ePM10AirQuality || eAIR_QUALITY_GOOD == pReportedData->ePM25AirQuality )
    {
        pReportedData->eAirQuality = eAIR_QUALITY_GOOD;
        Dev.u16AirQuality=2;
        return OK;
    }        
    else if ( eAIR_QUALITY_EXCELLENT == pReportedData->eCH2OAirQuality || eAIR_QUALITY_EXCELLENT == pReportedData->eCO2AirQuality || eAIR_QUALITY_EXCELLENT == pReportedData->ePM10AirQuality || eAIR_QUALITY_EXCELLENT == pReportedData->ePM25AirQuality )
    {
        pReportedData->eAirQuality = eAIR_QUALITY_EXCELLENT;
        Dev.u16AirQuality=1;
        return OK;
    }
    return OK;

}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FaultHandling(void) //故障处理
{
    //设备掉线
    if (CH2O_CO2.eCH2OFaultCode == eCH2O_EQUIPMENT_DROPS)
    {
        Dev.u16DebiceFault |= 0x01 << (3);
    }
    if (CH2O_CO2.eCO2FaultCode == eCO2_EQUIPMENT_DROPS)
    {
        Dev.u16DebiceFault |= 0x01 << (4);
    }
    if (PMSA.eFaultCode == ePMSA_EQUIPMENT_DROPS)
    {
        Dev.u16DebiceFault |= 0x01 << (5);
    }
    if (SHT20.eFaultCode == eSHT20_EQUIPMENT_DROPS)
    {
        Dev.u16DebiceFault |= 0x01 << (6);
    }

    //报文异常
    if (CH2O_CO2.eCH2OFaultCode == eCH2O_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (2);
    }
    if (CH2O_CO2.eCO2FaultCode == eCO2_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (3);
    }
    if (PMSA.eFaultCode == ePMSA_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (4);
    }
    if (SHT20.eFaultCode == eSHT20_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (5);
    }

    //数据异常
    if (CH2O_CO2.eCH2OFaultCode == eCH2O_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (13);
    }
    if (CH2O_CO2.eCO2FaultCode == eCO2_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (12);
    }
    if (PMSA.eFaultCode == ePMSA_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (11);
    }
    if (SHT20.eFaultCode == eSHT20_EXCEPTION_MESSAGE)
    {
        Dev.u16CommunicationFault |= 0x01 << (10);
    }


    //故障清除
    if (CH2O_CO2.eCH2OFaultCode == eCH2O_NORMAL)
    {
        Dev.u16DebiceFault &= ~(0x01 << 3 );
        Dev.u16CommunicationFault &= ~(0x01 << 2 );
        Dev.u16CommunicationFault &= ~(0x01 << 13 );
    }
    if (CH2O_CO2.eCO2FaultCode == eCO2_NORMAL)
    {
        Dev.u16DebiceFault &= ~(0x01 << 4 );
        Dev.u16CommunicationFault &= ~(0x01 << 3 );
        Dev.u16CommunicationFault &= ~(0x01 << 12 );
    }
    if (PMSA.eFaultCode == ePMSA_NORMAL)
    {
        Dev.u16DebiceFault &= ~(0x01 << 5 );
        Dev.u16CommunicationFault &= ~(0x01 << 4 );
        Dev.u16CommunicationFault &= ~(0x01 << 11 );
    }
    if (SHT20.eFaultCode == eSHT20_NORMAL)
    {
        Dev.u16DebiceFault &= ~(0x01 << 6 );
        Dev.u16CommunicationFault &= ~(0x01 << 5 );
        Dev.u16CommunicationFault &= ~(0x01 << 10 );
    }

    if (Dev.u16DebiceFault != 0 || Dev.u16CommunicationFault != 0)
    {
        if (ReportedData.u16FaultCodeSendWait > (10*1000))
        {
            ReportedData.u16FaultCodeSendWait = 0;
            ReportedData.eRunStateDifference = Enocean_Send_FaultCode;
            ReportedData.u8ProactiveReportFlagErr = 1;
            ReportedData.u8ErrRestoreFlag = 1;
        }
    }
    else
    {
        if ( ReportedData.u8ErrRestoreFlag > 0x00 )
        {
            ReportedData.u8ErrRestoreFlag++ ;
            if ( ReportedData.u8ErrRestoreFlag > 10)
            {
                ReportedData.u8ErrRestoreFlag = 0;
            }          
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_DEVICE_FAULT);
        }
    }


}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */        
void OverrunDataDeal(void)   //处理超过限值的数据
{
    /*   PM1  */
    if (Dev.u16PM1Value > PM_VALUE_MAX)
    {
        Dev.u16PM1Value = PM_VALUE_MAX;
    }
    /*   PM2.5  */
    if (Dev.u16PM25Value > PM_VALUE_MAX)
    {
        Dev.u16PM25Value = PM_VALUE_MAX;
    }
    /*   PM10  */
    if (Dev.u16PM100Value > PM_VALUE_MAX)
    {
        Dev.u16PM100Value = PM_VALUE_MAX;
    }

    /*   CO2  */
    if (Dev.u16CO2Value < CO2_VALUE_MIN)
    {
        Dev.u16CO2Value = CO2_VALUE_MIN;
    }
    else if (Dev.u16CO2Value > CO2_VALUE_MAX)
    {
        Dev.u16CO2Value = CO2_VALUE_MAX;
    }

    /*   CH2O  */
    if (Dev.u16CH2OValue > CH2O_VALUE_MAX)
    {
        Dev.u16CH2OValue = CH2O_VALUE_MAX;
    }

    /*   温度  */
    if (Dev.u16TemperatureValue < T_VALUE_MIN)
    {
        Dev.u16TemperatureValue = T_VALUE_MIN;
    }
    else if (Dev.u16TemperatureValue > T_VALUE_MAX)
    {
        Dev.u16TemperatureValue = T_VALUE_MAX;
    }
    /*   湿度  */
    if (Dev.u16HumidityValue > H_VALUE_MAX)
    {
        Dev.u16HumidityValue = H_VALUE_MAX;
    }
    
} 
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SensorDataCalibration_CH2O(void) //校准值的处理 CH2O
{
    uint16_t u16CalibrationNum;
    uint8_t  u8Num;

    u8Num = ReportedData.u16CalibrationCH2O >> (16-1);
    u16CalibrationNum = ReportedData.u16CalibrationCH2O & 0x7FFF;

    if (u8Num == 1)
    {
        if (u16CalibrationNum > CH2O_CO2.u16CH2ONumerical)
        {
            Dev.u16CH2OValue = 0;
            return OK;
        }
        Dev.u16CH2OValue = CH2O_CO2.u16CH2ONumerical - u16CalibrationNum;
        //return OK;
    }
    else
    {
        Dev.u16CH2OValue = CH2O_CO2.u16CH2ONumerical + u16CalibrationNum;
        //return OK;
    }
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SensorDataCalibration_CO2(void) //校准值的处理 CO2
{
    uint16_t u16CalibrationNum;
    uint8_t  u8Num;

    u8Num = ReportedData.u16CalibrationCO2 >> (16-1);
    u16CalibrationNum = ReportedData.u16CalibrationCO2 & 0x7FFF;

    if (u8Num == 1)
    {
        if (u16CalibrationNum > CH2O_CO2.u16CO2Numerical)
        {
            Dev.u16CO2Value = 0;
            return OK;
        }
        Dev.u16CO2Value = CH2O_CO2.u16CO2Numerical - u16CalibrationNum;
        return OK;
    }
    else
    {
        Dev.u16CO2Value = CH2O_CO2.u16CO2Numerical + u16CalibrationNum;
        return OK;
    }
    //return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SensorDataCalibration_H(void)  //校准值的处理 湿度
{
    uint16_t u16CalibrationNum;
    uint8_t  u8Num;

    u8Num = ReportedData.u16CalibrationH >> (16 - 1);
    u16CalibrationNum = ReportedData.u16CalibrationH & 0x7FFF;

    if (u8Num == 1)
    {
        if (u16CalibrationNum > SHT20.u8HumidityValue)
        {
            SHT20.u8HumidityValue = 0;
            return OK;
        }
        Dev.u16HumidityValue = SHT20.u8HumidityValue - u16CalibrationNum;
        return OK;
    }
    else
    {
        Dev.u16HumidityValue = SHT20.u8HumidityValue + u16CalibrationNum;
        return OK;
    }
    //return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SensorDataCalibration_T(void) //校准值的处理  温度
{
    uint16_t u16CalibrationNum;
    uint8_t u8Num;

    u8Num = ReportedData.u16CalibrationT >> (16 - 1);
    u16CalibrationNum = ReportedData.u16CalibrationT & 0x7FFF;

    if (u8Num == 1)
    {
        if (u16CalibrationNum > SHT20.i16TemperatureOfDegreesCelsius)
        {
            Dev.u16TemperatureValue = 0;
            return OK;
        }
        Dev.u16TemperatureValue = SHT20.i16TemperatureOfDegreesCelsius - u16CalibrationNum;
        return OK;
    }
    else
    {
        Dev.u16TemperatureValue = SHT20.i16TemperatureOfDegreesCelsius + u16CalibrationNum;
        return OK;
    }
    //return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SensorDataCalibration_PM10(void) //校准值的处理  PM1.0
{
    uint16_t u16CalibrationNum;
    uint8_t u8Num;

    u8Num = ReportedData.u16CalibrationPM10 >> (16 - 1);
    u16CalibrationNum = ReportedData.u16CalibrationPM10 & 0x7FFF;

    if (u8Num == 1)
    {
        if (u16CalibrationNum > PMSA.u16PM10Numerical)
        {
            Dev.u16PM1Value = 0;
            return OK;
        }
        Dev.u16PM1Value = PMSA.u16PM10Numerical - u16CalibrationNum;
        return OK;
    }
    else
    {
        Dev.u16PM1Value = PMSA.u16PM10Numerical + u16CalibrationNum;
        return OK;
    }
    //return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SensorDataCalibration_PM25(void) //校准值的处理  PM2.5
{
    uint16_t u16CalibrationNum;
    uint8_t u8Num;

    u8Num = ReportedData.u16CalibrationPM25 >> (16 - 1);
    u16CalibrationNum = ReportedData.u16CalibrationPM25 & 0x7FFF;

    if (u8Num == 1)
    {
        if (u16CalibrationNum > PMSA.u16PM25Numerical)
        {
            Dev.u16PM25Value = 0;
            return OK;
        }
        Dev.u16PM25Value = PMSA.u16PM25Numerical - u16CalibrationNum;
        return OK;
    }
    else
    {
        Dev.u16PM25Value = PMSA.u16PM25Numerical + u16CalibrationNum;
        return OK;
    }
    //return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SensorDataCalibration_PM100(void) //校准值的处理  PM100
{
    uint16_t u16CalibrationNum;
    uint8_t u8Num;

    u8Num = ReportedData.u16CalibrationPM100 >> (16 - 1);
    u16CalibrationNum = ReportedData.u16CalibrationPM100 & 0x7FFF;

    if (u8Num == 1)
    {
        if (u16CalibrationNum > PMSA.u16PM100Numerical)
        {
            Dev.u16PM100Value = 0;
            return OK;
        }
        Dev.u16PM100Value = PMSA.u16PM100Numerical - u16CalibrationNum;
        return OK;
    }
    else
    {
        Dev.u16PM100Value = PMSA.u16PM100Numerical + u16CalibrationNum;
        return OK;
    }
    //return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SensorDataCalibration(void) //校准值的处理  
{
    SensorDataCalibration_CH2O();
    SensorDataCalibration_CO2();
    SensorDataCalibration_H();
    SensorDataCalibration_T();
    SensorDataCalibration_PM10();
    SensorDataCalibration_PM25();
    SensorDataCalibration_PM100();
    OverrunDataDeal();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t  DifferenceCount_CH2O(void)  //差值计算 CH2O
{
    //uint16_t u16LastData;
    //uint16_t u16Data;

    if (Dev.u16CH2OValue == 0x00)
    {
        ReportedData.u16LastDataCH2O = Dev.u16CH2OValue ;
        ReportedData.u16DataCH2O     = Dev.u16CH2OValue ;
        return OK;
    }
    else
    {
        ReportedData.u16LastDataCH2O = Dev.u16CH2OValue ;
    }

    if (ReportedData.u16LastDataCH2O != ReportedData.u16DataCH2O )
    {

        if ( ReportedData.u16DataCH2O  > ReportedData.u16LastDataCH2O )
        {
            ReportedData.u16CH2ODifferece = ReportedData.u16DataCH2O - ReportedData.u16LastDataCH2O;
        }
        else
        {
            ReportedData.u16CH2ODifferece = ReportedData.u16LastDataCH2O - ReportedData.u16DataCH2O;
        }
            
    }

    if (ReportedData.u16CH2ODifferece > DIFFERENCE_CH2O_LIMIT)
    {
        ReportedData.u16DataCH2O = ReportedData.u16LastDataCH2O;
        return OK;
    }
    
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t  DifferenceCount_CO2(void)  //差值计算 CO2
{
    //uint16_t u16LastData;
    //uint16_t u16Data;

    if (Dev.u16CO2Value == 0x00)
    {
        ReportedData.u16LastDataCO2 = Dev.u16CO2Value ;
        ReportedData.u16DataCO2     = Dev.u16CO2Value ;
        return OK;
    }
    else
    {
        ReportedData.u16LastDataCO2 = Dev.u16CO2Value ;
    }

    if (ReportedData.u16LastDataCO2 != ReportedData.u16DataCO2 )
    {
        if ( ReportedData.u16DataCO2  > ReportedData.u16LastDataCO2 )
        {
            ReportedData.u16CO2Differece = ReportedData.u16DataCO2 - ReportedData.u16LastDataCO2;
        }
        else
        {
            ReportedData.u16CO2Differece = ReportedData.u16LastDataCO2 - ReportedData.u16DataCO2;
        }
    }

    if (ReportedData.u16CO2Differece > DIFFERENCE_CO2_LIMIT)
    {
        ReportedData.u16DataCO2 = ReportedData.u16LastDataCO2;
        return OK;
    }
    
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t  DifferenceCount_T(void)  //差值计算 温度T
{
    //uint16_t u16LastData;
    //uint16_t u16Data;

    if (Dev.u16TemperatureValue == 0x00)
    {
        ReportedData.u16LastDataT = Dev.u16TemperatureValue ;
        ReportedData.u16DataT     = Dev.u16TemperatureValue ;
        return OK;
    }
    else
    {
        ReportedData.u16LastDataT = Dev.u16TemperatureValue ;
    }

    if (ReportedData.u16LastDataT != ReportedData.u16DataT )
    {
        if ( ReportedData.u16DataT  > ReportedData.u16LastDataT )
        {
            ReportedData.u16TemperatureDifferece = ReportedData.u16DataT - ReportedData.u16LastDataT;
        }
        else
        {
            ReportedData.u16TemperatureDifferece = ReportedData.u16LastDataT - ReportedData.u16DataT;
        }
    }

    if (ReportedData.u16TemperatureDifferece > DIFFERENCE_T_LIMIT)
    {
        ReportedData.u16DataT = ReportedData.u16LastDataT;
        return OK;
    }
    
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t  DifferenceCount_H(void)  //差值计算 湿度H
{
    //uint16_t u16LastData;
    //uint16_t u16Data;

    if (Dev.u16HumidityValue == 0x00)
    {
        ReportedData.u16LastDataH = Dev.u16HumidityValue ;
        ReportedData.u16DataH     = Dev.u16HumidityValue ;
        return OK;
    }
    else
    {
        ReportedData.u16LastDataH = Dev.u16HumidityValue ;
    }

    if (ReportedData.u16LastDataH != ReportedData.u16DataH )
    {
        if ( ReportedData.u16DataH  > ReportedData.u16LastDataH )
        {
            ReportedData.u16HumidityDifferece = ReportedData.u16DataH - ReportedData.u16LastDataH;
        }
        else
        {
            ReportedData.u16HumidityDifferece = ReportedData.u16LastDataH - ReportedData.u16DataH;
        }
    }

    if (ReportedData.u16HumidityDifferece > DIFFERENCE_H_LIMIT)
    {
        ReportedData.u16DataH = ReportedData.u16LastDataH;
        return OK;
    }
    
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t  DifferenceCount_PM10(void)  //差值计算  PM10
{
    //uint16_t u16LastData;
    //uint16_t u16Data;

    if (Dev.u16PM1Value == 0x00)
    {
        ReportedData.u16LastDataPM10 = Dev.u16PM1Value ;
        ReportedData.u16DataPM10     = Dev.u16PM1Value ;
        return OK;
    }
    else
    {
        ReportedData.u16LastDataPM10 = Dev.u16PM1Value ;
    }

    if (ReportedData.u16LastDataPM10 != ReportedData.u16DataPM10 )
    {
        if ( ReportedData.u16DataPM10  > ReportedData.u16LastDataPM10 )
        {
            ReportedData.u16PM10Differece = ReportedData.u16DataPM10 - ReportedData.u16LastDataPM10;
        }
        else
        {
            ReportedData.u16PM10Differece = ReportedData.u16LastDataPM10 - ReportedData.u16DataPM10;
        }
    }

    if (ReportedData.u16PM10Differece > DIFFERENCE_PM10_LIMIT)
    {
        ReportedData.u16DataPM10 = ReportedData.u16LastDataPM10;
        return OK;
    }
    
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t  DifferenceCount_PM25(void)  //差值计算  PM25
{
    //uint16_t u16LastData;
    //uint16_t u16Data;

    if (Dev.u16PM25Value == 0x00)
    {
        ReportedData.u16LastDataPM25 = Dev.u16PM25Value ;
        ReportedData.u16DataPM25     = Dev.u16PM25Value ;
        return OK;
    }
    else
    {
        ReportedData.u16LastDataPM25 = Dev.u16PM25Value ;
    }

    if (ReportedData.u16LastDataPM25 != ReportedData.u16DataPM25 )
    {
        if ( ReportedData.u16DataPM25  > ReportedData.u16LastDataPM25 )
        {
            ReportedData.u16PM25Differece = ReportedData.u16DataPM25 - ReportedData.u16LastDataPM25;
        }
        else
        {
            ReportedData.u16PM25Differece = ReportedData.u16LastDataPM25 - ReportedData.u16DataPM25;
        }
    }

    if (ReportedData.u16PM25Differece > DIFFERENCE_PM25_LIMIT)
    {
        ReportedData.u16DataPM25 = ReportedData.u16LastDataPM25;
        return OK;
    }
    
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t  DifferenceCount_PM100(void)  //差值计算  PM100
{
    //uint16_t u16LastData;
    //uint16_t u16Data;

    if (Dev.u16PM100Value == 0x00)
    {
        ReportedData.u16LastDataPM100 = Dev.u16PM100Value ;
        ReportedData.u16DataPM100     = Dev.u16PM100Value ;
        return OK;
    }
    else
    {
        ReportedData.u16LastDataPM100 = Dev.u16PM100Value ;
    }

    if (ReportedData.u16LastDataPM100 != ReportedData.u16DataPM100 )
    {
        if ( ReportedData.u16DataPM100  > ReportedData.u16LastDataPM100 )
        {
            ReportedData.u16PM100Differece = ReportedData.u16DataPM100 - ReportedData.u16LastDataPM100;
        }
        else
        {
            ReportedData.u16PM100Differece = ReportedData.u16LastDataPM100 - ReportedData.u16DataPM100;
        }
    }

    if (ReportedData.u16PM100Differece > DIFFERENCE_PM100_LIMIT)
    {
        ReportedData.u16DataPM100 = ReportedData.u16LastDataPM100;
        return OK;
    }
    
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void DifferenceCount(void)  //差值计算  
{
    DifferenceCount_CH2O();
    DifferenceCount_CO2();
    DifferenceCount_H();
    DifferenceCount_T();
    DifferenceCount_PM10();
    DifferenceCount_PM25();
    DifferenceCount_PM100();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SensorProactiveReporting(void) 
{
    ReportedData.u16CalibrationCH2O  =  Dev.Cfg.u16CalibrationCH2O ;
    ReportedData.u16CalibrationCO2   =  Dev.Cfg.u16CalibrationCO2  ;
    ReportedData.u16CalibrationH     =  Dev.Cfg.u16CalibrationH    ;
    ReportedData.u16CalibrationT     =  Dev.Cfg.u16CalibrationT    ;
    ReportedData.u16CalibrationPM10  =  Dev.Cfg.u16CalibrationPM10 ;
    ReportedData.u16CalibrationPM25  =  Dev.Cfg.u16CalibrationPM25 ;
    ReportedData.u16CalibrationPM100 =  Dev.Cfg.u16CalibrationPM100;

    SensorDataCalibration();     
    DifferenceCount();

    if (ReportedData.u16CH2ODifferece > DIFFERENCE_CH2O_LIMIT)
    {  
        ReportedData.u16CH2OSendWait = 100;
        ReportedData.u16CH2ODifferece = 0;
        ReportedData.u8DifferenceReportFlagCH2O = 1;
        ReportedData.eRunStateDifference = eENOCEAN_DIFFERENCESEND_CH2O;
    }
    if (ReportedData.u16CO2Differece > DIFFERENCE_CO2_LIMIT)
    {
        ReportedData.u16CO2SendWait = 100;
        ReportedData.u16CO2Differece = 0;
        ReportedData.u8DifferenceReportFlagCO2 = 1;
        ReportedData.eRunStateDifference = eENOCEAN_DIFFERENCESEND_CO2;
    }
    if (ReportedData.u16HumidityDifferece > DIFFERENCE_H_LIMIT)
    {
        ReportedData.u16HSendWait = 100;
        ReportedData.u16HumidityDifferece = 0;
        ReportedData.u8DifferenceReportFlagH = 1;
        ReportedData.eRunStateDifference = eENOCEAN_DIFFERENCESEND_H;
    }
    if (ReportedData.u16TemperatureDifferece > DIFFERENCE_T_LIMIT)
    {
        ReportedData.u16TSendWait = 100;
        ReportedData.u16TemperatureDifferece = 0;
        ReportedData.u8DifferenceReportFlagT = 1;
        ReportedData.eRunStateDifference = eENOCEAN_DIFFERENCESEND_T;
    }
    if (ReportedData.u16PM100Differece > DIFFERENCE_PM100_LIMIT)
    {
        ReportedData.u16PM25SendWait = 100;
        ReportedData.u16PM100Differece = 0;
        ReportedData.u8DifferenceReportFlagPM100 = 1;
        ReportedData.eRunStateDifference = eENOCEAN_DIFFERENCESEND_PM100;
    }
    if (ReportedData.u16PM25Differece > DIFFERENCE_PM25_LIMIT)
    {
        ReportedData.u16PM25SendWait = 100;
        ReportedData.u16PM25Differece = 0;
        ReportedData.u8DifferenceReportFlagPM25 = 1;
        ReportedData.eRunStateDifference = eENOCEAN_DIFFERENCESEND_PM25;
    }
    if (ReportedData.u16PM10Differece > DIFFERENCE_PM10_LIMIT)
    {
        ReportedData.u16PM25SendWait = 100;
        ReportedData.u16PM10Differece = 0;
        ReportedData.u8DifferenceReportFlagPM10 = 1;
        ReportedData.eRunStateDifference = eENOCEAN_DIFFERENCESEND_PM10;
    }
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void EnOceanProactiveReporting(ReportedData_Typedef *pReportedData)  //Enocean主动上报
{


    switch (pReportedData->eRunStateProactive)
    {
    case eENOCEAN_PROACTIVESEND_IDLE:

        if (pReportedData->u8BootReportFlag != 1)
        {
            pReportedData->u32BootReportCount++;
        }          
        if (pReportedData->u32BootReportCount<50)
        {
            pReportedData->u32ReadWait = 5*1000;
        }
        else
        {
            pReportedData->u8BootReportFlag = 1;
            pReportedData->u32ReadWait = RandomReport_Time(); //随机时间
        }
        
        if (pReportedData->u32RandomNumberSeed>(900*1000))
        {
            pReportedData->u32RandomNumberSeed = 0;   //清零随机数种子
        }

        pReportedData->eRunStateProactive = eENOCEAN_PROACTIVESEND_WAIT;
        break;

    case eENOCEAN_PROACTIVESEND_WAIT: //等待

        if (pReportedData->u32ReadWait != 0)
        {
            break;
        }
        pReportedData->eRunStateProactive   = eENOCEAN_PROACTIVESEND_CO2;
        pReportedData->u32ReadWait = u32SendTimeInterval; //等待2s
        break;

    case eENOCEAN_PROACTIVESEND_CO2:

        if (pReportedData->u32ReadWait != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_CO2_VALUE);
        pReportedData->eRunStateProactive     = eENOCEAN_PROACTIVESEND_CH2O;
        pReportedData->u16ReadPeriod = u32SendTimeInterval; //等待1s
        break;

    case eENOCEAN_PROACTIVESEND_CH2O:

        if (pReportedData->u16ReadPeriod != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_CH2O_VALUE);
        pReportedData->eRunStateProactive = eENOCEAN_PROACTIVESEND_H;
        pReportedData->u16ReadPeriod = u32SendTimeInterval; //等待1s
        break;

    case eENOCEAN_PROACTIVESEND_H:

        if (pReportedData->u16ReadPeriod != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_HUMIDITY_VALUE);
        pReportedData->eRunStateProactive     = eENOCEAN_PROACTIVESEND_T;
        pReportedData->u16ReadPeriod = u32SendTimeInterval; //等待1s
        break;

    case eENOCEAN_PROACTIVESEND_T:

        if (pReportedData->u16ReadPeriod != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_TEMPERATURE_VALUE);
        pReportedData->eRunStateProactive     = eENOCEAN_PROACTIVESEND_PM10;
        pReportedData->u16ReadPeriod = u32SendTimeInterval; //等待1s
        break;

    case eENOCEAN_PROACTIVESEND_PM10:

        if (pReportedData->u16ReadPeriod != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_PM1_VALUE);
        pReportedData->eRunStateProactive     = eENOCEAN_PROACTIVESEND_PM25;
        pReportedData->u16ReadPeriod = u32SendTimeInterval; //等待1s
        break;

    case eENOCEAN_PROACTIVESEND_PM25:

        if (pReportedData->u16ReadPeriod != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_PM25_VALUE);
        pReportedData->eRunStateProactive = eENOCEAN_PROACTIVESEND_PM100;
        pReportedData->u16ReadPeriod = u32SendTimeInterval; //等待1s
        break;

    case eENOCEAN_PROACTIVESEND_PM100:

        if (pReportedData->u16ReadPeriod != 0)
        {
            break;
        }
        EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_PM10_VALUE);
        pReportedData->eRunStateProactive = eENOCEAN_PROACTIVESEND_IDLE;
        pReportedData->u16ReadPeriod = u32SendTimeInterval; //等待1s
        break;

    default:
        pReportedData->eRunStateProactive = eENOCEAN_PROACTIVESEND_IDLE;
        break;
    }
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void EnOceanDifferenceReport(ReportedData_Typedef *pReportedData)  //Enocean差值上报
{
    
    Air_Quality_Grade(pReportedData);
    FaultHandling();
    SensorProactiveReporting();
    
    if (pReportedData->eRunStateProactive > eENOCEAN_PROACTIVESEND_WAIT )
    {
        pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
    }

    switch (pReportedData->eRunStateDifference)
    {
    case eENOCEAN_DIFFERENCESEND_IDLE:

        pReportedData->u32DifferenceSendWait = 1000; 
        pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
        break;

    case eENOCEAN_DIFFERENCESEND_WAIT: //等待

        if (pReportedData->u32DifferenceSendWait != 0)
        {
            break;
        }
        pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
        pReportedData->u32DifferenceSendWait = u32SendTimeInterval; //等待2s
        break;

    case Enocean_Send_FaultCode: //故障上报

        if (pReportedData->u8ProactiveReportFlagErr == 1)
        {
            if (Dev.u16DebiceFault != 0)
            {
                EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_DEVICE_FAULT);
            }
            if (Dev.u16CommunicationFault != 0)
            {
                EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_COMMUNICATION_FAULT);
            }

            pReportedData->u8ProactiveReportFlagErr = 0;
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            break;
        }

    case eENOCEAN_DIFFERENCESEND_CO2:

        if (pReportedData->u8DifferenceReportFlagCO2 == 1)
        {
            if (pReportedData->u16CO2SendWait != 0)
            {
                break;
            }
            pReportedData->u8DifferenceReportFlagCO2 = 0;
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_CO2_VALUE);
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            break;
        }

    case eENOCEAN_DIFFERENCESEND_CH2O:

        if (pReportedData->u8DifferenceReportFlagCH2O == 1)
        {
            if (pReportedData->u16CH2OSendWait != 0)
            {
                break;
            }
            pReportedData->u8DifferenceReportFlagCH2O = 0;
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_CH2O_VALUE);
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            //pReportedData->u32ReadWait = u32SendTimeInterval; //等待1s
            break;
        }

    case eENOCEAN_DIFFERENCESEND_H:

        if (pReportedData->u8DifferenceReportFlagH == 1)
        {
            if (pReportedData->u16HSendWait != 0)
            {
                break;
            }
            pReportedData->u8DifferenceReportFlagH = 0;
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_HUMIDITY_VALUE);
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            //pReportedData->u32ReadWait = u32SendTimeInterval; //等待1s
             break;
        }

    case eENOCEAN_DIFFERENCESEND_T:

        if (pReportedData->u8DifferenceReportFlagT == 1)
        {
            if (pReportedData->u16TSendWait != 0)
            {
                break;
            }
            pReportedData->u8DifferenceReportFlagT = 0;
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_TEMPERATURE_VALUE);
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            break;
        }

    case eENOCEAN_DIFFERENCESEND_PM10:

        if (pReportedData->u8DifferenceReportFlagPM10 == 1)
        {
            if (pReportedData->u16PM25SendWait != 0 )
            {
                break;
            }
            pReportedData->u8DifferenceReportFlagPM10 = 0;
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_PM1_VALUE);
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            break;
        }

    case eENOCEAN_DIFFERENCESEND_PM25:

        if (pReportedData->u8DifferenceReportFlagPM25 == 1)
        {
            if (pReportedData->u16PM25SendWait != 0)
            {
                break;
            }
            pReportedData->u8DifferenceReportFlagPM25 = 0;
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_PM25_VALUE);
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            break;
        }

    case eENOCEAN_DIFFERENCESEND_PM100:

        if (pReportedData->u8DifferenceReportFlagPM100 == 1)
        {
            if (pReportedData->u16PM25SendWait != 0)
            {
                break;
            }
            pReportedData->u8DifferenceReportFlagPM100 = 0;
            EnOceanMSCSend(&Radio, &Dev, 0x01, MB_INPUT_PM10_VALUE);
            pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
            break;
        }

    default:
        pReportedData->eRunStateDifference = eENOCEAN_DIFFERENCESEND_WAIT;
        break;
    }
}

