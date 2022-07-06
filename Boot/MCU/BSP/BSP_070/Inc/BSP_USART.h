

#ifndef _BSP_USART_H_
#define _BSP_USART_H_



/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_DMA_ChannelEnable(void);
/*=============================================================================*/
/*===============================EnOcean  USART2===============================*/
/*=============================================================================*/
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_EnOceanUsartDMA_Init(uint8_t *puTxBuff);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_EnOceanUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity);
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_ModbusUsartDMA_Init(uint8_t *pu8RxBuff,uint8_t *puTxBuff);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_ModbusUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity);
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_CascadeUsartDMA_Init(uint8_t *pu8RxBuff,uint8_t *puTxBuff);
/* USART2 init function */
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_CascadeUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity);

/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_EnOceanSendStart(uint16_t u16SendMax);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_EnOceanSendStop(void);
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_RS485ModbusSendStart(uint16_t u16SendMax);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485ModbusSendStop(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485ModbusDirectSend(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485ModbusDirectReceive(void);

/**
     * @brief  
     * @param
     * @retval None
     */
void BSP_RS485CascadeSendStart(uint16_t u16SendMax);
/**
     * @brief
     * @param
     * @retval None
     */
uint8_t BSP_RS485CascadeSendStop(void);
/**
     * @brief
     * @param
     * @retval None
     */
uint8_t BSP_RS485CascadeDirectSend(void);    
/**
     * @brief
     * @param
     * @retval None
     */
uint8_t BSP_RS485CascadeDirectReceive(void);
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t BSP_RS485CascadeStatus(void);

#endif
/* End of file */
