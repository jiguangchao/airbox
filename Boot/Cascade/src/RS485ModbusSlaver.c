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


#include "Dataconfigure.h"
#include "BSP.h"
#include "main.h"
#include "RS485Cascade.h"
#include "RS485Modbus.h"
#include "EnOceanFun.h"

#ifdef MODBUS_485_CRC_DISABLE
    #pragma message("MODBUS_485_CRC_DISABLE")
#else
    #pragma message("MODBUS_485_CRC_ENABLE")
#endif

/** @addtogroup
  * @{
  */
/** @addtogroup
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* An array of Modbus functions handlers which associates Modbus function
 * codes with implementing functions.
 */


/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/


/* End of file */