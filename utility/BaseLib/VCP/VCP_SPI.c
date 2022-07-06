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
#if BSP_OLED_VCP_EN > 0
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
    const uint8_t u8BitMask[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */
    void VCP_SPI_Reset(SPI_BitbangDevice_t *pSPI)
    {       
        pSPI->pSetRESETHigh();    
    #if OLED_SSD1305_SPI_3_WIRE_EN > 0
        pSPI->pSetCSHigh();  
    #endif     
        pSPI->pSetCommand();
        pSPI->pSetSclkHigh();
        pSPI->pSetSdinHigh();   
        
          
        pSPI->pSetRESETLow();
        pSPI->pWait(600);
        pSPI->pSetRESETHigh();
    #if OLED_SSD1305_SPI_3_WIRE_EN == 1
        pSPI->pSetCSLow();
    #endif
    }
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteCommand(SPI_BitbangDevice_t *pSPI,uint8_t u8Command)
    {
        uint8_t u8i;

    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSLow();
    #endif

        pSPI->pSetCommand();    
        pSPI->pSetSclkHigh();
        //pSPI->pWait(10);
        for ( u8i = 0; u8i < 8; u8i ++ )
        {
            pSPI->pSetSclkLow();        
            //pSPI->pWait(1);
            
            if ( u8Command & u8BitMask[u8i] )
            {
                pSPI->pSetSdinHigh();
            }
            else
            {
                pSPI->pSetSdinLow();
            }
            
            //pSPI->pWait(1);
            pSPI->pSetSclkHigh();

            
            //pSPI->pWait(1);
        }
    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSHigh();  
    #endif      
        pSPI->pSetSdinHigh();
    }
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteCommands(SPI_BitbangDevice_t *pSPI,uint8_t *pu8Command,uint8_t u8CommandLength)
    {
        uint8_t u8i;
        uint8_t u8j;

    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSLow();
    #endif

        pSPI->pSetCommand();
        pSPI->pSetSclkHigh();
        //pSPI->pWait(10);
        for ( u8j = 0; u8j < u8CommandLength; u8j++ )
        {
            for ( u8i = 0; u8i < 8; u8i ++ )
            {
                pSPI->pSetSclkLow();
                //pSPI->pWait(1);
                if ( pu8Command[u8j] & u8BitMask[u8i] )
                {
                    pSPI->pSetSdinHigh();
                }
                else
                {
                    pSPI->pSetSdinLow();
                }
                //pSPI->pWait(1);
                pSPI->pSetSclkHigh(); 
                //pSPI->pWait(1);
            }
        }

    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSHigh();
    #endif
        pSPI->pSetSdinHigh();
    }
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteByte(SPI_BitbangDevice_t *pSPI,uint8_t u8Data)
    {    
        uint8_t u8i;

    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSLow();
    #endif
        pSPI->pSetData();    
        pSPI->pSetSclkHigh();    
        //pSPI->pWait(10);
        for ( u8i = 0; u8i < 8; u8i ++ )
        {
            pSPI->pSetSclkLow();
            //pSPI->pWait(1);
            
            if ( u8Data & u8BitMask[u8i] )
            {
                pSPI->pSetSdinHigh();
            }
            else
            {
                pSPI->pSetSdinLow();
            }
            
            //pSPI->pWait(1);
            pSPI->pSetSclkHigh();        

            
            //pSPI->pWait(1);
        }
    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSHigh();
    #endif
        pSPI->pSetSdinHigh();
    }
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteNBytes(SPI_BitbangDevice_t *pSPI,uint8_t *pu8Data,uint16_t u16DataLength)
    {   
        uint8_t u8i;
        uint16_t u16j;

    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSLow();
    #endif

        pSPI->pSetData();

        pSPI->pSetSclkHigh();
        //pSPI->pWait(10);
        for ( u16j = 0; u16j < u16DataLength; u16j++ )
        {
            for ( u8i = 0; u8i < 8; u8i ++ )
            {
                pSPI->pSetSclkLow();
                
                //pSPI->pWait(1);
                if ( pu8Data[u16j]& u8BitMask[u8i] )
                {
                    pSPI->pSetSdinHigh();
                }
                else
                {
                    pSPI->pSetSdinLow();
                }
                
                //pSPI->pWait(1);
                pSPI->pSetSclkHigh();

                //pSPI->pWait(1);
            }

            //pSPI->pWait(10);
        }
        
    #if OLED_SSD1305_SPI_4_WIRE_EN > 0
        pSPI->pSetCSHigh();
    #endif
        pSPI->pSetSdinHigh();
    }
#endif
/* EOF */
