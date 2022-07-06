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

#include ".\BSP_Include.h"


/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t BSP_SHT20_GetSclGpio(void)
{
    return LL_GPIO_IsInputPinSet(IIC1_SHT20_SCL_GPIO, IIC1_SHT20_SCL_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t BSP_SHT20_GetSdaGpio(void)
{
    return LL_GPIO_IsInputPinSet(IIC1_SHT20_SDA_GPIO, IIC1_SHT20_SDA_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_SHT20_SetSclHigh(void)
{
    LL_GPIO_SetOutputPin(IIC1_SHT20_SCL_GPIO, IIC1_SHT20_SCL_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_SHT20_SetSclLow(void)
{
    LL_GPIO_ResetOutputPin(IIC1_SHT20_SCL_GPIO, IIC1_SHT20_SCL_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_SHT20_SetSdaHigh(void)
{
    LL_GPIO_SetOutputPin(IIC1_SHT20_SDA_GPIO, IIC1_SHT20_SDA_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_SHT20_SetSdaLow(void)
{
    LL_GPIO_ResetOutputPin(IIC1_SHT20_SDA_GPIO, IIC1_SHT20_SDA_PIN);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_SHT20_SetSdaInput(void)
{
    LL_GPIO_SetPinMode(IIC1_SHT20_SDA_GPIO, IIC1_SHT20_SDA_PIN, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinOutputType(IIC1_SHT20_SDA_GPIO, IIC1_SHT20_SDA_PIN, LL_GPIO_OUTPUT_PUSHPULL);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_SHT20_SetSdaOut(void)
{
    LL_GPIO_SetPinMode(IIC1_SHT20_SDA_GPIO, IIC1_SHT20_SDA_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(IIC1_SHT20_SDA_GPIO, IIC1_SHT20_SDA_PIN, LL_GPIO_OUTPUT_PUSHPULL);
}

/* End of file */

