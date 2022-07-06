

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
#include "EnOceanFun.h"
#include "LedAndButton.h"

//#include "HWTest.h"
#include "RS485Cascade.h"
#include "RS485Modbus.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/*============================ IMPLEMENTATION ================================*/


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/



    /**
     * @brief
     * @param
     * @retval None
     */
    void EnOceanHandler(uint8_t u8SendIntervalPeriodSet)
    {
        uint8_t u8Status;

        /* Get and process EnOcean ESP3's data from receive queue  */
        u8Status = EnOceanESP3ReceivePacketParse(&Radio,PACKET_RESERVED);
        
        if (0 == u8Status)
        {                

        }
        else if (1 == u8Status)
        {        
            /* Init must be after the read NVM, Because the remancode and repeater setting save the NVM */
            EnOceanModuleInit();
        }
        else if (3 == u8Status)
        {
            if ( RM_SUCCESS == EnOceanReman(&Radio) )
            {
                u16EnOceanSendLastWaitTime = 3000;
                EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM,&Radio);
            }            
        }

        /* */
        if ( OK != EnOceanESP3SendStateProcess() )
        {
            EnOcean_HardwareReset();
        }

        EnOcean_GetSendQueuePopID(u8SendIntervalPeriodSet);
    }
    /**
     * @brief  远程管理命令处理函数
     * @param
     * @retval None 
     */
    RM_RETURN_TYPE EnOceanReman(Radio_Typedef *pRadio)
    {
        uint16_t u16RemanFN;
        uint32_t u32EnOceanBaseID;

        EnOceanGetHWBaseID ( &u32EnOceanBaseID );
        EnOceanSetDstID ( pRadio->Param.ReMan.u32SourceId );
        u16RemanFN              = pRadio->Telegram.ReMan.u16FnNum;

        /* Ping need not remotemangement password */
        if (RM_FN_PING_COMMAND == u16RemanFN) // PING 
        {
            EnOceanReManPingCommand(RPL4X_EEP, pRadio);
            return RM_SUCCESS;
        }
        /* Must unlock the devices, can use more function */
        /*
        if ( RM_SUCCESS != EnOceanReManSecurityProcess(pRadio) ) //
        {
            return RM_NO_SUCCESS;
        }
        */
        if (EnOceanReManCheckDestID(&pRadio->Param) == RM_NO_SUCCESS)
        {
            return RM_COMMAND_FLASH_READ_NO_SUCCESS;
        }
        if ( RM_RPC_UPGRADE_LONG_DATAS == u16RemanFN )
        {
            return EnOceanRemanUpgradeLongDatas(pRadio);
        }
        
        
        return RM_NO_SUCCESS;
    }

/**
 * @brief
 * @param
 * @retval
 */
RM_RETURN_TYPE EnOceanRemanUpgradeLongDatas(Radio_Typedef *pRadio)
{
    uint8_t  u8Cmd;

    //uint16_t u16Nums;
    uint16_t u16Length;

    uint8_t *p8ReceiveBuff;
    uint8_t *pu8SendBuff;

    p8ReceiveBuff = pRadio->Telegram.ReMan.u8Data;
    pu8SendBuff   = pRadio->Telegram.ReMan.u8Data;
    
    u8Cmd    = p8ReceiveBuff[1];
    //u16Nums  = p8ReceiveBuff[10] + 13;
    if ( MB_FUNC_READWRITE_MULTIPLE_REGISTERS == u8Cmd )
    {        
        if ( OK == UpgradeModbusReceiveReply(p8ReceiveBuff,pu8SendBuff,&u16Length) )
        {
            pRadio->Telegram.ReMan.u8Length           = u16Length;
            pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
            pRadio->Param.ReMan.u32SourceId           = EnOceanRun.u32ChipID;
            pRadio->Param.ReMan.u32DestinationId      = EnOceanRun.u32DstID;
            pRadio->Telegram.ReMan.u16FnNum           = RM_RPC_UPGRADE_LONG_DATAS_ANS;
            pRadio->Telegram.ReMan.u16ManId           = ENOCEAN_MENRED_MAN_ID;
            return RM_SUCCESS;
        }        
    }

    return RM_NO_SUCCESS;
}
/**
 * @brief
 * @param
 * @retval
 */
void EnOceanRemanResetReply(uint8_t *p8ReceiveBuff,Radio_Typedef *pRadio,uint32_t u32DstID)
{
    uint16_t i;
    //uint16_t u16Nums;
    
    

    for (i = 0; i < 9;i++)
    {
        pRadio->Telegram.ReMan.u8Data[i] = p8ReceiveBuff[i];
    }
    
    pRadio->Telegram.ReMan.u16FnNum           = RM_RPC_UPGRADE_LONG_DATAS_ANS;
    pRadio->Telegram.ReMan.u16ManId           = ENOCEAN_MENRED_MAN_ID;
    pRadio->Telegram.ReMan.u8Length           = 9;
    pRadio->Param.ReMan.u32DestinationId      = u32DstID;//EnOceanRun.u32DstID;
    pRadio->Param.ReMan.u32SourceId           = EnOceanRun.u32ChipID;
    pRadio->Param.ReMan.u8RandSendDelayEnable = REMAN_RANDOM_DISABLE;
    pRadio->u8PacketType                      = PACKET_REMOTE_MAN_COMMAND;
    EnOcean_PushData2Queue(eQUEUE_REMAN_TELEGRAM,pRadio);
}
/* End of file */