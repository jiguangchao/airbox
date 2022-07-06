
#ifndef _BSP_USART_H_
#define _BSP_USART_H_



/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_DMA_ChannelEnable(void);
/*=============================================================================*/
/*===============================EnOcean  USART3===============================*/
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

/*=============================================================================*/
/*===============================RS485  USART1===============================*/
/*=============================================================================*/
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

void BSP_RS485ModbusSendStart(uint8_t u8SendMax);
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

/*=============================================================================*/
/*===============================PMSA003  USART2===============================*/
/*=============================================================================*/
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_PMSAUsartDMA_Init(uint8_t *pu8RxBuff,uint8_t *puTxBuff);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_PMSAUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_PMSASendStart(uint8_t u8SendMax);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_PMSASendStop(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_PMSAStatus(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_PMSADirectSend(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_PMSADirectReceive(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_PMSAStatus(void);
/*=============================================================================*/
/*===============================CH2O+CO2  USART4===============================*/
/*=============================================================================*/
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_CH2O_CO2_UsartDMA_Init(uint8_t *pu8RxBuff,uint8_t *puTxBuff);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_CH2O_CO2_USART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_CH2O_CO2SendStart(uint8_t u8SendMax);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CH2O_CO2SendStop(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CH2O_CO2Status(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CH2O_CO2DirectSend(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CH2O_CO2DirectReceive(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_CH2O_CO2Status(void);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_CH2O_ChannelEnable(void);
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_CO2_ChannelEnable(void);

#endif

/* End of file */
