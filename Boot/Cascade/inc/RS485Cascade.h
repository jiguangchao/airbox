
#ifndef _RS485_CASCADE_H_
#define _RS485_CASCADE_H_

#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"
#include "RS485CascadeQueue.h"
/********************************************************************************************/
/********************************************************************************************/
//#define CASCADE_TX_QUEUE_MAX                                          (10)
/********************************************************************************************/
/********************************************************************************************/
#define CASCADE_CMD_ENOCEAN_RADIO_MASTER_2_SLAVE                      (0xF0)
#define CASCADE_CMD_ENOCEAN_RADIO_SLAVE_2_MASTER                      (0xF1)
#define CASCADE_CMD_ENOCEAN_REMAN_MASTER_2_SLAVE                      (0xF2)
#define CASCADE_CMD_ENOCEAN_REMAN_SLAVE_2_MASTER                      (0xF3)

#define CASCADE_CMD_MODBUS_MASTER_2_SLAVE                             (0xE0)
#define CASCADE_CMD_MODBUS_SLAVE_2_MASTER                             (0xE1)
/*
#define CASCADE_CMD_EXPAND_MASTER_2_SLAVE                             (0xD0)
#define CASCADE_CMD_EXPAND_SLAVE_2_MASTER                             (0xD1)

#define CASCADE_CMD_DALI_MASTER_2_SLAVE                               (0xC0)
#define CASCADE_CMD_DALI_SLAVE_2_MASTER                               (0xC1)

#define CASCADE_CMD_DALI_CONVERT_MASTER_2_SLAVE                       (0xCD)
#define CASCADE_CMD_DALI_CONVERT_SLAVE_2_MASTER                       (0xCE)
*/
/********************************************************************************************/
/* System */
/********************************************************************************************/
#define CASCADE_CMD_SYS_SEARCH_SYNC                                   (0x00)
#define CASCADE_CMD_SYS_DATA_SYNC                                     (0x01)
/********************************************************************************************/
/* Light and curtain blind */
/********************************************************************************************/
#define CASCADE_CMD_CTRL_CHANNEL                                      (0x10)
#define CASCADE_CMD_QUERY_CHANNEL                                     (0x11)
#define CASCADE_CMD_SET_CHANNEL                                       (0x12)
#define CASCADE_CMD_RESPONSE_CHANNEL                                  (0x13)

#define CASCADE_CMD_CTRL_CURTAIN                                      (0x14)
#define CASCADE_CMD_QUERY_CURTAIN                                     (0x15)
#define CASCADE_CMD_SET_CURTAIN_POSTION                               (0x16)
#define CASCADE_CMD_RESPONSE_CUTRAIN                                  (0x17)

#define CASCADE_CMD_QUERY_INPUT                                       (0x18)
#define CASCADE_CMD_RESPONSE_INPUT                                    (0x19)

#define CASCADE_CMD_SET_COLOR                                         (0x1A)
#define CASCADE_CMD_QUERY_COLOR                                       (0x1B)
#define CASCADE_CMD_RESPONSE_COLOR                                    (0x1C)
#define CASCADE_CMD_MASTER_RESPONSE_EXPAND                            (0x30)
/********************************************************************************************/
/* HVAC */
/********************************************************************************************/
enum
{
    eCOMMON_TYPE  = 0,
    eENOCEAN_TYPE = 1,
    eMODBUS_TYPE  = 2,
    eDALI_TYPE    = 3,

    eDI_TYPE              = 128,
    eEXPAND_PANEL_TYPE    = 129,
};
/********************************************************************************************/
/*  */
/********************************************************************************************/
#pragma pack(1)
typedef struct
{
    uint8_t  u8Cmd;
    uint8_t  u8State;
    uint8_t  u8ByteMax;
    
    uint8_t  u8Byte[100];
}CascadeModbusData_Typedef;

#ifdef CASCADE_MASTER
    typedef struct
    {
        uint32_t u32LearnSrcID[10][20];
        uint16_t u16LearnTabNums[10];        

    }CascadeInfo_Typedef;

    extern CascadeInfo_Typedef CasInfo;

#endif
#pragma pack()

extern Cascade_Function_Typedef RS485Cascade;
extern CascadeModbusData_Typedef CascadeModbus;


/**
   * @brief
   * @param
   * @retval
   */
uint8_t RS485CascadeInit(Cascade_Function_Typedef *pUSART);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t RS485CascadeSendOK(void);

/**
     * @brief
     * @param
     * @retval
     */
uint8_t RS485Cascade_EnOceanPushQueue(Radio_Typedef *pRadio,CascadeSendQueue_Typedef *pCascade);

#ifdef CASCADE_MASTER
    /**
     * @brief
     * @param
     * @retval
     */
    uint8_t RS485Cascade_MasterExpandPanelPushQueue(uint8_t u8DevID,uint8_t u8ButtonID);
    /**
         * @brief
         * @param
         * @retval
         */
    uint8_t RS485Cascade_MasterExpandPanelForward(SerialCascade_Typedef *pSerial);
    /**
     * @brief
     * @param
     * @retval
     */
    void RS485CascadeMasterGetModbus(CascadeModbusData_Typedef *pCascade,uint8_t *pu8ModbusBuff);
    /**
      * @brief
      * @param
      * @retval
      */
    uint8_t RS485Cascade_MasterEnOceanForward(CascadeSendQueue_Typedef *pCascade,SerialCascade_Typedef *pSerial);

    /**
      * @brief
      * @param
      * @retval None
      */
    void Cascade_MasterGetSlaverInfo(uint8_t u8PhyAdd,Radio_Typedef *pRadio);
    /**
      * @brief
      * @param
      * @retval None
      */
    uint16_t Cascade_MasterGetSlaverLearnIDs(void);
#else
    
    /**
     * @brief
     * @param
     * @retval
     */
    uint8_t RS485Cascade_SlaverDIForwardPopQueue(SerialCascade_Typedef *pSerial);
    /**
     * @brief
     * @param
     * @retval
     */
    void RS485Cascade_SlaverModbusGetOffsetDelay(uint16_t u16RegID, uint16_t u16RegNums,SerialCascade_Typedef *pSerial); 
#endif

#endif

/* End of file */
