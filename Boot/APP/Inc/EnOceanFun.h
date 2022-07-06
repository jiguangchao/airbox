

#ifndef _ENOCEAN_CASCADE_H_
#define _ENOCEAN_CASCADE_H_



#include "EnOceanlibInclude.h"




    /**
      * @brief
      * @param
      * @retval None
      */
    void EnOceanHandler(uint8_t u8SendIntervalPeriodSet);
    /**
      * @brief  
      * @param
      * @retval None 
      */
    RM_RETURN_TYPE EnOceanReman(Radio_Typedef *pRadio);

/**
 * @brief
 * @param
 * @retval
 */
RM_RETURN_TYPE EnOceanRemanUpgradeLongDatas(Radio_Typedef *pRadio);
/**
 * @brief
 * @param
 * @retval
 */
void EnOceanRemanResetReply(uint8_t *p8ReceiveBuff,Radio_Typedef *pRadio,uint32_t u32DstID);

#endif

