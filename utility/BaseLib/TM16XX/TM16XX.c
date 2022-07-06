

#include "..\BaselibInclude.h"

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteByte(sTM16XX_Typedef *psTM16XX,uint8_t u8WriteData)
{
	uint8_t u8Data;		
		
	for (u8Data = 0x01; u8Data != 0x00; u8Data<<=1) 
	{	
		psTM16XX->HWPort.pSetClkLow();
        psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);

		if (u8WriteData&u8Data) 
		{
			psTM16XX->HWPort.pSetDataHigh();
		}
		else
		{
            psTM16XX->HWPort.pSetDataLow();			
		}
		psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);			
			
		psTM16XX->HWPort.pSetClkHigh();
		psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);
	}
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteCmd(sTM16XX_Typedef *psTM16XX,uint8_t u8WriteCmd)
{
	
	psTM16XX->HWPort.pSetStbHigh();
	psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);
	psTM16XX->HWPort.pSetStbLow();	
	psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);
	TM16XX_WriteByte(psTM16XX,u8WriteCmd);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
uint8_t TM16XX_ReadByte(sTM16XX_Typedef *psTM16XX)
{
	uint8_t u8Data;
	uint8_t ucReadData;
	
	ucReadData = 0x00;				
		
	for (u8Data = 0x01; u8Data != 0x00; u8Data <<= 1) 
	{
		psTM16XX->HWPort.pSetClkLow();
		
		psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT*2);		

		if (psTM16XX->HWPort.pGetDataGpio()) 
		{			
			ucReadData |= u8Data;
		}	
		psTM16XX->HWPort.pSetClkHigh();
			
		psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);
	}
	
	return ucReadData;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteDataAutoIncrease(sTM16XX_Typedef *psTM16XX)
{
    uint8_t u8DisplayRegister;
		
	/* Write Data */
	for (u8DisplayRegister = 0; u8DisplayRegister < 14; u8DisplayRegister++)//
	{
		TM16XX_WriteByte(psTM16XX,psTM16XX->pu8Led[u8DisplayRegister]);
	}
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_WriteDataAutoIncreaseFixed(sTM16XX_Typedef *psTM16XX, uint8_t u8RegisterAddress)
{
    TM16XX_WriteByte(psTM16XX,psTM16XX->pu8Led[u8RegisterAddress]);
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_ReadKey(sTM16XX_Typedef *psTM16XX)
{
    uint8_t u8KeyRegister;
				
	TM16XX_WriteCmd(psTM16XX,TM16XX_CMD_DATA|TM16XX_CMD_DATA_READ_KEY);
	psTM16XX->HWPort.pSetDataInput();
	
		
	psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT*2);	
			
	/* Read Data */
	for (u8KeyRegister = 0; u8KeyRegister < 5; u8KeyRegister++)
	{
		psTM16XX->pu8Button[u8KeyRegister] = TM16XX_ReadByte(psTM16XX);
	}	
	
	psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);
	
	psTM16XX->HWPort.pSetDataOutput();
	
	psTM16XX->HWPort.pWait(TM16XX_DELAY_COUNT);
    
	psTM16XX->HWPort.pSetClkHigh();
	psTM16XX->HWPort.pSetDataHigh();
	psTM16XX->HWPort.pSetStbHigh();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void TM16XX_LEDControl(sTM16XX_Typedef *psTM16XX, uint8_t u8DisplayControlCmd)
{		
		   
	/* Set display mode */
    TM16XX_WriteCmd(psTM16XX,TM16XX_CMD_DISPLAY_MODE_2_8);
	/* Set data cmd */
	TM16XX_WriteCmd(psTM16XX,TM16XX_CMD_DATA);	
	/* Set display address */
	TM16XX_WriteCmd(psTM16XX,TM16XX_CMD_ADDRESS);
	
	/* Write data to display address */	
	TM16XX_WriteDataAutoIncrease(psTM16XX);	
	//TM16XX_WriteByte(psTM16XX,psTM16XX->pu8Led[0]);
	//TM16XX_WriteByte(psTM16XX,psTM16XX->pu8Led[1]);
		
	/* Set display control cmd */
	TM16XX_WriteCmd(psTM16XX,TM16XX_CMD_DISPLAY_CONTROL | TM16XX_CMD_DUTY_10_16 | u8DisplayControlCmd);
	
	psTM16XX->HWPort.pSetClkHigh();
	psTM16XX->HWPort.pSetDataHigh();
	psTM16XX->HWPort.pSetStbHigh();
}
/* End of file */
