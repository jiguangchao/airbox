

#ifndef _CRC_8_16_32_H_
#define _CRC_8_16_32_H_

/**
  * @brief  Get Buff CRC8
  * @param  *Buff Input the needs caulate
  *         BuffStart Can use buff Index
  *         DataLength
  * @retval Crc8 value
  */
unsigned char u8GetCrc8(unsigned char *Buff,unsigned char BuffStart,unsigned char DataLength);
/**
  * @brief
  * @param
  * @retval None
  */
//#pragma location = "IPECODE16"
unsigned int CRC16Get( unsigned char const* pucFrame, unsigned int usLen );


unsigned short crc16_ccitt_false_check(unsigned short *phwCRCValue, unsigned char chData);

unsigned short CRC16_CCITT_FALSE(const unsigned char *puchMsg, unsigned int usDataLen) ;
#endif




