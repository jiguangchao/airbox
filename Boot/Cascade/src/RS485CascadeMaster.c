/*******************************************************************
*
*    DESCRIPTION:
*
*    AUTHOR:
*
*    HISTORY:
*
*    DATE:
*
*******************************************************************/

#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"


#include "BSP.h"
#include "main.h"
#include "RS485Cascade.h"
//#include "RS485CascadeQueue.h"
#include "EnOceanFun.h"

#include "RS485Modbus.h"
#include "LedAndButton.h"

#ifdef CASCADE_485_CRC_DISABLE
    #pragma message("CASCADE_485_CRC_DISABLE")
#else
    #pragma message("CASCADE_485_CRC_ENABLE")
#endif






/**
  * @brief
  * @param
  * @retval None
  */
uint8_t RS485CascadeReset(SerialCascade_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t RS485CascadeDevError(SerialCascade_Typedef *pSerial);    
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_MasterModbusForward(CascadeModbusData_Typedef *pCascade,SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_MasterModbusReceive(SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_MasterEnOceanForward(CascadeSendQueue_Typedef *pCascade,SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_MasterEnOceanReceive(SerialCascade_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval
  */
uint8_t RS485Cascade_CommonParameter(SerialCascade_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t RS485CascadeReceiveOK(SerialCascade_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval
  */
uint8_t RS485CascadeSendPrepairData(SerialCascade_Typedef *pSerial);

/*
#define CASCADE_MASTER_BUFF_MAX                                       (128)
#define CASCADE_SLAVER_BUFF_MAX                                       (80)
*/
/******************************************************************************/
uint8_t u8CascadeReceiveData[CASCADE_BUFF_MAX];
uint8_t u8CascadeDMAData[CASCADE_BUFF_MAX];
uint8_t u8CascadeSendData[CASCADE_BUFF_MAX];


Cascade_Function_Typedef  RS485Cascade;
CascadeModbusData_Typedef CascadeModbus;
Radio_Typedef             CasRadio;

CascadeInfo_Typedef       CasInfo;

/**
   * @brief
   * @param
   * @retval
   */
uint8_t RS485CascadeInit(Cascade_Function_Typedef *pUSART)
{

    pUSART->Frame.pu8Receive           = u8CascadeReceiveData;
    pUSART->Frame.pu8DMAReceive        = u8CascadeDMAData;
    pUSART->Frame.pu8Send              = u8CascadeSendData;
    pUSART->Frame.u16ReceiveBuffMax    = CASCADE_BUFF_MAX;

    //pUSART->Frame.u8IdleNmsConfig   = 5;

    pUSART->SerialDevInit              = NULL;
    pUSART->SerialReceiveOK            = RS485CascadeReceiveOK;
    pUSART->SerialDevError             = RS485CascadeDevError;
    //pUSART->SerialDevFrameTime       = NULL;
    pUSART->SerialDevReset             = RS485CascadeReset;
    pUSART->SerialSendPrepair          = RS485CascadeSendPrepairData;

    pUSART->pStart                     = BSP_RS485CascadeSendStart;
    pUSART->pStop                      = BSP_RS485CascadeSendStop;
    pUSART->pSend                      = BSP_RS485CascadeDirectSend;
    pUSART->pReceive                   = BSP_RS485CascadeDirectReceive;
    pUSART->pGetBusBusy                = BSP_RS485CascadeStatus;

    pUSART->pReceive();
     
    
    BSP_CascadeUsartDMA_Init(u8CascadeDMAData,u8CascadeSendData);
    BSP_CascadeUSART_Init(19200, LL_USART_STOPBITS_1, LL_USART_PARITY_NONE);
    
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t RS485CascadeSendOK(void)
{
    if ( eSERIAL_BUS_STATE_SEND_DATA == RS485Cascade.Frame.eState )
    {
        RS485Cascade.Frame.eState         = eSERIAL_BUS_STATE_SEND_DATA_OK;        
        RS485Cascade.Frame.u8RxTxShiftNms = 3;        
        return OK;
    }
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t RS485CascadeReset(SerialCascade_Typedef *pSerial)
{   
    pSerial->u8SendCmd = 0x00; 
    pSerial->u8SendState = 0;
    pSerial->eState = eSERIAL_BUS_STATE_IDLE;
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t RS485CascadeDevError(SerialCascade_Typedef *pSerial)
{   
    pSerial->u8SendCmd = 0x00; 
    pSerial->u8SendState = 0;
    pSerial->eState = eSERIAL_BUS_STATE_IDLE;
    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
void RS485CascadeMasterSearchSlave(SerialCascade_Typedef *pSerial)
{
    uint16_t u16Crc;

    pSerial->pu8Send[0]  = 0x55;
    pSerial->pu8Send[1]  = 0x00;
    pSerial->pu8Send[2]  = *pSerial->pu8PhyAddress;
                     
    pSerial->pu8Send[3]  = 0xFF;
    pSerial->pu8Send[4]  = 0x09;
    pSerial->pu8Send[5]  = CASCADE_CMD_SYS_SEARCH_SYNC;
    pSerial->pu8Send[6]  = pSerial->u8SearchAddressCount;
    /*
    pSerial->pu8Send[7]  = (Dev.Cfg.u32EnOceanChipID>>24)&0xFF;
    pSerial->pu8Send[8]  = (Dev.Cfg.u32EnOceanChipID>>16)&0xFF;
    pSerial->pu8Send[9]  = (Dev.Cfg.u32EnOceanChipID>>8)&0xFF;
    pSerial->pu8Send[10] = Dev.Cfg.u32EnOceanChipID&0xFF;
    pSerial->pu8Send[11] = (Dev.Cfg.u32EnOceanBaseID>>24)&0xFF;
    pSerial->pu8Send[12] = (Dev.Cfg.u32EnOceanBaseID>>16)&0xFF;
    pSerial->pu8Send[13] = (Dev.Cfg.u32EnOceanBaseID>>8)&0xFF;
    pSerial->pu8Send[14] = Dev.Cfg.u32EnOceanBaseID&0xFF;
    */                    
    pSerial->u16SendBytesMax = 17;        
    
    u16Crc = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax-2] = u16Crc&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax-1] =   u16Crc>>8;
}
/**
 * @brief
 * @param
 * @retval
 */
void RS485Cascade_MasterSyncInit(SerialCascade_Typedef *pSerial)
{
    uint16_t u16Crc;

    pSerial->pu8Send[0] = 0x55;
    pSerial->pu8Send[1] = 0x00;
    pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
    pSerial->pu8Send[3] = 0xFF;
    pSerial->pu8Send[4] = 0x04;
    pSerial->pu8Send[5] = CASCADE_CMD_SYS_DATA_SYNC;    
    /*
    pSerial->pu8Send[6] = (Dev.Cfg.u32EnOceanBaseID>>24)&0xFF;
    pSerial->pu8Send[7] = (Dev.Cfg.u32EnOceanBaseID>>16)&0xFF;
    pSerial->pu8Send[8] = (Dev.Cfg.u32EnOceanBaseID>>8)&0xFF;
    pSerial->pu8Send[9] = Dev.Cfg.u32EnOceanBaseID&0xFF;
    */
    pSerial->u16SendBytesMax = 12;
    u16Crc = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax-2] = u16Crc&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax-1] =   u16Crc>>8;                
}
/**
 * @brief
 * @param
 * @retval
 */
void RS485Cascade_SetSlaverRelay(SerialCascade_Typedef *pSerial)
{
    uint16_t u16Crc;

    pSerial->pu8Send[0] = 0x55;
    pSerial->pu8Send[1] = 0x00;
    pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
    pSerial->pu8Send[3] = 0xFF;
    pSerial->pu8Send[4] = 0x00;
    pSerial->pu8Send[5] = 0x10;
    
    pSerial->u16SendBytesMax = 8;
    u16Crc = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax-2] = u16Crc&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax-1] =   u16Crc>>8;                
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_CommonParameter(SerialCascade_Typedef *pSerial)
{
    if ( CASCADE_CMD_SYS_SEARCH_SYNC == pSerial->u8SendCmd )
    {
        RS485CascadeMasterSearchSlave(pSerial);
        if ( 0 == pSerial->u8SearchAddressCount )
        {
            pSerial->u8SendCmd = CASCADE_CMD_SYS_DATA_SYNC;
        }        
    }
    else if ( CASCADE_CMD_SYS_DATA_SYNC == pSerial->u8SendCmd )
    {
        RS485Cascade_MasterSyncInit(pSerial);
        pSerial->u8SendCmd = CASCADE_CMD_SYS_SEARCH_SYNC;
    }
    else if ( CASCADE_CMD_CTRL_CHANNEL == pSerial->u8SendCmd )
    {
        RS485Cascade_SetSlaverRelay(pSerial);
    }
    else
    {
        pSerial->u8SendCmd = CASCADE_CMD_SYS_SEARCH_SYNC;
    }
        
    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
void RS485Cascade_MasterGetSlaverCommon(SerialCascade_Typedef *pSerial) 
{
    
}

/**
 * @brief
 * @param
 * @retval
 */
void RS485CascadeMasterGetModbus(CascadeModbusData_Typedef *pCascade,uint8_t *pu8ModbusBuff)
{
    uint16_t i;
    uint16_t u16NRegs;    

    switch (pu8ModbusBuff[1])
    {
    case MB_FUNC_READ_HOLDING_REGISTER:
    case MB_FUNC_READ_INPUT_REGISTER:

        pCascade->u8ByteMax = 8;
        for (i = 0; i < pCascade->u8ByteMax; i++)
        {
            pCascade->u8Byte[i] = pu8ModbusBuff[i];
        }
        break;

    case MB_FUNC_WRITE_REGISTER:
        pCascade->u8ByteMax = 8;
        for (i = 0; i < pCascade->u8ByteMax; i++)
        {
            pCascade->u8Byte[i] = pu8ModbusBuff[i];
        }
        break;

    case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
        u16NRegs   = (uint16_t)pu8ModbusBuff[4]<<8 | (uint16_t)pu8ModbusBuff[5];

        pCascade->u8ByteMax = u16NRegs*2 + 9;
        for (i = 0; i < pCascade->u8ByteMax; i++)
        {
            pCascade->u8Byte[i] = pu8ModbusBuff[i];
        }
        break;

    default:
        return;
        break;
    }
    
    pCascade->u8State = 1;
}
/**
     * @brief
     * @param
     * @retval
     */
uint8_t RS485Cascade_MasterModbusForward(CascadeModbusData_Typedef *pCascade,SerialCascade_Typedef *pSerial)
{
    uint8_t i;
    uint16_t u16Crc;
    uint8_t  u8SlaverAddress;

    if ( !pCascade->u8State )
    {
        return !OK;
    }
    pCascade->u8State = 0;
    /* channel 4--7, 8 --11 , 12 -- 15,16 -- 19,20 --23,*/
    /* channel 24--27, 28 --30 and 112 , 113 -- 116,117 -- 121 ,*/
    if ( (pCascade->u8Byte[2] >= SLAVER_DEV_INFO_START) )
    {
        u8SlaverAddress = pCascade->u8Byte[2]&0x0F;
    }    
    else if ( ( pCascade->u8Byte[2] >= LIGHT_CHANNEL_CASCADE_START )&&( pCascade->u8Byte[2] <= LIGHT_CHANNEL_CASCADE_END ) )
    {
        u8SlaverAddress = (pCascade->u8Byte[2]-1)/4;
    }    
    else
    {
        return !OK;
    }

    pSerial->pu8Send[0] = 0x55;
    pSerial->pu8Send[1] = 0x00;
    pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
    pSerial->pu8Send[3] = u8SlaverAddress;
    pSerial->pu8Send[4] = pCascade->u8ByteMax;
    pSerial->pu8Send[5] = CASCADE_CMD_MODBUS_MASTER_2_SLAVE;//

    pSerial->u16SendBytesMax = pSerial->pu8Send[4] + 8;
    if ( pSerial->u16SendBytesMax > CASCADE_BUFF_MAX )
    {
        return !OK;
    }

    /* filter the modbus crc */
    for (i = 0; i < pCascade->u8ByteMax; i++)
    {
        pSerial->pu8Send[6 + i] = pCascade->u8Byte[i];
    }
    

    u16Crc = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax - 2] = u16Crc&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax - 1] =   u16Crc>>8;
    //pSerial->eState  = eSERIAL_BUS_STATE_SEND_DATA_WAIT;
    pSerial->u8DataUpdateLock                   = 1;

    return OK;
}
/**
     * @brief
     * @param
     * @retval
     */
uint8_t RS485Cascade_MasterModbusReceive(SerialCascade_Typedef *pSerial)
{
    uint8_t i;
    uint16_t u16SendMax;
    //uint16_t u16Crc;

    if ( pSerial->pu8Receive[5] != CASCADE_CMD_MODBUS_SLAVE_2_MASTER )
    {
        return !OK;
    }
    u16SendMax                        = pSerial->pu8Receive[4];
    RS485Modbus.Frame.u16SendBytesMax = u16SendMax;
    for(i = 0; i < u16SendMax; i++)
    {
        RS485Modbus.Frame.pu8Send[i] = pSerial->pu8Receive[6+i];
    }

    USART_StateSetSend(&RS485Modbus.Frame, RS485Modbus.Frame.u16SendBytesMax,0,0);

    return OK;
}
/**
     * @brief
     * @param
     * @retval
     */
uint8_t RS485Cascade_EnOceanPushQueue(Radio_Typedef *pRadio,CascadeSendQueue_Typedef *pCascade)
{
    uint8_t  i;
    uint8_t  u8PacketType;
    uint16_t u16RemanFunNum;        
    uint32_t u32EnOceanBaseID;    
    uint32_t u32EnOceanChipID;

    u8PacketType = pRadio->u8PacketType;

    EnOceanGetHWBaseID  ( &u32EnOceanBaseID );
    EnOceanGetHWChipID  ( &u32EnOceanChipID );

    /* get gateway */
    if ( RADIO_CHOICE_VLD == pRadio->Telegram.raw.u8RORG )
    {
        if ( pRadio->Param.p_rx.u32DestinationId == u32EnOceanChipID )
        {

        }
        /* Receive the gateway or smarthive message */
        else if ( (pRadio->Param.p_rx.u32DestinationId&0xFFFFFF00) == (u32EnOceanBaseID&0xFFFFFF00) )
        {
            /* Add the Channel filter logic */
        }
        else
        {
            return !OK;
        }
    }
    else if ( RADIO_CHOICE_MSC == pRadio->Telegram.raw.u8RORG )
    {
        if ( pRadio->Param.p_rx.u32DestinationId == u32EnOceanChipID )
        {

        }
            /* Receive the gateway or smarthive message */
        else if ( (pRadio->Param.p_rx.u32DestinationId&0xFFFFFF00) == (u32EnOceanBaseID&0xFFFFFF00) )
        {
            /* Add the Channel filter logic */
        }
        else
        {
            return !OK;
        }        
    }
    

    if ( OK == Cascade_GetSendQueuePushID() )
    {            
        pCascade->Data[pCascade->u8PushCount].u8PacketType = u8PacketType;
        
        if ( PACKET_RADIO == u8PacketType )
        {                
            if ( pRadio->u16DataLength > CASCADE_BUFF_MAX )
            {
                return !OK;
            }
            pCascade->Data[pCascade->u8PushCount].u8ByteMax = pRadio->u16DataLength;
            
            pCascade->Data[pCascade->u8PushCount].u8Byte[0] = pRadio->Telegram.raw.u8RORG;
            
            for (i = 0; i < pRadio->u16DataLength-6 ; i++)
            {
                pCascade->Data[pCascade->u8PushCount].u8Byte[1+i] = pRadio->Telegram.raw.bytes[i];
            }
            pCascade->Data[pCascade->u8PushCount].u8Byte[pRadio->u16DataLength - 5] = pRadio->Param.p_rx.u32SourceId>>24;
            pCascade->Data[pCascade->u8PushCount].u8Byte[pRadio->u16DataLength - 4] = pRadio->Param.p_rx.u32SourceId>>16;
            pCascade->Data[pCascade->u8PushCount].u8Byte[pRadio->u16DataLength - 3] = pRadio->Param.p_rx.u32SourceId>> 8;
            pCascade->Data[pCascade->u8PushCount].u8Byte[pRadio->u16DataLength - 2] = pRadio->Param.p_rx.u32SourceId&0xFF;
            pCascade->Data[pCascade->u8PushCount].u8Byte[pRadio->u16DataLength - 1] = pRadio->Telegram.raw.u8Status;

            if ( pRadio->Param.p_rx.u32DestinationId == u32EnOceanChipID )
            {
                pCascade->Data[pCascade->u8PushCount].u8DstPhyaddress = 0xFF;
            }
            else if ( RADIO_CHOICE_VLD == pRadio->Telegram.raw.u8RORG )  
            {                
                pCascade->Data[pCascade->u8PushCount].u8DstPhyaddress = pRadio->Param.p_rx.u32DestinationId - u32EnOceanBaseID;                    
            }
            else
            {
                pCascade->Data[pCascade->u8PushCount].u8DstPhyaddress = 0xFF;
            }
            
        }
        else if ( PACKET_REMOTE_MAN_COMMAND == u8PacketType ) 
        {            
            if ( pRadio->Telegram.ReMan.u8Length + 14 > CASCADE_BUFF_MAX )
            {
                return !OK;
            }
            pCascade->Data[pCascade->u8PushCount].u8DstPhyaddress = 0xFF;
            /* Reman data + source ID + funnumber */
            pCascade->Data[pCascade->u8PushCount].u8ByteMax = pRadio->Telegram.ReMan.u8Length + 6;
            
            pCascade->Data[pCascade->u8PushCount].u8Byte[0] = pRadio->Param.ReMan.u32SourceId>>24;
            pCascade->Data[pCascade->u8PushCount].u8Byte[1] = pRadio->Param.ReMan.u32SourceId>>16;
            pCascade->Data[pCascade->u8PushCount].u8Byte[2] = pRadio->Param.ReMan.u32SourceId>> 8;
            pCascade->Data[pCascade->u8PushCount].u8Byte[3] = pRadio->Param.ReMan.u32SourceId&0xFF;

            u16RemanFunNum = pRadio->Telegram.ReMan.u16FnNum;
            pCascade->Data[pCascade->u8PushCount].u8Byte[4] =   u16RemanFunNum>>8;
            pCascade->Data[pCascade->u8PushCount].u8Byte[5] = u16RemanFunNum&0xFF;

            for (i = 0; i < pRadio->Telegram.ReMan.u8Length; i++)
            {
                pCascade->Data[pCascade->u8PushCount].u8Byte[6+i] = pRadio->Telegram.ReMan.u8Data[i];
            }
        }
        pCascade->Data[pCascade->u8PushCount].u8MessageType = eENOCEAN_TYPE;
        Cascade_SetSendQueueIDOccupy();
    }
    return OK;
}
/**
     * @brief
     * @param
     * @retval
     */
uint8_t RS485Cascade_MasterEnOceanForward(CascadeSendQueue_Typedef *pCascade,SerialCascade_Typedef *pSerial)
{
    uint8_t i;
    uint16_t u16Crc;
    

    if ( PACKET_RADIO == pCascade->Data[pCascade->u8PopCount].u8PacketType )
    {
        pSerial->pu8Send[0] = 0x55;
        pSerial->pu8Send[1] = 0x00;
        pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
        
        pSerial->pu8Send[3] = pCascade->Data[pCascade->u8PopCount].u8DstPhyaddress;
        pSerial->pu8Send[4] = pCascade->Data[pCascade->u8PopCount].u8ByteMax;
        pSerial->pu8Send[5] = CASCADE_CMD_ENOCEAN_RADIO_MASTER_2_SLAVE;//
    }
    else if ( PACKET_REMOTE_MAN_COMMAND == pCascade->Data[pCascade->u8PopCount].u8PacketType )
    {
        pSerial->pu8Send[0] = 0x55;
        pSerial->pu8Send[1] = 0x00;
        pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
        pSerial->pu8Send[3] = 0xFF;
        pSerial->pu8Send[4] = pCascade->Data[pCascade->u8PopCount].u8ByteMax;
        pSerial->pu8Send[5] = CASCADE_CMD_ENOCEAN_REMAN_MASTER_2_SLAVE;
    }
    else
    {
        return !OK;
    }

    pSerial->u16SendBytesMax = pSerial->pu8Send[4] + 8;
    if ( pSerial->u16SendBytesMax > CASCADE_BUFF_MAX )
    {
        return !OK;
    }
    for (i = 0; i < pCascade->Data[pCascade->u8PopCount].u8ByteMax; i++)
    {
        pSerial->pu8Send[6 + i] = pCascade->Data[pCascade->u8PopCount].u8Byte[i];
    }
    

    u16Crc = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax - 2] = u16Crc&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax - 1] =   u16Crc>>8;
    pSerial->u8DataUpdateLock                   = 1;

    return OK;
}
/**
     * @brief
     * @param
     * @retval
     */
uint8_t RS485Cascade_MasterEnOceanReceive(SerialCascade_Typedef *pSerial)
{
    uint8_t i;
    uint8_t u8PhyAdd;
    uint32_t u32EnOceanBaseID;
    uint32_t u32EnOceanChipID;

    EnOceanGetHWBaseID  ( &u32EnOceanBaseID );
    EnOceanGetHWChipID  ( &u32EnOceanChipID );

    u8PhyAdd = pSerial->pu8Receive[2];
    if ( pSerial->pu8Receive[5] == CASCADE_CMD_ENOCEAN_RADIO_SLAVE_2_MASTER )
    {
        CasRadio.u8PacketType                = PACKET_RADIO;
        CasRadio.u16DataLength               = pSerial->pu8Receive[4];
        CasRadio.Param.p_tx.u32DestinationId = 0xFFFFFFFF;
        CasRadio.u8OptionalDataLength        = 7;
        CasRadio.Telegram.raw.u8Status       = 0x0F;
        
        CasRadio.Telegram.raw.u8RORG = (CHOICE_TYPE)pSerial->pu8Receive[6];

        for (i = 0; i < CasRadio.u16DataLength-6; i++)
        {
            CasRadio.Telegram.raw.bytes[i] = pSerial->pu8Receive[7 + i];
        }
        /* Add the serial data to EnOcean send queue */            
        if ( RADIO_CHOICE_MSC == CasRadio.Telegram.raw.u8RORG )
        {
            /*
            if ( CasRadio.Telegram.raw.bytes[2] == 0 )
            {
                CasRadio.Param.p_tx.u32SourceId = u32EnOceanChipID;
            }
            else
            {
                CasRadio.Param.p_tx.u32SourceId = u32EnOceanBaseID + u8PhyAdd;
            }
            */
            CasRadio.Param.p_tx.u32SourceId = u32EnOceanChipID;
        }
        else if ( RADIO_CHOICE_VLD == CasRadio.Telegram.raw.u8RORG )
        {
            CasRadio.Param.p_tx.u32SourceId = u32EnOceanBaseID + pSerial->pu8Receive[2];
        }
        
        EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,&CasRadio);
    }
    else if ( pSerial->pu8Receive[5] == CASCADE_CMD_ENOCEAN_REMAN_SLAVE_2_MASTER )
    {
        CasRadio.u8PacketType                 = PACKET_REMOTE_MAN_COMMAND;
        CasRadio.Telegram.ReMan.u16ManId      = 0x051;
        CasRadio.Telegram.ReMan.u16FnNum      = pSerial->pu8Receive[10]<<8 | pSerial->pu8Receive[11];
        CasRadio.Param.ReMan.u32SourceId      = u32EnOceanChipID;
        CasRadio.Param.ReMan.u32DestinationId = pSerial->pu8Receive[6]<<24 | pSerial->pu8Receive[7]<<16|pSerial->pu8Receive[8]<<8 | pSerial->pu8Receive[9];

        CasRadio.u16DataLength                = pSerial->pu8Receive[4] - 6;
        CasRadio.Telegram.ReMan.u8Length      = CasRadio.u16DataLength;
        CasRadio.u8OptionalDataLength         = 10;

        for (i = 0; i < CasRadio.u16DataLength; i++)
        {
            CasRadio.Telegram.ReMan.u8Data[i] = pSerial->pu8Receive[12 + i];
        }

        Cascade_MasterGetSlaverInfo(u8PhyAdd,&CasRadio);
        /* Add the serial data to EnOcean send queue */
        EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM,&CasRadio); 
    }
    else
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
uint16_t Cascade_MasterGetSlaverLearnIDs(void) 
{
    uint8_t i;
    uint16_t u16Nums;

    u16Nums = 0;
    for (i = 0; i < LIGHT_CASCADE_NUMS_MAX; i ++)
    {
        u16Nums += CasInfo.u16LearnTabNums[i];
    }
    return u16Nums;
}
/**
     * @brief
     * @param
     * @retval None
     */
void Cascade_MasterGetSlaverInfo(uint8_t u8PhyAdd,Radio_Typedef *pRadio)
{
    uint16_t u16RemanFN;
    
    if ( pRadio->Telegram.ReMan.u16FnNum < 0x600 )
    {
        return;
    }
    u16RemanFN = pRadio->Telegram.ReMan.u16FnNum - 0x600;
    switch(u16RemanFN)
    {
    // Perform a visual signalisation on the I/O pins.
    // query infomation            
    case RM_FN_ACTION_COMMAND:            
        break;
        
    // rpc command for menred products
    case RM_RPC_RESET_ALL://0->0x300
        break;            
        
    case RM_RPC_ADD_ONE://5->0x305
        break;
        
    case RM_RPC_DEL_ONE://6->0x306            
        break;
                    
    case RM_RPC_READ_ONE_BY_ONE://8->0x308                        
        break;
        
    case RM_RPC_TEST_CHANNEL://9->0x309                                    
        break;
    /*
    case RM_RPC_READ_LIGHT_NUMS      ://0x30D
        return EnOceanReManResponseQueryChannelMax(pRadio,u8ChannelMax);
    */            
    case RM_RPC_READ_LIGHT_TYPE      ://0x30E
    case RM_RPC_WRITE_LIGHT_TYPE:            
        break;
        
    case RM_RPC_ADD_LEARN_ADVANCED    ://0x330            
        break;
        
    case RM_RPC_DEL_LEARN_ADVANCED    ://0x331            
        break;
    case RM_RPC_READ_GATEWAY_LEARN_IDS :
        CasInfo.u16LearnTabNums[u8PhyAdd] = pRadio->Telegram.ReMan.u8Data[1]<<8 | pRadio->Telegram.ReMan.u8Data[2];
        break;
    case RM_RPC_CLEAR_GATEWAY_LEARN_IDS :
        CasInfo.u16LearnTabNums[u8PhyAdd] = 0x0000;
        break;    
        // Here it could be received a remote telegram that TCM300 does not decode. Do nothing.
    default:
        break;
    }
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485CascadeReceiveOK(SerialCascade_Typedef *pSerial)
{
    
    /* Add the Data process content */       
    /* Check the EnOcean send info */
    if ( pSerial->pu8Receive[5] >= CASCADE_CMD_ENOCEAN_RADIO_MASTER_2_SLAVE )
    {
        /* Send to EnOcean */
        RS485Cascade_MasterEnOceanReceive(pSerial);
    }
    /* Check the RS485 reply cmd */
    else if ( pSerial->pu8Receive[5] >= CASCADE_CMD_MODBUS_MASTER_2_SLAVE )
    {
        /* Send to Modbus RS485 */
        RS485Cascade_MasterModbusReceive(pSerial);
    }        
    else
    {
        RS485Cascade_MasterGetSlaverCommon(pSerial) ;    
    }    

    return OK;
}

/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485CascadeStateSend(SerialCascade_Typedef *pSerial)
{
    return OK;
} 
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485CascadeSendPrepairData(SerialCascade_Typedef *pSerial)
{
    uint8_t u8Status;

    u8Status = 0x00;

    if ( !pSerial->u8SearchAddressCount )
    {
        /* Check RS485/Modbus data */

        /* Check EnOcean data */
        if ( OK == Cascade_GetSendQueuePopID() )
        {
            Cascade_ClearSendQueuePopID();

            if ( eENOCEAN_TYPE == CascadeSend.Data[CascadeSend.u8PopCount].u8MessageType )
            {
                u8Status = RS485Cascade_MasterEnOceanForward(&CascadeSend,pSerial);
            }
        }
        else
        {
            u8Status = RS485Cascade_MasterModbusForward(&CascadeModbus,pSerial);
        }

        if ( u8Status )
        {
            RS485Cascade_CommonParameter(pSerial);
        }
    }
    else
    {
        RS485Cascade_CommonParameter(pSerial);
    }

    return !OK;
}



/* End of file */