#ifndef _ESP3_COMMON_H_
#define _ESP3_COMMON_H_

#ifdef MDK
    #pragma anon_unions
#endif

#include "esp3_libCommon.h"





/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CommonCommandWriteSleepTime(Esp3Tx_Typedef *pEsp3Tx, uint32_t u32SleepTime);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CommonCommandWriteReset(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadVersion(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadVersionRespone(uint8_t *u8ReceiveBuff, EnoceanTCM310_Typedef *pEnoceanTCM310);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadSysLog(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadSysLogRespone(uint8_t *u8ReceiveBuff);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteBist(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteBistRespone(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteBaseID(Esp3Tx_Typedef *pEsp3Tx, uint32_t u32BaseID);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadBaseID(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadBaseIDRespone(uint8_t* u8ReceiveBuff, EnoceanTCM310_Typedef *pEnoceanTCM310);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteReapter(Esp3Tx_Typedef *pEsp3Tx,  uint8_t u8ReapterLevel);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadReapter(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadReapterRespone(uint8_t* u8ReceiveBuff, EnoceanTCM310_Typedef *pEnoceanTCM310);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteSubTel(Esp3Tx_Typedef *pEsp3Tx, uint8_t u8SubTel);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterAdd(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterDel(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterDelAll(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterEnable(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadFliter(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadFliterRespone(uint8_t* u8ReceiveBuff, EnOceanFilter_Typedef *Filter);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteWaitMaturity(Esp3Tx_Typedef *pEsp3Tx, uint8_t u8MaturityEnable);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteMemory(Esp3Tx_Typedef *pEsp3Tx, EnoceanMemory_Typedef EnoceanMemory,uint16_t u16WriteBytes);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemory(Esp3Tx_Typedef *pEsp3Tx, EnoceanMemory_Typedef EnoceanMemory, uint16_t u16ReadBytes);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemoryRespone(uint8_t *u8ReceiveBuff, EnoceanMemory_Typedef *EnoceanMemory);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemoryAddress(Esp3Tx_Typedef *pEsp3Tx,  uint8_t u8MemoryArea);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemoryAddressRespone(uint8_t* u8ReceiveBuff,  EnoceanMemory_Typedef *EnoceanMemory);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CO_ReadDutyCycleLimit(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CommonCommandInitExit(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t ESP3_GetCommonCommand(uint8_t *u8Buff);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t ESP3_GetCommonCommandRespone(uint8_t u8Cmd, uint8_t *u8ReceiveBuff, EnoceanTCM310_Typedef* pEnoceanTCM310);
/******************************* remote mangement Start*************************************************/
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t ESP3_ReManData2SerialBuff(Radio_Typedef *pRadio,Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t ESP3_SerialBuff2RemanData(Radio_Typedef *pRadio,uint8_t *u8SerialBuff);
/******************************* remote mangement end *************************************************/
/**
  * @brief
  * @param
  * @retval None
*/
uint8_t ESP3_SerialBuffHeaderCheck(uint8_t *u8PrcBuff);
/**
  * @brief
  * @param
  * @retval None
*/
uint8_t ESP3_SerialBuff2Check(uint8_t *u8PrcBuff);
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t ESP3_SerialBuff2RadioData(Radio_Typedef *pReceiveRadio,uint8_t *u8SerialBuff);
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t ESP3_RadioSendData2SerialBuff(Radio_Typedef *pSendRadio);

/*!\}*/

/**
* @brief   
* @param
* @retval None
*/
uint8_t Esp3_SmartAckPraseRadioData(uint8_t* p8ReceiveBuff,Radio_Typedef *pRadio);
/**
  * @brief  Enables or disables learn mode of smart ack 
  *         controller
  * @param  
  * @retval None
  */    
uint8_t Esp3_SmartAckWriteLearnMode(Esp3Tx_Typedef *pEsp3Tx,uint32_t u32TimeOut,uint8_t u8Extend,uint8_t u8Enable);
/**
  * @brief  Reads the learnmode state of smart ack controller
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckReadLearnMode(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief  Send smart ack learn answer to modify mailbox at 
  *         postmaster 
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckWriteLearnConfirm(Esp3Tx_Typedef *pEsp3Tx,uint16_t u16ResponseTime,
                                                           uint8_t u8ConfirmCode,
                                                           uint32_t u32PostMasterCandidateID,
                                                           uint32_t u32SmartAckClientID);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckWriteReset(Esp3Tx_Typedef *pEsp3Tx,uint32_t u32ClientID);
/**
  * @brief  This function will only be used in a smart ack 
  *         client 
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckReadLearnedClients(Esp3Tx_Typedef *pEsp3Tx);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckWritePostMaster(Esp3Tx_Typedef *pEsp3Tx,uint8_t u8MailBoxCount);
/**
  * @brief  samrt reclaim not successful Receive
  * @param  
  * @retval None
  */
uint8_t EnOceanEvent2SmartAckData(Radio_Typedef *pRadio,uint8_t *p8SerialBuff);
/**
  * @brief  samrt reclaim not successful Receive
  * @param  
  * @retval None
  */
uint8_t Esp3_EventSmartAckResponse(Radio_Typedef *pRadio,Esp3Tx_Typedef *pEsp3Tx );
/**
  * @brief  samrt reclaim not successful Receive
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckReclaimNotSuccessful(uint8_t* p8ReceiveBuff);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckReclaimNotSuccessfulResponse(Esp3Tx_Typedef *pEsp3Tx,uint8_t u8ResponseStatus);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckConfirmLearn(uint8_t* p8ReceiveBuff,Radio_Typedef *pRadio);
/**
  * @brief  SmartAckConfirmLearn event response 
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckConfirmLearnResponse(Esp3Tx_Typedef *pEsp3Tx,uint16_t u16ResponseTime,
                                                                  uint8_t  u8ConfirmCode,
                                                                  uint8_t  u8ResponseStatus);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckLearnAck(uint8_t* p8ReceiveBuff,uint16_t *p16ResponseTime,uint8_t  *p8ConfirmCode);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckLearnAckResponse(Esp3Tx_Typedef *pEsp3Tx,uint8_t u8ResponseStatus);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckCoReady(uint8_t* p8ReceiveBuff,uint8_t  *p8ResetCode);
/**
  * @brief  
  * @param  
  * @retval None
  */
uint8_t Esp3_SmartAckSecureDevices(uint8_t* p8ReceiveBuff,uint8_t  *p8EventCause,uint32_t *p32DeviceID);


#endif
