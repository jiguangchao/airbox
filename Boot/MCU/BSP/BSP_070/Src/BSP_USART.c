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

#include "..\..\BSP_Include.h"


/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_DMA_ChannelEnable(void)
{
    /* Init with LL driver */
    /* DMA controller clock enable */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    /* DMA1_Channel2_3_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

    NVIC_SetPriority(DMA1_Ch4_7_DMAMUX1_OVR_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Ch4_7_DMAMUX1_OVR_IRQn);
} 

/*=============================================================================*/
/*===============================EnOcean  USART3===============================*/
/*=============================================================================*/
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_EnOceanUsartDMA_Init(uint8_t *puTxBuff)
{
    /*************************** Rx *****************************/
    /********************** Tx *********************************/     
    LL_DMA_DisableChannel(DMA1, ENOCEAN_DMA_CHANNEL_TX);
    LL_DMA_SetPeriphRequest(DMA1, ENOCEAN_DMA_CHANNEL_TX, ENOCEAN_USART_DMA_TX_REQ);
    LL_DMA_SetDataTransferDirection(DMA1, ENOCEAN_DMA_CHANNEL_TX, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DMA1, ENOCEAN_DMA_CHANNEL_TX, LL_DMA_PRIORITY_HIGH);    
    LL_DMA_SetMode(DMA1, ENOCEAN_DMA_CHANNEL_TX, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DMA1, ENOCEAN_DMA_CHANNEL_TX, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, ENOCEAN_DMA_CHANNEL_TX, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, ENOCEAN_DMA_CHANNEL_TX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DMA1, ENOCEAN_DMA_CHANNEL_TX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemoryAddress(DMA1, ENOCEAN_DMA_CHANNEL_TX, (uint32_t)puTxBuff);
    LL_DMA_SetPeriphAddress(DMA1, ENOCEAN_DMA_CHANNEL_TX, (uint32_t)&ENOCEAN_USART->TDR);    
    //LL_DMA_SetDataLength(DMA1,ENOCEAN_DMA_CHANNEL_TX,ESP3_TX_BUF_MAX);

    /* Enable DMA transfer complete/error interrupts */
    LL_DMA_EnableIT_TC(DMA1, ENOCEAN_DMA_CHANNEL_TX);
    LL_DMA_EnableIT_TE(DMA1, ENOCEAN_DMA_CHANNEL_TX);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_EnOceanUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
        

    USART_InitStruct.PrescalerValue       = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate             = u32Baud;
    USART_InitStruct.DataWidth            = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits             = u32Stops;
    USART_InitStruct.Parity               = u32Parity;
    USART_InitStruct.TransferDirection    = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl  = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling         = LL_USART_OVERSAMPLING_16;


    /* USART1 interrupt Init */
    NVIC_SetPriority(ENOCEAN_USART_IRQ, 0);
    NVIC_EnableIRQ(ENOCEAN_USART_IRQ);    

    LL_USART_Disable(ENOCEAN_USART);
    LL_USART_Init(ENOCEAN_USART, &USART_InitStruct);
    
    LL_USART_SetTXFIFOThreshold(ENOCEAN_USART, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(ENOCEAN_USART, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_DisableFIFO(ENOCEAN_USART);   
    LL_USART_ConfigAsyncMode(ENOCEAN_USART);
    LL_USART_EnableIT_RXNE_RXFNE(ENOCEAN_USART);    
    //LL_USART_EnableIT_RXNE(ENOCEAN_USART);
    LL_USART_Enable(ENOCEAN_USART);
    

    /* Polling USART2 initialisation */
    while((!(LL_USART_IsActiveFlag_TEACK(ENOCEAN_USART))) || (!(LL_USART_IsActiveFlag_REACK(ENOCEAN_USART))))
    {
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* Polling USART initialisation */
    while ((!(LL_USART_IsActiveFlag_TEACK(ENOCEAN_USART))) || (!(LL_USART_IsActiveFlag_REACK(ENOCEAN_USART))))
    {
    }
}
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_EnOceanSendStart(uint16_t u16SendMax)
{         
    /* TC */
    //LL_USART_EnableIT_TC(ENOCEAN_USART);
    /* TXE */
    //LL_USART_EnableIT_TXE(ENOCEAN_USART);
    LL_USART_EnableDirectionTx(ENOCEAN_USART);     
    LL_USART_EnableDMAReq_TX(ENOCEAN_USART);
    LL_DMA_DisableChannel(DMA1, ENOCEAN_DMA_CHANNEL_TX);
    LL_DMA_SetDataLength(DMA1, ENOCEAN_DMA_CHANNEL_TX, u16SendMax);     
    LL_DMA_EnableChannel(DMA1, ENOCEAN_DMA_CHANNEL_TX);
}
/**
  * @brief
  * @param
  * @retval None
  */
void BSP_EnOceanSendStop(void)
{        
    /* TC */
    //LL_USART_DisableIT_TC(ENOCEAN_USART);
    /* TXE */
    //LL_USART_DisableIT_TXE(ENOCEAN_USART);

    LL_USART_DisableDirectionTx(ENOCEAN_USART);
    LL_USART_DisableDMAReq_TX(ENOCEAN_USART);
    LL_DMA_DisableChannel(DMA1, ENOCEAN_DMA_CHANNEL_TX);
}
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*=============================================================================*/
/*===============================Modbus  USART4================================*/
/*=============================================================================*/
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_ModbusUsartDMA_Init(uint8_t *pu8RxBuff,uint8_t *puTxBuff)
{
    /********************************* Rx ************************/ 
    /* Set DMA transfer addresses of source and destination */
    

    /* Set DMA transfer size */
    LL_DMA_DisableChannel(DMA1, RS485_MODBUS_DMA_CHANNEL_RX);
    LL_DMA_SetPeriphRequest(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, RS485_MODBUS_DMA_RX_REQ);
    LL_DMA_SetDataTransferDirection(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetChannelPriorityLevel(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, LL_DMA_PRIORITY_HIGH);    
    LL_DMA_SetMode(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemoryAddress(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, (uint32_t)pu8RxBuff);
    LL_DMA_SetPeriphAddress(DMA1, RS485_MODBUS_DMA_CHANNEL_RX, (uint32_t)&RS485_MODBUS_USART->RDR);
    LL_DMA_SetDataLength(DMA1,RS485_MODBUS_DMA_CHANNEL_RX,RS485_MODBUS_RX_BUFF);

    /* Enable DMA transfer complete/error interrupts */
    //LL_DMA_EnableIT_TC(DMA1, RS485_MODBUS_DMA_CHANNEL_RX);
    //LL_DMA_EnableIT_TE(DMA1, RS485_MODBUS_DMA_CHANNEL_RX);

    /* Start the DMA transfer Flash to Memory */
    LL_DMA_EnableChannel(DMA1, RS485_MODBUS_DMA_CHANNEL_RX);

    /******************************* Tx ***************************/ 
    LL_DMA_DisableChannel(DMA1, RS485_MODBUS_DMA_CHANNEL_TX);
    LL_DMA_SetPeriphRequest(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, RS485_MODBUS_DMA_TX_REQ);
    LL_DMA_SetDataTransferDirection(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, LL_DMA_PRIORITY_HIGH);    
    LL_DMA_SetMode(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, LL_DMA_MDATAALIGN_BYTE);   
    LL_DMA_SetMemoryAddress(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, (uint32_t)puTxBuff);
    LL_DMA_SetPeriphAddress(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, (uint32_t)&RS485_MODBUS_USART->TDR);        
    LL_DMA_SetDataLength(DMA1,RS485_MODBUS_DMA_CHANNEL_TX,RS485_MODBUS_TX_BUFF);    
    /* Enable DMA transfer complete/error interrupts */
    LL_DMA_EnableIT_TC(DMA1, RS485_MODBUS_DMA_CHANNEL_TX);
    LL_DMA_EnableIT_TE(DMA1, RS485_MODBUS_DMA_CHANNEL_TX);

    /* Start the DMA transfer Flash to Memory */    
}
/* USART2 init function */
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_ModbusUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};


    USART_InitStruct.PrescalerValue       = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate             = u32Baud;
    switch ( u32Parity )
    {
        case ePARITY_EVEN:
            
            USART_InitStruct.DataWidth  = LL_USART_DATAWIDTH_9B;
            break;
        case ePARITY_ODD:
            
            USART_InitStruct.DataWidth  = LL_USART_DATAWIDTH_9B;
            break;
        case ePARITY_NONE:
            
            USART_InitStruct.DataWidth  = LL_USART_DATAWIDTH_8B;
            break;
    }

    if ( eSTOP_2 == u32Stops )
    {
        USART_InitStruct.StopBits = LL_USART_STOPBITS_2;
    }
    else
    {
        USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    }
    //USART_InitStruct.DataWidth            = LL_USART_DATAWIDTH_8B;
    //USART_InitStruct.StopBits             = u32Stops;
    USART_InitStruct.Parity               = u32Parity;
    USART_InitStruct.TransferDirection    = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl  = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling         = LL_USART_OVERSAMPLING_16;
    
    LL_USART_Disable(RS485_MODBUS_USART);
    LL_USART_Init(RS485_MODBUS_USART, &USART_InitStruct);
    LL_USART_SetTXFIFOThreshold(RS485_MODBUS_USART, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(RS485_MODBUS_USART, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_DisableFIFO(RS485_MODBUS_USART);   
    LL_USART_ConfigAsyncMode(RS485_MODBUS_USART);

    //LL_USART_SetTXRXSwap(RS485_MODBUS_USART, LL_USART_TXRX_SWAPPED);
    
    /* USART2 interrupt Init */
    NVIC_SetPriority(RS485_MODBUS_USART_IRQ, 0);
    NVIC_EnableIRQ(RS485_MODBUS_USART_IRQ);    
    LL_USART_EnableDMAReq_RX(RS485_MODBUS_USART);
    LL_USART_EnableIT_IDLE(RS485_MODBUS_USART);
    LL_USART_Enable(RS485_MODBUS_USART);


    while((!(LL_USART_IsActiveFlag_TEACK(RS485_MODBUS_USART))) || (!(LL_USART_IsActiveFlag_REACK(RS485_MODBUS_USART))))
    {
    }


    /* Polling USART initialisation */
    while ((!(LL_USART_IsActiveFlag_TEACK(RS485_MODBUS_USART))) || (!(LL_USART_IsActiveFlag_REACK(RS485_MODBUS_USART))))
    {
    }
}

/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_RS485ModbusSendStart(uint16_t u16SendMax)
{       
    /* DMA */
    
    LL_USART_EnableDirectionTx(RS485_MODBUS_USART);     
    LL_USART_EnableDMAReq_TX(RS485_MODBUS_USART);
    LL_DMA_DisableChannel(DMA1, RS485_MODBUS_DMA_CHANNEL_TX);
    
    LL_DMA_SetDataLength(DMA1, RS485_MODBUS_DMA_CHANNEL_TX, u16SendMax);     
    LL_DMA_EnableChannel(DMA1, RS485_MODBUS_DMA_CHANNEL_TX);
    
    /* TC */
    //LL_USART_EnableIT_TC(RS485_MODBUS_USART);
    /* TXE */
    //LL_USART_EnableIT_TXE(RS485_MODBUS_USART);
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485ModbusSendStop(void)
{
    /* DMA */
    
    LL_USART_DisableDirectionTx(RS485_MODBUS_USART);
    LL_USART_DisableDMAReq_TX(RS485_MODBUS_USART);
    LL_DMA_DisableChannel(DMA1, RS485_MODBUS_DMA_CHANNEL_TX);
    
    /* TC */
    //LL_USART_DisableIT_TC(RS485_MODBUS_USART);
    /* TXE */
    //LL_USART_DisableIT_TXE(RS485_MODBUS_USART);
    return 0;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485ModbusDirectSend(void)
{    
    LL_GPIO_SetOutputPin(RS485_MODBUS_DE_GPIO, RS485_MODBUS_DE_PIN);
    return 0;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485ModbusDirectReceive(void)
{    
    LL_GPIO_ResetOutputPin(RS485_MODBUS_DE_GPIO, RS485_MODBUS_DE_PIN);
    return 0;
}

/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t BSP_RS485MBModbusStatus(void)
{
    return LL_USART_IsActiveFlag_BUSY(RS485_MODBUS_USART);
}
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* USART2 init function */
/*********************************************************************************************/
#if 0
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_CascadeUsartDMA_Init(uint8_t *pu8RxBuff,uint8_t *puTxBuff)
{
    /********************************* Rx ************************/ 
    /* Set DMA transfer addresses of source and destination */
    /* Set DMA transfer size */
    LL_DMA_DisableChannel(DMA1, RS485_CASCADE_DMA_CHANNEL_RX);
    LL_DMA_SetPeriphRequest(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, RS485_CASCADE_DMA_RX_REQ);
    LL_DMA_SetDataTransferDirection(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetChannelPriorityLevel(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, LL_DMA_PRIORITY_HIGH);    
    LL_DMA_SetMode(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemoryAddress(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, (uint32_t)pu8RxBuff);
    LL_DMA_SetPeriphAddress(DMA1, RS485_CASCADE_DMA_CHANNEL_RX, (uint32_t)&RS485_CASCADE_USART->RDR);
    LL_DMA_SetDataLength(DMA1,RS485_CASCADE_DMA_CHANNEL_RX,RS485_CASCADE_RX_BUFF);

    /* Enable DMA transfer complete/error interrupts */
    //LL_DMA_EnableIT_TC(DMA1, RS485_CASCADE_DMA_CHANNEL_RX);
    //LL_DMA_EnableIT_TE(DMA1, RS485_CASCADE_DMA_CHANNEL_RX);

    /* Start the DMA transfer Flash to Memory */
    LL_DMA_EnableChannel(DMA1, RS485_CASCADE_DMA_CHANNEL_RX);

    /******************************* Tx ***************************/ 
    LL_DMA_DisableChannel(DMA1, RS485_CASCADE_DMA_CHANNEL_TX);
    LL_DMA_SetPeriphRequest(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, RS485_CASCADE_DMA_TX_REQ);
    LL_DMA_SetDataTransferDirection(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, LL_DMA_PRIORITY_HIGH);    
    LL_DMA_SetMode(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, LL_DMA_MDATAALIGN_BYTE);   
    LL_DMA_SetMemoryAddress(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, (uint32_t)puTxBuff);
    LL_DMA_SetPeriphAddress(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, (uint32_t)&RS485_CASCADE_USART->TDR);        
    LL_DMA_SetDataLength(DMA1,RS485_CASCADE_DMA_CHANNEL_TX,RS485_CASCADE_TX_BUFF);    
    /* Enable DMA transfer complete/error interrupts */
    LL_DMA_EnableIT_TC(DMA1, RS485_CASCADE_DMA_CHANNEL_TX);
    LL_DMA_EnableIT_TE(DMA1, RS485_CASCADE_DMA_CHANNEL_TX);

    /* Start the DMA transfer Flash to Memory */    
}
/* USART2 init function */
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void BSP_CascadeUSART_Init(uint32_t u32Baud, uint32_t u32Stops, uint32_t u32Parity)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
                    
    USART_InitStruct.PrescalerValue       = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate             = u32Baud;
    //USART_InitStruct.DataWidth            = LL_USART_DATAWIDTH_8B;
    //USART_InitStruct.StopBits             = u32Stops;
    switch ( u32Parity )
    {
        case ePARITY_EVEN:
            
            USART_InitStruct.DataWidth  = LL_USART_DATAWIDTH_9B;
            break;
        case ePARITY_ODD:
            
            USART_InitStruct.DataWidth  = LL_USART_DATAWIDTH_9B;
            break;
        case ePARITY_NONE:
            
            USART_InitStruct.DataWidth  = LL_USART_DATAWIDTH_8B;
            break;
    }

    if ( eSTOP_2 == u32Stops )
    {
        USART_InitStruct.StopBits = LL_USART_STOPBITS_2;
    }
    else
    {
        USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    }
    
    USART_InitStruct.Parity               = u32Parity;
    USART_InitStruct.TransferDirection    = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl  = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling         = LL_USART_OVERSAMPLING_16;
    
    LL_USART_Disable(RS485_CASCADE_USART);
    LL_USART_Init(RS485_CASCADE_USART, &USART_InitStruct);
    LL_USART_SetTXFIFOThreshold(RS485_CASCADE_USART, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(RS485_CASCADE_USART, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_DisableFIFO(RS485_CASCADE_USART);   
    LL_USART_ConfigAsyncMode(RS485_CASCADE_USART);
    
    /* USER CODE BEGIN WKUPType USART2 */
    /* USER CODE END WKUPType USART2 */
    /* USART2 interrupt Init */
    NVIC_SetPriority(RS485_CASCADE_USART_IRQ, 0);
    NVIC_EnableIRQ(RS485_CASCADE_USART_IRQ);    
    LL_USART_EnableDMAReq_RX(RS485_CASCADE_USART);
    LL_USART_EnableIT_IDLE(RS485_CASCADE_USART);
    LL_USART_Enable(RS485_CASCADE_USART);

    /* Polling USART2 initialisation */
    while((!(LL_USART_IsActiveFlag_TEACK(RS485_CASCADE_USART))) || (!(LL_USART_IsActiveFlag_REACK(RS485_CASCADE_USART))))
    {
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* Polling USART initialisation */
    while ((!(LL_USART_IsActiveFlag_TEACK(RS485_CASCADE_USART))) || (!(LL_USART_IsActiveFlag_REACK(RS485_CASCADE_USART))))
    {
    }
}
/*=============================================================================*/
/*===============================Cascade  USART1===============================*/
/*=============================================================================*/
/**
  * @brief  
  * @param
  * @retval None
  */
void BSP_RS485CascadeSendStart(uint16_t u16SendMax)
{   
    /* DMA */
    
    LL_USART_EnableDirectionTx(RS485_CASCADE_USART);     
    LL_USART_EnableDMAReq_TX(RS485_CASCADE_USART);
    LL_DMA_DisableChannel(DMA1, RS485_CASCADE_DMA_CHANNEL_TX);
    LL_DMA_SetDataLength(DMA1, RS485_CASCADE_DMA_CHANNEL_TX, u16SendMax);     
    LL_DMA_EnableChannel(DMA1, RS485_CASCADE_DMA_CHANNEL_TX);
    
    /* TC */
    //LL_USART_EnableIT_TC(RS485_CASCADE_USART);
    /* TXE */
    //LL_USART_EnableIT_TXE(RS485_CASCADE_USART);
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485CascadeSendStop(void)
{
    /* DMA */
    
    LL_USART_DisableDirectionTx(RS485_CASCADE_USART);
    LL_USART_DisableDMAReq_TX(RS485_CASCADE_USART);
    LL_DMA_DisableChannel(DMA1, RS485_CASCADE_DMA_CHANNEL_TX);
    
    /* TC */
    //LL_USART_DisableIT_TC(RS485_CASCADE_USART);
    /* TXE */
    //LL_USART_DisableIT_TXE(RS485_CASCADE_USART);
    return 0;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485CascadeDirectSend(void)
{    
    LL_GPIO_SetOutputPin(RS485_CASCADE_DE_GPIO, RS485_CASCADE_DE_PIN);
  	return 0;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BSP_RS485CascadeDirectReceive(void)
{
    LL_GPIO_ResetOutputPin(RS485_CASCADE_DE_GPIO, RS485_CASCADE_DE_PIN);
	return 0;
}

/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t BSP_RS485CascadeStatus(void)
{
    return LL_USART_IsActiveFlag_BUSY(RS485_CASCADE_USART);
}

#endif
/* End of file */

