
/*!
*****************************************************************
$Name$
$Revision: 
$Date: 
\file 
\brief  
\author zhoujinbang


<b>Company:</b>\nmenred automation\n
修改记录
1、
2、
3、
4、
5、
6、
*****************************************************************/

/*============================ INCLUDES ======================================*/
#include "..\BaselibInclude.h"


/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 


/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/




/* Private variables ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrSendSetTime(uint32_t *pu32ErrTime,uint32_t u32ErrTimeSet)
{
    *pu32ErrTime = u32ErrTimeSet;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrOverSetTime(uint32_t *pu32ErrOverTime,uint32_t u32ErrOverTimeSet)
{
    *pu32ErrOverTime = u32ErrOverTimeSet;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t ErrOverTime(uint32_t u32ErrTime)
{
    if ( u32ErrTime  )
    {
        return !0;
    }

    return 0;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrTriggerTime(uint32_t *pu32ErrTime)
{
    if ( *pu32ErrTime  )
    {
        (*pu32ErrTime)--;
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrSetByCnt(uint8_t *pu8ErrCnt,uint8_t u8ErrCntMax,uint32_t *pu32Err,uint32_t u32ErrMask)
{
    (*pu8ErrCnt)++;
    if ( *pu8ErrCnt >= u8ErrCntMax )
    {
        *pu8ErrCnt  = 0;
        *pu32Err   |= u32ErrMask;
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrSet(uint32_t *pu32Err,uint32_t u32ErrMask)
{        
    *pu32Err   |= u32ErrMask;    
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ErrClear(uint8_t *pu8ErrCnt,uint32_t *pu32Err,uint32_t u32ErrMask)
{
    if ( pu8ErrCnt != NULL )
    {
        *pu8ErrCnt = 0;
    }
    
    *pu32Err  &= ~u32ErrMask;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t ErrGetStatus(uint32_t u32Err,uint32_t u32ErrMask)
{
    if (u32Err&u32ErrMask)
    {
        return 1;
    }

    return 0;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint32_t ErrSendMessage(uint32_t *pu32ErrTime,uint32_t u32ErrTimeMax,uint32_t u32Err,uint32_t u32ErrMask)
{
    if ( *pu32ErrTime >= u32ErrTimeMax )
    {
        *pu32ErrTime = 0;

        if ( u32Err&u32ErrMask)
        {
            return OK;
        }        
    }

    return !OK;
}


/* End of file */

