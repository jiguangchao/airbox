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
#include "RS485Modbus.h"
#include "EnOceanCascade.h"
#include "Led.h"

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
    pUSART->Frame.pu8Receive = RS485ModbusBuff;
    pUSART->Frame.pu8Send = RS485ModbusBuff;
    pUSART->Frame.pu8DMAReceive = RS485ModbusDMABuff;
    pUSART->Frame.u16ReceiveBuffMax = RS485_MODBUS_RX_BUFF;
    pUSART->Frame.u8IdleNmsConfig = u8BaudRateBytePeriodNmsConfigTab[pUSART->Frame.eBaudID];

    pUSART->SerialDevInit = NULL;
    //pUSART->SerialHardWareSetting         = NULL;//RS485MB_HardwareSetting;
    pUSART->SerialReceiveOK = RS485ModbusReceiveOK;
    pUSART->SerialDevError = RS485ModbusDevError;
    //pUSART->SerialDevFrameTime            = NULL;
    pUSART->SerialDevReset = RS485ModbusReset;
    //pUSART->SerialSendPrepair             = NULL;

    pUSART->pStart = BSP_RS485ModbusSendStart;
    pUSART->pStop = BSP_RS485ModbusSendStop;
    pUSART->pSend = BSP_RS485ModbusDirectSend;
    pUSART->pReceive = BSP_RS485ModbusDirectReceive;

    pUSART->pReceive();

    BSP_ModbusUsartDMA_Init(RS485ModbusDMABuff, RS485ModbusBuff);
    BSP_ModbusUSART_Init((uint32_t)eBaudRateTab[pUSART->Frame.eBaudID], pUSART->Frame.eStop, pUSART->Frame.eParity);

    return OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusSendOK(void)
{
    if (eSERIAL_BUS_STATE_SEND_DATA == RS485Modbus.Frame.eTxState)
    {
        RS485Modbus.Frame.eTxState = eSERIAL_BUS_STATE_SEND_DATA_OK;
        RS485Modbus.Frame.u8IdleNms = RS485Modbus.Frame.u8IdleNmsConfig;
        RS485Modbus.Frame.u8RxTxShiftNms = u8SerialRxTxShiftTimeConfigTab[RS485Modbus.Frame.eBaudID];
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

    pSerial->eRxState = eSERIAL_BUS_STATE_IDLE;
    pSerial->eTxState = eSERIAL_BUS_STATE_IDLE;

    //u16RegID = pSerial->pu8Receive[2] << 8 | pSerial->pu8Receive[3];
    if (pSerial->pu8Receive[0] != (*pSerial->pu8PhyAddress))
    {
        return !OK;
    }

    if (pSerial->pu8Receive[1] == 0x17)
    {
          UpgradeModbus_SlaveReceive( pSerial->pu8DMAReceive,\
                                    pSerial->u16ReceiveBytesCnt - 2,\
                                    0,\
                                    Dev.Cfg.u8ModbusPhyAdd,\
                                    Dev.Cfg.eBaudRateID,\
                                    Dev.Cfg.eStops,\
                                    Dev.Cfg.eParity,\
                                    0 );
          return ~OK;
    }
    else
    {
        
    
        if (RS485ModbusRTU(pSerial->pu8Receive, pSerial->pu8Send, &pSerial->u16ReceiveBytesMax))
        {
            pSerial->u16ReceiveBytesMax = 0;
            return !OK;
        }
        USART_ReceiveCount(pSerial);
        USART_StateSetSend(pSerial, pSerial->u16ReceiveBytesMax, 0, 0);
    }
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
static uint8_t RS485ModbusRTUAbnormal(uint8_t *p8ReceiveBuff, uint8_t *p8SendBuff, uint8_t u8Code)
{
    uint16_t u16CRC;

    p8SendBuff[0] = p8ReceiveBuff[0];
    p8SendBuff[1] = p8ReceiveBuff[1] | 0x80;
    p8SendBuff[2] = u8Code;
    u16CRC = CRC16Get(p8SendBuff, 3);
    p8SendBuff[3] = u16CRC & 0xFF;
    p8SendBuff[4] = u16CRC >> 8;
    return 0;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485ModbusRTU(uint8_t *p8ReceiveBuff, uint8_t *p8SendBuff, uint16_t *pu16Length)
{
    uint8_t u8Cmd;
    uint16_t u16Address;
    uint16_t u16NRegs;
    uint16_t u16CRC;

    uint16_t u16Nums;
    uint8_t u8Index;

    uint16_t u16RegValue;
    uint8_t u8Status;

    u8Cmd = p8ReceiveBuff[1];

    switch (u8Cmd)
    {
    case MB_FUNC_READ_COILS:
        break;
    case MB_FUNC_WRITE_SINGLE_COIL:
        break;
    case MB_FUNC_WRITE_MULTIPLE_COILS:
        break;

    case MB_FUNC_READ_HOLDING_REGISTER:
    {
#ifndef MODBUS_485_CRC_DISABLE
        if (0x00 != CRC16Get(p8ReceiveBuff, 8))
        {
            return !OK;
        }
#endif

        u16Address = (uint16_t)p8ReceiveBuff[2] << 8 | (uint16_t)p8ReceiveBuff[3];
        u16NRegs = (uint16_t)p8ReceiveBuff[4] << 8 | (uint16_t)p8ReceiveBuff[5];

        u16Nums = u16NRegs * 2 + 5;
        if (u16Nums >= RS485_MODBUS_TX_BUFF)
        {
            *pu16Length = 5;
            return RS485ModbusRTUAbnormal(p8ReceiveBuff, p8SendBuff, 0x02);
        }

        if (eMODBUS_OK != MB_ReadHoldReg(&p8SendBuff[3], u16Address, u16NRegs))
        {
            *pu16Length = 5;
            return RS485ModbusRTUAbnormal(p8ReceiveBuff, p8SendBuff, 0x02);
        }

        p8SendBuff[0] = p8ReceiveBuff[0];
        p8SendBuff[1] = p8ReceiveBuff[1];
        p8SendBuff[2] = u16NRegs * 2;
        u16Nums = p8SendBuff[2] + 3;

        u16CRC = CRC16Get(p8SendBuff, u16Nums);
        p8SendBuff[u16Nums] = u16CRC & 0xFF;
        p8SendBuff[u16Nums + 1] = u16CRC >> 8;

        *pu16Length = p8SendBuff[2] + 5;

        return OK;
        break;
    }
    case MB_FUNC_READ_INPUT_REGISTER:

#ifndef MODBUS_485_CRC_DISABLE
        if (0x00 != CRC16Get(p8ReceiveBuff, 8))
        {
            return !OK;
        }
#endif

        u16Address = (uint16_t)p8ReceiveBuff[2] << 8 | (uint16_t)p8ReceiveBuff[3];
        u16NRegs = (uint16_t)p8ReceiveBuff[4] << 8 | (uint16_t)p8ReceiveBuff[5];

        u16Nums = u16NRegs * 2 + 5;
        if (u16Nums >= RS485_MODBUS_TX_BUFF)
        {
            *pu16Length = 5;
            return RS485ModbusRTUAbnormal(p8ReceiveBuff, p8SendBuff, 0x02);
        }

        if (eMODBUS_OK != MB_ReadInputReg(&p8SendBuff[3], u16Address, u16NRegs))
        {
            *pu16Length = 5;
            return RS485ModbusRTUAbnormal(p8ReceiveBuff, p8SendBuff, 0x02);
        }

        p8SendBuff[0] = p8ReceiveBuff[0];
        p8SendBuff[1] = p8ReceiveBuff[1];
        p8SendBuff[2] = u16NRegs * 2;
        u16Nums = u16NRegs * 2 + 3;

        u16CRC = CRC16Get(p8SendBuff, u16Nums);
        p8SendBuff[u16Nums] = u16CRC & 0xFF;
        p8SendBuff[u16Nums + 1] = u16CRC >> 8;

        *pu16Length = p8SendBuff[2] + 5;
        return OK;
        break;

    case MB_FUNC_WRITE_REGISTER:

#ifndef MODBUS_485_CRC_DISABLE
        if (0x00 != CRC16Get(p8ReceiveBuff, 8))
        {
            return !OK;
        }
#endif

        u16Address = (uint16_t)p8ReceiveBuff[2] << 8 | (uint16_t)p8ReceiveBuff[3];
        u16RegValue = (uint16_t)p8ReceiveBuff[4] << 8;
        u16RegValue |= (uint16_t)p8ReceiveBuff[5];

        if (OK != RS485ModbusGetChannelAndRegPermission(MB_FUNC_WRITE_REGISTER, p8ReceiveBuff[2], p8ReceiveBuff[3], u16RegValue))
        {
            return !OK;
        }
        u8Status = MB_WriteHoldReg(u16Address, u16RegValue);
        if (u8Status > eMODBUS_OK_NO_REPLY_ENOCEAN)
        {
            *pu16Length = 5;
            return RS485ModbusRTUAbnormal(p8ReceiveBuff, p8SendBuff, 0x03);
        }

        for (u8Index = 0; u8Index < 8; u8Index++)
        {
            p8SendBuff[u8Index] = p8ReceiveBuff[u8Index];
        }

        *pu16Length = 8;

        /****** write reg update the ******************/
        return OK;
        break;

    case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
        u16Address = (uint16_t)p8ReceiveBuff[2] << 8 | (uint16_t)p8ReceiveBuff[3];
        u16NRegs = (uint16_t)p8ReceiveBuff[4] << 8 | (uint16_t)p8ReceiveBuff[5];
#ifndef MODBUS_485_CRC_DISABLE
        if (0x00 != CRC16Get(p8ReceiveBuff, u16NRegs * 2 + 9))
        {
            return !0;
        }
#endif

        u8Index = 0;
        while (u16NRegs > 0)
        {
            u16RegValue = (uint16_t)p8ReceiveBuff[7 + u8Index * 2] << 8;
            u16RegValue |= (uint16_t)p8ReceiveBuff[8 + u8Index * 2];
            u8Index++;
            u16Address++;
            u16NRegs--;
        }
        break;

    default:
#ifndef MODBUS_485_CRC_DISABLE
        if (0x00 != CRC16Get(p8ReceiveBuff, 8))
        {
            return !OK;
        }
#endif
        *pu16Length = 5;
        return RS485ModbusRTUAbnormal(p8ReceiveBuff, p8SendBuff, 0x01);
    }
    return !OK;
}
/**
 * @brief
 * @param
 * @retval
 */
eMODBUS_ERROR_TYPE MB_WriteHoldReg(uint16_t u16RegID, uint16_t u16RegValue)
{
    //uint8_t u8Channel;

    //u8Channel = 0xFF;

    if (u16RegID != 0x00)
    {
        Dev_HoldRegUpdateDataSetting(u16RegID, u16RegValue);
        return eMODBUS_OK;
    }


    return eMODBUS_WRITE_ONE_HOLD_VALUE_ERR;
}
/**
 * @brief
 * @param
 * @retval
 */
eMODBUS_ERROR_TYPE MB_ReadHoldReg(uint8_t *pu8SendBuff, uint16_t u16RegID, uint8_t u8RegNums)
{
    uint8_t u8RegLow;
    //uint8_t u8Channel;
    uint8_t i;

    u8RegLow = u16RegID & 0xFF;

    if ( (u16RegID & 0xFF00) == 0x0000 )
    {
        for (i = 0; i < u8RegNums; i++)
        {
            Dev_ReadRegHold(pu8SendBuff, i, u8RegLow + i);
        }
        return eMODBUS_OK;
    }
    return eMODBUS_READ_HOLD_REG_ID_ERR;
}
/**
 * @brief
 * @param
 * @retval
 */
eMODBUS_ERROR_TYPE MB_ReadInputReg(uint8_t *pu8SendBuff, uint16_t u16RegID, uint8_t u8RegNums)
{
    uint8_t u8RegLow;

    uint8_t i;

    u8RegLow = u16RegID & 0xFF;
    if ((u16RegID & 0xFF00) == 0x0000)
    {
        for (i = 0; i < u8RegNums; i++)
        {
            Dev_ReadRegInput(pu8SendBuff, i, u8RegLow + i);
        }
        return eMODBUS_OK;
    }

    return eMODBUS_READ_INPUT_REG_ID_ERR;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusGetRegPermission(uint8_t u8GetRegSize, RegTab_Typedef const *pu32DataTab, uint8_t u8Cmd, uint8_t u8RegIndex, uint16_t u16Data)
{
    uint8_t u8I;

    //uint16_t u16Data = (uint16_t)p8Data[0]<<8|(uint32_t)p8Data[1];

    if (!u8Cmd)
    {
        return !OK;
    }

    for (u8I = 0; u8I < u8GetRegSize; u8I++)
    {
        if (u8RegIndex != pu32DataTab[u8I].u8RegID)
        {
            continue;
        }

        if (!(u8Cmd & pu32DataTab[u8I].u3Permission)) //
        {
            return !OK;
        }

        if (MB_FUNC_WRITE_REGISTER == u8Cmd)
        {
            if (REG_VALUE_RANGE_DISABLE == pu32DataTab[u8I].u1RangeEnable)
            {
                return OK;
            }
            else if ((u16Data >= pu32DataTab[u8I].u16MinValue) && (u16Data <= pu32DataTab[u8I].u16MaxValue)) //
            {
                return OK;
            }
        }
        else if ((MB_FUNC_READ_INPUT_REGISTER == u8Cmd) || (MB_FUNC_READ_HOLDING_REGISTER == u8Cmd))
        {
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
uint8_t RS485ModbusGetChannelAndRegPermission(uint8_t u8Cmd, uint8_t u8Channel, uint8_t u8RegIndex, uint16_t u16Data)
{
    /* Must use "<=", because the MSC telegram relay channel is from 1 to 4 */

    if (0 == u8Channel) //
    {
        return RS485ModbusGetRegPermission(Dev_GetRegTabSize(), DevRegTab, u8Cmd, u8RegIndex, u16Data);
    }

    return !OK;
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval
 */
eMODBUS_ERROR_TYPE Dev_HoldRegUpdateDataSetting(uint16_t u16RegID, uint16_t u16RegValue)
{
    switch (u16RegID)
    {
    case MB_HOLD_SET_ADDR: //设置地址
        return eMODBUS_OK;

    case MB_HOLD_SET_BAUD: //设置波特率
        return eMODBUS_OK;

    case MB_HOLD_TIME_RESET_HIGH_PASSWORD: //时间复位密码高16位

        return eMODBUS_OK;

    case MB_HOLD_TIME_RESET_LOW_PASSWORD: //时间复位密码低16位

        return eMODBUS_OK;

    case MB_HOLD_DEVICE_RESET_TIMES: //设备运行时间复位次数

        return eMODBUS_OK;

        break;

    case MB_HOLD_CO2_RESET_TIMES: //CO2运行时间复位次数

        return eMODBUS_OK;
        break;

    case MB_HOLD_CH2O_RESET_TIMES: //甲醛运行时间复位次数

        return eMODBUS_OK;
        break;

    case MB_HOLD_PMSA03_RESET_TIMES: //PM2.5运行时间复位次数

        return eMODBUS_OK;
        break;

    case MB_HOLD_CH2O_FACTORY_YEAR_MONTH: //甲醛出厂时间年月

        break;
    case MB_HOLD_CH2O_FACTORY_DAY: //甲醛出厂时间日

        break;
    case MB_HOLD_CH2O_INSTALL_YEAR_MONTH: //甲醛安装时间年月

        break;
    case MB_HOLD_CH2O_INSTALL_DAY: //甲醛安装时间日

        break;
    case MB_HOLD_485MB_ADD:  //485地址设置

        /*
        if ( u16RegValue > 15 && u16RegValue < 32 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }
        Dev.Cfg.u8ModbusPhyAdd = u16RegValue;
        RS485ModbusInit(&RS485Modbus);
        FLASHRUN.u8CfgUpdateFlag = 1;
        */
        return eMODBUS_OK;   
        break;

    case MB_HOLD_485MB_BAUD: //485波特率设置

        if ( u16RegValue > 7 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }

        switch (u16RegValue)
        {
        case 0:
            Dev.Cfg.eBaudRateID = eBAUD_1200_ID;
            break;
        case 1:
            Dev.Cfg.eBaudRateID = eBAUD_2400_ID;
            break;
        case 2:
            Dev.Cfg.eBaudRateID = eBAUD_4800_ID;
            break;
        case 3:
            Dev.Cfg.eBaudRateID = eBAUD_9600_ID;
            break;
        case 4:
            Dev.Cfg.eBaudRateID = eBAUD_19200_ID;
            break;
        case 5:
            Dev.Cfg.eBaudRateID = eBAUD_38400_ID;
            break;
        case 6:
            Dev.Cfg.eBaudRateID = eBAUD_57600_ID;
            break;         
        case 7:
            Dev.Cfg.eBaudRateID = eBAUD_115200_ID;
            break;                                                                        

        default:
            break;
        }
        /*
        if (1 == u16RegValue)
        {
            Dev.Cfg.eBaudRateID = eBAUD_115200_ID;
        }
        else
        {
            Dev.Cfg.eBaudRateID = eBAUD_9600_ID;
        }
        */
        RS485Modbus.Frame.eBaudID = Dev.Cfg.eBaudRateID;
        RS485ModbusInit(&RS485Modbus);
        FLASHRUN.u8CfgUpdateFlag = 1;
        return eMODBUS_OK;

        break;
    case MB_HOLD_485MB_STOPS: //485停止位设置

        if ( u16RegValue > 1 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }
        if(0 == u16RegValue)
        {
            Dev.Cfg.eStops = eSTOP_1;
        }
        else if(1 == u16RegValue)
        {
            Dev.Cfg.eStops = eSTOP_2;
        }
        RS485Modbus.Frame.eStop = Dev.Cfg.eStops;
        RS485ModbusInit(&RS485Modbus); 
        FLASHRUN.u8CfgUpdateFlag = 1;      
        return eMODBUS_OK;
        break;
    case MB_HOLD_485MB_PARITY: //485奇偶校验位设置

        if ( u16RegValue > 2 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }
        if(0 == u16RegValue)
        {
            Dev.Cfg.eParity = ePARITY_NONE;
        }
        else if(1 == u16RegValue)
        {
            Dev.Cfg.eParity = ePARITY_EVEN;
        }
        else if(2 == u16RegValue)
        {
            Dev.Cfg.eParity = ePARITY_ODD;
        }
        RS485Modbus.Frame.eParity = Dev.Cfg.eParity;
        RS485ModbusInit(&RS485Modbus); 
        FLASHRUN.u8CfgUpdateFlag = 1;  
        return eMODBUS_OK;
        break;                        

    case MB_HOLD_TEMPERATURE_CALIB: //温度校准 
        
        if (u16RegValue < 500 &&  u16RegValue > 1750 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }
        ReportedData.u16CalibrationT  =  CalibrationValue_Processing(u16RegValue,SHT20.i16TemperatureOfDegreesCelsius);
        Dev.Cfg.u16CalibrationT       = ReportedData.u16CalibrationT;
        FLASHRUN.u8CfgUpdateFlag      = 1;       
        return eMODBUS_OK;
        break;

    case MB_HOLD_HUMIDITY_CALIB: //湿度校准
        
        if (u16RegValue > 200 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }        
        ReportedData.u16CalibrationH =  CalibrationValue_Processing(u16RegValue*2,SHT20.u8HumidityValue);
        Dev.Cfg.u16CalibrationH      =  ReportedData.u16CalibrationH;
        FLASHRUN.u8CfgUpdateFlag     =  1;
        return eMODBUS_OK;
        break;

    case MB_HOLD_CO2_CALIB: //CO2校准
        
        if (u16RegValue < 400 && u16RegValue > 5000 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }           
        ReportedData.u16CalibrationCO2  =  CalibrationValue_Processing(u16RegValue,CH2O_CO2.u16CO2Numerical);
        Dev.Cfg.u16CalibrationCO2       = ReportedData.u16CalibrationCO2;
        FLASHRUN.u8CfgUpdateFlag        = 1;
        return eMODBUS_OK;
        break;

    case MB_HOLD_PM1_CALIB: //PM1.0校准
        
        if (u16RegValue > 500 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }   
        ReportedData.u16CalibrationPM10  =  CalibrationValue_Processing(u16RegValue,PMSA.u16PM10Numerical);
        Dev.Cfg.u16CalibrationPM10       = ReportedData.u16CalibrationPM10;
        FLASHRUN.u8CfgUpdateFlag         = 1;
        return eMODBUS_OK;
        break;

    case MB_HOLD_PM25_CALIB: //PM2.5校准

        if (u16RegValue > 500 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }  
        ReportedData.u16CalibrationPM25 = CalibrationValue_Processing(u16RegValue, PMSA.u16PM25Numerical);
        Dev.Cfg.u16CalibrationPM25      = ReportedData.u16CalibrationPM25;
        FLASHRUN.u8CfgUpdateFlag        = 1;
        return eMODBUS_OK;
        break;

    case MB_HOLD_PM10_CALIB: //PM10校准
        
        if (u16RegValue > 500 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }          
        ReportedData.u16CalibrationPM100  =  CalibrationValue_Processing(u16RegValue,PMSA.u16PM100Numerical);
        Dev.Cfg.u16CalibrationPM100       = ReportedData.u16CalibrationPM100;
        FLASHRUN.u8CfgUpdateFlag          = 1;
        return eMODBUS_OK;
        break;

    case MB_HOLD_CH2O_CALIB: //CH2O(甲醛) 校准
        
        if (u16RegValue > 1500 )
        {
            return eMODBUS_OK_NO_REPLY_ENOCEAN;
        }  
        ReportedData.u16CalibrationCH2O   =  CalibrationValue_Processing(u16RegValue,CH2O_CO2.u16CH2ONumerical);
        Dev.Cfg.u16CalibrationCH2O        = ReportedData.u16CalibrationCH2O;
        FLASHRUN.u8CfgUpdateFlag          = 1;
        return eMODBUS_OK;
        break;

    case MB_HOLD_LED_SWITCH: //LED指示关闭

        if (u16RegValue == 0x01)
        {
            Dev.Cfg.u8LedSwtichFalg   = u16RegValue;
            LED.u8LedSwtichFalg       = Dev.Cfg.u8LedSwtichFalg;
            LED.eWorkMode             = eLEDWORK_SWITCH;
            FLASHRUN.u8CfgUpdateFlag  = 1; 
            return eMODBUS_OK;
            break;
        }
        else
        {
            Dev.Cfg.u8LedSwtichFalg   = u16RegValue;
            LED.u8LedSwtichFalg       = Dev.Cfg.u8LedSwtichFalg;
            LED.eWorkMode             = eLEDWORK_SWITCH;
            FLASHRUN.u8CfgUpdateFlag  = 1; 
            return eMODBUS_OK;
            break;            
        }

    case MB_HOLD_ENOCEAN_REAPTER: //Enocean Reapter

        Dev.Cfg.u8Repeater = u16RegValue;
        /* Must update the tcm310 */
        EnOcean_InitGetInfo(&Radio);
        return eMODBUS_OK;
        break;
        
    case MB_HOLD_AIRBOX_RESET_FACTORY_SETTINGS: //AirBox恢复出厂设置

        if (u16RegValue == 0x01 )
        {
            DevLoadDefaultSettingsByReset();
            FLASHRUN.u8CfgUpdateFlag = 1; 
            FLASHRUN.u8LogUpdateFlag = 1;
        }
        break;

    case VOID_RWPARAM_RESET_FACTORY_SETTINGS: //传感器恢复出厂设置

        switch (u16RegValue)
        {
        case 0x00: //CH2O
            Dev.Cfg.u16CalibrationCH2O = 0x00;
            FLASHRUN.u8CfgUpdateFlag = 1;  
            break;
        case 0x01: //CO2
            Dev.Cfg.u16CalibrationCO2 = 0x00;
            FLASHRUN.u8CfgUpdateFlag = 1;  
            break;
        case 0x02: //H（湿度）
            Dev.Cfg.u16CalibrationH = 0x00;
            FLASHRUN.u8CfgUpdateFlag = 1;  
            break;
        case 0x03: //T（温度）
            Dev.Cfg.u16CalibrationT = 0x00;
            FLASHRUN.u8CfgUpdateFlag = 1;  
            break;
        case 0x04: //PM10
            Dev.Cfg.u16CalibrationPM100 = 0x00;
            FLASHRUN.u8CfgUpdateFlag = 1;  
            break;   
        case 0x05: //PM2.5
            Dev.Cfg.u16CalibrationPM25 = 0x00;
            FLASHRUN.u8CfgUpdateFlag = 1;  
            break;  
        case 0x06: //PM1
            Dev.Cfg.u16CalibrationPM10 = 0x00;
            FLASHRUN.u8CfgUpdateFlag = 1;  
            break;                                                           

        default:
            break;
        }
        
        break;

    case MB_HOLD_SENSOR_REFRESH: //传感器刷新
    
        if (u16RegValue == 1)
        {
            SHT20.eRunState = eSHT20_START_MEASUREMENT_T;
            PMSA.eRunState = ePMSA_IDLE;
            CH2O_CO2.eRunState = eCH2O_START_MEASUREMENT;
            ReportedData.eRunStateProactive = eENOCEAN_PROACTIVESEND_CO2;
            ReportedData.u32ReadWait = 100;
            return eMODBUS_OK;
        }

        //Enocean.eRunState=eENOCEAN_SEND_CO2;

        break;

        /********************************************************************************/

    default:
        break;
    }
    return eMODBUS_WRITE_ONE_HOLD_VALUE_ERR;
}
/**
 * @brief
 * @param
 * @retval
 */
uint8_t Dev_ReadRegHold(uint8_t *pu8SendBuff, uint16_t u16RegBuffID, uint16_t u16RegID)
{
    uint16_t u16Value;

    pu8SendBuff[u16RegBuffID * 2] = 0x00;
    pu8SendBuff[u16RegBuffID * 2 + 1] = 0x00;

    switch (u16RegID)
    {
    case MB_HOLD_SET_ADDR: //设置地址
        return eMODBUS_OK;

    case MB_HOLD_SET_BAUD: //设置波特率
        return eMODBUS_OK;

    case MB_HOLD_TIME_RESET_HIGH_PASSWORD: //时间复位密码高16位
        pu8SendBuff[u16RegBuffID * 2] = (uint8_t)(Dev.Cfg.u32ResetPassword >> 24);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(Dev.Cfg.u32ResetPassword >> 16);
        return eMODBUS_OK;

    case MB_HOLD_TIME_RESET_LOW_PASSWORD: //时间复位密码低16位
        pu8SendBuff[u16RegBuffID * 2] = (uint8_t)(Dev.Cfg.u32ResetPassword >> 8);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)Dev.Cfg.u32ResetPassword;
        return eMODBUS_OK;

    case MB_HOLD_DEVICE_RESET_TIMES: //设备运行时间复位次数

        return eMODBUS_OK;

        break;

    case MB_HOLD_CO2_RESET_TIMES: //CO2运行时间复位次数

        return eMODBUS_OK;
        break;

    case MB_HOLD_CH2O_RESET_TIMES: //甲醛运行时间复位次数

        return eMODBUS_OK;
        break;

    case MB_HOLD_PMSA03_RESET_TIMES: //PM2.5运行时间复位次数

        return eMODBUS_OK;
        break;

    case MB_HOLD_CH2O_FACTORY_YEAR_MONTH: //甲醛出厂时间年月

        break;
    case MB_HOLD_CH2O_FACTORY_DAY: //甲醛出厂时间日

        break;
    case MB_HOLD_CH2O_INSTALL_YEAR_MONTH: //甲醛安装时间年月

        break;
    case MB_HOLD_CH2O_INSTALL_DAY: //甲醛安装时间日

        break;
    case MB_HOLD_485MB_ADD: //485地址设置
        
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u8ModbusPhyAdd;
        break;

    case MB_HOLD_485MB_BAUD: //485波特率设置

        switch (Dev.Cfg.eBaudRateID)
        {
        case eBAUD_1200_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_1200_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x00;
            break;
        case eBAUD_2400_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_2400_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x01;
            break;
        case eBAUD_4800_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_4800_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x02;
            break;
        case eBAUD_9600_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_9600_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x03;
            break;
        case eBAUD_19200_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_19200_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x04;
            break;
        case eBAUD_38400_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_38400_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x05;
            break;
        case eBAUD_57600_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_57600_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x06;
            break;         
        case eBAUD_115200_ID:
            //Dev.Cfg.eBaudRateID = eBAUD_115200_ID;
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x07;
            break;                                                                        

        default:
            break;
        }

        break;

    case MB_HOLD_485MB_STOPS: //485停止位设置

        if (Dev.Cfg.eStops == eSTOP_2 )
        {
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x01;
        }
        else
        {
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x00;
        }
        break;

    case MB_HOLD_485MB_PARITY: //485奇偶校验位设置

        if (Dev.Cfg.eParity == ePARITY_ODD )
        {
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x02;
        }
        else if (Dev.Cfg.eParity == ePARITY_EVEN )
        {
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x01;
        }
        else if (Dev.Cfg.eParity == ePARITY_NONE )
        {
            pu8SendBuff[u16RegBuffID * 2 + 1] = 0x00;
        }        
        break;    
       
    case MB_HOLD_TEMPERATURE_CALIB: //温度校准
        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u16CalibrationT >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u16CalibrationT & 0xFF ;
        break;
    case MB_HOLD_HUMIDITY_CALIB: //湿度校准

        u16Value = Dev.Cfg.u16CalibrationH;
        if ( 0x01 == u16Value >> 15)
        {
            u16Value = (u16Value & 0x7FFF)/2 ;
            u16Value =  u16Value | 0x8000;
        }
        else
        {
            u16Value = (u16Value & 0x7FFF)/2 ;
        }
        pu8SendBuff[u16RegBuffID * 2]     = u16Value >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = u16Value & 0xFF;
        break;
    case MB_HOLD_CO2_CALIB: //CO2校准
        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u16CalibrationCO2 >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u16CalibrationCO2 & 0xFF;
        break;
    case MB_HOLD_PM1_CALIB: //PM1.0校准
        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u16CalibrationPM10 >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u16CalibrationPM10 & 0xFF;
        break;
    case MB_HOLD_PM25_CALIB: //PM2.5校准
        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u16CalibrationPM25 >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u16CalibrationPM25 & 0xFF;
        break;
    case MB_HOLD_PM10_CALIB: //PM10校准
        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u16CalibrationPM100 >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u16CalibrationPM100 & 0xFF;
        break;
    case MB_HOLD_CH2O_CALIB: //CH2O(甲醛) 校准
        //Dev.Cfg.u16CalibrationCH2O        = Dev.Cfg.u16CalibrationCH2O / 2;
        u16Value = Dev.Cfg.u16CalibrationCH2O;
        
        pu8SendBuff[u16RegBuffID * 2]     = Dev.Cfg.u16CalibrationCH2O >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u16CalibrationCH2O & 0xFF;
        break;
    case MB_HOLD_LED_SWITCH: //LED指示关闭
        
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u8LedSwtichFalg;
        return eMODBUS_OK;
        break;

    case MB_HOLD_ENOCEAN_REAPTER: //Enocean Reapter
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.Cfg.u8Repeater;
        break;
        
    case MB_HOLD_AIRBOX_RESET_FACTORY_SETTINGS: //AirBox恢复出厂设置
        pu8SendBuff[u16RegBuffID * 2] = 0x00;
        pu8SendBuff[u16RegBuffID * 2 + 1] = 0x01;
        return eMODBUS_OK;
        break;        

    case VOID_RWPARAM_RESET_FACTORY_SETTINGS: //传感器恢复出厂设置
        pu8SendBuff[u16RegBuffID * 2] = 0x00;
        pu8SendBuff[u16RegBuffID * 2 + 1] = 0x01;
        return eMODBUS_OK;
        break;

    case MB_HOLD_SENSOR_REFRESH: //传感器刷新
        pu8SendBuff[u16RegBuffID * 2] = 0x00;
        pu8SendBuff[u16RegBuffID * 2 + 1] = 0x01;
        return eMODBUS_OK;
        break;

        /********************************************************************************/

    default:
        break;
    }
    return eMODBUS_WRITE_ONE_HOLD_VALUE_ERR;
}
/**
 * @brief
 * @param
 * @retval
 */

uint8_t Dev_ReadRegInput(uint8_t *pu8SendBuff, uint16_t u16RegBuffID, uint16_t u16RegID)
{
    uint16_t u16Value;
    uint8_t u8Value1;
    uint8_t u8Value2;
    pu8SendBuff[u16RegBuffID * 2] = 0x00;
    pu8SendBuff[u16RegBuffID * 2 + 1] = 0x00;
    switch (u16RegID)
    {

    case MB_INPUT_SOFT_YEAR_MONTH: //软件版本号年月

        u8Value1 = (uint8_t)(Dev.u32BuildYYMMDD >> 16) ;
        u8Value1 = (u8Value1/16)*10 + u8Value1 % 16;

        u8Value2 = (uint8_t)(Dev.u32BuildYYMMDD >> 8);
        u8Value2 = (u8Value2/16)*10 + u8Value2 % 16;

        u16Value = u8Value1*100 + u8Value2;
        //u16Value = (uint16_t)(u8Value1)<<8 + u8Value2 ;
        //u16Value = (u16Value<<8) + u8Value2 ;

        pu8SendBuff[u16RegBuffID * 2] = (uint8_t)(u16Value>>8);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)(u16Value);
        break;

    case MB_INPUT_SOFT_DAY_VERSION: //软件版本号日期版本
        /*
        pu8SendBuff[u16RegBuffID * 2] = (uint8_t)(Dev.u32BuildYYMMDD);
        pu8SendBuff[u16RegBuffID * 2 + 1] = (uint8_t)Dev.u16HWVersion;
        */
        u8Value1 = (uint8_t)(Dev.u32BuildYYMMDD);
        u8Value1 = (u8Value1/16)*10 + u8Value1 % 16;

        u8Value2 = (uint8_t)Dev.u16HWVersion;
        u8Value2 = (u8Value2/16)*10 + u8Value2 % 16;

        pu8SendBuff[u16RegBuffID * 2] = u8Value1;
        pu8SendBuff[u16RegBuffID * 2 + 1] = u8Value2;

        break;

    case MB_INPUT_SYSTEM_VOLT: //系统MCU电压

        break;

    case MB_INPUT_ENOCEAN_RSSI: //Enocean RSSI值

        //pu8SendBuff[u16RegBuffID * 2] = Dev.u16FWVersion >> 8;
        //pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16FWVersion & 0xFF;

        break;

    case MB_INPUT_WIFI_RSSI: //WIFI RSSI值

        break;

    case MB_INPUT_DEVICE_RUNNING_HIGH_TIME: //设备运行时间高16位

        break;

    case MB_INPUT_DEVICE_RUNNING_LOW_TIME: //设备运行时间低16位

        break;

    case MB_INPUT_CH2O_RUNNING_HIGH_TIME: //甲醛运行时间高16位

        break;

    case MB_INPUT_CH2O_RUNNING_LOW_TIME: //甲醛运行时间低16位

        break;

    case MB_INPUT_CO2_RUNNING_HIGH_TIME: //CO2运行时间高16位

        break;

    case MB_INPUT_CO2_RUNNING_LOW_TIME: //CO2运行时间低16位

        break;

    case MB_INPUT_PMSA03_RUNNING_HIGH_TIME: //PM2.5运行时间高16位

        break;

    case MB_INPUT_PMSA03_RUNNING_LOW_TIME: //PM2.5运行时间低16位

        break;
    /*
    case MB_INPUT_DEVICE_RUNNING_TIME: //设备运行时间

        break;

    case MB_INPUT_CH2O_RUNNING_TIME: //甲醛运行时间

        break;

    case MB_INPUT_CO2_RUNNING_TIME: //CO2运行时间

        break;

    case MB_INPUT_PMSA03_RUNNING_TIME: //PM2.5运行时间

        break;
    */

    case MB_INPUT_SENSOR_RUNNING_TIME: //设备、甲醛、CO2PM2.5、运行时间

        break;

    case MB_INPUT_COMMUNICATION_FAULT: //通信故障
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16CommunicationFault >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16CommunicationFault & 0xFF;
        break;

    case MB_INPUT_DEVICE_FAULT: //设备故障
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16DebiceFault >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16DebiceFault & 0xFF;
        break;

    case MB_INPUT_SENSOR_STATUS: //传感器状态

        break;

    case MB_INPUT_TEMPERATURE_VALUE: //温度值 --- 温度范围(-40~125℃ + 50℃ ) * 10 + 10%的校准参数 --- 90~1925
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16TemperatureValue >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16TemperatureValue & 0xFF;
        break;
    case MB_INPUT_HUMIDITY_VALUE: //湿度值 --- 湿度范围(0~100 %RH) * 2 + 10%的校准参数 --- 0~220
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16HumidityValue >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16HumidityValue & 0xFF;
        break;
    case MB_INPUT_CO2_VALUE: //CO2值 --- 最大值暂定8000 测量范围: 0-5000ppm
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16CO2Value >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16CO2Value & 0xFF;
        break;
    case MB_INPUT_PM1_VALUE: //PM1.0值
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16PM1Value >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16PM1Value & 0xFF;
        break;
    case MB_INPUT_PM25_VALUE: //PM25值
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16PM25Value >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16PM25Value & 0xFF;
        break;
    case MB_INPUT_PM10_VALUE: //PM100值
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16PM100Value >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16PM100Value & 0xFF;
        break;
    case MB_INPUT_CH2O_VALUE: //CH2O(甲醛)值
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16CH2OValue >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16CH2OValue & 0xFF;
        break;
    case MB_INPUT_SENSOR_VALUE: //所有传感数据(温度、湿度、CO2、PM1.0、PM2.5、PM10、CH2O)
        pu8SendBuff[u16RegBuffID * 2] = 0x00;
        pu8SendBuff[u16RegBuffID * 2 + 1] = 0x00;
        break;
    case MB_INPUT_AIR_QUALITY: //空气质量等级
        pu8SendBuff[u16RegBuffID * 2] = Dev.u16AirQuality >> 8;
        pu8SendBuff[u16RegBuffID * 2 + 1] = Dev.u16AirQuality & 0xFF;
        break;        

    default:
        return !OK;
        break;
    }
    return OK;
}

/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/

/* End of file */