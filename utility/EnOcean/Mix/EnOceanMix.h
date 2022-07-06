

#ifndef _ENOCEAN_MIX_H_
#define _ENOCEAN_MIX_H_



#include "esp3_libCommon.h"
#include "EnOceanLearn.h"
//#include "..\EEP/EEP_D201XX.h"
#define PIR_MODE_MAX                (1)
#define IDR_MODE_MAX                (1)
#define RPS_MODE_MAX                (4)

#define KEY_VALUE_MAX               (7)
#define MODE_MAX                    (1)
//#define CHANNEL_MAX                 (4)



/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanInit(void);
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanSetDstID  ( uint32_t u32ID );
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanGetHWChipID  ( uint32_t *  pu32ID );
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanGetHWBaseID  ( uint32_t *  pu32ID );
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t EnOceanGetSendBuffMax  ( void );
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t EnOceanGetReceiveBuffMax  ( void );
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManCheckDestID(TEL_PARAM_TYPE const *pParamRadioTel);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryBaseID(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryDevInfoOneByOne(Radio_Typedef *pRadio,uint32_t u32EEP,uint8_t u8PageID,uint8_t u8BaseID,uint8_t u8PageFunction);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryChannelMax(Radio_Typedef *pRadio,uint8_t u8ChannelMax);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryIONums(Radio_Typedef *pRadio,uint8_t u8Channel,uint8_t u8ChannelNums);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryChannelType(Radio_Typedef *pRadio,uint8_t u8Channel,uint8_t u8ChannelType,uint8_t u8DimmingType);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryAllBaseID(Radio_Typedef *pRadio,uint32_t u32EEP,uint32_t u32BaseID);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverPageConfig(Radio_Typedef *pRadio,uint32_t u32BaseID,uint8_t u8PageID,uint8_t u8PageConfig);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageButtonIconConfig(Radio_Typedef *pRadio,uint32_t u32BaseID,uint8_t u8PageID,uint8_t u8ButtonID,uint8_t u8ButtonFun,uint8_t u8IconID,uint8_t u8Mode);

/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageTitleConfig(Radio_Typedef *pRadio,uint8_t u8PageID,uint8_t u8Title);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageModeConfig(Radio_Typedef *pRadio,uint8_t u8PageID,uint8_t u8PageRockMode,
                                                              uint8_t u8Button1Mode,uint8_t u8Button2Mode,uint8_t u8Button3Mode,uint8_t u8Button4Mode,
                                                              uint8_t u8Button1Mask,uint8_t u8Button2Mask,uint8_t u8Button3Mask,uint8_t u8Button4Mask);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageChannelConfig(Radio_Typedef *pRadio,uint8_t u8PageID,uint8_t u8ButtonID,uint8_t u8ChannelMask);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWChannelConfig(Radio_Typedef *pRadio,uint8_t u8ChannelID,uint8_t u8ChannelType,uint8_t u8DimmingType);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseReadCloverType(Radio_Typedef *pRadio,uint8_t u8DisplayType,uint8_t u8OutType,uint8_t u8InterfaceMask);
/**
  * @brief  EnOcean Reman Check Page button logic control channel
  * @param
  * @retval None 
  */
RM_RETURN_TYPE EnOceanRemanResponseCloverPageButtonLogicControlChannelMask(Radio_Typedef *pRadio,uint8_t u8Mask);
// ***************************** END RM_CHECKDESTID *******************
//id      4
//eep     3
//channel 1
//mode    1
//key     1
//delay   1
//
// learn struct buff
// FnNumber
// ManID
// 0  -- 3 learnd source id
// 4  -- 6 learnd eep
// 7 -- channel
// 8 -- key
// 9 -- outmode
uint8_t EnOceanReManDataBuff2LearnInfo(TEL_RADIO_TYPE *pRadioTel,ID_SEARCH_TYPE *pSearch,uint8_t u8ChannelMax,uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManGetLearnIDInfo2DataBuff(TEL_RADIO_TYPE *pRadioTel,uint8_t u8Index,uint8_t u8ChannelOffset);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManReadDevAllLearnInfoByTabIds(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManReadDevByLearnIds(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  * 读取整个学习内容 0x308
  */
RM_RETURN_TYPE EnOceanReManReadDevAllLearnInfo_332(Radio_Typedef *pRadio,uint8_t u8PhyAdd,uint8_t u8Channel,uint8_t u8ChannelOffset,uint8_t u8ChannelStart);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManDelLearnDev(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManAddLearnDev2Tab(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManCascadeDevInfo(Radio_Typedef *pRadio,\
                                          uint16_t u16OnineMask,\
                                          uint8_t u8RelayNums,\
                                          uint8_t u8DALINums,\
                                          uint8_t u8TriacNums,\
                                          uint8_t u8BlindNums,\
                                          uint8_t u8DINums,\
                                          uint8_t u8VoltageNums);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManCascadeBusProtocolVersion(Radio_Typedef *pRadio,uint8_t u8CascadeAdd,uint16_t u16BusProtocolVersion);
/**
  * @brief
  * @param
  * @retval None
  * 删除学习条目 0x331
  */
RM_RETURN_TYPE EnOceanReManDelLearnDev_331(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel,uint8_t u8BuffChannel);
/**
  * @brief
  * @param
  * @retval None
  * 添加学习条目 0x330
  */
RM_RETURN_TYPE EnOceanReManAddLearnDev2Tab_330(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel,uint8_t u8BuffChannel);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManClearLearnIds(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManReadLearnIds(Radio_Typedef *pRadio,uint8_t u8LrnTabNums);
/**
  * @brief
  * @param
  * @retval None 
  */ 
RM_RETURN_TYPE EnOceanReManClearGateWayLearnIds(Radio_Typedef *pRadio,uint8_t u8SubAdd,uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManReadGatewayLearnIds(Radio_Typedef *pRadio,uint8_t u8SubAdd,uint16_t u16LrnTabNums);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManWriteDevCfg(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManReadDevCfg(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManResetDevAll(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManActive(Radio_Typedef *pRadio,uint8_t u8ChannelMax);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManTestDevChannel(Radio_Typedef *pRadio,uint8_t u8Channel,uint8_t u8ChannelMax);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManSecurityProcess(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManPingCommand(uint32_t u32EEP,Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManGateWayResponseQueryID(uint32_t u32SearchEEP,Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManResponseQueryID(Radio_Typedef *pRadio);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManQueryFunctionCommand(Radio_Typedef *pRadio,const uint16_t *pu16RpcCmd,uint8_t u8CmdMax);
/**
  * @brief
  * @param
  * @retval None
  */
RM_RETURN_TYPE EnOceanReManQueryStatus(Radio_Typedef *pRadio);


 



#endif

