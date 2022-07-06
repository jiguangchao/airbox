

#ifndef _ENOCEAN_CASCADE_H_
#define _ENOCEAN_CASCADE_H_



#include "EnOceanlibInclude.h"



/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanLearnSend(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanManualLearn(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadioMapChannel(uint8_t u8MapChannel,uint8_t *pu8IOChannel,uint8_t u8CascadeAdd);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadioMSC(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanLearnSensor(Radio_Typedef *pRadio,uint8_t u8LearnChannel, uint8_t u8LearnOutMode);


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




#endif

