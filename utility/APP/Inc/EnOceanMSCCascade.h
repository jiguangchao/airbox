


#ifndef _ENOCEAN_MSC_CASCADE_H_
#define _ENOCEAN_MSC_CASCADE_H_

typedef enum
{
    eMSC_CMD_DEV_SYS  = 0x00,
    eMSC_CMD_WRITE    = 0x01,
    eMSC_CMD_READ     = 0x02,
    eMSC_CMD_RESPONSE = 0x03,

}eMSC_CMD_TYPE;



/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCGetChannelAndRegPermission(uint8_t u8Cmd,uint8_t u8Channel,uint8_t u8RegIndex, uint32_t u32Data);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCReadSettings2SendQueue(uint8_t u8Cmd,uint8_t u8ReadChannel, uint8_t u8Register);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteSettings(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteSettingsByBaseID(Radio_Typedef *pRadio,uint8_t u8BuffChannel);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCMasterWriteSettingsByBaseID(Radio_Typedef *pRadio,uint8_t u8BaseOffset);

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteDevtings(uint8_t u8RegID,uint32_t u32Data,Dev_Typedef *pDev);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCResponseDevtings(uint8_t *p8Data,Dev_Typedef *pDev);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCResponse(Radio_Typedef *pRadio, Dev_Typedef *pDev);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWrite(Radio_Typedef *pRadio, Dev_Typedef *pDev);
/**
  * @brief
  * @param
  * @retval None
  */

void EnOceanMSCSend(Radio_Typedef *pRadio, Dev_Typedef *pDev,uint8_t u8RegH,uint8_t u8RegL);

#endif
