
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"

#include "BSP.h"
#include "Dataconfigure.h"
#include "main.h"
#include "EnOceanCascade.h"
#include "EnOceanMSCCascade.h"
#include "RS485Modbus.h"

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCGetRegPermission(uint8_t u8GetRegSize, RegTab_Typedef const *pu32DataTab, uint8_t u8Cmd, uint8_t u8RegIndex, uint32_t u32Data);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCGetRegPermission(uint8_t u8GetRegSize, RegTab_Typedef const *pu32DataTab, uint8_t u8Cmd, uint8_t u8RegIndex, uint32_t u32Data)
{

    return !OK;
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCGetChannelAndRegPermission(uint8_t u8Cmd, uint8_t u8Channel, uint8_t u8RegIndex, uint32_t u32Data)
{
    if (0 == u8Channel) //
    {
        return EnOceanMSCGetRegPermission(Dev_GetRegTabSize(), DevRegTab, u8Cmd, u8RegIndex, u32Data);
    }

    return !OK;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteSettings(Radio_Typedef *pRadio)
{
    uint8_t u8Cmd;
    uint8_t u8BuffChannel;
    uint8_t u8MSCChannel;
    uint8_t u8Register;
    uint32_t u32Data;

    u8Cmd = pRadio->Telegram.raw.bytes[1] & 0x0F;

    u8MSCChannel = pRadio->Telegram.raw.bytes[2];

    u8Register = pRadio->Telegram.raw.bytes[3];
    u32Data = pRadio->Telegram.raw.bytes[4] << 24 | pRadio->Telegram.raw.bytes[5] << 16 | pRadio->Telegram.raw.bytes[6] << 8 | pRadio->Telegram.raw.bytes[7];
    if (eMSC_CMD_WRITE != u8Cmd)
    {
        return !OK;
    }

    if (EnOceanMSCGetChannelAndRegPermission(eMSC_CMD_WRITE, u8MSCChannel, u8Register, u32Data))
    {
        return !OK;
    }
    if (EnOceanRadioMapChannel(u8MSCChannel, &u8BuffChannel, 0))
    {
        return !OK;
    }
    //u32Data = (uint32_t)pRadioTel->raw.bytes[4]<<24 | (uint32_t)pRadioTel->raw.bytes[5]<<16 | (uint32_t)pRadioTel->raw.bytes[6]<<8 | (uint32_t)pRadioTel->raw.bytes[7];
    /* Use chip id */
    if (0 == u8MSCChannel) //
    {
        if (EnOceanMSCWriteDevtings(u8Register, u32Data, &Dev))
        {
            return !OK;
        }
        pRadio->u16DataLength = 14;
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

uint8_t EnOceanMSCResponse(Radio_Typedef *pRadio, Dev_Typedef *pDev)
{
    //uint8_t  u8Channel;
    //uint8_t u8Register;
    uint8_t u8MSCChannel;
    //uint8_t u8BuffChannel;

    pRadio->Telegram.raw.bytes[0] = ENOCEAN_MENRED_MAN_ID >> 4;

    pRadio->Telegram.raw.bytes[1] = (ENOCEAN_MENRED_MAN_ID & 0x0F) << 4;

    pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    //u8Register = pRadio->Telegram.raw.bytes[3];

    u8MSCChannel = pRadio->Telegram.raw.bytes[2];
    /*
    if ( EnOceanMSCGetChannelAndRegPermission(eMSC_CMD_READ, u8MSCChannel, u8Register, 0) )
    {
        return !OK;
    }
*/
    /* Must use "<=", because the MSC telegram relay channel is from 1 to 3 */
    /* Dev channel use the ID is tcm310's ChipID */

    if (0x00 == u8MSCChannel)
    {
        EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);
        EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
    }
    else if (1 == u8MSCChannel)
    {
        EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);
        EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
    }
    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */

uint8_t EnOceanMSCWrite(Radio_Typedef *pRadio, Dev_Typedef *pDev)
{
    uint8_t  u8Channel;
    //uint8_t u8Register;
    //uint8_t u8MSCChannel;
    //uint8_t u8BuffChannel;
    uint32_t u32Data;

    u32Data = (uint32_t)pRadio->Telegram.raw.bytes[4] << 24 | (uint32_t)pRadio->Telegram.raw.bytes[5] << 16 | (uint32_t)pRadio->Telegram.raw.bytes[6] << 8 | (uint32_t)pRadio->Telegram.raw.bytes[7];

    u8Channel = pRadio->Telegram.raw.bytes[2];

    EnOceanMSCWriteDevtings(pRadio->Telegram.raw.bytes[3], u32Data, pDev);

    pRadio->Telegram.raw.bytes[0] = ENOCEAN_MENRED_MAN_ID >> 4;

    pRadio->Telegram.raw.bytes[1] = (ENOCEAN_MENRED_MAN_ID & 0x0F) << 4;

    pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    //u8Register = pRadio->Telegram.raw.bytes[3];

    pRadio->Telegram.raw.bytes[2] = u8Channel ;

    EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);
    EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */

void EnOceanMSCSend(Radio_Typedef *pRadio, Dev_Typedef *pDev, uint8_t u8RegH, uint8_t u8RegL)
{
    //uint8_t  u8Channel;
    //uint8_t u8Register;
    //uint8_t u8MSCChannel;
    //uint8_t u8BuffChannel;

    pRadio->Telegram.raw.bytes[0] = ENOCEAN_MENRED_MAN_ID >> 4;

    pRadio->Telegram.raw.bytes[1] = (ENOCEAN_MENRED_MAN_ID & 0x0F) << 4;

    pRadio->Telegram.raw.bytes[1] |= eMSC_CMD_RESPONSE;

    pRadio->Telegram.raw.bytes[2] = u8RegH;

    pRadio->Telegram.raw.bytes[3] = u8RegL;

    EnOceanMSCResponseDevtings(pRadio->Telegram.raw.bytes, pDev);

    EnOceanMSCRadioData(pRadio, 8, 0, 0xFFFFFFFF);
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteSettingsByBaseID(Radio_Typedef *pRadio, uint8_t u8BuffChannel)
{
    uint8_t u8Cmd;

    uint8_t u8Register;
    uint32_t u32Data;

    u8Cmd = pRadio->Telegram.raw.bytes[1] & 0x0F;

    u8Register = pRadio->Telegram.raw.bytes[3];
    u32Data = pRadio->Telegram.raw.bytes[4] << 24 | pRadio->Telegram.raw.bytes[5] << 16 | pRadio->Telegram.raw.bytes[6] << 8 | pRadio->Telegram.raw.bytes[7];
    if (eMSC_CMD_WRITE != u8Cmd)
    {
        return !OK;
    }

    if (EnOceanMSCGetChannelAndRegPermission(eMSC_CMD_WRITE, u8BuffChannel, u8Register, u32Data))
    {
        return !OK;
    }
    //u8BuffChannel = u8MSCChannel;

    if (u8BuffChannel == DEV_CHANNEL)
    {
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
uint8_t EnOceanMSCMasterWriteSettingsByBaseID(Radio_Typedef *pRadio, uint8_t u8BaseOffset)
{
    //uint8_t  u8Cmd;

    //uint8_t  u8BuffChannel;
    uint8_t u8MSCChannel;
    uint8_t u8Register;
    uint32_t u32Data;
    //uint8_t  u8Offset;

    //u8Cmd      = pRadio->Telegram.raw.bytes[1]&0x0F;
    u8MSCChannel = pRadio->Telegram.raw.bytes[2];

    u8Register = pRadio->Telegram.raw.bytes[3];
    u32Data = pRadio->Telegram.raw.bytes[4] << 24 | pRadio->Telegram.raw.bytes[5] << 16 | pRadio->Telegram.raw.bytes[6] << 8 | pRadio->Telegram.raw.bytes[7];

    if (EnOceanMSCGetChannelAndRegPermission(eMSC_CMD_WRITE, u8MSCChannel, u8Register, u32Data))
    {
        return !OK;
    }

    if (u8MSCChannel == DEV_CHANNEL)
    {
    }
    else
    {
        return !OK;
    }

    return OK;
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanMSCWriteDevtings(uint8_t u8RegID, uint32_t u32Data, Dev_Typedef *pDev)
{

    uint16_t u16RegValue;
    switch (u8RegID)
    {
    case MB_HOLD_SET_ADDR:
    case MB_HOLD_SET_BAUD:
    case MB_HOLD_TIME_RESET_PASSWORD:

    case MB_HOLD_DEVICE_RESET_TIMES:
    case MB_HOLD_CO2_RESET_TIMES:
    case MB_HOLD_CH2O_RESET_TIMES:
    case MB_HOLD_PMSA03_RESET_TIMES:
    case MB_HOLD_CH2O_FACTORY_TIME:
    //case MB_HOLD_CH2O_FACTORY_YEAR_MONTH:
    case MB_HOLD_CH2O_FACTORY_DAY:
    case MB_HOLD_CH2O_INSTALL_TIME:
    
    case MB_HOLD_485MB_ADD:
    case MB_HOLD_485MB_BAUD:
    case MB_HOLD_485MB_STOPS:
    case MB_HOLD_485MB_PARITY:

    case MB_HOLD_TEMPERATURE_CALIB:
    case MB_HOLD_HUMIDITY_CALIB:
    case MB_HOLD_CO2_CALIB:
    case MB_HOLD_PM1_CALIB:
    case MB_HOLD_PM25_CALIB:
    case MB_HOLD_PM10_CALIB:
    case MB_HOLD_CH2O_CALIB:
    case MB_HOLD_LED_SWITCH:
    case MB_HOLD_ENOCEAN_REAPTER:
    case MB_HOLD_AIRBOX_RESET_FACTORY_SETTINGS:
    case VOID_RWPARAM_RESET_FACTORY_SETTINGS:
    case MB_HOLD_SENSOR_REFRESH:

    default:
        u16RegValue = (uint16_t)(u32Data & 0xFFFF);
        if (eMODBUS_OK == Dev_HoldRegUpdateDataSetting(u8RegID, u16RegValue))
        {
            return OK;
        }
        break;
    }
    return !OK;

    //return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t u16ChipSelection;
uint8_t EnOceanMSCResponseDevtings(uint8_t *p8Data, Dev_Typedef *pDev)
{

    p8Data[4] = 0;
    p8Data[5] = 0;
    p8Data[6] = 0;
    p8Data[7] = 0;
    switch (p8Data[3])
    {
    case MB_INPUT_SOFT_YEAR_MONTH:
        Dev_ReadRegInput(p8Data, 2, p8Data[3]);
        Dev_ReadRegInput(p8Data, 3, p8Data[3] + 1);
        break;
    case MB_INPUT_SOFT_DAY_VERSION:
        Dev_ReadRegInput(p8Data, 3, p8Data[3]);
        break;
    case MB_INPUT_SYSTEM_VOLT:
    case MB_INPUT_ENOCEAN_RSSI:
    case MB_INPUT_WIFI_RSSI:
    case MB_INPUT_DEVICE_RUNNING_TIME:
        Dev_ReadRegInput(p8Data, 2, p8Data[3]);
        Dev_ReadRegInput(p8Data, 3, p8Data[3] + 1);
        break;

    case MB_INPUT_CH2O_RUNNING_TIME:
        Dev_ReadRegInput(p8Data, 2, p8Data[3]);
        Dev_ReadRegInput(p8Data, 3, p8Data[3] + 1);
        break;

    case MB_INPUT_CO2_RUNNING_TIME:
        Dev_ReadRegInput(p8Data, 2, p8Data[3]);
        Dev_ReadRegInput(p8Data, 3, p8Data[3] + 1);
        break;

    case MB_INPUT_PMSA03_RUNNING_TIME:
        Dev_ReadRegInput(p8Data, 2, p8Data[3]);
        Dev_ReadRegInput(p8Data, 3, p8Data[3] + 1);
        break;

        //    case MB_INPUT_DEVICE_RUNNING_TIME      :
        //    case MB_INPUT_CH2O_RUNNING_TIME        :
        //    case MB_INPUT_CO2_RUNNING_TIME         :
        //    case MB_INPUT_PMSA03_RUNNING_TIME      :
    case MB_INPUT_SENSOR_RUNNING_TIME:
    case MB_INPUT_COMMUNICATION_FAULT:
        Dev_ReadRegInput(p8Data, 3, p8Data[3]);
        break;
    case MB_INPUT_DEVICE_FAULT:
    case MB_INPUT_SENSOR_STATUS:
    case MB_INPUT_TEMPERATURE_VALUE:
    case MB_INPUT_HUMIDITY_VALUE:
    case MB_INPUT_CO2_VALUE:
    case MB_INPUT_PM1_VALUE:
    case MB_INPUT_PM25_VALUE:
    case MB_INPUT_PM10_VALUE:
    case MB_INPUT_CH2O_VALUE:
    case MB_INPUT_SENSOR_VALUE:
        Dev_ReadRegInput(p8Data, 3, p8Data[3]);
        break;

    case MB_HOLD_SET_ADDR:            //设置地址
    case MB_HOLD_SET_BAUD:            //设置波特率
    case MB_HOLD_TIME_RESET_PASSWORD: //时间复位密码
        Dev_ReadRegHold(p8Data, 2, p8Data[3]);
        Dev_ReadRegHold(p8Data, 3, p8Data[3] + 1);
        break;
    case MB_HOLD_DEVICE_RESET_TIMES: //设备运行时间复位次数
    case MB_HOLD_CO2_RESET_TIMES:    //CO2运行时间复位次数
    case MB_HOLD_CH2O_RESET_TIMES:   //甲醛运行时间复位次数
    case MB_HOLD_PMSA03_RESET_TIMES: //PM2.5运行时间复位次数
    case MB_HOLD_CH2O_FACTORY_TIME:    //甲醛出厂时间
        Dev_ReadRegHold(p8Data, 2, p8Data[3]);
        Dev_ReadRegHold(p8Data, 3, p8Data[3] + 1);
        break;
    case MB_HOLD_CH2O_INSTALL_TIME:   //甲醛安装时间
    case MB_HOLD_485MB_ADD:           //485地址设置
    case MB_HOLD_485MB_BAUD:          //485波特率设置
    case MB_HOLD_485MB_STOPS:         //485停止位设置
    case MB_HOLD_485MB_PARITY:        //485奇偶校验位设置
        Dev_ReadRegHold(p8Data,3,p8Data[3]);
        break;

    case MB_HOLD_TEMPERATURE_CALIB:           //温度校准
    case MB_HOLD_HUMIDITY_CALIB:              //湿度校准
    case MB_HOLD_CO2_CALIB:                   //CO2校准
    case MB_HOLD_PM1_CALIB:                   //PM1.0校准
    case MB_HOLD_PM25_CALIB:                  //PM2.5校准
    case MB_HOLD_PM10_CALIB:                  //PM10校准
    case MB_HOLD_CH2O_CALIB:                  //CH2O(甲醛) 校准
        Dev_ReadRegHold(p8Data, 3, p8Data[3]);
        break;
            
    case  MB_HOLD_LED_SWITCH            :     //LED指示关闭
    case MB_HOLD_ENOCEAN_REAPTER:             //Enocean Reapter
    case MB_HOLD_AIRBOX_RESET_FACTORY_SETTINGS: //AirBox恢复出厂设置
    case VOID_RWPARAM_RESET_FACTORY_SETTINGS: //传感器恢复出厂设置
    case MB_HOLD_SENSOR_REFRESH:              //传感器刷新

    default:
        return Dev_ReadRegHold(p8Data, 3, p8Data[3]);
        break;
        //return !OK;
    }
    return OK;
}

/* End of file */
