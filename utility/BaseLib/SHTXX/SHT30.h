

#ifndef _SHT30_H_
#define _SHT30_H_


#include "..\..\MCU\platform.h"

#define SHT30_PHY_ADDRESS_ID        (0x44)

typedef enum
{
   eSHT30_CMD_READ_SERIALNBR  = 0x3780, // read serial number
   eSHT30_CMD_READ_STATUS     = 0xF32D, // read status register
   eSHT30_CMD_CLEAR_STATUS    = 0x3041, // clear status register
                                       //
   eSHT30_CMD_HEATER_ENABLE   = 0x306D, // enabled heater
   eSHT30_CMD_HEATER_DISABLE  = 0x3066, // disable heater
   eSHT30_CMD_SOFT_RESET      = 0x30A2, // sofloat reset

   /* Readout of Measurement Results for Single Shot Mode */
   eSHT30_CMD_MEAS_CLOCKSTR_H = 0x2C06, // meas. clock stretching, high rep.
   eSHT30_CMD_MEAS_CLOCKSTR_M = 0x2C0D, // meas. clock stretching, medium rep.
   eSHT30_CMD_MEAS_CLOCKSTR_L = 0x2C10, // meas. clock stretching, low rep.
   eSHT30_CMD_MEAS_POLLING_H  = 0x2400, // meas. no clock stretching, high rep.
   eSHT30_CMD_MEAS_POLLING_M  = 0x240B, // meas. no clock stretching, medium rep.
   eSHT30_CMD_MEAS_POLLING_L  = 0x2416, // meas. no clock stretching, low rep.
   /* Measurement Commands for Periodic Data Acquisition Mode */
   eSHT30_CMD_MEAS_PERI_05_H  = 0x2032, // meas. periodic 0.5 mps, high rep.
   eSHT30_CMD_MEAS_PERI_05_M  = 0x2024, // meas. periodic 0.5 mps, medium rep.
   eSHT30_CMD_MEAS_PERI_05_L  = 0x202F, // meas. periodic 0.5 mps, low rep.
   eSHT30_CMD_MEAS_PERI_1_H   = 0x2130, // meas. periodic 1 mps, high rep.
   eSHT30_CMD_MEAS_PERI_1_M   = 0x2126, // meas. periodic 1 mps, medium rep.
   eSHT30_CMD_MEAS_PERI_1_L   = 0x212D, // meas. periodic 1 mps, low rep.
   eSHT30_CMD_MEAS_PERI_2_H   = 0x2236, // meas. periodic 2 mps, high rep.
   eSHT30_CMD_MEAS_PERI_2_M   = 0x2220, // meas. periodic 2 mps, medium rep.
   eSHT30_CMD_MEAS_PERI_2_L   = 0x222B, // meas. periodic 2 mps, low rep.
   eSHT30_CMD_MEAS_PERI_4_H   = 0x2334, // meas. periodic 4 mps, high rep.
   eSHT30_CMD_MEAS_PERI_4_M   = 0x2322, // meas. periodic 4 mps, medium rep.
   eSHT30_CMD_MEAS_PERI_4_L   = 0x2329, // meas. periodic 4 mps, low rep.
   eSHT30_CMD_MEAS_PERI_10_H  = 0x2737, // meas. periodic 10 mps, high rep.
   eSHT30_CMD_MEAS_PERI_10_M  = 0x2721, // meas. periodic 10 mps, medium rep.
   eSHT30_CMD_MEAS_PERI_10_L  = 0x272A, // meas. periodic 10 mps, low rep.

   eSHT30_CMD_FETCH_DATA      = 0xE000, // readout measurements for periodic mode
   eSHT30_CMD_R_AL_LIM_LS     = 0xE102, // read alert limits, low set
   eSHT30_CMD_R_AL_LIM_LC     = 0xE109, // read alert limits, low clear
   eSHT30_CMD_R_AL_LIM_HS     = 0xE11F, // read alert limits, high set
   eSHT30_CMD_R_AL_LIM_HC     = 0xE114, // read alert limits, high clear
   eSHT30_CMD_W_AL_LIM_LS     = 0x6100, // write alert limits, low set
   eSHT30_CMD_W_AL_LIM_LC     = 0x610B, // write alert limits, low clear
   eSHT30_CMD_W_AL_LIM_HS     = 0x611D, // write alert limits, high set
   eSHT30_CMD_W_AL_LIM_HC     = 0x6116, // write alert limits, high clear
   eSHT30_CMD_NO_SLEEP        = 0x303E,

   /* Break command / Stop Periodic Data Acquisition Mode */
   eSHT30_CMD_BREAK           = 0x3093,

}eSHT30_CMD_TYPE;


#define SHT30_IIC_DEMOTEST                     (1) 

typedef enum
{
   eSHT30_OK = 0,
   eSHT30_ERR_WRITE_PHY_NO_ACK,
   eSHT30_ERR_COMMAND_ADDRESS_H_NO_ACK,
   eSHT30_ERR_COMMAND_ADDRESS_L_NO_ACK,
   eSHT30_ERR_WRITE_DATA_NO_ACK,
   eSHT30_ERR_READ_DATA_WRITE_PHY_NO_ACK,

   eSHT30_ERR_INPUT_PHY_ADDRESS,
   eSHT30_ERR_INPUT_PAGE,
   eSHT30_ERR_DATA_CRC,
}eSHT30_RETURN_TYPE;



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*
typedef enum
{
    SHT30_Free              = 0x00,
    SHT30_StartReset        = 0x01,
    SHT30_Resetting         = 0x02,
    SHT30_StartMeasure      = 0x03,
    SHT30_Measuring         = 0x04,
    SHT30_MeasureComplete   = 0x05,
    
}SHT30RunStatus_Def;
*/
typedef enum
{
   SHT30_IDLE              = 0x00,
   SHT30_READ_STATUS       = 0x01,
   SHT30_CLEAR_STATUS      = 0x02,
   SHT30_RESET_READ_STATUS = 0x03,

   SHT30_START_MEASUREMENT = 0x10,
   SHT30_WAIT_MEASUREMENT  = 0x11,
   SHT30_READ_MEASUREMENT  = 0x12,

   SHT30_SELF_TEST_START_READ   = 0x20,
   SHT30_SELF_TEST_HEAT_ON      = 0x21,
   SHT30_SELF_TEST_WAIT         = 0x22,
   SHT30_SELF_TEST_HEAT_OFF     = 0x23,
   SHT30_SELF_TEST_STOP         = 0x24,

   SHT30_SW_RESET        = 0xF1,
   SHT30_INTERFACE_RESET   = 0xFF,

          
}eSHT30State_TYPE;

//-----------------------------------------------------------------------------

typedef struct
{    
   eSHT30State_TYPE    eRunState;

   uint16_t u16ReadPeriod;
   uint8_t  u8ReadWait;

   uint16_t u16Status;
   uint8_t  u8ErrorCount;
   uint8_t  u8Error;

   uint8_t  u8HumidityValue;
   int16_t  i16TemperatureOfDegreesCelsius;
   int16_t  i16TemperatureOfFahrenheit;

   uint8_t *p8Data;
   
   I2C_Bus_Typedef I2C;
   
}SHT30_Typedef;


//extern SHT30_Typedef   SHT30;

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
uint8_t Crc8_Calculate(uint8_t *prt,uint8_t length);
uint8_t Crc8Of31H_Calculate(uint8_t *prt,uint8_t length);


/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT30_RETURN_TYPE SHT30_SetCommand(I2C_Bus_Typedef *pSHT30);
/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT30_RETURN_TYPE SHT30_ReadBytes(I2C_Bus_Typedef *pSHT30);
#if 0
/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT30_RETURN_TYPE SHT30_MeasurementCommandsSingleShotDataAcquisitionMode(I2C_Bus_Typedef *pSHT30);
#endif
/**
   * @brief 
   * @param 
   * @retval 
   */
eSHT30_RETURN_TYPE SHT30_GetDataByBuff(SHT30_Typedef *pSHT30);
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT30_OperationTask(SHT30_Typedef *pSHT30,uint16_t u16ReadPeriodSet,uint8_t u8ReadWaitSet);
/**
   * @brief
   * @param
   * @retval
   */
void SHT30_BusReset(SHT30_Typedef *pSHT30);
/**
   * @brief 
   * @param 
   * @retval 
   */
void SHT30_Tick10ms(SHT30_Typedef *pSHT30);

#endif

/* End of file */
