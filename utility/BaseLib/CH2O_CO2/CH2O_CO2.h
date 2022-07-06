
#ifndef _CH2O_CO2_H_
#define _CH2O_CO2_H_

#include "platform.h"

/* ----------------------- Defines ------------------------------------------*/
typedef enum
{
    eCH2O_CO2_IDLE = 0x00,         //闲置状态
    eCH2O_CO2_RESET_STATUS = 0x01, //复位读状态
    eCH2O_CO2_WAIT_POWERON = 0x02, //上电等待

    eCH2O_START_MEASUREMENT = 0x03, //CH2O开始读数
    eCH2O_WAIT_MEASUREMENT = 0x04,  //等待读数
    eCH2O_READ_MEASUREMENT = 0x05,  //CH2O采样读数

    eCH2O_CO2_SWITCH_WAIT = 0x06, //温度和湿度切换等待时间

    eCO2_START_MEASUREMENT = 0x07, //开始读数
    eCO2_WAIT_MEASUREMENT = 0x08,  //等待读数
    eCO2_READ_MEASUREMENT = 0x09,  //读数

} eCH2O_CO2State_TYPE;

//-----------------------------------------------------------------------------
typedef enum //故障码
{
    eCH2O_NORMAL = 0x00,            //CH2O传感器正常
    eCH2O_ABNORMAL_DATA = 0x01,     //CH2O数据异常
    eCH2O_EXCEPTION_MESSAGE = 0x02, //CH2O报文异常
    eCH2O_EQUIPMENT_DROPS = 0x03,   //CH2O设备掉线



} eCH2O_FaultCode;

typedef enum //故障码
{

    eCO2_NORMAL = 0x00,            //CO2传感器正常
    eCO2_ABNORMAL_DATA,     //CO2数据异常
    eCO2_EXCEPTION_MESSAGE, //CO2报文异常
    eCO2_EQUIPMENT_DROPS,   //CO2设备掉线

} eCO2_FaultCode;


typedef struct
{
    eCH2O_CO2State_TYPE eRunState;
    eCH2O_FaultCode eCH2OFaultCode; //CH2O故障码
    eCO2_FaultCode  eCO2FaultCode;  //CO2故障码

    uint8_t u8CH2ODropscount; //CH2O掉线计数
    uint8_t u8CO2Dropscount;  //CO2掉线计数
    uint8_t u8CH2ODropsFlag;  //CH2O掉线标志
    uint8_t u8CO2DropsFlag;   //CO2掉线标志

    //uint16_t u16ReadPeriod;
    uint16_t u16ReadWait;
    uint32_t u32ReadPeriod;
    

    uint16_t u16CH2ONumerical;
    uint16_t u16CO2Numerical;

} CH2O_CO2_Typedef;

extern CH2O_CO2_Typedef CH2O_CO2;
extern USART_Function_Typedef CH2O_CO2_UART;
/**
   * @brief
   * @param
   * @retval
   */
uint8_t CH2O_CO2GetBusyState(void);
/**
   * @brief
   * @param
   * @retval
   */
uint8_t CH2O_CO2Init(USART_Function_Typedef *pUSART);
/**
 * @brief
 * @param
 * @retval None
 */
void CH2O_CO2_ChannelSwitch(CH2O_CO2_Typedef *pCH2O_CO2);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t CH2O_CO2SendOK(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t CH2O_CO2Reset(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t CH2O_CO2ReceiveOK(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t CH2O_CO2DevError(Serial_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
void CH2O_CO2_Tick1ms(CH2O_CO2_Typedef *pCH2O_CO2);
/**
 * @brief
 * @param
 * @retval
 */
void CH2O_CO2TestDriver(uint8_t *p8ReceiveBuff, uint8_t *p8SendBuff);
/**
   * @brief
   * @param
   * @retval
   */
void CH2O_CO2_OperationTask(CH2O_CO2_Typedef *pCH2O_CO2,uint32_t ReadPeriod);

/***********************************************************************************************************************/
/*******************************        CH2O函数                     ***************************************************/
/***********************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval
 */
uint8_t CH2O_CRC8(Serial_Typedef *pSerial);

uint8_t FucCheckSum(uint8_t *i, uint8_t l);
/**
 * @brief
 * @param
 * @retval None
 */
uint16_t CH2O_Active_Receive(Serial_Typedef *pSerial, uint16_t *pu16C2HO);
/**
 * @brief
 * @param
 * @retval None
 */
uint16_t CH2O_Passive_Receive(Serial_Typedef *pSerial, uint16_t *pu16C2HO);
/**
 * @brief
 * @param
 * @retval None
 */
void CH2O_ActiveSwitch_Send(Serial_Typedef *pSerial); //切换主动上报模式
/**
 * @brief
 * @param
 * @retval None
 */
void CH2O_PassiveSwitch_Send(Serial_Typedef *pSerial); //切换问答模式
/**
 * @brief
 * @param
 * @retval
 */
void CH2O_PassiveAsk_Send(Serial_Typedef *pSerial);

/***********************************************************************************************************************/
/**************************************** CO2函数        ***************************************************************/
/***********************************************************************************************************************/
/**
 * @brief
 * @param
 * @retval
 */
uint16_t Calculate_CRC16(uint8_t *cmd, uint8_t cmd_length);
/**
 * @brief
 * @param
 * @retval
 */
void CO2_Ask_Send(Serial_Typedef *pSerial); //查询
/**
 * @brief
 * @param
 * @retval None
 */
uint16_t CO2_Receive(Serial_Typedef *pSerial, uint16_t *pu16CO2); //被动模式数据处理

#endif

/* End of file */
