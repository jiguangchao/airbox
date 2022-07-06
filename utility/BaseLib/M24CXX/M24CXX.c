/***************************************************************************
* Designed by Osman Li <Li.haimeng@menred.com> 
* Copyright , Menred Group Corporation.
* This software is owned by Menred Group and is protected by and subject to 
* worldwide patent protection (china and foreign)
 ***************************************************************************/
 /***************************************************************************
* Release Notes:
*     V1.1  
*         Data: 
*          
*     V1.0  
*         Data:2015.1.26
*         Official release
****************************************************************************/

/*============================ INCLUDES ======================================*/

#include "..\BaselibInclude.h"


/*============================ MACROS ========================================*/
#define M24CXX_IIC_DEMOTEST                     (0) 
#define M24CXX_IIC_CMD_WRITE                    IIC_CMD_WRITE
#define M24CXX_IIC_CMD_READ                     IIC_CMD_READ

#define M24CXX_WRITE_OVER_PAGE_MAX_ENABLE       (1)              


#define M24CXX_PHY_BYTE_ADDRESS_ID              (0xA0)
#define M24CXX_PHY_PAGE_ADDRESS_ID              (0xB0)
#define M24CXX_DATA_HEADER                      (0xAA)
#define M24CXX_DATA_CHECK                       (0x51)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
EEPROM24CXX_Typedef *pM24CXX;
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXX_InitDataPoint(EEPROM24CXX_Typedef *pM24C)
{
    pM24CXX = pM24C;
}
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_WaitChipOK(void)
{
    if ( !pM24CXX->u8WritePageWait )
    {
        return eM24CXX_OK; 
    }

    return eM24CXX_ERR_WRITE_CHIP_OK;
}
/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXX_1msNeedCall(void)
{
    if ( pM24CXX->u8WritePageWait )
    {
        pM24CXX->u8WritePageWait--;
    }
} 
/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXX_WRInit(uint32_t u32DataAddress, uint8_t *pu8Data,uint16_t u16Nums)
{
    pM24CXX->u16NBytes      = u16Nums;
    pM24CXX->u16PageNums    = pM24CXX->u16NBytes/(eM24C256_PAGE_SIZE-2)+1;
    pM24CXX->u16PageID      = 0;
    pM24CXX->p8Bytes        = pu8Data;    
    pM24CXX->u16DataAddress = u32DataAddress&0xFFFF;
    pM24CXX->u16DataLength  = eM24C256_PAGE_SIZE;
}
/**
   * @brief 
   * @param 
   * @retval 
   */
void M24CXXClearAll(void)
{
    uint8_t i;
    uint16_t j;

    
    pM24CXX->u16DataLength  = eM24C256_PAGE_SIZE;

    for (i = 0; i < pM24CXX->u16DataLength; i++)
    {
        pM24CXX->p8Data[i] = 0xFF;
    }

    for ( j = 0; j < eM24C256_BYTES_SIZE/eM24C256_PAGE_SIZE;)
    {
        if ( eM24CXX_OK == M24CXX_WriteBytes() )
        {
            j++;
        }
    }    
}

/**
  * @brief
  * @param
  * @retval None
  */
uint8_t M24CXX_EEPROMWriteNBytes(void)
{
    uint16_t  i;
    uint8_t  u8DataCheck;
    //uint16_t  iPageOffset;

    if ( M24CXX_WaitChipOK() )
    {
        return !OK;
    }

    if ( pM24CXX->u16PageID < pM24CXX->u16PageNums )
    {
        pM24CXX->p8Data[0]    = M24CXX_DATA_HEADER;
        u8DataCheck           = pM24CXX->p8Data[0];

        //iPageOffset = pM24CXX->u16PageID*(pM24CXX->u16DataLength-2);

        if ( pM24CXX->u16NBytes >= pM24CXX->u16DataLength-2 )
        {
            for (i = 0; i < pM24CXX->u16DataLength-2; i++)
            {
                pM24CXX->p8Data[i+1] = pM24CXX->p8Bytes[i];
                u8DataCheck       += pM24CXX->p8Bytes[i];
            }
            pM24CXX->u16NBytes -= pM24CXX->u16DataLength-2;
            
        }
        else
        {
            for (i = 0; i < pM24CXX->u16NBytes; i++)
            {
                pM24CXX->p8Data[i+1] = pM24CXX->p8Bytes[i];
                u8DataCheck       += pM24CXX->p8Bytes[i];
            }
            for (i = pM24CXX->u16NBytes; i < pM24CXX->u16DataLength-1; i++)
            {
                pM24CXX->p8Data[i] = 0;
            }
                        
            pM24CXX->u16NBytes = 0;
        }
        pM24CXX->p8Bytes += (pM24CXX->u16DataLength-2);
        u8DataCheck ^= M24CXX_DATA_CHECK;
        pM24CXX->p8Data[pM24CXX->u16DataLength-1] = u8DataCheck;
        M24CXX_WriteBytes ();        
        pM24CXX->u16DataAddress += pM24CXX->u16DataLength;
        pM24CXX->u16PageID++;
    }
    else
    {
        pM24CXX->u16PageID   = 0;
        pM24CXX->u16PageNums = 0;
        return OK;
    }

    return !OK;
}
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t M24CXX_EEPROMReadNBytes(void)
{
    uint16_t  i;

    uint8_t  u8DataCheck;
    uint8_t   u8Status;
    

    u8DataCheck           = 0;
    u8Status              = !OK;
    
    while ( pM24CXX->u16PageID < pM24CXX->u16PageNums )
    {        
        M24CXX_ReadBytes();
        u8DataCheck = 0;
        for (i = 0; i < pM24CXX->u16DataLength-1; i++)
        {
            u8DataCheck += pM24CXX->p8Data[i];
        }            
        u8DataCheck ^= M24CXX_DATA_CHECK;
        

        if ( ( pM24CXX->p8Data[0] == M24CXX_DATA_HEADER )&&( u8DataCheck == pM24CXX->p8Data[pM24CXX->u16DataLength-1]) )
        {         
            if ( pM24CXX->u16NBytes >= pM24CXX->u16DataLength-2 )
            {
                for (i = 0; i < pM24CXX->u16DataLength-2; i++)
                {
                    pM24CXX->p8Bytes[i] = pM24CXX->p8Data[i+1];
                }
                pM24CXX->u16NBytes -= pM24CXX->u16DataLength-2;
            }
            else
            {
                for (i = 0; i < pM24CXX->u16NBytes; i++)
                {
                    pM24CXX->p8Bytes[i] = pM24CXX->p8Data[i+1];
                }
                pM24CXX->u16NBytes = 0;

                u8Status = OK;
            }
                                 
        }
        pM24CXX->p8Bytes += pM24CXX->u16DataLength-2;
        pM24CXX->u16DataAddress += pM24CXX->u16DataLength;
        pM24CXX->u16PageID++;
    }
    pM24CXX->u16PageNums = 0;
    return u8Status;
}
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_ReadBytes(void)
{
    uint16_t i=0; 
    uint8_t u8Data;
    
    if ( pM24CXX->u8PhyAddress > 7)
    {
        return eM24CXX_ERR_INPUT_PHY_ADDRESS;
    }
        
    u8Data = pM24CXX->u8PhyAddress;
    u8Data <<= 1;
    u8Data |= M24CXX_PHY_BYTE_ADDRESS_ID;

    I2C_start(&pM24CXX->HWPort);
    I2C_send_byte(&pM24CXX->HWPort, u8Data);

    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_WRITE_PHY_NO_ACK;
    }   


    if ( pM24CXX->u8ChipType >= eM24CXX_CHIP_M24C04 )
    {
        u8Data = pM24CXX->u16DataAddress>>8;
        I2C_send_byte(&pM24CXX->HWPort, u8Data);
        if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
        {
            return eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK;
        }
    }
    
    u8Data = pM24CXX->u16DataAddress&0xFF;
    I2C_send_byte(&pM24CXX->HWPort, u8Data);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK;
    }

    u8Data = M24CXX_PHY_BYTE_ADDRESS_ID|(pM24CXX->u8PhyAddress<<1)|M24CXX_IIC_CMD_READ;
    
    I2C_start(&pM24CXX->HWPort);
    I2C_send_byte(&pM24CXX->HWPort, u8Data);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_READ_DATA_WRITE_PHY_NO_ACK;
    }

    //pI2C->pSetSdaHigh();

    for (i = 0;i < pM24CXX->u16DataLength;i++)
    {        
        pM24CXX->p8Data[i] = I2C_receive_byte(&pM24CXX->HWPort); 

        if ( i <= (pM24CXX->u16DataLength-1) )
        {    
            I2C_ack(&pM24CXX->HWPort); 
        }
        else
        {
            I2C_no_ack(&pM24CXX->HWPort);
        }
    }     
    
    I2C_stop(&pM24CXX->HWPort);

    return eM24CXX_OK; 
}
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_WriteBytes(void)
{
    uint16_t i=0;
    uint8_t u8Data;

    if ( pM24CXX->u8WritePageWait )
    {
        return eM24CXX_ERR_WRITE_CHIP_OK;
    }

    if ( pM24CXX->u8PhyAddress > 7)
    {
        return eM24CXX_ERR_INPUT_PHY_ADDRESS;
    }
    //    M24CXX_IIC_CMD_READ
    u8Data = M24CXX_PHY_BYTE_ADDRESS_ID|(pM24CXX->u8PhyAddress<<1)|M24CXX_IIC_CMD_WRITE;

    I2C_start(&pM24CXX->HWPort);
    
    I2C_send_byte(&pM24CXX->HWPort, u8Data);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_WRITE_PHY_NO_ACK;
    }   

	if ( pM24CXX->u8ChipType >= eM24CXX_CHIP_M24C04 )
    {
        u8Data = pM24CXX->u16DataAddress>>8;
        I2C_send_byte(&pM24CXX->HWPort, u8Data);
        if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
        {
            return eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK;
        }
    }

    u8Data = pM24CXX->u16DataAddress&0xFF;
    I2C_send_byte(&pM24CXX->HWPort, u8Data);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK;
    }

    for( i = 0; i < pM24CXX->u16DataLength;i++)
    {
        I2C_send_byte(&pM24CXX->HWPort, pM24CXX->p8Data[i]);

        if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
        {
            I2C_stop(&pM24CXX->HWPort);
            return eM24CXX_ERR_WRITE_DATA_NO_ACK;
        }        
    }	    

    I2C_stop(&pM24CXX->HWPort);
    pM24CXX->u8WritePageWait = 5;
    return eM24CXX_OK; 
}

/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_ReadPage(void)
{
    uint16_t i=0; 
    uint8_t u8Data;
    
    if ( pM24CXX->u8PhyAddress > 7)
    {
        return eM24CXX_ERR_INPUT_PHY_ADDRESS;
    }

    u8Data = pM24CXX->u8PhyAddress;
    u8Data <<= 1;
    u8Data |= M24CXX_PHY_PAGE_ADDRESS_ID|M24CXX_IIC_CMD_WRITE;

    I2C_start(&pM24CXX->HWPort);
    I2C_send_byte(&pM24CXX->HWPort, u8Data);

    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_WRITE_PHY_NO_ACK;
    }   

    if ( pM24CXX->u8ChipType >= eM24CXX_CHIP_M24C04 )
    {
        I2C_send_byte(&pM24CXX->HWPort, pM24CXX->u16DataAddress>>8);
        if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
        {
            return eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK;
        }
    }
    

    I2C_send_byte(&pM24CXX->HWPort, pM24CXX->u16DataAddress&0xFF);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK;
    }

    u8Data = pM24CXX->u8PhyAddress;
    u8Data <<= 1;
    u8Data |= M24CXX_PHY_PAGE_ADDRESS_ID|M24CXX_IIC_CMD_READ;

    I2C_start(&pM24CXX->HWPort);
    I2C_send_byte(&pM24CXX->HWPort, u8Data);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_READ_DATA_WRITE_PHY_NO_ACK;
    }

    for (i = 0;i < pM24CXX->u16DataLength;i++)
    {        
        pM24CXX->p8Data[i] = I2C_receive_byte(&pM24CXX->HWPort); 

        if ( i != (pM24CXX->u16DataLength-1) )
        {    
            I2C_ack(&pM24CXX->HWPort); 
        }
    }     
    I2C_no_ack(&pM24CXX->HWPort);
    I2C_stop(&pM24CXX->HWPort);

    return eM24CXX_OK; 
}
/**
   * @brief 
   * @param 
   * @retval 
   */
eM24CXX_RETURN_TYPE M24CXX_WritePage(void)
{        
    uint16_t i=0;
    uint8_t u8Data;
    
    if ( pM24CXX->u8PhyAddress > 7)
    {
        return eM24CXX_ERR_INPUT_PHY_ADDRESS;
    }
        
    u8Data = pM24CXX->u8PhyAddress;
    u8Data <<= 1;
    u8Data |= M24CXX_PHY_PAGE_ADDRESS_ID;

    I2C_start(&pM24CXX->HWPort);
    
    I2C_send_byte(&pM24CXX->HWPort, u8Data);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_WRITE_PHY_NO_ACK;
    }   

	if ( pM24CXX->u8ChipType >= eM24CXX_CHIP_M24C04 )
    {
        I2C_send_byte(&pM24CXX->HWPort, pM24CXX->u16DataAddress>>8);
        if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
        {
            return eM24CXX_ERR_DATA_ADDRESS_H_NO_ACK;
        }
    }

    I2C_send_byte(&pM24CXX->HWPort, pM24CXX->u16DataAddress&0xFF);
    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {
        return eM24CXX_ERR_DATA_ADDRESS_L_NO_ACK;
    }

    for( i = 0; i < pM24CXX->u16DataLength;i++)
    {
        I2C_send_byte(&pM24CXX->HWPort, pM24CXX->p8Data[i]);       
    }	    

    if ( OK != I2C_wait_ack(&pM24CXX->HWPort) )
    {

    }
    I2C_stop(&pM24CXX->HWPort);

    return eM24CXX_OK; 
}


/* EOF */
