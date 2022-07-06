


#ifndef _ENOCEAN_LEARN_H_
#define _ENOCEAN_LEARN_H_


#include "esp3_libCommon.h"


/**************************** Learn Infomation *****************************/
#define LRN_REMOTE                  (1)

#define LRN_MANUAL                  (0)


#define LRN_SERACH                  (1)

#define RADIO_SERACH                (0)


#define RPS_LOW_4BIT                (0)
#define RPS_HIGH_4BIT               (1)


/* RPS learn channel mode */
typedef enum
{
    MODE_CHANNEL_ONOFF = 0,
    MODE_CHANNEL_TOGGLE,
    MODE_CHANNEL_OFF,
    MODE_CHANNEL_ON,
}eRPSLearnChannel_TYPE;

typedef enum
{
    eMODE_SENSOR_BIND_POSTIVE = 0,
    eMODE_SENSOR_BIND_NEGTIVE,
    eMODE_SENSOR_BIND_OFF,
    eMODE_SENSOR_BIND_ON,
}eSensorLearnChannel_TYPE;
/*
typedef enum
{
    eMODE_4BS_ON = 0,
    eMODE_4BS_OFF,
}e4BSLearnChannel_TYPE;

typedef enum
{
    eMODE_1BS_ON = 0,
    eMODE_1BS_OFF,
}e1BSLearnChannel_TYPE;
*/
/****************************ID DEFINES***********************************/
/*!
	\addtogroup id_def_grp ID constants
	Constant values used for the ID management.
	\ingroup id_grp
	@{
*/

/*!
	\name ID table related constants
	@{
*/
//! Maximum number of entries (IDs) that can be stored in the ID table
#define ID_MAX_NR_ENTRIES                   (LRN_TAB_CHANNEL_MAX*5)   
	//@}
/****************************ID TYPES***********************************/
typedef enum
{
    eLEARN_STATUS_ID_TAB_FULL = 0,
    eLEARN_STATUS_ID_TAB_EMPTY ,
    eLEARN_STATUS_RECEIVE_SUCCESS,
    eLEARN_STATUS_SEARCH_FAILURE ,
    eLEARN_STATUS_ADD_SUCCESS,
    eLEARN_STATUS_ADD_FAILURE,
    eLEARN_STATUS_DEL_SUCCESS,
    eLEARN_STATUS_DEL_FAILURE,

    eLEARN_STATUS_IDLE = 0xFF,
}eENOCEAN_LEARN_STATUS_TYPE;

enum
{
    eCMD_MANUAL_LEARN_INIT = 0,
    eCMD_MANUAL_LEARN_AUTO_LIGHT,

    eCMD_MANUAL_LEARN_ADD,
    eCMD_MANUAL_LEARN_DEL,
    
};
/*!
	\name ID table related structures
	@{
*/
//#pragma pack(1)
typedef struct 
{
    //! 启用 使能
    uint8_t u8Enable;
    //! 类型
    uint8_t u8Type;
    //! 通道
    uint8_t u8Channel;
    //! 按键
    uint8_t u8Key  ;

    uint8_t u8OutMode;
    //! 
    uint8_t u8Cmd;
}ID_LEARN_INFO;

#pragma pack(1)
//! ID table entry control byte information. This information accompanies the ID in each ID entry of the ID table
typedef struct
{
    uint8_t           :0;
    uint8_t           u1LrnType    :1;
    uint8_t           u3OutMode    :2;
    uint8_t           :0;
    uint8_t           u5Channel    ;
    uint8_t           :0;
    uint8_t           u3Key        :3;
    uint8_t           u2KeyState   :2;
    uint8_t           u3Cmd        :3;
} ID_ENTRY_RPS_TYPE;

typedef struct
{
    
    uint8_t           :0;
    uint8_t           u1LrnType    :1;
    uint8_t           u3OutMode    :2;
    uint8_t           :0;
    uint8_t           u5Channel    ;
    uint8_t           :0;

    uint8_t           u3Bit        :3;
    uint8_t           u2Bit        :2;
    uint8_t           u3Cmd        :3;       
    //! Telegram choice of the ID
} ID_ENTRY_PIR_TYPE;
// door window magnetic sensor 
typedef struct
{
    
    uint8_t           :0;
    uint8_t           u1LrnType    :1;
    uint8_t           u3OutMode    :2;
    uint8_t           :0;
    uint8_t           u5Channel    ;
    uint8_t           :0;

    uint8_t           u3Bit        :3;
    uint8_t           u2Bit        :2;
    uint8_t           u3Cmd        :3;       
    //! Telegram choice of the ID
} ID_ENTRY_IDR_TYPE;

typedef struct
{    
    uint8_t           :0;
    uint8_t           u1LrnType    :1;
    uint8_t           u3OutMode    :2;
    uint8_t           :0;
    uint8_t           u5Channel    ;
    uint8_t           :0;

    uint8_t           u3Bit        :3;
    uint8_t           u2Bit        :2;
    uint8_t           u3Cmd        :3;
    uint8_t           :0;
}ID_ENTRY_GENERAL_TYPE;


typedef union
{
    //! Telegram type, switch telegram rocker, switch telegram channel
    ID_ENTRY_PIR_TYPE                   PIR;
    ID_ENTRY_RPS_TYPE                   RPS;
    ID_ENTRY_IDR_TYPE                   IDR;
    ID_ENTRY_GENERAL_TYPE               General;
    uint16_t                            u16Data;
}LrnDev_Typedef;


typedef struct
{

    LrnDev_Typedef        LrnDev;
    //! Telegram ID bytes
    uint8_t               u8EepRorg;
    uint8_t               u8EepFun ;
    uint8_t               u8EepType;
    uint32_t              u32SrcId;
} ID_ENTRY_TYPE;
#pragma pack()

//! Input information for a search in the ID table performed by #id_search().
//! 在身份表中执行搜索到的输入信息
typedef struct
{
    //! First entry value (from 0 to #ID_MAX_NR_ENTRIES-1) to search in the ID table.
    //! 起点 第一个元素的值(从0到# ID_MAX_NR_ENTRIES-1) ID表中搜索
    uint8_t                    u8Start       ;// 30
    //! 通道检查               
    uint8_t                    u8ChannelCheck;//   1-30

    eENOCEAN_LEARN_STATUS_TYPE eState;
    //! ID入口列表
    ID_ENTRY_TYPE              entry;

} ID_SEARCH_TYPE;

#define ID_ENTRY_BYTES                            (ID_MAX_NR_ENTRIES*10+4)

#if (ID_ENTRY_BYTES%4) != 0
    #define ID_ENTRY_32BIT_NUMS                   (ID_ENTRY_BYTES/4 + 1)
#else
    #define ID_ENTRY_32BIT_NUMS                   (ID_ENTRY_BYTES/4)
#endif 

typedef union
{
    struct
    {
        //! Nr. of stored IDs in the ID table.
        //! Nr. ID存储在表的ID
        uint8_t               u8nrIDs;        
        uint8_t               u8Reserve0;
        uint8_t               u8Reserve1;
        uint8_t               u8Reserve2;
        
        //! ID table is an array of ID entries.
        //! 表是一个ID数组条目ID
        ID_ENTRY_TYPE      entry[ID_MAX_NR_ENTRIES];
    };

    uint32_t u32Words[ID_ENTRY_32BIT_NUMS];
    //uint16_t u16Bytes[ID_ENTRY_32BIT_NUMS*2];
    uint8_t  u8Bytes[ID_ENTRY_BYTES];
}LearnID_TYPE;

//! ID table structure.
//! ID 表结构
typedef struct
{
    LearnID_TYPE          ;

    uint8_t               u8DataUpdate;
    
    //uint8_t               u8DataWrite2NVMDelayTime;
} ID_TABLE_TYPE;
//#pragma pack()




/*!
	\name Switch rocker ID codes in ID table
	This codes are stored in the rocker field of each ID table entry. See #ID_ENTRY_CTRL_TYPE
	This codes have only meaning for switch telegrams
	@{
*/




//#pragma pack()
//! ID table counter + ID entries
//@}
/*!
	\name Functions return codes
	Return codes from the different ID functions
	@{
*/

//! ID functions return codes.
typedef enum
{
    //! Action correctly carried out
    ID_SUCCESS = 0      ,
    //! Error, ID table full with #ID_MAX_NR_ENTRIES IDs
    ID_MEMORY_FULL      ,
    //! Error, ID table is empty
    ID_MEMORY_EMPTY     ,
    //! No success in the search.
    ID_NO_SUCCESS       ,
    //! Can Learn
    ID_NO_ACCESS ,
} ID_RETURN_TYPE;


extern const uint32_t              u32LearnSupportEEP[];
extern ID_TABLE_TYPE               LearnInfoTab ;

/**
  * @brief
  * @param
  * @retval None
  */
void EnOceanDevSendEEPInfo2GateWay(Radio_Typedef *pRadio,uint32_t u32EEP,uint8_t u8ChannelID);
/**
  * @brief
  * @param
  * @retval None
  */
uint32_t EnOceanDevSendEEPInfoGetPhyID(uint32_t u32EEP,uint8_t u8BaseID);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSearchLearnDataByRPSLeft(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSearchLearnDataByRPSRight(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSearchLearnDataBy1BS(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSearchLearnDataBy4BS(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanGetSearchDataByUTEOrVLDTelRadio(Radio_Typedef const *pRadio,ID_SEARCH_TYPE *pSearchIn,ID_LEARN_INFO *pIDLearn);
/**
  * @brief
  * @param
  * @retval None
  */
ID_RETURN_TYPE EnOceanAddEEPInfo2LearnTab(ID_ENTRY_TYPE Entry );
/**
  * @brief
  * @param
  * @retval None
  */
ID_RETURN_TYPE EnOceanDelChannelLearnInfoFromTab(uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
// ***************************** ID_SEARCH ***************************************************************
/**
  * @brief  
  * @param
  * @retval None 
  */
uint8_t EnOceanGetLearnEvent(void);
/**
  * @brief  
  * @param
  * @retval None 
  */
void EnOceanClearLearnSaveEvent(void);
/**
  * @brief  
  * @param
  * @retval None 
  */
uint8_t EnOceanGetLearnTabNums(void);
/**
  * @brief  
  * @param
  * @retval None 
  */
uint8_t EnOceanGetLearnChannelTabNums(uint8_t u8Channel);
/**
  * @brief  
  * @param
  * @retval None 
  */
ID_RETURN_TYPE EnOceanClearLearnTabNums(void);
/**
  * @brief  
  * @param
  * @retval None 
  */
RM_RETURN_TYPE EnOceanSaveLearnTabEvent(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanSearchDevNumsByEEP(uint32_t u32EEP);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanSearchLearnDevByEEP(ID_SEARCH_TYPE *pSearchOut,uint32_t u32EEP);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanSearchDevNumsBySrcID(uint32_t u32SrcID);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanSearchDevLearnStatusBySrcID(uint32_t u32SrcID);
/**
  * @brief  
  * @param
  * @retval None 
  */
ID_RETURN_TYPE EnOceanSearchLearnTab(ID_SEARCH_TYPE const *pSearchIn,ID_SEARCH_TYPE *pSearchOut);
/**
  * @brief
  * @param
  * @retval None
  */
// ***************************** ID_DELETE *******************
ID_RETURN_TYPE EnOceanDelEEPInfoFromLearnTab(uint8_t u8index);
// ***************************** END ID_DELETE *******************

/**
  * @brief
  * @param
  * @retval None
  */
// ***************************** ID_DELETE_ALL *******************
ID_RETURN_TYPE EnOceanDelLearnTabAll(void);
// *************************** END ID_DELETE_ALL *****************

// ***************************** END ID_SEARCH *******************
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanManualLearnDev2Tab(ID_SEARCH_TYPE *pSearchIn);
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanManualAddDev2LearnTab(ID_SEARCH_TYPE *pSearchIn);
/**
  * @brief
  * @param
  * @retval None
  */
eENOCEAN_LEARN_STATUS_TYPE EnOceanManualDeleteDev2LearnTab(ID_SEARCH_TYPE *pSearchIn);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t EnOceanReManLearnDev2Tab(ID_SEARCH_TYPE *pSearchIn);
/**
  * @brief
  * @param
  * @retval None
  */
void Channel_ModifyManualMode(uint8_t u8DevChannelMode);




#endif
