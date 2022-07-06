

/*!
*****************************************************************
                        $Name$
                        $Revision: 27601 $
                        $Date: 2015-03-02 16:20:57 +0200 (Fr, 18 Jun 2010) $
    \file               Enocean_ESP.c
    \brief              MSG management related functions
    \author             zhoujinbang

    <b>Company:</b>\n   menred automation\n
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
#include "BSP.h"

#include "Dataconfigure.h"

#include "main.h"
#include "EnOceanCascade.h"
#include "EnOceanMSCCascade.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanDebug(void);

/*============================ IMPLEMENTATION ================================*/
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanLearnSend(void)
{
    if ((0x02 == Dev.u8State) || (0x03 == Dev.u8State))
    {
        if (0 == Dev.u8LearnAutoSendEEPTime)
        {
            /* 30*0.1s = 3s send the learn telegram */
            Dev.u8LearnAutoSendEEPTime = 30;
            Dev.u8State = 0;
            
            //Dev.u8LearnChannel
            EnOceanDevSendEEPInfo2GateWay(&Radio, AIRBOX_1_EEP, 0);
            EnOceanUTERadioData(&Radio, 0);
        }
    }

    if (!Dev.u8LearnSuccessTime)
    {
        Dev.u8LearnState = 0;
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanManualLearn(Radio_Typedef *pRadio)
{
    uint8_t u8LearnState;

    if ((0x02 == Dev.u8State) || (0x03 == Dev.u8State))
    {
        if ((eLEARN_STATUS_ADD_SUCCESS == Dev.u8LearnState) || (eLEARN_STATUS_DEL_SUCCESS == Dev.u8LearnState))
        {
            return;
        }

        u8LearnState = EnOceanLearnSensor(pRadio, Dev.u8LearnChannel, Dev.u8LearnMode);
        if ((eLEARN_STATUS_ADD_SUCCESS == u8LearnState) || (eLEARN_STATUS_DEL_SUCCESS == u8LearnState))
        {
            Dev.u8LearnState = u8LearnState;
            Dev.u8LearnSuccessTime = 50;
        }
    }
}
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanLearnSensor(Radio_Typedef *pRadio, uint8_t u8LearnChannel, uint8_t u8LearnOutMode)
{
    ID_SEARCH_TYPE Search;
    ID_LEARN_INFO LearnInfo;

    //eENOCEAN_LEARN_STATUS_TYPE eReturnState;

    uint32_t u32EnOceanChipID;

    EnOceanGetHWChipID(&u32EnOceanChipID);

    Search.u8Start = 0;

    LearnInfo.u8Channel = u8LearnChannel;
    LearnInfo.u8Cmd = 0;
    LearnInfo.u8Enable = LRN_SERACH;
    LearnInfo.u8Type = LRN_MANUAL;
    LearnInfo.u8OutMode = u8LearnOutMode;

    if (RADIO_CHOICE_RPS == pRadio->Telegram.raw.u8RORG)
    {
        if (OK != EnOceanGetSearchLearnDataByRPSLeft(pRadio, &Search, &LearnInfo))
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else if (RADIO_CHOICE_4BS == pRadio->Telegram.raw.u8RORG)
    {
        if (OK != EnOceanGetSearchLearnDataBy4BS(pRadio, &Search, &LearnInfo))
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else if (RADIO_CHOICE_1BS == pRadio->Telegram.raw.u8RORG)
    {
        if (OK != EnOceanGetSearchLearnDataBy1BS(pRadio, &Search, &LearnInfo))
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else if (RADIO_CHOICE_UTE == pRadio->Telegram.raw.u8RORG)
    {
        if (pRadio->Param.p_rx.u32DestinationId != u32EnOceanChipID)
        {
            return eLEARN_STATUS_IDLE;
        }

        if (OK != EnOceanGetSearchDataByUTEOrVLDTelRadio(pRadio, &Search, &LearnInfo))
        {
            return eLEARN_STATUS_IDLE;
        }
    }
    else
    {
        return eLEARN_STATUS_IDLE;
    }

    return EnOceanManualLearnDev2Tab(&Search);
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanRadioMapChannel(uint8_t u8MapChannel, uint8_t *pu8IOChannel, uint8_t u8CascadeAdd)
{
    uint8_t u8Channel;

    u8Channel = u8MapChannel;

    if (0 == u8Channel)
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
uint8_t EnOceanRadioMSC(Radio_Typedef *pRadio)
{

    uint16_t u16ManID;
    uint8_t u8BaseOffsetID;
    uint32_t u32EnOceanBaseID;
    uint32_t u32EnOceanChipID;

    uint8_t u8Cmd;
    //uint8_t u8BuffChannel;
    //uint8_t u8MSCChannel;

    u8Cmd = pRadio->Telegram.raw.bytes[1] & 0x0F;
    //u8MSCChannel = pRadio->Telegram.raw.bytes[2];

    u16ManID = ((uint16_t)pRadio->Telegram.raw.bytes[0] << 4) | ((uint16_t)(pRadio->Telegram.raw.bytes[1] & 0xF0) >> 4);
    if (ENOCEAN_MENRED_MAN_ID != u16ManID)
    {
        return !OK;
    }

    EnOceanGetHWBaseID(&u32EnOceanBaseID);
    EnOceanGetHWChipID(&u32EnOceanChipID);

    if (pRadio->Param.p_rx.u32DestinationId == u32EnOceanChipID)
    {
        //EnOceanRadioMapChannel(u8MSCChannel,&u8BuffChannel,Dev.Cfg.u8CascadePhyAdd);
        if (eMSC_CMD_WRITE == u8Cmd)
        {
            if (OK == EnOceanMSCWriteSettings(pRadio))
            {
                /* Only save profile parameter */
                return OK;
            }
        }
        else if (eMSC_CMD_READ == u8Cmd)
        {
            return OK;
        }
    }
    else if ((pRadio->Param.p_rx.u32DestinationId & 0xFFFFFF00) == (u32EnOceanBaseID & 0xFFFFFF00))
    {
        u8BaseOffsetID = pRadio->Param.p_rx.u32DestinationId - u32EnOceanBaseID;
        //EnOceanRadioMapChannel(u8MSCChannel,&u8BuffChannel,Dev.Cfg.u8CascadePhyAdd);

        if (eMSC_CMD_WRITE == u8Cmd)
        {
            if (OK == EnOceanMSCMasterWriteSettingsByBaseID(pRadio, u8BaseOffsetID))
            {
                /* Only save profile parameter */
                return OK;
            }
        }
        else if (eMSC_CMD_READ == u8Cmd)
        {
            return OK;
        }
    }
    else
    {
        return !OK;
    }

    return !OK;
}

/**
 * @brief
 * @param
 * @retval None
 */
void EnOceanHandler(uint8_t u8SendIntervalPeriodSet)
{
    uint8_t u8Status;

    /* Get and process EnOcean ESP3's data from receive queue  */
    u8Status = EnOceanESP3ReceivePacketParse(&Radio, PACKET_RESERVED);

    if (0 == u8Status)
    {
        //ENOCEAN_HARDWARE_RST_DISABLE();   //
        //EnOceanRun.u8SendPeriod = u8SendIntervalPeriodSet;
    }
    else if (1 == u8Status)
    {
        /* Init must be after the read NVM, Because the remancode and repeater setting save the NVM */
        EnOceanModuleInit();
    }
    else if (2 == u8Status)
    {
        if (Radio.Param.p_tx.u32DestinationId == Dev.Cfg.u32EnOceanChipID)
        {
            if (ENOCEAN_MENRED_MAN_ID >> 4 == Radio.Telegram.raw.bytes[0] && (ENOCEAN_MENRED_MAN_ID & 0x0F) == Radio.Telegram.raw.bytes[1] >> 4)
            {
                if (Radio.Telegram.raw.bytes[1] == 0x11)
                {
                    if (OK == EnOceanMSCWrite(&Radio, &Dev))
                    {
                    }
                }
                else
                {
                    if (OK == EnOceanMSCResponse(&Radio, &Dev))
                    {
                    }
                }
            }
        }
    }
    else if (3 == u8Status)
    {
        if (RM_SUCCESS == EnOceanReman(&Radio))
        {
            EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM, &Radio);
        }
    }

    /* */
    if (OK != EnOceanESP3SendStateProcess())
    {
        EnOcean_HardwareReset();
    }

    if (OK == EnOceanGetSendReady())
    {
        if (OK == EnOcean_GetSendQueuePopID())
        {
            EnOceanPopQueueSendData();

            EnOceanSetSendPeriod(u8SendIntervalPeriodSet);
        }
    }

    EnOceanLearnSend();
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t EnOceanDebug(void)
{
#ifdef HW_DEBUG
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_RPS) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanRPSID))
    {
        Dev.u32EnOceanRPSRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_1BS) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOcean1BSID))
    {
        Dev.u32EnOcean1BSRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_4BS) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOcean4BSID))
    {
        Dev.u32EnOcean4BSRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_VLD) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanVLDID))
    {
        Dev.u32EnOceanVLDRxCount++;
    }
    if ((Radio.Telegram.raw.u8RORG == RADIO_CHOICE_MSC) && (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanMSCID))
    {
        Dev.u32EnOceanMSCRxCount++;
    }
    if (Radio.Param.p_rx.u32SourceId == Dev.u32EnOceanRxID)
    {
        Dev.u32EnOceanRxCount++;
    }
#endif

    //return EnOceanLight(&Radio);
    return OK;
}

//!用户定义的远程功能
const uint16_t u16gRpc[] =
    {
        RM_FN_UNLOCK, //!<Unlock command.
        RM_DEFAULTMANID,
        RM_FN_LOCK, //!<Lock command.
        RM_DEFAULTMANID,
        RM_FN_SET_CODE, //!<Set security command.
        RM_DEFAULTMANID,
        RM_FN_QUERY_ID, //!<Query ID command.
        RM_DEFAULTMANID,
        RM_FN_ACTION_COMMAND, //!<Test command.
        RM_DEFAULTMANID,
        RM_FN_PING_COMMAND, //!<Ping command.
        RM_DEFAULTMANID,
        RM_FN_QUERY_FUNCTION_COMMAND, //!<Query supported RPC functions command.
        RM_DEFAULTMANID,
        RM_FN_QUERY_STATUS, //!<Query debug status of remote manager.

        RM_DEFAULTMANID,
        /*
    RM_RPC_RESET_ALL          , // 0 0x300
    ENOCEAN_MENRED_MAN_ID     , // 1
    RM_RPC_READ_IDS           , // 6 0x303
    ENOCEAN_MENRED_MAN_ID     , // 7
    RM_RPC_CLEAR_IDS          , // 8 0x304
    ENOCEAN_MENRED_MAN_ID     , // 9
    RM_RPC_ADD_ONE            , // 10 0x305
    ENOCEAN_MENRED_MAN_ID     , // 11
    RM_RPC_DEL_ONE            , // 12 0x306
    ENOCEAN_MENRED_MAN_ID     , // 13
    RM_RPC_READ_ONE           , // 14 0x307        
    ENOCEAN_MENRED_MAN_ID     , // 15
    RM_RPC_READ_ONE_BY_ONE    , // 16 0x308
    ENOCEAN_MENRED_MAN_ID     , // 17
    */
        RM_RPC_TEST_CHANNEL,   // 18 0x309
        ENOCEAN_MENRED_MAN_ID, // 19
        RM_RPC_READ_BASEID,
        ENOCEAN_MENRED_MAN_ID, // 19
        RM_RPC_WRITE_BASEID,
        ENOCEAN_MENRED_MAN_ID, // 19
        /*
    RM_RPC_READ_CLOVER_PAGE_CFG               ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_WRITE_CLOVER_PAGE_CFG              ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_READ_CLOVER_PAGE_ROCK_BUTTON_CFG   ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_BUTTON_CFG  ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_READ_CLOVER_PAGE_ROCK_TITLE_CFG    ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_TITLE_CFG   ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_READ_CLOVER_TYPE                   ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_READ_CLOVER_PAGE_ROCK_MODE_CFG     ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_MODE_CFG    ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_READ_CLOVER_PAGE_CHANNEL_MASK_CFG  ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_WRITE_CLOVER_PAGE_CHANNEL_MASK_CFG ,
    ENOCEAN_MENRED_MAN_ID,
    
    RM_RPC_READ_CLOVER_PAGE_DALI_CHANNEL_CFG  ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_ADD_CLOVER_PAGE_DALI_CHANNEL_CFG   ,
    ENOCEAN_MENRED_MAN_ID,
    RM_RPC_DEL_CLOVER_PAGE_DALI_CHANNEL_CFG   ,
    ENOCEAN_MENRED_MAN_ID,
    */
        RM_RPC_QUERY_ALL_BASEID_DEV_ADVANCED,
        ENOCEAN_MENRED_MAN_ID,
        RM_RPC_ADD_LEARN_ADVANCED,
        ENOCEAN_MENRED_MAN_ID,
        RM_RPC_DEL_LEARN_ADVANCED,
        ENOCEAN_MENRED_MAN_ID,
        RM_RPC_READ_LEARN_CHANNEL_INFO,
        ENOCEAN_MENRED_MAN_ID,
        RM_RPC_READ_GATEWAY_LEARN_IDS,
        ENOCEAN_MENRED_MAN_ID,
        RM_RPC_CLEAR_GATEWAY_LEARN_IDS,
        ENOCEAN_MENRED_MAN_ID,
};
/**
 * @brief  远程管理命令处理函数
 * @param
 * @retval None 
 */
RM_RETURN_TYPE EnOceanReman(Radio_Typedef *pRadio)
{
    //uint8_t i;
    //uint8_t u8Channel;
    //uint8_t u8BuffChannel;
    uint8_t u8ChannelMax;
    uint16_t u16RemanFN;
    uint8_t u8Mask;
    //uint8_t u8PhyAdd;
    uint32_t u32EnOceanBaseID;

    EnOceanGetHWBaseID(&u32EnOceanBaseID);
    EnOceanSetDstID(pRadio->Param.ReMan.u32SourceId);
    u16RemanFN = pRadio->Telegram.ReMan.u16FnNum;
    u8ChannelMax = 0; //LIGHT_CHANNEL_NUMS;//EEPD201XX_GetChannelNumMax();
    //pRadio->u8ResponseState = 0;
    /* Ping need not remotemangement password */
    if (RM_FN_PING_COMMAND == u16RemanFN) // PING
    {
        EnOceanReManPingCommand(AIRBOX_1_EEP, pRadio);
        return RM_SUCCESS;
    }
    /* Must unlock the devices, can use more function */
    if (RM_SUCCESS != EnOceanReManSecurityProcess(pRadio)) //
    {
        return RM_NO_SUCCESS;
    }

    if (RM_FN_QUERY_ID == u16RemanFN)
    {
        return EnOceanReManGateWayResponseQueryID(AIRBOX_1_EEP, pRadio);
    }

    if (EnOceanReManCheckDestID(&pRadio->Param) == RM_NO_SUCCESS)
    {
        return RM_COMMAND_FLASH_READ_NO_SUCCESS;
    }

    // Depending on the remote telegram command received a certain action is performed
    switch (u16RemanFN)
    {
    // Perform a visual signalisation on the I/O pins.
    // query infomation
    case RM_FN_QUERY_FUNCTION_COMMAND:
    {
        u8Mask = sizeof(u16gRpc) / sizeof(u16gRpc[0]);
        return EnOceanReManQueryFunctionCommand(pRadio, u16gRpc, u8Mask);
    }
    case RM_FN_QUERY_STATUS:
    {
        return EnOceanReManQueryStatus(pRadio);
    }
    case RM_FN_ACTION_COMMAND:
    {
        ReportedData.u8PMSTestFlag = 1;

        if (RM_SUCCESS == EnOceanReManActive(pRadio, u8ChannelMax))
        {
            return RM_SUCCESS;
        }
        return RM_NO_SUCCESS;
    }
    // rpc command for menred products
    case RM_RPC_RESET_ALL: //0->0x300
    {
        ReportedData.u8PMSTestFlag = 1;

        if (RM_SUCCESS == EnOceanReManResetDevAll(pRadio))
        {
            ResetDefaultData();
            ResetDefaultEnable();
            return RM_SUCCESS;
        }
        break;
    }

    case RM_RPC_TEST_CHANNEL: //9->0x309

        ReportedData.u8PMSTestFlag = 1;

        //u8Channel = pRadio->Telegram.ReMan.u8Data[0];
        return RM_NO_SUCCESS;

    case RM_RPC_READ_BASEID:  //0x30A
    case RM_RPC_WRITE_BASEID: //0x30B
        return EnOceanReManResponseQueryBaseID(pRadio);

    case RM_RPC_QUERY_ALL_BASEID_DEV_ADVANCED: //0x322

        break;

    case RM_RPC_ADD_LEARN_ADVANCED: //0x330
        //u8Channel = pRadio->Telegram.ReMan.u8Data[7];
        return RM_NO_SUCCESS;

    case RM_RPC_DEL_LEARN_ADVANCED: //0x331
        //u8Channel = pRadio->Telegram.ReMan.u8Data[7];

        return RM_NO_SUCCESS;
        // Here it could be received a remote telegram that TCM300 does not decode. Do nothing.
    default:
        return RM_NO_SUCCESS;
    }

    return RM_NO_SUCCESS;
}

/* End of file */