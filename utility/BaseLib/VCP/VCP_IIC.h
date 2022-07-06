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

#ifndef __VCP_IIC_H__
#define __VCP_IIC_H__

/*============================ INCLUDES ======================================*/
#include "stdbool.h"
#include "stdint.h"

/*============================ MACROS ========================================*/
#define IIC_CMD_WRITE                    (0x00)
#define IIC_CMD_READ                     (0x01)
#define IIC_N_DELAY                      (10)
#define IIC_N_DELAY_L                    (5)
/*============================ MACROFIED FUNCTIONS ===========================*/

/*============================ TYPES =========================================*/

typedef struct
{
     void(*pSetSclHigh)(void);
     void(*pSetSclLow)(void);
     void(*pSetSdaHigh)(void);
     void(*pSetSdaLow)(void);
     void(*pSetSdaInput)(void);
     void(*pSetSdaOutput)(void);
     uint8_t(*pGetSdaGpio)(void);
     uint8_t(*pGetSclGpio)(void);
     void(*pWait)(uint16_t u16Delay);
}I2C_BitbangDevice_t;


/*
typedef void (*pI2C_init)(I2C_BitbangDevice_t *me);
typedef void (*pI2C_start)(I2C_BitbangDevice_t *me);
typedef void (*pI2C_stop)(I2C_BitbangDevice_t *me); 
typedef void (*pI2C_ack)(I2C_BitbangDevice_t *me); 
typedef void (*pI2C_no_ack)(I2C_BitbangDevice_t *me); 
typedef bool (*pI2C_wait_ack)(I2C_BitbangDevice_t *me); 
typedef void (*pI2C_send_byte)(I2C_BitbangDevice_t *me,uint8_t sendData);
typedef uint8_t (*pI2C_receive_byte)(I2C_BitbangDevice_t *me);
typedef void (*pI2C_InterfaceReset)(I2C_BitbangDevice_t *me);
*/
typedef struct
{
    void    (*pInit)(I2C_BitbangDevice_t *me);
    void    (*pStart)(I2C_BitbangDevice_t *me);
    void    (*pStop)(I2C_BitbangDevice_t *me); 
    void    (*pAck)(I2C_BitbangDevice_t *me); 
    void    (*pNoAck)(I2C_BitbangDevice_t *me); 
    uint8_t (*pWaitAck)(I2C_BitbangDevice_t *me); 
    void    (*pSendByte)(I2C_BitbangDevice_t *me,uint8_t u8SendData);
    uint8_t (*pReceiveByte)(I2C_BitbangDevice_t *me);
    void    (*pInterfaceReset)(I2C_BitbangDevice_t *me);
}I2C_Func_Typedef;


typedef struct 
{
    uint8_t  u8PhyAddress;
    uint16_t u16DataMax;
    uint16_t u16DataLength;
    uint8_t  *p8Data;

    union
    {
        uint16_t u16DataAddress;
        uint8_t  u8DataAddress;
        uint16_t u16Cmd;
        uint8_t  u8Cmd;
        uint16_t u16RegisterAddress;
        uint8_t  u8RegisterAddress;
    };  
    //uint8_t u8Data[128];     

    //I2C_BitbangDevice_t HwPort;
    //I2C_Func_Typedef    Fun;
}I2C_Bus_Typedef;



/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_init(I2C_BitbangDevice_t *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_start(I2C_BitbangDevice_t *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_stop(I2C_BitbangDevice_t *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_ack(I2C_BitbangDevice_t *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_no_ack(I2C_BitbangDevice_t *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_wait_ack(I2C_BitbangDevice_t *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_send_byte(I2C_BitbangDevice_t *pI2C,uint8_t sendData);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_receive_byte(I2C_BitbangDevice_t *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_InterfaceReset(I2C_BitbangDevice_t *pI2C);

#if 0
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_init(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_start(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_stop(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_ack(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_no_ack(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_wait_ack(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_send_byte(I2C_Bus_Typedef *pI2C,uint8_t sendData);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_receive_byte(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
void I2C_InterfaceReset(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
uint8_t I2C_WriteAddress(uint8_t u8Cmd,uint8_t u8PhyAdd,I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
//uint8_t I2C_WriteDataWaitAck(uint8_t u8Data,I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
//uint8_t I2C_ReadDataWithAck(I2C_Bus_Typedef *pI2C);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
//uint8_t I2C_ReadDataWithNoAck(I2C_Bus_Typedef *pI2C);
#endif

#endif
/* EOF */
