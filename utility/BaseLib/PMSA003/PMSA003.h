
#ifndef _PMSA_H_
#define _PMSA_H_

#include "platform.h"

/* ----------------------- Defines ------------------------------------------*/
typedef enum
{
  ePMSA_IDLE = 0x00,        //闲置状态
  ePMSA_PERIOD_WAIT, //周期等待
  ePMSA_INITIALIZE_STATE,//初始化状态
  ePMSA_WAIT_STATUS , //等待复位
  ePMSA_SET_WORKMODE , //设置工作模式
  ePMSA_STARTWORT,   //开始工作
  ePMSA_START_MEASUREMENT , //PMSA开始读数
  ePMSA_WAIT_MEASUREMENT ,  //等待读数
  ePMSA_READ_MEASUREMENT ,  //PMSA采样读数

} ePMSAState_TYPE;

typedef enum //故障码
{
  ePMSA_NORMAL = 0x00,            //传感器正常
  ePMSA_ABNORMAL_DATA = 0x01,     //数据异常
  ePMSA_EXCEPTION_MESSAGE = 0x02, //报文异常
  ePMSA_EQUIPMENT_DROPS = 0x03,   //设备掉线

} ePMSA_FaultCode;

//-----------------------------------------------------------------------------

typedef struct
{
  ePMSAState_TYPE eRunState;
  ePMSA_FaultCode eFaultCode; //故障码

  uint8_t u8PMSADropsFlag;  //掉线标志
  uint8_t u8PMSADropscount; //掉线计数

  uint16_t u16CrcTest1;      //crc测试
  uint16_t u16CrcTest2;      //crc测试


  uint16_t u16ReadPeriod;
  uint32_t u32ReadWait;
  uint32_t u32Dormancywait;

  //uint8_t u8FailureState;

  uint16_t u16PM10Numerical;
  uint16_t u16PM25Numerical;
  uint16_t u16PM100Numerical;

  //USART_Function_Typedef  pUSART2;
  //Serial_Typedef  Frame;

} PMSA_Typedef;
/* ----------------------- Defines ------------------------------------------*/
extern PMSA_Typedef PMSA;
extern USART_Function_Typedef PMSA_UART;

/**
   * @brief
   * @param
   * @retval
   */
uint8_t PMSAGetBusyState(void);
/**
   * @brief
   * @param
   * @retval
   */
uint8_t PMSAInit(USART_Function_Typedef *pUSART);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t PMSASendOK(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t PMSAReset(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t PMSAReceiveOK(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t PMSADevError(Serial_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval
 */
void PMSATestDriver(uint8_t *p8ReceiveBuff, uint8_t *p8SendBuff);
/**
   * @brief
   * @param
   * @retval
   */
void PMSA_Tick1ms(PMSA_Typedef *pPMSA);
/**
   * @brief
   * @param
   * @retval
   */
void PMSA_OperationTask(PMSA_Typedef *pPMSA,uint32_t ReadPeriod,uint32_t Dormancywait) ;
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**
   * @brief
   * @param
   * @retval
   */
static uint16_t PMS03CRC(uint8_t DataBuf[], uint16_t DataCnt);
/**
 * @brief
 * @param
 * @retval
 */
void PMSA_ActiveSwitch_Send(Serial_Typedef *pSerial); //切换主动上报模式
/**
 * @brief
 * @param
 * @retval
 */
void PMSA_PassiveSwitch_Send(Serial_Typedef *pSerial); //切换问答模式
/**
 * @brief
 * @param
 * @retval
 */
void PMSA_PassiveAsk_Send(Serial_Typedef *pSerial); //查询
/*
 * 功能： 从PM2应答消息中解析出PM2浓度
 * 参数： msgdata： PM2应答的数据，长度必须 >= 32，否则解析失败
 * 返回值 > 0 ：正常
 * 返回值 <= 0 : 解析错误
 */
uint16_t PMSA_Receive(Serial_Typedef *pSerial);

#endif

/* End of file */
