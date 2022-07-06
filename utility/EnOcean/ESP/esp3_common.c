/*!
*****************************************************************
                        $Name$
                        $Revision: 27601 $
                        $Date: 2015-03-02 16:20:57 +0200 (Fr, 18 Jun 2010) $
    \file               Enocean_ESP.c
    \brief              MSG management related functions
    \author             zhoujinbang


    <b>Company:</b>\n   Menred GmbH\n
�޸ļ�¼
1��
2��
3��
4��
5��
6��
****************************************************************
*/
#include "esp3_common.h"

#if 0
//#pragma location = "IPECODE16_C"
/**
  * @brief
  * @param
  * @retval None
  */
const uint8_t u8CRC8Table[256] =
{
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15,//0x07
    0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,//0x0F
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
    0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,//0x1F
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5,
    0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85,
    0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
    0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2,
    0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32,
    0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
    0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c,
    0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec,
    0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
    0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c,
    0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b,
    0x76, 0x71, 0x78, 0x7f, 0x6A, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
    0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb,
    0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8D, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb,
    0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3,
};
/**
  * @brief  Get Buff CRC8
  * @param  *Buff Input the needs caulate
  *         BuffStart Can use buff Index
  *         DataLength
  * @retval Crc8 value
  */
uint8_t u8GetCrc8(uint8_t *Buff,uint8_t BuffStart,uint8_t DataLength)
{
    uint8_t i;

    uint8_t volatile u8Crc8;
    u8Crc8 = 0;
    for ( i = BuffStart; i < BuffStart+DataLength; i++)
    {
        u8Crc8 ^= Buff[i];
        u8Crc8  = u8CRC8Table[u8Crc8];
    }

    return u8Crc8;
}
#endif


Esp3Tx_Typedef          Esp3Tx;
Esp3Rx_Typedef          Esp3Rx;

/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CommonCommandWriteSleepTime(Esp3Tx_Typedef *pEsp3Tx, uint32_t u32SleepTime)
{
    pEsp3Tx->u16ByteMax = 7; //Header + CRC8D���ֽ��� --- 2018-3-6
    pEsp3Tx->u16ByteMax += 5;//Data�ֽ��� --- 2018-3-6
    pEsp3Tx->u16ByteMax += 0;//Optional Data�ֽ��� --- 2018-3-6

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 5;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_SLEEP;

    pEsp3Tx->u8Buff[7]  = u32SleepTime>>24;
    pEsp3Tx->u8Buff[8]  = u32SleepTime>>16;
    pEsp3Tx->u8Buff[9]  = u32SleepTime>>8;
    pEsp3Tx->u8Buff[10] = u32SleepTime&0xFF;
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CommonCommandWriteReset(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_RESET;


    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadVersion(Esp3Tx_Typedef *pEsp3Tx)
{

    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;
    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_VERSION;

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadVersionRespone(uint8_t *u8ReceiveBuff, EnoceanTCM310_Typedef *pEnoceanTCM310)
{
    memcpy(pEnoceanTCM310->HW.u8Info, &u8ReceiveBuff[7], 32);
    //uint8_t  u8ChipIDInfo[4];
    pEnoceanTCM310->HW.u8ChipIDInfo[0] = u8ReceiveBuff[18];
    pEnoceanTCM310->HW.u8ChipIDInfo[1] = u8ReceiveBuff[17];
    pEnoceanTCM310->HW.u8ChipIDInfo[2] = u8ReceiveBuff[16];
    pEnoceanTCM310->HW.u8ChipIDInfo[3] = u8ReceiveBuff[15];
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadSysLog(Esp3Tx_Typedef *pEsp3Tx)
{
    //pEnoceanBus->u8SendByteCnt = 0;
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;
    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_SYS_LOG;

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadSysLogRespone(uint8_t *u8ReceiveBuff)
{

}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteBist(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_BIST;


    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteBistRespone(Esp3Tx_Typedef *pEsp3Tx)
{

}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteBaseID(Esp3Tx_Typedef *pEsp3Tx, uint32_t u32BaseID)
{
    pEsp3Tx->u16ByteMax  = 7;
    pEsp3Tx->u16ByteMax += 5;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 5;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_IDBASE;

    pEsp3Tx->u8Buff[7] = u32BaseID >> 24;
    pEsp3Tx->u8Buff[8] = u32BaseID >> 16;
    pEsp3Tx->u8Buff[9] = u32BaseID >> 8;
    pEsp3Tx->u8Buff[10] = u32BaseID & 0xFF;
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadBaseID(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_IDBASE;
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadBaseIDRespone(uint8_t* u8ReceiveBuff, EnoceanTCM310_Typedef *pEnoceanTCM310)
{
    pEnoceanTCM310->HW.u32BaseID           = ((uint32_t)u8ReceiveBuff[7] << 24) | ((uint32_t)u8ReceiveBuff[8] << 16) |
                                             ((uint32_t)u8ReceiveBuff[9] << 8) | ((uint32_t)u8ReceiveBuff[10]);
    pEnoceanTCM310->HW.u8BaseIDRemainCycle = u8ReceiveBuff[11];
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteReapter(Esp3Tx_Typedef *pEsp3Tx,  uint8_t u8ReapterLevel)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 3;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 3;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_REPEATER;

    if ( u8ReapterLevel )
    {
        pEsp3Tx->u8Buff[7] = 1;
        pEsp3Tx->u8Buff[8] = u8ReapterLevel;
    }
    else
    {
        pEsp3Tx->u8Buff[7] = 0;
        pEsp3Tx->u8Buff[8] = 0;
    }

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadReapter(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_REPEATER;

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadReapterRespone(uint8_t* u8ReceiveBuff, EnoceanTCM310_Typedef *pEnoceanTCM310)
{
    if ( u8ReceiveBuff[7] )
    {
        pEnoceanTCM310->HW.u8Reapter = u8ReceiveBuff[8];
    }
    else
    {
        pEnoceanTCM310->HW.u8Reapter = 0;
    }
}

/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteSubTel(Esp3Tx_Typedef *pEsp3Tx, uint8_t u8SubTel)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 2;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 2;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_SUBTEL;

    pEsp3Tx->u8Buff[7] = u8SubTel;
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterAdd(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 7;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 7;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_FILTER_ADD;

    pEsp3Tx->u8Buff[7] = Filter.u8Type;
    pEsp3Tx->u8Buff[8] = Filter.u32Value>>24;
    pEsp3Tx->u8Buff[9] = Filter.u32Value >> 16;
    pEsp3Tx->u8Buff[10] = Filter.u32Value >> 8;
    pEsp3Tx->u8Buff[11] = Filter.u32Value&0xFF;
    pEsp3Tx->u8Buff[12] = Filter.u8Kind;

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterDel(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 7;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 7;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_FILTER_DEL;

    pEsp3Tx->u8Buff[7] = Filter.u8Type;
    pEsp3Tx->u8Buff[8] = Filter.u32Value >> 24;
    pEsp3Tx->u8Buff[9] = Filter.u32Value >> 16;
    pEsp3Tx->u8Buff[10] = Filter.u32Value >> 8;
    pEsp3Tx->u8Buff[11] = Filter.u32Value & 0xFF;


    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterDelAll(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_FILTER_DEL_ALL;

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteFliterEnable(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 3;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 3;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_FILTER_ENABLE;

    pEsp3Tx->u8Buff[7] = Filter.u8OnOff;

    /*  area */
    pEsp3Tx->u8Buff[8] = Filter.u8Operator;
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadFliter(Esp3Tx_Typedef *pEsp3Tx, EnOceanFilter_Typedef Filter)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_FILTER;


    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadFliterRespone(uint8_t* u8ReceiveBuff, EnOceanFilter_Typedef *Filter)
{

}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteWaitMaturity(Esp3Tx_Typedef *pEsp3Tx, uint8_t u8MaturityEnable)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 2;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 2;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_WAIT_MATURITY;

    pEsp3Tx->u8Buff[7] = u8MaturityEnable;
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_WriteMemory(Esp3Tx_Typedef *pEsp3Tx, EnoceanMemory_Typedef EnoceanMemory,uint16_t u16WriteBytes)
{

    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 6 + u16WriteBytes;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = (6 + u16WriteBytes)>>8;
    pEsp3Tx->u8Buff[2] = (6 + u16WriteBytes)&0xFF;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_WR_MEM;

    pEsp3Tx->u8Buff[7] = EnoceanMemory.u8Type;

    /*  area */
    pEsp3Tx->u8Buff[8] = EnoceanMemory.u32StartAddress>>24;
    pEsp3Tx->u8Buff[9] = EnoceanMemory.u32StartAddress >> 16;
    pEsp3Tx->u8Buff[10] = EnoceanMemory.u32StartAddress >> 8;
    pEsp3Tx->u8Buff[11] = EnoceanMemory.u32StartAddress & 0xFF;

    memcpy(&pEsp3Tx->u8Buff[12], EnoceanMemory.u8Data, u16WriteBytes);

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemory(Esp3Tx_Typedef *pEsp3Tx, EnoceanMemory_Typedef EnoceanMemory, uint16_t u16ReadBytes)
{

    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 8;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 8;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_MEM;

    pEsp3Tx->u8Buff[7] = EnoceanMemory.u8Type;

    /*  area */
    pEsp3Tx->u8Buff[8] = EnoceanMemory.u32StartAddress >> 24;
    pEsp3Tx->u8Buff[9] = EnoceanMemory.u32StartAddress >> 16;
    pEsp3Tx->u8Buff[10] = EnoceanMemory.u32StartAddress >> 8;
    pEsp3Tx->u8Buff[11] = EnoceanMemory.u32StartAddress & 0xFF;
    pEsp3Tx->u8Buff[12] = u16ReadBytes >> 8;
    pEsp3Tx->u8Buff[13] = u16ReadBytes & 0xFF;
    memcpy(&pEsp3Tx->u8Buff[12], EnoceanMemory.u8Data, u16ReadBytes);

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemoryRespone(uint8_t *u8ReceiveBuff, EnoceanMemory_Typedef *EnoceanMemory)
{


}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemoryAddress(Esp3Tx_Typedef *pEsp3Tx,  uint8_t u8MemoryArea)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 2;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 2;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_MEM_ADDRESS;

    pEsp3Tx->u8Buff[7] = u8MemoryArea;

    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_ReadMemoryAddressRespone(uint8_t* u8ReceiveBuff,  EnoceanMemory_Typedef *EnoceanMemory)
{

}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CO_ReadDutyCycleLimit(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_COMMON_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);
    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RD_DUTYCYCLE_LIMIT;	
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ESP3_CommonCommandInitExit(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = CO_RESERVED;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = CO_RESERVED;
    pEsp3Tx->u8Buff[2] = CO_RESERVED;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = CO_RESERVED;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = CO_RESERVED;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /*  area */
    pEsp3Tx->u8Buff[6] = CO_RESERVED;

    pEsp3Tx->u8Buff[7] = CO_RESERVED;
    //pEsp3Tx->u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;
}
/******************************* remote mangement Start*************************************************/
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t ESP3_ReManData2SerialBuff(Radio_Typedef *pRadio,Esp3Tx_Typedef *pEsp3Tx)
{
    uint8_t i;
    uint16_t u16DataLength;
    uint8_t  u8OptionalLength;

    u16DataLength    = (uint16_t)pRadio->u16DataLength;
    u8OptionalLength = (uint8_t)pRadio->u8OptionalDataLength;

    pEsp3Tx->u16ByteMax = u8OptionalLength+u16DataLength+7;

    if ( pEsp3Tx->u16ByteMax > ESP3_TX_BUF_MAX )
    {
        return ESP_SEND_BUFF_OVF_MAX_ERR;
    }

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = u16DataLength>>8;
    pEsp3Tx->u8Buff[2] = u16DataLength&0xFF;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = u8OptionalLength;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = pRadio->u8PacketType;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff,1,4);

    //sys_ex.sys_ex_data.u4FnNumH
    //sys_ex.sys_ex_data.u7ManufacturerIdH
    /*  area */
    pEsp3Tx->u8Buff[6] = pRadio->Telegram.ReMan.u16FnNum>>8;
    pEsp3Tx->u8Buff[7] = pRadio->Telegram.ReMan.u16FnNum&0xFF;
    pEsp3Tx->u8Buff[8] = pRadio->Telegram.ReMan.u16ManId>>8;
    pEsp3Tx->u8Buff[9] = pRadio->Telegram.ReMan.u16ManId&0xFF;

    for (i = 0; i < u16DataLength-4; i++)
    {
        pEsp3Tx->u8Buff[10 + i] = pRadio->Telegram.ReMan.u8Data[i];
    }

    /* Optional  area */
    /* Send ID */
    pEsp3Tx->u8Buff[ u16DataLength + 6 ] = (pRadio->Param.ReMan.u32DestinationId>>24)&0xFF;
    pEsp3Tx->u8Buff[ u16DataLength + 7 ] = (pRadio->Param.ReMan.u32DestinationId>>16)&0xFF;
    pEsp3Tx->u8Buff[ u16DataLength + 8 ] = (pRadio->Param.ReMan.u32DestinationId>> 8)&0xFF;
    pEsp3Tx->u8Buff[ u16DataLength + 9 ] = (pRadio->Param.ReMan.u32DestinationId    )&0xFF;
    pEsp3Tx->u8Buff[ u16DataLength + 10 ] = (pRadio->Param.ReMan.u32SourceId >> 24)&0xFF;
    pEsp3Tx->u8Buff[ u16DataLength + 11 ] = (pRadio->Param.ReMan.u32SourceId >> 16)&0xFF;
    pEsp3Tx->u8Buff[ u16DataLength + 12 ] = (pRadio->Param.ReMan.u32SourceId >>  8)&0xFF;
    pEsp3Tx->u8Buff[ u16DataLength + 13 ] = (pRadio->Param.ReMan.u32SourceId      )&0xFF;

    pEsp3Tx->u8Buff[ u16DataLength + 14 ] = 0xFF;
    /*
    if ( 0xFFFFFFFF == pRadio->Param.ReMan.u32DestinationId )
    {
        pEsp3Tx->u8Buff[u16DataLength + 15] = 1;
    }
    else
    {
        pEsp3Tx->u8Buff[u16DataLength + 15] = pRadio->u8RandomEnable;
    }
    */
    pEsp3Tx->u8Buff[u16DataLength + 15] = pRadio->Param.ReMan.u8RandSendDelayEnable;//pRadio->u8RandomEnable;
    pEsp3Tx->u8RandomEn                  = pRadio->Param.ReMan.u8RandSendDelayEnable;//pRadio->u8RandomEnable;
    //u16DataLength += 4;
    /* Data and optional  crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff,6,u16DataLength + u8OptionalLength);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return OK;
}
/**
  * @brief
  * @param
  * @retval None
*/
uint16_t ESP3_SerialBuff2RemanData(Radio_Typedef *pRadio,uint8_t *u8SerialBuff)
{
    uint8_t i;
    uint16_t u16DataLength;

    /* Get user  length */
    u16DataLength = (uint16_t)(u8SerialBuff[1]<<8) + (uint16_t)u8SerialBuff[2];
    /* Get Optional  length */

    pRadio->u8PacketType = u8SerialBuff[4];

    /*  area */

    pRadio->Telegram.ReMan.u16FnNum = (uint16_t)u8SerialBuff[6]<<8 | (uint16_t)u8SerialBuff[7];
    pRadio->Telegram.ReMan.u16ManId = (uint16_t)u8SerialBuff[8]<<8 | (uint16_t)u8SerialBuff[9];
    pRadio->Telegram.ReMan.u8Length = u16DataLength-4;
    for (i = 0; i < u16DataLength-4; i++)
    {
        pRadio->Telegram.ReMan.u8Data[i]         = u8SerialBuff[10 + i];
    }

    /* Optional  area */
    /* Send ID */

    pRadio->Param.ReMan.u32DestinationId         = (uint32_t)u8SerialBuff[ u16DataLength + 6 ]<<24|
                                                   (uint32_t)u8SerialBuff[ u16DataLength + 7 ]<<16|
                                                   (uint32_t)u8SerialBuff[ u16DataLength + 8 ]<<8|
                                                   (uint32_t)u8SerialBuff[ u16DataLength + 9 ];

    pRadio->Param.ReMan.u32SourceId              = (uint32_t)u8SerialBuff[ u16DataLength + 10 ]<<24|
                                                   (uint32_t)u8SerialBuff[ u16DataLength + 11 ]<<16|
                                                   (uint32_t)u8SerialBuff[ u16DataLength + 12 ]<<8|
                                                   (uint32_t)u8SerialBuff[ u16DataLength + 13 ];

    pRadio->Param.ReMan.u8Dbm                    = u8SerialBuff[ u16DataLength + 14 ];
    pRadio->Param.ReMan.u8RandSendDelayEnable = 0x00;

    //pRadio->u8RandomEnable = 0;

	/* Data and optional  crc8 */

    return OK;
}

/******************************* remote mangement end *************************************************/
/**
  * @brief
  * @param
  * @retval None
*/
uint8_t ESP3_SerialBuffHeaderCheck(uint8_t *u8PrcBuff)
{
    /* Header check */
    if ( 0x55 != u8PrcBuff[0] )
    {
        return !OK;
    }
    /* Header check crc8 */
    if ( u8PrcBuff[5] != u8GetCrc8(u8PrcBuff,1,4) )
    {
        return !OK;
    }

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
*/
uint8_t ESP3_SerialBuff2Check(uint8_t *u8PrcBuff)
{
    uint16_t u16DataLength;
    uint8_t  u8OptionalLength;
    uint16_t u16DataMax;

#if 0
    /* Header check */
    if ( 0x55 != u8PrcBuff[0] )
    {
        return !OK;
    }
#endif
    /* Header check crc8 */
    if ( u8PrcBuff[5] != u8GetCrc8(u8PrcBuff,1,4) )
    {
        return !OK;
    }

    u16DataLength = (uint16_t)(u8PrcBuff[1]<<8) + (uint16_t)u8PrcBuff[2];

    u8OptionalLength = u8PrcBuff[3];


    u16DataMax = u16DataLength + (uint16_t)u8OptionalLength + (uint16_t)7;
    if ( u8PrcBuff[u16DataMax - 1] != u8GetCrc8(u8PrcBuff,6,u16DataLength + u8OptionalLength) )
    {

        return !OK;
    }

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t ESP3_SerialBuff2RadioData(Radio_Typedef *pReceiveRadio,uint8_t *u8SerialBuff)
{
    uint8_t  u8i;
    uint16_t u16DataLength;
    uint8_t  u8OptionalLength;
    
    /* Get user  length */
    u16DataLength = (uint16_t)(u8SerialBuff[1]<<8) + (uint16_t)u8SerialBuff[2];
    /* Get Optional  length */
    u8OptionalLength = u8SerialBuff[3];

    /* Add the Data to the deveice's EEP */
    /* user  */
    for ( u8i = 0; u8i < u16DataLength - 6 ; u8i++ )
    {
        pReceiveRadio->Telegram.raw.bytes[u8i]      = u8SerialBuff[7 + u8i];
    }
    pReceiveRadio->Telegram.raw.u8Status            = u8SerialBuff[u16DataLength + 5 ];
    pReceiveRadio->u8PacketType                     = u8SerialBuff[4];
    pReceiveRadio->Telegram.raw.u8RORG              = (CHOICE_TYPE) u8SerialBuff[6];
    
    pReceiveRadio->Param.p_rx.u32SourceId           = ((uint32_t)u8SerialBuff[u16DataLength + 1 ]<<24) |
                                                      ((uint32_t)u8SerialBuff[u16DataLength + 2 ]<<16) |
                                                      ((uint32_t)u8SerialBuff[u16DataLength + 3 ]<<8)  |
                                                                (u8SerialBuff[u16DataLength + 4 ]);
    pReceiveRadio->u16DataLength                    = u16DataLength;
    pReceiveRadio->u8OptionalDataLength             = u8OptionalLength;


    pReceiveRadio->Param.p_rx.u8SubTelNum           = u8SerialBuff[6 + u16DataLength];

    pReceiveRadio->Param.p_rx.u32DestinationId      = ((uint32_t)u8SerialBuff[7 + u16DataLength]  << 24) |
                                                      ((uint32_t)u8SerialBuff[8 + u16DataLength]  << 16) |
                                                      ((uint32_t)u8SerialBuff[9 + u16DataLength]  << 8)  |
                                                      ((uint32_t)u8SerialBuff[10 + u16DataLength] << 0);

    pReceiveRadio->Param.p_rx.u8Dbm                 = u8SerialBuff[11 + u16DataLength];
    pReceiveRadio->Param.p_rx.u8SecurityLevel       = u8SerialBuff[12 + u16DataLength];

    return OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint16_t ESP3_RadioSendData2SerialBuff(Radio_Typedef *pSendRadio)
{
    uint8_t i;
    uint16_t u16DataLength;
    uint8_t  u8OptionalLength;

    u16DataLength    = (uint16_t)pSendRadio->u16DataLength;
    u8OptionalLength =  (uint8_t)pSendRadio->u8OptionalDataLength;

    //pEnoceanBus->u8SendByteCnt = 0;
    Esp3Tx.u16ByteMax = 7;
    Esp3Tx.u16ByteMax += u16DataLength;
    Esp3Tx.u16ByteMax += u8OptionalLength;

    if ( Esp3Tx.u16ByteMax > ESP3_TX_BUF_MAX )
    {
        return ESP_SEND_BUFF_OVF_MAX_ERR;
    }

    /* Header */
    /* Sync Byte */
    Esp3Tx.u8Buff[0] = 0x55;
    /* Data Length */
    Esp3Tx.u8Buff[1] = u16DataLength>>8;
    Esp3Tx.u8Buff[2] = u16DataLength&0xFF;
    /* Optional Length */
    Esp3Tx.u8Buff[3] = u8OptionalLength;
    /* Packet Type */
    Esp3Tx.u8Buff[4] = pSendRadio->u8PacketType;
    /* CRC8 */
    Esp3Tx.u8Buff[5] = u8GetCrc8(Esp3Tx.u8Buff,1,4);

    /*  Set Radio Choice */
    Esp3Tx.u8Buff[6] = pSendRadio->Telegram.raw.u8RORG;
    /* Load user data to the serial buff area */
    for (i = 0; i < u16DataLength - 6; i++)
    {
        Esp3Tx.u8Buff[7 + i] = pSendRadio->Telegram.raw.bytes[i];
    }
    /* Set source ID */
    Esp3Tx.u8Buff[1 + u16DataLength] = pSendRadio->Param.p_tx.u32SourceId >> 24;
    Esp3Tx.u8Buff[2 + u16DataLength] = pSendRadio->Param.p_tx.u32SourceId >> 16;
    Esp3Tx.u8Buff[3 + u16DataLength] = pSendRadio->Param.p_tx.u32SourceId >>  8;
    Esp3Tx.u8Buff[4 + u16DataLength] = pSendRadio->Param.p_tx.u32SourceId &0xFF;
    
    
    if ( Esp3Tx.u8Buff[6] == RADIO_CHOICE_RPS )
    {
        /* Status */
        Esp3Tx.u8Buff[u16DataLength + 5] = pSendRadio->Telegram.RPS.u8Status;
        #if 0
        if ( pEsp3Tx->u8Buff[7] )
        {
            pEsp3Tx->u8Buff[u16DataLength + 5] = pSendRadio->Telegram.RPS.u8Status;
        }
        else
        {
            pEsp3Tx->u8Buff[u16DataLength + 5] = 0x20;
        }
        #endif
    }
    else
    {
        /* Status */
        Esp3Tx.u8Buff[u16DataLength + 5] = 0x00;
    }


    /* Send ID */

    /* Optional  area */
    Esp3Tx.u8Buff[6 + u16DataLength]  = 3;//pSendRadio->u8SubTelNum;

    Esp3Tx.u8Buff[7 + u16DataLength]  = (pSendRadio->Param.p_tx.u32DestinationId>>24)&0xFF;
    Esp3Tx.u8Buff[8 + u16DataLength]  = (pSendRadio->Param.p_tx.u32DestinationId>>16)&0xFF;
    Esp3Tx.u8Buff[9 + u16DataLength]  = (pSendRadio->Param.p_tx.u32DestinationId>> 8)&0xFF;
    Esp3Tx.u8Buff[10 + u16DataLength] = (pSendRadio->Param.p_tx.u32DestinationId    )&0xFF;
    Esp3Tx.u8Buff[11 + u16DataLength] = 0xFF;//pSendRadio->Param.p_tx.u8Dbm;
    Esp3Tx.u8Buff[12 + u16DataLength] = pSendRadio->Param.p_tx.u8SecurityLevel;

    /* Data and optional  crc8 */
    Esp3Tx.u8Buff[Esp3Tx.u16ByteMax - 1] = u8GetCrc8(Esp3Tx.u8Buff,6,u16DataLength + u8OptionalLength);    
    Esp3Tx.u8RetransmissionCnt       = ESP3_RETRANSMISSION_NUM;

    pSendRadio->u8PacketType = PACKET_RESERVED;
    return OK;
}
/* SA = smart ack */
/* Lrn = learn */
/* En = Enable */
/* PM = Post Master */


/**
  * @brief
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckPraseRadioData(uint8_t* p8ReceiveBuff,Radio_Typedef *pRadio)
{
    //! Smart Ack Learn Reuqest telegram
    if ( RADIO_CHOICE_SM_LRN_REQ == p8ReceiveBuff[6] )
    {
        pRadio->Telegram.SmartAck.u8RORG = RADIO_CHOICE_SM_LRN_REQ;
        pRadio->Telegram.SmartAck.u5ReqCode = p8ReceiveBuff[7]>>3;
        pRadio->Telegram.SmartAck.u16ManId  = ((uint16_t)p8ReceiveBuff[7]&0x07)<<8|(uint16_t)p8ReceiveBuff[8];
        //pRadio->Telegram.SmartAck.u8RssiDbm        = p8ReceiveBuff[10];
        pRadio->Telegram.SmartAck.u8ClientEEP_RORG = p8ReceiveBuff[9];
        pRadio->Telegram.SmartAck.u8ClientEEP_FUN  = p8ReceiveBuff[10];
        pRadio->Telegram.SmartAck.u8ClientEEP_TYPE = p8ReceiveBuff[11];  
        
        pRadio->Telegram.SmartAck.u32PostMasterID  = (uint32_t)p8ReceiveBuff[14]<<24|
                                                     (uint32_t)p8ReceiveBuff[15]<<16|
                                                     (uint32_t)p8ReceiveBuff[16]<<8|
                                                     (uint32_t)p8ReceiveBuff[17];
         
        pRadio->Telegram.SmartAck.u32ClientId      = (uint32_t)p8ReceiveBuff[17]<<24|
                                                     (uint32_t)p8ReceiveBuff[18]<<16|
                                                     (uint32_t)p8ReceiveBuff[19]<<8|
                                                     (uint32_t)p8ReceiveBuff[20];  //客� ��  ID
        pRadio->Telegram.SmartAck.u8Status         = p8ReceiveBuff[21];

    }
    //! Smart Ack Learn Answer telegram
    else if ( RADIO_CHOICE_SM_LRN_ANS == p8ReceiveBuff[6] )
    {
        pRadio->Telegram.SmartAck.u8RORG = RADIO_CHOICE_SM_LRN_ANS;
    }
    //! Smart Ack Reclaim telegram  请�?信�  
    else if ( RADIO_CHOICE_RECLAIM == p8ReceiveBuff[6] )
    {
        pRadio->Telegram.SmartAck.u8RORG = RADIO_CHOICE_RECLAIM;
    }
    else
    {
        return 1;
    }
    
    return 0;
}
/**
  * @brief  Enables or disables learn mode of smart ack
  *         controller
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckWriteLearnMode(Esp3Tx_Typedef *pEsp3Tx,uint32_t u32TimeOut,uint8_t u8Extend,uint8_t u8Enable)
{
    pEsp3Tx->u16ByteMax = 14;
    //pEsp3Tx->u16ByteMax += 7;
    //pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 7;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_SMART_ACK_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /* data area */
    pEsp3Tx->u8Buff[6] = SA_WR_LEARNMODE;

    pEsp3Tx->u8Buff[7]  = u8Enable;
    pEsp3Tx->u8Buff[8]  = u8Extend;
    pEsp3Tx->u8Buff[9]  = u32TimeOut>>24;
    pEsp3Tx->u8Buff[10] = u32TimeOut>>16;
    pEsp3Tx->u8Buff[11] = u32TimeOut>>8;
    pEsp3Tx->u8Buff[12] = u32TimeOut&0xFF;
    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return 0;
}
/**
  * @brief  Reads the learnmode state of smart ack controller
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckReadLearnMode(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_SMART_ACK_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /* data area */
    pEsp3Tx->u8Buff[6] = SA_RD_LEARNMODE;

    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return 0;
}

/**
  * @brief  Send smart ack learn answer to modify mailbox at
  *         postmaster
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckWriteLearnConfirm(Esp3Tx_Typedef *pEsp3Tx,uint16_t u16ResponseTime,
                                                           uint8_t u8ConfirmCode,
                                                           uint32_t u32PostMasterCandidateID,
                                                           uint32_t u32SmartAckClientID)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 12;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 12;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_SMART_ACK_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /* data area */
    pEsp3Tx->u8Buff[6] = SA_WR_LEARNCONFIRM;

    pEsp3Tx->u8Buff[7] = u16ResponseTime>>8;
    pEsp3Tx->u8Buff[8] = u16ResponseTime&0xFF;
    pEsp3Tx->u8Buff[9] = u8ConfirmCode;
    pEsp3Tx->u8Buff[10] = u32PostMasterCandidateID>>24;
    pEsp3Tx->u8Buff[11] = u32PostMasterCandidateID>>16;
    pEsp3Tx->u8Buff[12] = u32PostMasterCandidateID>>8;
    pEsp3Tx->u8Buff[13] = u32PostMasterCandidateID&0xFF;
    pEsp3Tx->u8Buff[14] = u32SmartAckClientID>>24;
    pEsp3Tx->u8Buff[15] = u32SmartAckClientID>>16;
    pEsp3Tx->u8Buff[16] = u32SmartAckClientID>>8;
    pEsp3Tx->u8Buff[17] = u32SmartAckClientID&0xFF;
    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return 0;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckWriteReset(Esp3Tx_Typedef *pEsp3Tx,uint32_t u32ClientID)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 5;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 5;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_SMART_ACK_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /* data area */
    pEsp3Tx->u8Buff[6] = SA_WR_RESET;

    pEsp3Tx->u8Buff[8] = u32ClientID>>24;
    pEsp3Tx->u8Buff[9] = u32ClientID>>16;
    pEsp3Tx->u8Buff[10] = u32ClientID>>8;
    pEsp3Tx->u8Buff[11] = u32ClientID&0xFF;

    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return 0;
}
/**
  * @brief  This function will only be used in a smart ack
  *         client
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckReadLearnedClients(Esp3Tx_Typedef *pEsp3Tx)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_SMART_ACK_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /* data area */
    pEsp3Tx->u8Buff[6] = SA_RD_LEARNEDCLIENTS;

    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return 0;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckWritePostMaster(Esp3Tx_Typedef *pEsp3Tx,uint8_t u8MailBoxCount)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 2;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 2;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_SMART_ACK_COMMAND;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /* data area */
    pEsp3Tx->u8Buff[6] = SA_WR_POSTMASTER;
    pEsp3Tx->u8Buff[7] = u8MailBoxCount;

    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return 0;
}
/**
  * @brief  samrt reclaim not successful Receive
  * @param
  * @retval None
  */
uint8_t EnOceanEvent2SmartAckData(Radio_Typedef *pRadio,uint8_t *p8SerialBuff)
{
    //struct sm_lrn_req lrn;
    pRadio->u8PacketType                       = p8SerialBuff[4];
    //pRadio->Telegram.raw.u8RORG              =u8EventCode
    pRadio->Telegram.SmartAck.u8EventCode = p8SerialBuff[6];
    switch ( p8SerialBuff[6] )
    {
    case SA_RECLAIM_NOT_SUCCESSFUL:
        //return Esp3_SmartAckReclaimNotSuccessful(p8SerialBuff);
        break;
    case SA_CONFIRM_LEARN:
      return Esp3_SmartAckConfirmLearn(p8SerialBuff,pRadio);  //
    case SA_LEARN_ACK:
        /*
        return Esp3_SmartAckLearnAck(p8SerialBuff,&pRadio->Telegram.SmartAck.u16ResponseTime,
                                                  &pRadio->Telegram.SmartAck.u8ConfirmCode);
        */
        break;
    case CO_READY:
        return Esp3_SmartAckCoReady(p8SerialBuff,&pRadio->Telegram.SmartAck.u8ResetCause);
    case CO_EVENT_SECUREDEVICES:
        /*
        return Esp3_SmartAckSecureDevices(p8SerialBuff,&pRadio->Telegram.SmartAck.u8EventCause,
                                                       &pRadio->Telegram.SmartAck.u32ClientId);
        */ 
        break;
    }
    return !OK;
}
/**
  * @brief  samrt reclaim not successful Receive
  * @param
  * @retval None
  */
uint8_t Esp3_EventSmartAckResponse(Radio_Typedef *pRadio,Esp3Tx_Typedef *pEsp3Tx)
{
    pRadio->u8PacketType = PACKET_EVENT;
    switch ( pRadio->Telegram.SmartAck.u8EventCode )
    {
    case SA_RECLAIM_NOT_SUCCESSFUL:
        Esp3_SmartAckReclaimNotSuccessfulResponse(pEsp3Tx,pRadio->Telegram.SmartAck.u8Status);
        break;
    case SA_CONFIRM_LEARN:
        Esp3_SmartAckConfirmLearnResponse(pEsp3Tx,pRadio->Telegram.SmartAck.u16ResponseTime,
                                                  pRadio->Telegram.SmartAck.u8ConfirmCode,
                                                  pRadio->Telegram.SmartAck.u8Status);
        break;
    case SA_LEARN_ACK:
        
        //Esp3_SmartAckLearnAckResponse(pEsp3Tx,pRadio->Telegram.SmartAck.u8Status);
        break;
    case CO_READY:
        //Esp3_SmartAckCoReady(p8SerialBuff,&u8ResetCode);
        break;
    case CO_EVENT_SECUREDEVICES:
        //Esp3_SmartAckSecureDevices(p8SerialBuff,&u8EventCause,&u32DeviceID);
        break;
    }

    return 0;
}
//#if 0 --- 2018-3-5
/**
  * @brief  samrt reclaim not successful Receive
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckReclaimNotSuccessful(uint8_t* p8ReceiveBuff)
{
    return p8ReceiveBuff[5];
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckReclaimNotSuccessfulResponse(Esp3Tx_Typedef *pEsp3Tx,uint8_t u8ResponseStatus)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 1;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 1;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_RESPONSE;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);

    /* data area */
    pEsp3Tx->u8Buff[6] = u8ResponseStatus;

    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);

    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;

    return 0;
}
//#endif --- 2018-3-5
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckConfirmLearn(uint8_t* p8ReceiveBuff,Radio_Typedef *pRadio)
{
    pRadio->Telegram.SmartAck.u8PriorityOfPostMaster     = (p8ReceiveBuff[7]&0x0F);
    pRadio->Telegram.SmartAck.u16ManId                   = (uint16_t)(p8ReceiveBuff[8]&0x07)<<8|(uint16_t)p8ReceiveBuff[9];  
    pRadio->Telegram.SmartAck.u8ClientEEP_RORG           = p8ReceiveBuff[10];
    pRadio->Telegram.SmartAck.u8ClientEEP_FUN            = p8ReceiveBuff[11];
    pRadio->Telegram.SmartAck.u8ClientEEP_TYPE           = p8ReceiveBuff[12];

    pRadio->Telegram.SmartAck.u8RssiDbm                  = p8ReceiveBuff[13];

    pRadio->Telegram.SmartAck.u32PostMasterID            = (uint32_t)p8ReceiveBuff[14]<<24 |(uint32_t)p8ReceiveBuff[15] <<16|
                                                           (uint32_t)p8ReceiveBuff[16]<<8  |(uint32_t)p8ReceiveBuff[17];
    pRadio->Telegram.SmartAck.u32ClientId                = (uint32_t)p8ReceiveBuff[18]<<24 |(uint32_t)p8ReceiveBuff[19] <<16|
                                                           (uint32_t)p8ReceiveBuff[20]<<8  |(uint32_t)p8ReceiveBuff[21];

    pRadio->Telegram.SmartAck.u8HopCount                 = p8ReceiveBuff[22];

    return 0;
}
/**
  * @brief  SmartAckConfirmLearn event response
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckConfirmLearnResponse(Esp3Tx_Typedef *pEsp3Tx,uint16_t u16ResponseTime,
                                                                  uint8_t  u8ConfirmCode,
                                                                  uint8_t  u8ResponseStatus)
{
    pEsp3Tx->u16ByteMax = 7;
    pEsp3Tx->u16ByteMax += 4;
    pEsp3Tx->u16ByteMax += 0;

    /* Header */
    /* Sync Byte */
    pEsp3Tx->u8Buff[0] = 0x55;
    /* Data Length */
    pEsp3Tx->u8Buff[1] = 0;
    pEsp3Tx->u8Buff[2] = 4;
    /* Optional Length */
    pEsp3Tx->u8Buff[3] = 0;
    /* Packet Type */
    pEsp3Tx->u8Buff[4] = PACKET_RESPONSE;
    /* CRC8 */
    pEsp3Tx->u8Buff[5] = u8GetCrc8(pEsp3Tx->u8Buff, 1, 4);
    pEsp3Tx->u8Buff[6] = u8ResponseStatus;
    /* data area */
    pEsp3Tx->u8Buff[7] = u16ResponseTime>>8;
    pEsp3Tx->u8Buff[8] = u16ResponseTime&0xFF;
    pEsp3Tx->u8Buff[9] = u8ConfirmCode;
    /* Data and optional data crc8 */
    pEsp3Tx->u8Buff[pEsp3Tx->u16ByteMax - 1] = u8GetCrc8(pEsp3Tx->u8Buff, 6, pEsp3Tx->u16ByteMax - 7);
    pEsp3Tx->u8RetransmissionCnt = ESP3_RETRANSMISSION_NUM;
    return 0;
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t Esp3_SmartAckCoReady(uint8_t* p8ReceiveBuff,uint8_t  *p8ResetCode)
{
    *p8ResetCode = p8ReceiveBuff[7];

    return 0;
}


/************************** Remote mangement end *****************************************/

/* end of file */
