

/*!
*****************************************************************
						$Name$
						$Revision: 27601 $
						$Date: 2015-03-02 16:20:57 +0200 (Fr, 18 Jun 2010) $
	\file 				Enocean_ESP.c
	\brief 				MSG management related functions
	\author 			zhoujinbang


    <b>Company:</b>\n	menred automation\n
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
#include "esp3_radio.h"
#include "EnOceanLearn.h"
#include "EnOceanMix.h"
//#include "..\EEP/EEP_D201XX.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanInit(void)
{
    //EnOceanRun.pEnOceanReset();
    EnOceanRun.u16SendPeriod      = ENOCEAN_SEND_INTERVAl_DEFAULT;
    EnOceanRun.u8Lock             = RM_UNLOCK;
    EnOceanRun.u32LockCount       = RM_AUTO_LOCK_TIME;
    //EnOceanRun.u32LockCount       = RM_AUTO_LOCK_TIME*1000;
    if ( LearnInfoTab.u8nrIDs > ID_MAX_NR_ENTRIES )
    {
        EnOceanDelLearnTabAll();
    }
    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanSetDstID  ( uint32_t u32ID )
{
    EnOceanRun.u32DstID = u32ID;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanGetHWChipID  ( uint32_t *  pu32ID )
{
    *pu32ID = EnOceanRun.u32ChipID;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanGetHWBaseID  ( uint32_t *  pu32ID )
{
    *pu32ID = EnOceanRun.u32BaseID;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t EnOceanGetSendBuffMax  ( void )
{
    return ESP3_TX_BUF_MAX;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t EnOceanGetReceiveBuffMax  ( void )
{
    return ESP3_RX_BUF_MAX;
}
/**
  * @brief  核对目标ID  destinationID
  * @param  
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManCheckDestID(TEL_PARAM_TYPE const *pParamRadioTel)
{

    uint32_t    u32ChipID;

    // Get the chip ID.
    EnOceanGetHWChipID(&u32ChipID);

    // The chip ID is compared to the destion ID in the telegram.
    if ( u32ChipID != pParamRadioTel->ReMan.u32DestinationId )
    {
        //reman_setError(RM_RETURN_CODE_WRONG_ID);
        return RM_NO_SUCCESS;
    }

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryBaseID(Radio_Typedef *pRadio)
{
    //Radio_Typedef RadioTx;

    pRadio->Telegram.ReMan.u16FnNum = RM_RPC_READ_BASEID_ANS;
    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 5;

    pRadio->Telegram.ReMan.u8Data[0] = EnOceanRun.u32BaseID>>24;
    pRadio->Telegram.ReMan.u8Data[1] = EnOceanRun.u32BaseID>>16;
    pRadio->Telegram.ReMan.u8Data[2] = EnOceanRun.u32BaseID>> 8;
    pRadio->Telegram.ReMan.u8Data[3] = EnOceanRun.u32BaseID&0xFF;
    pRadio->Telegram.ReMan.u8Data[4] = EnOceanRun.u8BaseIDRemainCycle;

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    //EnOceanReManData2SerialBuff(&RadioTx,REMAN_RANDOM_DISABLE);

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryDevInfoOneByOne(Radio_Typedef *pRadio,uint32_t u32EEP,uint8_t u8PageID,uint8_t u8BaseID,uint8_t u8PageFunction)
{
    // radio data process
    
    uint32_t u32ID;

    if ( 0xFF == u8BaseID )
    {
        u32ID                                = 0xFFFFFFFF;
    }
    else
    {
        u32ID                                = EnOceanRun.u32BaseID + u8BaseID;
    }
    
    pRadio->Telegram.ReMan.u16FnNum      = RM_ANSWER_START + RM_RPC_QUERY_ALL_BASEID_DEV;
    pRadio->Telegram.ReMan.u16ManId      = 0x051;
    pRadio->Telegram.ReMan.u8Length      = 9;

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    pRadio->Telegram.ReMan.u8Data[0]     = u32ID >> 24;
    pRadio->Telegram.ReMan.u8Data[1]     = u32ID >> 16;
    pRadio->Telegram.ReMan.u8Data[2]     = u32ID >> 8;
    pRadio->Telegram.ReMan.u8Data[3]     = u32ID & 0xFF;
    pRadio->Telegram.ReMan.u8Data[4]     = u32EEP>>16;
    pRadio->Telegram.ReMan.u8Data[5]     = u32EEP>>8;
    pRadio->Telegram.ReMan.u8Data[6]     = u32EEP&0xFF;
    pRadio->Telegram.ReMan.u8Data[7]     = u8PageID;
    pRadio->Telegram.ReMan.u8Data[8]     = u8PageFunction;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryChannelMax(Radio_Typedef *pRadio,uint8_t u8ChannelMax)
{
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 1;
    pRadio->Telegram.ReMan.u8Data[0] = u8ChannelMax;
    pRadio->Telegram.ReMan.u8Data[1] = 0x00;
    pRadio->Telegram.ReMan.u8Data[2] = 0x00;
    pRadio->Telegram.ReMan.u8Data[3] = 0x00;     

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryIONums(Radio_Typedef *pRadio,uint8_t u8Channel,uint8_t u8ChannelNums)
{
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 2;
    pRadio->Telegram.ReMan.u8Data[0] = u8Channel;
    pRadio->Telegram.ReMan.u8Data[1] = u8ChannelNums;
    pRadio->Telegram.ReMan.u8Data[2] = 0x00;
    pRadio->Telegram.ReMan.u8Data[3] = 0x00;     

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryChannelType(Radio_Typedef *pRadio,uint8_t u8Channel,uint8_t u8ChannelType,uint8_t u8DimmingType)
{
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 3;

    pRadio->Telegram.ReMan.u8Data[0] = u8Channel;
    pRadio->Telegram.ReMan.u8Data[1] = u8ChannelType;
    pRadio->Telegram.ReMan.u8Data[2] = u8DimmingType;
    pRadio->Telegram.ReMan.u8Data[3] = 0x00; 

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseQueryAllBaseID(Radio_Typedef *pRadio,uint32_t u32EEP,uint32_t u32BaseID)
{
    if ( pRadio->Telegram.ReMan.u16FnNum < RM_ANSWER_START )
    {
        pRadio->Telegram.ReMan.u16FnNum  += RM_ANSWER_START;    
    }
    //pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 7;

    pRadio->Telegram.ReMan.u8Data[0] = u32BaseID>>24;
    pRadio->Telegram.ReMan.u8Data[1] = u32BaseID>>16;
    pRadio->Telegram.ReMan.u8Data[2] = u32BaseID>>8;
    pRadio->Telegram.ReMan.u8Data[3] = u32BaseID&0xFF; 
    pRadio->Telegram.ReMan.u8Data[4] = u32EEP>>16;
    pRadio->Telegram.ReMan.u8Data[5] = u32EEP>>8;
    pRadio->Telegram.ReMan.u8Data[6] = u32EEP&0xFF;

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverPageConfig(Radio_Typedef *pRadio,uint32_t u32BaseID,uint8_t u8PageID,uint8_t u8PageConfig)
{

    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;//RM_RPC_WRITE_CLOVER_PAGE_CFG_ANS;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 6;

    pRadio->Telegram.ReMan.u8Data[0] = u32BaseID>>24;
    pRadio->Telegram.ReMan.u8Data[1] = u32BaseID>>16;
    pRadio->Telegram.ReMan.u8Data[2] = u32BaseID>> 8;
    pRadio->Telegram.ReMan.u8Data[3] = u32BaseID&0xFF;
    pRadio->Telegram.ReMan.u8Data[4] = u8PageID;
    pRadio->Telegram.ReMan.u8Data[5] = u8PageConfig; 
    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageButtonIconConfig(Radio_Typedef *pRadio,uint32_t u32BaseID, uint8_t u8PageID,uint8_t u8ButtonID,uint8_t u8ButtonFun,uint8_t u8IconID,uint8_t u8Mode)
{
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;//RM_RPC_READ_CLOVER_PAGE_ROCK_BUTTON_CFG_ANS;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 9; 
     
    pRadio->Telegram.ReMan.u8Data[0] = u32BaseID>>24;
    pRadio->Telegram.ReMan.u8Data[1] = u32BaseID>>16;
    pRadio->Telegram.ReMan.u8Data[2] = u32BaseID>>8; 
    pRadio->Telegram.ReMan.u8Data[3] = u32BaseID&0xFF; 
     
    pRadio->Telegram.ReMan.u8Data[4] = u8PageID;
    pRadio->Telegram.ReMan.u8Data[5] = u8ButtonID;
    pRadio->Telegram.ReMan.u8Data[6] = u8ButtonFun; 
    pRadio->Telegram.ReMan.u8Data[7] = u8IconID;
    pRadio->Telegram.ReMan.u8Data[8] = u8Mode;

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageTitleConfig(Radio_Typedef *pRadio,uint8_t u8PageID,uint8_t u8Title)
{
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 2;

    pRadio->Telegram.ReMan.u8Data[0] = u8PageID;
    pRadio->Telegram.ReMan.u8Data[1] = u8Title;    

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageModeConfig(Radio_Typedef *pRadio,uint8_t u8PageID,uint8_t u8PageRockMode,
                                                              uint8_t u8Button1Mode,uint8_t u8Button2Mode,uint8_t u8Button3Mode,uint8_t u8Button4Mode,
                                                              uint8_t u8Button1Mask,uint8_t u8Button2Mask,uint8_t u8Button3Mask,uint8_t u8Button4Mask)
{
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 10;

    pRadio->Telegram.ReMan.u8Data[0] = u8PageID;
    pRadio->Telegram.ReMan.u8Data[1] = u8PageRockMode;
    pRadio->Telegram.ReMan.u8Data[2] = u8Button1Mode;
    pRadio->Telegram.ReMan.u8Data[3] = u8Button2Mode;
    pRadio->Telegram.ReMan.u8Data[4] = u8Button3Mode;
    pRadio->Telegram.ReMan.u8Data[5] = u8Button4Mode;

    pRadio->Telegram.ReMan.u8Data[6] = u8Button1Mask;
    pRadio->Telegram.ReMan.u8Data[7] = u8Button2Mask;
    pRadio->Telegram.ReMan.u8Data[8] = u8Button3Mask;
    pRadio->Telegram.ReMan.u8Data[9] = u8Button4Mask;

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    //EnOceanReManData2SerialBuff(&RadioTx,REMAN_RANDOM_DISABLE);

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWCloverRockPageChannelConfig(Radio_Typedef *pRadio,uint8_t u8PageID,uint8_t u8ButtonID,uint8_t u8ChannelMask)
{
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + pRadio->Telegram.ReMan.u16FnNum;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 5;

    pRadio->Telegram.ReMan.u8Data[0] = u8PageID;
    pRadio->Telegram.ReMan.u8Data[1] = u8ButtonID;
    pRadio->Telegram.ReMan.u8Data[2] = u8ChannelMask&0x01;
    pRadio->Telegram.ReMan.u8Data[3] = (u8ChannelMask>>1)&0x01;
    pRadio->Telegram.ReMan.u8Data[4] = (u8ChannelMask>>2)&0x01;

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    //EnOceanReManData2SerialBuff(&RadioTx,REMAN_RANDOM_DISABLE);

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseRWChannelConfig(Radio_Typedef *pRadio,uint8_t u8ChannelID,uint8_t u8ChannelType,uint8_t u8DimmingType)
{
    uint16_t u16RmFN;

    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 3;

    pRadio->Telegram.ReMan.u8Data[0] = u8ChannelID;
    pRadio->Telegram.ReMan.u8Data[1] = u8ChannelType;    
    pRadio->Telegram.ReMan.u8Data[2] = u8DimmingType;    

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;    

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManResponseReadCloverType(Radio_Typedef *pRadio,uint8_t u8DisplayType,uint8_t u8OutType,uint8_t u8InterfaceMask)
{    
    pRadio->Telegram.ReMan.u16FnNum  = RM_RPC_READ_CLOVER_TYPE_ANS;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 3;

    pRadio->Telegram.ReMan.u8Data[0] = u8DisplayType;
    pRadio->Telegram.ReMan.u8Data[1] = u8OutType;
    pRadio->Telegram.ReMan.u8Data[2] = u8InterfaceMask;
    pRadio->Telegram.ReMan.u8Data[3] = 0x00; 

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    //EnOceanReManData2SerialBuff(&RadioTx,REMAN_RANDOM_DISABLE);

    return RM_SUCCESS;
}
/**
  * @brief  EnOcean Reman Check Page button logic control channel
  * @param
  * @retval None 
  */
RM_RETURN_TYPE EnOceanRemanResponseCloverPageButtonLogicControlChannelMask(Radio_Typedef *pRadio,uint8_t u8Mask)
{
    pRadio->Telegram.ReMan.u16FnNum += RM_ANSWER_START;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 3;
    pRadio->Telegram.ReMan.u8Data[0] = pRadio->Telegram.ReMan.u8Data[0];
    pRadio->Telegram.ReMan.u8Data[1] = pRadio->Telegram.ReMan.u8Data[1];
    pRadio->Telegram.ReMan.u8Data[2] = u8Mask;    

    pRadio->Param.ReMan.u32DestinationId = pRadio->Param.ReMan.u32SourceId;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    return RM_SUCCESS;
}
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
/**
  * @brief
  * @param
  * @retval None
  * 学习数据缓冲区信息
  */
uint8_t EnOceanReManDataBuff2LearnInfo(TEL_RADIO_TYPE *pRadioTel,ID_SEARCH_TYPE *pSearch,uint8_t u8ChannelMax,uint8_t u8Channel)
{
    uint8_t u8Status;
    uint32_t u32Eep;
    
    u32Eep = (uint32_t)pRadioTel->ReMan.u8Data[4]<<16 | (uint32_t)pRadioTel->ReMan.u8Data[5]<<8 |(uint32_t)pRadioTel->ReMan.u8Data[6];

    u8Status = 0;
    switch (u32Eep)
    {
        case EEP_F60201:
        {
            if ( u8Channel >= u8ChannelMax )
            {
                u8Status = 16;
            }
            pSearch->entry.LrnDev.RPS.u5Channel    = u8Channel;
            if (  ( pRadioTel->ReMan.u8Data[8] == 0x01)
                ||( pRadioTel->ReMan.u8Data[8] == 0x03)
                ||( pRadioTel->ReMan.u8Data[8] == 0x05)
                ||( pRadioTel->ReMan.u8Data[8] == 0x07) )
            {
                
            }
            else
            {
                u8Status = 18;
            }
            pSearch->entry.LrnDev.RPS.u3Key        = pRadioTel->ReMan.u8Data[8];
            if ( pRadioTel->ReMan.u8Data[9] > RPS_MODE_MAX)
            {
                u8Status = 17;
            }
            pSearch->entry.LrnDev.RPS.u3OutMode    = pRadioTel->ReMan.u8Data[9];
            break;
        }
        case EEP_A50701:
        case EEP_A50702:
        case EEP_A50703:
        {
            if ( u8Channel >= u8ChannelMax )
            {
                u8Status = 16;
            }
            pSearch->entry.LrnDev.PIR.u5Channel    = u8Channel;
            
            if ( pRadioTel->ReMan.u8Data[9] > PIR_MODE_MAX)
            {
                u8Status = 17;
            } 
            pSearch->entry.LrnDev.PIR.u3OutMode  = pRadioTel->ReMan.u8Data[9];
            break;
        }
        case EEP_D50001:
        {
            if ( u8Channel >= u8ChannelMax )
            {
                u8Status = 16;
            }
            pSearch->entry.LrnDev.IDR.u5Channel    = u8Channel;
            
            if ( pRadioTel->ReMan.u8Data[9] > IDR_MODE_MAX)
            {
                u8Status = 17;
            }
            pSearch->entry.LrnDev.IDR.u3OutMode    = pRadioTel->ReMan.u8Data[9];
            break;
        }
        case EEP_D10104:
        {
            break;
        }    
        case EEP_A50905:
        case EEP_A50907:
        case EEP_A50910:
        {
            u8Status = 4;
            break;
        }    
        case EEP_SMART_HIVE:
        {
            if ( u8ChannelMax > 0 )
            {
                pRadioTel->ReMan.u8Data[4] = (LEARN_LIGHT_EEP>>16)&0xFF;
                pRadioTel->ReMan.u8Data[5] = (LEARN_LIGHT_EEP>>8)&0xFF;
                pRadioTel->ReMan.u8Data[6] = (LEARN_LIGHT_EEP)&0xFF;
            }
            else
            {
                pRadioTel->ReMan.u8Data[4] = (EEP_SMART_HIVE>>16)&0xFF;
                pRadioTel->ReMan.u8Data[5] = (EEP_SMART_HIVE>>8)&0xFF;
                pRadioTel->ReMan.u8Data[6] = (EEP_SMART_HIVE)&0xFF;
            }
            pSearch->entry.LrnDev.u16Data = 0x00;
            break;
        }
        case EEP_D20101:
        case EEP_D20113:
        case EEP_D20115:
        case EEP_D20116:
        case EEP_D1010C:
        case EEP_D1010D:
        {
        #if defined LEARN_LIGHT_EEP
            if ( LEARN_LIGHT_EEP != u32Eep )
            {
                u8Status = 4;
            }
        #else
            #error "Must define: MACRO LEARN_LIGHT_EEP for the actutor"
            #pragma message("Must define MACRO LEARN_LIGHT_EEP ")
        #endif
            break;
        }
        default:
            u8Status = 4;
            break;
    }
    
    pSearch->entry.u32SrcId                  = (uint32_t)pRadioTel->ReMan.u8Data[0]<<24;
    pSearch->entry.u32SrcId                 |= (uint32_t)pRadioTel->ReMan.u8Data[1]<<16;
    pSearch->entry.u32SrcId                 |= (uint32_t)pRadioTel->ReMan.u8Data[2]<<8;
    pSearch->entry.u32SrcId                 |= (uint32_t)pRadioTel->ReMan.u8Data[3];
    
    pSearch->entry.u8EepRorg                 = pRadioTel->ReMan.u8Data[4];
    pSearch->entry.u8EepFun                  = pRadioTel->ReMan.u8Data[5];
    pSearch->entry.u8EepType                 = pRadioTel->ReMan.u8Data[6];
    /* learn and search infomation setting,for the memeroy */
    pSearch->u8ChannelCheck                  = LRN_SERACH;
    pSearch->entry.LrnDev.General.u1LrnType  = LRN_REMOTE;
    pSearch->u8Start                         = 0;

    return u8Status;
}
/**
  * @brief
  * @param
  * @retval None
  * 学习数据缓冲区信息
  */
RM_RETURN_TYPE EnOceanReManGetLearnIDInfo2DataBuff(TEL_RADIO_TYPE *pRadioTel,uint8_t u8Index,uint8_t u8ChannelOffset)
{

    uint32_t u32Eep;

    #if defined LEARN_LIGHT_EEP
        uint32_t u32DevEEP;
        u32DevEEP = LEARN_LIGHT_EEP; 
    #else
        //#error "Must define: MACRO LEARN_LIGHT_EEP for the actutor"
        //#pragma message("Must define MACRO LEARN_LIGHT_EEP ")
    #endif
    
    
    // learn struct buff
    // FnNumber
    // ManID
    // 0  -- 3 learnd source id
    // 4  -- 6 learnd eep
    // 7 -- channel
    // 8 -- key
    // 9 -- outmode
    //pIdTable
    if ( u8Index >= ID_MAX_NR_ENTRIES )
    {
        return RM_NO_SUCCESS;
    }

    pRadioTel->ReMan.u8Data[4] = LearnInfoTab.entry[u8Index].u8EepRorg;
    pRadioTel->ReMan.u8Data[5] = LearnInfoTab.entry[u8Index].u8EepFun;
    pRadioTel->ReMan.u8Data[6] = LearnInfoTab.entry[u8Index].u8EepType;

    pRadioTel->ReMan.u8Data[0] = LearnInfoTab.entry[u8Index].u32SrcId>>24;
    pRadioTel->ReMan.u8Data[1] = LearnInfoTab.entry[u8Index].u32SrcId>>16;
    pRadioTel->ReMan.u8Data[2] = LearnInfoTab.entry[u8Index].u32SrcId>>8;
    pRadioTel->ReMan.u8Data[3] = LearnInfoTab.entry[u8Index].u32SrcId;

    u32Eep = (uint32_t)pRadioTel->ReMan.u8Data[4]<<16 | (uint32_t)pRadioTel->ReMan.u8Data[5]<<8 |pRadioTel->ReMan.u8Data[6];

    switch (u32Eep)
    {
        case EEP_F60201:
        {
            pRadioTel->ReMan.u8Data[7] = LearnInfoTab.entry[u8Index].LrnDev.RPS.u5Channel + u8ChannelOffset;
            pRadioTel->ReMan.u8Data[8] = LearnInfoTab.entry[u8Index].LrnDev.RPS.u3Key;
            pRadioTel->ReMan.u8Data[9] = LearnInfoTab.entry[u8Index].LrnDev.RPS.u3OutMode;    
            break;
        }
        case EEP_A50701:
        case EEP_A50702:
        case EEP_A50703:
        {
            pRadioTel->ReMan.u8Data[7] = LearnInfoTab.entry[u8Index].LrnDev.PIR.u5Channel + u8ChannelOffset;    
            break;
        }
        case EEP_D50001:
        {
            pRadioTel->ReMan.u8Data[7] = LearnInfoTab.entry[u8Index].LrnDev.IDR.u5Channel + u8ChannelOffset;    
            break;
        }
        
        case EEP_A50905:        
        case EEP_A50907:        
        case EEP_A50910:
        {
            pRadioTel->ReMan.u8Data[7] = LearnInfoTab.entry[u8Index].LrnDev.General.u5Channel + u8ChannelOffset;    
            break;
        }    
        case EEP_D10104:
        case EEP_SMART_HIVE:
        case EEP_D1010C:
        case EEP_D20101:
        case EEP_D20113:
        case EEP_D20115:
        case EEP_D20116:
        {
        #if defined LEARN_LIGHT_EEP
            if ( u32DevEEP == u32Eep )
            {
                pRadioTel->ReMan.u8Data[7] = 0x00;
                pRadioTel->ReMan.u8Data[8] = 0x00;
                pRadioTel->ReMan.u8Data[9] = 0x00;
            }
        #else
            pRadioTel->ReMan.u8Data[0] = 0xFF;
            pRadioTel->ReMan.u8Data[1] = 0xFF;
            pRadioTel->ReMan.u8Data[2] = 0xFF;
            pRadioTel->ReMan.u8Data[3] = 0xFF;
            pRadioTel->ReMan.u8Data[4] = 0xFF;
            pRadioTel->ReMan.u8Data[5] = 0xFF;
            pRadioTel->ReMan.u8Data[6] = 0xFF;
            pRadioTel->ReMan.u8Data[7] = 0xFF;
            pRadioTel->ReMan.u8Data[8] = 0xFF;
            return RM_NO_SUCCESS;
        #endif
            break;
        }
        default:
            pRadioTel->ReMan.u8Data[0] = 0xFF;
            pRadioTel->ReMan.u8Data[1] = 0xFF;
            pRadioTel->ReMan.u8Data[2] = 0xFF;
            pRadioTel->ReMan.u8Data[3] = 0xFF;
            pRadioTel->ReMan.u8Data[4] = 0xFF;
            pRadioTel->ReMan.u8Data[5] = 0xFF;
            pRadioTel->ReMan.u8Data[6] = 0xFF;
            pRadioTel->ReMan.u8Data[7] = 0xFF;
            pRadioTel->ReMan.u8Data[8] = 0xFF;
            return RM_NO_SUCCESS;
            break;
    }
    
    

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 读取整个学习内容 0x308
  */
RM_RETURN_TYPE EnOceanReManReadDevAllLearnInfoByTabIds(Radio_Typedef *pRadio)
{
    uint8_t u8I;
    uint8_t u8Status;

    u8Status = 0;
    
    if ( EnOceanGetLearnTabNums() )
    {        
        u8Status = 0;
    }
    else
    {
        u8Status = 1;
    }
    pRadio->Telegram.ReMan.u16FnNum      = RM_RPC_READ_ONE_BY_ONE_ANS;
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    pRadio->Telegram.ReMan.u8Length           = 10;

    if ( u8Status )
    {
        pRadio->Telegram.ReMan.u8Data[0] = u8Status;
        pRadio->Telegram.ReMan.u8Data[1] = u8Status;
        pRadio->Telegram.ReMan.u8Data[2] = u8Status;
        pRadio->Telegram.ReMan.u8Data[3] = u8Status;
        pRadio->Telegram.ReMan.u8Data[4] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[5] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[6] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[7] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[8] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[9] = 0xFF; 
    }
    else
    {

        for (u8I = 0; u8I < EnOceanGetLearnTabNums(); u8I ++)
        {           
            if ( OK == EnOcean_GetSendQueuePushID() )
            {
                pRadio->Telegram.ReMan.u8Data[0] = LearnInfoTab.entry[u8I].u32SrcId>>24;
                pRadio->Telegram.ReMan.u8Data[1] = LearnInfoTab.entry[u8I].u32SrcId>>16;
                pRadio->Telegram.ReMan.u8Data[2] = LearnInfoTab.entry[u8I].u32SrcId>> 8;
                pRadio->Telegram.ReMan.u8Data[3] = LearnInfoTab.entry[u8I].u32SrcId&0xFF;
                pRadio->Telegram.ReMan.u8Data[4] = LearnInfoTab.entry[u8I].u8EepRorg;
                pRadio->Telegram.ReMan.u8Data[5] = LearnInfoTab.entry[u8I].u8EepFun;
                pRadio->Telegram.ReMan.u8Data[6] = LearnInfoTab.entry[u8I].u8EepType;
                pRadio->Telegram.ReMan.u8Data[7] = LearnInfoTab.entry[u8I].LrnDev.General.u5Channel;
                pRadio->Telegram.ReMan.u8Data[8] = LearnInfoTab.entry[u8I].LrnDev.General.u3Bit;
                pRadio->Telegram.ReMan.u8Data[9] = LearnInfoTab.entry[u8I].LrnDev.General.u3OutMode;
            
                EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PushCount].u8Cmd = eQUEUE_REMAN_TELEGRAM;
                EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PushCount].Data = *pRadio;
                EnOcean_SetSendQueueIDOccupy();
            }        
        }

        return RM_NO_SUCCESS;
    }

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 指定学习条目读取内容 0x307
  */
RM_RETURN_TYPE EnOceanReManReadDevByLearnIds(Radio_Typedef *pRadio)
{
    uint8_t u8I;
    uint8_t u8Status;
  
    if( RM_NO_SUCCESS == EnOceanReManCheckDestID(&pRadio->Param) )
    {
        return RM_COMMAND_FLASH_READ_NO_SUCCESS;
    }
    
    if ( pRadio->Telegram.ReMan.u8Length == 0 )
    {
        u8Status = 1;
    }
    

    if ( pRadio->Telegram.ReMan.u8Data[0] < EnOceanGetLearnTabNums() )
    {
        u8I = pRadio->Telegram.ReMan.u8Data[0];        
        u8Status = 0;
    }
    // read over the id list max
    else
    {
        u8Status = 2;
    }
    pRadio->Telegram.ReMan.u16FnNum           = RM_RPC_READ_ONE_ANS;
    pRadio->Param.ReMan.u32DestinationId      = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId           = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    pRadio->Telegram.ReMan.u8Length           = 10;

    if ( u8Status )
    {
        pRadio->Telegram.ReMan.u8Data[0] = u8Status;
        pRadio->Telegram.ReMan.u8Data[1] = u8Status;
        pRadio->Telegram.ReMan.u8Data[2] = u8Status;
        pRadio->Telegram.ReMan.u8Data[3] = u8Status;
        pRadio->Telegram.ReMan.u8Data[4] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[5] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[6] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[7] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[8] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[9] = 0xFF;           
    }
    else
    {
        
        pRadio->Telegram.ReMan.u8Data[0] = LearnInfoTab.entry[u8I].u32SrcId>>24;
        pRadio->Telegram.ReMan.u8Data[1] = LearnInfoTab.entry[u8I].u32SrcId>>16;
        pRadio->Telegram.ReMan.u8Data[2] = LearnInfoTab.entry[u8I].u32SrcId>> 8;
        pRadio->Telegram.ReMan.u8Data[3] = LearnInfoTab.entry[u8I].u32SrcId&0xFF;
        pRadio->Telegram.ReMan.u8Data[4] = LearnInfoTab.entry[u8I].u8EepRorg;
        pRadio->Telegram.ReMan.u8Data[5] = LearnInfoTab.entry[u8I].u8EepFun;
        pRadio->Telegram.ReMan.u8Data[6] = LearnInfoTab.entry[u8I].u8EepType;
        pRadio->Telegram.ReMan.u8Data[7] = LearnInfoTab.entry[u8I].LrnDev.General.u5Channel;
        pRadio->Telegram.ReMan.u8Data[8] = LearnInfoTab.entry[u8I].LrnDev.General.u3Bit;
        pRadio->Telegram.ReMan.u8Data[9] = LearnInfoTab.entry[u8I].LrnDev.General.u3OutMode;
    }

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 读取整个学习内容 0x332
  */
RM_RETURN_TYPE EnOceanReManReadDevAllLearnInfo_332(Radio_Typedef *pRadio,uint8_t u8PhyAdd,uint8_t u8Channel,uint8_t u8ChannelOffset,uint8_t u8ChannelStart)
{
    uint8_t u8I;
    uint8_t u8Status;
    uint8_t u8ChannelLrnNums;
    uint8_t u8IDCnt;

    uint16_t u16RmFN;
    u8Status = 0;

    if ( 0xFF == u8Channel )
    {
        u8ChannelLrnNums = EnOceanGetLearnTabNums();
    }
    else
    {
        u8ChannelLrnNums = EnOceanGetLearnChannelTabNums(u8Channel);
    }
    

    if ( u8ChannelLrnNums )
    {        
        u8Status = 0;
    }
    else
    {
        u8Status = 1;
    }
    //pRadio->Telegram.ReMan.u16FnNum           = RM_RPC_READ_LEARN_CHANNEL_INFO;
    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;
    
    pRadio->Param.ReMan.u32DestinationId      = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId           = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    pRadio->Telegram.ReMan.u8Length           = 13;

    if ( u8Status )
    {
        /*
        pRadio->Telegram.ReMan.u8Data[0] = u8PhyAdd;
        pRadio->Telegram.ReMan.u8Data[1] = u8Channel;
        pRadio->Telegram.ReMan.u8Data[2] = 0x00;
        pRadio->Telegram.ReMan.u8Data[3] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[4] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[5] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[6] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[7] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[8] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[9] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[10] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[11] = 0xFF;
        pRadio->Telegram.ReMan.u8Data[12] = 0xFF; 
        */
        return RM_NO_SUCCESS;
    }
    else
    {        
        u8IDCnt = u8ChannelLrnNums-1;

        for (u8I = 0; u8I < EnOceanGetLearnTabNums(); u8I ++)
        {           
            if ( OK == EnOcean_GetSendQueuePushID() )
            {
                pRadio->Telegram.ReMan.u8Data[0] = u8PhyAdd;
                if ( 0xFF != u8Channel )
                {
                    if ( u8Channel != LearnInfoTab.entry[u8I].LrnDev.General.u5Channel )
                    {
                        continue;
                    }
                }
                pRadio->Telegram.ReMan.u8Data[1] = u8Channel;
                pRadio->Telegram.ReMan.u8Data[2] = u8IDCnt;
                u8IDCnt--;

                pRadio->Telegram.ReMan.u8Data[3] = LearnInfoTab.entry[u8I].u32SrcId>>24;
                pRadio->Telegram.ReMan.u8Data[4] = LearnInfoTab.entry[u8I].u32SrcId>>16;
                pRadio->Telegram.ReMan.u8Data[5] = LearnInfoTab.entry[u8I].u32SrcId>> 8;
                pRadio->Telegram.ReMan.u8Data[6] = LearnInfoTab.entry[u8I].u32SrcId&0xFF;
                pRadio->Telegram.ReMan.u8Data[7] = LearnInfoTab.entry[u8I].u8EepRorg;
                pRadio->Telegram.ReMan.u8Data[8] = LearnInfoTab.entry[u8I].u8EepFun;
                pRadio->Telegram.ReMan.u8Data[9] = LearnInfoTab.entry[u8I].u8EepType;
                pRadio->Telegram.ReMan.u8Data[10] = LearnInfoTab.entry[u8I].LrnDev.General.u5Channel;
                if ( pRadio->Telegram.ReMan.u8Data[10] >= u8ChannelStart )
                {
                    pRadio->Telegram.ReMan.u8Data[10] -= u8ChannelStart;
                    pRadio->Telegram.ReMan.u8Data[10] += u8ChannelOffset;
                }
                pRadio->Telegram.ReMan.u8Data[11] = LearnInfoTab.entry[u8I].LrnDev.General.u3Bit;
                pRadio->Telegram.ReMan.u8Data[12] = LearnInfoTab.entry[u8I].LrnDev.General.u3OutMode;
            
                EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PushCount].u8Cmd = eQUEUE_REMAN_TELEGRAM;
                EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PushCount].Data = *pRadio;
                EnOcean_SetSendQueueIDOccupy();
            }        
        }

        return RM_NO_SUCCESS;
    }

    //return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 删除学习条目 0x306
  */
RM_RETURN_TYPE EnOceanReManDelLearnDev(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel)
{
    ID_SEARCH_TYPE tSearch;
    ID_SEARCH_TYPE tSearchOut;
    uint8_t u8Status;

    u8Status = EnOceanReManDataBuff2LearnInfo(&pRadio->Telegram,&tSearch,u8ChannelMax, u8Channel);
    if ( RM_SUCCESS == u8Status )
    {        
        if ( ID_SUCCESS != EnOceanSearchLearnTab(&tSearch,&tSearchOut ) )             
        {
            u8Status = 0x05;//0x01;       
        }        

        if (  ID_SUCCESS != EnOceanDelEEPInfoFromLearnTab(tSearchOut.u8Start) ) 
        {
            u8Status = 0x02;
        }

        //u8Status = 0x00;

        EnOceanSaveLearnTabEvent();       
    }

    // radio data process
    pRadio->Telegram.ReMan.u16FnNum  = RM_RPC_DEL_ONE_ANS;
    pRadio->Telegram.ReMan.u16ManId  = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length  = 4;
    pRadio->Telegram.ReMan.u8Data[0] = u8Status;
    pRadio->Telegram.ReMan.u8Data[1] = u8Status;
    pRadio->Telegram.ReMan.u8Data[2] = u8Status;
    pRadio->Telegram.ReMan.u8Data[3] = u8Status;

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 添加学习条目 0x305
  */
RM_RETURN_TYPE EnOceanReManAddLearnDev2Tab(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel)
{
    ID_SEARCH_TYPE tSearch;
    uint8_t u8Status;

    u8Status = EnOceanReManDataBuff2LearnInfo(&pRadio->Telegram,&tSearch,u8ChannelMax,u8Channel);

    // radio data process
    if ( 0 == u8Status )
    {
        tSearch.u8ChannelCheck          = LRN_SERACH;
        tSearch.u8Start                 = 0;
        if ( OK == EnOceanReManLearnDev2Tab(&tSearch) )
        {           
            EnOceanSaveLearnTabEvent();
            u8Status = RM_SUCCESS;
        }
        else
        {   
            pRadio->Telegram.ReMan.u8Data[3]= 0x01;
            u8Status = 0x01;
        }
    }

    pRadio->Telegram.ReMan.u16FnNum             = RM_RPC_ADD_ONE_ANS;
    pRadio->Telegram.ReMan.u16ManId             = ENOCEAN_MENRED_MAN_ID;
    pRadio->Param.ReMan.u32DestinationId        = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId             = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable   = REMAN_RANDOM_DISABLE;

    pRadio->Telegram.ReMan.u8Length     = 4;
    pRadio->Telegram.ReMan.u8Data[0]    = 0x00;
    pRadio->Telegram.ReMan.u8Data[1]    = 0x00;
    pRadio->Telegram.ReMan.u8Data[2]    = 0x00;
    pRadio->Telegram.ReMan.u8Data[3]    = u8Status;

    return RM_SUCCESS;
}
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
                                          uint8_t u8VoltageNums)
{
    

    pRadio->Telegram.ReMan.u16FnNum             = RM_RPC_READ_DI_NUMS_ANS;
    pRadio->Telegram.ReMan.u16ManId             = ENOCEAN_MENRED_MAN_ID;
    pRadio->Param.ReMan.u32DestinationId        = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId             = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable   = REMAN_RANDOM_DISABLE;

    pRadio->Telegram.ReMan.u8Length     = 8;
    pRadio->Telegram.ReMan.u8Data[0]    = u16OnineMask>>8;
    pRadio->Telegram.ReMan.u8Data[1]    = u16OnineMask&0xFF;
    pRadio->Telegram.ReMan.u8Data[2]    = u8RelayNums;
    pRadio->Telegram.ReMan.u8Data[3]    = u8DALINums;
    pRadio->Telegram.ReMan.u8Data[4]    = u8TriacNums;
    pRadio->Telegram.ReMan.u8Data[5]    = u8BlindNums;
    pRadio->Telegram.ReMan.u8Data[6]    = u8DINums;
    pRadio->Telegram.ReMan.u8Data[7]    = u8VoltageNums;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManCascadeBusProtocolVersion(Radio_Typedef *pRadio,uint8_t u8CascadeAdd,uint16_t u16BusProtocolVersion)
{
    pRadio->Telegram.ReMan.u16FnNum             = RM_RPC_CASCADE_BUS_VERSION_ANS;
    pRadio->Telegram.ReMan.u16ManId             = ENOCEAN_MENRED_MAN_ID;
    pRadio->Param.ReMan.u32DestinationId        = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId             = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable   = REMAN_RANDOM_DISABLE;

    pRadio->Telegram.ReMan.u8Length     = 4;
    pRadio->Telegram.ReMan.u8Data[0]    = u8CascadeAdd;
    pRadio->Telegram.ReMan.u8Data[1]    = u16BusProtocolVersion>>8;
    pRadio->Telegram.ReMan.u8Data[2]    = u16BusProtocolVersion&0xFF;    

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 删除学习条目 0x331
  */
RM_RETURN_TYPE EnOceanReManDelLearnDev_331(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel,uint8_t u8BuffChannel)
{
    ID_SEARCH_TYPE tSearch;
    ID_SEARCH_TYPE tSearchOut;
    uint8_t u8Status;

    u8Status = EnOceanReManDataBuff2LearnInfo(&pRadio->Telegram,&tSearch,u8ChannelMax,u8BuffChannel);
    if ( 0 == u8Status )
    {        
        u8Status = EnOceanSearchLearnTab(&tSearch,&tSearchOut );
        if ( ID_SUCCESS != u8Status )             
        {
            u8Status = 0x05;       
        }        
        else 
        {
            u8Status = EnOceanDelEEPInfoFromLearnTab(tSearchOut.u8Start);
            if (  ID_SUCCESS == u8Status ) 
        	{
                EnOceanSaveLearnTabEvent();
        	}        
            else
        	{
                u8Status = 0x05;
            }           
        }
    }

    // radio data process
    pRadio->Telegram.ReMan.u16FnNum           = RM_RPC_DEL_LEARN_ADVANCED_ANS;
    pRadio->Telegram.ReMan.u16ManId           = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length           = 11;
    pRadio->Telegram.ReMan.u8Data[0]          = u8Status;

    pRadio->Telegram.ReMan.u8Data[1]          = tSearch.entry.u32SrcId>>24;
    pRadio->Telegram.ReMan.u8Data[2]          = tSearch.entry.u32SrcId>>16;
    pRadio->Telegram.ReMan.u8Data[3]          = tSearch.entry.u32SrcId>> 8;
    pRadio->Telegram.ReMan.u8Data[4]          = tSearch.entry.u32SrcId&0xFF;
    pRadio->Telegram.ReMan.u8Data[5]          = tSearch.entry.u8EepRorg;
    pRadio->Telegram.ReMan.u8Data[6]          = tSearch.entry.u8EepFun;
    pRadio->Telegram.ReMan.u8Data[7]          = tSearch.entry.u8EepType;
    pRadio->Telegram.ReMan.u8Data[8]          = u8Channel;
    pRadio->Telegram.ReMan.u8Data[9]          = tSearch.entry.LrnDev.General.u3Bit;
    pRadio->Telegram.ReMan.u8Data[10]         = tSearch.entry.LrnDev.General.u3OutMode;

    pRadio->Param.ReMan.u32DestinationId      = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId           = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 添加学习条目 0x330
  */
RM_RETURN_TYPE EnOceanReManAddLearnDev2Tab_330(Radio_Typedef *pRadio,uint8_t u8ChannelMax,uint8_t u8Channel,uint8_t u8BuffChannel)
{
    ID_SEARCH_TYPE tSearch;
    uint8_t u8Status;

    u8Status = EnOceanReManDataBuff2LearnInfo(&pRadio->Telegram,&tSearch,u8ChannelMax,u8BuffChannel);

    // radio data process
    if ( 0 == u8Status )
    {
        tSearch.u8ChannelCheck          = LRN_SERACH;
        tSearch.u8Start                 = 0;
        if ( OK == EnOceanReManLearnDev2Tab(&tSearch) )
        {           
            EnOceanSaveLearnTabEvent();
            u8Status = RM_SUCCESS;
        }
        else
        {               
            u8Status = 0x01;
        }
    }

    pRadio->Telegram.ReMan.u16FnNum           = RM_RPC_ADD_LEARN_ADVANCED_ANS;
    pRadio->Telegram.ReMan.u16ManId           = ENOCEAN_MENRED_MAN_ID;
    
    pRadio->Telegram.ReMan.u8Length           = 11;
    pRadio->Telegram.ReMan.u8Data[0]          = u8Status;

    pRadio->Telegram.ReMan.u8Data[1]          = tSearch.entry.u32SrcId>>24;
    pRadio->Telegram.ReMan.u8Data[2]          = tSearch.entry.u32SrcId>>16;
    pRadio->Telegram.ReMan.u8Data[3]          = tSearch.entry.u32SrcId>> 8;
    pRadio->Telegram.ReMan.u8Data[4]          = tSearch.entry.u32SrcId&0xFF;
    pRadio->Telegram.ReMan.u8Data[5]          = tSearch.entry.u8EepRorg;
    pRadio->Telegram.ReMan.u8Data[6]          = tSearch.entry.u8EepFun;
    pRadio->Telegram.ReMan.u8Data[7]          = tSearch.entry.u8EepType;
    pRadio->Telegram.ReMan.u8Data[8]          = u8Channel;//tSearch.entry.LrnDev.General.u5Channel;
    pRadio->Telegram.ReMan.u8Data[9]          = tSearch.entry.LrnDev.General.u3Bit;
    pRadio->Telegram.ReMan.u8Data[10]         = tSearch.entry.LrnDev.General.u3OutMode;

    pRadio->Param.ReMan.u32DestinationId      = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId           = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None 
  */ 
RM_RETURN_TYPE EnOceanReManClearLearnIds(Radio_Typedef *pRadio)
{
    

    // radio data process

    //pRadio->Telegram.ReMan.u16FnNum      = RM_RPC_CLEAR_IDS_ANS;
    uint16_t u16RmFN;

    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;

    pRadio->Telegram.ReMan.u16ManId      = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length      = 4;
    pRadio->Telegram.ReMan.u8Data[0]     = 0x00;
    pRadio->Telegram.ReMan.u8Data[1]     = 0x00;
    pRadio->Telegram.ReMan.u8Data[2]     = 0x00;
    pRadio->Telegram.ReMan.u8Data[3]     = 0x00;    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
        
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    EnOceanClearLearnTabNums();

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManReadLearnIds(Radio_Typedef *pRadio,uint8_t u8LrnTabNums)
{
    uint16_t u16RmFN;

    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;
    //pRadio->Telegram.ReMan.u16FnNum = RM_RPC_READ_IDS_ANS;
    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 4;
    pRadio->Telegram.ReMan.u8Data[0]= u8LrnTabNums;
    pRadio->Telegram.ReMan.u8Data[1]= u8LrnTabNums;
    pRadio->Telegram.ReMan.u8Data[2]= u8LrnTabNums;
    pRadio->Telegram.ReMan.u8Data[3]= u8LrnTabNums;
    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None 
  */ 
RM_RETURN_TYPE EnOceanReManClearGateWayLearnIds(Radio_Typedef *pRadio,uint8_t u8SubAdd,uint8_t u8Channel)
{    
    uint16_t u16RmFN;    
    
    uint8_t u8ChannelLrnNums;
    
    if ( 0xFF == u8Channel )
    {
        u8ChannelLrnNums = EnOceanGetLearnTabNums();
        EnOceanClearLearnTabNums();
    }
    else
    {
        u8ChannelLrnNums = EnOceanGetLearnChannelTabNums(u8Channel);
        EnOceanDelChannelLearnInfoFromTab(u8Channel);
    }
    
    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;

    pRadio->Telegram.ReMan.u16ManId      = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length      = 4;
    pRadio->Telegram.ReMan.u8Data[0]     = u8SubAdd;
    pRadio->Telegram.ReMan.u8Data[1]     = u8Channel;
    pRadio->Telegram.ReMan.u8Data[2]     = 0x00;
    pRadio->Telegram.ReMan.u8Data[3]     = u8ChannelLrnNums;    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
        
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    EnOceanSaveLearnTabEvent();
    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManReadGatewayLearnIds(Radio_Typedef *pRadio,uint8_t u8SubAdd,uint16_t u16LrnTabNums)
{
    uint16_t u16RmFN;

    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;
    //pRadio->Telegram.ReMan.u16FnNum = RM_RPC_READ_IDS_ANS;
    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 4;
    pRadio->Telegram.ReMan.u8Data[0]= u8SubAdd;
    pRadio->Telegram.ReMan.u8Data[1]= pRadio->Telegram.ReMan.u8Data[1];
    pRadio->Telegram.ReMan.u8Data[2]= u16LrnTabNums>>8;
    pRadio->Telegram.ReMan.u8Data[3]= u16LrnTabNums&0xFF;
    
    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManWriteDevCfg(Radio_Typedef *pRadio)
{

    return RM_NO_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManReadDevCfg(Radio_Typedef *pRadio)
{    
    if(EnOceanReManCheckDestID(&pRadio->Param) == RM_NO_SUCCESS)
    {
        return RM_COMMAND_FLASH_READ_NO_SUCCESS;
    }    

    return RM_NO_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManResetDevAll(Radio_Typedef *pRadio)
{
    //pRadio->Telegram.ReMan.u16FnNum = RM_RPC_RESET_ALL_ANS;
    uint16_t u16RmFN;

    u16RmFN = pRadio->Telegram.ReMan.u16FnNum;
    // radio data process
    //Radio_Typedef RadioTx;
    pRadio->Telegram.ReMan.u16FnNum  = RM_ANSWER_START + u16RmFN;

    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 4;

    pRadio->Telegram.ReMan.u8Data[0]= 0x00;
    pRadio->Telegram.ReMan.u8Data[1]= 0x00;
    pRadio->Telegram.ReMan.u8Data[2]= 0x00;
    pRadio->Telegram.ReMan.u8Data[3]= 0x00;
    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    //EnOceanReManData2SerialBuff(pRadio,REMAN_RANDOM_DISABLE);

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManActive(Radio_Typedef *pRadio,uint8_t u8ChannelMax)
{
    /*
    if ( 0 == u8ChannelMax )
    {
        return RM_NO_SUCCESS;
    }
    */
    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  *
  */
RM_RETURN_TYPE EnOceanReManTestDevChannel(Radio_Typedef *pRadio,uint8_t u8Channel,uint8_t u8ChannelMax)
{
    
    if ( u8Channel < u8ChannelMax )
    {       
        return RM_SUCCESS;
    }
    return RM_NO_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManSecurityProcess(Radio_Typedef *pRadio)
{
    uint32_t u32Code;

    u32Code  = (uint32_t)pRadio->Telegram.ReMan.u8Data[0]<<24;
    u32Code |= (uint32_t)pRadio->Telegram.ReMan.u8Data[1]<<16;
    u32Code |= (uint32_t)pRadio->Telegram.ReMan.u8Data[2]<<8;
    u32Code |= (uint32_t)pRadio->Telegram.ReMan.u8Data[3];

    if ( RM_FN_UNLOCK == pRadio->Telegram.ReMan.u16FnNum )
    {
        if ( 0xFFFFFFFF == u32Code )
        {
            return RM_NO_SUCCESS;
        }

        // update the cfg
        if ( u32Code == *EnOceanRun.pu32RemanCode )
        {
            EnOceanRun.u8Lock = RM_UNLOCK;
            EnOceanRun.u32LockCount = RM_AUTO_LOCK_TIME*1000;
        }

        return RM_NO_SUCCESS;
    }
    // Set remote management security code
    // 设置远程管理安全密码
    else if ( RM_FN_SET_CODE == pRadio->Telegram.ReMan.u16FnNum )
    {
        // Check if the data field length is correct

        if ( 0xFFFFFFFF == u32Code )
        {
            return RM_NO_SUCCESS;
        }
        if ( !EnOceanRun.u8Lock )
        {
            *EnOceanRun.pu32RemanCode = u32Code;       
        }
        // Error. If a remote status telegram were received, this code will be returned.
        // reman_setError(RM_RETURN_CODE_RPC_FAILED);
        return RM_COMMAND_SET_CODE_NO_SUCCESS;
    }
    else if ( RM_FN_LOCK == pRadio->Telegram.ReMan.u16FnNum )
    {
        
        if ( *EnOceanRun.pu32RemanCode == u32Code )
        {
            EnOceanRun.u8Lock = RM_LOCK;            
        }
         
        return RM_NO_SUCCESS;
    }
    else
    {
        if ( EnOceanRun.u8Lock )
        {
            return RM_NO_SUCCESS;
        }
    }

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * Ping 命令 0x006
  */
RM_RETURN_TYPE EnOceanReManPingCommand(uint32_t u32EEP,Radio_Typedef *pRadio)
{
    uint8_t u8Rorg;
    uint8_t u8Fun;
    uint8_t u8Type;

    //u8Rorg = (uint8_t)(LEARN_LIGHT_EEP>>16);
    //u8Fun  = (uint8_t)(LEARN_LIGHT_EEP>> 8);
    //u8Type = (uint8_t)(LEARN_LIGHT_EEP&0xFF);

    u8Rorg = (u32EEP>>16)&0xFF;

    u8Fun  = (u32EEP>>8)&0xFF;
    u8Fun<<= 2;
    u8Fun |= (u32EEP&0x60)>>5;
    u8Type = (u32EEP&0xFF)<<3;

    pRadio->Telegram.ReMan.u16FnNum = RM_FN_PING_COMMAND_ANS;
    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 4;

    pRadio->Telegram.ReMan.u8Data[0]= u8Rorg;
    pRadio->Telegram.ReMan.u8Data[1]= u8Fun;
    pRadio->Telegram.ReMan.u8Data[2]= u8Type;
    pRadio->Telegram.ReMan.u8Data[3]= pRadio->Param.ReMan.u8Dbm;
    
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    //EnOceanReManData2SerialBuff(pRadio,REMAN_RANDOM_DISABLE);

    return RM_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 
  */
RM_RETURN_TYPE EnOceanReManGateWayResponseQueryID(uint32_t u32SearchEEP,Radio_Typedef *pRadio)
{
    // radio data process

    uint32_t u32EEP1;
    uint8_t u8Mask;

    uint8_t u8Rorg;
    uint8_t u8Fun;
    uint8_t u8Type;

    u8Mask = pRadio->Telegram.ReMan.u8Data[2]&0x07;

    u32EEP1 = (uint32_t)pRadio->Telegram.ReMan.u8Data[0]<<16;        
    u32EEP1|= (uint32_t)(pRadio->Telegram.ReMan.u8Data[1]<<6)&0x3F00;
    u32EEP1|= (uint32_t)(pRadio->Telegram.ReMan.u8Data[1]&0x03)<<5;
    u32EEP1|= ((uint32_t)pRadio->Telegram.ReMan.u8Data[2]&0xF8)>>3;

    u8Rorg = (u32SearchEEP>>16)&0xFF;

    u8Fun  = (u32SearchEEP>>8)&0xFF;
    u8Fun<<= 2;
    u8Fun |= (u32SearchEEP&0x60)>>5;
    u8Type = (u32SearchEEP&0xFF)<<3;

    pRadio->Telegram.ReMan.u8Length = 3;

    if (   ( u8Mask )
         &&( u32EEP1 == u32SearchEEP ) )
    {               
        // radio data process
        pRadio->Telegram.ReMan.u16FnNum = RM_FN_QUERY_ID_ANS;
        pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
        pRadio->Telegram.ReMan.u8Data[0]= u8Rorg;
        pRadio->Telegram.ReMan.u8Data[1]= u8Fun;
        pRadio->Telegram.ReMan.u8Data[2]= u8Type;
        pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
        pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
        pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_ENABLE;
        return RM_SUCCESS;
    }
    else if ( 0 == u8Mask ) 
    {               
        pRadio->Telegram.ReMan.u16FnNum = RM_FN_QUERY_ID_ANS;
        pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
        pRadio->Telegram.ReMan.u8Data[0]= u8Rorg;
        pRadio->Telegram.ReMan.u8Data[1]= u8Fun;
        pRadio->Telegram.ReMan.u8Data[2]= u8Type;
        pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
        pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
        pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_ENABLE;

        //EnOceanReManData2SerialBuff(pRadio,REMAN_RANDOM_ENABLE);
        return RM_SUCCESS;
    }

    return RM_NO_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 查询功能命令函数 0x007
  */
RM_RETURN_TYPE EnOceanReManQueryFunctionCommand(Radio_Typedef *pRadio,const uint16_t *pu16RpcCmd,uint8_t u8CmdMax)
{
    uint8_t i;
    uint16_t u16DataLength;

    if ( Esp3Tx.u8State != eTX_IDLE )
    {
        return RM_NO_SUCCESS;
    }

    u16DataLength    = u8CmdMax*2+4;

    Esp3Tx.u16ByteMax = 10+u16DataLength+7;

    if ( Esp3Tx.u16ByteMax > ESP3_TX_BUF_MAX )
    {
        return RM_NO_SUCCESS;
    }

    /* Header */
    /* Sync Byte */
    Esp3Tx.u8Buff[0] = 0x55;
    /* Data Length */
    Esp3Tx.u8Buff[1] = u16DataLength>>8;
    Esp3Tx.u8Buff[2] = u16DataLength&0xFF;
    /* Optional Length */
    Esp3Tx.u8Buff[3] = 10;
    /* Packet Type */
    Esp3Tx.u8Buff[4] = 0x07;
    /* CRC8 */
    Esp3Tx.u8Buff[5] = u8GetCrc8(Esp3Tx.u8Buff,1,4);

    /*  area */
    Esp3Tx.u8Buff[6] = 0x06;
    Esp3Tx.u8Buff[7] = 0x07;
    Esp3Tx.u8Buff[8] = 0x07;
    Esp3Tx.u8Buff[9] = 0xFF;

    for ( i = 0; i < u8CmdMax/2;i ++ )
    {
        Esp3Tx.u8Buff[i*4+10]= pu16RpcCmd[i*2]>>8;
        Esp3Tx.u8Buff[i*4+11]= pu16RpcCmd[i*2]&0xFF;
        Esp3Tx.u8Buff[i*4+12]= pu16RpcCmd[i*2+1]>>8;
        Esp3Tx.u8Buff[i*4+13]= pu16RpcCmd[i*2+1]&0xFF;
    }

    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    /* Optional  area */
    /* Send ID */
    Esp3Tx.u8Buff[ u16DataLength + 6 ] = (pRadio->Param.ReMan.u32DestinationId>>24)&0xFF;
    Esp3Tx.u8Buff[ u16DataLength + 7 ] = (pRadio->Param.ReMan.u32DestinationId>>16)&0xFF;
    Esp3Tx.u8Buff[ u16DataLength + 8 ] = (pRadio->Param.ReMan.u32DestinationId>> 8)&0xFF;
    Esp3Tx.u8Buff[ u16DataLength + 9 ] = (pRadio->Param.ReMan.u32DestinationId    )&0xFF;
    Esp3Tx.u8Buff[ u16DataLength + 10 ] = (pRadio->Param.ReMan.u32SourceId >> 24)&0xFF;
    Esp3Tx.u8Buff[ u16DataLength + 11 ] = (pRadio->Param.ReMan.u32SourceId >> 16)&0xFF;
    Esp3Tx.u8Buff[ u16DataLength + 12 ] = (pRadio->Param.ReMan.u32SourceId >>  8)&0xFF;
    Esp3Tx.u8Buff[ u16DataLength + 13 ] = (pRadio->Param.ReMan.u32SourceId      )&0xFF;

    Esp3Tx.u8Buff[ u16DataLength + 14 ] = 0xFF;

    Esp3Tx.u8Buff[u16DataLength + 15] = REMAN_RANDOM_DISABLE;//pRadio->u8RandomEnable;
    Esp3Tx.u8RandomEn                 = 0;//pRadio->u8RandomEnable;
	/* Data and optional  crc8 */
    Esp3Tx.u8Buff[Esp3Tx.u16ByteMax - 1] = u8GetCrc8(Esp3Tx.u8Buff,6,u16DataLength + 10);
    Esp3Tx.u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    //EnOceanRun.u16SendPeriod               = 1000;
    return RM_NO_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  * 查询状态 0x008
  */
RM_RETURN_TYPE EnOceanReManQueryStatus(Radio_Typedef *pRadio)
{
    // radio data process

    pRadio->Telegram.ReMan.u16FnNum = RM_FN_QUERY_STATUS_ANS;
    pRadio->Telegram.ReMan.u16ManId = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length = 4;

    pRadio->Telegram.ReMan.u8Data[0]= 0x00;
    pRadio->Telegram.ReMan.u8Data[1]= 0x00;
    pRadio->Telegram.ReMan.u8Data[2]= 0x00;
    pRadio->Telegram.ReMan.u8Data[3]= 0x00;

    
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    pRadio->Param.ReMan.u32SourceId      = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u32DestinationId = EnOceanRun.u32DstID;
    //EnOceanReManData2SerialBuff(pRadio,REMAN_RANDOM_DISABLE);

    return RM_SUCCESS;
}

/* End of file */
