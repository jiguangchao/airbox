/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"

#define FLASH_USER_START_ADDR   (FLASH_BASE + (3 * FLASH_PAGE_SIZE))   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     (FLASH_BASE + FLASH_SIZE - 1)   /* End @ of user Flash area */

extern uint32_t FLASH_CFG_BUFF[64];
extern uint32_t FLASH_LOG_BUFF[64];

extern uint32_t FLASH_CFG_WRITE_BUFF[64];
extern uint32_t FLASH_CFG_READ_BUFF[64];
extern uint32_t FLASH_LOG_WRITE_BUFF[64];
extern uint32_t FLASH_LOG_READ_BUFF[64];
/*
#define FLASH_BUFF   (128)
uint8_t FLASH_RX_Buff[FLASH_BUFF];
*/
/*
#define  FLASH_START_ADDRESS      (0x08000000)    //起始地址
#define  FLASH_END_ADDRESS        (0x0801FFFF)    //结束地址
#define  FLASH_PAGE_BYTE          (0x7FF)         //每页字节数
*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void STMFLASH_Init(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_COPY(uint8_t *u8copyA,uint8_t *u8copyB,uint32_t u32Num);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t FLASH_ReadWord(uint32_t faddr);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_ReadWord_8Bit(uint8_t faddr);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_Read_32Bit(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead); //连续读取
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_Read_64Bit(uint32_t ReadAddr, uint64_t *u32pBuffer, uint32_t NumToRead); //连续读取
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_Read_8Bit(uint32_t ReadAddr, uint8_t *pu8Buffer, uint32_t NumToRead); //连续读取
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_ReadNBytes(uint32_t u32ReadAddr, uint32_t *u32pBuffer, uint32_t NumToRead);
/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
uint32_t GetPage(uint32_t Addr);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
//void FLASH_Write_64Bit(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);
uint8_t FLASH_Write_64Bit(uint32_t WriteAddr, uint64_t *pBuffer, uint32_t NumToWrite);

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_Write_32Bit(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */

uint8_t FLASH_Write_8Bit(uint32_t WriteAddr, uint8_t *u8pBuffer, uint32_t NumToWrite);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_WriyeNBytes(uint32_t WriteAddr, uint32_t *u32pBuffer, uint32_t NumToWrite);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint16_t FLASH_CRC16(uint8_t *DataBuf, uint16_t DataCnt);

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t FLASH_CRC32(uint32_t *DataBuf, uint16_t DataCnt);

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_Remove_Page(uint32_t WriteAddr);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_JustWrite_32Bit(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);   //只写入不擦除


#endif