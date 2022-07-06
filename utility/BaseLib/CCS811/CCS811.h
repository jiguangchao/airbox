/***************************************************************************
* Designed by Osman Li <Li.haimeng@menred.com> 
* Copyright , Menred Group Corporation.
* This software is owned by Menred Group and is protected by and subject to 
* worldwide patent protection (china and foreign)
 ***************************************************************************/
 /***************************************************************************
* Release Notes:
*     V1.1  
*         Data: 
*          
*     V1.0  
*         Data:2015.1.26
*         Official release
****************************************************************************/

#ifndef __CCS811_H__
#define __CCS811_H__

#include "..\..\MCU_platform\platform.h"

#define CCS811_IIC_DEMOTEST                     (0) 

typedef enum
{
    eCCS811_OK = 0,
    eCCS811_ERR_WRITE_PHY_NO_ACK,
    eCCS811_ERR_DATA_ADDRESS_H_NO_ACK,
    eCCS811_ERR_DATA_ADDRESS_L_NO_ACK,
    eCCS811_ERR_WRITE_DATA_NO_ACK,
    eCCS811_ERR_READ_DATA_WRITE_PHY_NO_ACK,

    eCCS811_ERR_INPUT_PHY_ADDRESS,
    eCCS811_ERR_INPUT_PAGE,
    
}eCCS811_RETURN_TYPE;

typedef enum
{
    /* R*/
    eCCS811_REG_STATUS = 0x00,
    eCCS811_REG_MEAS_MODE = 0x01,
    eCCS811_REG_ALG_RESULT_DATA = 0x02,
    eCCS811_REG_RAW_DATA = 0x03,
    eCCS811_REG_ENV_DATA = 0x05,
    eCCS811_REG_ENV_NTC = 0x06,
    eCCS811_REG_THRESHOLDS = 0x10,
    eCCS811_REG_BASELINE = 0x11,
    eCCS811_REG_HW_ID = 0x20,
    eCCS811_REG_FW_BOOT_VERSION = 0x23,
    eCCS811_REG_FW_APP_VERSION = 0x24,
    eCCS811_REG_ERROR_ID = 0xE0,
/*
    eCCS811_REG_APP_ERASE = 0xF1,
    eCCS811_REG_APP_DATA = 0xF2,
    eCCS811_REG_APP_VERIFY = 0xF3,
*/    
    eCCS811_REG_SW_RESET = 0xFF,

    eCCS811_REG_APP_START = 0xF4 ,
    

}eCCS811_REG_TYPE;

typedef enum
{
    eCCS811_IDLE              = 0x00,
    eCCS811_SW_RESET        ,
    eCCS811_READ_FW_BOOT_VERSION ,
    eCCS811_READ_FW_APP_VERSION ,
    eCCS811_READ_HW_ID             ,

    eCCS811_READ_STATUS       = 0x10,
    eCCS811_APP_START         ,
    eCCS811_APP_CHECK_STATUS,
    eCCS811_READ_ALG_RESULT_DATA,

    eCCS811_READ_MEAS_MODE    = 0x20,
    eCCS811_WRITE_MEAS_MODE   ,
    eCCS811_WRITE_MEAS_MODE_IDLE_WAIT,

    eCCS811_WRITE_ENV_DATA,
    eCCS811_WRITE_ENV_DATA_WAIT,

    eCCS811_ERROR_ID = 0x30,

    eCCS811_INTERFACE_RESET   = 0xFF,

    eCCS811_APP_ERASE = 0xF1,
    eCCS811_APP_DATA = 0xF2,
    eCCS811_APP_VERIFY = 0xF3,  
        
}eCCS811State_TYPE;

typedef union 
{
    struct
    {
        eCCS811State_TYPE eRunState;
        uint16_t  u16ReadPeriod;
        uint16_t  u16ReadWait;
        uint8_t  *p8Data;

        uint8_t  u8Status;
        uint8_t  u8MeasMode;
        uint16_t u16ECO2;
        uint16_t u16TVOC;
        uint16_t u16RawData;
        uint16_t u16EnvData;
        uint8_t  u8ErrorID;

        uint8_t  u16HWID;
        uint16_t u16HWVersion;
        uint16_t u16FWBootVersion;
        uint16_t u16FWAppVersion;
    };
    uint8_t u8Bytes[20];

}CCS811_Typedef;


/**
   * @brief 
   * @param 
   * @retval 
   */
eCCS811_RETURN_TYPE CCS811_WriteRegister(I2C_Bus_Typedef *pCCS811);
/**
   * @brief 
   * @param 
   * @retval 
   */
eCCS811_RETURN_TYPE CCS811_WriteRegisters(I2C_Bus_Typedef *pCCS811);
/**
   * @brief 
   * @param 
   * @retval 
   */
eCCS811_RETURN_TYPE CCS811_ReadRegisters(I2C_Bus_Typedef *pCCS811);
/**
   * @brief 
   * @param 
   * @retval 
   */
eCCS811_RETURN_TYPE CCS811_ReadAlgResultData();
/**
   * @brief 
   * @param 
   * @retval 
   */
void CCS811_Tick10ms(CCS811_Typedef *pCCS811);

/**
   * @brief 
   * @param 
   * @retval 
   */
void CCS811_OperationTask(CCS811_Typedef *pCCS811,uint16_t u16ReadPeriodSet,uint16_t u16ReadWaitSet);

#if CCS811_IIC_DEMOTEST > 0
/**
   * @brief 
   * @param 
   * @retval 
   */
void CCS811_Demo(void);
#endif

#endif
/* EOF */
