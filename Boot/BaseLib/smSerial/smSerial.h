


#ifndef _SM_SERIAL_H_
#define _SM_SERIAL_H_



#define SERIAL_DATA_BUFF                                       (256)
#define SERIAL_TX_BUFF                                         (128)
#define SERIAL_RX_BUFF                                         (128)
#define SERIAL_IDLE_TIME_MS                                    (5)
#define SERIAL_RX_TX_SHIFT_TIME                                (20)
#define SERIAL_CONNECT_TIME                                    (30)
#define SERIAL_INTPERRUT_SEND_OVER_TIME                        (5000)

//#define SERIAL_CASCADE_DEBUG

#define SERIAL_CASCADE_MASTER_PERIOD                           (500)
#define SERIAL_CASCADE_OFFLINE_TIME                            (500)
#define SERIAL_CASCADE_END_INTERVAL                            (50)
#define SERIAL_CASCADE_DEV_INTERVAL                            (35)
#define SERIAL_CASCADE_DEV_NUMS_MAX                            (10)

#define SERIAL_CASCADE_RECEIVE_DMA_ENABLE                      (1)
#define SERIAL_CASCADE_RECEIVE_INTERRUPT_ENABLE                (0)
#define SERIAL_CASCADE_RECEIVE_OPTION                          (SERIAL_CASCADE_RECEIVE_DMA_ENABLE)

//#define SERIAL_
/* ----------------------- Defines ------------------------------------------*/

#define MB_ADDRESS_BROADCAST                  ( 0 )   /*! Modbus broadcast address. */
#define MB_ADDRESS_MIN                        ( 1 )   /*! Smallest possible slave address. */
#define MB_ADDRESS_MAX                        ( 247) /*! Biggest possible slave address. */
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



typedef enum
{
    eSERIAL_BUS_STATE_IDLE = 0,
    eSERIAL_BUS_STATE_INIT,

    eSERIAL_BUS_STATE_RECEIVE_OK,
    eSERIAL_BUS_STATE_SEND_DATA_PREPAIR ,
    eSERIAL_BUS_STATE_SEND_DATA,
    eSERIAL_BUS_STATE_SEND_DATA_OK,

    eSERIAL_BUS_STATE_WAIT_RECEIVE,
    eSERIAL_BUS_STATE_SEND_TO_RECEIVE_WAIT,
    eSERIAL_BUS_STATE_SEND_TO_IDLE,
    eSERIAL_BUS_STATE_MASTER_WAIT_SLAVE_RESPONSE,

    eSERIAL_BUS_STATE_RESET_SLAVE,
    eSERIAL_BUS_STATE_ERROR_SLAVE,

    
    //eTX_FRAME_TIME,
}eSERIAL_BUS_STATE_TYPE;




extern const eUSART_BAUD_TYPE eBaudRateTab[];
extern const uint16_t u16SendOneByteNeed_N_Us[];
extern const uint8_t u8BaudRateBytePeriodNmsConfigTab[];
extern const uint8_t u8SerialRxTxShiftTimeConfigTab[];
//extern const USART_WordLength_TypeDef u8DataBits[];
//extern const eUSART_PARITY_TYPE eParity[];

/*******************************************************************************************/


typedef struct UsartFunction_t   USART_Function_Typedef;
typedef struct Serial_Frame      Serial_Typedef;
typedef uint8_t (*SerialReturnState_Typedef)(Serial_Typedef *pSerial);


typedef struct CascadeFunction_t Cascade_Function_Typedef;
typedef struct SerialCascade     SerialCascade_Typedef; 
typedef uint8_t (*SerialCascadeState_Typedef)(SerialCascade_Typedef *pSerial);


typedef void (*SerialPara_Typedef)(uint16_t u16SendMax);
typedef uint8_t (*SerialNoPara_Typedef)(void);



struct Serial_Frame
{
    //uint8_t                   u8DR;
    uint16_t                  u16SendBytesCnt;
    uint16_t                  u16ReceiveBytesCnt;

    uint16_t                  u16SendBytesMax;
    uint8_t                   *pu8Send;

    uint16_t                  u16ReceiveBuffMax;
    uint16_t                  u16ReceiveBytesMax;
    uint8_t                   *pu8Receive;
    uint8_t                   *pu8DMAReceive;

    eSERIAL_BUS_STATE_TYPE    eRxState;                          
    eSERIAL_BUS_STATE_TYPE    eTxState;

    uint8_t                   u8MasterSendPhyID;
    uint16_t                  u16MasterSendRegStart;
    uint16_t                  u16MasterSendRegNumsOrValue;

    uint16_t                  u16SlaveReceiveRegStart;
    uint16_t                  u16SlaveReceiveRegNums;

    uint8_t                   u8MessageType;
    uint16_t                  u16WaitReceiveOverNms; 
    /* RX to TX or Tx to RX time*/
    uint8_t                   u8RxTxShiftNms;
    /* Slave devices is not useful, because the master will retransmit data to the slave */
    uint8_t                   u8RetransCnt;
    uint16_t                  u16Error;
    uint16_t                  u16SendOverNms;
    uint16_t                  u16SendPeriod;
    uint8_t                   u8DataUpdateLock;

    uint8_t                   u8Parity;
    uint8_t                   u8Stop;
    uint8_t                   u8BaudID;
    /* Uart rx one byte by the interrupt */
    
    uint8_t                   u8IdleNms;
    uint8_t                   u8IdleNmsConfig;       
    
    uint32_t                  u32ReceiveCount;
    uint32_t                  u32SendCount;
    
    uint8_t                   *pu8PhyAddress;
};

struct SerialCascade
{
    uint16_t                  u16SendBytesMax;    
    uint8_t                   *pu8Send;

    uint16_t                  u16ReceiveBuffMax;
    uint16_t                  u16ReceiveBytesMax;    
    uint8_t                   *pu8Receive;
    uint8_t                   *pu8DMAReceive;
                              
    eSERIAL_BUS_STATE_TYPE    eState;
    uint8_t                   u8SendCmd;
    //uint8_t                   u8ReceiveCmd;
    uint16_t                  u16SearchAddressPeriodNms;
    uint8_t                   u8SearchAddressCount;
    uint8_t                   u8AddressMax;
    //uint8_t                   u8AddressPre;
    uint8_t                   u8SendState;
    uint8_t                   u8DataUpdateLock;
    
    /* RX to TX or Tx to RX time*/
    uint8_t                   u8RxTxShiftNms;
    uint16_t                  u16SendOverNms;
    uint16_t                  u16BusIdleNms;
    uint16_t                  u16SlaverDelaySendNms;    
    uint16_t                  u16MasterSendPeriodNms;

    uint8_t                   u8SendOccupyCount;
    uint8_t                   u8ReceiveWaitCount;

    /* The bus max device's numbers  < 16 */
    uint16_t                  *pu16OnlineMask;
    uint16_t                  u16OfflineTime[SERIAL_CASCADE_DEV_NUMS_MAX];
    uint8_t                   *pu8OnlineNums;
    /* Source Address */         
    uint8_t                   u8SrcAddress;
    /* Destination Address */
    uint8_t                   u8DstAddress;                            
        
    /* Slave devices is not useful, because the master will retransmit data to the slave */
    //uint8_t                   u8RetransCnt;
    //uint16_t                  u16Error;
    
    
    uint8_t        u8Parity;
    uint8_t          u8Stop;
    uint8_t       u8BaudID;
    /* Uart rx one byte by the interrupt */   
    uint32_t                  u32ReceiveCount;
    uint32_t                  u32SendCount;
    uint32_t                  u32SlaverReceiveMasterCount;

    uint8_t                   u8BusBusyState;
    uint8_t                   *pu8PhyAddress;
};
/*******************************************************************************************/

//typedef uint8_t (*SerialReturnCB_Typedef)(Serial_Typedef *pSerial);



struct UsartFunction_t
{
    Serial_Typedef                  Frame;
    SerialReturnState_Typedef       SerialDevInit;
    SerialReturnState_Typedef       SerialDevReset;
    SerialReturnState_Typedef       SerialReceiveOK;
    SerialReturnState_Typedef       SerialDevError;
    SerialReturnState_Typedef       SerialSendPrepair;
    
    /* Hardware controll */
    SerialPara_Typedef              pStart;
    SerialNoPara_Typedef            pStop;
    SerialNoPara_Typedef            pSend;
    SerialNoPara_Typedef            pReceive;
    SerialNoPara_Typedef            pDMARxConfig;
    SerialNoPara_Typedef            pDMATxConfig;
    SerialNoPara_Typedef            pDMATxSendStatus;
    SerialNoPara_Typedef            pGetBusBusy;
};


struct CascadeFunction_t
{
    SerialCascade_Typedef            Frame;
    SerialCascadeState_Typedef       SerialDevInit;
    SerialCascadeState_Typedef       SerialDevReset;
    SerialCascadeState_Typedef       SerialReceiveOK;
    SerialCascadeState_Typedef       SerialDevError;
    SerialCascadeState_Typedef       SerialSendPrepair;
    
    /* Hardware controll */
    SerialPara_Typedef              pStart;
    SerialNoPara_Typedef            pStop;
    SerialNoPara_Typedef            pSend;
    SerialNoPara_Typedef            pReceive;
    SerialNoPara_Typedef            pGetBusBusy;
};
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_Time_1ms(USART_Function_Typedef *pUSART);
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_Time_100ms(USART_Function_Typedef *pUSART);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_GetStateOfSendPeriod(Serial_Typedef *pSerial,uint16_t u16SendPeriod);
/**
  * @brief
  * @param
  * @retval None
  */
void USART_ReceiveFrameCount(Serial_Typedef *pSerial);
/**
   * @brief
   * @param
   * @retval
   */
uint8_t USART_GetBusyState(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_StateSetSend(Serial_Typedef *pSerial,uint16_t u16SendMax,uint8_t u8MessageType,uint16_t u16WaitOverTime);
/**
  * @brief
  * @param
  * @retval None
  */
void USART_SetSendRetryCount(Serial_Typedef *pSerial,uint8_t u8RetryCount);
/**
  * @brief
  * @param
  * @retval None
  */
void USART_ClearSendRetryCount(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_GetSendRetryCount(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_SendOK(Serial_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_StateMachineHandler(USART_Function_Typedef *pUSART);
/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_IdleInterruptGetDMABuff(Serial_Typedef *pSerial);
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t USART_GetSendbuff(Serial_Typedef *pSerial,uint8_t *pu8Data);
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_slave_get_receive_regs_info(Serial_Typedef *pSerial,uint16_t u16RegStart,uint16_t u16RegNums);
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_slave_receive_interrupt(Serial_Typedef *pSerial,uint8_t u8Data);
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_master_get_write_regs_success_status(Serial_Typedef *pSerial);
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_master_send_setting(Serial_Typedef *pSerial,uint8_t u8Cmd,uint8_t u8SendPhyID,uint16_t u16RegStart,uint16_t u16RegNums);
/**
 * @brief  
 * @param
 * @retval None
 */
uint8_t UART_modbus_master_receive_interrupt(Serial_Typedef *pSerial,uint8_t u8Data);

#ifdef MODBUS_MASTER_TX_QUEUE_MAX
    typedef struct
    {
        //uint8_t  u8Cmd;
        uint8_t  u8State;
        uint16_t u16WaitOverSet;
        // rock expand DI or enocean
        uint8_t  u8MessageType;

        uint8_t  u8Cmd;
        uint8_t  u8PhyAddress;
        uint16_t u16RegStart;
        uint16_t u16RegNums;
        uint16_t u16RegValue;

        uint8_t  u8Byte[128];    
        
    }ModbusMasterSend_Typedef;

    typedef struct
    {
        uint8_t  u8QueueFull;
        uint8_t  u8PushCount;
        uint8_t  u8PopCount;
        
        ModbusMasterSend_Typedef Data[MODBUS_MASTER_TX_QUEUE_MAX];

    }ModbusMasterSendQueue_Typedef;
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_ClearSendQueuePopID(ModbusMasterSendQueue_Typedef *pQueue);
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_GetQueueData(ModbusMasterSendQueue_Typedef *pQueue,uint8_t *u8PhyAddress,uint8_t *pu8Cmd,uint16_t *pu16RegID,uint16_t *pu16RegNums,uint16_t *pu16RegValue);
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_SetQueueData(ModbusMasterSendQueue_Typedef *pQueue,uint8_t u8PhyAddress,uint8_t u8Cmd,uint16_t u16RegID,uint16_t u16RegNums,uint16_t u16RegValue);
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t UART_modbus_master_GetSendQueuePopID(ModbusMasterSendQueue_Typedef *pQueue);
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t UART_modbus_master_GetSendQueueFull(ModbusMasterSendQueue_Typedef *pQueue);
    /**
     * @brief
     * @param
     * @retval None
     */
    void UART_modbus_master_SetSendQueueIDOccupy(ModbusMasterSendQueue_Typedef *pQueue);
    /**
     * @brief
     * @param
     * @retval None
     */
    uint8_t UART_modbus_master_GetSendQueuePushID(ModbusMasterSendQueue_Typedef *pQueue);
#endif    
/***********************************************************************************/

/**
  * @brief
  * @param
  * @retval None
  */            
void USART_CascadeTime_1ms(Cascade_Function_Typedef *pUSART);
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_CascadeTime_100ms(Cascade_Function_Typedef *pUSART);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t UASRT_CascadeFrameSendTime(SerialCascade_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t UASRT_CascadeFrameSendOK(SerialCascade_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */            
void USART_CascadeReceiveClear(SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval None
 */ 
uint8_t USART_CascadeGetOnlineDevNums(SerialCascade_Typedef *pSerial);
/**
 * @brief
 * @param
 * @retval None
 */ 
void USART_CascadeGetOnlineDevMask(SerialCascade_Typedef *pSerial);
/**
  * @brief
  * @param
  * @retval None
  */ 
uint8_t USART_CascadePhyAddressGetOnline(SerialCascade_Typedef *pSerial,uint8_t u8PhyAdd);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t USART_CascadeHandler(Cascade_Function_Typedef *pUSART);
/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_CascadeMasterSetFinallyAddress(SerialCascade_Typedef *pSerial);
/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_CascadeMasterSetTimeSequential(SerialCascade_Typedef *pSerial);

/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_CascadeReceiveFrameTime(SerialCascade_Typedef *pFrame);
/**
  * @brief  
  * @param
  * @retval None
  */
uint8_t USART_IdleInterruptCascadeGetDMABuff(SerialCascade_Typedef *pSerial);
/*******************************************************************************************/
#endif
/* End of file */
