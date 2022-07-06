/*!
*****************************************************************
$Name$
$Revision: 
$Date: 
\file 
\brief  
\author zhoujinbang


<b>Company:</b>\nmenred automation\n
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
#include "EnOceanlibInclude.h"
/* User App */
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "EnOceanCascade.h"

#include "RS485Modbus.h"
#include "Key.h"
#include "Led.h"
#include "RS485Modbus.h"
#include "EnOceanCascade.h"
#include "EnOceanMSCCascade.h"

#include "Debug.h"
#include "HWTest.h"
#include "SysError.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 



/*============================ LOCAL VARIABLES ===============================*/


/*============================ PROTOTYPES ====================================*/
uint8_t HWTest_RS485ModbusBuff[RS485_MODBUS_TX_BUFF];
uint8_t HWTest_RS485ModbusDMABuff[RS485_MODBUS_RX_BUFF];

HWTest_Typedef HWTest;
/*============================ IMPLEMENTATION ================================*/

/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
void HardwareSelfTest_Tick1ms(HWTest_Typedef *pHWTest)
{
    if (pHWTest->u8SelfTestState==1)
    {
        pHWTest->u32HWTestCount++;
    }
    if (pHWTest->u16HWTestLedTimer !=0)
    {
        pHWTest->u16HWTestLedTimer--;
    }
    
    pHWTest->u32HWTestEnoceanSendCout++;
    
}
/**
  * @brief
  * @param
  * @retval None     
  */
uint8_t HardwareSelfTestLedDisplay(void) //出厂自检函数
{
    if (CH2O_CO2.eCH2OFaultCode == eCH2O_EQUIPMENT_DROPS ) //CH2O
    {
        HWTest.eLedID = eLED_RED;
        return 1;
    }
    if (CH2O_CO2.eCO2FaultCode == eCO2_EQUIPMENT_DROPS ) //CO2
    {
        HWTest.eLedID = eLED_ORANGE;
        return 2;
    }
    if (PMSA.eFaultCode == ePMSA_EQUIPMENT_DROPS ) //PMSA
    {
        HWTest.eLedID = eLED_YELLOW;
        return 3;
    }
    if (SHT20.eFaultCode == eSHT20_EQUIPMENT_DROPS ) //SHT20
    {
        HWTest.eLedID = eLED_GREEN;
        return 4;
    }
    /*
    if (CH2O_CO2.eCO2FaultCode == eCO2_NORMAL && CH2O_CO2.eCH2OFaultCode == eCH2O_NORMAL && PMSA.eFaultCode == ePMSA_NORMAL && SHT20.eFaultCode == eSHT20_NORMAL )
    {
        HWTest.eLedID = eLED_ALL;
        return 5;
    }
    */
    return OK;
}
/**
  * @brief
  * @param
  * @retval None     
  */
uint8_t HardwareSelfTestLedDisplay2(void) //出厂自检函数
{
    
    if (CH2O_CO2.eCH2OFaultCode == eCH2O_EQUIPMENT_DROPS ) //CH2O
    {
        HWTest.eLedID = eLED_RED;
        return 1;
    }
    if (CH2O_CO2.eCO2FaultCode == eCO2_EQUIPMENT_DROPS ) //CO2
    {
        HWTest.eLedID = eLED_ORANGE;
        return 2;
    }
    if (PMSA.eFaultCode == ePMSA_EQUIPMENT_DROPS ) //PMSA
    {
        HWTest.eLedID = eLED_YELLOW;
        return 3;
    }
    if (SHT20.eFaultCode == eSHT20_EQUIPMENT_DROPS ) //SHT20
    {
        HWTest.eLedID = eLED_GREEN;
        return 4;
    }
    if (CH2O_CO2.eCO2FaultCode == eCO2_NORMAL && CH2O_CO2.eCH2OFaultCode == eCH2O_NORMAL && PMSA.eFaultCode == ePMSA_NORMAL && SHT20.eFaultCode == eSHT20_NORMAL )
    {
        HWTest.eLedID = eLED_ALL;
        return 5;
    }
    
    return OK;
}
/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
void HardwareSelfTestLed(HWTest_Typedef *pHWTest)
{

    switch (pHWTest->HWTestLed)
    {
    case eHWTESTLED_STANDBY:
    {
        if ( LED.eRunMode== eLEDRUN_STANDBY && pHWTest->eLedID < 5)
        {
            pHWTest->eLedID++;
            LedRunMode_Light(pHWTest->eLedID, 1);
        }
        if (pHWTest->eLedID == 5)
        {
            pHWTest->u8MarqueeFlag++;
            pHWTest->eLedID = eLED_INITIAL;
        }
        if (pHWTest->u8MarqueeFlag == 2)
        {
            pHWTest->u8MarqueeFlag = 0;
            pHWTest->eLedID = eLED_INITIAL;
            pHWTest->HWTestLed = eHWTESTLED_SELFTESTREADY;
        }
        break;
    }

    case eHWTESTLED_SELFTESTREADY: //自检测试准备
    {
        pHWTest->HWTestLed = eHWTESTLED_SELFTESTING;
        pHWTest->u16HWTestLedTimer = 30 * 1000; //等待 30s
        break;
    }

        case eHWTESTLED_SELFTESTING: //自检中...
        {
            if (OK != HardwareSelfTestLedDisplay())
            {
                LedRunMode_FaultAlarm(pHWTest->eLedID);
            }
            if (pHWTest->u16HWTestLedTimer != 0)
            {
                break;
            }
            
            if (ReportedData.u8PMSTestFlag == 1) //优先检查是否有PMS测试指令
            {
                pHWTest->HWTestLed = eHWTESTLED_PMSTEST_CMDSTART;
                //LED.eRunMode = eLEDRUN_STANDBY;
                pHWTest->eLedID = eLED_INITIAL;
                ReportedData.u8PMSTestFlag = 0;
                break;
            }
            else
            {
                pHWTest->HWTestLed = eHWTESTLED_SELFTESTSHOWSTART; //进入展示空气质量模式
                break;
            }

            //pHWTest->HWTestLed = eHWTESTLED_SELFTESTSHOWSTART;
        }

        case eHWTESTLED_SELFTESTSHOWSTART: //开始展示硬件检测结果
        {

            if (OK != HardwareSelfTestLedDisplay2())
            {
                LedRunMode_FaultAlarm(pHWTest->eLedID);
            }
            pHWTest->u16HWTestLedTimer = 5 * 1000; //延时5S
            pHWTest->HWTestLed = eHWTESTLED_SELFTESTSHOWING;
        }

        case eHWTESTLED_SELFTESTSHOWING: //等待展示硬件检测结果执行结束
        {
            if (pHWTest->u16HWTestLedTimer != 0)
            {
                break;
            }
            if (ReportedData.u8PMSTestFlag == 1) //优先检查是否有PMS测试指令
            {
                pHWTest->HWTestLed = eHWTESTLED_PMSTEST_CMDSTART;
                //LED.eRunMode == eLEDRUN_STANDBY;
                pHWTest->eLedID = eLED_INITIAL;
                ReportedData.u8PMSTestFlag = 0;
                break;
            }
            else
            {
                pHWTest->HWTestLed = eHWTESTLED_SELFTESTSHOWSTART;
                break;
            }
        }

        case eHWTESTLED_PMSTEST_CMDSTART: //PMS测试命令开始
        {

            LedRunMode_FaultAlarm(eLED_ALL); //呼吸1次
            pHWTest->u16HWTestLedTimer = 10 * 1000; //5S
            pHWTest->HWTestLed = eHWTESTLED_PMSTEST_WAITEND; //欢迎 
            break;
        }

        case eHWTESTLED_PMSTEST_WAITEND: //等待PMS测试命令结束
        {
            if (pHWTest->u16HWTestLedTimer != 0)
            {
                break;
            }
            pHWTest->HWTestLed = eHWTESTLED_SELFTESTSHOWSTART;
            break;
        }

        default:
            pHWTest->HWTestLed = eHWTESTLED_STANDBY;
            break;
        }
}
/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
#if 0
static uint8_t HardwareSelfTestEnOcean(uint32_t *pu32ResponseCnt)
{
    uint8_t u8Status;

    /* */
    u8Status = EnOceanESP3ReceivePacketParse(&Radio,PACKET_RESERVED);
    
    if (0 == u8Status)
    {
        (*pu32ResponseCnt)++;
    }
    else if (1 == u8Status)
    {
        EnOcean_HardwareReset();
    }
    else if (2 == u8Status)
    {              
        return OK;
    }

    /* */
    if ( OK != EnOceanESP3SendStateProcess() )
    {
        EnOcean_HardwareReset();
    }
    
    if ( OK == EnOceanGetSendReady() )
    {
        if ( OK == EnOcean_GetSendQueuePopID() )
        {      
            EnOceanPopQueueSendData();
            EnOceanSetSendPeriod(200) ;        
        }
    }

    return !OK;
}
#endif
/**
 * @brief
 * @param
 * @retval None
 */
void HardwareSelfTestInfoRS485Expand(Serial_Typedef *pSerial)
{
    //uint16_t u16CRC;

    //if ( OK == USART_GetStateOfSendPeriod(pSerial,1000) )
    {
        pSerial->u8DataUpdateLock = 1;
        pSerial->u16SendBytesCnt  = 0; 
        pSerial->u16SendBytesMax  = 8;
        pSerial->u8WaitReceiveState = 0xFF;
        pSerial->pu8Send[0] = 0x11;
        pSerial->pu8Send[1] = 0x04;
        pSerial->pu8Send[2] = 0x00;
        pSerial->pu8Send[3] = 0x00;
        pSerial->pu8Send[4] = 0x00;
        pSerial->pu8Send[5] = 0x01;
        //u16CRC = CRC16Get( pSerial->pu8Send, 6 );
        pSerial->pu8Send[6] = 0x33;
        pSerial->pu8Send[7] = 0x5a;
        //pSerial->pu8Send[7] = u16CRC>>8;
        //pSerial->pu8Send[6] = u16CRC&0xFF;

        USART_StateSetSend(pSerial, pSerial->u16SendBytesMax,3,100);
    }
}
/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
/*
static void HardwareSelfTestInfoRS485(uint32_t *pu32MBRecv,uint32_t *pu32ExRecv,uint32_t *pu32CasRecv)
{       
    
}
*/

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HardWareButtonTest(uint8_t *pu8State)
{

}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HardWareSwitchTest(uint8_t u8SwitchStatus)
{

}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HardWareEEPROM(void)
{

}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
static void HardWareEnoceanSend(Radio_Typedef *pRadio, Dev_Typedef *pDev,  uint8_t u8RegL)
{
    Radio.Telegram.raw.bytes[0] = 0xF5;

    Radio.Telegram.raw.bytes[1] = 0x1F;

    //pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    pRadio->Telegram.raw.bytes[2] = 0x00;

    pRadio->Telegram.raw.bytes[3] = u8RegL;

    pRadio->Telegram.raw.bytes[4] = 0;
    pRadio->Telegram.raw.bytes[5] = 0;
    pRadio->Telegram.raw.bytes[6] = 0;
    pRadio->Telegram.raw.bytes[7] = 0;

    switch (u8RegL)
    {
    case 0x00:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16HWVersion >> 24);
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16HWVersion >> 16);
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16HWVersion >> 8);
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16HWVersion >> 0);        
        break;

    case 0x01:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16FWVersion >> 24);
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16FWVersion >> 16);
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16FWVersion >> 8);
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16FWVersion >> 0);        
        break;

    case 0x02:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u32BuildYYMMDD >> 24);
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u32BuildYYMMDD >> 16);
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u32BuildYYMMDD >> 8);
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u32BuildYYMMDD >> 0);        
        break;

    case 0x03:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u32BuildHHMMSS >> 24);
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u32BuildHHMMSS >> 16);
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u32BuildHHMMSS >> 8);
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u32BuildHHMMSS >> 0);        
        break;        
    
    case 0x04:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.Cfg.u32EnOceanChipID >> 24);
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.Cfg.u32EnOceanChipID >> 16);
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.Cfg.u32EnOceanChipID >> 8);
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.Cfg.u32EnOceanChipID >> 0);        
        break; 

    case 0x05:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.Cfg.u32EnOceanBaseID >> 24);
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.Cfg.u32EnOceanBaseID >> 16);
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.Cfg.u32EnOceanBaseID >> 8);
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.Cfg.u32EnOceanBaseID >> 0);        
        break;               

    case 0x06:
        pRadio->Telegram.raw.bytes[4] = 0;
        pRadio->Telegram.raw.bytes[5] = 0;
        pRadio->Telegram.raw.bytes[6] = 0;
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(pRadio->Param.p_rx.u8Dbm );        
        break;    

    case 0x07:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(pRadio->Param.p_rx.u32DestinationId >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(pRadio->Param.p_rx.u32DestinationId >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(pRadio->Param.p_rx.u32DestinationId >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(pRadio->Param.p_rx.u32DestinationId >> 0 );        
        break;    

    case 0x08:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(RS485Modbus.Frame.u32SendCount >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(RS485Modbus.Frame.u32SendCount >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(RS485Modbus.Frame.u32SendCount >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(RS485Modbus.Frame.u32SendCount >> 0 );        
        break;

    case 0x09:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(RS485Modbus.Frame.u32ReceiveCount >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(RS485Modbus.Frame.u32ReceiveCount >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(RS485Modbus.Frame.u32ReceiveCount >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(RS485Modbus.Frame.u32ReceiveCount >> 0 );        
        break;        

    case 0x0A:
        if (SHT20.u8SHT20Dropscount != 0)
        {
            pRadio->Telegram.raw.bytes[7] = 1;
        }
        else 
        {
            pRadio->Telegram.raw.bytes[7] =0;
        }
        break; 

    case 0x0B:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16HumidityValue >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16HumidityValue >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16HumidityValue >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16HumidityValue >> 0 );        
        break; 

    case 0x0C:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16TemperatureValue >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16TemperatureValue >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16TemperatureValue >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16TemperatureValue >> 0 );        
        break;         

    case 0x0D:
        if (PMSA.u8PMSADropscount !=0)
        {
            pRadio->Telegram.raw.bytes[7] = 1;
        }
        else 
        {
            pRadio->Telegram.raw.bytes[7] =0;
        }   
        break; 

    case 0x0E:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16PM100Value >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16PM100Value >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16PM100Value >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16PM100Value >> 0 );        
        break;

    case 0x0F:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16PM25Value >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16PM25Value >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16PM25Value >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16PM25Value >> 0 );        
        break;     

    case 0x10:
        if (CH2O_CO2.u8CO2Dropscount !=0)
        {
            pRadio->Telegram.raw.bytes[7] = 1;
        }
        else 
        {
            pRadio->Telegram.raw.bytes[7] =0;
        }     
        break;     

    case 0x11:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16CO2Value >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16CO2Value >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16CO2Value >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16CO2Value >> 0 );        
        break;  

    case 0x12:
        if (CH2O_CO2.u8CH2ODropscount !=0)
        {
            pRadio->Telegram.raw.bytes[7] = 1;
        }
        else 
        {
            pRadio->Telegram.raw.bytes[7] =0;
        }       
        break;  

    case 0x13:
        pRadio->Telegram.raw.bytes[4] = (uint8_t)(Dev.u16CH2OValue >> 24 );
        pRadio->Telegram.raw.bytes[5] = (uint8_t)(Dev.u16CH2OValue >> 16 );
        pRadio->Telegram.raw.bytes[6] = (uint8_t)(Dev.u16CH2OValue >> 8 );
        pRadio->Telegram.raw.bytes[7] = (uint8_t)(Dev.u16CH2OValue >> 0 );        
        break;          

    default:
        pRadio->Telegram.raw.bytes[4] = 0;
        pRadio->Telegram.raw.bytes[5] = 0;
        pRadio->Telegram.raw.bytes[6] = 0;   
        pRadio->Telegram.raw.bytes[7] = 0;   
        break;
    }

    //EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);

    EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t HWTest_RS485ModbusReceiveOK(Serial_Typedef *pSerial)
{
    //uint16_t u16RegID;

    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;

    //u16RegID = pSerial->pu8Receive[2] << 8 | pSerial->pu8Receive[3];

    if (pSerial->pu8Receive[0] != (*pSerial->pu8PhyAddress))
    {
        return !OK;
    }
    if (pSerial->pu8Receive[0] == 0x11)
    {
        USART_ReceiveCount(pSerial);
        return OK;
    }
    
    
    if (RS485ModbusRTU(pSerial->pu8Receive, pSerial->pu8Send, &pSerial->u16ReceiveBytesMax))
    {
        pSerial->u16ReceiveBytesMax = 0;
        return !OK;
    }
    USART_ReceiveCount(pSerial);
    USART_StateSetSend(pSerial, pSerial->u16ReceiveBytesMax, 0, 0);

    return OK;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t HWTest_RS485ModbusInit(USART_Function_Typedef *pUSART)
{
    pUSART->Frame.pu8Receive = HWTest_RS485ModbusBuff;
    pUSART->Frame.pu8Send = HWTest_RS485ModbusBuff;
    pUSART->Frame.pu8DMAReceive = HWTest_RS485ModbusDMABuff;
    pUSART->Frame.u16ReceiveBuffMax = RS485_MODBUS_RX_BUFF;
    pUSART->Frame.u8IdleNmsConfig = u8BaudRateBytePeriodNmsConfigTab[pUSART->Frame.eBaudID];

    pUSART->SerialDevInit = NULL;
    //pUSART->SerialHardWareSetting         = NULL;//RS485MB_HardwareSetting;
    pUSART->SerialReceiveOK = HWTest_RS485ModbusReceiveOK;
    pUSART->SerialDevError = RS485ModbusDevError;
    //pUSART->SerialDevFrameTime            = NULL;
    pUSART->SerialDevReset = RS485ModbusReset;
    //pUSART->SerialSendPrepair             = NULL;

    pUSART->pStart = BSP_RS485ModbusSendStart;
    pUSART->pStop = BSP_RS485ModbusSendStop;
    pUSART->pSend = BSP_RS485ModbusDirectSend;
    pUSART->pReceive = BSP_RS485ModbusDirectReceive;

    pUSART->pReceive();

    BSP_ModbusUsartDMA_Init(HWTest_RS485ModbusDMABuff, HWTest_RS485ModbusBuff);
    BSP_ModbusUSART_Init((uint32_t)eBaudRateTab[pUSART->Frame.eBaudID], pUSART->Frame.eStop, pUSART->Frame.eParity);

    return OK;
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
static void HardwareModbusConfiguration(void)   //自检Modbus配置
{
    Dev.Cfg.u8ModbusPhyAdd = 0x11;

    RS485Modbus.Frame.pu8PhyAddress = &Dev.Cfg.u8ModbusPhyAdd;
    RS485Modbus.Frame.eParity = ePARITY_NONE;
    RS485Modbus.Frame.eBaudID = eBAUD_9600_ID;
    RS485Modbus.Frame.eStop   = eSTOP_1;

    HWTest_RS485ModbusInit(&RS485Modbus);
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HardwareSelfTest(HWTest_Typedef *pHWTest)
{   
   
    uint32_t u32EnOceanBaseID;     
    uint8_t  u8EnoceanSendFlag;   

    u8EnoceanSendFlag = 0;
    EnOceanGetHWBaseID ( &u32EnOceanBaseID );

    pHWTest->u8SelfTestState = 0;
    if (0 == KeyReadPin())
    {
        pHWTest->u8SelfTestState = 1;
        FLASHRUN.u8FactorySetCount = 1;
        HardwareModbusConfiguration();

        EnOceanModuleInit();
        EnOceanGetHWChipID(&Dev.Cfg.u32EnOceanChipID);
        EnOceanGetHWBaseID(&Dev.Cfg.u32EnOceanBaseID);
    }

    while (pHWTest->u8SelfTestState)
    {

        KeyEvent_Scanning(&KEY);

        LED_runmode(&LED);
        HardwareSelfTestLed(&HWTest);
        

        SystemTimeTick_10ms();
        SystemTimeTick_100ms();
        SystemTimeTick_1000ms();

        EnOceanHandler(Dev.Cfg.u8RadioInterval);
        EnOceanProactiveReporting(&ReportedData);
        EnOceanDifferenceReport(&ReportedData);
  
        USART_StateMachineHandler(&RS485Modbus);
        USART_StateMachineHandler(&CH2O_CO2_UART);
        USART_StateMachineHandler(&PMSA_UART);
        CH2O_CO2_OperationTask(&CH2O_CO2,2000);
        SHT20_OperationTask(&SHT20,2000);
        PMSA_OperationTask(&PMSA,1000,1000);

        if(pHWTest->u32HWTestEnoceanSendCout > 150)
        {
            if(u8EnoceanSendFlag > 20)
            {
                u8EnoceanSendFlag = 0;
                HardwareSelfTestInfoRS485Expand(&RS485Modbus.Frame);
            }
            
            pHWTest->u32HWTestEnoceanSendCout = 0;
            HardWareEnoceanSend(&Radio, &Dev, u8EnoceanSendFlag);
            u8EnoceanSendFlag ++;

        }

        //自检超时为10分钟，自动退出自检状态
        if (pHWTest->u32HWTestCount > (600 * 1000))
        {
            pHWTest->u8SelfTestState = 0;
            pHWTest->eLedID=eLED_INITIAL;
            KEY.eHardWareTest = eHWTESTMODE_No;
            //LED.eRunMode = eLEDWORK_STANDBY;
        }
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
