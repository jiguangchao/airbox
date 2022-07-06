//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __UPDATE_MODBUS_H__
#define __UPDATE_MODBUS_H__


/*******************************************************************************/
#define REG_UPDATA_VERSION                           (0x1801)
#define REG_TOTAL_MESAAGE_NUM                        (0x1802)
#define REG_CHECKSUM_HIGH                            (0x1805)
#define REG_UPDATA_STAR_WORD                         (0x1800)
#define REG_CHECKSUM_LOW                             (0x1806)
            
#define REG_SLAVE_STATUS_WORD                        (0x1810)
#define REG_REQUEST_SERIAL                           (0x1811)
            
#define REG_UPDATA_CURRENT_SERIAL                    (0x187F)  //129 register
#define REG_MESSAGE_FIRST_TWO_BYTE                   (0x1880)
#define REG_MESSAGE_LAST_TWO_BYTE                    (0x18BF)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define STAR_UPDATA_WORD                             (0x3589)  //升级字
#define RESTAR_UPDATA_WORD                           (0x3795)  //重新开始升级
#define UPDATA_VERSION                               (0x0001)  //升级方法版本
#define MIN_MESSAGE_NUM                              (3)//10
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



#define APP_MODBUS_MESSAGE_BYTE_NUMS                 (128)
#define APP_NEED_UPGRADE_UPDATING                    (0x8D731A75)
#define APP_NEED_UPGRADE_COMPLETE                    (0x519AE493)

#define BOOT_NEED_UPGRADE_UPDATING                   (0xD837A157)
#define BOOT_NEED_UPGRADE_COMPLETE                   (0x15A94E39)

#define CHECK_SUM_WORD_EVEN                          (0x39EA2E76)
#define CHECK_SUM_WORD_ODD                           (0x82B453C3)
/*******************************************************************************/
#define APP_INFO_WORDS_LENGTH                        (32)
#if ((APP_INFO_WORDS_LENGTH%2) > 0)
    #error macro APP_INFO_WORDS_LENGTH define must be odd
#endif

#define APP_INFO_OFFSET                              (APP_INFO_WORDS_LENGTH>>1)

#define APP_INFO_UPGRADE_COUNT                       (0)
#define APP_INFO_UPGRADE_STATUS                      (1)
#define APP_INFO_UPGRADE_CHECK_SUM                   (2)
#define APP_INFO_UPGRADE_CODE_SIZE                   (3)
#define APP_INFO_UPGRADE_FILE_MAP_VERSION            (4)

#define APP_INFO_HW_PHY_BAUD_STOP_PARITY             (5)

#define APP_INFO_HW_PHY_ADDRESS                      (5)
#define APP_INFO_HW_BAUD_ID                          (6)
#define APP_INFO_HW_STOP                             (7)
#define APP_INFO_HW_PARITY                           (8)

#define APP_INFO_HW_UPDATE_VERSION                   (9)
#define APP_INFO_TOTAL_MESSAGE_NUM                   (10)
#define APP_INFO_CHECK_SUM                           (11)
#define APP_INFO_UPDATE_STATUS                       (12)
#define APP_INFO_HW_SIGN                             (13)
#define APP_INFO_HW_UPGRADE_PORT                     (14)
#define APP_INFO_HW_ENOCEAN_CHIP_ID                  (15)

/*********************************************************************/
typedef enum
{
    eBOOT_RUN_STATE_IDLE              = 0x00,//等待完成收到数据，或上电检测跳转
    eBOOT_RUN_STATE_WRITE_APP_INFO    = 0x01,//上电复位直接跳转
    eBOOT_RUN_STATE_WAIT_CLOSE        = 0x02,//等待启动程序通信完成
    eBOOT_RUN_STATE_CLOSE_PERIPHERAL  = 0x03,//等待启动程序通信完成
    eBOOT_RUN_STATE_CHECK_APP_VERSION = 0x04,//检查是否需要升级，如果版本没有升级直接跳转到应用区
    eBOOT_RUN_STATE_CHECK_APP_LEGAL   = 0x05,//合法性检测,跳转到应用区
    //eBOOT_RUN_STATE_APP                 = 0x04,//在Boot区运行    
}eBootState_TYPE;

typedef enum
{
    eUPDATE_STATE_WAIT               =           0,//空闲状态
    eUPDATE_STATE_START              =           1,//升级开始
    eUPDATE_STATE_FILE_MAP           =           2,//升级应用区信息
    eUPDATE_STATE_CODE               =           3,//升级代码
    eUPDATE_STATE_SUCCESS            =           4,//升级成功
    eUPDATE_STATE_CHECKSUM_ERROR     =           5,//
    eUPDATE_STATE_VERSION_TYPE_ERROR =           6,
    eUPDATE_STATE_SN_ERROR           =           7,
    
}eUpdateState_TYPE;

typedef enum
{
    
    eAPP_INFO_OK                = 0x00,
    eAPP_INFO_NULL              = 0x01,
    eAPP_INFO_ERROR             = 0x02,

}eAppInfoUpdate_TYPE;

/**
 * @brief  用于写入一个页里面部分数据
 * @param  u32Address : Flash 地址
 *         *pu32WrBuff: 写入32位缓冲数据
 *         u8Start    : 一个页写入偏移
 *         u8Nums     : 一次写入数据，不超过一个页总数据量
 * @retval None
 */
void UpgradeModbus_WriteNWordsInOnePage(uint32_t u32Address,uint32_t* pu32WrBuff,uint16_t u16Start,uint16_t u16Nums);
/**
 * @brief  用于读取一个页里面部分数据，一个页有512字节，128个字，每次写入不需要对整个页数据全部处理
 * @param
 * @retval None
 */
void UpgradeModbus_ReadNWordsInOnePage(uint32_t u32Address,uint32_t* pu32Buff,uint16_t u16Nums);
/**
 * @brief  读取flash的数据流
 * @param
 * @retval None
 */
void UpgradeModbus_ReadAppArea4Bytes(uint32_t in_offset_addr,uint8_t* out_pData);


#if UPGRADE_MODBUS_BOOT > 0
    /**
     * @brief  
     * @param
     * @retval None
     */
    void UpgradeModbus_GetDefaultHardwareInfo(uint8_t *pu8PhyAdd, uint8_t *pu8BaudID, uint8_t *pu8Stops, uint8_t *pu8Parity,uint8_t *u8PortType,uint32_t *pu32DstID);
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbusResetReply(uint8_t *p8SendBuff,uint8_t u8PhyAdd,uint16_t *pu16Length);
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbusReceiveReply(uint8_t *p8ReceiveBuff,uint8_t *p8SendBuff,uint16_t *pu16Length);
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbus_GetStatus (uint32_t *pu32UpgradeStatus);
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbus_WriteAppInfomationAndReset(uint8_t u8PhyAddress,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity,uint8_t u8PortType);
    /**
     * @brief  程序跳转到应用区
     * @param
     * @retval None
     */
    void UpgradeModbus_BootJumpToApp(void);
#endif    





#if UPGRADE_MODBUS_APP > 0
    /**
     * @brief
     * @param
     * @retval
     */
    void UpgradeModbus_SlaveReceive(uint8_t *pu8uff,\
                                uint16_t u16ForwardNums,\
                                uint8_t u8PortType,\
                                uint8_t u8PhyAdd,\
                                uint8_t u8BaudID,\
                                uint8_t u8Stops,\
                                uint8_t u8Parity,\
                                uint32_t u32DstID);
    /**
     * @brief  
     * @param        
     * @retval None
     */
    void UpgradeModbus_SelfCheckAppInfo(uint8_t u8PhyAdd,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity);
#endif

#endif
//++++++++++++++++++++++++++++++++++End++++++++++++++++++++++++++++++++++++++++
