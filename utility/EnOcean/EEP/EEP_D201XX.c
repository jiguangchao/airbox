/*!
*****************************************************************
                        $Name$
                        $Revision: 27601 $
                        $Date: 2010-06-18 16:20:57 +0200 (Fr, 18 Jun 2010) $
    \file               
    \brief              
    \author             

    <b>Processor:</b>\n EO3000I\n\n
    <b>Company:</b>\n   EnOcean GmbH\n
****************************************************************
*/
#include "esp3_libCommon.h"
#include "esp3_radio.h"
#include "..\Learn/EnOceanLearn.h"
#include "..\Mix/EnOceanMix.h"
#include "EEP_D201XX.h"

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChannelNumMax(void)
{
    return EnOceanHardware.u8DOMaxNums;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_SettingsSaveNVM(IOProfile_Typedef *pIOProfile,uint8_t u8Channel)
{
    pIOProfile[u8Channel].u8DataUpdate  = 1;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_SetOneChannelCmdBy4BSPIR(ID_SEARCH_TYPE *pSearchOut,uint8_t *p8Data,IORun_Typedef *pIO)
{
    uint8_t        u8CmdFlag;
    
    uint8_t        u8Presence;
    uint8_t        u8Channel;
    uint8_t        u8ChannelMax;

    u8ChannelMax       = EEPD201XX_GetChannelNumMax();

    u8CmdFlag          = 0;
    u8Presence         = 0;
    u8Channel          = pSearchOut->entry.LrnDev.PIR.u5Channel;

    if ( u8Channel >= u8ChannelMax )
    {
        return !OK;
    }

    if ( ( pIO[u8Channel].u16LightOffDisableTime > 0 ) || (  pIO[u8Channel].u16LightOnDisableTime > 0 ) )
    {
         u8CmdFlag = 0;
    }
    else
    {
        if ( ( pSearchOut->entry.u8EepFun == 0x07 )&&(pSearchOut->entry.u8EepType == 0x01) )
        {
            if (p8Data[2] >= 128) 
            {
                u8Presence = 1;
            }
            u8CmdFlag = 1;
        }
        else if ( ( pSearchOut->entry.u8EepFun == 0x07 )&&(pSearchOut->entry.u8EepType == 0x02) )
        {
            if ( p8Data[3]&0x80 )
            {
                u8Presence = 1;
            }
            
            u8CmdFlag = 1;
        }
        else if ( ( pSearchOut->entry.u8EepFun == 0x07 )&&(pSearchOut->entry.u8EepType == 0x03) )
        {
            if ( p8Data[3]&0x80 )
            {
                u8Presence = 1;
            }
            
            u8CmdFlag = 1;
        }
    }

    if ( 0 == u8CmdFlag )
    {
        return !OK;
    }

    if (  ( LRN_REMOTE == pSearchOut->entry.LrnDev.PIR.u1LrnType )
        ||(LRN_MANUAL == pSearchOut->entry.LrnDev.PIR.u1LrnType) )
    {
        if ( MODE_CHANNEL_ONOFF == pSearchOut->entry.LrnDev.PIR.u2OutMode )
        {
            if (u8Presence)
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_ON;
            }
            else
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_OFF;
            }
            return OK;
        }
        else if ( MODE_CHANNEL_TOGGLE == pSearchOut->entry.LrnDev.PIR.u2OutMode )
        {
            /* Not support */
            return !OK;
        }
        else if ( MODE_CHANNEL_ON == pSearchOut->entry.LrnDev.PIR.u2OutMode )
        {
            if (u8Presence)
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_ON;
                return OK;
            }
        }
        else if ( MODE_CHANNEL_OFF == pSearchOut->entry.LrnDev.PIR.u2OutMode )
        {
            if (u8Presence)
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_OFF;
                return OK;
            }      
        }
    }
        
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_SetAllChannelCmdByPIR(Radio_Typedef *pRadio,IORun_Typedef *pIO   ,IOProfile_Typedef *pIOProfile)
{
    ID_SEARCH_TYPE SearchOut;
    ID_SEARCH_TYPE SearchIn;
    
    ID_LEARN_INFO LearnInfo;

    LearnInfo.u8Channel= 0;
    LearnInfo.u8Enable = RADIO_SERACH;
    LearnInfo.u8Key    = RPS_HIGH_4BIT;
    LearnInfo.u8Type   = LRN_MANUAL;

    if ( OK != EnOceanGetSearchLearnDataBy4BS(pRadio,&SearchIn,&LearnInfo) )
    {
        return;
    }

    while ( SearchIn.u8Start < EnOceanGetLearnTabNums() )
    {
        if ( ID_SUCCESS == EnOceanSearchLearnTab( &SearchIn,&SearchOut) )
        {
            if ( OK == EEPD201XX_SetOneChannelCmdBy4BSPIR(&SearchOut,pRadio->Telegram.raw.bytes,pIO) )
            {
                EEPD201XX_GetChanneAutoOffTime(SearchOut.entry.LrnDev.PIR.u5Channel,pIO,pIOProfile);
            }
            SearchIn.u8Start += 1;
            continue;
        }
        SearchIn.u8Start += 1;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_SetOnelChannelCmdBy1BS(ID_SEARCH_TYPE *pSearchOut,uint8_t u8Data,IORun_Typedef *pIO)
{
    uint8_t        u8Presence;
    uint8_t        u8Channel;
    uint8_t        u8ChannelMax;

    u8ChannelMax       = EEPD201XX_GetChannelNumMax();

    u8Presence = 0;
    u8Channel  = pSearchOut->entry.LrnDev.PIR.u5Channel;

    if ( pSearchOut->entry.u8EepFun != 0x00 )
    {
        return;
    }

    if ( pSearchOut->entry.u8EepType != 0x01 )
    {
        return;
    }

    if ( u8Channel >= u8ChannelMax )
    {
        return;
    }
    
    if ( u8Data == 0x09 )
    {
        u8Presence = 0;
    }
    else if ( u8Data == 0x08 )
    {
        u8Presence = 1;
    }

    if (  (LRN_REMOTE == pSearchOut->entry.LrnDev.IDR.u1LrnType)
        ||(LRN_MANUAL == pSearchOut->entry.LrnDev.IDR.u1LrnType) )
    {
        /* MACRO need redefine */
        if ( MODE_CHANNEL_ONOFF == pSearchOut->entry.LrnDev.IDR.u2OutMode )
        {
            if ( 0 == u8Presence )
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_OFF;
            }
            else if ( 1 == u8Presence )
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_ON;
            }
        }
        else if ( MODE_CHANNEL_TOGGLE == pSearchOut->entry.LrnDev.IDR.u2OutMode )
        {
            /* Not support */
        }
        else if ( MODE_CHANNEL_ON == pSearchOut->entry.LrnDev.IDR.u2OutMode )
        {
            if ( 1 == u8Presence )
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_ON;
            }
        }
        else if ( MODE_CHANNEL_OFF == pSearchOut->entry.LrnDev.IDR.u2OutMode )
        {
            if ( 1 == u8Presence )
            {
                pIO[u8Channel].eOutCmd = eCHANNEL_STATE_OFF;
            }
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_SetAllChannelCmdBy1BS(Radio_Typedef const *pRadio,IORun_Typedef *pIO)
{
    //! Indicates what channels have to be manipulated

    ID_SEARCH_TYPE SearchOut;
    ID_SEARCH_TYPE SearchIn;
    ID_LEARN_INFO LearnInfo;

    LearnInfo.u8Channel= 0;
    LearnInfo.u8Enable = RADIO_SERACH;
    LearnInfo.u8Key    = RPS_HIGH_4BIT;
    LearnInfo.u8Type   = LRN_MANUAL;

    if ( OK != EnOceanGetSearchLearnDataBy1BS(pRadio,&SearchIn,&LearnInfo) )
    {
        return;
    }

    while ( SearchIn.u8Start < EnOceanGetLearnTabNums() )
    {
        if ( ID_SUCCESS == EnOceanSearchLearnTab( &SearchIn,&SearchOut) )
        {
            EEPD201XX_SetOnelChannelCmdBy1BS(&SearchOut,pRadio->Telegram.raw.bytes[0],pIO);
        }
        SearchIn.u8Start += 1;
        
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetSensorDisableTimeByManual(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    // 20160806
    if ( pIOProfile[u8Channel].u1SensorDisable )
    {
        pIO[u8Channel].u1AutoOffState  = 0;
        pIO[u8Channel].u16AutoOff = 0;
        if ( pIO[u8Channel].eOutCmd == eCHANNEL_STATE_OFF )
        {
            pIO[u8Channel].u16LightOffDisableTime = pIOProfile[u8Channel].u16LightOffDisableTime;
            pIO[u8Channel].u16LightOnDisableTime  = 0;
        }
        else if ( pIO[u8Channel].eOutCmd == eCHANNEL_STATE_ON )
        {
            pIO[u8Channel].u16LightOnDisableTime  = pIOProfile[u8Channel].u16LightOnDisableTime;
            pIO[u8Channel].u16LightOffDisableTime = 0;
        }
        else if ( pIO[u8Channel].eOutCmd == eCHANNEL_STATE_IDLE )
        {
            if (pIO[u8Channel].u8ExeValue)
            {
                pIO[u8Channel].u16LightOffDisableTime = pIOProfile[u8Channel].u16LightOffDisableTime;
                pIO[u8Channel].u16LightOnDisableTime  = 0;
            }
            else
            {
                pIO[u8Channel].u16LightOnDisableTime  = pIOProfile[u8Channel].u16LightOnDisableTime;
                pIO[u8Channel].u16LightOffDisableTime = 0;
            }
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetRPSInfoForSearchLearnTab(IORun_Typedef *pIO,ID_SEARCH_TYPE *pSearchIn,ID_SEARCH_TYPE *pSearchOut)
{
    uint8_t        u8ChannelMax;

    u8ChannelMax       = EEPD201XX_GetChannelNumMax();

    while ( pSearchIn->u8Start < EnOceanGetLearnTabNums() )
    {
        if ( ID_SUCCESS != EnOceanSearchLearnTab( pSearchIn,pSearchOut) )
        {
            pSearchIn->u8Start += 1;
            continue;
        }

        if ( pSearchOut->entry.u8EepFun != PTM2XX_FUN )
        {
            pSearchIn->u8Start += 1;
            continue;
        }
        if ( pSearchOut->entry.u8EepType != PTM2XX_TYPE )
        {
            pSearchIn->u8Start += 1;
            continue;
        }
        if ( pSearchOut->entry.LrnDev.RPS.u5Channel >= u8ChannelMax )
        {
            pSearchIn->u8Start += 1;
            continue;
        }
        pSearchIn->u8Start += 1;

        /* Get the RPS infomation */
        pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u1RockProcess = 1;// dimmer
        pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u1LrnType     = pSearchOut->entry.LrnDev.RPS.u1LrnType;
        pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u2OutMode     = pSearchOut->entry.LrnDev.RPS.u2OutMode;
        pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u32ID         = pSearchIn->entry.u32SrcId;
        pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u3Key         = pSearchIn->entry.LrnDev.RPS.u3Key;
        /* !!!  For the Dimmer !!! */
        pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u16RockTime   = 0;// dimmer
        //pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u1ConfigSearch= 1;// dimmer
        /* !!! Must attention !!! */
        /* Search in data from radio telegram*/
        pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u2RockState   = pSearchIn->entry.LrnDev.RPS.u2KeyState;//dimmer

        if ( (pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u32ID == pSearchIn->entry.u32SrcId )&&
             (pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u3Key == pSearchIn->entry.LrnDev.RPS.u3Key) )
        {
            pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u16RedundacyTime = RPS_TOG_REDUNDACY_TIME;
        }
        else
        {
            pIO[pSearchOut->entry.LrnDev.RPS.u5Channel].u16RedundacyTime = 0;
        }        
    }
}
#if 1
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetRelayCmdByRPSInfo(IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    uint8_t     i;
    uint8_t     u8ChannelMax;

    u8ChannelMax       = EEPD201XX_GetChannelNumMax();

    for (i = 0; i < u8ChannelMax; i++)
    {
        if ( !pIO[i].u1RockProcess )
        {
            pIO[i].u16RockTime = 0;
            continue;
        }
        if ( eIO_RELAY != pIOProfile[i].u8Type )
        {
            continue;
        }
        if (MODE_CHANNEL_ONOFF == pIO[i].u2OutMode)
        {
            switch (pIO[i].u3Key) 
            {
            case EEP_F60201_ON_1:
            case EEP_F60201_ON_2:
                pIO[i].eOutCmd = eCHANNEL_STATE_ON;
                break;
            case EEP_F60201_OFF_1:
            case EEP_F60201_OFF_2:
                pIO[i].eOutCmd = eCHANNEL_STATE_OFF;
                break;
            }
        }
        else if ( MODE_CHANNEL_TOGGLE == pIO[i].u2OutMode )
        {
            //if ( !pIO[i].u16RedundacyTime )
            {
                pIO[i].eOutCmd = eCHANNEL_STATE_TOG;
            }
        }
        else if ( MODE_CHANNEL_ON == pIO[i].u2OutMode )
        {
            pIO[i].eOutCmd = eCHANNEL_STATE_ON;
        }
        else if ( MODE_CHANNEL_OFF == pIO[i].u2OutMode )
        {
            pIO[i].eOutCmd = eCHANNEL_STATE_OFF;
        }
        
        pIO[i].u3Key         = 0;

        pIO[i].u1RockProcess = 0;
        
        EEPD201XX_GetSensorDisableTimeByManual(i,pIO,pIOProfile);
    }
}
#endif
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChannelCmdByRPSLeftInfo(Radio_Typedef const *pRadio,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    //! Indicates what channels have to be manipulated
    
    ID_SEARCH_TYPE SearchOut;
    ID_SEARCH_TYPE SearchIn;
    ID_LEARN_INFO  LearnInfo;

    if ( PTM2XX_ROCK_PRESSED_STATUS == (pRadio->Telegram.raw.u8Status&PTM2XX_ROCK_PRESSED_STATUS) )
    {
        LearnInfo.u8Channel= 0;
        LearnInfo.u8Enable = RADIO_SERACH;
        LearnInfo.u8Key    = RPS_HIGH_4BIT;
        LearnInfo.u8Type   = LRN_MANUAL;
        if ( OK == EnOceanGetSearchLearnDataByRPSLeft(pRadio,&SearchIn,&LearnInfo) )
        {
            EEPD201XX_GetRPSInfoForSearchLearnTab(pIO,&SearchIn,&SearchOut);
            /* Only for the channel change the on/off */
            EEPD201XX_GetRelayCmdByRPSInfo(pIO,pIOProfile);

            return OK;
        }
        
        //Dimmer_RockSetConfigStateByRPS(pRadio->Telegram.raw.bytes[0],pRadio->Param.p_rx.u32SourceId,pIO,pIOProfile,Dev.u8OutNums);
    }
    
    return !OK; 
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChannelCmdByRPSRightInfo(Radio_Typedef const *pRadio,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    //! Indicates what channels have to be manipulated
    
    ID_SEARCH_TYPE SearchOut;
    ID_SEARCH_TYPE SearchIn;
    ID_LEARN_INFO  LearnInfo;

    if ( PTM2XX_ROCK_PRESSED_STATUS == (pRadio->Telegram.raw.u8Status&PTM2XX_ROCK_PRESSED_STATUS) )
    {
        LearnInfo.u8Channel= 0;
        LearnInfo.u8Enable = RADIO_SERACH;
        LearnInfo.u8Key    = RPS_LOW_4BIT;
        LearnInfo.u8Type   = LRN_MANUAL;
        if ( OK == EnOceanGetSearchLearnDataByRPSRight(pRadio,&SearchIn,&LearnInfo) )
        {
            EEPD201XX_GetRPSInfoForSearchLearnTab(pIO,&SearchIn,&SearchOut);
            /* Only for the channel change the on/off */
            EEPD201XX_GetRelayCmdByRPSInfo(pIO,pIOProfile);

            //if ( eIO_RELAY == pIOProfile[SearchOut.u8Start].u8Type )
            //{
                /* Only for the channel change the on/off */
                //EEPD201XX_GetRelayCmdByRPSInfo(pIO,pIOProfile);
            //}
            return OK;
        }
    }
    
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetChanneByRPSReleaseInfo(Radio_Typedef const *pRadio,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    uint8_t u8Channel;
    uint8_t u8ChannelMax;

    u8ChannelMax = EEPD201XX_GetChannelNumMax();

    if ( PTM2XX_ROCK_RELEASE_STATUS == (pRadio->Telegram.raw.u8Status&PTM2XX_ROCK_PRESSED_STATUS) ) //
    {
        for ( u8Channel = 0;u8Channel < u8ChannelMax;u8Channel++ )
        {
            if ( eIO_DIMMING != pIOProfile[u8Channel].u8Type )
            {
                continue;
            }
            if ( pIO[u8Channel].u32ID == pRadio->Param.p_rx.u32SourceId )
            {
                pIO[u8Channel].u2RockState   = eRPS_ROCK_RELEASE; 
            }
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_GetChanneCmdByVLDInfo(Radio_Typedef const *pRadio)
{
    //! Indicates what channels have to be manipulated

    ID_SEARCH_TYPE SearchOut;
    ID_SEARCH_TYPE SearchIn;
    ID_LEARN_INFO LearnInfo;

    LearnInfo.u8Channel= 0;
    LearnInfo.u8Enable = RADIO_SERACH;
    LearnInfo.u8Key    = RPS_HIGH_4BIT;
    LearnInfo.u8Type   = LRN_MANUAL;

    if ( OK == EnOceanGetSearchDataByUTEOrVLDTelRadio(pRadio,&SearchIn,&LearnInfo) )
    {
        while ( SearchIn.u8Start < EnOceanGetLearnTabNums() )
        {
            if ( ID_SUCCESS == EnOceanSearchLearnTab( &SearchIn,&SearchOut) )
            {
                return OK;
            }

            SearchIn.u8Start += 1;
        }
    }

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_GetChanneAutoOffTime(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    if ( ( 0 < pIOProfile[u8Channel].u16AutoOff )&&(pIOProfile[u8Channel].u16AutoOff < 0xFFFF) )
    {
        pIO[u8Channel].u16AutoOff = pIOProfile[u8Channel].u16AutoOff;
    }
    else
    {
        pIO[u8Channel].u16AutoOff = PIR_LEARN_NO_KEY_TIME_DELAY_DEFAULT;
    }
}
/**
  * @brief
  * @param
  * @retval
  */
uint8_t EEPD201XX_GetChanneAutoOffValue(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    if ( !pIO[u8Channel].u1AutoOffState )
    {
        if ( (0 < pIOProfile[u8Channel].u16AutoOff)&&(pIOProfile[u8Channel].u16AutoOff < 0xFFFF) )
        {
            pIO[u8Channel].u1AutoOffState  = 1;
            pIO[u8Channel].u16AutoOff = pIOProfile[u8Channel].u16AutoOff;
        }
        else if ( pIO[u8Channel].u16AutoOff )
        {
            pIO[u8Channel].u1AutoOffState  = 1;
        }
        
        pIO[u8Channel].u8OutValue       = pIO[u8Channel].u8ExeValue;
        
    }
    else //if ( 1 == pIO[u8Channel].u1AutoOffState )
    {
        if ( !pIO[u8Channel].u16AutoOff )
        {
            pIO[u8Channel].u1AutoOffState = 0;
            pIO[u8Channel].u8ExeValue     = 0;
            pIO[u8Channel].u8OutValue     = 0;
            return OK;
        }
    }
    
    pIO[u8Channel].u16OffDelay     = 0;
    pIO[u8Channel].u1OffDelayState = 0;

    return !OK;
}
/**
  * @brief
  * @param
  * @retval
  */
uint8_t EEPD201XX_GetChanneOffDelayValue(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    if ( !pIO[u8Channel].u1OffDelayState )
    {
        if ( (0 < pIOProfile[u8Channel].u16OffDelay)&&(pIOProfile[u8Channel].u16OffDelay < 0xFFFF) )
        {
            pIO[u8Channel].u1OffDelayState = 1;
            pIO[u8Channel].u16OffDelay     = pIOProfile[u8Channel].u16OffDelay;
        }
        else
        {
            pIO[u8Channel].u8OutValue     = pIO[u8Channel].u8ExeValue;
        }
    }
    else //if ( 1 == pIO[u8Channel].u1OffDelayState )
    {
        if ( !pIO[u8Channel].u16OffDelay )
        {
            pIO[u8Channel].u1OffDelayState = 0;
            pIO[u8Channel].u8ExeValue      = 0;
            pIO[u8Channel].u8OutValue      = 0;
            return OK;
        }
    }
    pIO[u8Channel].u16AutoOff = 0;
    pIO[u8Channel].u1AutoOffState = 0;

    return !OK;
}
/**
  * @brief
  * @param
  * @retval
  */
uint8_t EEPD201XX_GetChannelAutoOffAndDelayOff(uint8_t u8Channel,IORun_Typedef *pIO,IOProfile_Typedef *pIOProfile)
{
    if ( eIO_DIMMING == pIOProfile[u8Channel].u8Type )
    {
        /* If Dimmer is busy , disable the autooff and delay off funtion */
        /*
        if ( pIO[u8Channel].eOutCmd )
        {
            pIO[u8Channel].u8OutValue     = pIO[u8Channel].u8ExeValue;
            return;
        }
        */
        if ( pIO[u8Channel].u8ExeValue )
        {
            return EEPD201XX_GetChanneAutoOffValue(u8Channel,pIO,pIOProfile);
        }
        else
        {
            return EEPD201XX_GetChanneOffDelayValue(u8Channel,pIO,pIOProfile);
        }   
    }
    /* default channel type is relay*/
    else
    {
        if ( pIO[u8Channel].u8ExeValue )
        {
            return EEPD201XX_GetChanneAutoOffValue(u8Channel,pIO,pIOProfile);
        }
        else
        {
            return EEPD201XX_GetChanneOffDelayValue(u8Channel,pIO,pIOProfile);
        }
    }

    //return !OK;
}
/******************************************************************************************************************************/
/******************************************************************************************************************************/
/******************************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_ReceiveAndResponse(Radio_Typedef *pRadio,IOProfile_Typedef *pIOProfile,IORun_Typedef *pIO)
{
    uint8_t u8Cmd;
    uint8_t u8I;
    //uint8_t u8Status;
    uint8_t u8Channel;
    uint8_t u8ChannelMax;

    //EnoceanTxContent_Typedef QueueSend;
    uint32_t u32EnOceanBaseID;
    uint32_t u32EnOceanChipID;

    EnOceanGetHWBaseID  ( &u32EnOceanBaseID );
    EnOceanGetHWChipID  ( &u32EnOceanChipID );

    u8ChannelMax = EEPD201XX_GetChannelNumMax();

    u8Cmd        = pRadio->Telegram.raw.bytes[0]&0x0F;
    u8Channel    = pRadio->Telegram.raw.bytes[1] & 0x1F;

    //u8Status = !OK;

    switch (u8Cmd)
    {
    case 0x01:
        if (0x1E == u8Channel)
        {
            for ( u8I = 0; u8I < u8ChannelMax; u8I++ )
            {
                EEPD201XX_ActuatorSetOutputCmd_01(pRadio->Telegram.raw.bytes,u8I,pIOProfile,pIO);
            }
        }
        else if (u8Channel < u8ChannelMax)
        {
            EEPD201XX_ActuatorSetOutputCmd_01(pRadio->Telegram.raw.bytes,u8Channel,pIOProfile,pIO);
        }
        else if (0x1F == u8Channel)
        {
        }
        break;

    case 0x02:
        if (0x1E == u8Channel)
        {
            for ( u8I = 0; u8I < u8ChannelMax; u8I++ )
            {
                EEPD201XX_ActuatorSetLocal_02(pRadio->Telegram.raw.bytes,u8I,pIOProfile) ;
                EEPD201XX_SettingsSaveNVM(pIOProfile,u8I);
            }
        }
        else if (u8Channel < u8ChannelMax)
        {
            EEPD201XX_ActuatorSetLocal_02(pRadio->Telegram.raw.bytes,u8Channel,pIOProfile) ;
            EEPD201XX_SettingsSaveNVM(pIOProfile,u8Channel);
        }
        else if (0x1F == u8Channel)
        {
        }
        break;

    case 0x03:
        // query status
        if (0x1E == u8Channel)
        {
            for ( u8I = 0; u8I < u8ChannelMax; u8I++ )
            {
                EEPD201XX_ActuatorQueryStatusResponse_04(pRadio->Telegram.raw.bytes, u8I, pIOProfile, pIO, pIO[u8I].u8OutValue);
                EnOceanVLDRadioData(pRadio,3,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
            }
        }
        else if (u8Channel <= u8ChannelMax)
        {
            EEPD201XX_ActuatorQueryStatusResponse_04(pRadio->Telegram.raw.bytes, u8I, pIOProfile, pIO, pIO[u8I].u8OutValue);
            EnOceanVLDRadioData(pRadio,3,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
        }
        else if (0x1F == u8Channel)
        {
        }
        break;

    case 0x0B:
        if (0x1E == u8Channel)
        {
            for ( u8I = 0; u8I < u8ChannelMax ; u8I++ )
            {
                EEPD201XX_ActuatorSetExternalInterfaceSettingsCmd_0B(pRadio->Telegram.raw.bytes,u8I,pIOProfile);
                EEPD201XX_SettingsSaveNVM(pIOProfile,u8I);

                EEPD201XX_ActuatorExternalInterfaceSettingsResponseCmd_0D(pRadio->Telegram.raw.bytes,u8I,pIOProfile);
                EnOceanVLDRadioData(pRadio,7,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
            }
        }
        else if (u8Channel < u8ChannelMax)
        {
            EEPD201XX_ActuatorSetExternalInterfaceSettingsCmd_0B(pRadio->Telegram.raw.bytes,u8Channel,pIOProfile);
            EEPD201XX_SettingsSaveNVM(pIOProfile,u8Channel);

            EEPD201XX_ActuatorExternalInterfaceSettingsResponseCmd_0D(pRadio->Telegram.raw.bytes,u8Channel,pIOProfile);
            EnOceanVLDRadioData(pRadio,7,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
        }
        else if (0x1F == u8Channel)
        {
        }
        break;

    case 0x0C:
        // get response info for the next send message
        if ( 0x1E == u8Channel )
        {
            for ( u8I = 0; u8I < u8ChannelMax ; u8I++ )
            {
                EEPD201XX_ActuatorExternalInterfaceSettingsResponseCmd_0D(pRadio->Telegram.raw.bytes,u8I,pIOProfile);
                EnOceanVLDRadioData(pRadio,7,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
            }
        }
        else if (u8Channel < u8ChannelMax)
        {
            EEPD201XX_ActuatorExternalInterfaceSettingsResponseCmd_0D(pRadio->Telegram.raw.bytes,u8I,pIOProfile);
            EnOceanVLDRadioData(pRadio,7,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
        }
        else if (0x1F == u8Channel)
        {
        }
        break;
    case 0x0F:
        if ( OK == EEPD201XX_ActuatorExtendFunctionCmd_0F(pRadio->Telegram.raw.bytes,u8ChannelMax,pIOProfile) )
        {
            EnOceanVLDRadioData(pRadio,5,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
        }
        break;
    default:
        u8Cmd = 0;
        break;
    }
    return u8Cmd;
}

/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetOutputCmd_01(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile,IORun_Typedef *pIO)
{
    uint8_t eOutCmd;

    pIO[u8Channel].u8NeedProcess = 1;

    if ( eIO_RELAY == pIOProfile[u8Channel].u8Type )
    {
        if ( ( p8Data[2]&0x7F ) )
        {
            pIO[u8Channel].eOutCmd = eCHANNEL_STATE_ON;
        }
        else
        {
            pIO[u8Channel].eOutCmd = eCHANNEL_STATE_OFF;
        }
        // Reset pir sensor disable time
        if ( pIOProfile[u8Channel].u1SensorDisable )
        {
            if ( pIO[u8Channel].eOutCmd == eCHANNEL_STATE_OFF )
            {
                pIO[u8Channel].u16LightOffDisableTime = pIOProfile[u8Channel].u16LightOffDisableTime;
                pIO[u8Channel].u16LightOnDisableTime  = 0;
            }
            else if ( pIO[u8Channel].eOutCmd == eCHANNEL_STATE_ON )
            {
                pIO[u8Channel].u16LightOnDisableTime  = pIOProfile[u8Channel].u16LightOnDisableTime;
                pIO[u8Channel].u16LightOffDisableTime = 0;
            }
        }
    }
    else if ( eIO_DIMMING == pIOProfile[u8Channel].u8Type )
    {
        pIO[u8Channel].u8ExeValue = p8Data[2];
        pIO[u8Channel].eOutCmd    = eCMD_DIMMING_SET_LUX;
        
        /* */
        eOutCmd = p8Data[1]&0xE0;
        eOutCmd >>= 5;
        if (eOutCmd == 0x00 )
        {
            pIOProfile[u8Channel].Dimmer.u8Time = 0;
        }
        else if ( eOutCmd == 0x01 )
        {
            pIOProfile[u8Channel].Dimmer.u8Time = pIOProfile[u8Channel].Dimmer.u8DimmerTim1;
        }
        else if ( eOutCmd == 0x02 )
        {
            pIOProfile[u8Channel].Dimmer.u8Time = pIOProfile[u8Channel].Dimmer.u8DimmerTim2;
        }
        else if ( eOutCmd == 0x03 )
        {
            pIOProfile[u8Channel].Dimmer.u8Time = pIOProfile[u8Channel].Dimmer.u8DimmerTim3;
        }
        else
        {
            pIO[u8Channel].eOutCmd             = eCHANNEL_STATE_IDLE;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetLocal_02(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile)
{
    if ( eIO_DIMMING == pIOProfile[u8Channel].u8Type )
    {
        pIOProfile[u8Channel].u1TaughtInDevs             = (p8Data[0]&0x80)>>7;
        pIOProfile[u8Channel].u1LocalControl             = (p8Data[1]&0x20)>>5;
        pIOProfile[u8Channel].Dimmer.u8DimmerTim1        = p8Data[3]&0x0F;
        pIOProfile[u8Channel].Dimmer.u8DimmerTim2        = (p8Data[2]&0xF0)>>4;
        pIOProfile[u8Channel].Dimmer.u8DimmerTim3        = (p8Data[2]&0x0F)   ;
        pIOProfile[u8Channel].u1UserInterfaceIndication  = (p8Data[3]&0x80)>>7;       
        pIOProfile[u8Channel].u2DefaultState             = (p8Data[3]&0x30)>>4;
    }
    else
    {
        pIOProfile[u8Channel].u1TaughtInDevs             = (p8Data[0]&0x80)>>7;

        pIOProfile[u8Channel].u1LocalControl             = (p8Data[1]&0x20)>>5;
        pIOProfile[u8Channel].Dimmer.u8DimmerTim1        = 0;
        pIOProfile[u8Channel].Dimmer.u8DimmerTim2        = 0;
        pIOProfile[u8Channel].Dimmer.u8DimmerTim3        = 0;
        pIOProfile[u8Channel].u1UserInterfaceIndication  = (p8Data[3]&0x80)>>7;
        pIOProfile[u8Channel].u2DefaultState             = (p8Data[3]&0x30)>>4;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorQueryStatusResponse_04(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile,IORun_Typedef *pIO,uint8_t u8Value)
{
    if ( eIO_DIMMING == pIOProfile[u8Channel].u8Type )
    {
        p8Data[0]  = 0x00;//pIOProfile[u8Channel].u1PowerFailure<<7;
        p8Data[0] |= 0x00;//pIOProfile[u8Channel].u1PowerFailureDetection<<6;
        p8Data[0] |= 0x04;

        p8Data[1]  = 0;
        p8Data[1] |= pIO[u8Channel].u2ErrorLevel<<6;
        p8Data[1] |= u8Channel;

        p8Data[2]  = 0;
        p8Data[2] |= pIOProfile[u8Channel].u1LocalControl<<7;
        p8Data[2] |= u8Value;//pIO[u8Channel].Dimmer.u8Value;
    }
    else
    {
        p8Data[0]  = 0x00;//pIOProfile[u8Channel].u1PowerFailure<<7;
        p8Data[0] |= 0x00;//pIOProfile[u8Channel].u1PowerFailureDetection<<6;
        p8Data[0] |= 0x04;

        p8Data[1]  = 0;
        p8Data[1] |= pIO[u8Channel].u2ErrorLevel<<6;
        p8Data[1] |= u8Channel;

        p8Data[2]  = 0;
        p8Data[2] |= pIOProfile[u8Channel].u1LocalControl<<7;
        p8Data[2] |= u8Value;//pIO[u8Channel].u8ExeValue;//pIO[u8Channel].u8OutValue;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetExternalInterfaceSettingsCmd_0B(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile)
{
    pIOProfile[u8Channel].u16AutoOff               = (uint16_t)p8Data[2]<<8 | (uint16_t)p8Data[3]            ;       //
    pIOProfile[u8Channel].u16OffDelay              = (uint16_t)p8Data[4]<<8 | (uint16_t)p8Data[5]            ;       //
    pIOProfile[u8Channel].u2ExternalPushButton     = (p8Data[6]&0xC0)>>6;
    pIOProfile[u8Channel].u1State2Switch           = (p8Data[6]&0x20)>>5;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorExternalInterfaceSettingsResponseCmd_0D(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile)
{
    p8Data[0] = 0x0D;
    p8Data[1] = u8Channel;

    p8Data[2] = pIOProfile[u8Channel].u16AutoOff>>8;
    p8Data[3] = pIOProfile[u8Channel].u16AutoOff&0xFF;
    p8Data[4] = pIOProfile[u8Channel].u16OffDelay>>8;
    p8Data[5] = pIOProfile[u8Channel].u16OffDelay&0xFF;
    p8Data[6] = 0;
    p8Data[6]|= pIOProfile[u8Channel].u2ExternalPushButton<<6;
    p8Data[6]|= pIOProfile[u8Channel].u1State2Switch<<5;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_ActuatorExtendFunctionCmd_0F(uint8_t *p8Data,uint8_t u8ChannelMax,IOProfile_Typedef *pIOProfile)
{
    uint8_t u8I;
    uint8_t u8Channel;

    //EnoceanTxContent_Typedef QueueSend;

    if ( ( p8Data[0]&0x0F ) != 0x0F)
    {
        return !OK;
    }
    //u8Channel = (p8Data[2]&0xF8)>>3;

    u8Channel = p8Data[2]>>3;
    
    /* Write */
    if ( p8Data[1] == 0x00)
    {
        if (0x1E == u8Channel)
        {
            for ( u8I = 0; u8I < u8ChannelMax ;u8I ++)
            {
                if ( eIO_DIMMING != pIOProfile[u8I].u8Type )
                {
                    continue;
                }
                EEPD201XX_ActuatorSetDimmingLimitsCmd_0F00(p8Data,u8I,pIOProfile);               
                EEPD201XX_SettingsSaveNVM(pIOProfile,u8I);
            }
        }
        else if (u8Channel < u8ChannelMax)
        {
            if ( eIO_DIMMING != pIOProfile[u8Channel].u8Type )
            {
                return !OK;
            }
            EEPD201XX_ActuatorSetDimmingLimitsCmd_0F00(p8Data,u8Channel,pIOProfile);
            EEPD201XX_SettingsSaveNVM(pIOProfile,u8Channel);
        }
        else
        {
            return !OK;
        }
    }

    /* Query channel infomation , and push the data to queue */
    if ( ( p8Data[1] == 0x01)||( p8Data[1] == 0x00) )
    {
        if (0x1E == u8Channel)
        {
            for ( u8I = 0; u8I < u8ChannelMax ;u8I ++)
            {
                if ( eIO_DIMMING != pIOProfile[u8I].u8Type )
                {
                    continue;
                }
                
                return EEPD201XX_ActuatorDimmingLimitsResponseCmd_0F02(p8Data,u8I,pIOProfile);
            }
        }
        else if (u8Channel < u8ChannelMax)
        {
            if ( eIO_DIMMING != pIOProfile[u8Channel].u8Type )
            {
                return !OK;
            }
            
            return EEPD201XX_ActuatorDimmingLimitsResponseCmd_0F02(p8Data,u8I,pIOProfile);
            //EnOceanVLDRadioData(&Radio,5,u32EnOceanBaseID,ENOCEAN_BROADCAST_ID);
        }
    }
    
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorSetDimmingLimitsCmd_0F00(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile)
{
    if ( (p8Data[3]&0x7F) <= (p8Data[4]&0x7F) )
    {
        return;
    }

    pIOProfile[u8Channel].Dimmer.u7LimitMax = p8Data[3]&0x7F;
    if ( pIOProfile[u8Channel].Dimmer.u7LimitMax > 100 )
    {
        pIOProfile[u8Channel].Dimmer.u7LimitMax = 100;
    }

    pIOProfile[u8Channel].Dimmer.u7LimitMin = p8Data[4]&0x7F;
    if ( pIOProfile[u8Channel].Dimmer.u7LimitMin > 99 )
    {
        pIOProfile[u8Channel].Dimmer.u7LimitMin = 0;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EEPD201XX_ActuatorDimmingLimitsQueryCmd_0F01(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile)
{
    
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EEPD201XX_ActuatorDimmingLimitsResponseCmd_0F02(uint8_t *p8Data,uint8_t u8Channel,IOProfile_Typedef *pIOProfile)
{
    p8Data[0] = 0x0F;
    p8Data[1] = 0x02;
    p8Data[2] = u8Channel<<3;
    p8Data[3] = pIOProfile[u8Channel].Dimmer.u7LimitMax;
    p8Data[4] = pIOProfile[u8Channel].Dimmer.u7LimitMin;    

    return OK;
}

// ***************************** END ID_SEARCH_CHANNELS *******************
