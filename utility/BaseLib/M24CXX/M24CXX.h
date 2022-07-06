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

#ifndef __M24CXX_H__
#define __M24CXX_H__

#include "..\..\MCU\platform.h"

typedef enum
{
	eM24CXX_CHIP_M24C01 = 0,
	eM24CXX_CHIP_M24C02 = 1,
	eM24CXX_CHIP_M24C04 = 2,
	eM24CXX_CHIP_M24C08 = 3,
	eM24CXX_CHIP_M24C16 = 4,
    eM24CXX_CHIP_M24C32 = 5,
    eM24CXX_CHIP_M24C64 = 6,
    eM24CXX_CHIP_M24C128 = 7,
    eM24CXX_CHIP_M24C256 = 8,
    
}eM24CXX_CHIP_TYPE;

typedef enum
{
	eM24C01_PAGE_NUMS = 8,
	eM24C02_PAGE_NUMS = 16,
	eM24C04_PAGE_NUMS = 32,
	eM24C08_PAGE_NUMS = 64,
	eM24C16_PAGE_NUMS = 128,
    eM24C32_PAGE_NUMS = 128,
    eM24C64_PAGE_NUMS = 256,
    eM24C128_PAGE_NUMS = 256,
    eM24C256_PAGE_NUMS = 512,
    
}eM24CXX_PAGE_MAX;

typedef enum
{
	eM24C01_PAGE_SIZE = 16,
	eM24C02_PAGE_SIZE = 16,
	eM24C04_PAGE_SIZE = 16,
	eM24C08_PAGE_SIZE = 16,
	eM24C16_PAGE_SIZE = 16,
    eM24C32_PAGE_SIZE = 32,
    eM24C64_PAGE_SIZE = 32,
    eM24C128_PAGE_SIZE = 64,
    eM24C256_PAGE_SIZE = 64,
	eM24C512_PAGE_SIZE = 128,
}eM24CXX_PAGE_SIZE;


typedef enum
{
	eM24C01_BYTES_SIZE = 128,
	eM24C02_BYTES_SIZE = 256,
	eM24C04_BYTES_SIZE = 512,
	eM24C08_BYTES_SIZE = 1024,
	eM24C16_BYTES_SIZE = 2048,
    eM24C32_BYTES_SIZE = 4096,
    eM24C64_BYTES_SIZE = 8192,
    eM24C128_BYTES_SIZE = 16384,
    eM24C256_BYTES_SIZE = 32768,
	eM24C512_BYTES_SIZE = 65536,
}eM24CXX_BYTES_SIZE;

typedef enum
{
    eM24CXX_OK = 0,
    eM24CXX_ERR_WRITE_CHIP_OK,
    eM24CXX_ERR_WRITE_PHY_NO_ACK,
    eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK,
    eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK,
    eM24CXX_ERR_WRITE_DATA_NO_ACK,
    eM24CXX_ERR_READ_DATA_WRITE_PHY_NO_ACK,

    eM24CXX_ERR_INPUT_PHY_ADDRESS,
    eM24CXX_ERR_INPUT_PAGE,
    
}eM24CXX_RETURN_TYPE;


typedef struct
{    
    //uint16_t u16ReadPeriod;
    //uint8_t  u8ReadWait;

    uint16_t u16Status;
    uint8_t  u8ErrorCount;
    uint8_t  u8Error;

    uint8_t  u8WritePageWait;
    
    uint8_t *p8Data;

    uint16_t u16DataLength;

    uint8_t  *p8Bytes;
    uint16_t u16NBytes; 
    uint16_t u16PageID;    
    uint16_t u16PageNums;

    uint8_t  u8ChipType;    
    uint8_t  u8PhyAddress;

    union
    {
        uint16_t u16DataAddress;
        uint8_t  u8DataAddress;    
    };

    I2C_BitbangDevice_t HWPort;

}EEPROM24CXX_Typedef;


/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXX_InitDataPoint(EEPROM24CXX_Typedef *pM24C);
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_WaitChipOK(void);
/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXX_1msNeedCall(void);
/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXX_WRInit(uint32_t u32DataAddress, uint8_t *pu8Data,uint16_t u16Nums);
/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXXClearAll(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t M24CXX_EEPROMWriteNBytes(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t M24CXX_EEPROMReadNBytes(void);
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_ReadBytes(void);
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_WriteBytes(void);


#endif
/* EOF */
