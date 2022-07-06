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

#define PMSA_USART_DMA_CHANNEL_TX           (LL_DMA_CHANNEL_1)
#define PMSA_USART_DMA_CHANNEL_RX           (LL_DMA_CHANNEL_2)
 
#define ENOCEAN_DMA_CHANNEL_TX              (LL_DMA_CHANNEL_3)

#define RS485_MODBUS_DMA_CHANNEL_TX         (LL_DMA_CHANNEL_4)
#define RS485_MODBUS_DMA_CHANNEL_RX         (LL_DMA_CHANNEL_5)

#define CH2O_CO2_USART_DMA_CHANNEL_TX       (LL_DMA_CHANNEL_6)
#define CH2O_CO2_USART_DMA_CHANNEL_RX       (LL_DMA_CHANNEL_7)


#define RS485_MODBUS_USART                  (USART1)    
#define RS485_MODBUS_USART_IRQ              (USART1_IRQn)    
#define RS485_MODBUS_DMA_TX_REQ             LL_DMAMUX_REQ_USART1_TX
#define RS485_MODBUS_DMA_RX_REQ             LL_DMAMUX_REQ_USART1_RX
//#define RS485_MODBUS_TX_BUFF                (128)
//#define RS485_MODBUS_RX_BUFF                (128)

#define PMSA_USART                          (USART2)
#define PMSA_USART_IRQ                      (USART2_IRQn)
#define PMSA_USART_DMA_TX_REQ               LL_DMAMUX_REQ_USART2_TX
#define PMSA_USART_DMA_RX_REQ               LL_DMAMUX_REQ_USART2_RX
#define PMSA_TX_BUFF                        (64)
#define PMSA_RX_BUFF                        (64)

#define ENOCEAN_USART                       (USART3)
#define ENOCEAN_USART_IRQ                   (USART3_4_IRQn)
#define ENOCEAN_USART_DMA_TX_REQ            LL_DMAMUX_REQ_USART3_TX  

#define CH2O_CO2_USART                      (USART4)
#define CH2O_CO2_USART_IRQ                  (USART3_4_IRQn)
#define CH2O_CO2_USART_DMA_TX_REQ           LL_DMAMUX_REQ_USART4_TX 
#define CH2O_CO2_USART_DMA_RX_REQ           LL_DMAMUX_REQ_USART4_RX 
#define CH2O_CO2_TX_BUFF                    (64)
#define CH2O_CO2_RX_BUFF                    (64)


/******************************************************************************/
/* KEY PIN IN MCU */
/******************************************************************************/
#define KEY_LRN1_GPIO                       (GPIOB)
#define KEY_LRN1_PIN                        (LL_GPIO_PIN_2)

/******************************************************************************/
/* DIP swith PIN IN MCU */
/******************************************************************************/
/*
#define SWITCH1_GPIO                        (GPIOC)
#define SWITCH2_GPIO                        (GPIOA)
#define SWITCH3_GPIO                        (GPIOA)
#define SWITCH4_GPIO                        (GPIOA)

#define SWITCH1_PIN                         (LL_GPIO_PIN_7)
#define SWITCH2_PIN                         (LL_GPIO_PIN_10)
#define SWITCH3_PIN                         (LL_GPIO_PIN_11)
#define SWITCH4_PIN                         (LL_GPIO_PIN_12)
*/

#define SWITCH1_GPIO                        (GPIOA)
#define SWITCH2_GPIO                        (GPIOD)
#define SWITCH3_GPIO                        (GPIOD)
#define SWITCH4_GPIO                        (GPIOB)

#define SWITCH1_PIN                         (LL_GPIO_PIN_15)
#define SWITCH2_PIN                         (LL_GPIO_PIN_2)
#define SWITCH3_PIN                         (LL_GPIO_PIN_3)
#define SWITCH4_PIN                         (LL_GPIO_PIN_3)

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
/* RS485 Cascade  -- uart1  RX->PB7 TX->PB6 EN3->PB8 */
/******************************************************************************/    
#define RS485_MODBUS_TX_PIN                  (LL_GPIO_PIN_6)
#define RS485_MODBUS_TX_GPIO                 (GPIOB)
#define RS485_MODBUS_RX_PIN                  (LL_GPIO_PIN_7)
#define RS485_MODBUS_RX_GPIO                 (GPIOB)

#define RS485_MODBUS_DE_PIN                  (LL_GPIO_PIN_8)
#define RS485_MODBUS_DE_GPIO                 (GPIOB) 
/******************************************************************************/
/* PMSA003  -- uart2  RX->PA3 TX->PA2 RST->PD1 SET->PD0 */
/******************************************************************************/    
#define PMSA_TX_PIN                           (LL_GPIO_PIN_2)
#define PMSA_TX_GPIO                          (GPIOA)
#define PMSA_RX_PIN                           (LL_GPIO_PIN_3)
#define PMSA_RX_GPIO                          (GPIOA)

#define PMSA_RST_PIN                          (LL_GPIO_PIN_1)
#define PMSA_RST_GPIO                         (GPIOD)   
#define PMSA_SET_PIN                          (LL_GPIO_PIN_0)
#define PMSA_SET_GPIO                         (GPIOD)     
                                                
#define PMSA_RST_DISABLE()                    LL_GPIO_SetOutputPin(PMSA_RST_GPIO, PMSA_RST_PIN)  
#define PMSA_RST_ENABLE()                     LL_GPIO_ResetOutputPin(PMSA_RST_GPIO, PMSA_RST_PIN) 

#define PMSA_SET_DISABLE()                    LL_GPIO_ResetOutputPin(PMSA_SET_GPIO, PMSA_SET_PIN)  
#define PMSA_SET_ENABLE()                     LL_GPIO_SetOutputPin(PMSA_SET_GPIO, PMSA_SET_PIN)     


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
/* CH2O+CO2  -- uart4  RX->PA1 TX->PA0 CH2O_CO2_UARTA->PA4 CH2O_CO2_UARTB->PA5 */
/******************************************************************************/    
#define CH2O_CO2_TX_PIN                       (LL_GPIO_PIN_0)
#define CH2O_CO2_TX_GPIO                      (GPIOA)
#define CH2O_CO2_RX_PIN                       (LL_GPIO_PIN_1)
#define CH2O_CO2_RX_GPIO                      (GPIOA)

#define CH2O_CO2_UARTA_PIN                    (LL_GPIO_PIN_4)
#define CH2O_CO2_UARTA_GPIO                   (GPIOA)   
#define CH2O_CO2_UARTB_PIN                    (LL_GPIO_PIN_5)
#define CH2O_CO2_UARTB_GPIO                   (GPIOA)     
                                               /*Set输出高电平  Reset输出低电平 BA  00->CH2O  01->CO2 */    
//#define CH2O_UART_SELECT()                    LL_GPIO_ResetOutputPin(CH2O_CO2_UARTA_GPIO, CH2O_CO2_UARTA_PIN) 
//                                              LL_GPIO_ResetOutputPin(CH2O_CO2_UARTB_GPIO, CH2O_CO2_UARTB_PIN) 

//#define CO2_UART_SELECT()                     LL_GPIO_SetOutputPin(CH2O_CO2_UARTA_GPIO, CH2O_CO2_UARTA_PIN)
//                                              LL_GPIO_ResetOutputPin(CH2O_CO2_UARTB_GPIO, CH2O_CO2_UARTB_PIN)                                                     
/******************************************************************************/
/* SHT20 IIC1 SDA->PB14 SCL->PB13 */
/******************************************************************************/
#define IIC1_SHT20_SDA_GPIO                   (GPIOB)
#define IIC1_SHT20_SCL_GPIO                   (GPIOC)
#define IIC1_SHT20_SDA_PIN                    (LL_GPIO_PIN_9)
#define IIC1_SHT20_SCL_PIN                    (LL_GPIO_PIN_13)
/******************************************************************************/
/* EEPROM IIC2 SDA->PB9 SCL->PC13 */
/******************************************************************************/
#define IIC2_EEPROM_SDA_GPIO                  (GPIOB)
#define IIC2_EEPROM_SCL_GPIO                  (GPIOC)
#define IIC2_EEPROM_SDA_PIN                   (LL_GPIO_PIN_14)
#define IIC2_EEPROM_SCL_PIN                   (LL_GPIO_PIN_13)                                                    

                    
#endif
/* End of file */
