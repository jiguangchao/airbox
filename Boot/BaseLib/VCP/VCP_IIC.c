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
//#define IIC_NOTE       (0)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_init(I2C_BitbangDevice_t *pI2C)
{
    pI2C->pSetSclHigh();
    pI2C->pSetSdaHigh();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_start(I2C_BitbangDevice_t *pI2C)
{    
    /* Init */
    //pI2C->pSetSclLow(); 
     
    //pI2C->pSetSdaLow(); 
    //pI2C->pWait(IIC_N_DELAY*5);
    
    if ( !pI2C->pGetSclGpio() )
    {
        if( !pI2C->pGetSdaGpio() )
        {
            pI2C->pSetSclLow(); 
            pI2C->pSetSdaOutput();
            pI2C->pSetSdaLow(); 
            pI2C->pWait(IIC_N_DELAY*5);
        }
        else
        {
            pI2C->pSetSdaOutput();
        }

        pI2C->pSetSdaHigh();  
        pI2C->pWait(IIC_N_DELAY*2);  
        pI2C->pSetSclHigh();
        pI2C->pWait(IIC_N_DELAY);  
        pI2C->pSetSdaLow();    
        pI2C->pWait(IIC_N_DELAY);
        pI2C->pSetSclLow();  
        pI2C->pWait(IIC_N_DELAY);
    }
    else 
    {
        pI2C->pSetSdaOutput();

        pI2C->pSetSdaHigh();
        pI2C->pSetSclHigh();
        pI2C->pWait(IIC_N_DELAY);  
        pI2C->pSetSdaLow();    
        pI2C->pWait(IIC_N_DELAY);
        pI2C->pSetSclLow();  
    }
    
         
      
    //pI2C->pWait(IIC_N_DELAY);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_stop(I2C_BitbangDevice_t *pI2C)
{
    pI2C->pSetSclLow();
    pI2C->pWait(IIC_N_DELAY*2);
    pI2C->pSetSdaOutput();
    pI2C->pSetSdaLow();    
    pI2C->pSetSclHigh();
    pI2C->pWait(IIC_N_DELAY*2);    
    pI2C->pSetSdaHigh();
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_ack(I2C_BitbangDevice_t *pI2C)
{
    pI2C->pSetSclLow(); 
    pI2C->pWait(IIC_N_DELAY);
    pI2C->pSetSdaLow();
    pI2C->pSetSdaOutput();
    
    pI2C->pWait(IIC_N_DELAY*2);
    pI2C->pSetSclHigh();
    pI2C->pWait(IIC_N_DELAY*2);
    //pI2C->pSetSclLow(); 
    //pI2C->pWait(IIC_N_DELAY);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_no_ack(I2C_BitbangDevice_t *pI2C)
{
    //pI2C->pSetSclHigh();
    //pI2C->pWait(IIC_N_DELAY);

    pI2C->pSetSclLow();
    pI2C->pWait(IIC_N_DELAY);
    
    pI2C->pSetSdaHigh();
    pI2C->pSetSdaOutput();
           
    pI2C->pWait(IIC_N_DELAY);
    pI2C->pSetSclHigh();
    pI2C->pWait(IIC_N_DELAY);    
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_wait_ack(I2C_BitbangDevice_t *pI2C)
{      
    uint8_t  u8Status;
    uint16_t u16WaitNop;
    
    pI2C->pSetSdaInput();
    pI2C->pSetSdaHigh();
    //pI2C->pSetSclLow();
    pI2C->pWait(IIC_N_DELAY);

    pI2C->pSetSclHigh();
    //pI2C->pWait(IIC_N_DELAY);
    
    u16WaitNop = 250;
    u8Status   = !OK;

    while(u16WaitNop)
    {
        u16WaitNop--;
        if( pI2C->pGetSdaGpio() )
        {            
            pI2C->pWait(IIC_N_DELAY);
        }
        else
        {
            u8Status = OK;   
            break;
        }
    }
    pI2C->pSetSclLow();
    //pI2C->pSetSdaOutput();    
    //pI2C->pWait(IIC_N_DELAY); 

    return u8Status;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_send_byte(I2C_BitbangDevice_t *pI2C,uint8_t sendData)
{
    uint8_t i;
    
    i = 8;

    pI2C->pSetSclLow();
    pI2C->pWait(IIC_N_DELAY);
    pI2C->pSetSdaOutput();
    

    while (i)
    {               
        if (sendData&0x80)
        {
            pI2C->pSetSdaHigh();
        }
        else
        { 
            pI2C->pSetSdaLow(); 
        }
        
        sendData<<=1;
        
        pI2C->pWait(IIC_N_DELAY_L);

        pI2C->pSetSclHigh();
        pI2C->pWait(IIC_N_DELAY);

        pI2C->pSetSclLow();        
        //pI2C->pWait(IIC_N_DELAY);
        i--;
    }

    //pI2C->pSetSclLow();        
    //pI2C->pWait(IIC_N_DELAY);
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_receive_byte(I2C_BitbangDevice_t *pI2C)
{   
    uint8_t i=0x80;
    uint8_t ReceiveByte=0;
    /* Before IIC SDA pin change to input mode,SDA should out high logic 
    that prevent the pin from being pulled low by VSS -- 20210113*/
    pI2C->pSetSclLow();
    pI2C->pSetSdaInput();
    pI2C->pWait(IIC_N_DELAY);
    //pI2C->pSetSdaHigh();    
    //pI2C->pWait(IIC_N_DELAY*2);
    
    while(i)
    {
        pI2C->pSetSclHigh();
        pI2C->pWait(IIC_N_DELAY);
        if (pI2C->pGetSdaGpio())
        {
            ReceiveByte |= i;
        }
        pI2C->pSetSclLow();
        pI2C->pWait(IIC_N_DELAY_L);
        i >>= 1;
    }   

    return ReceiveByte;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_InterfaceReset(I2C_BitbangDevice_t *pI2C)
{   
    uint8_t u8Count;

    /* IIC start */ 
    pI2C->pSetSdaHigh();
    pI2C->pSetSclHigh();
    pI2C->pWait(IIC_N_DELAY);
    pI2C->pSetSdaLow();

    u8Count = 100;

    while (u8Count) 
    {
        u8Count--;
        
        pI2C->pWait(IIC_N_DELAY);
        
        pI2C->pSetSclHigh();
        
        pI2C->pWait(IIC_N_DELAY);
        
        pI2C->pSetSclLow();
        
        pI2C->pWait(IIC_N_DELAY);
    }
    pI2C->pSetSdaHigh();
    pI2C->pSetSclHigh();
}


/* EOF */
