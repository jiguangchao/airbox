
#ifndef _RS485MB_H_
#define _RS485MB_H_

#include "platform.h"



/* ----------------------- Defines ------------------------------------------*/
#define MB_TIMER_PRESCALER                    ( TIM4_Prescaler_4 )
#define MB_TIMER_TICKS                        ( F_CPU / 4 )
#define MB_50US_TICKS                         (150)
#if 0
#define MB_ADDRESS_BROADCAST                  ( 0 )   /*! Modbus broadcast address. */
#define MB_ADDRESS_MIN                        ( 1 )   /*! Smallest possible slave address. */
#define MB_ADDRESS_MAX                        ( 247)  /*! Biggest possible slave address. */
#define MB_FUNC_NONE                          (  0 )
#define MB_FUNC_READ_COILS                    (  1 )
#define MB_FUNC_READ_DISCRETE_INPUTS          (  2 )
#define MB_FUNC_WRITE_SINGLE_COIL             (  5 )
#define MB_FUNC_WRITE_MULTIPLE_COILS          ( 15 )
#define MB_FUNC_READ_HOLDING_REGISTER         (  3 )
#define MB_FUNC_READ_INPUT_REGISTER           (  4 )
#define MB_FUNC_WRITE_REGISTER                (  6 )
#define MB_FUNC_WRITE_MULTIPLE_REGISTERS      ( 16 )
#define MB_FUNC_READWRITE_MULTIPLE_REGISTERS  ( 23 )
#define MB_FUNC_DIAG_READ_EXCEPTION           (  7 )
#define MB_FUNC_DIAG_DIAGNOSTIC               (  8 )
#define MB_FUNC_DIAG_GET_COM_EVENT_CNT        ( 11 )
#define MB_FUNC_DIAG_GET_COM_EVENT_LOG        ( 12 )
#define MB_FUNC_OTHER_REPORT_SLAVEID          ( 17 )
#define MB_FUNC_ERROR                         ( 128)
#endif




extern USART_Function_Typedef RS485Modbus;
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusGetBusyState(void);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusInit(USART_Function_Typedef *pUSART);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusSendOK(void);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusReset(Serial_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusReceiveOK(Serial_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval None
 */
uint8_t RS485ModbusDevError(Serial_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485ModbusRTUAbnormal(uint8_t *p8ReceiveBuff,uint8_t *p8SendBuff,uint8_t u8Code);

/**
 * @brief
 * @param
 * @retval
 */
uint8_t RS485ModbusRTU(uint8_t *p8ReceiveBuff,uint8_t *p8SendBuff,uint16_t *pu16Length);

/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/


/**
 * @brief
 * @param
 * @retval None
 */
uint8_t AppModbusSlave_BootReply(Serial_Typedef *pSerial);

#endif

/* End of file */
