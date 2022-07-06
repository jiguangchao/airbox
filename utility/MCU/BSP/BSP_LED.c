
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
#include "BSP_LED.h"

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
void BSP_LEDPWM_RED(uint16_t PWMVlue)
{
    LL_TIM_OC_SetCompareCH2(TIM1, PWMVlue);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDPWM_Green(uint16_t PWMVlue)
{
    LL_TIM_OC_SetCompareCH1(TIM1, PWMVlue);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDPWM_ORG(uint16_t PWMVlue)
{  
    LL_TIM_OC_SetCompareCH2(TIM15, PWMVlue);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDPWM_Yellow(uint16_t PWMVlue)
{
    LL_TIM_OC_SetCompareCH1(TIM3, PWMVlue);
}
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_RED(void)
{
    LL_TIM_OC_SetCompareCH2(TIM1, 0);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_Green(void)
{
    LL_TIM_OC_SetCompareCH1(TIM1, 0);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_ORG(void)
{
    LL_TIM_OC_SetCompareCH2(TIM15, 0);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDLight_Yellow(void)
{
    LL_TIM_OC_SetCompareCH1(TIM3, 0);
}
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_RED(void)
{
    LL_TIM_OC_SetCompareCH2(TIM1, 1000);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_Green(void)
{
    LL_TIM_OC_SetCompareCH1(TIM1, 1000);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_ORG(void)
{
    LL_TIM_OC_SetCompareCH2(TIM15, 1000);
}
/**
 * @brief
 * @param
 * @retval None
 */
void BSP_LEDDark_Yellow(void)
{
    LL_TIM_OC_SetCompareCH1(TIM3, 1000);
}
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/


