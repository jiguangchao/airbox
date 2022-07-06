/*******************************************************************
*
*    DESCRIPTION:
*
*    AUTHOR:
*
*    HISTORY:
*
*    DATE:
*
*******************************************************************/

#include ".\BSP_Include.h"


#define PAGE_WORD_HEADER          (0xAA5555AA)


/*2K ROM */
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
  * @brief  Erases a specified page in program memory.
  * @param  PageAddress The page address in program memory to be erased.
  * @note   A Page is erased in the Program memory only if the address to load 
  *         is the start address of a page (multiple of @ref FLASH_PAGE_SIZE bytes).
  * @retval None
  */
void NVM_FLASH_PageErase(uint32_t PageAddress)
{
    //HAL_StatusTypeDef status;
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR);
    while (HAL_OK != HAL_FLASH_Unlock() )
    {
        ;
    }
    //status = FLASH_WaitForLastOperation(1000); //1s timeout
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR);
    while (FLASH_WaitForLastOperation(1000) != HAL_OK)
    {
        ;
    }
    FLASH_PageErase(FLASH_BANK_1, (PageAddress-FLASH_BASE)/CHIP_FLASH_PAGE_BYTES_SIZE);
    //status = FLASH_WaitForLastOperation(1000);
    while (FLASH_WaitForLastOperation(1000) != HAL_OK)
    {
        ;
    }
    CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

    HAL_FLASH_Lock();
}
/**
 * @brief
 * @param
 * @retval None
 */
void NVM_FLASH_WriteNWords(uint32_t u32Address,uint32_t* pu32WrBuff,uint16_t u16NWords)
{
    uint16_t i;
    uint32_t u32PageFirstAddress ;
    
    if ( u16NWords%2 )
    {
        return;
    }
    if ( u32Address%4 )
    {
        return;
    }

    u32PageFirstAddress = u32Address - u32Address%CHIP_FLASH_PAGE_BYTES_SIZE;
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ECCC | FLASH_FLAG_ECCD);
    
    if ( ( u32Address%CHIP_FLASH_PAGE_BYTES_SIZE ) == 0 )
    {
        NVM_FLASH_PageErase(u32PageFirstAddress);
    }

    HAL_FLASH_Unlock();
    for(i = 0; i < u16NWords; )
    {                     
        if ( HAL_OK == HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, u32Address, (uint64_t)pu32WrBuff[i+1]<<32|(uint64_t)pu32WrBuff[i]) )
        {
            u32Address += 8;
            i          += 2;
        }
        
    }
    HAL_FLASH_Lock();
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
#if FLASH_DATA_USAGE > 0
    /**
     * @brief
     * @param
     * @retval None
     */
    void NVM_FLASH_WriteDataNWords(uint16_t u16PageNum,uint16_t u16FlashAreaSize,uint32_t *pu32Data,uint16_t u16Nums)
    {
        uint16_t  i;
        uint32_t u32DataCheck;
        uint32_t u32DataAddress;    
        uint16_t u16FlashNums;
        //uint16_t u16BlockMax;
        uint16_t u16BlockIndex;
        uint32_t u32DataHeader;

        u32DataCheck = 0;
        u16FlashNums   = u16Nums+2;
        /* Over buff size max */
        /* Over buff size flash area size */
        if ( u16FlashNums > u16FlashAreaSize/4 )
        {
            return;
        }
        //u16BlockMax     = u16FlashAreaSize/(u16FlashNums*4);

        u32DataHeader = PAGE_WORD_HEADER;
        u32DataCheck = PAGE_WORD_HEADER;
        for (i = 0; i < u16Nums; i++)
        {
            u32DataCheck += pu32Data[i];
        }
        
        /******************************************************************/
        if ( OK == NVM_FLASH_ReadDataLastBlockId(u16PageNum,u16FlashAreaSize,&u16BlockIndex,u16Nums) )
        {
            
        }
        else
        {
            u16BlockIndex = 0;        
        }

        if ( 0 == u16BlockIndex )
        {
            /* Clear All */
            u32DataAddress = u16PageNum*CHIP_FLASH_PAGE_NEED_ERASE;
            i = 0;
            while (i < u16FlashAreaSize)
            {
                NVM_FLASH_PageErase(u32DataAddress);
                i              += CHIP_FLASH_PAGE_NEED_ERASE;
                u32DataAddress += CHIP_FLASH_PAGE_NEED_ERASE;
            }
        }
        /* Get the data current block's flash */
        u32DataAddress = u16BlockIndex*u16FlashNums*4 + u16PageNum*CHIP_FLASH_PAGE_NEED_ERASE;
            
        HAL_FLASH_Unlock();
        for(i = 0; i < u16FlashNums; i++)
        {
            if ( 0 == i)
            {            
                HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, u32DataAddress, u32DataHeader);
            }
            else if ( (u16FlashNums-1) == i)
            {            
                HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, u32DataAddress, u32DataCheck);
            }
            else
            {            
                HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, u32DataAddress, pu32Data[i-1]);
            }
            u32DataAddress += 4;
        }
        HAL_FLASH_Lock();
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    uint16_t NVM_FLASH_WriteDataBlockBlankCheck(uint32_t u32Address, uint16_t u16Nums)
    {
        uint16_t i;
        uint16_t j;
        uint32_t u32Data;
        
        i = 0;
        j = 0;
        while (i < u16Nums)
        {
            u32Data = *((volatile uint32_t *)(u32Address + i * 4));
            if (u32Data != 0xFFFFFFFF)
            {
                j++;
            }
            i++;
        }

        return j;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t NVM_FLASH_ReadDataLastBlockId(uint16_t u16PageNum,uint16_t u16FlashAreaSize,uint16_t *pu16ReadBlock, uint16_t u16Nums)
    {
        uint16_t  i;
        uint32_t u32DataCheck;   
        uint32_t u32DataAddress;
        uint16_t u16FlashNums;
        uint16_t u16BlockMax;
        uint16_t u16BlockIndex;
        uint32_t u32ReadCheck;
        uint32_t u32FirstHead;

        u32DataCheck = 0;
        u16FlashNums   = u16Nums+2;
        /* Over buff size max */
        /* Over buff size flash area size */
        if ( u16FlashNums > u16FlashAreaSize/4 )
        {
            return ~OK;
        }
        u16BlockMax     = u16FlashAreaSize/(u16FlashNums*4);
        u16BlockIndex   = u16BlockMax;
        /* Get the data current block's flash */
        //u32DataAddress = u16BlockIndex*u16FlashNums*4 + u16PageNum*DATA_PAGE_NEED_ERASE;

        while (u16BlockIndex)
        {   
            u32DataAddress = (u16BlockIndex-1)*u16FlashNums*4 + u16PageNum*CHIP_FLASH_PAGE_NEED_ERASE;

            u32DataCheck   = 0;
            for (i = 0; i < u16FlashNums-1; i++)
            {
                u32DataCheck += *((volatile uint32_t *)(u32DataAddress + i * 4));
            }
            
            u32FirstHead    = *((volatile uint32_t *)(u32DataAddress)); 
            u32DataAddress += (u16FlashNums-1)*4;
            u32ReadCheck   = *((volatile uint32_t *)(u32DataAddress));

            if ( ( PAGE_WORD_HEADER == u32FirstHead)&&( u32DataCheck == u32ReadCheck ) )
            {
                if ( (u16BlockIndex+1) > u16BlockMax )
                {
                    return ~OK;
                }
                //u16BlockIndex ++;
                u32DataAddress = u16BlockIndex*u16FlashNums*4 + u16PageNum*CHIP_FLASH_PAGE_NEED_ERASE;
                if ( 0 == NVM_FLASH_WriteDataBlockBlankCheck(u32DataAddress, u16FlashNums) )
                {                
                    if ( u16BlockIndex >= u16BlockMax )
                    {
                        return ~OK;
                    }
                    else
                    {
                        *pu16ReadBlock = u16BlockIndex;
                        return OK;
                    }
                    
                }    
                else
                {
                    return ~OK;
                }
            }
            
            u16BlockIndex--;
        }
        *pu16ReadBlock = 0;
        return ~OK;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t NVM_FLASH_ReadDataNWords(uint16_t u16PageNum,uint16_t u16FlashAreaSize, uint32_t *pu32Data,uint16_t u16Nums)
    {
    
        uint16_t  i;
        uint32_t u32DataCheck;   
        uint32_t u32DataAddress;
        uint16_t u16FlashNums;
        //uint16_t u16BlockMax;
        uint16_t u16BlockIndex;
        uint32_t u32ReadCheck;
        uint32_t u32FirstHead;

        u32DataCheck = 0;
        u16FlashNums   = u16Nums+2;
        /* Over buff size max */
        /* Over buff size flash area size */
        if ( u16FlashNums > u16FlashAreaSize/4 )
        {
            return ~OK;
        }
        u16BlockIndex   = u16FlashAreaSize/(u16FlashNums*4);
        
        /* Get the data current block's flash */
        //u32DataAddress = u16BlockIndex*u16FlashNums*4 + u16PageNum*DATA_PAGE_NEED_ERASE;

        while (u16BlockIndex)
        {
            u32DataAddress = (u16BlockIndex-1)*u16FlashNums*4 + u16PageNum*CHIP_FLASH_PAGE_NEED_ERASE;

            u32DataCheck   = 0;
            for (i = 0; i < u16FlashNums-1; i++)
            {
                u32DataCheck += *((volatile uint32_t *)(u32DataAddress + i * 4));
            }
            
            u32FirstHead    = *((volatile uint32_t *)(u32DataAddress)); 
            u32DataAddress += (u16FlashNums-1)*4;
            u32ReadCheck   = *((volatile uint32_t *)(u32DataAddress));

            if ( ( PAGE_WORD_HEADER == u32FirstHead)&&( u32DataCheck == u32ReadCheck ) )
            {
                u32DataAddress = (u16BlockIndex-1)*u16FlashNums*4 + u16PageNum*CHIP_FLASH_PAGE_NEED_ERASE;
                
                for (i = 1; i <= u16Nums; i++)
                {
                    pu32Data[i-1] = *((volatile uint32_t *)(u32DataAddress + i * 4));
                }
                return OK;
            }
            u16BlockIndex--;
        }
        
        return !OK;
    }
#endif

/* End of file */

