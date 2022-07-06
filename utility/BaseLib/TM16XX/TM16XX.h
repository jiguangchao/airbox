

#ifndef _TM16XX_H_
#define _TM16XX_H_


/*********************************************************************************/
#define TM16XX_DELAY_COUNT                           (10)  
/*********************************************************************************/

#define TM16XX_CMD_DISPLAY                           (0x00)
#define TM16XX_CMD_DISPLAY_MODE_2_8                  (0x00)
#define TM16XX_CMD_DISPLAY_MODE_3_7                  (0x03)

#define TM16XX_CMD_DATA                              (0x40)
#define TM16XX_CMD_DATA_WRITE_TO_REGISTER            (0x00)
#define TM16XX_CMD_DATA_READ_KEY                     (0x02)
#define TM16XX_CMD_DATA_ADD_AUTO_INCREASE            (0x00)
#define TM16XX_CMD_DATA_ADD_FIXED                    (0x04)
#define TM16XX_CMD_DATA_MODE_NORMAL                  (0x00)
#define TM16XX_CMD_DATA_MODE_TEST                    (0x08)

#define TM16XX_CMD_ADDRESS                           (0xC0)

#define TM16XX_CMD_DISPLAY_CONTROL                   (0x80)
#define TM16XX_CMD_DUTY_1_16                         (0x00)
#define TM16XX_CMD_DUTY_2_16                         (0x01)
#define TM16XX_CMD_DUTY_4_16                         (0x02)
#define TM16XX_CMD_DUTY_10_16                        (0x03)
#define TM16XX_CMD_DUTY_11_16                        (0x04)
#define TM16XX_CMD_DUTY_12_16                        (0x05)
#define TM16XX_CMD_DUTY_13_16                        (0x06)
#define TM16XX_CMD_DUTY_14_16                        (0x07)
#define TM16XX_CMD_DISPLAY_OFF                       (0x00)
#define TM16XX_CMD_DISPLAY_ON                        (0x08)
/*********************************************************************************/
typedef struct 
{   
    void(*pSetStbHigh)(void);
    void(*pSetStbLow)(void);     
    void(*pSetClkHigh)(void);
    void(*pSetClkLow)(void);
    void(*pSetDataHigh)(void);
    void(*pSetDataLow)(void);
    void(*pSetDataInput)(void);
    void(*pSetDataOutput)(void);
    uint8_t(*pGetDataGpio)(void);
    void(*pWait)(uint16_t u16Delay);    
}sTM16XX_HW_Typedef;

typedef struct 
{
	uint8_t *pu8Button;
    uint8_t *pu8Led;

	//uint8_t ReadKeyCycle;
	//uint8_t DisplayCycle;	
    
    sTM16XX_HW_Typedef HWPort;

}sTM16XX_Typedef;

//extern stTM1617_Typedef   stTM1617;


/*********************************************************************************/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteByte(sTM16XX_Typedef *psTM16XX,uint8_t u8WriteDisplayData);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteCmd(sTM16XX_Typedef *psTM16XX,uint8_t u8WriteCmd);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t TM16XX_ReadByte(sTM16XX_Typedef *psTM16XX);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteDataAutoIncrease(sTM16XX_Typedef *psTM16XX);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteDataAutoIncreaseFixed(sTM16XX_Typedef *psTM16XX, uint8_t u8RegisterAddress);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_ReadKey(sTM16XX_Typedef *psTM16XX);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_LEDControl(sTM16XX_Typedef *psTM16XX,uint8_t u8DisplayControlCmd);

#endif
