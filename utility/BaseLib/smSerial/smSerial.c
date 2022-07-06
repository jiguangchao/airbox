
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
const USART_WordLength_TypeDef u8DataBits[]=
{
    USART_WordLength_8b,
    USART_WordLength_9b,
};
const eUSART_PARITY_TYPE eParity[]=
{
    ePARITY_NONE,
    ePARITY_EVEN ,
    ePARITY_ODD ,
};



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
uint8_t USART_StateSetSend(Serial_Typedef *pSerial,uint16_t u16SendMax,uint8_t u8SendState,uint16_t u16WaitOverNms)
{    
    /* Set the bus status */
    pSerial->u16SendBytesMax       = u16SendMax;
    pSerial->eTxState              = eSERIAL_BUS_STATE_IDLE;

    /* Receive ok and response the data to the master */
    /* Close interrupt */
    /* Shift the RS485 Chip direction to send */
    pSerial->u16SendBytesCnt       = 0;        
    //pSerial->u32ReceiveCount       ++;
    pSerial->u32SendCount            ++;
    pSerial->u16ReceiveBytesCnt    = 0;
    pSerial->u8RxTxShiftNms        = 3;//u8SerialRxTxShiftTimeConfigTab[pSerial->eBaudID];
    pSerial->u8IdleNms             = pSerial->u8IdleNmsConfig;
    pSerial->u8RetransCnt          = 1;
    pSerial->u8WaitReceiveState    = u8SendState;
    pSerial->u16WaitReceiveOverNms = u16WaitOverNms;

    return OK;    
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_ReceiveCount(Serial_Typedef *pSerial)
{    
          
    pSerial->u32ReceiveCount       ++;
 

    return OK;    
}
/**
  * @brief
  * @param
  * @retval None
  */            
uint8_t USART_StateMachineHandler(USART_Function_Typedef *pUSART)
{
    if ( eSERIAL_BUS_STATE_RECEIVE_OK == pUSART->Frame.eRxState )
    {
        pUSART->SerialReceiveOK(&pUSART->Frame);
    }

    switch (pUSART->Frame.eTxState)
    {      
    case eSERIAL_BUS_STATE_INIT:
        pUSART->SerialDevInit(&pUSART->Frame);
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
        pUSART->pReceive();
    
        if (!pUSART->Frame.u8IdleNms)
        {            
            /* If master should prepair the data to transmit */
            if ( pUSART->Frame.u8RetransCnt )
            {                       
                pUSART->Frame.u8RetransCnt--;
                pUSART->Frame.eTxState  = eSERIAL_BUS_STATE_SEND_DATA_PREPAIR;                           
            }
        }        
        break;       

        /* ready send */
    case eSERIAL_BUS_STATE_SEND_DATA_PREPAIR :
        pUSART->pSend();

        if ( !pUSART->Frame.u8RxTxShiftNms )
        {
            pUSART->Frame.u16SendBytesCnt = 0;
            pUSART->Frame.u16SendOverNms  = u16SendOneByteNeed_N_Us[pUSART->Frame.eBaudID]*pUSART->Frame.u16SendBytesMax/10;
            pUSART->pStart(pUSART->Frame.u16SendBytesMax);

            pUSART->Frame.eTxState = eSERIAL_BUS_STATE_SEND_DATA;         // send       
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
        pUSART->Frame.eTxState     = eSERIAL_BUS_STATE_SEND_TO_RECEIVE_WAIT;
        pUSART->Frame.u16SendBytesCnt = 0;        
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
                pUSART->Frame.eTxState = eSERIAL_BUS_STATE_SEND_TO_IDLE;
            }
            pUSART->pReceive();                    
            //pUSART->Frame.u32SendCount            ++;
        }

        break;

    case eSERIAL_BUS_STATE_SEND_TO_IDLE:
        
        pUSART->Frame.eTxState               = eSERIAL_BUS_STATE_IDLE;        
        break;

    default:
        pUSART->Frame.eTxState = eSERIAL_BUS_STATE_IDLE;        
        break;
    }

    return !OK;
}

/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_IdleInterruptGetDMABuff(Serial_Typedef *pSerial)
{
    uint16_t i;
    /*
    if ( pSerial->u16ReceiveBytesMax < 8 )
    {
        return !OK;
    }
    */
    for ( i = 0; i < pSerial->u16ReceiveBytesMax; i++ )
    {
        pSerial->pu8Receive[i]           = pSerial->pu8DMAReceive[i];            
    }
 
    pSerial->eRxState             = eSERIAL_BUS_STATE_RECEIVE_OK;
    return OK;
}
#if 0
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t USART_GetTransmitData(USART_Function_Typedef *pUSART)
    {
        if ( pUSART->Frame.u16SendBytesCnt < pUSART->Frame.u16SendBytesMax )
        {
            pUSART->Frame.u8DR = pUSART->Frame.pu8Send[pUSART->Frame.u16SendBytesCnt];             
            pUSART->Frame.u16SendBytesCnt++;            

            return OK;
        }
        else
        {            
            pUSART->Frame.eState         = eSERIAL_BUS_STATE_SEND_TO_RECEIVE_WAIT;                       
        }
        pUSART->Frame.u8IdleNms         = pUSART->Frame.u8IdleNmsConfig;
        pUSART->Frame.u8RxTxShiftNms    = u8SerialRxTxShiftTimeConfigTab[pUSART->Frame.eBaudID];
        pUSART->Frame.u16SendOverNms    = SERIAL_INTPERRUT_SEND_OVER_TIME;//u16SendOneByteNeed_N_Us[pUSART->Frame.eBaudID]*pUSART->Frame.u16SendBytesMax/10;

        return !OK;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t USART_GetReceiveData(USART_Function_Typedef *pUSART)
    {
        if ( !pUSART->Frame.u8IdleNms )
        {   
            pUSART->Frame.u16ReceiveBytesCnt = 0;
        }
        /* Init Frame idle time */
        pUSART->Frame.u8IdleNms = pUSART->Frame.u8IdleNmsConfig;
        
        if (pUSART->Frame.u16ReceiveBytesCnt < 250) 
        {
            pUSART->Frame.pu8Receive[pUSART->Frame.u16ReceiveBytesCnt] = pUSART->Frame.u8DR; 
            switch (pUSART->Frame.u16ReceiveBytesCnt)
            {
            case 0:
                if ( pUSART->Frame.u8DR == pUSART->Frame.u8PhyAddress )
                {                                
                    pUSART->Frame.u16ReceiveBytesCnt++;
                }
                break;
            case 1:       
                pUSART->Frame.u16ReceiveBytesCnt++;
                break;
            case 2:
                pUSART->Frame.u16ReceiveBytesMax = 8;
                pUSART->Frame.u16ReceiveBytesCnt++;
                break;
            default:
                pUSART->Frame.u16ReceiveBytesCnt++;
                if ( pUSART->Frame.u16ReceiveBytesCnt >= pUSART->Frame.u16ReceiveBytesMax )
                {
                    pUSART->Frame.u16ReceiveBytesCnt = 0;
                    pUSART->Frame.eState = eSERIAL_BUS_STATE_RECEIVE_OK;
                }
                break;
            }   
            return OK;
        }
        return !OK;
    }
#endif
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
        if ( 1 == pSerial->u8SendState )
        {
            if ( ( 0 == pSerial->u16SlaverDelaySendNms )&&(pSerial->u16BusIdleNms > 3) )
            {
                if ( !pSerial->u8BusBusyState )
                {
                    pSerial->u8SendState = 2;                
                }            
            }
        }
    }
    else
    {
        if ( 0 == pSerial->u16MasterSendPeriodNms )
        {
            pSerial->eState                        = eSERIAL_BUS_STATE_IDLE;

            if ( pSerial->u8SearchAddressCount )
            {
                pSerial->u8SearchAddressCount--;           
                pSerial->u16MasterSendPeriodNms    = SERIAL_CASCADE_MASTER_PERIOD;
                pSerial->u16SearchAddressPeriodNms = 10000;
                pSerial->u8SendCmd                 = 0x00;
            }
            else
            {
                if ( pSerial->u8SendOccupyCount )
                {
                    pSerial->u16MasterSendPeriodNms   = 200;
                }
                else
                {
                    pSerial->u16MasterSendPeriodNms   = pSerial->u8AddressMax*SERIAL_CASCADE_DEV_INTERVAL + SERIAL_CASCADE_END_INTERVAL;

                    if ( 0 == pSerial->u16SearchAddressPeriodNms )
                    {
                        pSerial->u8SearchAddressCount = 1;
                    }
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
    pSerial->u8RxTxShiftNms     = u8SerialRxTxShiftTimeConfigTab[pSerial->eBaudID];    
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
        if ( (pSerial->u16OnlineMask&0x0001) == 0x0000 )
        {
            pSerial->u32SlaverReceiveMasterCount = 0;
        }
    }
    pSerial->u16OnlineMask                          |= 1<<(*pSerial->pu8PhyAddress);
    pSerial->u16OfflineTime[*pSerial->pu8PhyAddress] = SERIAL_CASCADE_OFFLINE_TIME;//100*100ms = 10s
    pSerial->u8OnlineNums = 0;
    for (i = 0; i < SERIAL_CASCADE_DEV_NUMS_MAX; i ++)
    {
        if ( !pSerial->u16OfflineTime[i] )
        {
            pSerial->u16OnlineMask &= ~(1<<i); 
        }
        if ( pSerial->u16OnlineMask&(1<<i) )
        {
            pSerial->u8OnlineNums++;
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
    return pSerial->u8OnlineNums;
}
/**
  * @brief
  * @param
  * @retval None
  */ 
uint8_t USART_CascadePhyAddressGetOnline(SerialCascade_Typedef *pSerial,uint8_t u8PhyAdd)
{
    if ( pSerial->u16OnlineMask&(1<<u8PhyAdd) )
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
            pUSART->Frame.u16SendOverNms = pUSART->Frame.u16SendBytesMax + 10;
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
            pUSART->pReceive();

            pUSART->Frame.eState = eSERIAL_BUS_STATE_IDLE;
            //pUSART->Frame.u32SendCount            ++;
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
    pSerial->u8ReceiveCmd       = pSerial->pu8Receive[5];
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
        pSerial->u16OnlineMask             |= 1<<pSerial->u8SrcAddress;

        pSerial->u16OfflineTime[pSerial->u8SrcAddress] = SERIAL_CASCADE_OFFLINE_TIME;//SERIAL_CASCADE_OFFLINE_TIME*100ms
    }
    /*************************************************************************************************/
    for (i = SERIAL_CASCADE_DEV_NUMS_MAX-1; i >= 0; i--)
    {
        if ( ( pSerial->u16OnlineMask&(1<<i) )&&(pSerial->u8AddressMax < i ) )
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
            if ( 0x00 == pSerial->u8ReceiveCmd )
            {
                pSerial->u16SlaverDelaySendNms             = (*pSerial->pu8PhyAddress)*SERIAL_CASCADE_DEV_INTERVAL;
            }
            
            pSerial->u8SendState                           = 1;
            
            pSerial->u32SlaverReceiveMasterCount          ++;    
            pSerial->u16OnlineMask                        |= 1<<(*pSerial->pu8PhyAddress);
            pSerial->u16OfflineTime[*pSerial->pu8PhyAddress] = SERIAL_CASCADE_OFFLINE_TIME;//SERIAL_CASCADE_OFFLINE_TIME*100ms            
        }

        if ( pSerial->u8ReceiveCmd > 0x00)
        {
            if ( ( pSerial->u8SrcAddress < *pSerial->pu8PhyAddress )&&(pSerial->u8AddressPre < pSerial->u8SrcAddress ) )
            {
                pSerial->u8AddressPre = pSerial->u8SrcAddress;
            }
            else if (pSerial->u8AddressPre == pSerial->u8SrcAddress)
            {
                pSerial->u16SlaverDelaySendNms = SERIAL_CASCADE_DEV_INTERVAL;
            }
        }
        
        
        if ( pSerial->u8ReceiveWaitCount ) 
        {
            pSerial->u16SlaverDelaySendNms += pSerial->u8ReceiveWaitCount*SERIAL_CASCADE_DEV_INTERVAL;
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
            pSerial->u16MasterSendPeriodNms = pSerial->u8ReceiveWaitCount*SERIAL_CASCADE_DEV_INTERVAL*6 + 1000;
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