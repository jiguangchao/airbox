
#ifndef _BSP_TM1617_H_
#define _BSP_TM1617_H_

#include "..\..\MCU\platform.h"


/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetSTBHigh(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetSTBLow(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetClkHigh(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetClkLow(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataHigh(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataLow(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t BSP_TM16XX_GetDataGpio(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataInput(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_TM16XX_SetDataOut(void);


#endif

/* End of file */
