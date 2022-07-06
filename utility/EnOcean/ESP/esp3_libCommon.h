
#ifndef _ESP3_LIB_COMMON_H_
#define _ESP3_LIB_COMMON_H_

#include "platform.h"
#include "..\BaseLib\BaselibInclude.h"

/*********************************************************************************************/
/************************************ UART MODULE *******************************************/
/*********************************************************************************************/
#define ESP3_RETRANSMISSION_NUM                     (3)
/*********************************************************************************************/
/*********************************************************************************************/ 
#define ENOCEAN_MENRED_MAN_ID                       (0x051)
#define ENOCEAN_BASEID_START                        (0xFF800000)
#define ENOCEAN_BASEID_END                          (0xFFFFFF80)
//#define ENOCEAN_EEP_DB_MAX                          (16)

/****************** EEP MACRO ****************************************************************/ 
#define EEP_F60201                                  (0xF60201)
#define EEP_A50701                                  (0xA50701)
#define EEP_A50702                                  (0xA50702)
#define EEP_A50703                                  (0xA50703)
#define EEP_A50801                                  (0xA50801)
#define EEP_A50802                                  (0xA50802)
#define EEP_A50803                                  (0xA50803)

#define EEP_D50001                                  (0xD50001)
#define EEP_A50905                                  (0xA50905)
#define EEP_A50907                                  (0xA50907)
#define EEP_A50910                                  (0xA50910)
/* airbox */
#define EEP_D10104                                  (0xD10104)
/* lock */
#define EEP_D10105                                  (0xD10105)
/* */
#define EEP_D10106                                  (0xD10106)
#define EEP_D10107                                  (0xD10107)
#define EEP_D10108                                  (0xD10108)
#define EEP_D10109                                  (0xD10109)
/* Clover thermostate */
#define EEP_D1010A                                  (0xD1010A)
/* Clover light */
#define EEP_D1010B                                  (0xD1010B)
/* Dali dimming */
#define EEP_D1010C                                  (0xD1010C)
/* RPL.4X */
#define EEP_D1010D                                  (0xD1010D)

#define EEP_D20101                                  (0xD20101)
#define EEP_D20113                                  (0xD20113)
#define EEP_D20115                                  (0xD20115)
#define EEP_D20116                                  (0xD20116)

#define EEP_SMART_HIVE                              (0xD1F5F1)
/****************** EEP MACRO END *******************************************/ 

/***************** PTM2XX MACRO  ***********************************/
typedef enum
{
    EEP_F60201_ON_1                          = 0x01,
    EEP_F60201_OFF_1                         = 0x03,
    EEP_F60201_ON_2                          = 0x05,
    EEP_F60201_OFF_2                         = 0x07,
                                                  
    EEP_F60201_ON_1_SHORT_RELEASE            = 0x00,
    EEP_F60201_OFF_1_SHORT_RELEASE           = 0x02,
    EEP_F60201_ON_2_SHORT_RELEASE            = 0x04,
    EEP_F60201_OFF_2_SHORT_RELEASE           = 0x06,
                                              
    EEP_F60201_ON_1_LONG_PRESSED             = 0xF1,
    EEP_F60201_OFF_1_LONG_PRESSED            = 0xF3,
    EEP_F60201_ON_2_LONG_PRESSED             = 0xF5,
    EEP_F60201_OFF_2_LONG_PRESSED            = 0xF7,
    
    EEP_F60201_ON_1_LONG_RELEASED            = 0xF0,
    EEP_F60201_OFF_1_LONG_RELEASED           = 0xF2,
    EEP_F60201_ON_2_ONG_RELEASED             = 0xF4,
    EEP_F60201_OFF_2_LONG_RELEASED           = 0xF6,
    /* Origined */
    EEP_F60201_ON_1_KEY_PRESSED              = 0x10,
    EEP_F60201_OFF_1_KEY_PRESSED             = 0x30,
    EEP_F60201_ON_2_KEY_PRESSED              = 0x50,
    EEP_F60201_OFF_2_KEY_PRESSED             = 0x70,

    EEP_F60201_ON_1_KEY_RELEASE              = 0x00,
    EEP_F60201_OFF_1_KEY_RELEASE             = 0x20,
    EEP_F60201_ON_2_KEY_RELEASE              = 0x40,
    EEP_F60201_OFF_2_KEY_RELEASE             = 0x60,
                                                  
    EEP_F60201_ON1_ON2_KEY_PRESSED           = 0x15,
    EEP_F60201_ON2_OFF1_KEY_PRESSED          = 0x17,
    EEP_F60201_OFF2_OFF2_KEY_PRESSED         = 0x37,

}
ePTM2XX_BUTTON_TYPE;


#define PTM2XX_RORG                                 (0xF6)
#define PTM2XX_FUN                                  (0x02)
#define PTM2XX_TYPE                                 (0x01)

#define PTM2XX_ROCK_PRESSED_STATUS                  (0x30)//EEP(F60201)按下状态应该是0x10
#define PTM2XX_ROCK_RELEASE_STATUS                  (0x20)//EEP(F60201)按下状态应该是0x00

/******************PTM2XX MACRO END *******************************/ 
/* reapter */
typedef enum
{
    REAPTER_LEVEL_0 = 0,
    REAPTER_LEVEL_1 ,
    REAPTER_LEVEL_2 ,
}eReapter_TYPE;

enum
{
    eRPS_ROCK_IDLE = 0,
    eRPS_ROCK_DOWN ,
    eRPS_ROCK_RELEASE ,
};

typedef void (*CallBackFun_Typedef)(void);
typedef void (*CallBackSend_Typedef)(uint8_t u8Data);
typedef uint8_t (*u8ReturnCallBackFun_Typedef)(void);
typedef uint8_t (*CallBackFun_u8_Typedef)(uint8_t u8State);



typedef enum
{
    PACKET_RESERVED             = 0x00, //! Reserved
    PACKET_RADIO                = 0x01, //! Radio telegram
    PACKET_RESPONSE             = 0x02, //! Response to any packet
    PACKET_RADIO_SUB_TEL        = 0x03, //! Radio subtelegram 
    PACKET_EVENT                = 0x04, //! Event message
    PACKET_COMMON_COMMAND       = 0x05, //! Common command
    PACKET_SMART_ACK_COMMAND    = 0x06, //! Smart Ack command
    PACKET_REMOTE_MAN_COMMAND   = 0x07, //! Remote management command
    PACKET_PRODUCTION_COMMAND   = 0x08, //! Production command
    PACKET_RADIO_MESSAGE        = 0x09  //! Radio message (chained radio telegrams)
} PACKET_TYPE;

//! Response type
typedef enum
{
    RET_OK                  = 0x00, //! OK ... command is understood and triggered
    RET_ERROR               = 0x01, //! There is an error occured
    RET_NOT_SUPPORTED       = 0x02, //! The functionality is not supported by that implementation
    RET_WRONG_PARAM         = 0x03, //! There was a wrong parameter in the command
    RET_OPERATION_DENIED    = 0x04, //! Example: memory access denied (-protected)
    RET_DUTY_LOCK_SET       = 0x05, //! Example: memory access denied (-protected)
    RET_USER                = 0x80  //! Return codes greater than 0x80 are used for commands with special return information, not commonly useable.
    //RET_NO_USER             = 0x80  //! Return codes greater than 0x80 are used for commands with special return information, not commonly useable.
} RESPONSE_TYPE;

//! Common command enum
typedef enum
{
    CO_RESERVED         = 0,
    CO_WR_SLEEP         = 1,    //! Order to enter in energy saving mode
    CO_WR_RESET         = 2,    //! Order to reset the device
    CO_RD_VERSION       = 3,    //! Read the device (SW) version / (Dev) version, chip ID etc.
    CO_RD_SYS_LOG       = 4,    //! Read system log from device databank
    CO_WR_SYS_LOG       = 5,    //! Reset System log from device databank
    CO_WR_BIST          = 6,    //! Perform Flash BIST operation
    CO_WR_IDBASE        = 7,    //! Write ID range base number
    CO_RD_IDBASE        = 8,    //! Read ID range base number
    CO_WR_REPEATER      = 9,    //! Write Repeater Level off,1,2
    CO_RD_REPEATER      = 10,   //! Read Repeater Level off,1,2
    CO_WR_FILTER_ADD    = 11,   //! Add filter to filter list
    CO_WR_FILTER_DEL    = 12,   //! Delete filter from filter list
    CO_WR_FILTER_DEL_ALL= 13,   //! Delete filters
    CO_WR_FILTER_ENABLE = 14,   //! Enable/Disable supplied filters
    CO_RD_FILTER        = 15,   //! Read supplied filters
    CO_WR_WAIT_MATURITY = 16,   //! Waiting till end of maturity time before received radio telegrams will transmitted
    CO_WR_SUBTEL        = 17,   //! Enable/Disable transmitting additional subtelegram info
    CO_WR_MEM           = 18,   //! Write x bytes of the Flash, XRAM, RAM0 ?
    CO_RD_MEM           = 19,   //! Read x bytes of the Flash, XRAM, RAM0 ?
    CO_RD_MEM_ADDRESS   = 20,   //! Feedback about the used address and length of the config area and the Smart Ack Table
    //#ifdef
    CO_RD_SECURITY      = 21,   //! Read security informations (level, keys)
    CO_WR_SECURITY      = 22,   //! Write security informations (level, keys)
    CO_WR_LEARNMODE     = 23,   //! Set/Reset controller learn mode
    CO_RD_LEARNMODE     = 24,   //! Get controller learn mode state
    CO_WR_SECUREDEVICE_ADD = 25,//! Add secure device to controller
    CO_WR_SECUREDEVICE_DEL = 26,//! Delete secure device from controller
    CO_RD_SECUREDEVICE_BY_INDEX = 27,   //! Read teached in secure devices by index
    CO_WR_MODE = 28,    //! Sets the gateway transceiver mode
    CO_RD_SECUREDEVICE_COUNT = 29,  //! Read number of teached in secure devices
    CO_RD_SECUREDEVICE_BY_ID = 30,  //! Check, if secure device with given Id is teached in    
    CO_RD_DUTYCYCLE_LIMIT    = 35,
//#endif
} COMMON_COMMAND_TYPE;

//! SmartAck command enum
typedef enum
{
    SA_WR_LEARNMODE     = 1,    //Set/Reset Smart Ack learn mode
    SA_RD_LEARNMODE     = 2,    //Get Smart Ack learn mode state
    SA_WR_LEARNCONFIRM  = 3,    //Used for Smart Ack to add or delete a mailbox of a client
    SA_WR_CLIENTLEARNRQ = 4,    //Send Smart Ack Learn request (Client)
    SA_WR_RESET         = 5,    //Send reset command to every SA sensor
    SA_RD_LEARNEDCLIENTS= 6,    //Get Smart Ack learned sensors / mailboxes
    SA_WR_RECLAIMS      = 7,    //Set number of reclaim attempts
    SA_WR_POSTMASTER    = 8,    //Activate/Deactivate Post master functionality

} SMARTACK_COMMAND_TYPE;

//! Event enum
typedef enum
{
    SA_RECLAIM_NOT_SUCCESSFUL   = 0x01, //Informs the backbone of a Smart Ack Client to not successful reclaim.
    SA_CONFIRM_LEARN            = 0x02, //Used for SMACK to confirm/discard learn in/out
    SA_LEARN_ACK                = 0x03, //Inform backbone about result of learn request
    CO_READY                    = 0x04, //Inform backbone about operational readiness
    CO_EVENT_SECUREDEVICES      = 0x05, //Inform backbone about a secure device
    CO_DUTYCYCLE_LIMIT          = 0x06,
} EVENT_TYPE;
/************************* Remote manged process command ******************************/
#define  RM_DEFAULTMANID   0x7FF
#define  RM_DEFAULT_REMAN_CODE   0xF5F1511D
//  Default Manufacturer ID.

 #define  RM_DEFAULTEEP   0x000
//  Default EEP.

 #define  RM_ANSWER_START   0x600
 #define  RM_EXPAND_ANSWER_START   0x700
//  Begin of the answer function codes.

 #define  RM_RPC_START   0x200
//  Value from which rpc codes begin.

 #define  LOCK_INIT_VALUE   0xFFFFFFFF
//  Initial value of a blank flash page.

 #define  EXIT_NO_FURTHER_ANALYSIS   0x00
//  Return value when user application does not do anything further.


/*!
    \name  Remote learn related telegram codes
    The code relates to the byte 9 in the SYS_EX telegram when the telegram function is REMOTE LEARN
    @{
*/
//! Code that starts the remote learn.
#define RM_LRN_START                      0x01
//! Code that changes to the next learn channel
#define RM_LRN_NEXT_CHANNEL               0x02
//! Code that leaves the learn mode
#define RM_LRN_STOP                       0x03


#define RM_LOCK             (1)
#define RM_UNLOCK           (0)
#define RM_AUTO_LOCK_TIME   (18000)


#define MENRED_RPC_CMD_BASE                                                (0x300)
#define RANDOM_ENABLE                                                      (1)
#define RANDOM_DISABLE                                                     (0)


/************************* Remote manged process command ******************************/
/*
#define RM_COMMANDO_ACTION_DATA_LENGTH                            (0x00)
#define RM_COMMANDO_LRN_DATA_LENGTH                               (0x04)
#define RM_COMMANDO_SET_CODE_DATA_LENGTH                          (0x04)
#define RM_COMMANDO_FLASH_READ_DATA_LENGTH                        (0x04)
#define RM_COMMANDO_SMACK_SETINGS_READ_DATA_LENGTH                (0x01)
#define RM_COMMANDO_SMACK_SETINGS_WRITE_DEL_DATA_LENGTH           (0x02)

#define RM_RPC_RESET_ALL_LENGTH                                   (0x04)
#define RM_RPC_READ_CFG_LENGTH                                    (0x04)
#define RM_RPC_WRITE_CFG_LENGTH                                   (0x04)
#define RM_RPC_READ_IDS_LENGTH                                    (0x04)
#define RM_RPC_WRITE_IDS_LENGTH                                   (0x04)
#define RM_RPC_ADD_ONE_LENGTH                                     (0x0A)
#define RM_RPC_DEL_ONE_LENGTH                                     (0x0A)
#define RM_RPC_READ_ONE_LENGTH                                    (0x0A)
#define RM_RPC_READ_ONE_BY_ONE_LENGTH                             (0x04)
#define RM_RPC_READ_CODE_LENGTH                                   (0x04)
#define RM_RPC_WRITE_CODE_LENGTH                                  (0x04)
#define RM_RPC_RESET_CODE_LENGTH                                  (0x04)
*/


//! Return codes from RMCC and RPC functions. Values are used in Query Status commands.
typedef enum
{
    RM_RETURN_CODE_OK                               = 0x00, //!<OK return .
    RM_RETURN_CODE_WRONG_ID	                        = 0x01, //!<Wrong target ID .
    RM_RETURN_CODE_WRONG_CODE                       = 0x02, //!<Wrong securty  return .
    RM_RETURN_CODE_WRONG_EEP                        = 0x03, //!<Wrong EEP.
    RM_RETURN_CODE_WRONG_MANID                      = 0x04, //!<Wrong Manufacturer ID.
    RM_RETURN_CODE_WRONG_DATA_SIZE                  = 0x05, //!<Function misses  to execute.
    RM_RETURN_CODE_NO_CODE_SET                      = 0x06, //!<No security  set return .
    RM_RETURN_CODE_NOT_SENT                         = 0x07, //!<Answer / telegram not send.
    RM_RETURN_CODE_RPC_FAILED                       = 0x08, //!<RPC failed.
    RM_RETURN_CODE_MESSAGE_TIME_OUT                 = 0x09, //!<Previous message was chain period time-out.
    RM_RETURN_CODE_TOO_LONG_MESSAGE                 = 0x0A, //!<Too long message, the sum of to transfer  extends the internal buffer.
    RM_RETURN_CODE_MESSAGE_PART_ALREADY_RECEIVED    = 0x0B, //!<In merge process the actual message part was already received. Indicates an possible error state.
    RM_RETURN_CODE_MESSAGE_NOT_RECEIVED             = 0x0C, //!<Previous message was not received completly.
    RM_RETURN_CODE_ADDRESS_OUT_OF_RANGE             = 0x0D, //!<Specified address is out of range
    RM_RETURN_CODE_DATA_SIZE_EXCEEDED               = 0x0E, //!<Unable to process requested  size
    RM_RETURN_CODE_WRONG_DATA                       = 0x0F  //!<Data are not in expected range
} RM_RETURN_CODE;

//! Remote manager function codes
typedef enum
{
    RM_NOT_DEFINED                            = 0x00, //!<Not definet function , represents the null value.
    RM_FN_UNLOCK                              = 0x01, //!<Unlock command.
    RM_FN_LOCK                                = 0x02, //!<Lock command.
    RM_FN_SET_CODE                            = 0x03, //!<Set security command.
                                              
    RM_FN_QUERY_ID                            = 0x04, //!<Query ID command.
    RM_FN_ACTION_COMMAND                      = 0x05, //!<Test command.
    RM_FN_PING_COMMAND                        = 0x06, //!<Ping command.
    RM_FN_QUERY_FUNCTION_COMMAND              = 0x07, //!<Query supported RPC functions command.
    RM_FN_QUERY_STATUS                        = 0x08, //!<Query debug status of remote manager.
                                         
    RM_FN_REMOTE_LEARN                        = RM_RPC_START + 0x01, //!<Remote learn RPC .
    RM_FN_REMOTE_CLEAR                        = RM_RPC_START + 0x02, //!<Remote clear RPC , structure to be defined.
    RM_FN_REMOTE_WRITE                        = RM_RPC_START + 0x03, //!<Remote write RPC .
    RM_FN_REMOTE_READ                         = RM_RPC_START + 0x04, //!<Remote read RPC .
    RM_FN_SMACK_SETTING_READ                  = RM_RPC_START + 0x05, //!<RPC for Smack query setting.
    RM_FN_SMACK_SETTING_WRITE                 = RM_RPC_START + 0x06, //!<RPC for Smack write setting.
                                              
    //RM_FN_QUERY_ID_ANS                        = RM_EXPAND_ANSWER_START + RM_FN_QUERY_ID,//RM_ANSWER_START + RM_FN_QUERY_ID,               //!<Query ID answer.
    RM_FN_QUERY_ID_ANS                        = RM_ANSWER_START + RM_FN_QUERY_ID,               //!<Query ID answer.
    RM_FN_PING_COMMAND_ANS                    = RM_ANSWER_START + RM_FN_PING_COMMAND,           //!<Ping answer.
    RM_FN_QUERY_FUNCTION_COMMAND_ANS          = RM_ANSWER_START + RM_FN_QUERY_FUNCTION_COMMAND, //!<Query supported RPC functions answer.
    RM_FN_QUERY_STATUS_ANS                    = RM_ANSWER_START + RM_FN_QUERY_STATUS,           //!<Query status answer.
    RM_FN_REMOTE_READ_ANS                     = RM_ANSWER_START + RM_FN_REMOTE_READ,            //!<Remote read answer.
    RM_FN_SMACK_SETTING_ANS                   = RM_ANSWER_START + RM_FN_SMACK_SETTING_READ,     //!<RPC Smack query setting answer.
    RM_FN_LEARNED_SENSORS_ANS                 = RM_ANSWER_START + RM_FN_SMACK_SETTING_READ +1,  //!<RPC Smack query sensor answer.


    /* */
    RM_RPC_RESET_ALL                              = MENRED_RPC_CMD_BASE,
    RM_RPC_READ_CFG                               = MENRED_RPC_CMD_BASE + 0x01,
    RM_RPC_WRITE_CFG                              = MENRED_RPC_CMD_BASE + 0x02,
    RM_RPC_READ_IDS                               = MENRED_RPC_CMD_BASE + 0x03,
    RM_RPC_CLEAR_IDS                              = MENRED_RPC_CMD_BASE + 0x04,
    RM_RPC_ADD_ONE                                = MENRED_RPC_CMD_BASE + 0x05,
    RM_RPC_DEL_ONE                                = MENRED_RPC_CMD_BASE + 0x06,
    RM_RPC_READ_ONE                               = MENRED_RPC_CMD_BASE + 0x07,
    RM_RPC_READ_ONE_BY_ONE                        = MENRED_RPC_CMD_BASE + 0x08,
    RM_RPC_TEST_CHANNEL                           = MENRED_RPC_CMD_BASE + 0x09,
                                                  
    RM_RPC_READ_BASEID                            = MENRED_RPC_CMD_BASE + 0x0A,
    RM_RPC_WRITE_BASEID                           = MENRED_RPC_CMD_BASE + 0x0B,
    RM_RPC_QUERY_ALL_BASEID_DEV                   = MENRED_RPC_CMD_BASE + 0x0C,
    RM_RPC_READ_LIGHT_NUMS                        = MENRED_RPC_CMD_BASE + 0x0D,
    RM_RPC_READ_LIGHT_TYPE                        = MENRED_RPC_CMD_BASE + 0x0E,
    RM_RPC_READ_CURTAIN_NUMS                      = MENRED_RPC_CMD_BASE + 0x0F,
    RM_RPC_READ_CURTAIN_TYPE                      = MENRED_RPC_CMD_BASE + 0x10,
                                                  
    RM_RPC_READ_CLOVER_PAGE_CFG                   = MENRED_RPC_CMD_BASE + 0x11,
    RM_RPC_WRITE_CLOVER_PAGE_CFG                  = MENRED_RPC_CMD_BASE + 0x12,
    RM_RPC_READ_CLOVER_PAGE_ROCK_BUTTON_CFG       = MENRED_RPC_CMD_BASE + 0x13,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_BUTTON_CFG      = MENRED_RPC_CMD_BASE + 0x14,
    RM_RPC_READ_CLOVER_PAGE_ROCK_TITLE_CFG        = MENRED_RPC_CMD_BASE + 0x15,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_TITLE_CFG       = MENRED_RPC_CMD_BASE + 0x16,
    RM_RPC_READ_CLOVER_TYPE                       = MENRED_RPC_CMD_BASE + 0x17,
    RM_RPC_READ_CLOVER_PAGE_ROCK_MODE_CFG         = MENRED_RPC_CMD_BASE + 0x18,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_MODE_CFG        = MENRED_RPC_CMD_BASE + 0x19,
    RM_RPC_READ_CLOVER_PAGE_CHANNEL_MASK_CFG      = MENRED_RPC_CMD_BASE + 0x1A,
    RM_RPC_WRITE_CLOVER_PAGE_CHANNEL_MASK_CFG     = MENRED_RPC_CMD_BASE + 0x1B,
    RM_RPC_WRITE_LIGHT_TYPE                       = MENRED_RPC_CMD_BASE + 0x1C,
    
    RM_RPC_READ_CLOVER_PAGE_DALI_CHANNEL_CFG      = MENRED_RPC_CMD_BASE + 0x1D,
    RM_RPC_ADD_CLOVER_PAGE_DALI_CHANNEL_CFG       = MENRED_RPC_CMD_BASE + 0x1E,
    RM_RPC_DEL_CLOVER_PAGE_DALI_CHANNEL_CFG       = MENRED_RPC_CMD_BASE + 0x1F,
    RM_RPC_CASCADE_DEV_NUMS                       = MENRED_RPC_CMD_BASE + 0x20,
    RM_RPC_CASCADE_BUS_VERSION                    = MENRED_RPC_CMD_BASE + 0x21,
    RM_RPC_QUERY_ALL_BASEID_DEV_ADVANCED          = MENRED_RPC_CMD_BASE + 0x22,
    RM_RPC_READ_DI_NUMS                           = MENRED_RPC_CMD_BASE + 0x23,

    RM_RPC_ADD_LEARN_ADVANCED                     = MENRED_RPC_CMD_BASE + 0x30,
    RM_RPC_DEL_LEARN_ADVANCED                     = MENRED_RPC_CMD_BASE + 0x31,
    RM_RPC_READ_LEARN_CHANNEL_INFO                = MENRED_RPC_CMD_BASE + 0x32,
    RM_RPC_OPEN_CURTAIN_LEARN                     = MENRED_RPC_CMD_BASE + 0x33,
    RM_RPC_READ_GATEWAY_LEARN_IDS                 = MENRED_RPC_CMD_BASE + 0x34,
    RM_RPC_CLEAR_GATEWAY_LEARN_IDS                = MENRED_RPC_CMD_BASE + 0x35,                                                                                                        
    RM_RPC_FORWARD_LONG_DATAS                     = MENRED_RPC_CMD_BASE + 0x36,    

    //RM_RPC_READ_CODE                              = MENRED_RPC_CMD_BASE + 0xF0,
    //RM_RPC_WRITE_CODE                             = MENRED_RPC_CMD_BASE + 0xF1,
    //RM_RPC_RESET_CODE                             = MENRED_RPC_CMD_BASE + 0xF2,

    /* */
    RM_RPC_RESET_ALL_ANS                          = RM_ANSWER_START + RM_RPC_RESET_ALL,
    RM_RPC_READ_CFG_ANS                           = RM_ANSWER_START + RM_RPC_READ_CFG,
    RM_RPC_WRITE_CFG_ANS                          = RM_ANSWER_START + RM_RPC_WRITE_CFG,
    RM_RPC_READ_IDS_ANS                           = RM_ANSWER_START + RM_RPC_READ_IDS,
    RM_RPC_CLEAR_IDS_ANS                          = RM_ANSWER_START + RM_RPC_CLEAR_IDS,
    RM_RPC_ADD_ONE_ANS                            = RM_ANSWER_START + RM_RPC_ADD_ONE,
    RM_RPC_DEL_ONE_ANS                            = RM_ANSWER_START + RM_RPC_DEL_ONE,
    RM_RPC_READ_ONE_ANS                           = RM_ANSWER_START + RM_RPC_READ_ONE,
    RM_RPC_READ_ONE_BY_ONE_ANS                    = RM_ANSWER_START + RM_RPC_READ_ONE_BY_ONE,
    //RM_RPC_READ_CODE_ANS                          = RM_ANSWER_START + RM_RPC_READ_CODE,
    //RM_RPC_WRITE_CODE_ANS                         = RM_ANSWER_START + RM_RPC_WRITE_CODE,
    //RM_RPC_RESET_CODE_ANS                         = RM_ANSWER_START + RM_RPC_RESET_CODE,
    RM_RPC_TEST_CHANNEL_ANS                       = RM_ANSWER_START + RM_RPC_TEST_CHANNEL,
                                                                                                    
    RM_RPC_READ_BASEID_ANS                        = RM_ANSWER_START + RM_RPC_READ_BASEID         ,
    RM_RPC_WRITE_BASEID_ANS                       = RM_ANSWER_START + RM_RPC_WRITE_BASEID        ,
    RM_RPC_QUERY_ALL_BASEID_DEV_ANS               = RM_ANSWER_START + RM_RPC_QUERY_ALL_BASEID_DEV,
    RM_RPC_READ_LIGHT_NUMS_ANS                    = RM_ANSWER_START + RM_RPC_READ_LIGHT_NUMS     ,
    RM_RPC_READ_LIGHT_TYPE_ANS                    = RM_ANSWER_START + RM_RPC_READ_LIGHT_TYPE     ,
    RM_RPC_READ_CURTAIN_NUMS_ANS                  = RM_ANSWER_START + RM_RPC_READ_CURTAIN_NUMS   ,
    RM_RPC_READ_CURTAIN_TYPE_ANS                  = RM_ANSWER_START + RM_RPC_READ_CURTAIN_TYPE   ,
                                                  
    RM_RPC_READ_CLOVER_PAGE_CFG_ANS               = RM_ANSWER_START + RM_RPC_READ_CLOVER_PAGE_CFG      ,
    RM_RPC_WRITE_CLOVER_PAGE_CFG_ANS              = RM_ANSWER_START + RM_RPC_WRITE_CLOVER_PAGE_CFG     ,
    RM_RPC_READ_CLOVER_PAGE_ROCK_BUTTON_CFG_ANS   = RM_ANSWER_START + RM_RPC_READ_CLOVER_PAGE_ROCK_BUTTON_CFG ,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_BUTTON_CFG_ANS  = RM_ANSWER_START + RM_RPC_WRITE_CLOVER_PAGE_ROCK_BUTTON_CFG,
    RM_RPC_READ_CLOVER_PAGE_ROCK_TITLE_CFG_ANS    = RM_ANSWER_START + RM_RPC_READ_CLOVER_PAGE_ROCK_TITLE_CFG,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_TITLE_CFG_ANS   = RM_ANSWER_START + RM_RPC_WRITE_CLOVER_PAGE_ROCK_TITLE_CFG,
    RM_RPC_READ_CLOVER_TYPE_ANS                   = RM_ANSWER_START + RM_RPC_READ_CLOVER_TYPE,          
    RM_RPC_READ_CLOVER_PAGE_ROCK_MODE_CFG_ANS     = RM_ANSWER_START + RM_RPC_READ_CLOVER_PAGE_ROCK_MODE_CFG,
    RM_RPC_WRITE_CLOVER_PAGE_ROCK_MODE_CFG_ANS    = RM_ANSWER_START + RM_RPC_WRITE_CLOVER_PAGE_ROCK_MODE_CFG,
    RM_RPC_READ_CLOVER_PAGE_CHANNEL_MASK_CFG_ANS  = RM_ANSWER_START + RM_RPC_READ_CLOVER_PAGE_CHANNEL_MASK_CFG,
    RM_RPC_WRITE_CLOVER_PAGE_CHANNEL_MASK_CFG_ANS = RM_ANSWER_START + RM_RPC_WRITE_CLOVER_PAGE_CHANNEL_MASK_CFG,
    RM_RPC_WRITE_CLOVER_CHANNEL_TYPE_CFG_ANS      = RM_ANSWER_START + RM_RPC_WRITE_LIGHT_TYPE,

    RM_RPC_READ_CLOVER_PAGE_DALI_CHANNEL_CFG_ANS  = RM_ANSWER_START + RM_RPC_READ_CLOVER_PAGE_DALI_CHANNEL_CFG,
    RM_RPC_ADD_CLOVER_PAGE_DALI_CHANNEL_CFG_ANS   = RM_ANSWER_START + RM_RPC_ADD_CLOVER_PAGE_DALI_CHANNEL_CFG,
    RM_RPC_DEL_CLOVER_PAGE_DALI_CHANNEL_CFG_ANS   = RM_ANSWER_START + RM_RPC_DEL_CLOVER_PAGE_DALI_CHANNEL_CFG,
    RM_RPC_CASCADE_BUS_VERSION_ANS                = RM_ANSWER_START + RM_RPC_CASCADE_BUS_VERSION,
    RM_RPC_QUERY_ALL_BASEID_DEV_ADVANCED_ANS      = RM_ANSWER_START + RM_RPC_QUERY_ALL_BASEID_DEV_ADVANCED,
    RM_RPC_READ_DI_NUMS_ANS                       = RM_ANSWER_START + RM_RPC_READ_DI_NUMS,
    RM_RPC_ADD_LEARN_ADVANCED_ANS                 = RM_ANSWER_START + RM_RPC_ADD_LEARN_ADVANCED,
    RM_RPC_DEL_LEARN_ADVANCED_ANS                 = RM_ANSWER_START + RM_RPC_DEL_LEARN_ADVANCED,
    RM_RPC_READ_LEARN_CHANNEL_INFO_ANS            = RM_ANSWER_START + RM_RPC_READ_LEARN_CHANNEL_INFO,
    RM_RPC_OPEN_CURTAIN_LEARN_ANS                 = RM_ANSWER_START + RM_RPC_OPEN_CURTAIN_LEARN,
    RM_RPC_READ_GATEWAY_LEARN_IDS_ANS             = RM_ANSWER_START + RM_RPC_READ_GATEWAY_LEARN_IDS,
    RM_RPC_CLEAR_GATEWAY_LEARN_IDS_ANS            = RM_ANSWER_START + RM_RPC_CLEAR_GATEWAY_LEARN_IDS,
    RM_RPC_FORWARD_LONG_DATAS_ANS                 = RM_ANSWER_START + RM_RPC_FORWARD_LONG_DATAS,

}  RM_RPC;

/*!
    \name Function return codes
    Remote management function return codes
    @{
*/
typedef enum
{
    //! General positive result
    RM_SUCCESS                                  ,
    //! General negative result
    RM_NO_SUCCESS                               ,
    //!
    RM_COMMAND_LEARN_NO_SUCCESS                 ,
    RM_COMMAND_LEARN_START                      ,
    RM_COMMAND_LEARN_STOP                       ,
    RM_COMMAND_LEARN_NEXT_CHANNEL               ,
    RM_COMMAND_FLASH_READ_NO_SUCCESS            ,
    RM_COMMAND_FLASH_READ                       ,
    RM_COMMAND_SMACK_SETTING_READ_NO_SUCCESS    ,
    RM_COMMAND_SMACK_SETTING_READ               ,
    RM_COMMAND_SMACK_SETTING_WRITE_NO_SUCCESS   ,
    RM_COMMAND_SMACK_SETTING_WRITE              ,
    RM_COMMAND_ACTION_NO_SUCCESS                ,
    RM_COMMAND_ACTION                           ,
    RM_COMMAND_SET_CODE_NO_SUCCESS              ,
    RM_COMMAND_SET_CODE                         ,

    RM_LEARN_CHANNEL,
}RM_RETURN_TYPE;

/*****************************************************************************************************************/
typedef enum
{
    ESP_NO_ERR = 0,
    ESP_SEND_BUFF_OVF_MAX_ERR = 1,
    ESP_RECEIVE_BUFF_OVF_MAX_ERR,
    //ESP_RECEIVE_THREAD_BUFF_OVF_MAX_ERR,
}ESP_ERR;

enum
{
    eTX_IDLE = 0,
    eTX_SEND_DATA_PROCESS ,
    eTX_SEND_DATA,
    eTX_SEND_OK,
    eTX_WAIT_RECEIVE,
    eTX_RECEIVE_OK,
};

//! Function return codes
typedef enum
{
    //! <b>0</b> - Action performed. No problem detected
    //OK=0,
    //! <b>1</b> - Action couldn't be carried out within a certain time.
    TIME_OUT = 1,
    //! <b>2</b> - The write/erase/verify process failed, the flash page seems to be corrupted
    FLASH_HW_ERROR,
    //! <b>3</b> - A new UART/SPI byte received
    NEW_RX_BYTE,
    //! <b>4</b> - No new UART/SPI byte received
    NO_RX_BYTE,
    //! <b>5</b> - New telegram received
    NEW_RX_TEL,
    //! <b>6</b> - No new telegram received
    NO_RX_TEL,
    //! <b>7</b> - Checksum not valid
    NOT_VALID_CHKSUM,
    //! <b>8</b> - Telegram not valid
    NOT_VALID_TEL,
    //! <b>9</b> - Buffer full, no space in Tx or Rx buffer
    BUFF_FULL,
    //! <b>10</b> - Address is out of memory
    ADDR_OUT_OF_MEM,
    //! <b>11</b> - Invalid function parameter
    NOT_VALID_PARAM,
    //! <b>12</b> - Built in self test failed
    BIST_FAILED,
    //! <b>13</b> - Before entering power down, the short term timer had timed out.
    ST_TIMEOUT_BEFORE_SLEEP,
    //! <b>14</b> - Maximum number of filters reached, no more filter possible
    MAX_FILTER_REACHED,
    //! <b>15</b> - Filter to delete not found
    FILTER_NOT_FOUND,
    //! <b>16</b> - BaseID out of range
    BASEID_OUT_OF_RANGE,
    //! <b>17</b> - BaseID was changed 10 times, no more changes are allowed
    BASEID_MAX_REACHED,
    //! <b>18</b> - XTAL is not stable
    XTAL_NOT_STABLE,
    //! <b>19</b> - No telegram for transmission in queue
    NO_TX_TEL,
    //!	<b>20</b> - Waiting before sending broadcast message
    TELEGRAM_WAIT,
    //!	<b>21</b> - Generic out of range return
    OUT_OF_RANGE,
    //!	<b>22</b> - Function was not executed due to sending lock
    LOCK_SET,
    //! <b>23</b> - New telegram transmitted
    NEW_TX_TEL
} RETURN_TYPE;

//! Records enum structure for the API System Log  - DON'T CHANGE !
//>>Section:EO3000I-API:0x7E00
typedef enum
{
    //! There was no free serial fifo to store information
    ERR_ISRUARTRXTX_RX_OVERFLOW = 0,
    //! There was a UART RX interrupt lost by RMW problematic
    ERR_UART_RX_INT_LOST,
    //! There was a UART TX interrupt lost by RMW problematic
    ERR_UART_TX_INT_LOST,
    //! UART send buffer full
    ERR_UART_SEND_BUFFER_FULL,
    //! Obsolete since API 2.2.5.0 - No free buffer in the Rx radio buffers and no buffer could be released with maturity time 0xFF
    ERR_RADIORX_NO_FREE_BUFFER,
    //! No free buffer in the Tx radio buffers
    ERR_RADIOTX_NO_FREE_BUFFER,
    //! Obsolete since API 2.2.5.0 - Error in the rx pointers, this may happen if the rx state machine is reinitialised while reading telegram
    ERR_RADIORX_RX_PTR,
    //! Obsolete since API 2.2.5.0 - Wrong received telegram checksum
    ERR_RADIORX_CHKSUM,
    //! Obsolete since API 2.2.5.0 - The received telegram is shorter than the minimum size
    ERR_RADIORX_MINSIZE,
    //! Obsolete since API 2.2.5.0 - The rx pointer reached the security value fixed in the Maximum Packet Size
    ERR_RADIORX_MAXSIZE,
    //! Obsolete since API 2.2.5.0 - Telegram EOF not found
    ERR_RADIORX_EOF,
    //! Obsolete since API 2.2.5.0 - An inverse bit was not correct while decoding telegram
    ERR_RADIORX_DECGROUP,
    //! Error interrupt detected during Tx statemachine
    ERR_RADIORX_TXERRIRQ,
    //! Obsolete since API 2.2.5.0 - Radio LBT counter
    ERR_RADIOTX_LBT_L,
    ERR_RADIOTX_LBT_H,
    //! Obsolete since API 2.2.5.0 - Radio TX ignore LBT for fitting sub telegram timing
    ERR_RADIOTX_IGNORELBT,
    //! There is no free intermediate buffer, telegram dropped
    ERR_RADIORX_INTBUFFER,
    //! The length of the telegram to send is zero
    ERR_RADIOSEND_LENGTH_ZERO,
    //! The number of telegrams is not 1,2 or 3
    ERR_RADIOSEND_NUMB_SUBTEL_WRONG,
    //! The length of the telegram to send exceeds the radio buffer
    ERR_RADIOSEND_LENGTH_TOO_BIG,
    //! The id of the telegram to send is not in the range of the base id
    ERR_RADIOSEND_BASEID_WRONG,
    //! Task for flash operation was already occupied when whanted to change value. - called from interrupt
    SMACK_BUSY_TASKINT,
    //! Task for flash operation was already occupied when whanted to change value. - called from main
    SMACK_BUSY_TASKMAIN,
    //! Index of radio buffer where reclaim is stored was busy.
    SMACK_BUSY_RECLAIM_RADIO,
    //! Index of xram buffer where reclaim is stored was busy.
    SMACK_BUSY_RECLAIM_MB,
    //! Temporary mailbox was busy when wanted to use.
    SMACK_BUSY_TEMP,
    //! In Learn period two sensers wanted to be learn in.
    SMACK_DOUBLE_LRN,
    //! System works with unknown acknowledge .
    SMACK_WRONG_ACKCODE,
    //! System should learn out sensor - but there is no mailbox to delete.
    SMACK_NOTHIG_TO_DELETE,
    //! Write mailbox was called but no free mailbox available.
    SMACK_NO_FREE_MB,
    //! Smack needed to send telegram but there was no free buffer.
    SMACK_NO_BUFFER_TO_SEND,
    //! Temporary mailbox was timed out. This should never occur, because temp should be ready when reclaiming. When not somewhere the message was lost.
    SMACK_TEMP_TIMMED_OUT,
    //! No reclaim telegram was sent
    SMACK_RECLAIM_NOT_SENT,
    //! Wakeup of reclaim standby mode not by RX telegram
    SMACK_RECLAIM_WAKEUP_NOT_RX,
    //! No reclaim acknowledge received
    SMACK_RECLAIM_NO_ACK,
    //! Other message after reclaim received, not the expected reclaim acknowledge
    SMACK_RECLAIM_OTHER_MSG,
    //! Chained telegrams with different sequence received. Probably two controller communicating at the same time
    REMAN_MIX_SEQUENCE,
    //! Chained telegrams  was too long and did not fit to the REMAN buffer
    REMAN_BUFFER_OVERFLOW,
    //! error memory size, has to stay as the last enum,
    API_ERR_MEM_SIZE,
     //! reserved until 128 values
} API_ERRLOG;
//>>SectionEnd

//! System log allocated in API - DON'T CHANGE !


//! @}
/*********************************************************************************************/
/************************************ RADIO MODULE *******************************************/
/*********************************************************************************************/
/*!
\addtogroup radio_grp radio
Using the RADIO module the EnOcean protocol stack can be used. The radio module enables sending and receiving telegrams.\n
The module has radio functions for application like TCMxxx which are always supplied with voltage. These functions needs the
schedule in order to work correctly. The ULP functions are radio functions for energy autarkic devices like PTM or STM.
For more information about the radio protocol stack read the \ref erp_page chapter.

\ingroup ESSL
*/

//! @addtogroup radio_telegram_struct_grp Radio Telegram Structures
//! Structures that are used in RADIO module
//! \ingroup radio_grp
//! @{

//! Telegram choice codes applies to radio telegram only
typedef enum
{
    //! RPS telegram
    RADIO_CHOICE_RPS = 0xF6,
    //! 1BS telegram
    RADIO_CHOICE_1BS = 0xD5,
    //! 4BS telegram
    RADIO_CHOICE_4BS = 0xA5,
    //! HRC telegram
    RADIO_CHOICE_HRC = 0xA3,
    //! SYS telegram
    RADIO_CHOICE_SYS = 0xA4,
    //! SYS_EX telegram
    RADIO_CHOICE_SYS_EX = 0xC5,
    //! Smart Ack Learn Reuqest telegram
    RADIO_CHOICE_SM_LRN_REQ = 0xC6,
    //! Smart Ack Learn Answer telegram
    RADIO_CHOICE_SM_LRN_ANS = 0xC7,
    //! Smart Ack Reclaim telegram
    RADIO_CHOICE_RECLAIM = 0xA7,
    //! Smart Request telegram
    RADIO_CHOICE_SIGNAL = 0xD0,
    //! Encapsulated addressable telegram
    RADIO_CHOICE_ADT = 0xA6,
    //! Variable Length Data
    RADIO_CHOICE_VLD = 0xD2,
    //! Universal Teach In EEP based
    RADIO_CHOICE_UTE = 0xD4,
    //! Manufacturer Specific Communication
    RADIO_CHOICE_MSC = 0xD1,
    //! Chained  message
    RADIO_CHOICE_CDM = 0x40,
    //! Secure telegram	without choice encapsulation
    RADIO_CHOICE_SEC = 0x30,
    //! Secure telegram	with choice encapsulation
    RADIO_CHOICE_SEC_ENCAPS = 0x31,
    //! Non-secure telegram
    RADIO_CHOICE_NON_SEC = 0x32,
    //! Secure teach-in telegram
    RADIO_CHOICE_SEC_TI = 0x35,
    //! GenericProfiles Teach-in
    RADIO_CHOICE_GP_TI  = 0xB0,
    //! GenericProfiles Teach-in request
    RADIO_CHOICE_GP_TR = 0xB1,
    //! GenericProfiles Complete Data
    RADIO_CHOICE_GP_CD = 0xB2,
    //! GenericProfiles Selective Data
    RADIO_CHOICE_GP_SD = 0xB3,

} CHOICE_TYPE;


//! Status byte masks
typedef enum
{
    //! Bitmask for masking CRC vs CHECKSUM in status byte
    STATUS_CRC=              0x80,
    //! Bitmask for masking telegram generation bit in status byte
    STATUS_GENERATION =      0x20,
    //! Bitmask for masking normal/unassigned bit in status byte
    STATUS_ASSIGNED =        0x10,
    //! Bitmask for masking repeater / hop counter / path selection bits
    STATUS_REPEATER =        0x0F,

} STATUS_MASK;

//! Radio init parameters
typedef enum
{
    //! Trigger chains download
    TRIGGER_CHAINS=      0x00,
    //! Configure all chains and trigger download
    CFG_ALL       =      0x01,
    //! Configure analog0  chain and trigger download
    CFG_ANALOG0 =        0x02,
} RADIO_INIT_PARAM;


//!Destination broadcast ID, you can get the destination ID through TEL_PARAM_TYPE
#define  ENOCEAN_BROADCAST_ID       0xFFFFFFFF

//*********************RADIO PARAM***************************

#define RADIO_BUFF_NUM 10
#define RADIO_MATURITY_TIME 100

//#pragma pack(1)
//#pragma anon_unions
typedef union
{
    struct
    {
        uint8_t  u8AppVerInfo[4];
        uint8_t  u8ApiVerInfo[4];
        union
        {
            uint8_t  u8ChipIDInfo[4];
            uint32_t u32ChipID;
        };

        uint8_t  u8ChipVerInfo[4];
        uint8_t  u8AppDescriptionInfo[16];
        uint32_t u32BaseID;
        uint8_t  u8BaseIDRemainCycle;
        uint8_t  u8Reapter;
    };
    uint8_t u8Info[38];
} EnOceanHW_Typedef;

//!
typedef union
{
    struct
    {
        uint8_t u8Enable;
        uint8_t u8Level;
    };
    uint8_t u8Buff[2];
}EnoceanRPT_Typedef;
//!
typedef union
{
    struct
    {
        uint8_t u8Type;
        uint32_t u32Value;
        uint8_t u8Kind;
    };
    struct
    {
        uint8_t u8OnOff;
        uint8_t u8Operator;
    };
    uint8_t u8Buff[6];
}EnOceanFilter_Typedef;
//!
typedef union
{
    struct
    {
        uint8_t u8App[128];
        uint8_t u8Api[128];
    };
    uint8_t u8Buff[256];
}EnOceanSYS_LOG_Typedef;

//!
typedef union
{
    struct
    {
        uint8_t u8Type;
        uint32_t u32StartAddress;
        uint16_t u16Length;
        uint8_t u8Data[256];
    };
    uint8_t u8Buff[263];

}EnoceanMemory_Typedef;
//!
typedef union
{
    struct
    {
        uint8_t u8Level;
        uint8_t u8Key[4];
    };
    uint8_t u8Buff[5];

}EnOceanSecurity_Typedef;

//! TCM310 Hardware info
typedef struct
{
    EnOceanHW_Typedef    HW;
    EnoceanRPT_Typedef    RPT;
}EnoceanTCM310_Typedef;

/*******************************************************************/




//! Smart ack Learn Asnwer telegram datafield definition
typedef union
{
    //! Datafiled structure for message Learn reply
    struct answer_reply
    {
        uint16_t    u16ResponseTime;
        uint8_t     u8AckCode;
        uint32_t    u32SensorId;

    }answer_reply;
    //! Datafiled structure for message Learn reply
    struct answer_acknowledge
    {
        uint16_t    u16ResponseTime;
        uint8_t     u8AckCode;
        uint8_t     u8MailBoxIdx;

    }answer_acknowledge;
} smart_answer;

//! Telegram structure used for Radio transmission.
//! 报文结构用于无线电传输
typedef union
{
    struct raw_TEL_RADIO_TYPE
    {
        CHOICE_TYPE u8RORG;
        //! Telegram seen as a array of bytes without logical structure.
        uint8_t bytes[RADIO_BUFF_LENGTH];
        uint8_t  u8Status;

        //! Radio telegram length, it's not part of the transmitted/received , it is used only for processing the telegram
        uint8_t u8Length;
    } raw;

    struct rps_TEL_RADIO_TYPE
    {
        CHOICE_TYPE u8RORG;
        uint8_t u8Data;
        //! Telegram seen as a array of bytes without logical structure.
        uint8_t bytes[RADIO_BUFF_LENGTH];
        //uint32_t u32Id;
        uint8_t  u8Status;

        //! Radio telegram length, it's not part of the transmitted/received , it is used only for processing the telegram
        uint8_t u8Length;
    } RPS;
    //! SYS_EX radio telegram structure
    struct ReMan
    {
        //! Note the sequence is correct because Keil takes the bitfield from right to left. See telegram definition for more information
        uint16_t         u16FnNum;
        uint16_t         u16ManId;
        uint8_t          u8Data[RADIO_BUFF_LENGTH];


        uint8_t          u8Length;
    }ReMan;
    
    struct SmartAck
    {
        CHOICE_TYPE      u8RORG;
        uint8_t          u5ReqCode;
        uint16_t         u16ManId;  //制造商ID
        //uint16_t         u16ManId;
        //uint16_t         u5ReqCode: 5;

        uint8_t          u8ClientEEP_RORG;  //客户Rorg
        uint8_t          u8ClientEEP_FUN;   //客户EEP
        uint8_t          u8ClientEEP_TYPE;

        uint8_t          u8RssiDbm;
        uint32_t         u32PostMasterID;// with or without reapter
        //uint32_t         u32RepeaterId;
        uint32_t         u32ClientId;
        uint8_t          u8Status;
        uint8_t          u8HopCount;
        //uint8_t          u8Chk;
        uint8_t          u8LearnEnable;
        uint16_t         u16ResponseTime;
        uint8_t	         u8ConfirmCode;
        uint8_t          u8EventCause;
        uint8_t          u8ResetCause;
        uint8_t          u8EventCode;
        uint8_t          u8MailBoxIdx;

        uint8_t          u8PriorityOfPostMaster;
        //uint8_t          u8Fill[RADIO_BUFF_LENGTH-17];
    }SmartAck;
    
} TEL_RADIO_TYPE;


//! Telegram parameter structure
//! 报文参数结构
typedef union
{
    //! param structure for transmitted telegrams
    //! TX_参数结构发送报文
    struct p_tx
    {
        
        //! to send Destination ID
        //! 发送目的地ID
        uint32_t u32DestinationId;
        //! 源始ID
        uint32_t u32SourceId;
        //! 无线信号强度
        uint8_t  u8Dbm;
        //! number of subtelegrams to send
        //! subtelegrams发送的数量
        uint8_t  u8SubTelNum;
        //! 安全级别
        uint8_t  u8SecurityLevel;

    }p_tx;

    //! param structure for received telegrams
    //! RX_参数结构接收报文
    struct p_rx
    {
        
        //! received Destination ID
        //! 接收目的地ID
        uint32_t u32DestinationId;
        //! 源始ID
        uint32_t u32SourceId;
        //! u8Dbm of the last subtelegram calculated from RSSI. Note this value is an unsigned value. The real dBm signal is a negative value.
        //! 无线信号强度 真正的dBm信号是一个负值
        uint8_t  u8Dbm;
        //! number of subtelegrams received	(= number of originals + number of repeated)
        //! 收到的subtelegrams
        uint8_t  u8SubTelNum;
        //! 安全级别
        uint8_t  u8SecurityLevel;

    }p_rx;

    struct ParaReMan
    {
        //! 目的地ID
        uint32_t u32DestinationId;
        //! 源始ID
        uint32_t u32SourceId;
        //! 信号强度
        uint8_t  u8Dbm;
        //! 发送延时
        uint8_t  u8RandSendDelayEnable;
        
        //uint32_t u32DestID;
    }ReMan;


} TEL_PARAM_TYPE;


typedef void (*EnOceanFun_Typedef)(void);
typedef void (*EnOceanValue_Typedef)(uint16_t u16Value);

typedef struct
{
    uint16_t                u16ByteMax;
    uint8_t                 u8Buff[ESP3_TX_BUF_MAX];

    //uint8_t                 u8BusyState;
    uint16_t                u16ByteCnt;
    uint8_t                 u8State;
    uint16_t                u16OvfCnt;
    uint8_t                 u8RetransmissionCnt;
    uint16_t                u16IdleTime;
    uint8_t                 u8RandomEn;

    //EnOceanValue_Typedef    pStart;
    //EnOceanFun_Typedef      pStop;

}Esp3Tx_Typedef;

typedef struct
{
    uint16_t u16ByteMax;
    uint8_t  u8State;
    uint8_t  u8Buff[ESP3_RX_BUF_MAX];

}Esp3RxQueue_Typedef;

typedef struct
{
    Esp3RxQueue_Typedef Queue[ESP3_RX_QUEUE];
    
    /* */ 
    uint8_t  u8DMABuff[ESP3_RX_BUF_MAX];
    uint16_t u16DMABuffMax;
    /* Usart receive a byte once */
    uint16_t u16ByteCnt;
    uint8_t  u8BusyTime;
    uint8_t  u8RegData;

    
    uint8_t  u8QueueFull;
    uint8_t  u8PushCount;
    uint8_t  u8PopCount;
       
    

}Esp3Rx_Typedef;


typedef struct
{
    /****************RADIO_ERP1报文类型里的：Optional Data区 + u32SourceId****************/
    //! 参数
    TEL_PARAM_TYPE Param;
    
    /***************RADIO_ERP1报文类型里的：Data Type Radio e.g.type VLD区****************/
    //! 电报 报文
    TEL_RADIO_TYPE Telegram;
    

    //ReManSecurity_Typedef ReManSecurity;
    /**************************RADIO_ERP1报文类型里的：Header区**************************/
    //! 数据包类型
    uint8_t  u8PacketType;
    //! 接收缓冲区索引
    //uint8_t  u8RxBuffIndex;
    //! 数据长度
    uint16_t u16DataLength;
    //! 可选数据长度
    uint8_t u8OptionalDataLength;

    //void (*pFun)(void);
    //! 随机启用
    uint8_t u8ResponseState;

}Radio_Typedef;

//typedef 
typedef struct 
{
    uint8_t  u8Cmd;
    uint8_t  u8State;

    Radio_Typedef Data;
        
}EnoceanTxContent_Typedef;

/****************************************************************************************/
typedef struct 
{
    uint8_t  u8PushCount;
    uint8_t  u8PopCount;
    uint8_t  u8QueueFull;

    //uint16_t u16QueueClearOvfTime;

    EnoceanTxContent_Typedef Queue[ESP3_TX_QUEUE];
       
}EnoceanTxQueue_Typedef;

typedef struct
{
    uint8_t                 u8Lock;
    uint16_t                u16LockCount;

    uint16_t                u16SendPeriod;

    uint8_t                 u8ErrorCount;
    uint8_t                 u8Error;
    

    uint8_t                 u8LatestReceiveRssi;
    uint32_t                u32LatestReceiveID;
    uint32_t                u32DstID;
    uint32_t                u32ChipID;
    uint32_t                u32BaseID;
    uint32_t                *pu32RemanCode;
    uint8_t                 *pu8Reapter;
    uint8_t                 u8BaseIDRemainCycle;
    uint32_t                u32EEP;

    EnoceanTxQueue_Typedef  Tx;

    EnOceanValue_Typedef    pStart;
    EnOceanFun_Typedef      pStop;
    EnOceanValue_Typedef    pEnOceanError;
    EnOceanFun_Typedef      pEnOceanReset;

}EnOceanRun_Typedef;
/****************************************************************************************/
/* Read area */
/*
typedef struct
{

    uint32_t          u32ChipID;
    uint32_t          u32BaseID;
    uint32_t          *pu32RemanCode;
    uint8_t           *pu8Reapter;
    uint8_t           u8BaseIDRemainCycle;
    uint32_t          u32EEP;
    
    
    //EnOceanFun_Typedef   pEnOceanReset;
    //EnOceanValue_Typedef pEnOceanError;

}EnOceanHw_Typedef;
*/
//#pragma pack()

extern   Esp3Tx_Typedef         Esp3Tx;
extern   Esp3Rx_Typedef         Esp3Rx;

#define  REMAN_RANDOM_ENABLE    (1)
#define  REMAN_RANDOM_DISABLE   (0)





//***********************************RECLAIM TELEGRAM DEFINES

    //!First byte of encoded Reclaim Choice.
    #define RECLAIM_CHOICE_ENCODED_B0   0xA2
    //!Second byte of encoded Reclaim Choice.
    #define RECLAIM_CHOICE_ENCODED_B1   0xD0
//***********************************RECLAIM TELEGRAM DEFINES END
/*!\}*/

/*!  \name Reclaim telegram defines
    For faster Reclaim telegram processing we access telegram  with pointer and relative possition. Defines are constant.
    Also masks to separate reclaim type from mailbox index are listened.
 */
/*!\{*/
//***********************************RECLAIM TELEGRAM DEFINES
    //!Possition of the reclaim type.
    #define REC_TYPE_POS                1
    //!Possition of the Source Id.
    #define REC_SRC_ID_POS              2
    //!Mask to get relcaim type
    #define REC_TYPE_MASK               0x80
    //!Mask to get mailbox index
    #define REC_MBIDX_MASK              0x7F
//***********************************RECLAIM TELEGRAM DEFINES   END
/*!\}*/

/*!  \name Learn request telegram defines
    For faster Learn Request telegram processing we access telegram  with pointer and relative possition. Defines are constant.
*/
/*!\{*/
//***********************************LEARN REQUEST TELEGRAM DEFINES
    //!Possition of the learn request .
    #define LRN_REQ_REQ_CODE_POS        1
    //!Possition of the EEP.
    #define LRN_REQ_EEP_POS             5
    //!Possition of the RSSI.
    #define LRN_REQ_RSSI_POS            6
    //!Possition of the Candidate Id.
    #define LRN_REQ_CANDIDATE_POS       7
    //!Possition of the source Id.
    #define LRN_REQ_SRC_ID_POS          (RADIO_DEC_LENGTH_SM_LRN_REQ-LEN_SRCID_STAT_CHCK)
    //!Possition of the status field
    #define LRN_REQ_STATUS_POS          (RADIO_DEC_LENGTH_SM_LRN_REQ-2)
//***********************************LEARN REQUEST TELEGRAM DEFINES	END
/*!\}*/

/*!  \name Learn answer telegram defines
    For faster Learn answer telegram processing we access telegram  with pointer and relative possition. Defines are constant.
    Learn answer can encapsulate Learn Reply or Learn Acknowledge.
*/
/*!\{*/
//***********************************LEARN REQUEST TELEGRAM DEFINES
    //!Possition of the message index.
    #define LRN_ANS_MSG_IDX_POS             1
    //!Possition of the response time.
    #define LRN_ANS_RESPONSE_TIME_POS       2
    //!Possition of Acknowledge
    #define LRN_ANS_ACK_CODE_POS            4
    //!Possition of Sensor Id in Learn Reply
    #define LRN_ANS_REP_SENSOR_ID_POS       5
    //!Possition of Mailbox Index in Learn Acknowledge
    #define LRN_ANS_ACK_MB_IDX_POS          5
//***********************************LEARN REQUEST TELEGRAM DEFINES	END
/*!\}*/

/*!  \name Learn request  defines
    In Learn Request telegram Learn Request  share one byte with Manufacturer Id. For accessing values we use bite masks and bit operations.
 */
/*!\{*/
//***********************************LEARN REQUEST CODES DEFINES
    //!Request  mask of the sharing byte in learn request telegram with Manufacturer Id.
    #define REQ_CODE_MASK               0xF8
    //!Manufacturer Id mask of the sharing byte in learn request telegram with request .
    #define MAN_CODE_MASK               0x07
    //!Default request  send by Sensor.
    #define SENSOR_DEFAULT_REQ_CODE     0x1F
//***********************************LEARN REQUEST CODES END


//*****************************PRIORITY FLAGS
/*
    #define PF_LOCAL                0x1
    #define PF_RSSI_OK              0x2
    #define PF_PLACE_OK             0x4
    #define PF_PM                   0x8
    #define PF_REP                  0x10
    */
//*****************************PRIORITY FLAGS END
/*!\}*/

/*!  \name Learn acknowledge  defines
    Learn Acknowledge  is separated into main and second part. The main part idetify the operation and the second gives additional infromation
    about it. For accessing main and second part we use bit masks and bit operations.
*/
/*!\{*/
//***********************************LEARN ACKNOWLEDGE CODE
    //!Main acknowledge  for Learn In.
    #define ACK_CODE_LEARN_IN                   0x00
    //!Main acknowledge  for discard Learn In.
    #define ACK_CODE_LEARN_DISCARD              0x10
    //!Main acknowledge  for Learn Out.
    #define ACK_CODE_LEARN_OUT                  0x20
    //!Mask for main acknowledge .
    #define ACK_CODE_MAIN_MASK                  0xF0
    //!Mask for second acknowledge .
    #define ACK_CODE_SECOND_MASK                0x0F
//***********************************LEARN ACKNOWLEDGE CODES
/*!\}*/

/*!  \name Discard reason defines
    Discard reason gives more infromation about the reason why was the LearnIn discarted. It is saved in second part of a Learn Acknowledge .
 */
/*!\{*/
//***********************************DISCARD REASON
    //!Second acknowledge  for discard Learn In - EEP not accepted.
    #define ACK_CODE_EEP_NOT_ACCEPTED           0x01
    //!Second acknowledge  for discard Learn In - declared Post Master has no place for next MailBox.
    #define ACK_CODE_PM_NO_PLACE                0x02
    //!Second acknowledge  for discard Learn In - Controller has no place to Learn In next Sensor.
    #define ACK_CODE_CONTROLLER_NO_PLACE        0x03
    //!RSSI was not good enough.
    #define ACK_CODE_NO_GOOD_RSSI               0x04

//***********************************DISCARD REASON END

/*!\}*/

/*!  \name learn mode defines
    Learn modes of smart ack controller.
 */
/*!\{*/
//***********************************DISCARD REASON
    //!Simple learnmode is used, when only Smart Ack Controller should be selected as postmaster. All learn requests received by repeater will be ignored.
    #define SIMPLE_LEARNMODE                    0x00
    //!Advanced learnmode is used, when also repeater can be selected as postmaster. But when Controller reaches sensor, controller is selected.
    #define ADVANCED_LEARNMODE                  0x01
    //!Anvanced learnmode select repeater is used, when always the best available repeater will be selected as postmaster. Controller is only selected, when no repeater is in system.
    #define ADVANCED_LEARNMODE_SELECT_REPEATER  0x02

//***********************************DISCARD REASON END


/*!\{*/
    //!Code for no MailBox found.
    #define NO_MAILBOX_FOUND        0xFF
    //! Maximum value of response time [ms] - in case of LRN reclaim it must be at least 500
    #define MAX_RESPONSE_TIME       550























//无线_类型定义

/*********************************************************************************************/
/************************************ FILTER FUNCTION PROTOTYPES ******************************/
/*********************************************************************************************/

/*!
\addtogroup filter_grp  filter
The FILTER module is used to filter received telegrams according:
- ID (source or destination)
- CHOICE
- dBm

When the filter is active telegrams which matches to the  specified with the
filter module are dropped and the application does not receive them. Independently the filters
can be defined for repeating functionality to realize a selected by filter repeating.
\ingroup ESSL
Note:IDX_FILTER_OPERATOR is valid for all filters!!
Note:FILTER_KIND=APPLY => BLOCK all other type of Telegrams.
*/

//! @addtogroup filter_cfg_grp FILTER config parameters
//! Filter initialization parameters. The first enumeration member = 0, the next = 1, etc
//! \ingroup filter_grp
//! @{
//! Filter initialization parameter indexes
typedef enum
{
    //! Maximum number of filters [ro]
    IDX_FILTER_MAX = 0,
    //! Operator of all filters:FILTER_ALL_AND or FILTER_ALL_OR
    //! When using more filters, each filter has to be seen as a logical object with boolean
    //! result. These rsults are then all computed with the adjusted operator AND or OR.
    //! F.e., the operator AND is only sensfull when using different filter types
    //! The operator OR is useful to filter some learned IDs, when only they are allowed.
    IDX_FILTER_OPERATOR
} FILTER_PARAM_IDX;
//! @}

//! @addtogroup filter_struct_grp FILTER structures
//! Structures that are used in the filter module
//! \ingroup filter_grp
//! @{
typedef enum
{
    //! Filter has type source ID
    FILTER_TYPE_ID=0,
    //! Filter has type source ID. Same as FILTER_TYPE_ID. Use FILTER_TYPE_SOURCE_ID for new applications
    FILTER_TYPE_SOURCE_ID=FILTER_TYPE_ID,
    //! Filter has type RORG
    FILTER_TYPE_RORG,
    //! Filter has type Choice (same as RORG), use FILTER_TYPE_RORG for new applications
    FILTER_TYPE_CHOICE=FILTER_TYPE_RORG,
    //! Filter has type DBM
    FILTER_TYPE_DBM,
    //! Filter has type destination ID
    FILTER_TYPE_DESTINATION_ID
} FILTER_TYPE;

typedef enum
{
    //! Filter blocks criteria to application interface	(#radio_getTelegram)
    FILTER_KIND_BLOCK=0x00,
    //! Filter applies criteria to application interface (#radio_getTelegram)
    FILTER_KIND_APPLY=0x80,
    //! Filter blocks criteria for repeating
    FILTER_KIND_BLOCK_REP=0x40,
    //! Filter applies critera for repeating
    FILTER_KIND_APPLY_REP=0xC0
}FILTER_KIND;

//! IDX_FILTER_OPERATOR OR  applying for all filters
#define FILTER_ALL_OR  0
//! IDX_FILTER_OPERATOR AND applying for all filters
#define FILTER_ALL_AND 1
//! IDX_FILTER_OPERATOR AND for repeating and OR for radio interface
#define FILTER_REP_AND_RADIO_OR 8
//! IDX_FILTER_OPERATOR OR for repeating and AND for radio interface
#define FILTER_REP_OR_RADIO_AND 9
//! @}

//! @addtogroup filter_fn_grp FILTER functions


//! @}






//! @}

//! @addtogroup mem_fn_grp MEMORY functions
//! \copydetails mem_grp
//! \ingroup mem_grp
//! @{

/*********************************************************************************************/
/************************  MESSAGE TRANSMISSION DEFINES AND PROTOTYPES ***********************/
/*********************************************************************************************/
/*!
\addtogroup msg_grp  msg
The message module allows to send longer radio message by using telegram chaining functionality.
\ingroup ESSL
*/

//! @addtogroup msg_cfg_grp Message module structures
//! Message structures.
//! \ingroup msg_grp
//! @{

//! Message Type
typedef struct
{
    //! Message type.
    uint8_t     u8RORG;
    //! Source ID
    uint32_t    u32SourceId;
    //! The length of the u8Data
    uint16_t    u16Length;
    //! The maximal length of the u8Data
    uint16_t    u16MaxLength;
    //! Data buffer
    uint8_t     *u8Data;
} MESSAGE_TYPE;

//! Message Module Parameters
typedef struct
{
    //! Maximal time between two radio telegrams in chain [ms]. Default = 100
    uint16_t    u16ReceiveTimeout;
    //! Delay between two send radio telegrams in [ms]. Default = 40 ms
    uint16_t    u16SendDelay;
} MESSAGE_PARAM;
//! @}







//! @}

//************************ END FUNCTION PROTOTYPES **********************


/*********************************************************************************************/
/************************************ SECURITY MODULE *******************************************/
/*********************************************************************************************/
/*!
\addtogroup sec_grp sec
Security module. The module's functions are responsible for the encryption, decryption, authentication of messages.
Several encryption algorithms like AES128 and ARC4 can be used.
Rolling  strategy is also included to avoid replay attacks.\n\n

A detail description of the security protocol and secure strategies implemented can be read under http://www.enocean.com/en/knowledge-base/
\ingroup ESSL
*/

//! @addtogroup sec_struct_grp Secure module structures	and constants
//! Data structures and constant values that are used in SECURITY module
//! \ingroup sec_grp
//! @{

//! Amount of bytes of the CMAC subkeys
#define  CMAC_SUBKEY_SIZE       16


//! \name teach-in info byte bit masks
//! @{
//! INFO field bit mask in teach-in info byte
#define  TEACH_IN_TYPE_MASK     0x0C
//! INFO field bit mask in teach-in info byte
#define  TEACH_IN_INFO_MASK     0x03
//! @}


//! \name Teach-in info byte fields values
//! @{
//! Non-specific type identification
#define  TEACH_IN_TYPE_NON_SPEC 0x00
//! PTM type identification
#define  TEACH_IN_TYPE_PTM      0x04
//! PTM info first rocker
#define  TEACH_IN_INFO_ROCKER_A 0x00
//! PTM info second rocker
#define  TEACH_IN_INFO_ROCKER_B 0x01
//! @}


//! \name SLF byte bit masks
//! @{
//! Rolling  algorithm identification bit mask in SLF byte
#define  SLF_RLC_ALGO_MASK      0xC0
//! Rolling  send/not send bit mask in SLF byte
#define  SLF_RLC_TX_MASK        0x20
//! Message authentication  identificator bit mask in SLF byte.
#define  SLF_MAC_ALGO_MASK      0x18
//! Encryption identificator bit mask.
#define  SLF_DATA_ENC_MASK      0x07
//! @}


//! \name SLF byte fields values
//! @{
//! No rolling  identification
#define  SLF_NO_RLC_ALGO        0x00
//! 16-bit rolling  identification
#define  SLF_RLC_16_BIT         0x40
//! 24-bit rolling  identification
#define  SLF_RLC_24_BIT         0x80
//! Not sending rolling  in telegram identification
#define  SLF_RLC_TX_NO          0x00
//! Sending rolling  in telegram identification
#define  SLF_RLC_TX_YES         0x20
//! No athentication in telegram identification
#define  SLF_MAC_NO             0x00
//! 3-byte MAC identification
#define  SLF_MAC_3_AES128       0x08
//! 4-byte MAC identification
#define  SLF_MAC_4_AES128       0x10
//! No encryption identification
#define  SLF_ENC_NO             0x00
//! ARC4 encryption identification
#define  SLF_ENC_ARC4           0x02
//! Variable AES128  encryption identification
#define  SLF_ENC_VAES128        0x03
//! AES128  encryption identification
#define  SLF_ENC_AES128         0x04
//! @}


//!Security module function return values.
typedef enum
{
    SEC_OK   = 0,               //!< function correctly executed.
    SEC_RLC_OUT_OF_RANGE,       //!< Received rolling  out of range.
    SEC_SIZE_WRONG,             //!< One of the parameters had a not permitted amount of bytes.
    SEC_CMAC_WRONG,             //!< Received and expected CMAC do not match.
    SEC_CHOICE_WRONG,           //!< Message choice not valid.
    SEC_ENC_WRONG,              //!< Encryption method  in SLF byte not allowed.
    SEC_SLF_WRONG,              //!< Not valid SLF .

}SEC_RESULT;

//!Security information structure.
typedef struct
{
    uint8_t     u8TeachInInfo;          //!< Teach-in info byte : | 4: RESERVED | 2: TYPE | 2: INFO |. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
    uint8_t     u8SLF;                  //!< Security layer format byte : | 2: RLC_ALGO | 1: RLC_TX | 2: MAC_ALGO | 3: DATA_ENC |. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
    uint32_t    u32RLC;                 //!< Rolling  value. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
    uint8_t     u8Key[16];              //!< Encryption/decryption key. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
    uint8_t     u8KeySize;              //!< Size of the key in bytes. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
    uint8_t     u8CMACsubkey1[16];      //!< Subkey1 for the CMAC calculation. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
    uint8_t     u8CMACsubkey2[16];      //!< Subkey2 for the CMAC calculation. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.

}SECU_TYPE;

//! @}


/*********************************************************************************************/
/************************************ REPEATER FUNCTION PROTOTYPES ********************************/
/*********************************************************************************************/
/*!
\addtogroup rep_grp  rep
The REP module is used for the repeater functionality of Dolphin. For more information be sure to read \ref repeater_page
The initialization of the REP module  is done through Dolphin Studio. The generated settings are saved to the file EO3000I_CFG.h.

\note
By default, repeating functionality is switched OFF.

\note
For the repeater module to work the scheduler has to run. For more information read \ref time_grp module.


\ingroup ESSL
*/

//! @addtogroup rep_cfg_grp REP config parameters
//! REP initialization parameters.
//! \ingroup rep_grp
//! @{
//! REP initialization parameter indexes
typedef enum
{
    IDX_REP_ENABLE = 0,
    IDX_REP_LEVEL
} REP_PARAM_IDX;

//! Repeater disabled
#define REP_DISABLED            0
//! Repeater enabled
#define REP_ENABLED             1
//! Repeater enabled filtered
#define REP_ENABLED_FILTERED    2
//! @}


// All the visible modules group definitions are done here so that when the library is compilled this groups stay
// The modules that are used only inside the api are not visible here (i.e. proc_)

/**
*  @ingroup ESSL
*/

/************************* API INTERFACE RELATED TYPES/STRUCTURES/PARAMETERS ***************************/

#define DEBUG_ERRRAWTEL


//! @}

/*********************************************************************************************/
/************************************ SMART ACKNOWLEDGE FUNCTION PROTOTYPES ********************************/
/*********************************************************************************************/
/*!
    \addtogroup smack_grp  smart ack
    The smack module enables Smart Acknowledge functionality for Controller, Repeater and Sensor in Dolphin API. Functions handle all time and energy critical
    parts of communication. The functions for line powered Smack Acknowledge actors are same. Controller and Repeater use the same functions, but Controller can
    addtioanlly learn Sensors so it uses special functions for this purpose.
    \n\n
    The initialization of the SMACK module is done through Dolphin Studio. The generated settings are saved to the file EO3000I_CFG.h.
    \n\n
    \note
    By default, smack functionality is switched OFF.
    \note
    If the repeater is active and has enabled SmartACK postmaster functionality, telegrams located in the mailbox of the postmaster
    are not available for the application. These telegrams are filtered on the lower API layers and are not
    received by radio_getTelegram.

    \ingroup ESSL
*/

//! @addtogroup smack_cfg_grp Smart Acknowledge initial parameters
//! Smack initialization parameters.
//! \ingroup smack_grp
//! @{

//! Smart Ack initialization parameter indexes
typedef enum
{
    //! Maximum number of mailboxes [ro]
    IDX_MAILBOX_COUNT = 0,
    //! Flash address for mailbox storage  [ro]
    IDX_MAILBOX_FLASH_ADDR
} SMACK_PARAM_IDX;

//! @}


//! @addtogroup smack_fn_grp Smart Acknowledge functions
//! \copydetails smack_grp
//! \ingroup smack_grp

//! @{

/*!	 \name Reclaim choice encoded defines
    Defines are used for checking in radio_tx for reclaim telegrams.
 */
/*!\{*/
//***********************************RECLAIM TELEGRAM DEFINES

    //!First byte of encoded Reclaim Choice.
    #define RECLAIM_CHOICE_ENCODED_B0   0xA2
    //!Second byte of encoded Reclaim Choice.
    #define RECLAIM_CHOICE_ENCODED_B1   0xD0
//***********************************RECLAIM TELEGRAM DEFINES END
/*!\}*/

/*!  \name Reclaim telegram defines
    For faster Reclaim telegram processing we access telegram  with pointer and relative possition. Defines are constant.
    Also masks to separate reclaim type from mailbox index are listened.
 */
/*!\{*/
//***********************************RECLAIM TELEGRAM DEFINES
    //!Possition of the reclaim type.
    #define REC_TYPE_POS                1
    //!Possition of the Source Id.
    #define REC_SRC_ID_POS              2
    //!Mask to get relcaim type
    #define REC_TYPE_MASK               0x80
    //!Mask to get mailbox index
    #define REC_MBIDX_MASK              0x7F
//***********************************RECLAIM TELEGRAM DEFINES END
/*!\}*/

/*!  \name Learn request telegram defines
    For faster Learn Request telegram processing we access telegram  with pointer and relative possition. Defines are constant.
*/
/*!\{*/
//***********************************LEARN REQUEST TELEGRAM DEFINES
    //!Possition of the learn request .
    #define LRN_REQ_REQ_CODE_POS        1
    //!Possition of the EEP.
    #define LRN_REQ_EEP_POS             5
    //!Possition of the RSSI.
    #define LRN_REQ_RSSI_POS            6
    //!Possition of the Candidate Id.
    #define LRN_REQ_CANDIDATE_POS       7
    //!Possition of the source Id.
    #define LRN_REQ_SRC_ID_POS          (RADIO_DEC_LENGTH_SM_LRN_REQ-LEN_SRCID_STAT_CHCK)
    //!Possition of the status field
    #define LRN_REQ_STATUS_POS          (RADIO_DEC_LENGTH_SM_LRN_REQ-2)
//***********************************LEARN REQUEST TELEGRAM DEFINES END
/*!\}*/

/*!  \name Learn answer telegram defines
    For faster Learn answer telegram processing we access telegram  with pointer and relative possition. Defines are constant.
    Learn answer can encapsulate Learn Reply or Learn Acknowledge.
*/
/*!\{*/
//***********************************LEARN REQUEST TELEGRAM DEFINES
    //!Possition of the message index.
    #define LRN_ANS_MSG_IDX_POS             1
    //!Possition of the response time.
    #define LRN_ANS_RESPONSE_TIME_POS       2
    //!Possition of Acknowledge
    #define LRN_ANS_ACK_CODE_POS            4
    //!Possition of Sensor Id in Learn Reply
    #define LRN_ANS_REP_SENSOR_ID_POS       5
    //!Possition of Mailbox Index in Learn Acknowledge
    #define LRN_ANS_ACK_MB_IDX_POS          5
//***********************************LEARN REQUEST TELEGRAM DEFINES	END
/*!\}*/

/*!  \name Learn request  defines
    In Learn Request telegram Learn Request  share one byte with Manufacturer Id. For accessing values we use bite masks and bit operations.
 */
/*!\{*/
//***********************************LEARN REQUEST CODES DEFINES
    //!Request  mask of the sharing byte in learn request telegram with Manufacturer Id.
    #define REQ_CODE_MASK               0xF8
    //!Manufacturer Id mask of the sharing byte in learn request telegram with request .
    #define MAN_CODE_MASK               0x07
    //!Default request  send by Sensor.
    #define SENSOR_DEFAULT_REQ_CODE     0x1F
//***********************************LEARN REQUEST CODES END
/*!\}*/

/*!  \name Priority flags defines
    Priority of the Post Master Candidate is evaluated by a hierarchically priority system. So the Flag bits have also a priority.
    The highest priority has the already post master flag. At the end the highest priority is taken as result. In evaluation process
    the flags are used to set the properities:
    <ol>
        <li>
        ALREDY POST MASTER / CANDIDATE
        </li>
        <li>
        PLACE FOR NEXT MAILBOX / NO PLACE FOR NEXT MAILBOX
        </li>
        <li>
        GOOD RSSI / NOT GOOD RSSI
        </li>
        <li>
        LOCAL / REMOTE
        </li>
    </ol>

    \note TRUE - 1 means the first choice

 */
/*!\{*/

//*****************************PRIORITY FLAGS
/*
    #define PF_LOCAL                0x01
    #define PF_RSSI_OK              0x02
    #define PF_PLACE_OK             0x04
    #define PF_PM                   0x08
    #define PF_REP                  0x10
    */
//*****************************PRIORITY FLAGS END
/*!\}*/

/*!  \name Learn acknowledge  defines
    Learn Acknowledge  is separated into main and second part. The main part idetify the operation and the second gives additional infromation
    about it. For accessing main and second part we use bit masks and bit operations.
*/
/*!\{*/
//***********************************LEARN ACKNOWLEDGE CODE
    //!Main acknowledge  for Learn In.
    #define ACK_CODE_LEARN_IN                   0x00
    //!Main acknowledge  for discard Learn In.
    #define ACK_CODE_LEARN_DISCARD              0x10
    //!Main acknowledge  for Learn Out.
    #define ACK_CODE_LEARN_OUT                  0x20
    //!Mask for main acknowledge .
    #define ACK_CODE_MAIN_MASK                  0xF0
    //!Mask for second acknowledge .
    #define ACK_CODE_SECOND_MASK                0x0F
//***********************************LEARN ACKNOWLEDGE CODES
/*!\}*/

/*!  \name Discard reason defines
    Discard reason gives more infromation about the reason why was the LearnIn discarted. It is saved in second part of a Learn Acknowledge .
 */
/*!\{*/
//***********************************DISCARD REASON
    //!Second acknowledge  for discard Learn In - EEP not accepted.
    #define ACK_CODE_EEP_NOT_ACCEPTED           0x01
    //!Second acknowledge  for discard Learn In - declared Post Master has no place for next MailBox.
    #define ACK_CODE_PM_NO_PLACE                0x02
    //!Second acknowledge  for discard Learn In - Controller has no place to Learn In next Sensor.
    #define ACK_CODE_CONTROLLER_NO_PLACE        0x03
    //!RSSI was not good enough.
    #define ACK_CODE_NO_GOOD_RSSI               0x04

//***********************************DISCARD REASON END

/*!\}*/

/*!  \name learn mode defines
    Learn modes of smart ack controller.
 */
/*!\{*/
//***********************************DISCARD REASON
    //!Simple learnmode is used, when only Smart Ack Controller should be selected as postmaster. All learn requests received by repeater will be ignored.
    #define SIMPLE_LEARNMODE                    0x00
    //!Advanced learnmode is used, when also repeater can be selected as postmaster. But when Controller reaches sensor, controller is selected.
    #define ADVANCED_LEARNMODE                  0x01
    //!Anvanced learnmode select repeater is used, when always the best available repeater will be selected as postmaster. Controller is only selected, when no repeater is in system.
    #define ADVANCED_LEARNMODE_SELECT_REPEATER  0x02

//***********************************DISCARD REASON END

/*!\}*/


/*!	 \name Other defines
 */
/*!\{*/
    //!Code for no MailBox found.
    #define NO_MAILBOX_FOUND        0xFF
    //! Maximum value of response time [ms] - in case of LRN reclaim it must be at least 500
    #define MAX_RESPONSE_TIME 550
/*!\}*/
    //!Smart Acknowledge result used in Controller and Sensor application to indicate return or status.
    typedef enum
    {
        SMACK_OK     = 0,   //!<Ok message.
        NO_MORE_MAILBOX,    //!<No more free MailBox available.
        FLASH_FAILURE,      //!<Flash write or read failure.
        NO_RECLAIM_MESSAGE, //!<No reclaim message received.
        COLLECTING,         //!<Module is collecting learn request telegrams.
        RESULT_READY,       //!<Result from learn request collecting process is ready.
        NO_RESULT,          //!<No result from learn request collecting process is ready.
        LEARN_ON_SIMPLE,    //!<Module is in simple Learn Mode.
        LEARN_ON_ADVANCED,  //!<Module is in advanced Learn Mode.
        LEARN_TIMEOUT,      //!<Module just switched of the Learn Mode because of learn period timeout.
        OTHER_MESSAGE       //!<Received other radio telegram while reclaim
    }SMACK_RESULT;

    //!Signal telegram message index.
    typedef enum
    {
        RESERVED     = 0,           //!<RESERVED.
        MAILBOX_EMPTY,              //!<Smart acknowledge - reclaimed mailbox is empty.
        MAILBOX_DOES_NOT_EXIST,     //!<Smart acknowledge - reclaimed mailbox does not exists.
        MAILBOX_RESET               //!<Smart acknowledge - rest learn process.

    }SIGNAL_INDEX;

    //!Smart acknowledge reclaim type.
    typedef enum
    {
        LEARN_RECLAIM = 0,  //!<Learn reclaim type.
        DATA_RECLAIM        //!<Data reclaim type.

    }SMACK_RECLAIM_TYPE;

    //!Smart acknowledge learn answer telegram message index.
    typedef enum
    {
        LRN_REP = 1,        //!<Learn reply message index.
        LRN_ACK             //!<Learn acknowledge message index.

    }LRN_MSG_IDX;

    //!Smart acknoweldge mailbox handling task.
    typedef enum
    {
        NOTHING  = 0,       //!<Do nothing.
        ADD_MB,             //!<Add MailBox.
        DELETE_MB           //!<Delete MailBox.

    }SMACK_TASK;

    //!Smart acknowledge learn result structure. It is used to Controller to evalute learn result.
    typedef struct
    {
        uint8_t         u8Priority ;    //!<Priority of the PostMaster candidate.
        uint8_t         u8ManId_byte1;  //!<Manufacturer Id byte 1 of the learned Sensor.
        uint8_t         u8ManId_byte0;  //!<Manufacturer Id byte 0 of the learned Sensor.
        uint8_t         u8EEP_byte2;    //!<EEP byte 2 of the learned Sensor.
        uint8_t         u8EEP_byte1;    //!<EEP byte 1 of the learned Sensor.
        uint8_t         u8EEP_byte0;    //!<EEP byte 0 of the learned Sensor.
        uint8_t         u8dBm;          //!<Rssi in dBm of the Learn Request telegram received by candidate.
        uint32_t        u32CandidateId; //!<Id of Candidate for PostMaster for learned Sensor.
        uint32_t        u32SensorId;    //!<Id of the learned Sensor.
        uint8_t         u8HopCount;     //!<Hop count from candidate to controller.

    }LEARN_RESULT;

    //*****************************MAILBOX STRUCTURES
    //!Strucutre for memory occupied by MailBoxes in flash.
    typedef struct
    {
        uint32_t u32SensorId;       //!<MailBox Sensor Id.
        uint32_t u32ControllerId;   //!<MailBox Controller Id.
        uint8_t  u8MBIndex;         //!<Index of the MailBox.

    }MAILBOX_FLASH;

    //!Strucutre for memory occupied by MailBox in xram.
    typedef struct
    {
        uint32_t u32Timer;                      //!<Timer for MailBox. Used for MailBox period.
        uint8_t  u8Length;                      //!<Length of saved Mail.
        uint8_t  u8Bytes[RADIO_BUFF_LENGTH];    //!<Saved Mail for Sensor. Default length defined by radio buffers.
    }MAILBOX_XRAM;
//*****************************MAILBOX STRUCTURES END

    //! Variable determines the MailBox that should be writen/deleted as next. It is a intern variable of smack module. It is only avaivable because of Remote Management.
    extern volatile MAILBOX_FLASH               gMbfAct;
    //! Variable determines operation that should be perfomed with #gMbfAct. It is a intern variable of smack module. It is only avaivable because of Remote Management.
    extern volatile SMACK_TASK                  gSmTask;
    extern volatile uint8_t                     u8gGERssiDbm;




 //! Paramter indexes for initalization.
typedef enum
{
    //!Index of EEP Byte0 and Byte1
    IDX_EEP_BYTE0_BYTE1=0,
    //!Index of EEP Byte2
    IDX_EEP_BYTE2,
    //!Product manufacturer
    IDX_MANUFACTURERID,
    //!Index for buffer length. It determines how much memory space the application dedicated to remote management buffer for message merging.
    //!It also determines what is the biggest message to receive.
    IDX_BUFF_SIZE,
    //! Memory  adress where the 4byte Code is saved [ro]
    IDX_CODE_ADDR,
    //! Minimum delay between two chained telegrams in message.
    IDX_TEL_DELAY
} RM_PARAM_IDX;

//! Paramter indexes for call back function intialization.
typedef enum
{
    //! Index for action function call back. [ro]
    IDX_PF_ACTION_COMMAND,
    //! Index for write  function call back. [ro]
    IDX_PF_CODE_WRITE
} RM_CALLBACKS_IDX;

//! @}


//! @addtogroup reman_fn_grp Remote management functions
//! \copydetails reman_grp
//! \ingroup reman_grp

//! @{

 /*!    \name System defines
    These defines are system specific.
 */
/*!\{*/
//***********************************RM SYSTEM DEFINES
#if 0
    //! Default Manufacturer ID.
    #define  RM_DEFAULTMANID                      0x7FF
    //! Default EEP.
    #define  RM_DEFAULTEEP                        0x000
    //!Begin of the answer function codes.
    #define RM_ANSWER_START                       0x600
    //! Value from which rpc codes begin.
    #define RM_RPC_START                          0x200
    //! Initial value of a blank flash page.
    #define LOCK_INIT_VALUE                       0xFFFFFFFF
    //! Return value when user application does not do anything further.
    #define EXIT_NO_FURTHER_ANALYSIS              0x00
#endif
//***********************************REMAN SYSTEM DEFINES END
/*!\}*/


 /*!    \name Enums
    Enums used in remote management module.
 */
/*!\{*/

//! Learn flags for RMCC remote learn.
typedef enum
{

    START_LEARN = 0x01,         //!<Defines to enable learn mode.
    NEXT_CHANNEL,               //!<Defines to jump to next chanell.
    STOP_LEARN,                 //!<Defines to stop the actual learn mode.
    SMACK_START_SIMPLE_LEARN,   //!<Defines to start Smart Ack simple learn mode, can be applied only on modules where SMACK is implemented.
    SMACK_START_ADVANCED_LEARN, //!<Defines to start Smart Ack advanced learn mode, can be applied only on modules where SMACK is implemented.
    SMACK_STOP_LEARN            //!<Defines to stop Smart Ack learn mode, can be applied only on modules where SMACK is implemented.
}RM_LEARN_FLAG;



//! Remote manager function codes
typedef enum
{
    MB_SETTINGS = 0x01,                 //!<Read out mail box settings.
    LEARNED_SENSORS_CONTROLLER          //!<Read out learned sensors. Only from controller.

}SETTINGS_TYPE;

//! Smack write settings operation types
typedef enum
{
    ADDFLASH_MB = 0x01,                 //!<Defines to add a specified Mail Box.
    DELETEFLASH_MB,                     //!<Defines to delete a specified Mail Box.
    LEARNIN,                            //!<Defines to Learn In a specified sensor. Only controller.
    LEARNOUT                            //!<Defines to Learn Out a specified sensor. Only controller.

}OPERATION_TYPE;


#endif
