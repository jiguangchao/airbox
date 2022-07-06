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

#ifndef __VCP_SPI_H__
#define __VCP_SPI_H__

/*============================ INCLUDES ======================================*/
#include "stdbool.h"
#include "stdint.h"

/*============================ MACROS ========================================*/
//#define IIC_SPEED_DELAY      (100)//100us

#if BSP_OLED_VCP_EN > 0

/*============================ MACROFIED FUNCTIONS ===========================*/

/*============================ TYPES =========================================*/

    typedef struct
    {
        void (*pSetRESETLow)(void);
        void (*pSetRESETHigh)(void);
        void (*pSetCSLow)(void);
        void (*pSetCSHigh)(void);   
        void (*pSetCommand)(void);
        void (*pSetData)(void);     
        void (*pSetSclkHigh)(void);
        void (*pSetSclkLow)(void);
        void (*pSetSdinHigh)(void);     
        void (*pSetSdinLow)(void);
        void (*pWait)(uint16_t u16Delay);
    }SPI_BitbangDevice_t;


    //typedef void (*pSPI_Reset)(SPI_BitbangDevice_t *me);
    //typedef void (*pSPI_send_byte)(SPI_BitbangDevice_t *me,uint8_t sendData);
    //typedef uint8_t (*pSPI_receive_byte)(SPI_BitbangDevice_t *me);

    typedef struct
    {
        void (*pVCP_SPI_Reset)         (SPI_BitbangDevice_t *pSPI);
        void (*pVCP_SPI_WriteCommand)  (SPI_BitbangDevice_t *pSPI,uint8_t u8Command);
        void (*pVCP_SPI_WriteCommands) (SPI_BitbangDevice_t *pSPI,uint8_t *pu8Command,uint8_t u8CommandLength);
        void (*pVCP_SPI_WriteByte)     (SPI_BitbangDevice_t *pSPI,uint8_t u8Data);
        void (*pVCP_SPI_WriteNBytes)   (SPI_BitbangDevice_t *pSPI,uint8_t *pu8Data,uint16_t u16DataLength);
    }SPI_Func_Typedef;


    typedef struct 
    {
        SPI_BitbangDevice_t HwPort;

        SPI_Func_Typedef    Fun;

    }SPI_Bus_Typedef;



    /*============================ GLOBAL VARIABLES ==============================*/
    /*============================ LOCAL VARIABLES ===============================*/
    /*============================ PROTOTYPES ====================================*/
    void VCP_SPI_Reset(SPI_BitbangDevice_t *pSPI);
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteCommand(SPI_BitbangDevice_t *pSPI,uint8_t u8Command);
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteCommands(SPI_BitbangDevice_t *pSPI,uint8_t *pu8Command,uint8_t u8CommandLength);
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteByte(SPI_BitbangDevice_t *pSPI,uint8_t u8Data);
    /*! \note  
     *  \param  
     *  \retval  
     *  \retval  
     */ 
    void VCP_SPI_WriteNBytes(SPI_BitbangDevice_t *pSPI,uint8_t *pu8Data,uint16_t u16DataLength);

#endif

#endif
/* EOF */
