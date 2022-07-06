
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


#include "..\BaselibInclude.h"
/** @addtogroup 
  * @{
  */
/** @addtogroup 
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

const eUSART_BAUD_TYPE eBaudRateTab[]=
{    
    eBAUD_1200,
    eBAUD_2400,
    eBAUD_4800,
    eBAUD_9600,
    eBAUD_19200,
    eBAUD_38400,
    eBAUD_57600,
    eBAUD_115200,
};

const uint16_t u16SendOneByteNeed_N_Us[]=
{    
    1000,
    500,
    250,
    125,
    62,
    32,
    16,
    8,
};

const uint8_t u8BaudRateBytePeriodNmsConfigTab[]=
{    
    80,
    40,
    20,
    10,
    3,
    3,
    3,
    3,
};

const uint8_t u8SerialRxTxShiftTimeConfigTab[]=
{    
    20,
    10,
    6,
    3,
    3,
    3,
    3,
    3,
};
/*
const USART_WordLength_TypeDef u8DataBits[]=
{
    USART_WordLength_8b,
    USART_WordLength_9b,
};
*/
/*
const eUSART_PARITY_TYPE eParity[]=
{
    ePARITY_NONE,
    ePARITY_EVEN ,
    ePARITY_ODD ,
};
*/


/**
  * @brief
  * @param
  * @retval None
  */            
void USART_Time_1ms(USART_Function_Typedef *pUSART)
{
    if ( pUSART->Frame.u8IdleNms )
    {
        pUSART->Frame.u8IdleNms--;
    }

    if ( pUSART->Frame.u8RxTxShiftNms )
    {
        pUSART->Frame.u8RxTxShiftNms--;
    }

    if ( pUSART->Frame.u16SendOverNms )
    {
        pUSART->Frame.u16SendOverNms--;
    }

    if ( pUSART->Frame.u16SendPeriod )
    {
        pUSART->Frame.u16SendPeriod--;
    }

    if ( pUSART->Frame.u16WaitReceiveOverNms )
    {
        pUSART->Frame.u16WaitReceiveOverNms--;
    }
    
}
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_Time_100ms(USART_Function_Typedef *pUSART)
{

}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_GetStateOfSendPeriod(Serial_Typedef *pSerial,uint16_t u16SendPeriod)
{
    if ( pSerial->u16WaitReceiveOverNms )
    {
        return !OK;
    }
    
    if ( 0 == pSerial->u16SendPeriod )
    {
        pSerial->u16SendPeriod      = u16SendPeriod;
        return OK;
    }
    
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
void USART_ReceiveFrameCount(Serial_Typedef *pSerial)
{
    pSerial->u32ReceiveCount       ++;
    pSerial->u16ReceiveBytesCnt = 0;
    pSerial->u8RxTxShiftNms   = u8SerialRxTxShiftTimeConfigTab[pSerial->u8BaudID];
    pSerial->u8IdleNms        = pSerial->u8IdleNmsConfig;
}
/**
   * @brief
   * @param
   * @retval
   */
uint8_t USART_GetBusyState(Serial_Typedef *pSerial)
{
    if (0 != pSerial->u16SendBytesCnt)
    {
        return !OK;
    }

    if (0 != pSerial->u16ReceiveBytesCnt)
    {
        return !OK;
    }

    if (0 != pSerial->u8IdleNms)
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
uint8_t USART_StateSetSend(Serial_Typedef *pSerial,uint16_t u16SendMax,uint8_t u8MessageType,uint16_t u16WaitOverNms)
{    
    /* Set the bus status */
    pSerial->u16SendBytesMax       = u16SendMax;
    pSerial->eTxState              = eSERIAL_BUS_STATE_IDLE;
    
    /* Receive ok and response the data to the master */
    /* Close interrupt */
    /* Shift the RS485 Chip direction to send */
    pSerial->u16SendBytesCnt       = 0;
    pSerial->u16ReceiveBytesCnt    = 0;
    pSerial->u8RxTxShiftNms        = u8SerialRxTxShiftTimeConfigTab[pSerial->u8BaudID];
    pSerial->u8IdleNms             = pSerial->u8IdleNmsConfig;
    pSerial->u8RetransCnt          = 1;
    pSerial->u8MessageType         = u8MessageType;
    pSerial->u16WaitReceiveOverNms = u16WaitOverNms;

    return OK;    
}
/**
  * @brief
  * @param
  * @retval None
  */
void USART_SetSendRetryCount(Serial_Typedef *pSerial,uint8_t u8RetryCount)
{
    pSerial->u8RetransCnt          = u8RetryCount;
}
/**
  * @brief
  * @param
  * @retval None
  */
void USART_ClearSendRetryCount(Serial_Typedef *pSerial)
{
    pSerial->u8RetransCnt          = 0;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_GetSendRetryCount(Serial_Typedef *pSerial)
{
    return pSerial->u8RetransCnt;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_SendOK(Serial_Typedef *pSerial)
{
    if ( eSERIAL_BUS_STATE_SEND_DATA == pSerial->eTxState )
    {
        pSerial->eTxState          = eSERIAL_BUS_STATE_SEND_DATA_OK;
        
        return OK;
    }
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */            
uint8_t USART_StateMachineHandler(USART_Function_Typedef *pUSART)
{
    //uint32_t u32SendRAMAddress;
    uint8_t  u8Status;
    u8Status = !OK;

    if ( eSERIAL_BUS_STATE_RECEIVE_OK == pUSART->Frame.eRxState )
    {
        pUSART->Frame.eRxState = eSERIAL_BUS_STATE_IDLE; 
        
        if ( OK == pUSART->SerialReceiveOK(&pUSART->Frame) )
        {
            USART_ReceiveFrameCount(&pUSART->Frame);
        }
    }
/*
    if (OK == pUSART->pDMATxSendStatus() )
    {
        u8Status = USART_SendOK(&pUSART->Frame);
    }
*/
    switch (pUSART->Frame.eTxState)
    {      
    case eSERIAL_BUS_STATE_INIT:
        pUSART->SerialDevInit(&pUSART->Frame);
        pUSART->pReceive();
        break;

    case eSERIAL_BUS_STATE_RESET_SLAVE:
        pUSART->Frame.eTxState = eSERIAL_BUS_STATE_IDLE;
        pUSART->Frame.eRxState = eSERIAL_BUS_STATE_IDLE;
        pUSART->SerialDevReset(&pUSART->Frame);
        pUSART->pReceive();
        break;

    case eSERIAL_BUS_STATE_ERROR_SLAVE:
        pUSART->Frame.eTxState = eSERIAL_BUS_STATE_IDLE;
        pUSART->Frame.eRxState = eSERIAL_BUS_STATE_IDLE;
        pUSART->SerialDevError(&pUSART->Frame);
        pUSART->pReceive();
        break;

    /* When slave bus's state is idle  */
    /* uart send message state process */
    case eSERIAL_BUS_STATE_IDLE:
        pUSART->pReceive();
    
        if (!pUSART->Frame.u8IdleNms)
        {            
            /* If master should prepair the data to transmit */
            if ( pUSART->Frame.u8RetransCnt )
            {                       
                pUSART->Frame.u8RetransCnt--;
                pUSART->Frame.eTxState  = eSERIAL_BUS_STATE_SEND_DATA_PREPAIR;                           
            }
            else
            {
                pUSART->Frame.u8DataUpdateLock = 0;
            }
        }        
        break;       

        /* ready send */
    case eSERIAL_BUS_STATE_SEND_DATA_PREPAIR :
        pUSART->pSend();

        if ( !pUSART->Frame.u8RxTxShiftNms )
        {
            pUSART->Frame.u16SendBytesCnt  = 0;
            pUSART->Frame.u16SendOverNms   = u16SendOneByteNeed_N_Us[pUSART->Frame.u8BaudID]*pUSART->Frame.u16SendBytesMax/10;
            //u32SendRAMAddress = (uint32_t)pUSART->Frame.pu8Send;
            pUSART->pStart(pUSART->Frame.u16SendBytesMax);
            pUSART->Frame.u8DataUpdateLock = 0;
            pUSART->Frame.eTxState         = eSERIAL_BUS_STATE_SEND_DATA;         // send       
        }
        break;

    case eSERIAL_BUS_STATE_SEND_DATA:
        /* interuppt send */
        if ( !pUSART->Frame.u16SendOverNms )
        {
            pUSART->Frame.eTxState = eSERIAL_BUS_STATE_ERROR_SLAVE;
        }
        break;
        /* shift to the wait response */
    case eSERIAL_BUS_STATE_SEND_DATA_OK:
        pUSART->Frame.eTxState        = eSERIAL_BUS_STATE_SEND_TO_RECEIVE_WAIT;
        pUSART->Frame.u8IdleNms       = pUSART->Frame.u8IdleNmsConfig;
        pUSART->Frame.u8RxTxShiftNms  = u8SerialRxTxShiftTimeConfigTab[pUSART->Frame.u8BaudID];         
        pUSART->Frame.u32SendCount    ++;
        break;

    case eSERIAL_BUS_STATE_SEND_TO_RECEIVE_WAIT:
        if ( pUSART->Frame.u8RxTxShiftNms )
        {
            pUSART->pSend();
            pUSART->pStop();
        }
        else
        {
            if ( 0 == pUSART->Frame.u16WaitReceiveOverNms )
            {
                pUSART->Frame.eTxState = eSERIAL_BUS_STATE_ERROR_SLAVE;
            }
            else
            {                                                                                
                pUSART->pReceive();
                u8Status = OK;
            }    
        }

        break;

    case eSERIAL_BUS_STATE_SEND_TO_IDLE:
        
        pUSART->Frame.eTxState               = eSERIAL_BUS_STATE_IDLE; 
        break;

    default:
        pUSART->Frame.eTxState = eSERIAL_BUS_STATE_IDLE;        
        break;
    }

    return u8Status;
}

/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_IdleInterruptGetDMABuff(Serial_Typedef *pSerial)
{
    uint16_t i;
    for ( i = 0; i < pSerial->u16ReceiveBytesMax; i++ )
    {
        pSerial->pu8Receive[i]           = pSerial->pu8DMAReceive[i];            
    }
 
    pSerial->eRxState             = eSERIAL_BUS_STATE_RECEIVE_OK;
    return OK;
}
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t USART_GetSendbuff(Serial_Typedef *pSerial,uint8_t *pu8Data)
{
    uint32_t u32SendOverNms;

    if ( pSerial->u16SendBytesCnt < pSerial->u16SendBytesMax )
    {
        *pu8Data      = pSerial->pu8Send[pSerial->u16SendBytesCnt];
        pSerial->u16SendBytesCnt++;                  
    }
    else
    {            
        pSerial->eTxState         = eSERIAL_BUS_STATE_SEND_DATA_OK;
        return OK;        
    }
    pSerial->u8IdleNms         = pSerial->u8IdleNmsConfig;
    pSerial->u8RxTxShiftNms    = u8SerialRxTxShiftTimeConfigTab[pSerial->u8BaudID];
    u32SendOverNms             = u16SendOneByteNeed_N_Us[pSerial->u8BaudID]*pSerial->u16SendBytesMax/10;
    pSerial->u16SendOverNms    = (uint16_t)u32SendOverNms;

    return !OK;
}
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_slave_get_receive_regs_info(Serial_Typedef *pSerial,uint16_t u16RegStart,uint16_t u16RegNums)
{
    pSerial->u16SlaveReceiveRegStart = u16RegStart;
    pSerial->u16SlaveReceiveRegNums  = u16RegNums;
    return OK;
}    
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_slave_receive_interrupt(Serial_Typedef *pSerial,uint8_t u8Data)
{
    if ( !pSerial->u8IdleNms )
    {   
        pSerial->u16ReceiveBytesCnt = 0;
    }
    /* Init Frame idle time */
    pSerial->u8IdleNms = pSerial->u8IdleNmsConfig;
    
    if (pSerial->u16ReceiveBytesCnt < pSerial->u16ReceiveBuffMax) 
    {
        pSerial->pu8Receive[pSerial->u16ReceiveBytesCnt] = u8Data; 
        switch (pSerial->u16ReceiveBytesCnt)
        {
        /* judge the phyaddress = receive byte0*/
        case 0:
            if ( u8Data == *pSerial->pu8PhyAddress )
            {                                
                pSerial->u16ReceiveBytesCnt++;
            }
            break;
        /* judge the modbus support command */
        case 1:
            switch (u8Data)
            {
                case MB_FUNC_READ_COILS                    :
                case MB_FUNC_READ_DISCRETE_INPUTS          :
                case MB_FUNC_WRITE_SINGLE_COIL             :
                case MB_FUNC_WRITE_MULTIPLE_COILS          :
                case MB_FUNC_READ_HOLDING_REGISTER         :
                case MB_FUNC_READ_INPUT_REGISTER           :
                case MB_FUNC_WRITE_REGISTER                :
                case MB_FUNC_WRITE_MULTIPLE_REGISTERS      :
                case MB_FUNC_READWRITE_MULTIPLE_REGISTERS  :
                    break;
                default:
                {
                    return !OK;
                }
            }
            
            pSerial->u16ReceiveBytesCnt++;
            break;
        /* Judge the modbus's command frame min length*/
        case 2:
            switch (pSerial->pu8Receive[1])
            {                
                case MB_FUNC_READ_DISCRETE_INPUTS          :                                    
                case MB_FUNC_WRITE_MULTIPLE_COILS          :
                    return !OK;

                case MB_FUNC_READ_COILS                    :     
                case MB_FUNC_WRITE_SINGLE_COIL             :    
                case MB_FUNC_READ_HOLDING_REGISTER         :
                case MB_FUNC_READ_INPUT_REGISTER           :
                case MB_FUNC_WRITE_REGISTER                :
                    pSerial->u16ReceiveBytesMax = 8;
                    break;
                case MB_FUNC_WRITE_MULTIPLE_REGISTERS      :
                    pSerial->u16ReceiveBytesMax = 9;
                    break;
                case MB_FUNC_READWRITE_MULTIPLE_REGISTERS  :
                    pSerial->u16ReceiveBytesMax = 13;
                    break;
                default:
                {
                    return !OK;
                }
            }
            
            pSerial->u16ReceiveBytesCnt++;
            break;
        /* Judge the write multiple regs frame length*/
        case 5:
            if ( MB_FUNC_WRITE_MULTIPLE_REGISTERS == pSerial->pu8Receive[1] )
            {
                pSerial->u16ReceiveBytesMax += u8Data*2;
            }
            /*
            switch (pSerial->pu8Receive[1])
            {                
                case MB_FUNC_READ_DISCRETE_INPUTS          :                                    
                case MB_FUNC_WRITE_MULTIPLE_COILS          :
                    return !OK;
                case MB_FUNC_READ_COILS                    :    
                    break;
                case MB_FUNC_WRITE_SINGLE_COIL             :    
                case MB_FUNC_READ_HOLDING_REGISTER         :
                case MB_FUNC_READ_INPUT_REGISTER           :
                case MB_FUNC_WRITE_REGISTER                :
                    pSerial->u16ReceiveBytesMax = 8;
                    break;
                case MB_FUNC_WRITE_MULTIPLE_REGISTERS      :
                    pSerial->u16ReceiveBytesMax += u8Data*2;
                    break;
                default:
                {
                    return !OK;
                }
            }
            */
            pSerial->u16ReceiveBytesCnt++;
            break;        
        default:
            if (  ( 10 == pSerial->u16ReceiveBytesCnt )
                &&( MB_FUNC_READWRITE_MULTIPLE_REGISTERS == pSerial->pu8Receive[1] ) )
            {
                pSerial->u16ReceiveBytesMax += pSerial->pu8Receive[10];
            }

            pSerial->u16ReceiveBytesCnt++;
            if ( pSerial->u16ReceiveBytesCnt >= pSerial->u16ReceiveBytesMax )
            {
                pSerial->u16ReceiveBytesCnt = 0;
                pSerial->eRxState = eSERIAL_BUS_STATE_RECEIVE_OK;
            }
            break;
        }   
        return OK;
    }
    return !OK;
}
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_master_get_write_regs_success_status(Serial_Typedef *pSerial)
{
    uint8_t  u8Cmd;
    uint16_t u16RegAddress;
    uint16_t u16NRegsOrValue;

    u8Cmd = pSerial->pu8Receive[1];
    
    switch (u8Cmd)
    {    
    case MB_FUNC_WRITE_REGISTER:
    case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
        u16RegAddress     = (uint16_t)pSerial->pu8Receive[2]<<8 | (uint16_t)pSerial->pu8Receive[3];
        u16NRegsOrValue   = (uint16_t)pSerial->pu8Receive[4]<<8 | (uint16_t)pSerial->pu8Receive[5];
        /* Clear retring tranismit count */
        if ( ( u16RegAddress == pSerial->u16MasterSendRegStart )&&(u16NRegsOrValue == pSerial->u16MasterSendRegNumsOrValue) ) 
        {
            USART_ClearSendRetryCount(pSerial);
            return OK;
        }
        
        break;            

    default:

        break;
                    
    }

    return !OK;  
}
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_master_send_setting(Serial_Typedef *pSerial,\
                                        uint8_t u8Cmd,\
                                        uint8_t u8SendPhyID,\
                                        uint16_t u16RegStart,\
                                        uint16_t u16RegNumsOrValue)
{
    uint16_t u16CRCModbus;

    pSerial->u8MasterSendPhyID            = u8SendPhyID;
    pSerial->u16MasterSendRegStart        = u16RegStart;
    pSerial->u16MasterSendRegNumsOrValue  = u16RegNumsOrValue;
    
    switch (u8Cmd)
    {                
        case MB_FUNC_READ_DISCRETE_INPUTS          :                                    
        case MB_FUNC_WRITE_MULTIPLE_COILS          :
            return !OK;
        case MB_FUNC_READ_COILS                    :    
        case MB_FUNC_READ_HOLDING_REGISTER         :
        case MB_FUNC_READ_INPUT_REGISTER           :
        case MB_FUNC_WRITE_SINGLE_COIL             : 
        case MB_FUNC_WRITE_REGISTER                :
            pSerial->pu8Send[0] = pSerial->u8MasterSendPhyID;
            pSerial->pu8Send[1] = u8Cmd;
            pSerial->pu8Send[2] = pSerial->u16MasterSendRegStart>>8;
            pSerial->pu8Send[3] = pSerial->u16MasterSendRegStart&0xFF;
            pSerial->pu8Send[4] = pSerial->u16MasterSendRegNumsOrValue>>8;
            pSerial->pu8Send[5] = pSerial->u16MasterSendRegNumsOrValue&0xFF;
            pSerial->u16SendBytesMax = 6;
            break;           
        case MB_FUNC_WRITE_MULTIPLE_REGISTERS      :
            pSerial->pu8Send[0] = pSerial->u8MasterSendPhyID;
            pSerial->pu8Send[1] = u8Cmd;
            pSerial->pu8Send[2] = pSerial->u16MasterSendRegStart>>8;
            pSerial->pu8Send[3] = pSerial->u16MasterSendRegStart&0xFF;
            pSerial->pu8Send[4] = pSerial->u16MasterSendRegNumsOrValue>>8;
            pSerial->pu8Send[5] = pSerial->u16MasterSendRegNumsOrValue&0xFF;
            pSerial->pu8Send[6] = pSerial->u16MasterSendRegNumsOrValue*2;
            pSerial->u16SendBytesMax = 7 + pSerial->pu8Send[6];
            break;
        case MB_FUNC_READWRITE_MULTIPLE_REGISTERS  :
            pSerial->pu8Send[0] = pSerial->u8MasterSendPhyID;
            pSerial->pu8Send[1] = u8Cmd;
            pSerial->pu8Send[2] = pSerial->u16MasterSendRegStart>>8;
            pSerial->pu8Send[3] = pSerial->u16MasterSendRegStart&0xFF;
            pSerial->pu8Send[4] = pSerial->u16MasterSendRegNumsOrValue>>8;
            pSerial->pu8Send[5] = pSerial->u16MasterSendRegNumsOrValue&0xFF;
            pSerial->u16SendBytesMax = 6;
            break;    
        default:
        {
            return !OK;
        }
    }
    u16CRCModbus = CRC16Get(pSerial->pu8Send,pSerial->u16SendBytesMax);
    
    pSerial->pu8Send[pSerial->u16SendBytesMax] = u16CRCModbus&0xFF;
    pSerial->u16SendBytesMax++;
    pSerial->pu8Send[pSerial->u16SendBytesMax] = u16CRCModbus>>8;
    pSerial->u16SendBytesMax++;
    return OK;
}
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_master_receive_interrupt(Serial_Typedef *pSerial,uint8_t u8Data)
{
    if ( !pSerial->u8IdleNms )
    {   
        pSerial->u16ReceiveBytesCnt = 0;
    }
    /* Init Frame idle time */
    pSerial->u8IdleNms = pSerial->u8IdleNmsConfig;
    
    if (pSerial->u16ReceiveBytesCnt < pSerial->u16ReceiveBuffMax) 
    {
        pSerial->pu8Receive[pSerial->u16ReceiveBytesCnt] = u8Data; 
        switch (pSerial->u16ReceiveBytesCnt)
        {
        case 0:
            if ( u8Data == pSerial->u8MasterSendPhyID )
            {                                
                pSerial->u16ReceiveBytesCnt++;
            }
            break;
        case 1:
            switch (pSerial->pu8Receive[1])
            {                
                case MB_FUNC_READ_DISCRETE_INPUTS          :                                    
                case MB_FUNC_WRITE_MULTIPLE_COILS          :
                    return !OK;
                case MB_FUNC_READ_COILS                    :    
                case MB_FUNC_READ_HOLDING_REGISTER         :
                case MB_FUNC_READ_INPUT_REGISTER           :
                case MB_FUNC_WRITE_SINGLE_COIL             :    
                case MB_FUNC_WRITE_REGISTER                :                    
                case MB_FUNC_WRITE_MULTIPLE_REGISTERS      :
                    break;
                case MB_FUNC_READWRITE_MULTIPLE_REGISTERS  :
                    pSerial->u16ReceiveBytesMax = 12;
                    break;
                default:
                {
                    return !OK;
                }
            }
            pSerial->u16ReceiveBytesCnt++;
            break;
        case 2:
            switch (pSerial->pu8Receive[1])
            {                
                case MB_FUNC_READ_DISCRETE_INPUTS          :                                    
                case MB_FUNC_WRITE_MULTIPLE_COILS          :
                    return !OK;
                case MB_FUNC_READ_COILS                    :    
                case MB_FUNC_READ_HOLDING_REGISTER         :
                case MB_FUNC_READ_INPUT_REGISTER           :
                    pSerial->u16ReceiveBytesMax = pSerial->pu8Receive[2] + 5;
                    break;

                case MB_FUNC_WRITE_SINGLE_COIL             :    
                case MB_FUNC_WRITE_REGISTER                :                    
                case MB_FUNC_WRITE_MULTIPLE_REGISTERS      :
                    pSerial->u16ReceiveBytesMax = 8;
                    break;
                case MB_FUNC_READWRITE_MULTIPLE_REGISTERS  :
                    break;    
                default:
                {
                    return !OK;
                }
            }            
            pSerial->u16ReceiveBytesCnt++;
            break;
        
        default:
            pSerial->u16ReceiveBytesCnt++;
            if ( pSerial->u16ReceiveBytesCnt >= pSerial->u16ReceiveBytesMax )
            {
                pSerial->u16ReceiveBytesCnt = 0;
                pSerial->eRxState = eSERIAL_BUS_STATE_RECEIVE_OK;
            }
            break;
        }   
        return OK;
    }
    return !OK;
}

#ifdef MODBUS_MASTER_TX_QUEUE_MAX
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_ClearSendQueuePopID(ModbusMasterSendQueue_Typedef *pQueue)
    {
        pQueue->Data[pQueue->u8PopCount].u8State = 0;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_GetQueueData(ModbusMasterSendQueue_Typedef *pQueue,uint8_t *pu8PhyAddress,uint8_t *pu8Cmd,uint16_t *pu16RegID,uint16_t *pu16RegNums,uint16_t *pu16RegValue)
    {    
        *pu8Cmd        = pQueue->Data[pQueue->u8PopCount].u8Cmd;
        *pu8PhyAddress = pQueue->Data[pQueue->u8PopCount].u8PhyAddress;
        *pu16RegID     = pQueue->Data[pQueue->u8PopCount].u16RegStart;
        *pu16RegNums   = pQueue->Data[pQueue->u8PushCount].u16RegNums;
        *pu16RegValue  = pQueue->Data[pQueue->u8PopCount].u16RegValue;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_SetQueueData(ModbusMasterSendQueue_Typedef *pQueue,uint8_t u8PhyAddress,uint8_t u8Cmd,uint16_t u16RegID,uint16_t u16RegNums,uint16_t u16RegValue)
    {    
        if ( OK != UART_modbus_master_GetSendQueuePushID(pQueue) ) 
        {      
            return ;
        }
        pQueue->Data[pQueue->u8PushCount].u8Cmd        = u8Cmd;
        pQueue->Data[pQueue->u8PushCount].u8PhyAddress = u8PhyAddress;
        pQueue->Data[pQueue->u8PushCount].u16RegStart  = u16RegID;
        pQueue->Data[pQueue->u8PushCount].u16RegNums   = u16RegNums;
        pQueue->Data[pQueue->u8PushCount].u16RegValue  = u16RegValue;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t UART_modbus_master_GetSendQueuePopID(ModbusMasterSendQueue_Typedef *pQueue)
    {
        uint8_t i;
        uint8_t j;

        UART_modbus_master_GetSendQueueFull(pQueue);

        if ( pQueue->u8PopCount >= MODBUS_MASTER_TX_QUEUE_MAX )
        {
            pQueue->u8PopCount = 0;
        }

        j = pQueue->u8PopCount;

        /*  Search the current id to the queue Max */
        for (i = j+1; i < MODBUS_MASTER_TX_QUEUE_MAX;i++)
        {
            if ( 0 == pQueue->Data[i].u8State ) 
            {
                continue;
            }

            pQueue->u8PopCount = i;
            pQueue->Data[i].u8State = 0;
            return OK;
        }
        
        /* Search the start 0 to the current id */
        for (i = 0; i < j; i++)
        {
            if ( 0 == pQueue->Data[i].u8State )
            {
                continue;  
            }
            pQueue->u8PopCount = i;
            pQueue->Data[i].u8State = 0;
            return OK;
        }

        return !OK;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t UART_modbus_master_GetSendQueueFull(ModbusMasterSendQueue_Typedef *pQueue)
    {
        uint8_t i;

        for (i = 0; i < MODBUS_MASTER_TX_QUEUE_MAX;i++)
        {
            if ( 0 == pQueue->Data[i].u8State )
            {
                pQueue->u8QueueFull = 0;
            }
        }

        return pQueue->u8QueueFull;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_SetSendQueueIDOccupy(ModbusMasterSendQueue_Typedef *pQueue)
    {
        pQueue->Data[pQueue->u8PushCount].u8State = 1;
    }
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t UART_modbus_master_GetSendQueuePushID(ModbusMasterSendQueue_Typedef *pQueue)
    {
        uint8_t i;
        uint8_t j;

        if ( pQueue->u8QueueFull )
        {
            return !OK;
        }

        j = pQueue->u8PushCount;

        /*  Search the current id to the queue Max */
        for (i = j+1; i < MODBUS_MASTER_TX_QUEUE_MAX;i++)
        {
            if ( 1 == pQueue->Data[i].u8State )
            {
                continue;
            }
            pQueue->u8PushCount = i;
            pQueue->Data[pQueue->u8PushCount].u8State = 1;
            return OK;
        }
        
        /* Search the start 0 to the current id */
        for (i = 0; i < j; i++)
        {
            if ( 1 == pQueue->Data[i].u8State )
            {
                continue;
            }
            pQueue->u8PushCount = i;
            pQueue->Data[pQueue->u8PushCount].u8State = 1;
            return OK;
        }
        pQueue->u8QueueFull = 1;

        return !OK;
    }
#endif
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_CascadeTime_1ms(Cascade_Function_Typedef *pUSART)
{
    if ( pUSART->Frame.u8RxTxShiftNms )
    {
        pUSART->Frame.u8RxTxShiftNms--;
    }

    if ( pUSART->Frame.u16SendOverNms )
    {
        pUSART->Frame.u16SendOverNms--;
    }

    if ( pUSART->Frame.u16MasterSendPeriodNms )
    {
        pUSART->Frame.u16MasterSendPeriodNms--;
    }

    if ( pUSART->Frame.u16SlaverDelaySendNms )
    {
        pUSART->Frame.u16SlaverDelaySendNms--;
    }
    
    if ( pUSART->Frame.u16BusIdleNms < 0xFFFF )
    {
        pUSART->Frame.u16BusIdleNms++;
    }

    if ( pUSART->Frame.u16SearchAddressPeriodNms )
    {
        pUSART->Frame.u16SearchAddressPeriodNms--;
    }
    //pUSART->Frame.u16CascadeSalverReceiveMasterTime ++;
}
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_CascadeTime_100ms(Cascade_Function_Typedef *pUSART)
{
    uint8_t i;

    for (i = 0; i < SERIAL_CASCADE_DEV_NUMS_MAX; i++)
    {
        if ( pUSART->Frame.u16OfflineTime[i] )
        {
            pUSART->Frame.u16OfflineTime[i]--;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t UASRT_CascadeFrameSendTime(SerialCascade_Typedef *pSerial)
{
    if (*pSerial->pu8PhyAddress > 0)
    {
        if ( ( 1 == pSerial->u8SendState )&&( !pSerial->u8BusBusyState ) )
        {
            if ( ( 0 == pSerial->u16SlaverDelaySendNms )&&(pSerial->u16BusIdleNms > 3) )
            {
                pSerial->u8SendState = 2;
            }
        }
    }
    else
    {
        if ( 0 == pSerial->u16MasterSendPeriodNms )
        {            
            if ( pSerial->u8SearchAddressCount )
            {
                pSerial->u8SearchAddressCount--;           
                pSerial->u16MasterSendPeriodNms    = SERIAL_CASCADE_MASTER_PERIOD;
                pSerial->u16SearchAddressPeriodNms = 10000;
                pSerial->u8SendCmd                 = 0x00;
            }
            else
            {
                if ( !pSerial->u8ReceiveWaitCount )
                {
                    if ( pSerial->u8SendOccupyCount )
                    {
                        pSerial->u16MasterSendPeriodNms   = 200;
                    }
                    else
                    {
                        
                        pSerial->u16MasterSendPeriodNms   = (pSerial->u8AddressMax+1)*SERIAL_CASCADE_DEV_INTERVAL + SERIAL_CASCADE_END_INTERVAL;

                        if ( 0 == pSerial->u16SearchAddressPeriodNms )
                        {
                            pSerial->u16SearchAddressPeriodNms = 30000;
                            pSerial->u8SearchAddressCount = 1;
                        }
                    }
                }
                else
                {
                    pSerial->u16MasterSendPeriodNms   = (pSerial->u8ReceiveWaitCount+1)*SERIAL_CASCADE_DEV_INTERVAL + SERIAL_CASCADE_END_INTERVAL;
                }
            }
                     
            if ( !pSerial->u8BusBusyState )
            {
                if ( pSerial->u16BusIdleNms > 3 )
                {
                    pSerial->u8SendState     = 2;
                }
            }                                   
        }        
    }

    if ( pSerial->u8BusBusyState )
    {
        pSerial->u16BusIdleNms = 0;
    }
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t UASRT_CascadeFrameSendOK(SerialCascade_Typedef *pSerial)
{
    pSerial->eState                = eSERIAL_BUS_STATE_SEND_TO_RECEIVE_WAIT;
    pSerial->u8SendState           = 0;
    
    if ( pSerial->u8SendOccupyCount )
    {
        pSerial->u8SendOccupyCount --;
        pSerial->u16SlaverDelaySendNms = 50;
        pSerial->u8SendState        = 1;
    }
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_CascadeReceiveClear(SerialCascade_Typedef *pSerial)
{
    /* Clear the receive the address */
    /* Receive ok and response the data to the master */    
    pSerial->u16ReceiveBytesMax = 0;        
    pSerial->u8RxTxShiftNms     = u8SerialRxTxShiftTimeConfigTab[pSerial->u8BaudID];    
    if ( eSERIAL_BUS_STATE_RECEIVE_OK == pSerial->eState )
    {
        pSerial->u32ReceiveCount    ++;
    }
    pSerial->eState             = eSERIAL_BUS_STATE_IDLE;
}
/**
 * @brief
 * @param
 * @retval None
 */ 
void USART_CascadeGetOnlineDevMask(SerialCascade_Typedef *pSerial)
{
    uint8_t i;

    if (*pSerial->pu8PhyAddress > 0)
    {
        if ( (*pSerial->pu16OnlineMask&0x0001) == 0x0000 )
        {
            pSerial->u32SlaverReceiveMasterCount = 0;
        }
    }
    *pSerial->pu16OnlineMask                        |= 1<<(*pSerial->pu8PhyAddress);
    pSerial->u16OfflineTime[*pSerial->pu8PhyAddress] = SERIAL_CASCADE_OFFLINE_TIME;//100*100ms = 10s
    *pSerial->pu8OnlineNums = 0;
    for (i = 0; i < SERIAL_CASCADE_DEV_NUMS_MAX; i ++)
    {
        if ( !pSerial->u16OfflineTime[i] )
        {
            *pSerial->pu16OnlineMask &= ~(1<<i); 
        }
        if ( *pSerial->pu16OnlineMask&(1<<i) )
        {
            (*pSerial->pu8OnlineNums)++;
        }
    }
}
/**
 * @brief
 * @param
 * @retval None
 */ 
uint8_t USART_CascadeGetOnlineDevNums(SerialCascade_Typedef *pSerial)
{
    return (*pSerial->pu8OnlineNums);
}
/**
  * @brief
  * @param
  * @retval None
  */ 
uint8_t USART_CascadePhyAddressGetOnline(SerialCascade_Typedef *pSerial,uint8_t u8PhyAdd)
{
    if ( *pSerial->pu16OnlineMask&(1<<u8PhyAdd) )
    {
        return OK;
    }
    return !OK;
} 
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_CascadeHandler(Cascade_Function_Typedef *pUSART)
{
    uint8_t u8Status;
    //uint32_t u32SendRAMAddress;

    u8Status = 0xFF;
    
    pUSART->Frame.u8BusBusyState = pUSART->pGetBusBusy();

    USART_CascadeGetOnlineDevMask(&pUSART->Frame);
    UASRT_CascadeFrameSendTime(&pUSART->Frame);

    switch (pUSART->Frame.eState)
    {  
    case eSERIAL_BUS_STATE_RECEIVE_OK:
        /* Get time for send data */
        if ( OK == USART_CascadeReceiveFrameTime(&pUSART->Frame) )
        {        
            u8Status = pUSART->SerialReceiveOK(&pUSART->Frame);
        }
    
        /* Clear the frame status*/
        USART_CascadeReceiveClear(&pUSART->Frame);
        return u8Status;
        break;

    case eSERIAL_BUS_STATE_INIT:
        //pUSART->SerialDevInit(&pUSART->Frame);
        pUSART->pReceive();
        break;

    case eSERIAL_BUS_STATE_RESET_SLAVE:
        pUSART->SerialDevReset(&pUSART->Frame);
        pUSART->pReceive();
        break;

    case eSERIAL_BUS_STATE_ERROR_SLAVE:
        pUSART->SerialDevError(&pUSART->Frame);
        pUSART->pReceive();
        break;
    /* When slave bus's state is idle  */
    /* uart send message state process */
    case eSERIAL_BUS_STATE_IDLE:
        /* If master should prepair the data to transmit */
        pUSART->pReceive();
        if ( 2 == pUSART->Frame.u8SendState )
        {                       
            pUSART->Frame.u8SendState       = 3;
            pUSART->Frame.eState            = eSERIAL_BUS_STATE_SEND_DATA_PREPAIR;
            pUSART->Frame.u8RxTxShiftNms    = 3;
            
        }        
        break;    
        /* Ovf the time and clear the cnt,Master have the function */
        /*
    case eSERIAL_BUS_STATE_MASTER_WAIT_SLAVE_RESPONSE:
        //pUSART->Frame.u8IdleNms = pUSART->Frame.u8IdleNmsConfig;
        if ( !pUSART->Frame.u8RetransCnt )
        {
            pUSART->Frame.eState = eSERIAL_BUS_STATE_IDLE;

            pUSART->SerialDevError(&pUSART->Frame);
            return !OK; // end of the send process
        }
        break;
        */
        /* ready send */
    case eSERIAL_BUS_STATE_SEND_DATA_PREPAIR :
        pUSART->pSend();

        if ( !pUSART->Frame.u8DataUpdateLock )
        {
            pUSART->SerialSendPrepair(&pUSART->Frame);
        }

        if ( !pUSART->Frame.u8RxTxShiftNms )
        {
            pUSART->Frame.u8DataUpdateLock  = 0;
            pUSART->Frame.eState          = eSERIAL_BUS_STATE_SEND_DATA;
            pUSART->Frame.u16SendOverNms = pUSART->Frame.u16SendBytesMax * 10;
            
            pUSART->pStart(pUSART->Frame.u16SendBytesMax);            
        }
        break;
    
    case eSERIAL_BUS_STATE_SEND_DATA:
        /* interuppt send */
        if ( !pUSART->Frame.u16SendOverNms )
        {
            pUSART->Frame.eState = eSERIAL_BUS_STATE_ERROR_SLAVE;
        }
        break;
        /* shift to the wait response */
    case eSERIAL_BUS_STATE_SEND_DATA_OK:
        
        UASRT_CascadeFrameSendOK(&pUSART->Frame);

        break;
    case eSERIAL_BUS_STATE_SEND_TO_RECEIVE_WAIT:
        if ( pUSART->Frame.u8RxTxShiftNms )
        {
            pUSART->pSend();
        }
        else
        {
            
            {
                pUSART->pReceive();

                pUSART->Frame.eState = eSERIAL_BUS_STATE_IDLE;
                pUSART->Frame.u32SendCount            ++;
            }
            
        }
        break;
    case eSERIAL_BUS_STATE_SEND_TO_IDLE:
        
        pUSART->Frame.eState               = eSERIAL_BUS_STATE_IDLE;
        
        break;
    default:
        pUSART->Frame.eState = eSERIAL_BUS_STATE_IDLE;
        break;
    }

    return !OK;
}
/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_CascadeReceiveFrameTime(SerialCascade_Typedef *pSerial)
{
    int16_t i;

    pSerial->u8ReceiveWaitCount = pSerial->pu8Receive[1];
    pSerial->u8SrcAddress       = pSerial->pu8Receive[2];
    pSerial->u8DstAddress       = pSerial->pu8Receive[3];
    //pSerial->u8ReceiveCmd       = pSerial->pu8Receive[5];
    /* Check the frame length*/    
    if ( pSerial->u16ReceiveBytesMax != pSerial->pu8Receive[4] + 8 )
    {
        pSerial->eState             = eSERIAL_BUS_STATE_IDLE;
        return !OK;        
    }
    /* Check the frame data CRC16 */
    if (0x00 != CRC16Get(pSerial->pu8Receive, pSerial->u16ReceiveBytesMax))
    {
        pSerial->eState             = eSERIAL_BUS_STATE_IDLE;
        return !OK;
    }
    
    /* Set online the mask */
    if ( pSerial->u8SrcAddress < SERIAL_CASCADE_DEV_NUMS_MAX )
    {
        *pSerial->pu16OnlineMask             |= 1<<pSerial->u8SrcAddress;

        pSerial->u16OfflineTime[pSerial->u8SrcAddress] = SERIAL_CASCADE_OFFLINE_TIME;//SERIAL_CASCADE_OFFLINE_TIME*100ms
    }
    /*************************************************************************************************/
    for (i = SERIAL_CASCADE_DEV_NUMS_MAX-1; i >= 0; i--)
    {
        if ( ( *pSerial->pu16OnlineMask&(1<<i) )&&(pSerial->u8AddressMax < i ) )
        {
            /* Record the dev max address */            
            pSerial->u8AddressMax = i;
            break;
        }
    }

    /* Receive the master, and the slave process */
    if ( ( *pSerial->pu8PhyAddress > 0 )&&( *pSerial->pu8PhyAddress < SERIAL_CASCADE_DEV_NUMS_MAX ) )
    {   
        if ( 0x00 == pSerial->u8SrcAddress )
        {
            /* Set slaver state, wait the delay time to send */
            /* Set max wait time */                  
            pSerial->u16SlaverDelaySendNms                 = (*pSerial->pu8PhyAddress)*(pSerial->u16ReceiveBytesMax+5);                        
            pSerial->u8SendState                           = 1;
            
            pSerial->u32SlaverReceiveMasterCount          ++;    
            *pSerial->pu16OnlineMask                      |= 1<<(*pSerial->pu8PhyAddress);
            pSerial->u16OfflineTime[*pSerial->pu8PhyAddress] = SERIAL_CASCADE_OFFLINE_TIME;//SERIAL_CASCADE_OFFLINE_TIME*100ms            
        }
        else if ( *pSerial->pu8PhyAddress > pSerial->u8SrcAddress )
        {
            
        }

        if ( pSerial->u8ReceiveWaitCount ) 
        {
            if ( *pSerial->pu8PhyAddress >= pSerial->u8SrcAddress )
            {
                pSerial->u16SlaverDelaySendNms += pSerial->u8ReceiveWaitCount*SERIAL_CASCADE_DEV_INTERVAL;
            }
            else
            {
                pSerial->u16SlaverDelaySendNms  = 500;
            }
        }        
    }
    /* Master receive the slave data */
    else
    {        
        /* Clear the Last Address,and search every time */
        /* Get the every communication ,response address */    
        if ( !pSerial->u8ReceiveWaitCount )
        {
            if ( !pSerial->u8SearchAddressCount )
            {                                   
                if ( pSerial->u8AddressMax == pSerial->u8SrcAddress )
                {
                    pSerial->u16MasterSendPeriodNms = SERIAL_CASCADE_END_INTERVAL;
                }                
            }
        }
        else
        {
            if ( 0 == pSerial->u8AddressMax )
            {
                pSerial->u8ReceiveWaitCount = 0;
                pSerial->u16MasterSendPeriodNms = 1000;
            }
            else
            {
                pSerial->u16MasterSendPeriodNms = pSerial->u8ReceiveWaitCount*SERIAL_CASCADE_END_INTERVAL + 500;
            }
        }
    }
        
   
    return OK;
}
/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_IdleInterruptCascadeGetDMABuff(SerialCascade_Typedef *pSerial)
{
    uint16_t i;

    if ( pSerial->u16ReceiveBytesMax < 8 )
    {
        return !OK;
    }

    for ( i = 0; i < pSerial->u16ReceiveBytesMax; i++ )
    {
        pSerial->pu8Receive[i]           = pSerial->pu8DMAReceive[i];            
    }
    
    pSerial->eState             = eSERIAL_BUS_STATE_RECEIVE_OK;
    return OK;
}


/* End of file */