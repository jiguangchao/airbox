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
#include "PMSA003.h"
#include "EnOceanCascade.h"
#include "Key.h"

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

uint8_t PMSA_TX_Buff[PMSA_TX_BUFF];
uint8_t PMSA_RX_Buff[PMSA_RX_BUFF];
uint8_t PMSA_DMABuff[PMSA_RX_BUFF];

PMSA_Typedef PMSA;
USART_Function_Typedef PMSA_UART;
//USART_Function_Typedef PMSA;

/**
 * @brief
 * @param
 * @retval
 */
uint8_t PMSAInit(USART_Function_Typedef *pUSART)
{
    pUSART->Frame.pu8Receive              = PMSA_RX_Buff;
    pUSART->Frame.pu8Send                 = PMSA_TX_Buff;
    pUSART->Frame.pu8DMAReceive           = PMSA_DMABuff;
    pUSART->Frame.u16ReceiveBuffMax       = PMSA_RX_BUFF;
    pUSART->Frame.u8IdleNmsConfig        = u8BaudRateBytePeriodNmsConfigTab[pUSART->Frame.eBaudID];

    pUSART->SerialDevInit                 = NULL;
    //pUSART->SerialHardWareSetting         = NULL;//RS485MB_HardwareSetting;
    pUSART->SerialReceiveOK               = PMSAReceiveOK;
    pUSART->SerialDevError                = PMSADevError;
    //pUSART->SerialDevFrameTime            = NULL;
    pUSART->SerialDevReset                = PMSAReset;
    //pUSART->SerialSendPrepair             = NULL;

    pUSART->pStart                        = BSP_PMSASendStart;
    pUSART->pStop                         = BSP_PMSASendStop;
    pUSART->pSend                         = BSP_PMSADirectSend;
    pUSART->pReceive                      = BSP_PMSADirectReceive;

    pUSART->pReceive();
    
    BSP_PMSAUsartDMA_Init(PMSA_DMABuff,PMSA_TX_Buff);
    BSP_PMSAUSART_Init((uint32_t)eBaudRateTab[pUSART->Frame.eBaudID], pUSART->Frame.eStop, pUSART->Frame.eParity);

    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t PMSASendOK(void)
{
    if (eSERIAL_BUS_STATE_SEND_DATA == PMSA_UART.Frame.eTxState)
    {
        PMSA_UART.Frame.eTxState = eSERIAL_BUS_STATE_SEND_DATA_OK;
        PMSA_UART.Frame.u8IdleNms = PMSA_UART.Frame.u8IdleNmsConfig;
        PMSA_UART.Frame.u8RxTxShiftNms = u8SerialRxTxShiftTimeConfigTab[PMSA_UART.Frame.eBaudID];
        return OK;
    }
    return !OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t PMSAReset(Serial_Typedef *pSerial)
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
uint8_t PMSAReceiveOK(Serial_Typedef *pSerial)
{

    PMSA.u8PMSADropsFlag = 1;
    PMSA.u8PMSADropscount = 0;
    if (PMSA.eRunState == ePMSA_WAIT_MEASUREMENT)
    {
        if (OK == PMSA_Receive(pSerial))
        {

            PMSA.u16PM10Numerical = (((uint16_t)pSerial->pu8Receive[10]) << 8) + (uint16_t)pSerial->pu8Receive[11];  //PM1.0
            PMSA.u16PM25Numerical = (((uint16_t)pSerial->pu8Receive[12]) << 8) + (uint16_t)pSerial->pu8Receive[13];  //PM2.5
            PMSA.u16PM100Numerical = (((uint16_t)pSerial->pu8Receive[14]) << 8) + (uint16_t)pSerial->pu8Receive[15]; //PM10

            //数据范围上限控制
            if (PMSA.u16PM10Numerical > 999)
            {
                PMSA.u16PM10Numerical = 999;
                PMSA.eFaultCode = ePMSA_ABNORMAL_DATA; //数据异常
            }
            else
            {
                PMSA.eFaultCode = ePMSA_NORMAL;
            }
            if (PMSA.u16PM25Numerical > 999)
            {
                PMSA.u16PM25Numerical = 999;
                PMSA.eFaultCode = ePMSA_ABNORMAL_DATA; //数据异常
            }
            else
            {
                PMSA.eFaultCode = ePMSA_NORMAL;
            }
            if (PMSA.u16PM100Numerical > 999)
            {
                PMSA.u16PM100Numerical = 999;
                PMSA.eFaultCode = ePMSA_ABNORMAL_DATA; //数据异常
            }
            else
            {
                PMSA.eFaultCode = ePMSA_NORMAL;
            }
            //数据范围下限控制
            if (0 == PMSA.u16PM10Numerical)
            {
                PMSA.u16PM10Numerical = 1;
            }
            if (0 == PMSA.u16PM25Numerical)
            {
                PMSA.u16PM25Numerical = 1;
            }
            if (0 == PMSA.u16PM100Numerical)
            {
                PMSA.u16PM100Numerical = 1;
            }

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
uint8_t PMSADevError(Serial_Typedef *pSerial)
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
void PMSA_Tick1ms(PMSA_Typedef *pPMSA)
{

    if (pPMSA->u32ReadWait)
    {
        pPMSA->u32ReadWait--;
    }
    if (pPMSA->u32Dormancywait)
    {
        pPMSA->u32Dormancywait--;
    }
    
}
/**
   * @brief
   * @param
   * @retval
   */
void PMSA_OperationTask(PMSA_Typedef *pPMSA, uint32_t ReadPeriod, uint32_t Dormancywait) //开始时间  和 休眠时间都大于30S
{

    if (pPMSA->eRunState > 8)
    {
        pPMSA->eRunState = ePMSA_IDLE;
    }
    if (pPMSA->eFaultCode > 3)
    {
        pPMSA->eFaultCode = ePMSA_NORMAL;
    }
    

    switch (pPMSA->eRunState)
    {
    case ePMSA_IDLE:

        if (KEY.eHardWareTest == eHWTESTMODE_YES)
        {
            pPMSA->u32Dormancywait = 0;
            pPMSA->eRunState = ePMSA_PERIOD_WAIT; //自检模式下不进入休眠
            break;
        }
        else
        {
            pPMSA->u32Dormancywait = Dormancywait; //休眠30S
            pPMSA->eRunState = ePMSA_PERIOD_WAIT;
            break;
        }
        break;
        //pPMSA->u32ReadWait = Dormancywait;
        //pPMSA->eRunState = ePMSA_PERIOD_WAIT;
        //break;

    case ePMSA_PERIOD_WAIT:

        if (pPMSA->u32Dormancywait != 0)
        {
            break;
        }
        pPMSA->eRunState = ePMSA_INITIALIZE_STATE;
        break;

    case ePMSA_INITIALIZE_STATE:

        PMSA_RST_ENABLE();         //拉低复位引脚   开始复位
        pPMSA->u32ReadWait = 1000; //等待1s
        pPMSA->eRunState = ePMSA_WAIT_STATUS;
        break;

    case ePMSA_WAIT_STATUS: //等待复位

        if (pPMSA->u32ReadWait != 0)
        {
            break;
        }
        PMSA_SET_ENABLE();  //进入工作状态
        PMSA_RST_DISABLE(); //拉高复位引脚  停止复位
        pPMSA->eRunState = ePMSA_SET_WORKMODE;
        pPMSA->u32ReadWait = 3 * 1000; //等待3s
        break;

    case ePMSA_SET_WORKMODE:

        if (pPMSA->u32ReadWait != 0)
        {
            break;
        }
        PMSA_ActiveSwitch_Send(&PMSA_UART.Frame); //进入主动工作模式
        //pPMSA->u8PMSADropsFlag = 0;
        pPMSA->u32ReadWait = 2 * 1000; //等待2S
        pPMSA->eRunState = ePMSA_STARTWORT;
        break;

    case ePMSA_STARTWORT:

        if (pPMSA->u32ReadWait != 0)
        {
            break;
        }
        PMSA_SET_ENABLE(); //进入工作状态
        pPMSA->eRunState = ePMSA_START_MEASUREMENT;
        if (KEY.eHardWareTest == eHWTESTMODE_YES)
        {
            pPMSA->u32ReadWait = 1000; //等待15S  硬件测试
        }
        else
        {
            pPMSA->u32ReadWait = 30 * 1000; //等待30s  数据稳定
        }
        break;

    case ePMSA_START_MEASUREMENT: //开始采样

        if (pPMSA->u32ReadWait != 0)
        {
            break;
        }
        pPMSA->u8PMSADropsFlag = 0;
        pPMSA->u32ReadWait = 5000;
        pPMSA->eRunState = ePMSA_WAIT_MEASUREMENT;
        break;

    case ePMSA_WAIT_MEASUREMENT:

        if (pPMSA->u32ReadWait != 0)
        {
            break;
        }
        if (pPMSA->u8PMSADropsFlag == 0)
        {
            pPMSA->u8PMSADropscount++;
            if (pPMSA->u8PMSADropscount > 5)
            {
                pPMSA->u8PMSADropscount = 0;
                pPMSA->eFaultCode = ePMSA_EQUIPMENT_DROPS;
            }
            pPMSA->u32ReadWait = 100;
            pPMSA->eRunState = ePMSA_START_MEASUREMENT;
            break;
        }
        else
        {
            pPMSA->eRunState = ePMSA_READ_MEASUREMENT;
            break;
        }
        break;

    case ePMSA_READ_MEASUREMENT:

        PMSA_SET_DISABLE(); //进入休眠状态
        pPMSA->eRunState = ePMSA_IDLE;
        break;

    default:
        pPMSA->eRunState = ePMSA_IDLE;
        break;
    }
}

//PM2 数据 CRC计算
static uint16_t PMS03CRC(uint8_t DataBuf[], uint16_t DataCnt)
{
    uint8_t  i;
    uint16_t CRCValue = 0x00;

    for(i=0; i<DataCnt; i++)
    {
        CRCValue += DataBuf[i];
    }

    return CRCValue;
}
/**
 * @brief
 * @param
 * @retval
 */
void PMSA_ActiveSwitch_Send(Serial_Typedef *pSerial) //切换主动上报模式
{
    pSerial->pu8Send[0] = 0x42;
    pSerial->pu8Send[1] = 0x4d;
    pSerial->pu8Send[2] = 0xe1;
    pSerial->pu8Send[3] = 0x00;
    pSerial->pu8Send[4] = 0x01;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x71;

    USART_StateSetSend(pSerial, 7, 0, 100);
}
/**
 * @brief
 * @param
 * @retval
 */
void PMSA_PassiveSwitch_Send(Serial_Typedef *pSerial) //切换问答模式
{
    pSerial->pu8Send[0] = 0x42;
    pSerial->pu8Send[1] = 0x4d;
    pSerial->pu8Send[2] = 0xe1;
    pSerial->pu8Send[3] = 0x00;
    pSerial->pu8Send[4] = 0x00;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x70;
    USART_StateSetSend(pSerial, 7, 0, 100);
}
/**
 * @brief
 * @param
 * @retval
 */
void PMSA_PassiveAsk_Send(Serial_Typedef *pSerial) //查询
{
    pSerial->pu8Send[0] = 0x42;
    pSerial->pu8Send[1] = 0x4d;
    pSerial->pu8Send[2] = 0xe2;
    pSerial->pu8Send[3] = 0x00;
    pSerial->pu8Send[4] = 0x00;
    pSerial->pu8Send[5] = 0x01;
    pSerial->pu8Send[6] = 0x71;
    USART_StateSetSend(pSerial, 7, 0, 100);
}
/*
 * 功能： 从PM2应答消息中解析出PM2浓度
 * 参数： msgdata： PM2应答的数据，长度必须 >= 32，否则解析失败
 * 返回值 > 0 ：正常
 * 返回值 <= 0 : 解析错误
 */
uint16_t PMSA_Receive(Serial_Typedef *pSerial)
{
    uint16_t crcval;
    if (pSerial->pu8Receive[0] != 0x42)
    {
        PMSA.eFaultCode = ePMSA_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }
    if (pSerial->pu8Receive[1] != 0x4D)
    {
        PMSA.eFaultCode = ePMSA_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }
    if (pSerial->pu8Receive[2] != 0x00)
    {
        PMSA.eFaultCode = ePMSA_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }
    if (pSerial->pu8Receive[3] != 0x1C)
    {
        PMSA.eFaultCode = ePMSA_EXCEPTION_MESSAGE; //报文异常
        return 2;
    }
    //CRC检查
    crcval = PMS03CRC(pSerial->pu8Receive, pSerial->u16ReceiveBytesMax - 2);

    PMSA.u16CrcTest1=crcval;
    PMSA.u16CrcTest2=(uint16_t)pSerial->pu8Receive[30]<<8 | pSerial->pu8Receive[31];

    if ((pSerial->pu8Receive[30] == (crcval >> 8)) && (pSerial->pu8Receive[31] == (crcval & 0x00FF)))
    {
        return OK;
    }
    else
    {
        PMSA.eFaultCode = ePMSA_EXCEPTION_MESSAGE; //报文异常
        return !OK;
    }

    //return !OK;
}

/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/

/* End of file */
