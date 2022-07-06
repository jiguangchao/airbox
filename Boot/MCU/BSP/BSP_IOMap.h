#ifndef _BSP_IO_MAP_H_
#define _BSP_IO_MAP_H_

#ifdef  G_PORT_MAP_MODULE
#define G_PORT_MAP_EXT
#else
#define G_PORT_MAP_EXT extern
#endif


#define FCLK                                      (64000000)//64MHz




/*############################################################################################################*/
/*############################################################################################################*/
/*                                                                                                            */
/*                                           STM32G070xx                                                      */
/*                                                                                                            */
/*############################################################################################################*/
/*############################################################################################################*/

/******************************************************************************/
/* USART DMA TRANSFORM */
/******************************************************************************/
#define RS485_CASCADE_DMA_CHANNEL_TX    (LL_DMA_CHANNEL_1)
#define RS485_CASCADE_DMA_CHANNEL_RX    (LL_DMA_CHANNEL_2)

#define ENOCEAN_DMA_CHANNEL_TX          (LL_DMA_CHANNEL_3)

#define RS485_MODBUS_DMA_CHANNEL_TX     (LL_DMA_CHANNEL_4)
#define RS485_MODBUS_DMA_CHANNEL_RX     (LL_DMA_CHANNEL_5)

#define RS485_EXPAND_DMA_CHANNEL_TX     (LL_DMA_CHANNEL_6)
#define RS485_EXPAND_DMA_CHANNEL_RX     (LL_DMA_CHANNEL_7)


#define RS485_MODBUS_USART                  (USART1)    
#define RS485_MODBUS_USART_IRQ              (USART1_IRQn)    
#define RS485_MODBUS_DMA_TX_REQ             LL_DMAMUX_REQ_USART1_TX
#define RS485_MODBUS_DMA_RX_REQ             LL_DMAMUX_REQ_USART1_RX
//#define RS485_MODBUS_TX_BUFF                (128)
//#define RS485_MODBUS_RX_BUFF                (128)


#define ENOCEAN_USART                       (USART3)
#define ENOCEAN_USART_IRQ                   (USART3_4_IRQn)
#define ENOCEAN_USART_DMA_TX_REQ            LL_DMAMUX_REQ_USART3_TX  

/*
#define RS485_MODBUS_USART (USART3)
#define RS485_MODBUS_USART_IRQ (USART3_4_IRQn)
#define RS485_MODBUS_DMA_TX_REQ LL_DMAMUX_REQ_USART3_TX
#define RS485_MODBUS_DMA_RX_REQ LL_DMAMUX_REQ_USART3_RX

#define RS485_EXPAND_USART (USART4)
#define RS485_EXPAND_USART_IRQ (USART3_4_IRQn)
#define RS485_EXPAND_DMA_TX_REQ LL_DMAMUX_REQ_USART4_TX
#define RS485_EXPAND_DMA_RX_REQ LL_DMAMUX_REQ_USART4_RX

#define ENOCEAN_USART                       (USART3)
#define ENOCEAN_USART_IRQ                   (USART3_4_IRQn)
#define ENOCEAN_USART_DMA_TX_REQ            LL_DMAMUX_REQ_USART3_TX  

#define RS485_CASCADE_USART (USART1)
#define RS485_CASCADE_USART_IRQ (USART1_IRQn)
#define RS485_CASCADE_DMA_TX_REQ LL_DMAMUX_REQ_USART1_TX
#define RS485_CASCADE_DMA_RX_REQ LL_DMAMUX_REQ_USART1_RX
#define RS485_CASCADE_TX_BUFF (128)
#define RS485_CASCADE_RX_BUFF (128)
*/

/******************************************************************************/
/* RS485 Cascade  -- uart1  RX->PB7 TX->PB6 EN3->PB8 */
/******************************************************************************/    
#define RS485_MODBUS_TX_PIN                  (LL_GPIO_PIN_6)
#define RS485_MODBUS_TX_GPIO                 (GPIOB)
#define RS485_MODBUS_RX_PIN                  (LL_GPIO_PIN_7)
#define RS485_MODBUS_RX_GPIO                 (GPIOB)

#define RS485_MODBUS_DE_PIN                  (LL_GPIO_PIN_8)
#define RS485_MODBUS_DE_GPIO                 (GPIOB) 

/******************************************************************************/
/* TCM_310  -- uart3  RX->PB11 TX->PB10 RST->PB12 */
/******************************************************************************/    
#define ENOCEAN_RX_PIN                        (LL_GPIO_PIN_11)
#define ENOCEAN_RX_GPIO                       (GPIOB)        

#define ENOCEAN_TX_PIN                        (LL_GPIO_PIN_10)
#define ENOCEAN_TX_GPIO                       (GPIOB)        

#define ENOCEAN_RST_PIN                       (LL_GPIO_PIN_12)
#define ENOCEAN_RST_GPIO                      (GPIOB)
                                                                                                
#define ENOCEAN_HARDWARE_RST_DISABLE()        LL_GPIO_ResetOutputPin(ENOCEAN_RST_GPIO, ENOCEAN_RST_PIN)  
#define ENOCEAN_HARDWARE_RST_ENABLE()         LL_GPIO_SetOutputPin(ENOCEAN_RST_GPIO, ENOCEAN_RST_PIN) 

/******************************************************************************/
/* LED PIN OUT MCU */
/******************************************************************************/
#define LED_RED_GPIO                        (GPIOA)
#define LED_GREEN_GPIO                      (GPIOA)
#define LED_ORG_GPIO                        (GPIOB)
#define LED_YELLOW_GPIO                     (GPIOC)

#define LED_RED_PIN                         (LL_GPIO_PIN_9)
#define LED_GREEN_PIN                       (LL_GPIO_PIN_8)
#define LED_ORG_PIN                         (LL_GPIO_PIN_15)
#define LED_YELLOW_PIN                      (LL_GPIO_PIN_6)


                                            /*Set输出高电平  Reset输出低电平 */                                                
#define Red_ON()                            LL_GPIO_SetOutputPin(LED_RED_GPIO, LED_RED_PIN) 
#define Red_OFF()                           LL_GPIO_ResetOutputPin(LED_RED_GPIO, LED_RED_PIN)

#define Green_ON()                          LL_GPIO_SetOutputPin(LED_GREEN_GPIO, LED_GREEN_PIN)                                          
#define Green_OFF()                         LL_GPIO_ResetOutputPin(LED_GREEN_GPIO, LED_GREEN_PIN)  
                                          
#define ORG_ON()                            LL_GPIO_SetOutputPin(LED_ORG_GPIO, LED_ORG_PIN)                                            
#define ORG_OFF()                           LL_GPIO_ResetOutputPin(LED_ORG_GPIO, LED_ORG_PIN)  
                                           
#define Yellow_ON()                         LL_GPIO_SetOutputPin(LED_YELLOW_GPIO, LED_YELLOW_PIN)                                             
#define Yellow_OFF()                        LL_GPIO_ResetOutputPin(LED_YELLOW_GPIO, LED_YELLOW_PIN)  

/******************************************************************************/
/* KEY PIN IN MCU */
/******************************************************************************/
#define KEY_LRN1_GPIO                       (GPIOB)
#define KEY_LRN1_PIN                        (LL_GPIO_PIN_2)        

#if 0
/******************************************************************************/
/* RS485 Expand  -- uart4 */
/******************************************************************************/
#define RS485_EXPAND_TX_PIN (LL_GPIO_PIN_0)
#define RS485_EXPAND_TX_GPIO (GPIOA)
#define RS485_EXPAND_RX_PIN (LL_GPIO_PIN_1)
#define RS485_EXPAND_RX_GPIO (GPIOA)
#define RS485_EXPAND_DE_PIN (LL_GPIO_PIN_2)
#define RS485_EXPAND_DE_GPIO (GPIOD)
/******************************************************************************/
/* RS485 Modbus  -- uart3 */
/******************************************************************************/
#define RS485_MODBUS_TX_PIN (LL_GPIO_PIN_8)
#define RS485_MODBUS_TX_GPIO (GPIOB)
#define RS485_MODBUS_RX_PIN (LL_GPIO_PIN_9)
#define RS485_MODBUS_RX_GPIO (GPIOB)
#define RS485_MODBUS_DE_PIN (LL_GPIO_PIN_13)
#define RS485_MODBUS_DE_GPIO (GPIOC)
/******************************************************************************/
/* DALI */
/******************************************************************************/
#define DALI_RX_PIN (LL_GPIO_PIN_0)
#define DALI_RX_GPIO (GPIOD)

#define DALI_TX_PIN (LL_GPIO_PIN_15)
#define DALI_TX_GPIO (GPIOA)
/******************************************************************************/
/* KEY PIN IN MCU */
/******************************************************************************/
#define KEY_LRN1_GPIO (GPIOD)
#define KEY_LRN2_GPIO (GPIOC)
#define KEY_SET_GPIO (GPIOB)
#define KEY_LRN1_PIN (LL_GPIO_PIN_3)
#define KEY_LRN2_PIN (LL_GPIO_PIN_14)
#define KEY_SET_PIN (LL_GPIO_PIN_2)

/******************************************************************************/
/* 0-10V DC Output */
/******************************************************************************/
#define DC_OUTPUT1_GPIO (GPIOD)
#define DC_OUTPUT1_PIN (LL_GPIO_PIN_1)

/******************************************************************************/
/* Relay */
/******************************************************************************/
#define RELAY_SIG0_A_GPIO (GPIOB)
#define RELAY_SIG0_B_GPIO (GPIOC)
#define RELAY_SIG0_A_PIN (LL_GPIO_PIN_15)
#define RELAY_SIG0_B_PIN (LL_GPIO_PIN_7)

#define RELAY_SIG1_A_GPIO (GPIOA)
#define RELAY_SIG1_B_GPIO (GPIOC)
#define RELAY_SIG1_A_PIN (LL_GPIO_PIN_9)
#define RELAY_SIG1_B_PIN (LL_GPIO_PIN_7)

#define RELAY_SIG2_A_GPIO (GPIOA)
#define RELAY_SIG2_B_GPIO (GPIOC)
#define RELAY_SIG2_A_PIN (LL_GPIO_PIN_8)
#define RELAY_SIG2_B_PIN (LL_GPIO_PIN_7)

#define RELAY_SIG3_A_GPIO (GPIOC)
#define RELAY_SIG3_B_GPIO (GPIOC)
#define RELAY_SIG3_A_PIN (LL_GPIO_PIN_6)
#define RELAY_SIG3_B_PIN (LL_GPIO_PIN_7)

#define AC_ZERO_GPIO (GPIOB)
#define AC_ZERO_PIN (LL_GPIO_PIN_14)

#define AC_OUT_R0_GPIO (GPIOB)
#define AC_OUT_R0_PIN (LL_GPIO_PIN_11)
#define AC_OUT_R1_GPIO (GPIOB)
#define AC_OUT_R1_PIN (LL_GPIO_PIN_10)
#define AC_OUT_R2_GPIO (GPIOB)
#define AC_OUT_R2_PIN (LL_GPIO_PIN_12)
#define AC_OUT_R3_GPIO (GPIOB)
#define AC_OUT_R3_PIN (LL_GPIO_PIN_13)

#define RELAY1_ON()                                              \
    LL_GPIO_SetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_B_GPIO, RELAY_SIG0_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)
#define RELAY1_OFF()                                             \
    LL_GPIO_SetOutputPin(RELAY_SIG0_B_GPIO, RELAY_SIG0_B_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_SetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)
#define RELAY1_IDLE()                                            \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_B_GPIO, RELAY_SIG0_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)

#define RELAY3_ON()                                              \
    LL_GPIO_SetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_B_GPIO, RELAY_SIG1_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)
#define RELAY3_OFF()                                             \
    LL_GPIO_SetOutputPin(RELAY_SIG1_B_GPIO, RELAY_SIG1_B_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN); \
    LL_GPIO_SetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)
#define RELAY3_IDLE()                                            \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_B_GPIO, RELAY_SIG1_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)

#define RELAY0_ON()                                              \
    LL_GPIO_SetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_B_GPIO, RELAY_SIG2_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)
#define RELAY0_OFF()                                             \
    LL_GPIO_SetOutputPin(RELAY_SIG2_B_GPIO, RELAY_SIG2_B_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_SetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)
#define RELAY0_IDLE()                                            \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_B_GPIO, RELAY_SIG2_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN)

#define RELAY2_ON()                                              \
    LL_GPIO_SetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_B_GPIO, RELAY_SIG3_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN)
#define RELAY2_OFF()                                             \
    LL_GPIO_SetOutputPin(RELAY_SIG3_B_GPIO, RELAY_SIG3_B_PIN);   \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN); \
    LL_GPIO_SetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN);   \
    LL_GPIO_SetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN)
#define RELAY2_IDLE()                                            \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_A_GPIO, RELAY_SIG3_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG3_B_GPIO, RELAY_SIG3_B_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG0_A_GPIO, RELAY_SIG0_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG2_A_GPIO, RELAY_SIG2_A_PIN); \
    LL_GPIO_ResetOutputPin(RELAY_SIG1_A_GPIO, RELAY_SIG1_A_PIN)

/******************************************************************************/
/* RS485 Cascade  -- uart1 */
/******************************************************************************/
#define RS485_CASCADE_TX_PIN (LL_GPIO_PIN_6)
#define RS485_CASCADE_TX_GPIO (GPIOB)
#define RS485_CASCADE_RX_PIN (LL_GPIO_PIN_7)
#define RS485_CASCADE_RX_GPIO (GPIOB)

#define RS485_CASCADE_DE_PIN (LL_GPIO_PIN_3)
#define RS485_CASCADE_DE_GPIO (GPIOB)
/******************************************************************************/
/* TCM310  -- uart2 */
/******************************************************************************/
#define ENOCEAN_RX_PIN (LL_GPIO_PIN_3)
#define ENOCEAN_RX_GPIO (GPIOA)

#define ENOCEAN_TX_PIN (LL_GPIO_PIN_2)
#define ENOCEAN_TX_GPIO (GPIOA)

#define ENOCEAN_RST_PIN (LL_GPIO_PIN_4)
#define ENOCEAN_RST_GPIO (GPIOA)

#define ENOCEAN_HARDWARE_RST_DISABLE() LL_GPIO_ResetOutputPin(ENOCEAN_RST_GPIO, ENOCEAN_RST_PIN)
#define ENOCEAN_HARDWARE_RST_ENABLE() LL_GPIO_SetOutputPin(ENOCEAN_RST_GPIO, ENOCEAN_RST_PIN)

/******************************************************************************/
/* IIC */
/******************************************************************************/
#define IIC_M24XX_SDA_GPIO (GPIOB)
#define IIC_M24XX_SCL_GPIO (GPIOB)
#define IIC_M24XX_SDA_PIN (LL_GPIO_PIN_5)
#define IIC_M24XX_SCL_PIN (LL_GPIO_PIN_4)

/******************************************************************************/
/* TM1617 */
/******************************************************************************/
#define TM1617_DATA_GPIO (GPIOA)
#define TM1617_CLK_GPIO (GPIOA)
#define TM1617_STB_GPIO (GPIOA)
#define TM1617_DATA_PIN (LL_GPIO_PIN_10)
#define TM1617_CLK_PIN (LL_GPIO_PIN_11)
#define TM1617_STB_PIN (LL_GPIO_PIN_12)

/******************************************************************************/
/* DIP Switch */
/******************************************************************************/
#define SWITCH1_GPIO (GPIOA)
#define SWITCH2_GPIO (GPIOA)
#define SWITCH3_GPIO (GPIOA)
#define SWITCH4_GPIO (GPIOB)
#define SWITCH5_GPIO (GPIOB)

#define SWITCH1_PIN (LL_GPIO_PIN_5)
#define SWITCH2_PIN (LL_GPIO_PIN_6)
#define SWITCH3_PIN (LL_GPIO_PIN_7)
#define SWITCH4_PIN (LL_GPIO_PIN_0)
#define SWITCH5_PIN (LL_GPIO_PIN_1)
#endif         

#endif
/* End of file */
