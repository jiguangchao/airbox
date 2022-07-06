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



#include "BSP.h"
#include "main.h"
#include "RS485Cascade.h"
#include "RS485Modbus.h"
#include "EnOceanFun.h"


#ifdef MODBUS_485_CRC_DISABLE
    #pragma message("MODBUS_485_CRC_DISABLE")
#else
    #pragma message("MODBUS_485_CRC_ENABLE")
#endif

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
/* An array of Modbus functions handlers which associates Modbus function
 * codes with implementing functions.
 */
 

uint8_t RS485ModbusBuff[RS485_MODBUS_TX_BUFF];
uint8_t RS485ModbusDMABuff[RS485_MODBUS_RX_BUFF];

USART_Function_Typedef RS485Modbus;
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485ModbusGetBusyState(void)
{
    if (0 != RS485Modbus.Frame.u16SendBytesCnt)
    {
        return !OK;
    }

    if (0 != RS485Modbus.Frame.u16ReceiveBytesCnt)
    {
        return !OK;
    }

    if (0 != RS485Modbus.Frame.u8IdleNms)
    {
        return !OK;
    }

    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485ModbusInit(USART_Function_Typedef *pUSART)
{
    pUSART->Frame.pu8Receive              = RS485ModbusBuff;
    pUSART->Frame.pu8Send                 = RS485ModbusBuff;
    pUSART->Frame.pu8DMAReceive           = RS485ModbusDMABuff;
    pUSART->Frame.u16ReceiveBuffMax       = RS485_MODBUS_RX_BUFF;
    pUSART->Frame.u8IdleNmsConfig        = u8BaudRateBytePeriodNmsConfigTab[pUSART->Frame.u8BaudID];

    pUSART->SerialDevInit                 = NULL;
    //pUSART->SerialHardWareSetting         = NULL;//RS485MB_HardwareSetting;
    pUSART->SerialReceiveOK               = RS485ModbusReceiveOK;
    pUSART->SerialDevError                = RS485ModbusDevError;
    //pUSART->SerialDevFrameTime            = NULL;
    pUSART->SerialDevReset                = RS485ModbusReset;
    //pUSART->SerialSendPrepair             = NULL;

    pUSART->pStart                        = BSP_RS485ModbusSendStart;
    pUSART->pStop                         = BSP_RS485ModbusSendStop;
    pUSART->pSend                         = BSP_RS485ModbusDirectSend;
    pUSART->pReceive                      = BSP_RS485ModbusDirectReceive;

    pUSART->pReceive();
    
    BSP_ModbusUsartDMA_Init(RS485ModbusDMABuff,RS485ModbusBuff);
    BSP_ModbusUSART_Init((uint32_t)eBaudRateTab[pUSART->Frame.u8BaudID], pUSART->Frame.u8Stop, pUSART->Frame.u8Parity);

    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusSendOK(void)
{
    if ( eSERIAL_BUS_STATE_SEND_DATA == RS485Modbus.Frame.eTxState )
    {
        RS485Modbus.Frame.eTxState           = eSERIAL_BUS_STATE_SEND_DATA_OK;        
        return OK;
    }
    return !OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusReset(Serial_Typedef *pSerial)
{
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;
    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusReceiveOK(Serial_Typedef *pSerial)
{    
    //uint16_t u16RegID;
    //uint8_t  u8Cmd;
    //uint8_t  
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;        
    
    //u16RegID = pSerial->pu8Receive[2]<<8 | pSerial->pu8Receive[3];        
    //u8Cmd    = pSerial->pu8Receive[1];

    if ( pSerial->pu8Receive[0] != *pSerial->pu8PhyAddress )
    {            
        return !OK;
    }

    /* Deveice address */
    if ( RS485ModbusRTU(pSerial->pu8Receive,pSerial->pu8Send,&pSerial->u16ReceiveBytesMax) )
    {
        pSerial->u16ReceiveBytesMax = 0;
        pSerial->eTxState            = eSERIAL_BUS_STATE_IDLE;
        return !OK;
    }

    
    USART_StateSetSend(pSerial,pSerial->u16ReceiveBytesMax,0,500);
   
    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusDevError(Serial_Typedef *pSerial)
{
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;
    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485ModbusRTUAbnormal(uint8_t *p8ReceiveBuff,uint8_t *p8SendBuff,uint8_t u8Code)
{
    uint16_t u16CRC;

    p8SendBuff[0] = p8ReceiveBuff[0];
    p8SendBuff[1] = p8ReceiveBuff[1]|0x80;
    p8SendBuff[2] = u8Code;
    u16CRC        = CRC16Get( p8SendBuff, 3 );
    p8SendBuff[3] = u16CRC&0xFF;
    p8SendBuff[4] = u16CRC>>8;
    return 0;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485ModbusRTU(uint8_t *p8ReceiveBuff,uint8_t *p8SendBuff,uint16_t *pu16Length)
{
    return UpgradeModbusReceiveReply(p8ReceiveBuff,p8SendBuff,pu16Length);
}
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/


/* End of file */