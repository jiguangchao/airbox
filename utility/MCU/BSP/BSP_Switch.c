
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
#include "BSP_Switch.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t SwitchScan(void)
{
    uint8_t         u8SwitchPin;

    u8SwitchPin = 0;
    
    if (1 != LL_GPIO_IsInputPinSet(SWITCH1_GPIO,SWITCH1_PIN))
    {
        u8SwitchPin |= 0x08;
    }
    if (1 != LL_GPIO_IsInputPinSet(SWITCH2_GPIO,SWITCH2_PIN))
    {
        u8SwitchPin |= 0x04;
    }
    if (1 != LL_GPIO_IsInputPinSet(SWITCH3_GPIO,SWITCH3_PIN))
    {
        u8SwitchPin |= 0x02;
    }
    if (1 != LL_GPIO_IsInputPinSet(SWITCH4_GPIO,SWITCH4_PIN))
    {
        u8SwitchPin |= 0x01;
    }
  
    return u8SwitchPin + 16 ;
}
/**
 * @brief
 * @param
 * @retval None
 */
void SwitchReadPinStatus(uint8_t *pu8Status)
{
    uint8_t i;
    uint8_t u8Pin;
    
    uint8_t u8PinPre;

    i = 0;

    while ( i < 50 )
    {
        u8Pin = SwitchScan();

        if ( u8PinPre != u8Pin )
        {
            i = 0;
        }
        else
        {
            if ( i < 0xFF )
            {
                i++;
            }
        }
        u8PinPre = u8Pin;

        if (i < 50)
        {
            u8Pin = 0;
        }
        else
        {
            *pu8Status = u8Pin;
            break;
        }
    }
}
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t KeyReadPin(void)
{
    return LL_GPIO_IsInputPinSet(KEY_LRN1_GPIO,KEY_LRN1_PIN);
}


