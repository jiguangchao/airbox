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
#include "EnOceanlibInclude.h"

#include "RS485Cascade.h"

#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"


/******************************************************************************/

CascadeSendQueue_Typedef  CascadeSend;


/**
 * @brief
 * @param
 * @retval None
 */
void Cascade_ClearSendQueuePopID(void)
{
    CascadeSend.Data[CascadeSend.u8PopCount].u8State = 0;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Cascade_GetSendQueuePopID(void)
{
    uint8_t i;
    uint8_t j;

    Cascade_GetSendQueueFull();

    if ( CascadeSend.u8PopCount >= CASCADE_TX_QUEUE_MAX )
    {
        CascadeSend.u8PopCount = 0;
    }

    j = CascadeSend.u8PopCount;

    /*  Search the current id to the queue Max */
    for (i = j+1; i < CASCADE_TX_QUEUE_MAX;i++)
    {
        if ( 0 == CascadeSend.Data[i].u8State ) 
        {
            continue;
        }

        CascadeSend.u8PopCount = i;
        return OK;
    }
    
    /* Search the start 0 to the current id */
    for (i = 0; i < j; i++)
    {
        if ( 0 == CascadeSend.Data[i].u8State )
        {
            continue;  
        }
        CascadeSend.u8PopCount = i;
        return OK;
    }

    //Esp3Rx.u8PopCount = 0;

    return !OK;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Cascade_GetSendQueueFull(void)
{
    uint8_t i;

    for (i = 0; i < CASCADE_TX_QUEUE_MAX;i++)
    {
        if ( 0 == CascadeSend.Data[i].u8State )
        {
            CascadeSend.u8QueueFull = 0;
        }
    }

    return CascadeSend.u8QueueFull;
}
/**
 * @brief
 * @param
 * @retval None
 */
void Cascade_SetSendQueueIDOccupy(void)
{
    CascadeSend.Data[CascadeSend.u8PushCount].u8State = 1;
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t Cascade_GetSendQueuePushID(void)
{
    uint8_t i;
    uint8_t j;

    if ( CascadeSend.u8QueueFull )
    {
        return !OK;
    }

    j = CascadeSend.u8PushCount;

    /*  Search the current id to the queue Max */
    for (i = j+1; i < CASCADE_TX_QUEUE_MAX;i++)
    {
        if ( 1 == CascadeSend.Data[i].u8State )
        {
            continue;
        }
        CascadeSend.u8PushCount = i;
        return OK;
    }
    
    /* Search the start 0 to the current id */
    for (i = 0; i < j; i++)
    {
        if ( 1 == CascadeSend.Data[i].u8State )
        {
            continue;
        }
        CascadeSend.u8PushCount = i;
        return OK;
    }
    CascadeSend.u8QueueFull = 1;

    return !OK;
}
/* End of file */