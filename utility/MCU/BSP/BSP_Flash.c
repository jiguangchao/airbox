
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
#include "BSP_Flash.h"
#include "Dataconfigure.h"
#include "stm32g0xx_hal.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/

uint32_t FLASH_CFG_BUFF[64];
uint32_t FLASH_LOG_BUFF[64];

uint32_t FLASH_CFG_WRITE_BUFF[64];
uint32_t FLASH_CFG_READ_BUFF[64];
uint32_t FLASH_LOG_WRITE_BUFF[64];
uint32_t FLASH_LOG_READ_BUFF[64];
/* Private variables ---------------------------------------------------------*/

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void STMFLASH_Init(void)
{
    //uint8_t u8Flag;
    //uint32_t u32FlagReset[8];

}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_COPY(uint8_t *u8copyA,uint8_t *u8copyB,uint32_t u32Num)
{
    
    uint8_t i;
    for ( i = 0; i < u32Num; i++)
    {
        u8copyA[i] = u8copyB[i];
    }
    
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t FLASH_ReadWord(uint32_t faddr)
{
    return *(uint32_t *)faddr;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_ReadWord_8Bit(uint8_t faddr)
{
    return *(uint8_t *)faddr;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_Read_64Bit(uint32_t ReadAddr, uint64_t *u32pBuffer, uint32_t NumToRead) //连续读取
{
    uint32_t i;
    for (i = 0; i < NumToRead; i++)
    {
        u32pBuffer[i] = FLASH_ReadWord(ReadAddr); //读取4个字节.
        ReadAddr += 8;                            //偏移4个字节.
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_Read_32Bit(uint32_t ReadAddr, uint32_t *u32pBuffer, uint32_t NumToRead) //连续读取
{
    uint32_t i;
    for (i = 0; i < NumToRead; i++)
    {
        u32pBuffer[i] = FLASH_ReadWord(ReadAddr); //读取4个字节.
        ReadAddr += 4;                            //偏移4个字节.
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_Read_8Bit(uint32_t ReadAddr, uint8_t *pu8Buffer, uint32_t NumToRead) //连续读取
{
   FLASH_Read_32Bit(ReadAddr,(uint32_t*) pu8Buffer,NumToRead);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */

uint8_t FLASH_ReadNBytes(uint32_t u32ReadAddr, uint32_t *u32pBuffer, uint32_t NumToRead)
{

    uint32_t u32flashCrc;

    FLASH_Read_32Bit(u32ReadAddr, u32pBuffer, NumToRead + 1);
    u32flashCrc = FLASH_CRC32(u32pBuffer, NumToRead);
    if (u32flashCrc == u32pBuffer[NumToRead + 1])
    {
        //FLASH_COPY(pu8Buffer, FLASH_READ_BUFF, NumToRead);
        return OK;
    }
    return !OK;

    //return OK;
}

#if 0
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_Write_64Bit(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite)
{
    FLASH_EraseInitTypeDef FlashEraseInit;
    HAL_StatusTypeDef FlashStatus = HAL_OK;
    uint32_t PageError = 0;
    uint32_t addrx = 0;
    uint32_t endaddr = 0;
    /*
    if (WriteAddr < FLASH_PROG_NOT_EMPTY || WriteAddr % 4)
    {
        return; //非法地址
    }
    */

    HAL_FLASH_Unlock();                   //解锁
    addrx = WriteAddr;                    //写入的起始地址
    endaddr = WriteAddr + NumToWrite * 8; //写入的结束地址

    if (addrx < 0x1fff0000)
    {
        while (addrx < endaddr) //扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
        {
            if (FLASH_ReadWord(addrx) != 0XFFFFFFFF) //有非0XFFFFFFFF的地方,要擦除这个扇区
            {
                FlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES; //擦除类型，页擦除
                FlashEraseInit.Page = 63;                         //从哪页开始擦除
                FlashEraseInit.NbPages = 1;                       //一次只擦除一页
                if (HAL_FLASHEx_Erase(&FlashEraseInit, &PageError) != HAL_OK)
                {
                    break; //发生错误了
                }
            }
            else
                addrx += 4;
            FLASH_WaitForLastOperation(1000); //等待上次操作完成
        }
    }
    FlashStatus = FLASH_WaitForLastOperation(1000); //等待上次操作完成


    if (FlashStatus == HAL_OK)
    {
        while (WriteAddr < endaddr) //写数据
        {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WriteAddr, *(uint64_t *)pBuffer) != HAL_OK) //写入数据
            {
                break; //写入异常
            }
            WriteAddr += 8;
            pBuffer += 2;
        }
    }
    HAL_FLASH_Lock(); //上锁
}
#endif
/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
uint32_t GetPage(uint32_t Addr)
{
    return (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_Write_64Bit(uint32_t WriteAddr, uint64_t *pBuffer, uint32_t NumToWrite)
{

    uint32_t FirstPage = 0; 
    uint32_t NbOfPages = 0;
    uint32_t PageError = 0;
    uint32_t addrx = 0;
    uint32_t endaddr = 0;
    HAL_StatusTypeDef FlashStatus = HAL_OK;
    FLASH_EraseInitTypeDef EraseInitStruct = {0};

    addrx = WriteAddr;
    endaddr = WriteAddr + NumToWrite * (sizeof(uint64_t)/sizeof(uint8_t)); 

    HAL_FLASH_Unlock();

    /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

    if (FLASH_LOG_ADD == addrx || FLASH_CFG_ADD == addrx )
    {
        /* Get the 1st page to erase */
        FirstPage = GetPage(addrx);

        /* Get the number of pages to erase from 1st page */
        NbOfPages = GetPage(addrx) - FirstPage + 1;

        /* Fill EraseInit structure*/
        EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
        EraseInitStruct.Page = FirstPage;
        EraseInitStruct.NbPages = NbOfPages;

        /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
        if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
        {
            /*
      Error occurred while page erase.
      User can add here some code to deal with this error.
      PageError will contain the faulty page and then to know the code error on this page,
      user can call function 'HAL_FLASH_GetError()'
      */
            HAL_FLASH_GetError();
            return !OK;
        }
        FlashStatus = FLASH_WaitForLastOperation(1000); //等待上次操作完成
    }
    /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

    
    if (FlashStatus == HAL_OK)
    {
        while (addrx < endaddr)
        {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addrx, *(uint64_t *)pBuffer) == HAL_OK)
            {
                addrx = addrx + 8;
                pBuffer++; 
            }
            else
            {
                return !OK;
            }
        }
    }

    /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
    HAL_FLASH_Lock();

    return OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_Write_32Bit(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite)
{

    uint32_t FirstPage = 0; 
    uint32_t NbOfPages = 0;
    uint32_t PageError = 0;
    uint32_t addrx = 0;
    uint32_t endaddr = 0;
    uint32_t *u32pBuff;
    HAL_StatusTypeDef FlashStatus = HAL_OK;
    FLASH_EraseInitTypeDef EraseInitStruct = {0};

    u32pBuff = pBuffer;
    addrx = WriteAddr;
    endaddr = WriteAddr + NumToWrite * (sizeof(uint32_t)/sizeof(uint8_t)); 

    //Dev.Cfg.u16FlashWriteSuccessCount++;

    HAL_FLASH_Unlock();

    /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
    if (FLASH_LOG_ADD == addrx || FLASH_CFG_ADD == addrx )
    {
        /* Get the 1st page to erase */
        FirstPage = GetPage(addrx);

        /* Get the number of pages to erase from 1st page */
        NbOfPages = GetPage(addrx) - FirstPage + 1;

        /* Fill EraseInit structure*/
        EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
        EraseInitStruct.Banks =FLASH_BANK_1;						//操作BANK1
        EraseInitStruct.Page = FirstPage;
        EraseInitStruct.NbPages = NbOfPages;
        //EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;      //电压范围，VCC=2.7~3.6V之间!!


        /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
        if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
        {
            /*
      Error occurred while page erase.
      User can add here some code to deal with this error.
      PageError will contain the faulty page and then to know the code error on this page,
      user can call function 'HAL_FLASH_GetError()'
      */
            return !OK;
        }

        //SCB_CleanInvalidateDCache();   

        /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

        FLASH_WaitForLastOperation(1000); //等待上次操作完成

        //FLASH_WaitForLastOperation(FLASH_BANK_1);
    }

    FlashStatus = FLASH_WaitForLastOperation(5000); //等待上次操作完成

    //FLASH->CR = ((63 <<  FLASH_CR_PNB_Pos));

    //FLASH->WRP1AR = (62 << FLASH_WRP1AR_WRP1A_STRT);

    if (HAL_OK == FlashStatus  )
    {
        while (addrx < endaddr)
        {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, addrx, (uint64_t)u32pBuff) == HAL_OK)
            {
                addrx = addrx + 4;
                pBuffer++; 
            }
            else
            {
               // return !OK;
               break;
            }
        }
    }

    /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
    HAL_FLASH_Lock();

    return OK;
}
#if 0
static void FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRDPEndOffset)
{
  /* Check the parameters */
  assert_param(IS_OB_WRPAREA(WRPArea));
  assert_param(IS_FLASH_PAGE(WRPStartOffset));
  assert_param(IS_FLASH_PAGE(WRDPEndOffset));

  /* Configure the write protected area */
  if (WRPArea == OB_WRPAREA_ZONE_A)
  {
    FLASH->WRP1AR = ((WRDPEndOffset << FLASH_WRP1AR_WRP1A_END_Pos) | WRPStartOffset);
  }
#if defined(FLASH_DBANK_SUPPORT)
  else if (WRPArea == OB_WRPAREA_ZONE2_A)
  {
    FLASH->WRP2AR = ((WRDPEndOffset << FLASH_WRP2AR_WRP2A_END_Pos) | WRPStartOffset);
  }
  else if (WRPArea == OB_WRPAREA_ZONE2_B)
  {
    FLASH->WRP2BR = ((WRDPEndOffset << FLASH_WRP2BR_WRP2B_END_Pos) | WRPStartOffset);
  }
#endif
  else
  {
    FLASH->WRP1BR = ((WRDPEndOffset << FLASH_WRP1BR_WRP1B_END_Pos) | WRPStartOffset);
  }
}
#endif
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void FLASH_JustWrite_32Bit(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite) //只写入不擦除
{
    HAL_StatusTypeDef FlashStatus = HAL_OK;
    //FLASH_EraseInitTypeDef EraseInitStruct = {0};
    //FLASH_OBProgramInitTypeDef OBProgramInitStruct  = {0};

    uint32_t endaddr = 0;
    uint32_t addrx = 0;
    //uint32_t FirstPage = 0;
    //uint32_t NbOfPages = 0;


    /* Get the 1st page to erase */
    //FirstPage = GetPage(addrx);

    /* Get the number of pages to erase from 1st page */
    //NbOfPages = GetPage(addrx) - FirstPage + 1;
    /*
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Banks = FLASH_BANK_1; //操作BANK1
    EraseInitStruct.Page = FirstPage;
    EraseInitStruct.NbPages = NbOfPages;
    */   

    HAL_FLASH_Unlock(); //解锁


    addrx = WriteAddr;
    endaddr = WriteAddr + NumToWrite * (sizeof(uint32_t) / sizeof(uint8_t));

    //FLASH->CR = ((63 <<  FLASH_CR_PNB_Pos));
    //FLASH->WRP1AR = 0x3E;
    //FLASH_OB_WRPConfig( OB_WRPAREA_ZONE_A, 0x30,0x30);
    /*
    OBProgramInitStruct.WRPArea = OB_WRPAREA_ZONE_A;
    OBProgramInitStruct.WRPStartOffset = 0x30;
    OBProgramInitStruct.WRPEndOffset   = 0x00;
    HAL_FLASHEx_OBProgram(&OBProgramInitStruct);
    */

    while (WriteAddr < endaddr) //写数据
    {
        FlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, addrx, (uint64_t)pBuffer);

        if (FlashStatus == HAL_OK)
        {
            addrx = addrx + 4;
            pBuffer++;
        }
        else
        {
            // return ;
            break;
        }
    }
    
    HAL_FLASH_Lock(); //上锁
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_Remove_Page(uint32_t WriteAddr)
{
    uint32_t FirstPage = 0; 
    uint32_t NbOfPages = 0;
    uint32_t PageError = 0;
    uint32_t addrx ;
    //uint32_t endaddr;
    //uint32_t *u32pBuff;
    HAL_StatusTypeDef FlashStatus = HAL_OK;
    FLASH_EraseInitTypeDef EraseInitStruct = {0};

    //u32pBuff = pBuffer;
    addrx = WriteAddr;
    //endaddr = WriteAddr + NumToWrite * (sizeof(uint64_t)/sizeof(uint8_t)); 

    HAL_FLASH_Unlock();

    
    /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
    if (FLASH_LOG_ADD == addrx || FLASH_CFG_ADD == addrx )
    {
        /* Get the 1st page to erase */
        FirstPage = GetPage(addrx);

        /* Get the number of pages to erase from 1st page */
        NbOfPages = GetPage(addrx) - FirstPage + 1;

        /* Fill EraseInit structure*/
        EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
        EraseInitStruct.Page = FirstPage;
        EraseInitStruct.NbPages = NbOfPages;

        /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
        if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
        {
            /*
      Error occurred while page erase.
      User can add here some code to deal with this error.
      PageError will contain the faulty page and then to know the code error on this page,
      user can call function 'HAL_FLASH_GetError()'
      */
            //return !OK;
        }

        /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
    }
    FlashStatus = FLASH_WaitForLastOperation(1000); //等待上次操作完成

    if (FlashStatus == HAL_OK)
    {

    }
    HAL_FLASH_Lock();

    return OK;
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_Write_8Bit(uint32_t WriteAddr, uint8_t *u8pBuffer, uint32_t NumToWrite)
{

    if( OK == FLASH_Write_64Bit(WriteAddr,(uint64_t*) u8pBuffer,NumToWrite)) 
    {
        return OK;
    }
    return !OK;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t FLASH_WriyeNBytes(uint32_t WriteAddr, uint32_t *u32pBuffer, uint32_t NumToWrite)
{
   
    uint32_t u32FlashCrc;
    uint32_t u32NumWord;
    u32NumWord = NumToWrite+1;


    //FLASH_COPY(FLASH_WRITE_BUFF,u8pBuffer,NumToWrite);

    u32FlashCrc = FLASH_CRC32(u32pBuffer,NumToWrite);
    u32pBuffer[NumToWrite+1] = u32FlashCrc;
    

    if( OK == FLASH_Write_32Bit(WriteAddr,u32pBuffer,u32NumWord)) 
    {
        return OK;
    }
    return !OK;
    
   //return OK;
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint16_t FLASH_CRC16(uint8_t *DataBuf, uint16_t DataCnt)
{
    uint8_t i;
    uint16_t CRCValue = 0x00;

    for (i = 0; i < DataCnt; i++)
    {
        CRCValue += DataBuf[i];
    }

    return CRCValue;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t FLASH_CRC32(uint32_t *DataBuf, uint16_t DataCnt)
{
    uint8_t i;
    uint32_t CRCValue = 0;

    for (i = 0; i < DataCnt; i++)
    {
        CRCValue += DataBuf[i];
    }

    return CRCValue;
}


