

#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_

/**
  * @brief  Erases a specified page in program memory.
  * @param  PageAddress The page address in program memory to be erased.
  * @note   A Page is erased in the Program memory only if the address to load 
  *         is the start address of a page (multiple of @ref FLASH_PAGE_SIZE bytes).
  * @retval None
  */
void NVM_FLASH_PageErase(uint32_t PageAddress);
/**
 * @brief
 * @param
 * @retval None
 */
void NVM_FLASH_WriteNWords(uint32_t u32Address,uint32_t* pu32WrBuff,uint16_t u16NWords);

#if FLASH_DATA_USAGE > 0
    /**
     * @brief
     * @param
     * @retval None
     */
    void NVM_FLASH_WriteDataNWords(uint16_t u16PageNum,uint16_t u16FlashAreaSize,uint32_t *pu32Data,uint16_t u16Nums);
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t NVM_FLASH_ReadDataLastBlockId(uint16_t u16PageNum,uint16_t u16FlashAreaSize,uint16_t *pu16ReadBlock, uint16_t u16Nums);
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t NVM_FLASH_ReadDataNWords(uint16_t u16PageNum,uint16_t u16FlashAreaSize, uint32_t *pu32Data,uint16_t u16Nums);
#endif




#endif
/* End of file */
