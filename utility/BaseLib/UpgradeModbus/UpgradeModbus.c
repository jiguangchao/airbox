/*============================ INCLUDES ======================================*/
#include "..\BaseLibInclude.h"


uint32_t            u32PageBuff[CHIP_FLASH_PAGE_WORD_SIZE];
/**
 * @brief  用于写入一个页里面部分数据
 * @param  u32Address : Flash 地址
 *         *pu32WrBuff: 写入32位缓冲数据
 *         u8Start    : 一个页写入偏移
 *         u8Nums     : 一次写入数据，不超过一个页总数据量
 * @retval None
 */
void UpgradeModbus_WriteNWordsInOnePage(uint32_t u32Address,uint32_t* pu32WrBuff,uint16_t u16Start,uint16_t u16Nums)
{
    uint32_t u32PageFirstAddress ;
    uint16_t u16StartOffset;
    uint16_t i;
    

    if ( (u16Start+u16Nums) > CHIP_FLASH_PAGE_WORD_SIZE)
    {
        return;
    }

    u16StartOffset = u16Start;
    u32PageFirstAddress = u32Address - u32Address%CHIP_FLASH_PAGE_BYTES_SIZE;
    /**/
    for(i = 0; i < CHIP_FLASH_PAGE_WORD_SIZE; i++)
    {
        u32PageBuff[i] = *((uint32_t *)(u32PageFirstAddress + i * 4));
    }
    
    for(i = 0; i < u16Nums; i++)
    {
        u32PageBuff[i + u16StartOffset] = pu32WrBuff[i];
    }

    NVM_FLASH_WriteNWords(u32PageFirstAddress,u32PageBuff,CHIP_FLASH_PAGE_WORD_SIZE);
}
/**
 * @brief  用于读取一个页里面部分数据，一个页有512字节，128个字，每次写入不需要对整个页数据全部处理
 * @param
 * @retval None
 */
void UpgradeModbus_ReadNWordsInOnePage(uint32_t u32Address,uint32_t* pu32Buff,uint16_t u16Nums)
{
    uint16_t i;
    uint32_t u32ReadAddr;

    u32ReadAddr = u32Address ;
    for (i = 0; i < u16Nums;i++)
    {
        pu32Buff[i] = *((uint32_t *)(u32ReadAddr + i * 4));
    }
}
/**
 * @brief  读取flash的数据流
 * @param
 * @retval None
 */
void UpgradeModbus_ReadAppArea4Bytes(uint32_t in_offset_addr,uint8_t* out_pData)
{
    uint32_t  word = 0;
    uint32_t  addr = 0;

    if((APP_ADDRESS_START + in_offset_addr) > APP_ADDRESS_END)//地址保护
    {
        return;
    }
    addr = (APP_ADDRESS_START + in_offset_addr);
    word = *((uint32_t *)(addr));   

    out_pData[0] = (uint8_t)((word >>  0) & 0x000000FF);
    out_pData[1] = (uint8_t)((word >>  8) & 0x000000FF); 
    out_pData[2] = (uint8_t)((word >> 16) & 0x000000FF); 
    out_pData[3] = (uint8_t)((word >> 24) & 0x000000FF); 
}
    

#if UPGRADE_MODBUS_BOOT > 0
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    eUpdateState_TYPE   eUpdateState = eUPDATE_STATE_WAIT;
    eBootState_TYPE     eBootState;

    uint16_t            u16FirewareBlockID;
    uint16_t            u16UpgradeMessageCurrentID;
    uint32_t            u32UpgradeCodeByteSize;    
    uint16_t            u16UpgradeMessageTotalNum;    
    uint16_t            u16HardwareSignID;
    uint32_t            u32FileMap_ver;
    uint32_t            u32Upgrade_SnNum;    
    uint32_t            u32UpgradeCodeChecksum;
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    /**
     * @brief  
     * @param
     * @retval None
     */
    static void UpgradeModbus_SetStateAfterReset(void);
    /**
     * @brief  
     * @param
     * @retval None
     */
    static void UpgradeModbus_GetRegisterValue(uint16_t regAddr,uint16_t* pDataBuff);
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint8_t UpgradeModbus_SetRegisterValue(uint8_t *pu8Buff);
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint32_t UpgradeModbus_MakeOneCheckText(uint32_t u32Data,uint32_t u32Count);
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint8_t UpgradeModbus_AppChecksumIsOK(uint32_t checksum,uint32_t codesize);
    //--------------------------------------------------------------------------------
    //生成校验和
    //入口:8bits的数据指针，数据长度
    //出口:32bit的校验和
    //--------------------------------------------------------------------------------
    static uint32_t UpgradeModbus_MakeCheckSumText(uint8_t* pData,uint32_t Length);
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //#define KEYVAL  0x89,0x8E,0x3C,0x72,0xA7,0x19,0xF4,0x5D
    //-------------------------------------------------------------------------------------------------
    //名称: 文件解码
    //功能: 传入密文，传出明文
    //入口: 
    //        _Mix_binf   文件入口指针                    <<---->>
    //        _In_Length  文件长度,必须是128的倍数        <<----
    //出口: 
    //-------------------------------------------------------------------------------------------------
    static void UpgradeModbus_AppCodeDecrypt(uint8_t* _Mix_binf,uint8_t _In_Length);
    //--------------------------------------------------------------------------------------------------
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint8_t UpgradeModbus_GetAppInformationStatus(uint32_t *pu32Buff);
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint8_t UpgradeModbus_WriteHWAppInfomationForBootloader(uint8_t u8PhyAddress,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity,uint8_t u8PortType);    
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint8_t UpgradeModbus_WriteAppInfomation(uint8_t *pu8Buff);
    /**
     * @brief  
     * @param
     * @retval None
     */
    static void UpgradeModbus_WriteAppAreaOneBlock(uint16_t in_block_num,uint8_t* in_pBuff);
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint16_t UpgradeModbus_WriteOneBlockCode(uint16_t in_block_num,uint8_t* in_pBuff);
    /*******************************************************************************************************************/
    
    /**
     * @brief  
     * @param
     * @retval None
     */
    static void UpgradeModbus_SetStateAfterReset(void)
    {
        eUpdateState               = eUPDATE_STATE_START;
        u16UpgradeMessageCurrentID = 0;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    static void UpgradeModbus_GetRegisterValue(uint16_t regAddr,uint16_t* pDataBuff)
    {
        //static uint16_t u16BlockNumID;
        switch(regAddr)
        {
            case REG_SLAVE_STATUS_WORD:
            {
                //从机状态字
                if (eUpdateState == eUPDATE_STATE_SUCCESS )
                {
                    *pDataBuff = 2;
                }
                else //if ( ( eUPDATE_STATE_FILE_MAP == eUpdateState )||( eUPDATE_STATE_CODE == eUpdateState ) )
                {
                    *pDataBuff = 1;
                }
                break;
            }
            case REG_REQUEST_SERIAL:
            {    
                //从机报文当前需求序号          
                *pDataBuff   = u16UpgradeMessageCurrentID;
                break;
            } 
            default:
            {
                break;
            }
        }  
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint8_t UpgradeModbus_SetRegisterValue(uint8_t *pu8Buff)
    {
        uint16_t i;
        uint16_t u16RegID;

        uint16_t u16WriteRegAddress;
        uint16_t u16WriteNRegs;
        uint16_t u16WriteRegValue;
        uint8_t *pu8Data;
        uint8_t  u8Status;
        
        u8Status           = ~OK;
        pu8Data            = pu8Buff;
        u16WriteRegAddress = (uint16_t)pu8Data[6]<<8 | (uint16_t)pu8Data[7];
        u16WriteNRegs      = (uint16_t)pu8Data[8]<<8 | (uint16_t)pu8Data[9];

        for (i = 0; i < u16WriteNRegs; i++)
        {
            u16RegID         = u16WriteRegAddress + i;
            /* */        
            if ( REG_MESSAGE_FIRST_TWO_BYTE == u16RegID )
            {               
                if ( eUPDATE_STATE_FILE_MAP == eUpdateState )
                {
                    u8Status = UpgradeModbus_WriteAppInfomation(&pu8Data[13]);                                
                }
                else if ( ( eUPDATE_STATE_CODE == eUpdateState )||(eUPDATE_STATE_SUCCESS == eUpdateState ) )
                {
                    u8Status = UpgradeModbus_WriteOneBlockCode(u16UpgradeMessageCurrentID-1,&pu8Data[13]);  //压入报文数据                
                }
                //else if ( eUPDATE_STATE_SUCCESS != eUpdateState )//升级中
                if ( OK == u8Status )
                {
                    if (u16UpgradeMessageCurrentID >= u16UpgradeMessageTotalNum)
                    {
                        eUpdateState = eUPDATE_STATE_SUCCESS;//升级中
                        u16UpgradeMessageCurrentID = u16UpgradeMessageTotalNum;
                    }
                    else
                    {
                        u16UpgradeMessageCurrentID++;
                    }
                    
                }
                else
                {
                    eUpdateState = eUPDATE_STATE_SN_ERROR;
                }
                break;
            }
            else
            {
                u16WriteRegValue = (uint16_t)pu8Data[11 + i*2]<<8 | (uint16_t)pu8Data[12 + i*2] ;
                switch(u16RegID)
                {
                    case REG_UPDATA_STAR_WORD:
                    {//升级启动字 
                        if((STAR_UPDATA_WORD == u16WriteRegValue) || (RESTAR_UPDATA_WORD == u16WriteRegValue))
                        {                                
                            eUpdateState = eUPDATE_STATE_START;//升级中
                        }
                        break;
                    }
                    case REG_UPDATA_VERSION:
                    { //升级方法版本
                        break;
                    }
                    case REG_TOTAL_MESAAGE_NUM:
                    {  //报文总序号   
                        u16UpgradeMessageTotalNum = u16WriteRegValue;
                        break;
                    }
                    case REG_CHECKSUM_HIGH:
                    {
                        break;
                    }
                    case REG_CHECKSUM_LOW:
                    {                           
                        if ( eUpdateState == eUPDATE_STATE_START )//升级中
                        {
                            u16UpgradeMessageCurrentID = 0;
                            u8Status = OK;
                        }
                        
                        break;
                    }
                    case REG_UPDATA_CURRENT_SERIAL:
                    {                    
                        /* 获取当前序号 */
                        u16UpgradeMessageCurrentID = u16WriteRegValue ;
                        //从机报文当前需求序号          
                        if ( eUPDATE_STATE_START    == eUpdateState )
                        {
                            eUpdateState = eUPDATE_STATE_FILE_MAP;
                            u16UpgradeMessageCurrentID = 0;
                        }
                        else if ( eUPDATE_STATE_FILE_MAP == eUpdateState )//升级中
                        {
                            eUpdateState = eUPDATE_STATE_CODE;
                                                                
                        }
                        else if ( eUPDATE_STATE_CODE == eUpdateState )//升级中
                        {
                            
                        }
                        
                        
                        break;
                    }
                    default:
                    {
                        break;
                    }
                
                }
            }
        }

        return u8Status;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint32_t UpgradeModbus_MakeOneCheckText(uint32_t u32Data,uint32_t u32Count)
    {
        if( u32Count&0x00000001 )
        {
            u32Data = u32Data^CHECK_SUM_WORD_ODD;
        }
        else
        {
            u32Data = u32Data^CHECK_SUM_WORD_EVEN;
        }

        return(u32Data);
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint8_t UpgradeModbus_AppChecksumIsOK(uint32_t checksum,uint32_t codesize)
    {
        uint32_t offset_addr = 0;
        uint8_t  rd_buff[4];
        uint32_t make_checksum = 0;
        uint32_t rd_data;
        uint32_t count = 0;
        
        codesize = codesize/4;  //折算成32bits的大小
        while(codesize)
        {
            UpgradeModbus_ReadAppArea4Bytes(offset_addr,&rd_buff[0]);                        
            rd_data = pbc_arrayToInt32u_bigEndian(&rd_buff[0]);       
            make_checksum += UpgradeModbus_MakeOneCheckText(rd_data,count);
            offset_addr += 4;
            codesize --;
            count++;              
        }
        
        if(checksum == make_checksum)
        {
            return OK;
        }
        return !OK;
    }
    //--------------------------------------------------------------------------------
    //生成校验和
    //入口:8bits的数据指针，数据长度
    //出口:32bit的校验和
    //--------------------------------------------------------------------------------
    static uint32_t UpgradeModbus_MakeCheckSumText(uint8_t* pData,uint32_t Length)
    {
        uint32_t iWords,This_ids;
        uint32_t Index;
        uint32_t MakeSum,ReadData;

        iWords = (Length)/4;
        This_ids = 0;
        MakeSum = 0;
        Index = 0;
        while(iWords)
        {
            ReadData = (uint32_t)pData[Index]&0x000000FF;
            ReadData = ReadData<<8;
            ReadData = ReadData|((uint32_t)pData[Index+1]&0x000000FF);
            ReadData = ReadData<<8;
            ReadData = ReadData|((uint32_t)pData[Index+2]&0x000000FF);
            ReadData = ReadData<<8;
            ReadData = ReadData|((uint32_t)pData[Index+3]&0x000000FF);
            MakeSum += UpgradeModbus_MakeOneCheckText(ReadData,This_ids);
            Index = Index+4;
            iWords--;
            This_ids++;
        }
        return(MakeSum);
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //#define KEYVAL  0x89,0x8E,0x3C,0x72,0xA7,0x19,0xF4,0x5D
    //-------------------------------------------------------------------------------------------------
    //名称: 文件解码
    //功能: 传入密文，传出明文
    //入口: 
    //        _Mix_binf   文件入口指针                    <<---->>
    //        _In_Length  文件长度,必须是128的倍数        <<----
    //出口: 
    //-------------------------------------------------------------------------------------------------
    static void UpgradeModbus_AppCodeDecrypt(uint8_t* _Mix_binf,uint8_t _In_Length)
    {
        uint8_t Key[8]={(uint8_t)0x89,(uint8_t)0x8E,(uint8_t)0x3C,(uint8_t)0x72,(uint8_t)0xA7,(uint8_t)0x19,(uint8_t)0xF4,(uint8_t)0x5D,};
        uint8_t i;
        uint8_t Length,BaseIndex;

        if(_In_Length < 128)
        {
            return;
        }
        
        Length = _In_Length;
        BaseIndex = 0;
        while(0!=Length)
        {
            Key[0] = (uint8_t)0x89;
            Key[1] = (uint8_t)0x8E;
            Key[2] = (uint8_t)0x3C;
            Key[3] = (uint8_t)0x72;
            Key[4] = (uint8_t)0xA7;
            Key[5] = (uint8_t)0x19;
            Key[6] = (uint8_t)0xF4;
            Key[7] = (uint8_t)0x5D;

            for(i=0 ;i<16 ;i++)
            {
                _Mix_binf[0+i*8+BaseIndex] = _Mix_binf[0+i*8+BaseIndex] ^ Key[0];
                _Mix_binf[1+i*8+BaseIndex] = _Mix_binf[1+i*8+BaseIndex] ^ Key[1];
                _Mix_binf[2+i*8+BaseIndex] = _Mix_binf[2+i*8+BaseIndex] ^ Key[2];
                _Mix_binf[3+i*8+BaseIndex] = _Mix_binf[3+i*8+BaseIndex] ^ Key[3];
                _Mix_binf[4+i*8+BaseIndex] = _Mix_binf[4+i*8+BaseIndex] ^ Key[4];
                _Mix_binf[5+i*8+BaseIndex] = _Mix_binf[5+i*8+BaseIndex] ^ Key[5];
                _Mix_binf[6+i*8+BaseIndex] = _Mix_binf[6+i*8+BaseIndex] ^ Key[6];
                _Mix_binf[7+i*8+BaseIndex] = _Mix_binf[7+i*8+BaseIndex] ^ Key[7];

                char lastkeybit;
                if(Key[0] & 0x80)
                {
                    lastkeybit = 0x01;
                }
                else
                {
                    lastkeybit = 0x00;
                }
                unsigned char ics;
                for(ics=0;ics<7;ics++)
                {
                    Key[ics] = Key[ics]<<1;
                    if(Key[ics+1] & 0x80)
                    {
                        Key[ics] |= 0x01;
                    }
                }
                Key[ics] = Key[ics]<<1;
                Key[ics] |= lastkeybit;
            }
            if(Length < 128)
            {
                break;
            }
            Length = Length-128;
            BaseIndex += 128;
        }
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint8_t UpgradeModbus_GetAppInformationStatus(uint32_t *pu32Buff)
    {
        uint8_t i;
        uint8_t u8ParErrCount;

        u8ParErrCount = 0;
        
        for (i = 0; i < APP_INFO_OFFSET; i++)
        {
            if ( pu32Buff[i] != ~pu32Buff[i+APP_INFO_OFFSET] )
            {
                u8ParErrCount++;
            }
        }
        return u8ParErrCount;
    }    
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint8_t UpgradeModbus_WriteHWAppInfomationForBootloader(uint8_t u8PhyAddress,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity,uint8_t u8PortType)
    {
        uint32_t i;
        uint32_t u32AppInfo[APP_INFO_WORDS_LENGTH];

        UpgradeModbus_ReadNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_WORDS_LENGTH);
  
        
        u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]                     = (u8Parity<<24)|(u8Stops<<16)|(u8BaudRateID<<8)|(u8PhyAddress);         
        u32AppInfo[APP_INFO_UPDATE_STATUS]                               = APP_NEED_UPGRADE_COMPLETE;                
        u32AppInfo[APP_INFO_HW_SIGN ]                                    = APP_HARDWARE_SIGN;                
        u32AppInfo[APP_INFO_HW_UPGRADE_PORT ]                            = u8PortType;
        
        for (i = 0; i < APP_INFO_OFFSET; i++)
        {
            if ( u32AppInfo[i] != ~u32AppInfo[i+APP_INFO_OFFSET] )
            {
                u32AppInfo[i+APP_INFO_OFFSET] = ~u32AppInfo[i];
            }
        }        
        UpgradeModbus_WriteNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_HW_PAGE_OFFSET,APP_INFO_WORDS_LENGTH);

        return 0;
    }
    
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint8_t UpgradeModbus_WriteAppInfomation(uint8_t *pu8Buff)
    {
        uint32_t  u32AppInfo[APP_INFO_WORDS_LENGTH];
        uint8_t   buff_block[APP_MODBUS_MESSAGE_BYTE_NUMS];
        uint8_t   i;
        uint16_t  hardwareSign;//硬件标识
        uint32_t  checkSum;

        for(i = 0; i < APP_MODBUS_MESSAGE_BYTE_NUMS; i++)
        {
            buff_block[i] = pu8Buff[i];
        }

        hardwareSign = pbc_arrayToInt16u_bigEndian(&buff_block[32]);
        checkSum     = pbc_arrayToInt32u_bigEndian(&buff_block[124]);

        
        if(checkSum != UpgradeModbus_MakeCheckSumText(&buff_block[0],124)) //信息块(32bytes)
        {
            return ~OK;
        }

        if (  (u16HardwareSignID == 0xFFFF)
            ||(u16HardwareSignID == 0xAA55)
            ||(u16HardwareSignID == 0x55AA)
            ||(u16HardwareSignID == 0x0000) )
        {
            
        }    
        else
        {
            if (hardwareSign != u16HardwareSignID )
            {        
                return ~OK;
            }
        }

        u32Upgrade_SnNum          = pbc_arrayToInt32u_bigEndian(&buff_block[16]); //序号,app区
        u32Upgrade_SnNum          = u32Upgrade_SnNum + 1;
        u32FileMap_ver            = pbc_arrayToInt32u_bigEndian(&buff_block[120]);//version
        u32UpgradeCodeChecksum    = pbc_arrayToInt32u_bigEndian(&buff_block[108]);//校验文
        u32UpgradeCodeByteSize    = pbc_arrayToInt32u_bigEndian(&buff_block[112]);//代码字节数
        u16UpgradeMessageTotalNum = u32UpgradeCodeByteSize/128 ;//+ 1; 

        if ( 0x00000001 == u32FileMap_ver )
        {
            UpgradeModbus_ReadNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_WORDS_LENGTH);
            u32AppInfo[APP_INFO_UPGRADE_COUNT]                               = u32Upgrade_SnNum;
            u32AppInfo[APP_INFO_UPGRADE_STATUS]                              = APP_NEED_UPGRADE_UPDATING;
            u32AppInfo[APP_INFO_UPGRADE_CHECK_SUM]                           = u32UpgradeCodeChecksum;
            u32AppInfo[APP_INFO_UPGRADE_CODE_SIZE]                           = u32UpgradeCodeByteSize;
            u32AppInfo[APP_INFO_UPGRADE_FILE_MAP_VERSION]                    = u32FileMap_ver;
        
            for (i = 0; i < APP_INFO_OFFSET; i++)
            {
                if ( u32AppInfo[i] != ~u32AppInfo[i+APP_INFO_OFFSET] )
                {
                    u32AppInfo[i+APP_INFO_OFFSET] = ~u32AppInfo[i];
                }
            }   
        
            u16FirewareBlockID = 0;
            UpgradeModbus_WriteNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_HW_PAGE_OFFSET,APP_INFO_WORDS_LENGTH);

            return OK;
        }
        return ~OK;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    static void UpgradeModbus_WriteAppAreaOneBlock(uint16_t in_block_num,uint8_t* in_pBuff)
    {
        uint32_t u32DataAddress;

        u32DataAddress = (APP_ADDRESS_START + in_block_num * 128);

        if (APP_ADDRESS_END < u32DataAddress) 
        {
            return;
        }   
        
        uint8_t  i = 0;
            
        for(i = 0; i < APP_BLOCK_LENGTH; i++)
        {
            uint32_t dat  =  0;
            dat |= in_pBuff[i * 4 + 3];
            dat <<= 8;
            dat |= in_pBuff[i * 4 + 2];
            dat <<= 8;
            dat |= in_pBuff[i * 4 + 1];
            dat <<= 8;
            dat |= in_pBuff[i * 4 + 0];
            u32PageBuff[i] = dat;     
        }

        NVM_FLASH_WriteNWords(u32DataAddress,u32PageBuff,APP_BLOCK_LENGTH);
    }
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint16_t UpgradeModbus_WriteOneBlockCode(uint16_t in_block_num,uint8_t* in_pBuff)
    {
        uint8_t buff_block[APP_MODBUS_MESSAGE_BYTE_NUMS];
        uint8_t i;
        
        if ( u16FirewareBlockID != in_block_num )
        {
            return ~OK;
        }

        for(i = 0; i < sizeof(buff_block)/sizeof(uint8_t); i++)
        {
            buff_block[i] = in_pBuff[i];
        }
            
        UpgradeModbus_AppCodeDecrypt(&buff_block[0],APP_MODBUS_MESSAGE_BYTE_NUMS);
        UpgradeModbus_WriteAppAreaOneBlock(u16FirewareBlockID, &buff_block[0]);//写入一个块的数据到upgrade区

        u16FirewareBlockID++;
        if(u16FirewareBlockID >= (u32UpgradeCodeByteSize / APP_MODBUS_MESSAGE_BYTE_NUMS))
        {
            u16FirewareBlockID = 0;
            
            eBootState = eBOOT_RUN_STATE_CHECK_APP_LEGAL;//eBOOT_RUN_STATE_WRITE_APP_INFO;        
        }
        
        return OK;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    void UpgradeModbus_GetDefaultHardwareInfo(uint8_t *pu8PhyAdd, uint8_t *pu8BaudID, uint8_t *pu8Stops, uint8_t *pu8Parity,uint8_t *u8PortType,uint32_t *pu32DstID)
    {
        uint8_t  i;
        uint8_t  u8Data;
        uint32_t u32AppInfo[APP_INFO_WORDS_LENGTH];
        uint8_t  u8WriteBack;
        /* read hard infomation from the HW's first address */

        u8WriteBack = 0;
        UpgradeModbus_ReadNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_WORDS_LENGTH);
        /* Check the modbus's phyaddress ,baudid ,stops parity *///
        if ( u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY] == ~u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY + APP_INFO_OFFSET] )
        {
            u8Data = u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]&0xFF;
            if ( ( u8Data > 128 )||( u8Data < 1 ) )
            {
                *pu8PhyAdd   = 32;
                u8WriteBack |= 0x01;
            }
            else
            {
                *pu8PhyAdd = u8Data;                
            }
            u8Data = (u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]>>8)&0xFF;
            if ( ( u8Data > 0x07 )||( u8Data < 0x02 ) )
            {
                *pu8BaudID   = 3;
                u8WriteBack |= 0x02;
            }
            else
            {
                *pu8BaudID = u8Data;
            }
            u8Data = (u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]>>16)&0xFF;
            if ( u8Data  > 0x01 )
            {
                *pu8Stops    = 0;
                u8WriteBack |= 0x04;
            }
            else
            {
                *pu8Stops = u8Data;
            }
            
            u8Data = (u32AppInfo[APP_INFO_HW_PARITY]>>24)&0xFF;
            if ( u8Data > 0x02 )
            {
                *pu8Parity = 0x00;
                u8WriteBack |= 0x08;
            }
            else
            {
                *pu8Parity = u8Data;
            }
            
        }
        else
        {
            *pu8PhyAdd = 32;
            *pu8BaudID = 3;
            *pu8Stops  = 0;
            *pu8Parity = 0x00;
            u8WriteBack |= 0x0F;
            u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY] = (*pu8Parity<<24)|(*pu8Stops<<16)|(*pu8BaudID<<8)|(*pu8PhyAdd);
        }
        if ( u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM] == ~u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM + APP_INFO_OFFSET] )
        {
            u16UpgradeMessageTotalNum = u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM];
        }


        if ( u32AppInfo[APP_INFO_HW_UPGRADE_PORT] == ~u32AppInfo[APP_INFO_HW_UPGRADE_PORT + APP_INFO_OFFSET] )
        {
            u8Data = u32AppInfo[APP_INFO_HW_UPGRADE_PORT];

            if ( u8Data < 2 )
            {
                *u8PortType = u8Data;
            }        
        }

        if ( u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID] == ~u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID + APP_INFO_OFFSET] )
        {
            *pu32DstID = u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID];
        }

        if ( u32AppInfo[APP_INFO_UPGRADE_CHECK_SUM] != ~u32AppInfo[APP_INFO_UPGRADE_CHECK_SUM + APP_INFO_OFFSET] )
        {
            u8WriteBack |= 0x10;
        }

        if ( u32AppInfo[APP_INFO_UPGRADE_CODE_SIZE] != ~u32AppInfo[APP_INFO_UPGRADE_CODE_SIZE + APP_INFO_OFFSET] )
        {
            u8WriteBack |= 0x20;
        }

        if ( u8WriteBack )
        {                        
            for (i = 0; i < APP_INFO_OFFSET; i++)
            {
                if ( u32AppInfo[i] != ~u32AppInfo[i+APP_INFO_OFFSET] )
                {
                    u32AppInfo[i+APP_INFO_OFFSET] = ~u32AppInfo[i];
                }
            } 
            UpgradeModbus_WriteNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_HW_PAGE_OFFSET,APP_INFO_WORDS_LENGTH);
        }
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbusResetReply(uint8_t *p8SendBuff,uint8_t u8PhyAdd,uint16_t *pu16Length)
    {
        uint16_t u16CRC;

        p8SendBuff[0] = u8PhyAdd;
        p8SendBuff[1] = MB_FUNC_READWRITE_MULTIPLE_REGISTERS;
        p8SendBuff[2] = 4;
        p8SendBuff[3] = 0x00;
        p8SendBuff[4] = 0x01;
        p8SendBuff[5] = 0x00;
        p8SendBuff[6] = 0x00;
        
        u16CRC = CRC16Get( p8SendBuff, 7 );
        p8SendBuff[7] = u16CRC&0xFF;
        p8SendBuff[8] = u16CRC>>8;
        *pu16Length   = 9;
        return OK;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbusReceiveReply(uint8_t *p8ReceiveBuff,uint8_t *p8SendBuff,uint16_t *pu16Length)
    {
        uint8_t  u8Cmd;
        uint16_t u16RegAddress;
        uint16_t u16NRegs;
        uint16_t u16CRC;

        uint16_t u16Nums;


        uint16_t u16RegValue;
        
        u8Cmd = p8ReceiveBuff[1];
        if ( *pu16Length < 12 )
        {
            return ~OK;
        }
        if (MB_FUNC_READWRITE_MULTIPLE_REGISTERS != u8Cmd )
        {
            return ~OK;
        }

        if ( OK == UpgradeModbus_SetRegisterValue(p8ReceiveBuff) )
        {
            u16RegAddress  = (uint16_t)p8ReceiveBuff[2]<<8 | (uint16_t)p8ReceiveBuff[3];
            u16NRegs       = (uint16_t)p8ReceiveBuff[4]<<8 | (uint16_t)p8ReceiveBuff[5];
            p8SendBuff[0] = p8ReceiveBuff[0];
            p8SendBuff[1] = p8ReceiveBuff[1];
            p8SendBuff[2] = u16NRegs*2;
            
            for (u16Nums = 0; u16Nums < u16NRegs; u16Nums++)
            {                        
                UpgradeModbus_GetRegisterValue(u16RegAddress+u16Nums,&u16RegValue);
                p8SendBuff[3+u16Nums*2] = u16RegValue>>8;
                p8SendBuff[4+u16Nums*2] = u16RegValue&0xFF;
            }
            u16Nums       = p8SendBuff[2] + 3;

            u16CRC = CRC16Get( p8SendBuff, u16Nums );
            p8SendBuff[u16Nums] = u16CRC&0xFF;
            p8SendBuff[u16Nums+1] = u16CRC>>8;

            *pu16Length = p8SendBuff[2] + 5;

            return OK;
        }

        return ~OK;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbus_GetStatus (uint32_t *pu32UpgradeStatus)
    {
        //uint8_t  i;
        //uint8_t  j;
        uint32_t u32AppInfo[APP_INFO_WORDS_LENGTH];

        UpgradeModbus_ReadNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_WORDS_LENGTH);
    #if 0
        j = 0;
        for (i = 0; i < 64; i++)
        {
            if (u32AppInfo[i] == 0xFFFFFFFF)
            {
                j++;
            }
        }
        /* Infomation not init,because the area is bank */
        if (j == 64)
        {
            return OK;
        }
    #endif
        if ( u32AppInfo[APP_INFO_UPDATE_STATUS] == ~u32AppInfo[APP_INFO_UPDATE_STATUS + APP_INFO_OFFSET] )
        {
            *pu32UpgradeStatus = u32AppInfo[APP_INFO_UPDATE_STATUS];
        }
        if ( u32AppInfo[APP_INFO_HW_SIGN] == ~u32AppInfo[APP_INFO_HW_SIGN + APP_INFO_OFFSET] )
        {
            u16HardwareSignID = u32AppInfo[APP_INFO_HW_SIGN];
        }
        
        if ( 0 == UpgradeModbus_GetAppInformationStatus(u32AppInfo) )
        {        
            if ( APP_NEED_UPGRADE_COMPLETE == u32AppInfo[APP_INFO_UPDATE_STATUS] )
            {
                if (OK == UpgradeModbus_AppChecksumIsOK(u32AppInfo[APP_INFO_UPGRADE_CHECK_SUM],u32AppInfo[APP_INFO_UPGRADE_CODE_SIZE]))
                {                
                    return OK;
                }
            }
            else if ( APP_NEED_UPGRADE_UPDATING == u32AppInfo[APP_INFO_UPDATE_STATUS] )
            {
                UpgradeModbus_SetStateAfterReset();
            }
        }
                
        return !OK;
    }
    /**
     * @brief  
     * @param
     * @retval None
     */
    uint8_t UpgradeModbus_WriteAppInfomationAndReset(uint8_t u8PhyAddress,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity,uint8_t u8PortType)
    {
        if ( eBOOT_RUN_STATE_CHECK_APP_LEGAL == eBootState )
        {
            UpgradeModbus_WriteHWAppInfomationForBootloader(u8PhyAddress, u8BaudRateID, u8Stops, u8Parity,u8PortType);
            NVIC_SystemReset();
            
        }
        return !OK;
    }
    /**
     * @brief  程序跳转到应用区
     * @param
     * @retval None
     */
    void UpgradeModbus_BootJumpToApp(void)
    {
        uint32_t JumpAddress;
        JumpAddress = 0;
        

        while (((*(__IO uint32_t*) (APP_ADDRESS_START) ) & 0x2FF20000 ) != 0x20000000)
        {
            ;
        }
        __ASM("CPSID  I");
        __disable_irq(); // 关闭总中断
        
        BSP_DeInitAll();
        
        /* 跳转到应用程序位置 */
        JumpAddress = *(__IO uint32_t*) (APP_ADDRESS_START + 4);
        __set_PSP(*(__IO uint32_t*) (APP_ADDRESS_START));
        __set_MSP(*(__IO uint32_t*) (APP_ADDRESS_START));
        (*( void (*)( ) )JumpAddress) ();
    }
    
#endif    





#if UPGRADE_MODBUS_APP > 0
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    uint8_t             u8BootUpgradeState;
    //uint16_t            u16UpdateTotalNums;
    uint16_t            u16UpdateReceiveCnt;
    uint16_t            u16UpgradeMessageTotalNum; 
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
    /*******************************************************************************************************************/
#if UPGRADE_MODBUS_FORWARD_ENABLE      >     (0)    
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_MasterForwardReceiveSlaveData(uint8_t *pu8InBuff,Serial_Typedef *pSerial,uint16_t u16BuffNums);
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_SlaveForwardMasterReceiveData(uint8_t *pu8InBuff,Serial_Typedef *pSerial,uint16_t u16BuffNums);
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_GetForwardStatus(void);
    /**
     * @brief
     * @param
     * @retval
     */
    static void UpgradeModbus_Clear(void);
    /* If the packet to the slave's foward */
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_SlaveForwardMasterReceiveStatus(uint16_t u16ForwardNums);
#endif    
    /**
     * @brief
     * @param
     * @retval
     */
    static void UpgradeModbus_ResetMCU(void);
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint8_t UpgradeModbus_WriteHWAppInfomationForBootloader(uint8_t *pu8Buff,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity,uint8_t u8PortType,uint32_t u32DstID);

    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint32_t UpgradeModbus_JumpBoot(uint8_t *pu8Buff,uint8_t u8PhyAddress);
    
    /*******************************************************************************************************************/
#if UPGRADE_MODBUS_FORWARD_ENABLE      >     (0)        
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_MasterForwardReceiveSlaveData(uint8_t *pu8InBuff,Serial_Typedef *pSerial,uint16_t u16BuffNums)
    {
        uint8_t  i;
        uint16_t u16CRC;

        if ( pu8InBuff[0] > 64 )
        {
            for (i = 1; i < u16BuffNums; i++)
            {
                pSerial->pu8Send[i]      = pu8InBuff[i];
            }

            
            pSerial->pu8Send[0]      = pu8InBuff[0]-64;

            pSerial->u16SendBytesMax = u16BuffNums;
            u16CRC        = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax );
            
            pSerial->pu8Send[pSerial->u16SendBytesMax] = u16CRC&0xFF;
            pSerial->pu8Send[pSerial->u16SendBytesMax+1] = u16CRC>>8;
            pSerial->u16SendBytesMax += 2;
            USART_StateSetSend(pSerial,pSerial->u16SendBytesMax,0,500);
        }
        
        return OK;
    }
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_SlaveForwardMasterReceiveData(uint8_t *pu8InBuff,Serial_Typedef *pSerial,uint16_t u16BuffNums)
    {
        uint8_t  i;
        uint16_t u16CRC;
        
        if ( MB_FUNC_READWRITE_MULTIPLE_REGISTERS != pu8InBuff[1] )
        {
            return ~OK;
        }
        
        if ( u16UpgradeMessageTotalNum > 0 )
        {
            if ( u16UpdateReceiveCnt >= u16UpgradeMessageTotalNum )
            {
                u16UpdateReceiveCnt = 0;
                u16UpgradeMessageTotalNum  = 0;
                u8BootUpgradeState       = 0;
            }
        }        

        for (i = 1; i < u16BuffNums; i++)
        {
            pSerial->pu8Send[i]      = pu8InBuff[i];
        }

        
        pSerial->pu8Send[0]      = pu8InBuff[0] + 64;
        pSerial->u16SendBytesMax = u16BuffNums;
        u16CRC        = CRC16Get( pSerial->pu8Send, pSerial->u16SendBytesMax );
        pSerial->pu8Send[pSerial->u16SendBytesMax] = u16CRC&0xFF;
        pSerial->pu8Send[pSerial->u16SendBytesMax+1] = u16CRC>>8;
        pSerial->u16SendBytesMax += 2;
        USART_StateSetSend(pSerial,pSerial->u16SendBytesMax,0,500);

        return OK;
    }
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_GetForwardStatus(void)
    {
        if ( 2 == u8BootUpgradeState )
        {        
            return OK;
        }
        return ~OK;
    }
    /**
     * @brief
     * @param
     * @retval
     */
    static void UpgradeModbus_Clear(void)
    {
        u8BootUpgradeState       = 0;
    }
    /* If the packet to the slave's foward */
    /**
     * @brief
     * @param
     * @retval
     */
    static uint8_t UpgradeModbus_SlaveForwardMasterReceiveStatus(uint16_t u16ForwardNums)
    {
        if ( 2 == u8BootUpgradeState )
        {
            //UpgradeModbus_SlaveForwardMasterReceiveData(ModbuMaster.Frame.pu8Receive,&ModbuSlave.Frame,u16ForwardNums);
            return OK;
        }
        return ~OK;
    }
#endif    
    /**
     * @brief
     * @param
     * @retval
     */
    static void UpgradeModbus_ResetMCU(void)
    {
        if ( u8BootUpgradeState == 1 )
        { 
            u8BootUpgradeState = 0;
            
            NVIC_SystemReset();
        }
    }
    /**
     * @brief  
     * @param        
     * @retval None
     */
    static uint8_t UpgradeModbus_WriteHWAppInfomationForBootloader(uint8_t *pu8Buff,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity,uint8_t u8PortType,uint32_t u32DstID)
    {
        uint16_t  i;
        uint32_t u32AppInfo[APP_INFO_WORDS_LENGTH];
        uint32_t u32UpdateVersion;
        uint32_t u32TotalMessageNum;
        uint32_t u32CheckSum;
        uint8_t  u8PhyAddress;

        
        
        u8PhyAddress       = pu8Buff[0];
        u32UpdateVersion   = (uint32_t)pu8Buff[13]<<8 | (uint32_t)pu8Buff[14];
        u32TotalMessageNum = (uint32_t)pu8Buff[15]<<8 | (uint32_t)pu8Buff[16];
        u32CheckSum        = (uint32_t)pu8Buff[21]<<24 | (uint32_t)pu8Buff[22]<<16 | (uint32_t)pu8Buff[23]<<8 | (uint32_t)pu8Buff[24];

        UpgradeModbus_ReadNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_WORDS_LENGTH);

        for (i = 0; i < APP_INFO_OFFSET; i++)
        {
            if ( u32AppInfo[i+APP_INFO_OFFSET] != ~u32AppInfo[i] )
            {
                u32AppInfo[i] = 0xAA5555AA;
                u32AppInfo[i+APP_INFO_OFFSET] = ~u32AppInfo[i];
            }            
        }
        

        u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]                     = (u8Parity<<24)|(u8Stops<<16)|(u8BaudRateID<<8)|(u8PhyAddress);
        u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY + APP_INFO_OFFSET]   = ~u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY];

        u32AppInfo[APP_INFO_HW_UPDATE_VERSION]                           = u32UpdateVersion;
        u32AppInfo[APP_INFO_HW_UPDATE_VERSION + APP_INFO_OFFSET]         = ~u32AppInfo[APP_INFO_HW_UPDATE_VERSION];
 
        u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM]                           = u32TotalMessageNum;
        u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM + APP_INFO_OFFSET]         = ~u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM];

        u32AppInfo[APP_INFO_CHECK_SUM]                                   = u32CheckSum;
        u32AppInfo[APP_INFO_CHECK_SUM + APP_INFO_OFFSET]                 = ~u32AppInfo[APP_INFO_CHECK_SUM];

        u32AppInfo[APP_INFO_UPDATE_STATUS]                               = APP_NEED_UPGRADE_UPDATING;
        u32AppInfo[APP_INFO_UPDATE_STATUS + APP_INFO_OFFSET]             = ~u32AppInfo[APP_INFO_UPDATE_STATUS];

        u32AppInfo[APP_INFO_HW_SIGN ]                                    = APP_HARDWARE_SIGN;
        u32AppInfo[APP_INFO_HW_SIGN + APP_INFO_OFFSET]                   = ~u32AppInfo[APP_INFO_HW_SIGN ];

        u32AppInfo[APP_INFO_HW_UPGRADE_PORT ]                            = u8PortType;
        u32AppInfo[APP_INFO_HW_UPGRADE_PORT + APP_INFO_OFFSET]           = ~u32AppInfo[APP_INFO_HW_UPGRADE_PORT ];

        u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID ]                         = u32DstID;
        u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID + APP_INFO_OFFSET]        = ~u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID ];
                
        UpgradeModbus_WriteNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_HW_PAGE_OFFSET,APP_INFO_WORDS_LENGTH);

        return 0;
    }

    /**
     * @brief  
     * @param
     * @retval None
     */
    static uint32_t UpgradeModbus_JumpBoot(uint8_t *pu8Buff,uint8_t u8PhyAddress)
    {
        uint16_t i;
        uint16_t u16RegID;

        uint16_t u16WriteRegAddress;
        uint16_t u16WriteNRegs;
        uint16_t u16WriteRegValue;
        uint8_t *pu8Data;
        uint32_t u32UpdateCmd;
        uint8_t  u8Address;
        u8Address          = pu8Buff[0];
        pu8Data            = pu8Buff;
        u16WriteRegAddress = (uint16_t)pu8Data[6]<<8 | (uint16_t)pu8Data[7];
        u16WriteNRegs      = (uint16_t)pu8Data[8]<<8 | (uint16_t)pu8Data[9];        
        u32UpdateCmd       = 0x00000000;

        for (i = 0; i < u16WriteNRegs; i++)
        {
            u16RegID         = u16WriteRegAddress + i;
                    
            u16WriteRegValue = (uint16_t)pu8Data[11 + i*2]<<8 | (uint16_t)pu8Data[12 + i*2] ;

            
            switch(u16RegID)
            {
                case REG_UPDATA_STAR_WORD:
                { 
                    
                    if((STAR_UPDATA_WORD == u16WriteRegValue) || (RESTAR_UPDATA_WORD == u16WriteRegValue))
                    {                                                    
                        u32UpdateCmd = 0xAA55AA55;
                    }
                    /*
                    else if((FOWARD_STAR_UPDATA_WORD == u16WriteRegValue) || (FOWARD_RESTAR_UPDATA_WORD == u16WriteRegValue))
                    {                                                    
                        u32UpdateCmd = 0x55AA55AA;
                    }
                    */               
                    break;
                }
                case REG_UPDATA_VERSION:
                { //升级方法版本
                    //u32UpdateVersion = u16WriteRegValue;
                    break;
                }
                case REG_TOTAL_MESAAGE_NUM:
                {  //报文总序号   
                    //u32TotalMessageNum = u16WriteRegValue;
                    break;
                }
                case REG_CHECKSUM_HIGH:
                {
                    break;
                }
                case REG_CHECKSUM_LOW:
                { 
                    if ( u32UpdateCmd == 0xAA55AA55 )
                    {
                        if ( u8Address == u8PhyAddress )
                        {
                            return u32UpdateCmd;
                        }
                        else if ( u8Address == (u8PhyAddress+64) )
                        {
                            return 0x55AA55AA;
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
            
        }

        return 0;
    }
    
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
                                uint32_t u32DstID)
    {
        uint32_t u32UpgradeCmd;

        u32UpgradeCmd = UpgradeModbus_JumpBoot(pu8uff,u8PhyAdd);
                
        /* If the message packet for update the best FC */
        if ( 0xAA55AA55 == u32UpgradeCmd )
        {   
            u8BootUpgradeState = 1; 
            UpgradeModbus_WriteHWAppInfomationForBootloader(pu8uff,u8BaudID,u8Stops,u8Parity,u8PortType,u32DstID);
            UpgradeModbus_ResetMCU();
        }
        /* If the message packet to the RC panel's */
        else if ( 0x55AA55AA == u32UpgradeCmd )
        {
            u8BootUpgradeState  = 2;
            u16UpdateReceiveCnt = 0;
            u16UpgradeMessageTotalNum  = (uint16_t)pu8uff[15]<<8 | (uint16_t)pu8uff[16];
            //UpgradeModbus_MasterForwardReceiveSlaveData(pu8uff,&ModbuMaster.Frame,u16ForwardNums);
        }
        else if ( 2 == u8BootUpgradeState )
        {
            if ( ( u8PhyAdd+64) == pu8uff[0] )
            {
                u16UpdateReceiveCnt = (uint16_t)pu8uff[11]<<8 | (uint16_t)pu8uff[12];
                //UpgradeModbus_MasterForwardReceiveSlaveData(pu8uff,&ModbuMaster.Frame,u16ForwardNums);
            }
        }
    }
    
    /**
     * @brief  
     * @param        
     * @retval None
     */
    void UpgradeModbus_SelfCheckAppInfo(uint8_t u8PhyAdd,uint8_t u8BaudRateID,uint8_t u8Stops,uint8_t u8Parity)
    {
        uint8_t  i;
        uint8_t  u8Data;
        //uint32_t u8DataAddress;
        uint32_t u32AppInfo[APP_INFO_WORDS_LENGTH];
        uint8_t  u8WriteBack;
        /* read hard infomation from the HW's first address */

        u8WriteBack = 0;
        UpgradeModbus_ReadNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_WORDS_LENGTH);
        if ( u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY] == ~u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY + APP_INFO_OFFSET] )
        {
            u8Data = u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]&0xFF;
            if ( ( u8Data > 128 )||( u8Data < 1 ) )
            {
                u8WriteBack |= 0x01;
            }

            u8Data = (u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]>>8)&0xFF;
            if ( u8Data > 0x07 )
            {
                u8WriteBack |= 0x02;
            }

            u8Data = (u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]>>16)&0xFF;
            if ( u8Data  > 0x01 )
            {

                u8WriteBack |= 0x04;
            }

            
            u8Data = (u32AppInfo[APP_INFO_HW_PARITY]>>24)&0xFF;
            if ( u8Data > 0x02 )
            {

                u8WriteBack |= 0x08;
            }
        }
        else
        {

            u8WriteBack |= 0x01;
        }

        if ( u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM] == ~u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM + APP_INFO_OFFSET] )
        {
            u16UpgradeMessageTotalNum = u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM];
        }
        else    
        {
            u16UpgradeMessageTotalNum = 0;
            u8WriteBack |= 0x08;
        }

        if ( u32AppInfo[APP_INFO_HW_UPGRADE_PORT] == ~u32AppInfo[APP_INFO_HW_UPGRADE_PORT + APP_INFO_OFFSET] )
        {
            u8Data = u32AppInfo[APP_INFO_HW_UPGRADE_PORT];

            if ( u8Data > 1)
            {
                u8WriteBack |= 0x10;
            }        
        }
        else    
        {
            u8WriteBack |= 0x10;
        }

        if ( u8WriteBack )
        {
            for (i = 0; i < APP_INFO_OFFSET; i++)
            {
                if ( u32AppInfo[i+APP_INFO_OFFSET] != ~u32AppInfo[i] )
                {
                    u32AppInfo[i] = 0xAA5555AA;
                    u32AppInfo[i+APP_INFO_OFFSET] = ~u32AppInfo[i];
                }            
            }

            u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY]                      = (u8Parity<<24)|(u8Stops<<16)|(u8BaudRateID<<8)|(u8PhyAdd);
            u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY + APP_INFO_OFFSET]    = ~u32AppInfo[APP_INFO_HW_PHY_BAUD_STOP_PARITY];

            u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM + APP_INFO_OFFSET]          = u32AppInfo[APP_INFO_TOTAL_MESSAGE_NUM];
            u32AppInfo[APP_INFO_HW_UPGRADE_PORT + APP_INFO_OFFSET]            = ~u32AppInfo[APP_INFO_HW_UPGRADE_PORT];
            u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID + APP_INFO_OFFSET]         = ~u32AppInfo[APP_INFO_HW_ENOCEAN_CHIP_ID];
            
            UpgradeModbus_WriteNWordsInOnePage(APP_ADDRESS_INFO_START,u32AppInfo,APP_INFO_HW_PAGE_OFFSET,APP_INFO_WORDS_LENGTH);
        }
    }
    
#endif
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/

