

#include ".\BSP_Include.h"



/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetSTBHigh(void)
{
    LL_GPIO_SetOutputPin(TM1617_STB_GPIO, TM1617_STB_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetSTBLow(void)
{
    LL_GPIO_ResetOutputPin(TM1617_STB_GPIO, TM1617_STB_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetClkHigh(void)
{
    LL_GPIO_SetOutputPin(TM1617_CLK_GPIO, TM1617_CLK_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetClkLow(void)
{
    LL_GPIO_ResetOutputPin(TM1617_CLK_GPIO, TM1617_CLK_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataHigh(void)
{
    LL_GPIO_SetOutputPin(TM1617_DATA_GPIO, TM1617_DATA_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataLow(void)
{
    LL_GPIO_ResetOutputPin(TM1617_DATA_GPIO, TM1617_DATA_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t BSP_TM16XX_GetDataGpio(void)
{
    return LL_GPIO_IsInputPinSet(TM1617_DATA_GPIO, TM1617_DATA_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataInput(void)
{
    LL_GPIO_SetPinMode(TM1617_DATA_GPIO, TM1617_DATA_PIN, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinOutputType(TM1617_DATA_GPIO, TM1617_DATA_PIN, LL_GPIO_OUTPUT_PUSHPULL);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataOut(void)
{
    LL_GPIO_SetPinMode(TM1617_DATA_GPIO, TM1617_DATA_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(TM1617_DATA_GPIO, TM1617_DATA_PIN, LL_GPIO_OUTPUT_PUSHPULL);
}
/* End of file */
