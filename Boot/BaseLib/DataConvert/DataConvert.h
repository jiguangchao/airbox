

#ifndef _DATA_CONVERT_H_
#define _DATA_CONVERT_H_


extern const uint8_t HexCode[];

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
//void NumericalVariable2String_Dec(char *str,uint32_t u32Num);

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
//void NumericalVariable2String_Hex(char *str,uint32_t u32Num);
/**
  * @brief
  * @param
  * @retval None
  */
void HSVtoRGB(uint8_t *r, uint8_t *g, uint8_t *b, uint16_t h, uint16_t s, uint16_t v);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void ClearBuff(char *p,uint8_t u8Size);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2DecBlinkBuff(char *p8Buff,uint8_t u8BuffSize,uint32_t u32Input);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2DecBuff(char *p8Buff,int32_t i32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Num2HexBuff(char *p8Buff,uint32_t u32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void Version2HexBuff(char *p8Buff,uint32_t u32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void YYMMDD2HexBuff(char *p8Buff,uint32_t u32Data);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HHMMSS2HexBuff(char *p8Buff,uint32_t u32Data);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: 16位数据转换成字符串
//功能:
//入口: 
//      in_data  ---16位的shu
//      out_string  字符串指针
//
//出口: 
//-------------------------------------------------------------------------------------------------
void pbc_int16u_to_string_convert(uint16_t in_data,char* out_string);
//-------------------------------------------------------------------------------------------------
void pbc_string_append(char* in_pAppend,char* out_string);
//-------------------------------------------------------------------------------------------------
uint16_t pbc_arrayToInt16u_bigEndian(uint8_t* in_data);
//-------------------------------------------------------------------------------------------------
uint32_t pbc_arrayToInt32u_bigEndian(uint8_t* in_data);
//-------------------------------------------------------------------------------------------------
void pbc_int16uToArray_bigEndian(uint16_t in_data,uint8_t* out_array);
//-------------------------------------------------------------------------------------------------
void pbc_int32uToArray_bigEndian(uint32_t in_data,uint8_t* out_array);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void pbc_int32u_to_array_small_endian(uint32_t in_data,uint8_t* out_array);
uint32_t pbc_array_to_int32u_small_endian(uint8_t* in_data);

void pbc_array_copy(uint8_t *copy,uint8_t *dat,uint8_t length);
uint8_t pbc_array_compcare(uint8_t *array1,uint8_t *array2,uint8_t length);
void pbc_array16_copy(uint16_t *copy,uint16_t *dat,uint8_t length);
uint8_t pbc_array16_compcare(uint16_t *array1,uint16_t *array2,uint8_t length);

uint8_t pbc_boardcast_compcare(uint8_t *array1);

uint8_t pbc_byte_array_compcare_value(uint8_t *array1,uint16_t u8length,uint8_t u8value);
#endif

/* End of file */
