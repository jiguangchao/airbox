
#ifndef _SHT20_H_
#define _SHT20_H_

#include "..\..\MCU\platform.h"

#define SHT20_PHY_ADDRESS_ID (0x40)

typedef enum
{
   SHT2X_HM_TRIG_TEMP_MEAS = 0xE3,   //command trig. temp meas. hold master
   SHT2X_HM_TRIG_HUMI_MEAS = 0xE5,   //command trig. humidity meas. hold master
   SHT2X_NOHM_TRIG_TEMP_MEAS = 0xF3, //command trig. temp meas. no hold master
   SHT2X_NOHM_TRIG_HUMI_MEAS = 0xF5, //command trig. humidity meas. no hold master
   SHT2X_W_USER_REG = 0xE6,          //command writing user register
   SHT2X_R_USER_REG = 0xE7,          //command reading user register
   SHT2X_SOFT_RESET = 0xFE           //command soft reset
} etSHT2XCommand;

typedef enum
{
   SHT2X_RES_12_14BIT = 0x00, //RH=12bit, T=14bit
   SHT2X_RES_8_12BIT = 0x01,  //RH=8bit,  T=12bit
   SHT2X_RES_10_13BIT = 0x80, //RH=10bit, T=13bit
   SHT2X_RES_11_11BIT = 0x81, //RH=11bit, T=11bit
   SHT2X_RES_MASK = 0x81,     //Mask for res. bits (7,0) in user reg.
} etSHT2XResolution;

typedef enum
{
   SHT2X_EOB_ON = 0x40,   //end of battery
   SHT2X_EOB_MASK = 0x40, //Mask for EOB bit(6) in user reg.
} etSHT2XEob;

typedef enum
{
   SHT2X_HEATER_ON = 0x04,   //heater on
   SHT2X_HEATER_OFF = 0x00,  //heater off
   SHT2X_HEATER_MASK = 0x04, //Mask for Heater bit(2) in user reg.
} etSHT2XHeater;

typedef enum
{
   SHT2X_I2C_ADR_W = 0x80, //sensor I2C address + write bit
   SHT2X_I2C_ADR_R = 0x81, //sensor I2C address + read bit
} etSHT2XI2cHeader;

#define SHT20_IIC_DEMOTEST (1)

typedef enum
{
   eSHT20_OK = 0,
   eSHT20_ERR_WRITE_PHY_NO_ACK,
   eSHT20_ERR_COMMAND_ADDRESS_H_NO_ACK,
   eSHT20_ERR_COMMAND_ADDRESS_L_NO_ACK,
   eSHT20_ERR_WRITE_DATA_NO_ACK,
   eSHT20_ERR_READ_DATA_WRITE_PHY_NO_ACK,

   eSHT20_ERR_INPUT_PHY_ADDRESS,
   eSHT20_ERR_INPUT_PAGE,
   eSHT20_ERR_DATA_CRC,
} eSHT20_RETURN_TYPE;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

typedef enum
{
   eSHT20_IDLE = 0x00,             //闲置状态
   eSHT20_PERIOD_WAIT = 0x01,      //周期等待
   eSHT20_INITIALIZE_STATE = 0x02, //初始化状态

   eSHT20_START_MEASUREMENT_T , //开始读数
   eSHT20_WAIT_MEASUREMENT_T ,  //等待读数
   eSHT20_READ_MEASUREMENT_T ,  //读数

   eSHT20_SWITCH_WAIT , //温度和湿度切换等待时间

   eSHT20_START_MEASUREMENT_H , //开始读数
   eSHT20_WAIT_MEASUREMENT_H ,  //等待读数
   eSHT20_READ_MEASUREMENT_H ,  //读数

   eSHT20_READ_END , //读数结束

} eSHT20State_TYPE;

typedef enum //故障码
{
   eSHT20_NORMAL = 0x00,            //传感器正常
   eSHT20_ABNORMAL_DATA = 0x01,     //数据异常
   eSHT20_EXCEPTION_MESSAGE = 0x02, //报文异常
   eSHT20_EQUIPMENT_DROPS = 0x03,   //设备掉线

} eSHT20_FaultCode;

//-----------------------------------------------------------------------------

typedef struct
{
   eSHT20State_TYPE eRunState;
   eSHT20_FaultCode eFaultCode;

   uint8_t u8SHT20DropsFlag;  //掉线标志
   uint8_t u8SHT20Dropscount; //掉线计数

   uint16_t u16TCalibration;   //温度校准值
   uint16_t u16HCalibration;   //湿度校准值

   uint32_t u32ReadCycle;     //读周期
   uint16_t u16ReadPeriod;
   uint16_t u16ReadWait;

   uint16_t u16Status;
   uint8_t u8ErrorCount;
   uint8_t u8Error;

   uint8_t u8HumidityValue;
   int16_t i16TemperatureOfDegreesCelsius;
   int16_t i16TemperatureOfFahrenheit;

   uint8_t *p8HData;
   uint8_t *p8TData;

   I2C_Bus_Typedef I2C;
   I2C_BitbangDevice_t HwPort;
} SHT20_Typedef;

//extern SHT20_Typedef   SHT20;

//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------------------------------------
//Task
//------------------------------------------------------------------------------
//Event
//------------------------------------------------------------------------------
//Status
//------------------------------------------------------------------------------
//Function
/**
   * @brief 
   * @param 
   * @retval 
   */
uint8_t SHT20_CheckSum_CRC8(SHT20_Typedef *pSHT20);
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT20_T_SetCommand(SHT20_Typedef *pSHT20); //温度转换
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT20_H_SetCommand(SHT20_Typedef *pSHT20); //湿度转换
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT20_T_ReadBytes(SHT20_Typedef *pSHT20); //读取温度
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT20_H_ReadBytes(SHT20_Typedef *pSHT20); //读取湿度
                                               /**
   * @brief 
   * @param 
   * @retval 
   */
float SHT20_Measure(char MeasureTorH, SHT20_Typedef *pSHT20);
/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT20_RETURN_TYPE SHT20_SetCommand(I2C_Bus_Typedef *pSHT20);
/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT20_RETURN_TYPE SHT20_ReadBytes(I2C_Bus_Typedef *pSHT20);
#if 0
/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT20_RETURN_TYPE SHT20_MeasurementCommandsSingleShotDataAcquisitionMode(I2C_Bus_Typedef *pSHT20);
#endif
/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT20_RETURN_TYPE SHT20_GetDataByBuff(SHT20_Typedef *pSHT20);
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT20_OperationTask(SHT20_Typedef *pSHT20,uint32_t ReadCycle);
/**
   * @brief
   * @param
   * @retval
   */
void SHT20_BusReset(SHT20_Typedef *pSHT20);
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT20_Tick10ms(SHT20_Typedef *pSHT20);
/**
   * @brief
   * @param
   * @retval
   */
void SHT20_Tick100us(SHT20_Typedef *pSHT20);

#endif

/* End of file */
