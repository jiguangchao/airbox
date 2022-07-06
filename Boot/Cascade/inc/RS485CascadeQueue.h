
#ifndef _RS485_CASCADE_QUEUE_H_
#define _RS485_CASCADE_QUEUE_H_

#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"

/********************************************************************************************/
/********************************************************************************************/

/********************************************************************************************/
/********************************************************************************************/
#pragma pack(1)
typedef struct 
{
    //uint8_t  u8Cmd;
    uint8_t  u8State;
    // rock expand DI or enocean 
    uint8_t  u8MessageType;
    uint8_t  u8ByteMax;
    uint8_t  u8PacketType;
    uint8_t  u8Byte[CASCADE_BUFF_MAX];    
    uint8_t  u8DstPhyaddress;
}CascadeProtocolData_Typedef;

typedef struct
{
    uint8_t  u8QueueFull;
    uint8_t  u8PushCount;
    uint8_t  u8PopCount;
    
    CascadeProtocolData_Typedef Data[CASCADE_TX_QUEUE_MAX];

}CascadeSendQueue_Typedef;
#pragma pack()



extern CascadeSendQueue_Typedef CascadeSend;


/**
 * @brief
 * @param
 * @retval None
 */
void Cascade_ClearSendQueuePopID(void);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Cascade_GetSendQueuePopID(void);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Cascade_GetSendQueueFull(void);
/**
 * @brief
 * @param
 * @retval None
 */
void Cascade_SetSendQueueIDOccupy(void);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Cascade_GetSendQueuePushID(void);

#endif

/* End of file */
