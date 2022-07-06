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

#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "CH2O_CO2.h"
#include "EnOceanCascade.h"
#include "Key.h"
/*
#ifdef MODBUS_485_CRC_DISABLE
    #pragma message("MODBUS_485_CRC_DISABLE")
#else
    #pragma message("MODBUS_485_CRC_ENABLE")
#endif
*/
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

uint8_t CH2O_CO2_TX_Buff[CH2O_CO2_TX_BUFF];
uint8_t CH2O_CO2_RX_Buff[CH2O_CO2_RX_BUFF];
uint8_t CH2O_CO2_DMABuff[CH2O_CO2_RX_BUFF];

//USART_Function_Typedef CH2O_CO2;
CH2O_CO2_Typedef CH2O_CO2;
USART_Function_Typedef CH2O_CO2_UART;
/**
 * @brief
 * @param
 * @retval
 */
uint8_t CH2O_CO2GetBusyState(void)
{
    if (0 != CH2O_CO2_UART.Frame.u16SendBytesCnt)
    {
        return !OK;
    }

    if (0 != CH2O_CO2_UART.Frame.u16ReceiveBytesCnt)
    {
        return !OK;
    }

    if (0 != CH2O_CO2_UART.Frame.u8IdleNms)
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

uint8_t CH2O_CO2Init(USART_Function_Typedef *pUSART)
{
    pUSART->Frame.pu8Receive = CH2O_CO2_RX_Buff;
    pUSART->Frame.pu8Send = CH2O_CO2_TX_Buff;
    pUSART->Frame.pu8DMAReceive = CH2O_CO2_DMABuff;
    pUSART->Frame.u16ReceiveBuffMax = CH2O_CO2_RX_BUFF;
    pUSART->Frame.u8IdleNmsConfig = u8BaudRateBytePeriodNmsConfigTab[pUSART->Frame.eBaudID];

    pUSART->SerialDevInit = NULL;
    //pUSART->SerialHardWareSetting         = NULL;//RS485MB_HardwareSetting;
    pUSART->SerialReceiveOK = CH2O_CO2ReceiveOK;
    pUSART->SerialDevError = CH2O_CO2DevError;
    //pUSART->SerialDevFrameTime            = NULL;
    pUSART->SerialDevReset = CH2O_CO2Reset;
    //pUSART->SerialSendPrepair             = NULL;

    pUSART->pStart = BSP_CH2O_CO2SendStart;
    pUSART->pStop = BSP_CH2O_CO2SendStop;
    pUSART->pSend = BSP_CH2O_CO2DirectSend;
    pUSART->pReceive = BSP_CH2O_CO2DirectReceive;

    pUSART->pReceive();

    BSP_CH2O_CO2_UsartDMA_Init(CH2O_CO2_DMABuff, CH2O_CO2_TX_Buff);
    BSP_CH2O_CO2_USART_Init((uint32_t)eBaudRateTab[pUSART->Frame.eBaudID], pUSART->Frame.eStop, pUSART->Frame.eParity);

    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
/*
uint8_t CH2O_CO2Init(CH2O_CO2_Typedef *pCH2O_CO2)
{
    pCH2O_CO2->Frame.pu8Receive              = CH2O_CO2_RX_Buff;
    pCH2O_CO2->Frame.pu8Send                 = CH2O_CO2_TX_Buff;
    pCH2O_CO2->Frame.pu8DMAReceive           = CH2O_CO2_DMABuff;
    pCH2O_CO2->Frame.u16ReceiveBuffMax       = CH2O_CO2_RX_BUFF;
    pCH2O_CO2->Frame.u8IdleNmsConfig        = u8BaudRateBytePeriodNmsConfigTab[pCH2O_CO2->Frame.eBaudID];

    pCH2O_CO2->pUSART4.SerialDevInit         = NULL;
    //pUSART->SerialHardWareSetting         NULL;//RS485MB_HardwareSetting;
    //pCH2O_CO2->pUSART4.SerialReceiveOK       = CH2O_CO2ReceiveOK;
    pCH2O_CO2->pUSART4.SerialDevError        = CH2O_CO2DevError;
    //pUSART->SerialDevFrameTime            = NULL;
    pCH2O_CO2->pUSART4.SerialDevReset       = CH2O_CO2Reset;
    //pUSART->SerialSendPrepair             = NULL;

    pCH2O_CO2->pUSART4.pStart                = BSP_CH2O_CO2SendStart;
    pCH2O_CO2->pUSART4.pStop                 = BSP_CH2O_CO2SendStop;
    pCH2O_CO2->pUSART4.pSend                 = BSP_CH2O_CO2DirectSend;
    pCH2O_CO2->pUSART4.pReceive              = BSP_CH2O_CO2DirectReceive;

    //pCH2O_CO2->pReceive();
    
    BSP_CH2O_CO2_UsartDMA_Init(CH2O_CO2_DMABuff,CH2O_CO2_TX_Buff);
    BSP_CH2O_CO2_USART_Init((uint32_t)eBaudRateTab[pCH2O_CO2->Frame.eBaudID], pCH2O_CO2->Frame.eStop, pCH2O_CO2->Frame.eParity);

    return OK;
}
*/
/**
   * @brief
   * @param
   * @retval
   */
void CH2O_CO2_Tick1ms(CH2O_CO2_Typedef *pCH2O_CO2)
{

    if (pCH2O_CO2->u16ReadWait)
    {
        pCH2O_CO2->u16ReadWait--;
    }
    if (pCH2O_CO2->u32ReadPeriod)
    {
        pCH2O_CO2->u32ReadPeriod--;
    }
}

/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CH2O_CO2ReceiveOK(Serial_Typedef *pSerial)
{
    uint16_t u16Data;

    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;    

    if (CH2O_CO2.eRunState == eCH2O_WAIT_MEASUREMENT)
    {
        CH2O_CO2.u8CH2ODropsFlag = 1;
        CH2O_CO2.u8CH2ODropscount = 0;
        if (OK == CH2O_Passive_Receive(pSerial, &u16Data))
        {  
            CH2O_CO2.u16CH2ONumerical = u16Data;
            CH2O_CO2.eRunState = eCH2O_READ_MEASUREMENT;
            //CH2O_CO2.eRunState = eCO2_START_MEASUREMENT;
            //CH2O_CO2.u16ReadWait = 1*1000;          //等待1S
            USART_ReceiveCount(pSerial);
            return OK;
        }
        return OK;
    }
    else if (CH2O_CO2.eRunState == eCO2_WAIT_MEASUREMENT)
    {
        CH2O_CO2.u8CO2DropsFlag = 1;
        CH2O_CO2.u8CO2Dropscount = 0;
        if (OK == CO2_Receive(pSerial, &u16Data))
        {
            CH2O_CO2.u16CO2Numerical = u16Data;
            CH2O_CO2.eRunState = eCO2_READ_MEASUREMENT;
            //CH2O_CO2.eRunState = eCH2O_START_MEASUREMENT;
            //CH2O_CO2.u16ReadWait = 1*1000;          //等待1S
            USART_ReceiveCount(pSerial);
            return OK;
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
void CH2O_CO2_ChannelSwitch(CH2O_CO2_Typedef *pCH2O_CO2)
{
    if (pCH2O_CO2->eRunState < eCH2O_CO2_SWITCH_WAIT) //切换到CH2O读写通道
    {
        BSP_CH2O_ChannelEnable();
    }
    else if (pCH2O_CO2->eRunState >= eCH2O_CO2_SWITCH_WAIT) //切换到CO2读写通道
    {
        BSP_CO2_ChannelEnable();
    }
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CH2O_CO2SendOK(void)
{
    if (eSERIAL_BUS_STATE_SEND_DATA == CH2O_CO2_UART.Frame.eTxState)
    {
        CH2O_CO2_UART.Frame.eTxState = eSERIAL_BUS_STATE_SEND_DATA_OK;
        CH2O_CO2_UART.Frame.u8IdleNms = CH2O_CO2_UART.Frame.u8IdleNmsConfig;
        CH2O_CO2_UART.Frame.u8RxTxShiftNms = u8SerialRxTxShiftTimeConfigTab[CH2O_CO2_UART.Frame.eBaudID];
        return OK;
    }
    return !OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CH2O_CO2Reset(Serial_Typedef *pSerial)
{
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;

    if ((CH2O_CO2.eRunState >= eCH2O_START_MEASUREMENT) && (CH2O_CO2.eRunState <= eCH2O_READ_MEASUREMENT))
    {

        return OK;
    }
    else if ((CH2O_CO2.eRunState >= eCO2_START_MEASUREMENT) && (CH2O_CO2.eRunState <= eCO2_READ_MEASUREMENT))
    {
        return OK;
    }

    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CH2O_CO2DevError(Serial_Typedef *pSerial)
{
    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;

    if ((CH2O_CO2.eRunState >= eCH2O_START_MEASUREMENT) && (CH2O_CO2.eRunState <= eCH2O_READ_MEASUREMENT))
    {
    }
    else if ((CH2O_CO2.eRunState >= eCO2_START_MEASUREMENT) && (CH2O_CO2.eRunState <= eCO2_READ_MEASUREMENT))
    {
    }

    return OK;
}

/**
   * @brief
   * @param
   * @retval
   */
uint8_t CH2O_CO2_SetState(CH2O_CO2_Typedef *pCH2O_CO2, uint8_t u8SetState, uint16_t u16SetWait)
{
    /*
    if (pCH2O_CO2->u16ReadWait)
    {
        return !OK;
    }
    pCH2O_CO2->u16ReadWait = u16SetWait; //等待1S
    pCH2O_CO2->eRunState = u8SetState;
    */
    return OK;
}
/**
   * @brief
   * @param
   * @retval
   */
void CH2O_CO2_OperationTask(CH2O_CO2_Typedef *pCH2O_CO2,uint32_t ReadPeriod)
{
    if (pCH2O_CO2->eRunState > 9)
    {
        pCH2O_CO2->eRunState = eCH2O_CO2_IDLE;
    }
    if (pCH2O_CO2->eCH2OFaultCode > 3)
    {
        pCH2O_CO2->eCH2OFaultCode = eCH2O_NORMAL;
    }
    if (pCH2O_CO2->eCO2FaultCode > 3)
    {
        pCH2O_CO2->eCO2FaultCode = eCO2_NORMAL;
    }    

    CH2O_CO2_ChannelSwitch(pCH2O_CO2); //切换到CH2O读写通道

    switch (pCH2O_CO2->eRunState)
    {
    case eCH2O_CO2_IDLE:

        if (KEY.eHardWareTest == eHWTESTMODE_YES)
        {
            pCH2O_CO2->u32ReadPeriod = 5 * 1000; //硬件自检模式
        }
        else
        {
            pCH2O_CO2->u32ReadPeriod = ReadPeriod; //上电等待稳定   18S
        }

        pCH2O_CO2->eRunState = eCH2O_CO2_WAIT_POWERON;
        break;

    case eCH2O_CO2_WAIT_POWERON:

        if (pCH2O_CO2->u32ReadPeriod != 0)
        {
            break;
        }
        pCH2O_CO2->eRunState = eCH2O_START_MEASUREMENT;
        pCH2O_CO2->u16ReadWait = 100;
        CH2O_PassiveSwitch_Send(&CH2O_CO2_UART.Frame); //设置为被动工作模式
        break;

    case eCH2O_START_MEASUREMENT:

        if (pCH2O_CO2->u16ReadWait != 0)
        {
            break;
        }
        CH2O_PassiveAsk_Send(&CH2O_CO2_UART.Frame); //发送CH2O查询命令
        pCH2O_CO2->u8CH2ODropsFlag = 0;             //接收标志置0
        pCH2O_CO2->eRunState = eCH2O_WAIT_MEASUREMENT;
        pCH2O_CO2->u16ReadWait = 1 * 1000; //等待采样1s
        break;

    case eCH2O_WAIT_MEASUREMENT:

        if (pCH2O_CO2->u16ReadWait != 0)
        {
            break;
        }
        if (pCH2O_CO2->u8CH2ODropsFlag == 0)
        {
            pCH2O_CO2->u8CH2ODropscount++;
            if (pCH2O_CO2->u8CH2ODropscount > 5)
            {
                pCH2O_CO2->u8CH2ODropscount = 0;
                pCH2O_CO2->eCH2OFaultCode = eCH2O_EQUIPMENT_DROPS; //设备掉线
                pCH2O_CO2->eRunState = eCH2O_CO2_SWITCH_WAIT;    //设备通信不上时再次通信
                break;
            }
            pCH2O_CO2->eRunState = eCH2O_START_MEASUREMENT;    //设备通信不上时再次通信
            break;
        }
        else
        {
            pCH2O_CO2->eRunState = eCH2O_READ_MEASUREMENT;
            break;
        }

    case eCH2O_READ_MEASUREMENT:

        if (pCH2O_CO2->u16ReadWait != 0)
        {
            break;
        }

        pCH2O_CO2->eRunState = eCH2O_CO2_SWITCH_WAIT;
        pCH2O_CO2->u16ReadWait = 100;
        break;

    case eCH2O_CO2_SWITCH_WAIT:

        if (pCH2O_CO2->u16ReadWait != 0)
        {
            break;
        }
        pCH2O_CO2->eRunState = eCO2_START_MEASUREMENT;
        break;

    case eCO2_START_MEASUREMENT:

        CO2_Ask_Send(&CH2O_CO2_UART.Frame);
        pCH2O_CO2->u8CO2DropsFlag = 0;
        pCH2O_CO2->eRunState = eCO2_WAIT_MEASUREMENT;
        pCH2O_CO2->u16ReadWait = 1 * 1000; //等待采样1s
        break;

    case eCO2_WAIT_MEASUREMENT:
        if (pCH2O_CO2->u16ReadWait != 0)
        {
            break;
        }
        if (pCH2O_CO2->u8CO2DropsFlag == 0)
        {
            pCH2O_CO2->u8CO2Dropscount++;
            if (pCH2O_CO2->u8CO2Dropscount > 5)
            {
                pCH2O_CO2->u8CO2Dropscount = 0;
                pCH2O_CO2->eCO2FaultCode = eCO2_EQUIPMENT_DROPS; //设备掉线
                pCH2O_CO2->eRunState = eCH2O_START_MEASUREMENT;    
                break;
            }
            pCH2O_CO2->eRunState = eCO2_START_MEASUREMENT;
            break;
        }
        else
        {
            pCH2O_CO2->eRunState = eCO2_READ_MEASUREMENT;
            break;
        }

    case eCO2_READ_MEASUREMENT:
        if (pCH2O_CO2->u16ReadWait != 0)
        {
            break;
        }
        pCH2O_CO2->u16ReadWait = 100;
        pCH2O_CO2->eRunState = eCH2O_START_MEASUREMENT;
        break;

    default:
        pCH2O_CO2->eRunState = eCH2O_CO2_IDLE;
        break;
    }
}
/*****************************************************************************************************************************************/
/*******************************************CH2O函数        ****************************************************************/
/*****************************************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval None
 */
uint16_t CH2O_Active_Receive(Serial_Typedef *pSerial, uint16_t *pu16CH2O) //主动模式数据处理
{
    if (OK != CH2O_CRC8(pSerial))
    {
        return 1; //CRC校验失败
    }
    if (pSerial->pu8Receive[0] != 0xff)
    {
        return 2; //
    }

    if (pSerial->pu8Receive[1] != 0x86)
    {
        return 3;
    }

    *pu16CH2O = (uint16_t)(pSerial->pu8Receive[4] << 8 | (uint16_t)pSerial->pu8Receive[5]);
    USART_ReceiveCount(pSerial);
    return 0;
}
/**
 * @brief
 * @param
 * @retval None
 */
//uint16_t CO2_Receive(Serial_Typedef *pSerial,uint32_t *pu32CO2)
uint16_t CH2O_Passive_Receive(Serial_Typedef *pSerial, uint16_t *pu16CH2O) //被动模式数据处理
{
    if (OK != CH2O_CRC8(pSerial))
    {
        CH2O_CO2.eCH2OFaultCode = eCH2O_EXCEPTION_MESSAGE; //报文异常
        return 2;                                     //CRC校验失败
    }
    if (pSerial->pu8Receive[0] != 0xff)
    {
        CH2O_CO2.eCH2OFaultCode = eCH2O_EXCEPTION_MESSAGE; //报文异常
        return 2;                                     //
    }

    if ( pSerial->pu8Receive[1] != 0x86 )
    {
        CH2O_CO2.eCH2OFaultCode = eCH2O_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }

    *pu16CH2O = (uint16_t)(pSerial->pu8Receive[2] << 8 | (uint16_t)pSerial->pu8Receive[3]);
    if (*pu16CH2O > 1500)
    {
        *pu16CH2O = 1500;
        CH2O_CO2.eCH2OFaultCode = eCH2O_ABNORMAL_DATA; //数据异常
    }
    else
    {
        CH2O_CO2.eCH2OFaultCode = eCH2O_NORMAL;
    }
    
    return 0;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t CH2O_CRC8(Serial_Typedef *pSerial)
{

    uint8_t tempq;
    uint8_t j;

    tempq = 0;
    for (j = 0; j < (pSerial->u16ReceiveBytesMax - 1); j++)
    {
        tempq += pSerial->pu8Receive[j];
    }
    tempq = (~tempq);

    if (pSerial->pu8Receive[8] == tempq)
    {
        return OK;
    }

    return !OK;
}
uint8_t FucCheckSum(uint8_t *i, uint8_t l)
{
    uint8_t j = 0;
    uint8_t tempq = 0;

    i += 1;
    for (j = 0; j < (l - 2); j++)
    {
        tempq += *i;
        i++;
    }
    tempq = (~tempq) + 1;
    return (tempq);
}
/**
 * @brief
 * @param
 * @retval
 */
void CH2O_ActiveSwitch_Send(Serial_Typedef *pSerial) //切换主动上报模式
{
    pSerial->pu8Send[0] = 0xff;
    pSerial->pu8Send[1] = 0x01;
    pSerial->pu8Send[2] = 0x78;
    pSerial->pu8Send[3] = 0x40;
    pSerial->pu8Send[4] = 0x00;
    pSerial->pu8Send[5] = 0x00;
    pSerial->pu8Send[6] = 0x00;
    pSerial->pu8Send[7] = 0x00;
    pSerial->pu8Send[8] = 0x47;

    USART_StateSetSend(pSerial, 9, 0, 0);
}
/**
 * @brief
 * @param
 * @retval
 */
void CH2O_PassiveSwitch_Send(Serial_Typedef *pSerial) //切换问答模式
{
    pSerial->pu8Send[0] = 0xff;
    pSerial->pu8Send[1] = 0x01;
    pSerial->pu8Send[2] = 0x78;
    pSerial->pu8Send[3] = 0x41;
    pSerial->pu8Send[4] = 0x00;
    pSerial->pu8Send[5] = 0x00;
    pSerial->pu8Send[6] = 0x00;
    pSerial->pu8Send[7] = 0x00;
    pSerial->pu8Send[8] = 0x46;
    USART_StateSetSend(pSerial, 9, 0, 0);
}
/**
 * @brief
 * @param
 * @retval
 */
void CH2O_PassiveAsk_Send(Serial_Typedef *pSerial) //查询
{
    pSerial->pu8Send[0] = 0xff;
    pSerial->pu8Send[1] = 0x01;
    pSerial->pu8Send[2] = 0x86;
    pSerial->pu8Send[3] = 0x00;
    pSerial->pu8Send[4] = 0x00;
    pSerial->pu8Send[5] = 0x00;
    pSerial->pu8Send[6] = 0x00;
    pSerial->pu8Send[7] = 0x00;
    pSerial->pu8Send[8] = 0x79;
    USART_StateSetSend(pSerial, 9, 0, 100);
}
/*****************************************************************************************************************************************/
/*******************************************CO2函数        ****************************************************************/
/*****************************************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval
 */
uint16_t Calculate_CRC16(uint8_t *cmd, uint8_t cmd_length)
{
    uint16_t ret = 0xffff;
    uint16_t polynomial = 0xa001;
    uint8_t shift = 0x0;
    for (int i = cmd_length - 1; i >= 0; i--)
    {
        uint16_t code;
        code = (uint16_t)(cmd[cmd_length - 1 - i] & 0xff);
        ret = ret ^ code;
        shift = 0x0;
        while (shift <= 7)
        {
            if (ret & 0x1)
            {
                ret = ret >> 1;
                ret = ret ^ polynomial;
            }
            else
            {
                ret = ret >> 1;
            }
            shift++;
        }
    }
    return ret;
}
/**
 * @brief
 * @param
 * @retval
 */
void CO2_Ask_Send(Serial_Typedef *pSerial) //查询
{
    uint16_t crcnumber;
    pSerial->pu8Send[0] = 0xaa;
    pSerial->pu8Send[1] = 0x55;
    pSerial->pu8Send[2] = 0x14;
    pSerial->pu8Send[3] = 0x00;

    crcnumber = Calculate_CRC16(pSerial->pu8Send, 4);

    pSerial->pu8Send[4] = crcnumber;
    pSerial->pu8Send[5] = crcnumber >> 8;
    USART_StateSetSend(pSerial, 6, 0, 100);
}
/**
 * @brief
 * @param
 * @retval None
 */
uint16_t CO2_Receive(Serial_Typedef *pSerial, uint16_t *pu16CO2) //被动模式数据处理
{

    if (pSerial->pu8Receive[6] == Calculate_CRC16(pSerial->pu8Receive, 4))
    {
        CH2O_CO2.eCO2FaultCode = eCO2_EXCEPTION_MESSAGE; //报文异常
        return 2;                                    //CRC校验失败
    }

    if (pSerial->pu8Receive[7] == (Calculate_CRC16(pSerial->pu8Receive, 4) >> 8))
    {
        CH2O_CO2.eCO2FaultCode = eCO2_EXCEPTION_MESSAGE; //报文异常
        return 2;                                    //CRC校验失败
    }

    if (pSerial->pu8Receive[0] != 0xbb)
    {
        CH2O_CO2.eCO2FaultCode = eCO2_EXCEPTION_MESSAGE; //报文异常
        return 2;                                    //
    }
    if (pSerial->pu8Receive[1] != 0x66)
    {
        CH2O_CO2.eCO2FaultCode = eCO2_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }
    if (pSerial->pu8Receive[2] != 0x15)
    {
        CH2O_CO2.eCO2FaultCode = eCO2_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }

    if (pSerial->pu8Receive[3] != 0x02)
    {
        CH2O_CO2.eCO2FaultCode = eCO2_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }
    *pu16CO2 = (uint16_t)(pSerial->pu8Receive[5] << 8 | (uint16_t)pSerial->pu8Receive[4]);

    if (*pu16CO2 > 5000)
    {
        *pu16CO2 = 5000;
        CH2O_CO2.eCO2FaultCode = eCO2_ABNORMAL_DATA; //数据异常
    }
    else
    {
        CH2O_CO2.eCO2FaultCode = eCO2_NORMAL;
    }
    if (*pu16CO2 < 400)
    {
        *pu16CO2 = 400;
        CH2O_CO2.eCO2FaultCode = eCO2_ABNORMAL_DATA; //数据异常
    }
    else
    {
        CH2O_CO2.eCO2FaultCode = eCO2_NORMAL;
    }

    return OK;
}
/* End of file */
