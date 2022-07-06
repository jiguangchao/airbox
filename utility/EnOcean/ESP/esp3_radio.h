#ifndef  _ESP3_RADIO_H_
#define  _ESP3_RADIO_H_

#include "esp3_libCommon.h"

#define ENOCEAN_GET_WRONG_CHIPID_ERROR                 (0x01)
#define ENOCEAN_GET_WRONG_BASEID_ERROR                 (0x02)
#define ENOCEAN_CAN_NOT_GET_ID_ERROR                   (0x04)

typedef enum//根据应用而来 --- 2018-3-6
{
    eQUEUE_IDLE = 0,            //无线发送队列空闲
    eQUEUE_TEST_TELEGRAM,       // 
    eQUEUE_LEARN_ID_TAB ,       //循环发送数据列表
/*
    eQUEUE_SEND_LEARN_EEP_INFO, //学习报文
    eQUEUE_EEP_D201XX_CMD_04,   //发送单个通道状态
    eQUEUE_EEP_D201XX_CMD_0D,   //通道设定    
    eQUEUE_EEP_D201XX_CMD_0F02, //   
    eQUEUE_EEP_F60201,          // 

    eQUEUE_DEV_MSC_RESPONSE,    //
    eQUEUE_DEV_BASE_ID_TAB ,    //循环发送数据列表
*/   
    eQUEUE_MODIFY_REAPTER,      //修改TCM310中继参数
    eQUEUE_READ_REAPTER,        //读TCM310中继参数
    eQUEUE_TCM310_READ_BASEID,  //
    eQUEUE_TCM310_WRITE_BASEID, //

//    eQUEUE_PANNEL_HOST_PLUG, //

//    eQUEUE_COMMON_CMD, //

    eQUEUE_REMAN_TELEGRAM, //

    eQUEUE_RADIO_TELEGRAM, //
/***********  smart ack ********************************/ 
    eQUEUE_SMARTACK_POST_MASTER_ON,
    eQUEUE_SMARTACK_POST_MASTER_OFF,
    eQUEUE_SMARTACK_WR_LRN_CONFIRM,
    eQUEUE_SMARTACK_EVENT_LRN_RESPONSE,
    eQUEUE_SMARTACK_WR_LRN_MODE_ON,
    eQUEUE_SMARTACK_WR_LRN_MODE_OFF,
    eQUEUE_SMARTACK_ANS_RECLAIM_DATA,
    eQUEUE_SMARTACK_CONFIRM_LEARN_RESPONSE, 
    //eQUEUE_SMARTACK_LRN_OUT_DEL_MAIL_BOX,
    eQUEUE_SMARTACK_REPLY_MESSAGE,  
/******************************************************/
    //eQUEUE_AIRCONDITION,
    //eQUEUE_FLOORHEATING,
    //eQUEUE_VENTILATION,
/******************************************************/

}eEnOceanRUN_TYPE;



//extern   EnOceanHw_Typedef      EnOceanHardware;
extern   EnOceanRun_Typedef     EnOceanRun;



/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanRPSRadioData(Radio_Typedef *pRadio,uint8_t u8Status,uint32_t u32SrcID,uint32_t u32DstID);
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOcean4BSRadioData(Radio_Typedef *pRadio,uint8_t u8Status,uint32_t u32SrcID,uint32_t u32DstID);
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOcean1BSRadioData(Radio_Typedef *pRadio,uint8_t u8Status,uint32_t u32SrcID,uint32_t u32DstID);
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanVLDRadioData(Radio_Typedef *pRadio,uint8_t u8Bytes,uint32_t u32SrcID,uint32_t u32DstID);
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanMSCRadioData(Radio_Typedef *pRadio,uint8_t u8Bytes,uint32_t u32SrcID,uint32_t u32DstID);
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanUTERadioData(Radio_Typedef *pRadio,uint32_t u32SrcID);
/************************** Remote mangement start *****************************************/
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanReManData2SerialBuff(Radio_Typedef *pRadio,uint8_t u8RandomEn);
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanReManDataTest(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanTime_100us(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanTime_1ms(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanTime_100ms(void);
/**
  * @brief
  * @param
  * @retval None
*/
void EnOceanWriteRepeater(void);
/**
  * @brief
  * @param
  * @retval None
*/
void EnOceanReadRepeater(void);
/**
  * @brief  push UTE learn EEP to queue
  * @param  u32EEP       : dev's eep
  *         
  * @retval None
  */
void EnOceanManualLearnSendUTEInfo(uint32_t u32EEP,uint8_t u8BaseID);


/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_PushData2Queue(eEnOceanRUN_TYPE eCmd,Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ClearSendQueuePopID(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetSendQueuePopID(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetSendQueueFull(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetSendQueuePushID(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_GetSendQueuePopData(Radio_Typedef *pRadioData);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_SetSendQueueIDOccupy(void);

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ClearReceiveQueuePopID(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_SetReceiveQueueIDOccupy(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanPopQueueSendData(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanESP3ReceivePacketParse(Radio_Typedef *pRadio,PACKET_TYPE eType);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetReceiveQueuePushID(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ReceiveUsartDMAPushQueue(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ReceiveUsartDataPushQueue(uint8_t u8RegData);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_SendOK(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetBusyState(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanESP3SendStateProcess(void);

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSendReady(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanSetSendPeriod(uint16_t u16SendPeriod) ;

/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_InitGetInfo(Radio_Typedef *pRadio);
#endif

