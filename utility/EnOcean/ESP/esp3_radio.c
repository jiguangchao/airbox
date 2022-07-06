/*!
*****************************************************************
                        $Name$
                        $Revision: 27601 $
                        $Date: 2015-03-02 16:20:57 +0200 (Fr, 18 Jun 2010) $
    \file               Enocean_ESP.c
    \brief              MSG management related functions
    \author             zhoujinbang


    <b>Company:</b>\n	Menred GmbH\n

****************************************************************
*/
#include "esp3_common.h"
#include "esp3_radio.h"
#include "..\Mix/EnOceanMix.h"
//#include "SysError.h"

//EnOceanHw_Typedef       EnOceanHardware;
EnOceanRun_Typedef      EnOceanRun;

/************************************ ERP *************************************************/
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanRPSRadioData(Radio_Typedef *pRadio,uint8_t u8Status,uint32_t u32SrcID,uint32_t u32DstID)
{
    pRadio->u8PacketType                = PACKET_RADIO;
    
    pRadio->u16DataLength               = 7;//choice + user data + sender ID + status
    pRadio->u8OptionalDataLength        = 7;
    
    pRadio->Telegram.RPS.u8RORG         = RADIO_CHOICE_RPS;
    pRadio->Telegram.RPS.u8Status       = u8Status;
    
    //! number of subtelegrams to send
    pRadio->Param.p_tx.u8SubTelNum      = 3;
    pRadio->Param.p_tx.u32SourceId      = u32SrcID;
    //! to send Destination ID
    pRadio->Param.p_tx.u32DestinationId = u32DstID;
    pRadio->Param.p_tx.u8Dbm            = 0xFF;
    pRadio->Param.p_tx.u8SecurityLevel  = 0;
    //ESP3_RadioSendData2SerialBuff(pRadio);//
    EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,pRadio);
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOcean4BSRadioData(Radio_Typedef *pRadio,uint8_t u8Status,uint32_t u32SrcID,uint32_t u32DstID)
{
    pRadio->u8PacketType = PACKET_RADIO;

    pRadio->u16DataLength = 10;
    pRadio->u8OptionalDataLength = 7;
    
    pRadio->Telegram.raw.u8RORG = RADIO_CHOICE_4BS;
    pRadio->Telegram.raw.u8Status = u8Status;
    
    //! number of subtelegrams to send
    pRadio->Param.p_tx.u8SubTelNum = 3;
    pRadio->Param.p_tx.u32SourceId      = u32SrcID;
    //! to send Destination ID
    pRadio->Param.p_tx.u32DestinationId = u32DstID;
    pRadio->Param.p_tx.u8Dbm            = 0xFF;
    pRadio->Param.p_tx.u8SecurityLevel  = 0;
    EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,pRadio);
    
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOcean1BSRadioData(Radio_Typedef *pRadio,uint8_t u8Status,uint32_t u32SrcID,uint32_t u32DstID)
{
    pRadio->u8PacketType = PACKET_RADIO;

    pRadio->u16DataLength = 7;
    pRadio->u8OptionalDataLength = 7;
    
    pRadio->Telegram.raw.u8RORG = RADIO_CHOICE_1BS;
    pRadio->Telegram.raw.u8Status = u8Status;
    
    //! number of subtelegrams to send
    pRadio->Param.p_tx.u8SubTelNum = 3;
    pRadio->Param.p_tx.u32SourceId      = u32SrcID;
    //! to send Destination ID
    pRadio->Param.p_tx.u32DestinationId = u32DstID;
    pRadio->Param.p_tx.u8Dbm            = 0xFF;
    pRadio->Param.p_tx.u8SecurityLevel  = 0;
    EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,pRadio);
    
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanVLDRadioData(Radio_Typedef *pRadio,uint8_t u8Bytes,uint32_t u32SrcID,uint32_t u32DstID)
{
    pRadio->u8PacketType = PACKET_RADIO;
    
    pRadio->u16DataLength= u8Bytes+6;
    pRadio->u8OptionalDataLength = 7;
    
    pRadio->Telegram.raw.u8RORG = RADIO_CHOICE_VLD;
    pRadio->Telegram.raw.u8Status = 0x00;
    
    //! number of subtelegrams to send
    pRadio->Param.p_tx.u8SubTelNum = 3;
    //! to send Destination ID
    pRadio->Param.p_tx.u32SourceId      = u32SrcID;
    pRadio->Param.p_tx.u32DestinationId = u32DstID;
    pRadio->Param.p_tx.u8Dbm            = 0xFF;
    pRadio->Param.p_tx.u8SecurityLevel  = 0;
    //ESP3_RadioSendData2SerialBuff(pRadio);//
    EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,pRadio);
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanMSCRadioData(Radio_Typedef *pRadio,uint8_t u8Bytes,uint32_t u32SrcID,uint32_t u32DstID)
{
    pRadio->u8PacketType = PACKET_RADIO;

    pRadio->u16DataLength = u8Bytes + 6;
    pRadio->u8OptionalDataLength = 7;
    
    pRadio->Telegram.raw.u8RORG = RADIO_CHOICE_MSC;
    pRadio->Telegram.raw.u8Status = 0x00;

    //! number of subtelegrams to send
    pRadio->Param.p_tx.u8SubTelNum = 3;
    pRadio->Param.p_tx.u32SourceId      = u32SrcID;
    //! to send Destination ID
    pRadio->Param.p_tx.u32DestinationId = u32DstID;
    pRadio->Param.p_tx.u8Dbm            = 0xFF;
    pRadio->Param.p_tx.u8SecurityLevel  = 0;
    EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,pRadio);
    
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanUTERadioData(Radio_Typedef *pRadio,uint32_t u32SrcID)
{
    pRadio->u8PacketType = PACKET_RADIO;

    pRadio->u16DataLength        = 13;
    pRadio->u8OptionalDataLength = 7;
    
    pRadio->Telegram.raw.u8RORG = RADIO_CHOICE_UTE;
    pRadio->Telegram.raw.u8Status = 0x00;
    
    //! number of subtelegrams to send
    pRadio->Param.p_tx.u8SubTelNum = 3;
    //! to send Destination ID
    pRadio->Param.p_tx.u32SourceId      = u32SrcID;
    pRadio->Param.p_tx.u32DestinationId = ENOCEAN_BROADCAST_ID;
    pRadio->Param.p_tx.u8Dbm            = 0xFF;
    pRadio->Param.p_tx.u8SecurityLevel  = 0;

    EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,pRadio);
    return OK;
    //return ESP3_RadioSendData2SerialBuff(pRadio);
}
/************************** Remote mangement start *****************************************/
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t EnOceanReManData2SerialBuff(Radio_Typedef *pRadio,uint8_t u8RandomEn)
{
    //uint32_t u32Id;
    pRadio->u8PacketType = PACKET_REMOTE_MAN_COMMAND;

    //pRadio->u16DataLength = u8ReManBytes+4;
    pRadio->u16DataLength = pRadio->Telegram.ReMan.u8Length+4;
    pRadio->u8OptionalDataLength = 10;

    //u32Id = pRadio->Param.ReMan.u32DestinationId;
    //pRadio->Param.ReMan.u32DestinationId = pRadio->Param.ReMan.u32SourceId;
    //! to send Destination ID
    pRadio->Param.ReMan.u32SourceId = EnOceanRun.u32ChipID;//pRadio->Param.ReMan.u32DestinationId; //u32Id;

    //!
    pRadio->Param.ReMan.u8Dbm       = 0xFF;
    pRadio->Param.ReMan.u8RandSendDelayEnable = u8RandomEn;    
    
    ESP3_ReManData2SerialBuff(pRadio,&Esp3Tx);
    pRadio->Param.ReMan.u8RandSendDelayEnable = 0;
    
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanTime_100us(void)
{
    if ( Esp3Rx.u8BusyTime )
    {
        Esp3Rx.u8BusyTime--;        
    }   
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanTime_1ms(void)
{    
    if ( Esp3Tx.u16OvfCnt )
    {
        Esp3Tx.u16OvfCnt--;
    }
    if ( Esp3Tx.u16IdleTime )
    {
        Esp3Tx.u16IdleTime--;
    }   
    if ( EnOceanRun.u16SendPeriod )
    {
        EnOceanRun.u16SendPeriod --;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanTime_100ms(void)
{
    if ( EnOceanRun.u16LockCount )
    {
        EnOceanRun.u16LockCount--;
    }
    else
    {
        EnOceanRun.u8Lock = RM_LOCK;
    }
}
/**
  * @brief
  * @param
  * @retval None
*/
void EnOceanWriteRepeater(void)
{
    uint8_t u8Repeater;

    u8Repeater = *EnOceanRun.pu8Reapter;

    ESP3_WriteReapter(&Esp3Tx,  u8Repeater);
}
/**
  * @brief
  * @param
  * @retval None
*/
void EnOceanReadRepeater(void)
{
    ESP3_ReadReapter(&Esp3Tx);
}
/**
  * @brief
  * @param
  * @retval None
*/
void EnOceanReadBseeID(void)
{
    ESP3_ReadBaseID(&Esp3Tx);
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_PushData2Queue(eEnOceanRUN_TYPE eCmd,Radio_Typedef *pRadio)
{
    if ( OK == EnOcean_GetSendQueuePushID() )
    {
        EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PushCount].u8Cmd = eCmd;
        if ( pRadio != NULL )
        {
            EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PushCount].Data  = *pRadio;
        }
        EnOcean_SetSendQueueIDOccupy();
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ClearSendQueuePopID(void)
{
    EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PopCount].u8State = 0;

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetSendQueuePopID(void)
{
    uint8_t i;
    uint8_t j;

    EnOcean_GetSendQueueFull();
    j = EnOceanRun.Tx.u8PopCount;

    /*  Search the current id to the queue Max */
    for (i = j+1; i < ESP3_TX_QUEUE;i++)
    {
        if ( 0 == EnOceanRun.Tx.Queue[i].u8State ) 
        {
            continue;
        }

        EnOceanRun.Tx.u8PopCount = i;
        return OK;       
    }
    
    /* Search the start 0 to the current id */
    for (i = 0; i <= j; i++)
    {
        if ( 0 == EnOceanRun.Tx.Queue[i].u8State ) 
        {                
            continue;  
        }

        EnOceanRun.Tx.u8PopCount = i;
        return OK;
    }

    //Esp3Rx.u8PopCount = 0;

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetSendQueueFull(void)
{
    uint8_t i;

    for (i = 0; i < ESP3_TX_QUEUE;i++)
    {
        if ( 0 == EnOceanRun.Tx.Queue[i].u8State )
        {
            EnOceanRun.Tx.u8QueueFull = 0;
        }
    }

    return EnOceanRun.Tx.u8QueueFull;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetSendQueuePushID(void)
{
    uint8_t i;
    uint8_t j;

    if ( EnOcean_GetSendQueueFull() )
    {
        return !OK;
    }
    j = EnOceanRun.Tx.u8PushCount;

    /*  Search the current id to the queue Max */
    for (i = j+1; i < ESP3_TX_QUEUE;i++)
    {
        if ( 1 == EnOceanRun.Tx.Queue[i].u8State )
        {
            continue;
        }
        EnOceanRun.Tx.u8PushCount = i;
        return OK;
    }
    
    /* Search the start 0 to the current id */
    for (i = 0; i <= j; i++)
    {
        if ( 1 == EnOceanRun.Tx.Queue[i].u8State )
        {
            continue;
        }
        EnOceanRun.Tx.u8PushCount = i;
        return OK;
    }
    EnOceanRun.Tx.u8QueueFull = 1;

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_GetSendQueuePopData(Radio_Typedef *pRadioData)
{
    *pRadioData = EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PopCount].Data;
    EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PopCount].u8State = 0;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_SetSendQueueIDOccupy(void)
{
    EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PushCount].u8State = 1;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ClearReceiveQueuePopID(void)
{
    Esp3Rx.Queue[Esp3Rx.u8PopCount].u8State = 0;

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetReceiveQueuePopID(PACKET_TYPE eType)
{
    uint8_t i;
    uint8_t j;

    j = Esp3Rx.u8PopCount;

    /*  Search the current id to the queue Max */
    for (i = j+1; i < ESP3_RX_QUEUE;i++)
    {
        if ( 0 == Esp3Rx.Queue[i].u8State ) 
        {
            continue;
        }

        if ( OK != ESP3_SerialBuff2Check(Esp3Rx.Queue[i].u8Buff) )
        {
            Esp3Rx.Queue[i].u8State = 0;
            continue;
        }
        
        if ( eType == PACKET_RESPONSE )
        {
            if ( PACKET_RESPONSE == Esp3Rx.Queue[i].u8Buff[4] )
            {
                Esp3Rx.u8PopCount = i;
                return OK;
            }
            else
            {
                Esp3Rx.Queue[i].u8State = 0;
            }
        }
        else
        {
            Esp3Rx.u8PopCount = i;
            return OK;
        }
    }
    
    /* Search the start 0 to the current id */
    for (i = 0; i <= j; i++)
    {
        if ( 0 == Esp3Rx.Queue[i].u8State ) 
        {                
            continue;  
        }

        if ( OK != ESP3_SerialBuff2Check(Esp3Rx.Queue[i].u8Buff) )
        {
            Esp3Rx.Queue[i].u8State = 0;
            continue;
        }
        
        if ( eType == PACKET_RESPONSE )
        {                                             
            if ( PACKET_RESPONSE == Esp3Rx.Queue[i].u8Buff[4] )
            {                
                Esp3Rx.u8PopCount = i;
                return OK;
            }
            else
            {
                Esp3Rx.Queue[i].u8State = 0;
            }
        }
        else
        {
            Esp3Rx.u8PopCount = i;
            return OK;
        }
    }

    //Esp3Rx.u8PopCount = 0;

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetRecevieQueueFull(void)
{
    uint8_t i;

    for (i = 0; i < ESP3_RX_QUEUE;i++)
    {
        if ( 0 == Esp3Rx.Queue[i].u8State )
        {
            Esp3Rx.u8QueueFull = 0;
        }
    }

    return Esp3Rx.u8QueueFull;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetReceiveQueuePushID(void)
{
    uint8_t i;
    uint8_t j;

    j = Esp3Rx.u8PushCount;

    /*  Search the current id to the queue Max */
    for (i = j+1; i < ESP3_RX_QUEUE;i++)
    {
        if ( 1 == Esp3Rx.Queue[i].u8State )
        {
            continue;
        }
        Esp3Rx.u8PushCount = i;
        return OK;
    }
    
    /* Search the start 0 to the current id */
    for (i = 0; i <= j; i++)
    {
        if ( 1 == Esp3Rx.Queue[i].u8State )
        {
            continue;
        }
        Esp3Rx.u8PushCount = i;
        return OK;
    }
    Esp3Rx.u8QueueFull = 1;

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_SetReceiveQueueIDOccupy(void)
{
    Esp3Rx.Queue[Esp3Rx.u8PushCount].u8State = 1;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanESP3ReceivePacketParse(Radio_Typedef *pRadio,PACKET_TYPE eType)
{
    uint8_t u8RxDataIndex = 0;
    uint8_t u8Status;

    EnOcean_GetRecevieQueueFull();

    u8Status = 0xFF;
    /*
    if ( OK != EnOcean_GetBusyState() )
    {
        return u8Status;
    }
    */
    if ( OK != EnOcean_GetReceiveQueuePopID(eType) )
    {
        return u8Status;
    }
    u8RxDataIndex = Esp3Rx.u8PopCount;
    
    if ( PACKET_RESPONSE == Esp3Rx.Queue[u8RxDataIndex].u8Buff[4] )
    {
        u8Status             = Esp3Rx.Queue[u8RxDataIndex].u8Buff[6];
        pRadio->u8PacketType = PACKET_RESPONSE;

        Esp3Tx.u8RetransmissionCnt = 0;
        Esp3Tx.u8State             = eTX_IDLE;

        if ( OK == u8Status )
        {
            u8Status = 0;
        }

        if ( RET_DUTY_LOCK_SET == u8Status )
        {
            u8Status = 1;
        }

        EnOceanRun.u8ErrorCount = 0;
        
    }
    else if ( PACKET_RADIO == Esp3Rx.Queue[u8RxDataIndex].u8Buff[4] )
    {                       
        u8Status = ESP3_SerialBuff2RadioData(pRadio,Esp3Rx.Queue[u8RxDataIndex].u8Buff);
        EnOceanRun.u8LatestReceiveRssi = pRadio->Param.p_rx.u8Dbm;
        EnOceanRun.u32LatestReceiveID  = pRadio->Param.p_rx.u32SourceId;

        if (  (pRadio->Param.p_rx.u32SourceId&0xFFFFFF00) != (EnOceanRun.u32BaseID&0xFFFFFF00) 
            &&(pRadio->Param.p_rx.u32SourceId != EnOceanRun.u32ChipID ) )   
        {
            if ( OK == u8Status )
            {
                u8Status = 2;
            }    
        }
    }
    else if ( PACKET_REMOTE_MAN_COMMAND == Esp3Rx.Queue[u8RxDataIndex].u8Buff[4] )
    {
        u8Status = ESP3_SerialBuff2RemanData(pRadio,Esp3Rx.Queue[u8RxDataIndex].u8Buff);
        if ( OK == u8Status )
        {
            u8Status = 3;
        }
        EnOceanRun.u8LatestReceiveRssi = pRadio->Param.ReMan.u8Dbm;
        EnOceanRun.u32LatestReceiveID  = pRadio->Param.ReMan.u32SourceId;
    }
    else if ( PACKET_SMART_ACK_COMMAND == Esp3Rx.Queue[u8RxDataIndex].u8Buff[4] )
    {

    }           
    else if ( PACKET_EVENT == Esp3Rx.Queue[u8RxDataIndex].u8Buff[4] )
    {
        switch (Esp3Rx.Queue[u8RxDataIndex].u8Buff[6])
        {
        case SA_RECLAIM_NOT_SUCCESSFUL  ://Informs the backbone of a Smart Ack Client to not successful reclaim.
            break;
        case SA_CONFIRM_LEARN           ://Used for SMACK to confirm/discard learn in/out
            break;
        case SA_LEARN_ACK               ://Inform backbone about result of learn request
            break;
        case CO_READY                   ://Inform backbone about operational readiness
            break;
        case CO_EVENT_SECUREDEVICES     : //Inform backbone about a secure device

            break;
        case CO_DUTYCYCLE_LIMIT         :
            if ( Esp3Rx.Queue[u8RxDataIndex].u8Buff[7] )
            {
                u8Status = 1;
            }
            break;
        }
    }
    EnOcean_ClearReceiveQueuePopID();
    return u8Status;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanPopQueueSendData(void)
{
    /* send all learn info */
    /* Send all channel info */
    /* Read learn info ,query send */

    switch (EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PopCount].u8Cmd)
    {
    case eQUEUE_REMAN_TELEGRAM:
        EnOceanReManData2SerialBuff(&EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PopCount].Data, EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PopCount].Data.Param.ReMan.u8RandSendDelayEnable);
        break;

    case eQUEUE_RADIO_TELEGRAM:
        ESP3_RadioSendData2SerialBuff(&EnOceanRun.Tx.Queue[EnOceanRun.Tx.u8PopCount].Data);//
        break;
    case eQUEUE_MODIFY_REAPTER:
        EnOceanWriteRepeater();
        break;

    case eQUEUE_READ_REAPTER:
        EnOceanReadRepeater();
        break;

    default :
        break;
    }
    EnOcean_ClearSendQueuePopID();
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ReceiveUsartDMAPushQueue(void)
{
    uint16_t i;

    if ( Esp3Rx.u8QueueFull )
    {
        return 0;
    }
    
    for (i = 0; i < Esp3Rx.Queue[Esp3Rx.u8PushCount].u16ByteMax; i++)
    {
        Esp3Rx.Queue[Esp3Rx.u8PushCount].u8Buff[i] = Esp3Rx.u8DMABuff[i];
    }

    Esp3Rx.Queue[Esp3Rx.u8PushCount].u8State = 1;
    EnOcean_GetReceiveQueuePushID();
    
    return 0;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_ReceiveUsartDataPushQueue(uint8_t u8RegData)
{
    uint8_t u8Data;

    u8Data = u8RegData;
    if ( !Esp3Rx.u8BusyTime )
    {
        Esp3Rx.u16ByteCnt = 0;
    }
    Esp3Rx.u8BusyTime = 30;

    if ( Esp3Rx.u8QueueFull )
    {
        return 0;
    }

    if ( Esp3Rx.u16ByteCnt >= ESP3_RX_BUF_MAX)
    {
        Esp3Rx.u16ByteCnt = 0;
        return 0;
    }
    
    Esp3Rx.Queue[Esp3Rx.u8PushCount].u8Buff[Esp3Rx.u16ByteCnt] = u8Data;

    if ( 0 == Esp3Rx.u16ByteCnt )
    {
        if ( 0x55 != u8Data )//ESP3 Packet Sync
        {
            Esp3Rx.u16ByteCnt = 0;
        }
        else
        {
            Esp3Rx.Queue[Esp3Rx.u8PushCount].u16ByteMax = 8;
            Esp3Rx.u16ByteCnt = 1;
        }
    }
    else if ( 4 == Esp3Rx.u16ByteCnt )//ESP3 frame length
    {
        Esp3Rx.Queue[Esp3Rx.u8PushCount].u16ByteMax  = (uint16_t)Esp3Rx.Queue[Esp3Rx.u8PushCount].u8Buff[1]<<8;
        Esp3Rx.Queue[Esp3Rx.u8PushCount].u16ByteMax += (uint16_t)Esp3Rx.Queue[Esp3Rx.u8PushCount].u8Buff[2];
        Esp3Rx.Queue[Esp3Rx.u8PushCount].u16ByteMax += (uint16_t)Esp3Rx.Queue[Esp3Rx.u8PushCount].u8Buff[3];
        Esp3Rx.Queue[Esp3Rx.u8PushCount].u16ByteMax += 7;

        Esp3Rx.u16ByteCnt++;
    }
    else
    {
        Esp3Rx.u16ByteCnt++;
        if ( Esp3Rx.u16ByteCnt >= Esp3Rx.Queue[Esp3Rx.u8PushCount].u16ByteMax )
        {
            Esp3Rx.u16ByteCnt = 0;
            Esp3Rx.u8BusyTime = 0;
            Esp3Rx.Queue[Esp3Rx.u8PushCount].u8State = 1;

            EnOcean_GetReceiveQueuePushID();
        }
    }
    return 0;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_SendOK(void)
{
    if ( eTX_SEND_DATA == Esp3Tx.u8State )
    {
        Esp3Tx.u8State = eTX_SEND_OK;
        EnOceanRun.pStop();
        return OK;
    }
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOcean_GetBusyState(void)
{
    /*
    if ( eTX_IDLE != Esp3Tx.u8State ) // IDLE
    {
        return !OK;
    }
    */
    if ( Esp3Tx.u16IdleTime )
    {
        return !OK;
    }
    
    if ( Esp3Rx.u8BusyTime )
    {
        return !OK;
    }

    if ( eTX_IDLE != Esp3Tx.u8State )
    {
        EnOceanRun.u16SendPeriod               = 100;
        return !OK;
    }
    /*
    if ( eTX_IDLE != Esp3Tx.u8BusyState )
    {
        return !OK;
    }
    */
    
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanESP3SendStateProcess(void)
{
    uint32_t u32EnOceanBaseID;
    uint32_t u32EnOceanChipID;

    EnOceanGetHWBaseID  ( &u32EnOceanBaseID );
    EnOceanGetHWChipID  ( &u32EnOceanChipID );
    
    EnOcean_GetBusyState();

    if ( ( 0x00000000 == u32EnOceanChipID )||( 0xFFFFFFFF == u32EnOceanChipID ) )
    {
        EnOceanRun.u8Error |= ENOCEAN_GET_WRONG_CHIPID_ERROR;
    }
    else
    {
        EnOceanRun.u8Error &= ~ENOCEAN_GET_WRONG_CHIPID_ERROR;
    }

    if ( ( u32EnOceanBaseID < ENOCEAN_BASEID_START )||( u32EnOceanBaseID > ENOCEAN_BASEID_END ) )
    {
        EnOceanRun.u8Error |= ENOCEAN_GET_WRONG_BASEID_ERROR;
    }
    else
    {
        EnOceanRun.u8Error &= ~ENOCEAN_GET_WRONG_BASEID_ERROR;
    }

    if ( EnOceanRun.u8ErrorCount > 10 )
    {
        EnOceanRun.u8Error |= ENOCEAN_CAN_NOT_GET_ID_ERROR;
    }
    else
    {
        EnOceanRun.u8Error &= ~ENOCEAN_CAN_NOT_GET_ID_ERROR;
    }

    if ( Esp3Rx.u8BusyTime  )
    {
        return OK;
    }
    
    // uart send message state process
    if ( eTX_IDLE == Esp3Tx.u8State ) // IDLE
    {
        if ( (Esp3Tx.u8RetransmissionCnt)&&(!Esp3Tx.u16IdleTime) )
        {
            Esp3Tx.u8RetransmissionCnt--;
            Esp3Tx.u8State     = eTX_SEND_DATA_PROCESS;

            //EnOceanRun.u16HeartTickPeriod = 300;
        }
    }
    else if ( eTX_SEND_DATA_PROCESS == Esp3Tx.u8State ) // ready send
    {
        Esp3Tx.u8State     = eTX_SEND_DATA;         // send
        Esp3Tx.u16ByteCnt  = 0;
        Esp3Tx.u16IdleTime = 200;
        
        EnOceanRun.pStart(Esp3Tx.u16ByteMax);
    }
    else if ( eTX_SEND_DATA == Esp3Tx.u8State )
    {
        /* interuppt send */
        if ( !Esp3Tx.u16IdleTime )
        {
            Esp3Tx.u8State = eTX_IDLE;
        }
    }
    else if ( eTX_SEND_OK == Esp3Tx.u8State )//shift to the wait response
    {
        Esp3Tx.u8State    = eTX_WAIT_RECEIVE;
        Esp3Tx.u16ByteCnt = 0;
        //Esp3Tx.u8BusyState = 0;
        //Esp3Tx.pStop();
        Esp3Tx.u16IdleTime = 0;
        EnOceanRun.u16SendPeriod               = 100;

        if (Esp3Tx.u8RandomEn)
        {
            Esp3Tx.u16OvfCnt = 2000;
        }
        else
        {
            Esp3Tx.u16OvfCnt = 1000;
        }
    }
    else if ( eTX_WAIT_RECEIVE == Esp3Tx.u8State )// ovf the time and clear the cnt
    {        
        if ( !Esp3Tx.u16OvfCnt )
        {
            Esp3Tx.u8State = eTX_IDLE;

            if ( !Esp3Tx.u8RetransmissionCnt )
            {
                if ( EnOceanRun.u8ErrorCount < 0xFF )
                {
                    EnOceanRun.u8ErrorCount++;
                }
                //Esp3Tx.u8BusyState = 0;
                return !OK; // end of the send process
            }
        }
        // wait the TCM310 response message

        // ovf the time clear the time
    }
    else
    {
        Esp3Tx.u8RetransmissionCnt = 0;
        Esp3Tx.u8State = eTX_IDLE;
    }

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSendReady(void) 
{
    if ( EnOceanRun.u16SendPeriod )
    {
        return !OK;
    }

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanSetSendPeriod(uint16_t u16SendPeriod) 
{
    EnOceanRun.u16SendPeriod = u16SendPeriod;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOcean_InitGetInfo(Radio_Typedef *pRadio)
{
    uint8_t u8InitState;
    uint8_t u8Error;
    uint8_t u8Count;
    //EnOceanFilter_Typedef Filter;

    u8InitState                = 0x01;
    u8Error                    = 0x00;

    Esp3Tx.u8State             = eTX_IDLE;
    Esp3Tx.u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    Esp3Rx.u16DMABuffMax       = ESP3_RX_BUF_MAX;

    u8Count = 0;
    
    EnOceanRun.pEnOceanReset();

    Esp3Tx.u16IdleTime = 100;
    ESP3_ReadVersion(&Esp3Tx);
    
    while (u8InitState)
    {
        
        EnOceanRun.pEnOceanError(u8Error);

        if ( OK != EnOceanESP3SendStateProcess() )
        {
            Esp3Tx.u8State = eTX_IDLE;
            u8Error        = 1;
            u8InitState = 1;
        

            EnOceanRun.pEnOceanReset();

            ESP3_ReadVersion(&Esp3Tx);
            u8Count++;
            if (u8Count >= 5)
            {
                break;
            }
        }

        if ( OK != EnOceanESP3ReceivePacketParse(pRadio,PACKET_RESPONSE) )
        {
            continue;
        }
        
        if ( PACKET_RESPONSE != pRadio->u8PacketType )
        {
            continue;
        }
        u8Error = 0;

        switch( u8InitState )
        {
        case 1:
            if ( ( 0x21 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[2] )||( 0x00 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[3] ) )
            {
                ESP3_ReadVersion(&Esp3Tx);
                break;
            }
            EnOceanRun.u32ChipID  = (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[15] << 24;
            EnOceanRun.u32ChipID |= (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[16] << 16;
            EnOceanRun.u32ChipID |= (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[17] << 8;
            EnOceanRun.u32ChipID |= (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[18];
            
            ESP3_ReadBaseID(&Esp3Tx);
            u8InitState = 2;
            break;

        case 2:
            if ( ( 0x05 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[2] )||( 0x01 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[3] ) )
            {
                ESP3_ReadBaseID(&Esp3Tx);
                break;
            }
            EnOceanRun.u32BaseID  = (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[7] << 24;
            EnOceanRun.u32BaseID |= (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[8] << 16;
            EnOceanRun.u32BaseID |= (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[9] << 8;
            EnOceanRun.u32BaseID |= (uint32_t)Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[10];
            EnOceanRun.u8BaseIDRemainCycle = Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[11];
            ESP3_WriteWaitMaturity(&Esp3Tx, 1);
            
            u8InitState = 3;
            break;

        case 3:
            if ( ( 0x01 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[2] )||( 0x00 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[3] ) )
            {
                ESP3_WriteWaitMaturity(&Esp3Tx, 1);
                break;
            }

            ESP3_WriteReapter(&Esp3Tx,  *EnOceanRun.pu8Reapter);
            u8InitState = 4;
            break;

        case 4:
            if ( ( 0x01 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[2] )||( 0x00 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[3] ) )
            {
                ESP3_WriteReapter(&Esp3Tx,  *EnOceanRun.pu8Reapter);
                break;
            }

            ESP3_ReadReapter(&Esp3Tx);
            u8InitState = 5;
            break;

        case 5:
            if ( ( 0x03 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[2] )||( 0x00 != Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[3] ) )
            {
                ESP3_ReadReapter(&Esp3Tx);
                break;
            }
            else
            {
                if ( *EnOceanRun.pu8Reapter == Esp3Rx.Queue[Esp3Rx.u8PopCount].u8Buff[8] )
                {
                    u8InitState = 0;
                }
            }
            /*
            u8InitState = 6;
            Filter.u8Type = 0x00;
            Filter.u32Value = 0x01A38564;
            Filter.u8Kind = 0x80;

            ESP3_WriteFliterAdd(&Esp3Tx, Filter);
            */
            break;
        case 6:
            //ESP3_ReadMemoryAddress(&Esp3Tx,  1);
            /*
            Filter.u8OnOff = 0x01;
            Filter.u8Operator = 0x01;
            ESP3_WriteFliterEnable(&Esp3Tx, Filter); 
            */
            
            u8InitState = 0;
            break;
        case 7:
            //Esp3_SmartAckWritePostMaster(&Esp3Tx,0);
            
            u8InitState = 0;
            break;
        case 8:
            //Esp3_SmartAckWritePostMaster(&Esp3Tx,10);

            u8InitState = 9;
            break;
        case 9:
            u8InitState = 0;
            break;
        default:
            u8InitState = 0;
            break;
        }
    }
    
}
/* end of file */
