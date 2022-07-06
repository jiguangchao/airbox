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


#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "RS485Cascade.h"
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
 * @retval None
 */
uint8_t RS485CascadeSlaverReplyEnOcean(SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_SlaverEnOceanForward(Radio_Typedef *pCasRadio,SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485Cascade_SlaverReplyModbus(SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_SlaverModbusForward(SerialCascade_Typedef *pSerial);

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



/******************************************************************************/
uint8_t u8CascadeReceiveData[CASCADE_BUFF_MAX];
uint8_t u8CascadeDMAData[CASCADE_BUFF_MAX];
uint8_t u8CascadeSendData[CASCADE_BUFF_MAX];


Cascade_Function_Typedef  RS485Cascade;
CascadeModbusData_Typedef CascadeModbus;
Radio_Typedef             CasRadio;



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

    pUSART->SerialDevInit              = NULL;
    pUSART->SerialReceiveOK            = RS485CascadeReceiveOK;
    pUSART->SerialDevError             = RS485CascadeDevError;
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
uint8_t RS485Cascade_CommonParameter(SerialCascade_Typedef *pSerial)
{
    uint8_t i;
    uint16_t u16Crc;


    switch ( pSerial->u8SendCmd )
    {
    case CASCADE_CMD_CTRL_CHANNEL                                      :
        break;
    case CASCADE_CMD_QUERY_CHANNEL                                     :
        break;
    case CASCADE_CMD_SET_CHANNEL                                       :
        break;
    case CASCADE_CMD_RESPONSE_CHANNEL                                  :    

        break;
    case CASCADE_CMD_CTRL_CURTAIN                                      :
        break;
    case CASCADE_CMD_QUERY_CURTAIN                                     :
        break;
    case CASCADE_CMD_SET_CURTAIN_POSTION                               :
        break;
    case CASCADE_CMD_RESPONSE_CUTRAIN                                  :
        break;

    case CASCADE_CMD_QUERY_INPUT                                       :
        break;
    case CASCADE_CMD_RESPONSE_INPUT                                    :
        //pSerial->pu8Send[4] = 18;
        
        //pSerial->u16SendBytesMax = pSerial->pu8Send[4]+8;
        break;

    case CASCADE_CMD_SET_COLOR                                         :
        break;
    case CASCADE_CMD_QUERY_COLOR                                       :
        break;
    case CASCADE_CMD_RESPONSE_COLOR                                    :
        break;
    default:
        break;    
    }

    pSerial->pu8Send[0] = 0x55;
    pSerial->pu8Send[1] = 0x00;
    pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;                        
    pSerial->pu8Send[3] = 0xFF;        
    pSerial->pu8Send[5] = pSerial->u8SendCmd;
    pSerial->u16SendBytesMax = pSerial->pu8Send[4]+8;
    u16Crc = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax-2] = u16Crc&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax-1] =   u16Crc>>8;

    return OK;
}


/**
 * @brief
 * @param
 * @retval
 */
void RS485Cascade_SlaverGetCommon(SerialCascade_Typedef *pSerial) 
{
             
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485CascadeSlaverReplyEnOcean(SerialCascade_Typedef *pSerial)
{
    uint8_t u8Cmd;
    uint8_t i;

    u8Cmd = pSerial->pu8Receive[5];

    if ( CASCADE_CMD_ENOCEAN_RADIO_MASTER_2_SLAVE == u8Cmd )
    {            
        if ( ( 0xFF == pSerial->pu8Receive[3] )||(*pSerial->pu8PhyAddress == pSerial->pu8Receive[3]) )
        {
            
        }
        else
        {
            return !OK;
        }
        
        CasRadio.u8PacketType = PACKET_RADIO;
        CasRadio.u16DataLength = pSerial->pu8Receive[4];
        
        CasRadio.Telegram.raw.u8RORG = (CHOICE_TYPE)pSerial->pu8Receive[6];

        for (i = 0; i < CasRadio.u16DataLength - 6; i++)
        {
            CasRadio.Telegram.raw.bytes[i] = pSerial->pu8Receive[7+i];
        }

        CasRadio.Param.p_rx.u32SourceId =  pSerial->pu8Receive[CasRadio.u16DataLength+1]<<24\
                                          |pSerial->pu8Receive[CasRadio.u16DataLength+2]<<16\
                                          |pSerial->pu8Receive[CasRadio.u16DataLength+3]<<8\
                                          |pSerial->pu8Receive[CasRadio.u16DataLength+4];
        CasRadio.Telegram.raw.u8Status =  pSerial->pu8Receive[CasRadio.u16DataLength+5];

        

        //if ( OK == EnOceanLight(&CasRadio) )
        {
            EnOcean_PushData2Queue(eQUEUE_RADIO_TELEGRAM,&CasRadio);
        }
        //else
        {
            RS485Cascade_CommonParameter(pSerial);
        }
    }
    else if ( CASCADE_CMD_ENOCEAN_REMAN_MASTER_2_SLAVE == u8Cmd )
    {
        CasRadio.u8PacketType = PACKET_REMOTE_MAN_COMMAND;

        CasRadio.Telegram.ReMan.u8Length = pSerial->pu8Receive[4] - 6;

        CasRadio.Param.ReMan.u32SourceId = pSerial->pu8Receive[6] << 24 | pSerial->pu8Receive[7]<<16 | pSerial->pu8Receive[8]<<8 | pSerial->pu8Receive[9];
        CasRadio.Telegram.ReMan.u16FnNum = pSerial->pu8Receive[10]<<8 | pSerial->pu8Receive[11];

        for (i = 0; i < CasRadio.Telegram.ReMan.u8Length;i++)
        {
            CasRadio.Telegram.ReMan.u8Data[i] = pSerial->pu8Receive[12 + i];
        }
        
        if ( RM_SUCCESS == RS485Cascade_EnOceanSlaverReman(&CasRadio) )
        {                
            EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM,&CasRadio);
        }
    }
    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485Cascade_SlaverEnOceanForward(Radio_Typedef *pCasRadio,SerialCascade_Typedef *pSerial)
{
    uint8_t i;
    uint16_t u16Crc;

    if ( PACKET_RADIO == pCasRadio->u8PacketType )
    {
        pSerial->pu8Send[0] = 0x55;
        pSerial->pu8Send[1] = pSerial->u8SendOccupyCount;
        pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
        pSerial->pu8Send[3] = 0xFF;
        pSerial->pu8Send[4] = pCasRadio->u16DataLength;
        pSerial->pu8Send[5] = CASCADE_CMD_ENOCEAN_RADIO_SLAVE_2_MASTER;

        pSerial->pu8Send[6] = pCasRadio->Telegram.raw.u8RORG;

        for (i = 0; i < pCasRadio->u16DataLength-1; i++)
        {
            pSerial->pu8Send[7 + i] = pCasRadio->Telegram.raw.bytes[i];
        }       
    }
    else if ( PACKET_REMOTE_MAN_COMMAND == pCasRadio->u8PacketType )
    {
        if ( pCasRadio->Telegram.ReMan.u8Length+12 > CASCADE_BUFF_MAX )
        {
            return !OK;
        }
        pSerial->pu8Send[0] = 0x55;
        pSerial->pu8Send[1] = pSerial->u8SendOccupyCount;
        pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
        pSerial->pu8Send[3] = 0xFF;
        pSerial->pu8Send[4] = pCasRadio->Telegram.ReMan.u8Length + 6;
        pSerial->pu8Send[5] = CASCADE_CMD_ENOCEAN_REMAN_SLAVE_2_MASTER;

        pSerial->pu8Send[6] = pCasRadio->Param.ReMan.u32DestinationId>>24;
        pSerial->pu8Send[7] = pCasRadio->Param.ReMan.u32DestinationId>>16;
        pSerial->pu8Send[8] = pCasRadio->Param.ReMan.u32DestinationId>>8;
        pSerial->pu8Send[9] = pCasRadio->Param.ReMan.u32DestinationId&0xFF;

        pSerial->pu8Send[10] = pCasRadio->Telegram.ReMan.u16FnNum >> 8;
        pSerial->pu8Send[11] = pCasRadio->Telegram.ReMan.u16FnNum&0xFF;
        
        for (i = 0; i < pCasRadio->Telegram.ReMan.u8Length; i++)
        {
            pSerial->pu8Send[12 + i] = pCasRadio->Telegram.ReMan.u8Data[i];
        }
    }
    else
    {
        return !OK;
    }

    pSerial->u16SendBytesMax = pSerial->pu8Send[4] + 8;

    u16Crc = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax - 2] = u16Crc&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax - 1] =   u16Crc>>8;
    
    pSerial->u8DataUpdateLock                   = 1;
    //pSerial->eState  = eSERIAL_BUS_STATE_SEND_DATA_WAIT;

    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
void RS485Cascade_SlaverModbusGetOffsetDelay(uint16_t u16RegID, uint16_t u16RegNums,SerialCascade_Typedef *pSerial)
{
    uint16_t u16Reg;
    uint8_t u8PhyAdd;

    if ( (u16RegID >= MODBUS_LIGHT_CASCADE_START) && (u16RegID <= MODBUS_LIGHT_CASCADE_END) )
    {
        u16Reg   = u16RegID>>8;
        u16Reg  -= 1;
        u8PhyAdd = u16Reg/4;

        if ( u8PhyAdd < u8CascadePhyAdd )
        {
            pSerial->u16SlaverDelaySendNms += u16RegNums;
        }
    }
    else if ( u16RegID >= MODBUS_SLAVER_DEV_INFO_START )
    {
        u8PhyAdd = u16RegID>>8;
        u8PhyAdd &= 0x0F;

        if ( u8PhyAdd < u8CascadePhyAdd )
        {
            pSerial->u16SlaverDelaySendNms += u16RegNums;
        }
    }    
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485Cascade_SlaverReplyModbus(SerialCascade_Typedef *pSerial)
{
    //uint8_t i;

    uint16_t u16CRC;
    //uint16_t u16Crc;
    //uint16_t u16Address;
    uint16_t u16RegID;
    uint16_t u16NRegs;
    //uint8_t  u8SendMax;
    uint16_t u16RegValue;
    uint8_t  u8Channel;
    uint16_t u16Nums;
    uint8_t  u8Index;
    uint8_t  u8Cmd;
    uint16_t u16Length;

    uint8_t *p8ReceiveBuff;
    uint8_t *p8SendBuff;    
    
    if ( pSerial->pu8Receive[5] != CASCADE_CMD_MODBUS_MASTER_2_SLAVE )
    {
        return !OK;
    }

    p8ReceiveBuff = &pSerial->pu8Receive[6];
    p8SendBuff    = &pSerial->pu8Send[6];
    u8Cmd         = p8ReceiveBuff[1];


    pSerial->pu8Send[0] = 0x55;
    pSerial->pu8Send[1] = 0x00;
    pSerial->pu8Send[2] = *pSerial->pu8PhyAddress;
    /* Reply the master */
    pSerial->pu8Send[3] = 0x00;
    pSerial->pu8Send[4] = u16Length;
    pSerial->pu8Send[5] = CASCADE_CMD_MODBUS_SLAVE_2_MASTER;

    pSerial->u16SendBytesMax = u16Length + 8;

    u16CRC = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax-2 );

    pSerial->pu8Send[pSerial->u16SendBytesMax - 2] = u16CRC&0xFF;
    pSerial->pu8Send[pSerial->u16SendBytesMax - 1] =   u16CRC>>8;
    
    pSerial->u8DataUpdateLock                   = 1;

    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
void RS485Cascade_SlaverReportSlaverEnOcean(void)
{
    
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485CascadeReceiveOK(SerialCascade_Typedef *pSerial)
{                
    if ( 0x00 == pSerial->u8SrcAddress )
    {
        /* Check the EnOcean receive info */
        if ( pSerial->pu8Receive[5] >= CASCADE_CMD_ENOCEAN_RADIO_MASTER_2_SLAVE )
        {
            /* Send data to the queue,and wait process the state */
            RS485CascadeSlaverReplyEnOcean(pSerial);
        }
        /* Check the RS485/modbus receive info */
        else if ( pSerial->pu8Receive[5] >= CASCADE_CMD_MODBUS_MASTER_2_SLAVE )
        {
            /* prepare the data to the master,and wait process the state */
            RS485Cascade_SlaverReplyModbus(pSerial);
        }        
        /* Check the RS485 reply cmd */            
        else
        {
            RS485Cascade_SlaverGetCommon(pSerial);
        }
    }
    else
    {                   
        /* Receive the slaver's DI status */
        RS485Cascade_SlaverGetCommon(pSerial);
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
    /* Send more the data for loop type */    
    if ( OK == EnOcean_GetSendQueuePopID(100) )
    {
        EnOcean_GetSendQueuePopData(&CasRadio);
        RS485Cascade_SlaverEnOceanForward(&CasRadio,pSerial);        
    }   
    else if ( OK == Cascade_GetSendQueuePopID() )
    {
        Cascade_ClearSendQueuePopID();

        if ( eDI_TYPE == CascadeSend.Data[CascadeSend.u8PopCount].u8MessageType )
        {
            
        }
    }
    else
    {
        pSerial->u8SendCmd = CASCADE_CMD_RESPONSE_CHANNEL;
        /* Send common data */
        RS485Cascade_CommonParameter(pSerial);
    }

    return !OK;
}
/* End of file */