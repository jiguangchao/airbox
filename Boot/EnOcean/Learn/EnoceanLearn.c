/*!
*****************************************************************
						$Name$
						$Revision: 27601 $
						$Date: 2010-06-18 16:20:57 +0200 (Fr, 18 Jun 2010) $
	\file 				id_mod.c
	\brief 				ID management related functions
	\author 			EnOcean

	<b>Processor:</b>\n	EO3000I\n\n
    <b>Company:</b>\n	menred automation\n
1、修改记录 
   修改函数 EnOceanGetSearchLearnDataByRPSLeft，学习时一个按键有效，数据时两个按键都有效
   增加函数 EnOceanGetSearchLearnDataByRPSLeft 用于检测低位按键
****************************************************************
*/

/*============================ INCLUDES ======================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "esp3_radio.h"
#include "EnOceanLearn.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
const uint32_t u32LearnSupportEEP[] = 
{
    EEP_SMART_HIVE ,
    EEP_F60201     ,
    EEP_A50701     ,
    EEP_A50702     ,
    EEP_A50703     ,
    EEP_A50801     ,
    EEP_A50802     ,
    EEP_A50803     ,
                   
    EEP_D50001     ,
    EEP_A50905     ,
    EEP_A50907     ,
    EEP_A50910     ,
    EEP_D10104     ,
    EEP_D10105     ,
    EEP_D10106     ,
    EEP_D10107     ,
    EEP_D10108     ,
    EEP_D10109     ,
    EEP_D1010A     ,                   
                  
    EEP_D20101     ,
    EEP_D20113     ,
    EEP_D20115     ,
    EEP_D20116     ,

};


ID_TABLE_TYPE               LearnInfoTab ;
/**
  * @brief
  * @param
  * @retval None
  */
uint32_t EnOceanDevSendEEPInfoGetPhyID(uint32_t u32EEP,uint8_t u8BaseID)
{
    if ( u32EEP == CLOVER_GATEWAY_EEP)
    {
        return EnOceanRun.u32ChipID;
    }
    else if ( u32EEP == LEARN_LIGHT_EEP)
    {
        return EnOceanRun.u32BaseID;
    }
    else if ( u32EEP == LEARN_ROOM_EEP )
    {        
        return EnOceanRun.u32BaseID + u8BaseID;
    }
    else if ( u32EEP == LEARN_AIR_CONDITION_EEP )
    {        
        return EnOceanRun.u32BaseID + u8BaseID;
    }
    else if ( u32EEP == LEARN_FLOOR_HEATING_EEP )
    {        
        return EnOceanRun.u32BaseID + u8BaseID;
    }
    else if ( u32EEP == LEARN_VENTILATION_EEP )
    {        
        return EnOceanRun.u32BaseID + u8BaseID;
    }
    else if ( u32EEP == CLOVER_RELAY_EEP )
    {
        return EnOceanRun.u32BaseID;
    }
    
    return EnOceanRun.u32ChipID;
}
/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanDevSendEEPInfo2GateWay(Radio_Typedef *pRadio,uint32_t u32EEP,uint8_t u8ChannelID)
{         
    pRadio->Param.p_tx.u32DestinationId = 0xFFFFFFFF;
    
    pRadio->Telegram.raw.bytes[0] = 0xA0; //DB6
    pRadio->Telegram.raw.bytes[1] = u8ChannelID; //DB5
    pRadio->Telegram.raw.bytes[2] = 0x51;//DB4
    pRadio->Telegram.raw.bytes[3] = 0x00;//DB3

    pRadio->Telegram.raw.bytes[4] = (u32EEP    )&0xFF;//DB2
    pRadio->Telegram.raw.bytes[5] = (u32EEP>>8 )&0xFF;//DB1
    pRadio->Telegram.raw.bytes[6] = (u32EEP>>16)&0xFF;//DB0
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSearchLearnDataByRPSRight(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn)
{
    // Channel to search information
    pSearchIn->u8Start                              = 0;
    pSearchIn->u8ChannelCheck                       = pIDLearn->u8Enable;

    pSearchIn->entry.LrnDev.u16Data                = 0;
    pSearchIn->entry.LrnDev.RPS.u1LrnType          = pIDLearn->u8Type;
    pSearchIn->entry.LrnDev.RPS.u5Channel          = pIDLearn->u8Channel;
    pSearchIn->entry.LrnDev.RPS.u3OutMode          = 0;
    pSearchIn->entry.u8EepRorg                     = pRadio->Telegram.raw.u8RORG;

    if ( (pRadio->Telegram.raw.u8Status&0x30) != 0x30)
    {
        return !OK;
    }

    if ( RADIO_CHOICE_RPS != pSearchIn->entry.u8EepRorg )
    {
        return !OK;
    }

    if ( pIDLearn->u8Enable == LRN_SERACH )
    {
        if ( pRadio->Telegram.raw.bytes[0]&0x07 )
        {
            return !OK;
        }
        pSearchIn->entry.u8EepFun  = PTM2XX_FUN;
        pSearchIn->entry.u8EepType = PTM2XX_TYPE;
        
        pSearchIn->entry.u32SrcId                     = pRadio->Param.p_rx.u32SourceId;
        pSearchIn->entry.LrnDev.RPS.u3Key             = (pRadio->Telegram.raw.bytes[0]>>4)&0x07;    
        return OK;
    }
    else if ( pIDLearn->u8Enable == RADIO_SERACH )
    {   
        if ( (pRadio->Telegram.raw.bytes[0]&0x07) == 0x00 )
        {
            return !OK;
        }
                    
        pSearchIn->entry.u8EepFun  = PTM2XX_FUN;
        pSearchIn->entry.u8EepType = PTM2XX_TYPE;
        
        pSearchIn->entry.u32SrcId                      = pRadio->Param.p_rx.u32SourceId;
        
        switch ( pRadio->Telegram.raw.bytes[0] & 0x07 )
        {
        case 0x01:
        case 0x03:
        case 0x05:
        case 0x07:
            pSearchIn->entry.LrnDev.RPS.u3Key          = pRadio->Telegram.raw.bytes[0] & 0x07; 
            pSearchIn->entry.LrnDev.RPS.u2KeyState     = eRPS_ROCK_DOWN;
            break;
        case 0x00:    
        case 0x02:                    
        case 0x04:            
        case 0x06:
            pSearchIn->entry.LrnDev.RPS.u3Key          = pRadio->Telegram.raw.bytes[0] & 0x07; 
            pSearchIn->entry.LrnDev.RPS.u3Key         += 1;
            pSearchIn->entry.LrnDev.RPS.u2KeyState     = eRPS_ROCK_RELEASE;
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
uint8_t EnOceanGetSearchLearnDataByRPSLeft(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn)
{
    // Channel to search information
    uint8_t u8Data;
    pSearchIn->u8Start 	                           = 0;
    pSearchIn->u8ChannelCheck                      = pIDLearn->u8Enable;

    pSearchIn->entry.LrnDev.u16Data                = 0;
    pSearchIn->entry.LrnDev.RPS.u1LrnType          = pIDLearn->u8Type;
    pSearchIn->entry.LrnDev.RPS.u5Channel          = pIDLearn->u8Channel;
    pSearchIn->entry.LrnDev.RPS.u3OutMode          = pIDLearn->u8OutMode;
    pSearchIn->entry.LrnDev.RPS.u3Cmd              = pIDLearn->u8Cmd;
    pSearchIn->entry.LrnDev.RPS.u2KeyState         = eRPS_ROCK_IDLE;
    pSearchIn->entry.u8EepRorg                     = pRadio->Telegram.raw.u8RORG;

    if ( (pRadio->Telegram.raw.u8Status&0x30) != 0x30)
    {
        return !OK;
    }

    if ( RADIO_CHOICE_RPS != pSearchIn->entry.u8EepRorg )
    {
        return !OK;
    }
                  
    if ( pIDLearn->u8Enable == LRN_SERACH )
    {
        if ( pRadio->Telegram.raw.bytes[0]&0x07 )
        {
            return !OK;
        }
        u8Data = (pRadio->Telegram.raw.bytes[0]>>4) & 0x07;
        switch ( u8Data )
        {
        case 0x01:
        case 0x03:
        case 0x05:
        case 0x07:            
            break;
        default:
            return !OK;
            break;
        }
        pSearchIn->entry.u8EepFun  = PTM2XX_FUN;
        pSearchIn->entry.u8EepType = PTM2XX_TYPE; 
        
        pSearchIn->entry.u32SrcId               = pRadio->Param.p_rx.u32SourceId;
        pSearchIn->entry.LrnDev.RPS.u3Key       = u8Data;    
        return OK;
    }
    else if ( pIDLearn->u8Enable == RADIO_SERACH )
    {
        pSearchIn->entry.u8EepFun  = PTM2XX_FUN;
        pSearchIn->entry.u8EepType = PTM2XX_TYPE;
        
        pSearchIn->entry.u32SrcId     = pRadio->Param.p_rx.u32SourceId;
        u8Data = (pRadio->Telegram.raw.bytes[0]>>4) & 0x07;
        switch ( u8Data )
        {
        case 0x01:
        case 0x03:
        case 0x05:
        case 0x07:
            pSearchIn->entry.LrnDev.RPS.u3Key          = u8Data; 
            pSearchIn->entry.LrnDev.RPS.u2KeyState     = eRPS_ROCK_DOWN;
            break;
        case 0x00:
        case 0x02:                            
        case 0x04:            
        case 0x06:
            pSearchIn->entry.LrnDev.RPS.u3Key          = u8Data+1; 
            pSearchIn->entry.LrnDev.RPS.u2KeyState     = eRPS_ROCK_RELEASE;
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
uint8_t EnOceanGetSearchLearnDataBy1BS(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn)
{
    // Channel to search information
    pSearchIn->u8Start 	                           = 0;
    pSearchIn->u8ChannelCheck                      = pIDLearn->u8Enable;

    pSearchIn->entry.LrnDev.u16Data                = 0;
    pSearchIn->entry.LrnDev.IDR.u1LrnType          = pIDLearn->u8Type;
    pSearchIn->entry.LrnDev.IDR.u5Channel          = pIDLearn->u8Channel;
    pSearchIn->entry.LrnDev.IDR.u3OutMode          = pIDLearn->u8OutMode;
    pSearchIn->entry.LrnDev.IDR.u3Cmd              = pIDLearn->u8Cmd;
    pSearchIn->entry.u8EepRorg                     = pRadio->Telegram.raw.u8RORG;

    pSearchIn->entry.u32SrcId                      = pRadio->Param.p_rx.u32SourceId ;//pRadioTel->raw.u32Id;
    if ( ( (pRadio->Telegram.raw.bytes[0]&0x08) == 0x00 )&&(pIDLearn->u8Enable == LRN_SERACH) )
    {
        pSearchIn->entry.u8EepFun  = 0x00;
        pSearchIn->entry.u8EepType = 0x01;
        return OK;
    }
    if ( ( (pRadio->Telegram.raw.bytes[0]&0x08) == 0x08 )&&(pIDLearn->u8Enable == RADIO_SERACH) )
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
uint8_t EnOceanGetSearchLearnDataBy4BS(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn)
{
    // Channel to search information
    pSearchIn->u8Start 	                               = 0;
    pSearchIn->u8ChannelCheck                          = pIDLearn->u8Enable;

    pSearchIn->entry.LrnDev.u16Data                    = 0;
    pSearchIn->entry.LrnDev.PIR.u1LrnType              = pIDLearn->u8Type;
    pSearchIn->entry.LrnDev.PIR.u5Channel              = pIDLearn->u8Channel;
    pSearchIn->entry.LrnDev.PIR.u3OutMode              = pIDLearn->u8OutMode;
    pSearchIn->entry.LrnDev.PIR.u3Cmd                  = pIDLearn->u8Cmd;
    pSearchIn->entry.u8EepRorg                         = pRadio->Telegram.raw.u8RORG;


    pSearchIn->entry.u32SrcId                              = pRadio->Param.p_rx.u32SourceId ;//pRadioTel->raw.u32Id;

    if ( ( ( pRadio->Telegram.raw.bytes[3]&0x08 ) == 0x00 )&&(pIDLearn->u8Enable == LRN_SERACH) )
    {
        pSearchIn->entry.u8EepFun                       = (pRadio->Telegram.raw.bytes[0]&0xFC)>>2;
        pSearchIn->entry.u8EepType                      = (pRadio->Telegram.raw.bytes[0]&0x03)<<5;
        pSearchIn->entry.u8EepType                     |= (pRadio->Telegram.raw.bytes[1]&0xF8)>>3;
        // A5 07 01
        if ( ( 0x07 == pSearchIn->entry.u8EepFun )&&(0x01 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
        // A5 07 03
        else if ( ( 0x07 == pSearchIn->entry.u8EepFun )&&(0x02 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
        // A5 07 03
        else if ( ( 0x07 == pSearchIn->entry.u8EepFun )&&(0x03 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
        
        else if ( ( 0x08 == pSearchIn->entry.u8EepFun )&&(0x01 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
        // A5 07 03
        else if ( ( 0x08 == pSearchIn->entry.u8EepFun )&&(0x02 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
        // A5 07 03
        else if ( ( 0x08 == pSearchIn->entry.u8EepFun )&&(0x03 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
    #if 0
        // A5 09 04 CO2 T RH
        else if ( ( 0x09 == pSearchIn->entry.u8EepFun )&&(0x04 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
        // A5 09 05 C2HO
        else if ( ( 0x09 == pSearchIn->entry.u8EepFun )&&(0x05 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
        // A5 09 07 PM2.5 
        else if ( ( 0x09 == pSearchIn->entry.u8EepFun )&&(0x07 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
    #endif
        // A5 09 10 
        else if ( ( 0x09 == pSearchIn->entry.u8EepFun )&&(0x10 == pSearchIn->entry.u8EepType ) )
        {
            return OK;
        }
    }
    else if ( ( ( pRadio->Telegram.raw.bytes[3]&0x08 ) == 0x08 )&&(RADIO_SERACH == pIDLearn->u8Enable) )
    {
        pSearchIn->entry.u32SrcId                      = pRadio->Param.p_rx.u32SourceId ;//pRadioTel->raw.u32Id;
        return OK;
    }


    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSearchDataByUTEOrVLDTelRadio(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn)
{
    // Channel to search information
    uint32_t u32SearchEEP;
    uint32_t u32EEP;

    pSearchIn->u8Start                                 = 0;
    pSearchIn->u8ChannelCheck                           = pIDLearn->u8Enable;

    pSearchIn->entry.LrnDev.u16Data                    = 0;
    pSearchIn->entry.LrnDev.General.u1LrnType          = pIDLearn->u8Type;
    pSearchIn->entry.LrnDev.General.u5Channel          = pIDLearn->u8Channel;
    pSearchIn->entry.LrnDev.General.u3OutMode          = 0;
    pSearchIn->entry.LrnDev.General.u3Cmd              = pIDLearn->u8Cmd;
    pSearchIn->entry.u8EepRorg                         = pRadio->Telegram.raw.u8RORG;
    pSearchIn->entry.u32SrcId                          = pRadio->Param.p_rx.u32SourceId ;//pRadioTel->raw.u32Id;

    if ( LRN_SERACH == pIDLearn->u8Enable )
    {
        if (pRadio->Telegram.raw.u8RORG != RADIO_CHOICE_UTE)
        {
            return !OK;
        }
        u32SearchEEP                            = (uint32_t)pRadio->Telegram.raw.bytes[6]<<16
                                                | (uint32_t)pRadio->Telegram.raw.bytes[5]<<8
                                                | (uint32_t)pRadio->Telegram.raw.bytes[4];
        if ( pRadio->Telegram.raw.bytes[0] == 0x91 )
        {
            
        #if defined LEARN_LIGHT_EEP
            //#pragma message("Must define macro LEARN_LIGHT_EEP for the actutor")
            u32EEP = LEARN_LIGHT_EEP;
            if ( u32SearchEEP == u32EEP )
            {
                pSearchIn->entry.u8EepRorg                      = (LEARN_LIGHT_EEP>>16)&0xFF;
                pSearchIn->entry.u8EepFun                       = (LEARN_LIGHT_EEP>> 8)&0xFF;
                pSearchIn->entry.u8EepType                      = (LEARN_LIGHT_EEP    )&0xFF;
                return OK;
            }
        #else
            #error "Must define: MACRO LEARN_LIGHT_EEP for the actutor"
            #pragma message("Must define MACRO LEARN_LIGHT_EEP ")
        #endif
            
        }
        else //if ( pRadio->Telegram.raw.bytes[0] == 0x20 )
        {
            u32SearchEEP                            = (uint32_t)pRadio->Telegram.raw.bytes[6]<<16
                                                    | (uint32_t)pRadio->Telegram.raw.bytes[5]<<8
                                                    | (uint32_t)pRadio->Telegram.raw.bytes[4];
        #if defined EEP_D10104
            u32EEP = EEP_D10104;
            if ( u32SearchEEP == u32EEP )
            {
                pSearchIn->entry.u8EepRorg                      = (EEP_D10104>>16)&0xFF;
                pSearchIn->entry.u8EepFun                       = (EEP_D10104>> 8)&0xFF;
                pSearchIn->entry.u8EepType                      = (EEP_D10104    )&0xFF;
                return OK;
            }
        #else
            #error "Must define: MACRO AIRBOX_1_EEP for the HVAC"
            #pragma message("Must define MACRO AIRBOX_1_EEP ")
        #endif
        }
    }
    else if ( RADIO_SERACH == pIDLearn->u8Enable )
    {        
        if ( pRadio->Telegram.raw.u8RORG == RADIO_CHOICE_VLD )
        {
            return OK;
        }
        else if (pRadio->Telegram.raw.u8RORG == RADIO_CHOICE_MSC)
        {
            u32SearchEEP = (uint32_t)pSearchIn->entry.u8EepRorg<<16 | (uint32_t)pSearchIn->entry.u8EepFun<<8 | (uint32_t)pSearchIn->entry.u8EepType;
            if ( AIRBOX_1_EEP == u32SearchEEP )
            {
                pSearchIn->entry.u8EepRorg                      = RADIO_CHOICE_VLD;
                return OK;
            }
            else
            {
                return OK;
            }
        }
    }

    return !OK;
}
/**
  * @brief  
  * @param
  * @retval None 
  */
uint8_t EnOceanGetLearnEvent(void)
{
    return LearnInfoTab.u8DataUpdate;
}
/**
  * @brief  
  * @param
  * @retval None 
  */
void EnOceanClearLearnSaveEvent(void)
{
    LearnInfoTab.u8DataUpdate = 0;
}
/**
  * @brief  
  * @param
  * @retval None 
  */
uint8_t EnOceanGetLearnTabNums(void)
{
    return LearnInfoTab.u8nrIDs;
}
/**
  * @brief  
  * @param
  * @retval None 
  */
uint8_t EnOceanGetLearnChannelTabNums(uint8_t u8Channel)
{
    uint8_t u8Nums;
    uint8_t i;
    
    u8Nums = 0;
    for ( i = 0; i < LearnInfoTab.u8nrIDs; i++ )
    {
        if ( u8Channel == LearnInfoTab.entry[i].LrnDev.General.u5Channel )
        {
            u8Nums++;
        }        
    }    
    return u8Nums;
}
/**
  * @brief  
  * @param
  * @retval None 
  */
ID_RETURN_TYPE EnOceanClearLearnTabNums(void)
{
    LearnInfoTab.u8nrIDs = 0;
    return ID_SUCCESS;
}
/**
  * @brief  
  * @param
  * @retval None 
  */
RM_RETURN_TYPE EnOceanSaveLearnTabEvent(void)
{
    LearnInfoTab.u8DataUpdate = 1;
    return RM_SUCCESS;
}
/**
  * @brief 
  * @param
  * @retval None
  */
uint8_t EnOceanSearchDevNumsByEEP(uint32_t u32EEP)
{
    // Nr. of ID table entries stored currently
    uint8_t u8LearnNums;
    uint32_t u32LearnEEP;
    // ID table entry index
    uint8_t u8index;
        
    u8LearnNums = 0;

    // Search through the ID table (IDtable.entry[]) the information entryToSearch
    for (u8index = 0; u8index < LearnInfoTab.u8nrIDs; u8index++)
    {
        u32LearnEEP = (uint32_t)LearnInfoTab.entry[u8index].u8EepRorg << 16 \
                    | (uint32_t)LearnInfoTab.entry[u8index].u8EepFun << 8 \
                    | (uint32_t)LearnInfoTab.entry[u8index].u8EepType;
        // Telegram ID and telegram type must agree
        if (  u32LearnEEP == u32EEP )
        {
            u8LearnNums++;
        }        
    }

    
    return u8LearnNums;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanSearchLearnDevByEEP(ID_SEARCH_TYPE        *pSearchOut,uint32_t u32EEP)
{
    // Nr. of ID table entries stored currently
    uint8_t u8LearnNums;
    uint32_t u32LearnEEP;
    // ID table entry index
    uint8_t u8index;
        
    u8LearnNums = 0;

    // Search through the ID table (IDtable.entry[]) the information entryToSearch
    for (u8index = 0; u8index < LearnInfoTab.u8nrIDs; u8index++)
    {
        u32LearnEEP = (uint32_t)LearnInfoTab.entry[u8index].u8EepRorg << 16 \
                    | (uint32_t)LearnInfoTab.entry[u8index].u8EepFun << 8 \
                    | (uint32_t)LearnInfoTab.entry[u8index].u8EepType;
        // Telegram ID and telegram type must agree
        if (  u32LearnEEP == u32EEP )
        {
            u8LearnNums++;
            //*pu8TabID   = u8index;
            pSearchOut->u8Start = u8index;
            pSearchOut->entry = LearnInfoTab.entry[u8index];
        }        
    }

    return u8LearnNums;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanSearchDevNumsBySrcID(uint32_t u32SrcID)
{
    // Nr. of ID table entries stored currently
    uint8_t u8LearnNums;
    //uint32_t u32LearnSrcID;
    // ID table entry index
    uint8_t u8index;
        
    u8LearnNums = 0;

    // Search through the ID table (IDtable.entry[]) the information entryToSearch
    for (u8index = 0; u8index < LearnInfoTab.u8nrIDs; u8index++)
    {
        // Telegram ID and telegram type must agree
        if (  LearnInfoTab.entry[u8index].u32SrcId == u32SrcID )
        {
            u8LearnNums++;
        }        
    }
    
    return u8LearnNums;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanSearchDevLearnStatusBySrcID(uint32_t u32SrcID)
{
    // ID table entry index
    uint8_t u8index;

    // Search through the ID table (IDtable.entry[]) the information entryToSearch
    for (u8index = 0; u8index < LearnInfoTab.u8nrIDs; u8index++)
    {
        // Telegram ID and telegram type must agree
        if (  LearnInfoTab.entry[u8index].u32SrcId == u32SrcID )
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
// ***************************** ID_SEARCH ***************************************************************
ID_RETURN_TYPE EnOceanSearchLearnTab(ID_SEARCH_TYPE const *pSearchIn,ID_SEARCH_TYPE *pSearchOut )
{
    // Nr. of ID table entries stored currently
    uint8_t u8nrEntries;
    // Information to search in the ID table
    //ID_ENTRY_TYPE   	entryToSearch;
    // 1: A switch telegram is to be searched ; 0: No switch telegram is to be searched
    // bit1                    u1switchIndicator;
    // ID table entry index
    uint8_t u8index;
    uint8_t u8SearchMode;
    // Get the nr. of IDs stored in the table
    u8nrEntries = LearnInfoTab.u8nrIDs;//ID_PTABLE_NR_ENTRIES(pIdTable);

    // Check that the entry to start the search with is not bigger that the last occupied entry
    if (u8nrEntries <= pSearchIn->u8Start)
    {
        return ID_NO_SUCCESS;
    }

    // Search through the ID table (IDtable.entry[]) the information entryToSearch
    for (u8index = pSearchIn->u8Start; u8index < u8nrEntries; u8index++)
    {
        // Telegram ID and telegram type must agree
        if (  (LearnInfoTab.entry[u8index].u8EepRorg != pSearchIn->entry.u8EepRorg)
            ||(LearnInfoTab.entry[u8index].u32SrcId !=  pSearchIn->entry.u32SrcId ) )
        {
            continue;            
        }

        if ( RADIO_CHOICE_VLD != pSearchIn->entry.u8EepRorg )
        {
            if ( LRN_SERACH == pSearchIn->u8ChannelCheck ) // if learn ,need to check channel.but check channel output,not to need
            {
                // The switch channel must be searched AND was correctly found?
                if ( LearnInfoTab.entry[u8index].LrnDev.General.u5Channel != pSearchIn->entry.LrnDev.General.u5Channel )
                {
                    // No search needed OR not found.
                    continue;
                }
            }

            if (RADIO_CHOICE_RPS == pSearchIn->entry.u8EepRorg)
            {
                u8SearchMode = LearnInfoTab.entry[u8index].LrnDev.RPS.u3OutMode;

                if ( MODE_CHANNEL_ONOFF == u8SearchMode )
                {
                    if ( LearnInfoTab.entry[u8index].LrnDev.RPS.u3Key != pSearchIn->entry.LrnDev.RPS.u3Key )
                    {
                        // No search needed OR not found.
                        if ( (( LearnInfoTab.entry[u8index].LrnDev.RPS.u3Key == 0x01)&&(pSearchIn->entry.LrnDev.RPS.u3Key == 0x03 ))||
                             (( LearnInfoTab.entry[u8index].LrnDev.RPS.u3Key == 0x03)&&(pSearchIn->entry.LrnDev.RPS.u3Key == 0x01 ))||
                             (( LearnInfoTab.entry[u8index].LrnDev.RPS.u3Key == 0x05)&&(pSearchIn->entry.LrnDev.RPS.u3Key == 0x07 ))||
                             (( LearnInfoTab.entry[u8index].LrnDev.RPS.u3Key == 0x07)&&(pSearchIn->entry.LrnDev.RPS.u3Key == 0x05 )) )
                        {
                            //continue;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                else
                {
                    if ( LearnInfoTab.entry[u8index].LrnDev.RPS.u3Key != pSearchIn->entry.LrnDev.RPS.u3Key )
                    {
                        continue;
                    }
                }
            }
            
        }

        pSearchOut->u8Start        = u8index;
        pSearchOut->entry          = LearnInfoTab.entry[u8index];

        // Information found! The entry index, where the info was found, is stored in *u8index
        return ID_SUCCESS;

    }

    // No ID entry found with the given search criteria
    return ID_NO_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  */
ID_RETURN_TYPE EnOceanAddEEPInfo2LearnTab(ID_ENTRY_TYPE Entry )
{
    uint8_t u8i;

    u8i = LearnInfoTab.u8nrIDs;//ID_PTABLE_NR_ENTRIES(pIDtable);
    // Space in the ID table for a new entry?
    if(u8i >= ID_MAX_NR_ENTRIES)
    {  	// No more space
        //Restore previous write protection setting

        return ID_MEMORY_FULL;
    }

    //! Telegram ID bytes
    LearnInfoTab.entry[u8i] = Entry;

    // Increment the ID table entry counter
    LearnInfoTab.u8nrIDs++;

    return 	ID_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  */
ID_RETURN_TYPE EnOceanDelChannelLearnInfoFromTab(uint8_t u8Channel)
{
    // Stores the index of the last entry in the ID table
    uint8_t u8lastIndex;
    uint8_t u8index;

    // Useless to delete if no IDs in ID table
    if(LearnInfoTab.u8nrIDs == 0)
    {
        return ID_MEMORY_EMPTY;
    }

    for (u8index = 0; u8index < LearnInfoTab.u8nrIDs; u8index++)
    {
        if ( u8Channel == LearnInfoTab.entry[u8index].LrnDev.General.u5Channel )
        {
            memset(&LearnInfoTab.entry[u8index], 0, sizeof(ID_ENTRY_TYPE)); 
        }     
    }    

    for (u8index = 0; u8index < LearnInfoTab.u8nrIDs; u8index++)
    {
        if ( 0 == LearnInfoTab.entry[u8index].u32SrcId )
        {
            for ( u8lastIndex = LearnInfoTab.u8nrIDs - 1; u8lastIndex >= u8index; u8lastIndex-- )
            {
                if ( 0 != LearnInfoTab.entry[u8lastIndex].u32SrcId )
                {
                    LearnInfoTab.entry[u8index] = LearnInfoTab.entry[u8lastIndex];
                    LearnInfoTab.u8nrIDs--;
                    break;
                }
                else
                {
                    memset(&LearnInfoTab.entry[u8lastIndex], 0, sizeof(ID_ENTRY_TYPE)); 
                    LearnInfoTab.u8nrIDs--;
                    if ( LearnInfoTab.u8nrIDs )
                    {
                        continue;
                    }
                    else
                    {
                        return ID_SUCCESS;
                    }
                }
                
            }
        }
    }
    
    return ID_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  */
ID_RETURN_TYPE EnOceanDelEEPInfoFromLearnTab(uint8_t u8index)
{
    // Stores the index of the last entry in the ID table
    uint8_t  u8lastEntryIndex;

    // Useless to delete if no IDs in ID table
    if(LearnInfoTab.u8nrIDs == 0)
    {
        return ID_MEMORY_EMPTY;
    }

    u8lastEntryIndex = LearnInfoTab.u8nrIDs - 1;

    // The entry index to delete can not be over the index of the last entry, since the ID table is compacted
    if(u8index > u8lastEntryIndex)
    {
        return ID_NO_SUCCESS;
    }
    memset(&LearnInfoTab.entry[u8index], 0, sizeof(ID_ENTRY_TYPE));

    // Compact the ID table, by moving the last entry to the entry to erase.
    // In case that only 1 entry or the last entry is to erase, no move is needed
    LearnInfoTab.entry[u8index] = LearnInfoTab.entry[u8lastEntryIndex];

    // Decrement the nr. of entries in the ID table
    LearnInfoTab.u8nrIDs--;

    return ID_SUCCESS;
}
// ***************************** END ID_DELETE *******************

/**
  * @brief
  * @param
  * @retval None
  */
// ***************************** ID_DELETE_ALL *******************
ID_RETURN_TYPE EnOceanDelLearnTabAll(void)
{
    //Get previous write protection setting

    // Id table contents (ID counter and ID entries) are set to 0
    // memset(LearnInfoTab.u32Words,0,sizeof(ID_TABLE_TYPE)/sizeof(uint32_t) );
    LearnInfoTab.u8nrIDs = 0;
    return ID_SUCCESS;
}
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanManualLearnDev2Tab(ID_SEARCH_TYPE *pSearchIn)
{
    uint8_t u8Status;
    eENOCEAN_LEARN_STATUS_TYPE eLearnStatus;

    ID_RETURN_TYPE  idReturn;               // Return  from id functions
    ID_SEARCH_TYPE  SearchOut;
    
    eLearnStatus = eLEARN_STATUS_IDLE;

    u8Status = EnOceanSearchLearnTab( pSearchIn,&SearchOut) ;

    if ( ID_SUCCESS == u8Status )
    {
        if ( ID_SUCCESS == EnOceanDelEEPInfoFromLearnTab( SearchOut.u8Start) )
        {
            eLearnStatus = eLEARN_STATUS_DEL_SUCCESS;
            EnOceanSaveLearnTabEvent();
        }
        else
        {
            eLearnStatus = eLEARN_STATUS_DEL_FAILURE;
        }
    }
    else if ( ID_NO_SUCCESS == u8Status )
    {

        // Add info to the RAM ID table
        idReturn = EnOceanAddEEPInfo2LearnTab( pSearchIn->entry);

        // ID found place in RAM ID table?
        if (idReturn == ID_SUCCESS)
        {
            eLearnStatus = eLEARN_STATUS_ADD_SUCCESS;
            EnOceanSaveLearnTabEvent();
        }
        // ID did not found place is ID table?
        else if (idReturn == ID_MEMORY_FULL)
        {
            // Leave the learn mode, indicating the exit event
            eLearnStatus = eLEARN_STATUS_ID_TAB_FULL;
        }
    }

    return eLearnStatus;
}
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanManualAddDev2LearnTab(ID_SEARCH_TYPE *pSearchIn)
{
    eENOCEAN_LEARN_STATUS_TYPE eLearnStatus;
    uint8_t u8Status;
    
    ID_RETURN_TYPE  idReturn;               // Return  from id functions
    ID_SEARCH_TYPE  SearchOut;

    eLearnStatus = eLEARN_STATUS_IDLE;
    u8Status = !OK;

    u8Status = EnOceanSearchLearnTab(pSearchIn,&SearchOut) ;

    if ( ID_SUCCESS == u8Status )
    {       
        eLearnStatus = eLEARN_STATUS_ADD_SUCCESS;
    }
    else if ( ID_NO_SUCCESS == u8Status )
    {
        // Add info to the RAM ID table
        idReturn = EnOceanAddEEPInfo2LearnTab(pSearchIn->entry);

        // ID found place in RAM ID table?
        if (idReturn == ID_SUCCESS)
        {
            eLearnStatus = eLEARN_STATUS_ADD_SUCCESS;
        }
        // ID did not found place is ID table?
        else if (idReturn == ID_MEMORY_FULL)
        {
            // Leave the learn mode, indicating the exit event
            eLearnStatus = eLEARN_STATUS_ID_TAB_FULL;
        }
    }

    return eLearnStatus;
}
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanManualDeleteDev2LearnTab(ID_SEARCH_TYPE *pSearchIn)
{
    uint8_t u8Status;

    ID_SEARCH_TYPE  SearchOut;
    eENOCEAN_LEARN_STATUS_TYPE eLearnStatus;

    u8Status = !OK;
    
    u8Status = EnOceanSearchLearnTab( pSearchIn,&SearchOut) ;

    if ( ID_NO_SUCCESS == u8Status )
    {
        /* Can't not search data */
        eLearnStatus = eLEARN_STATUS_SEARCH_FAILURE;
        return eLearnStatus;
    }

    u8Status = EnOceanDelEEPInfoFromLearnTab(SearchOut.u8Start);

    if ( ID_MEMORY_EMPTY == u8Status )
    {
        /* Delet fail */
        eLearnStatus = eLEARN_STATUS_DEL_FAILURE;
        return eLearnStatus;
    }

    if ( ID_NO_SUCCESS == u8Status )
    {
        /* Delet fail */
        eLearnStatus = eLEARN_STATUS_DEL_FAILURE;
        return eLearnStatus;
    }

    eLearnStatus = eLEARN_STATUS_DEL_SUCCESS;

    return eLearnStatus;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanReManLearnDev2Tab(ID_SEARCH_TYPE *pSearchIn)
{

    uint8_t u8Status;

    ID_RETURN_TYPE          idReturn;               // Return  from id functions
    ID_SEARCH_TYPE          tSearchInOut;

    u8Status = EnOceanSearchLearnTab( pSearchIn,&tSearchInOut);

    // Copy the ID table from FLASH to RAM, since the ID table is going to be modified
    if ( ID_NO_SUCCESS == u8Status )
    {
        //Entry = pSearchIn->entry;
        // Add info	to the RAM ID table
        idReturn = EnOceanAddEEPInfo2LearnTab( pSearchIn->entry);

        // ID found place in RAM ID table
        if (idReturn == ID_SUCCESS)
        {
            u8Status = 0;
        }
        // ID did not found place is ID table?
        else if (idReturn == ID_MEMORY_FULL)
        {
            // Leave the learn mode, indicating the exit event
            u8Status = 1;
        }
    }
    else
    {
        /* had added to the learn tab */ 
    }

    return u8Status;
}
/* End of file */
