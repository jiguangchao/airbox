
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
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"

/* User App */
#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "RS485Modbus.h"
#include "EnOceanCascade.h"
#include "EnOceanMSCCascade.h"
#include "Debug.h"
#include "HWTest.h"

#include "SysError.h"
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
void SysytemError(void)
{
    

}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SysErrorTime_1000ms(void)
{
    if ( Dev.u16CleanErrorFlagTime )
    {
        Dev.u16CleanErrorFlagTime --;
    }
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SysErrorNeedManualClear(void)
{
    
    return OK;
        
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t SysErrorManualClearID(void)
{
    
    
    return 0;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SysErrorManualClear(void)
{
    
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
